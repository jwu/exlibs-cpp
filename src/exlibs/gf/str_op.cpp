// ======================================================================================
// File         : String.cpp
// Author       : Wu Jie 
// Last Change  : 10/19/2008 | 22:01:03 PM | Sunday,October
// Description  : 
// ======================================================================================

///////////////////////////////////////////////////////////////////////////////
// includes
///////////////////////////////////////////////////////////////////////////////

#include "exlibs.h"

// #########################
namespace ex { 
// #########################

// ######################### 
namespace str { 
// ######################### 

// ------------------------------------------------------------------
// Desc: 
// ------------------------------------------------------------------

// char
void simplify( char* _in_out_filename, bool _stripAll )
{
    int		components = 0;
    char	*p, *tail, *start;
    bool    stripping_disabled = false;
    bool    relative = true;

    //
    p = _in_out_filename;

    //
    if (p[1] == ':')	    /* skip "x:" */
        p += 2;

    if (str::isPathSep(*p))
    {
        relative = false;
        do
            ++p;
        while (str::isPathSep(*p));
    }
    start = p;	    /* remember start after "c:/" or "/" or "///" */

    do
    {
        /* At this point "p" is pointing to the char following a single "/"
         * or "p" is at the "start" of the (absolute or relative) path name. */
        if (str::isPathSep(*p))
            str::move(p, p + 1);		/* remove duplicate "/" */
        else if (p[0] == '.' && (str::isPathSep(p[1]) || p[1] == EX_NUL))
        {
            if (p == start && relative && !_stripAll )
                p += 1 + (p[1] != EX_NUL);	/* keep single "." or leading "./" */
            else
            {
                /* Strip "./" or ".///".  If we are at the end of the file name
                 * and there is no trailing path separator, either strip "/." if
                 * we are after "start", or strip "." if we are at the beginning
                 * of an absolute path name . */
                tail = p + 1;
                if (p[1] != EX_NUL)
                    while (str::isPathSep(*tail))
                        ++tail;
                else if (p > start)
                    --p;		/* strip preceding path separator */
                str::move(p, tail);
            }
        }
        else if (p[0] == '.' && p[1] == '.' &&
                 (str::isPathSep(p[2]) || p[2] == EX_NUL))
        {
            /* Skip to after ".." or "../" or "..///". */
            tail = p + 2;
            while (str::isPathSep(*tail))
                ++tail;

            if (components > 0)		/* strip one preceding component */
            {
                bool    do_strip = false;
                char    saved_char;
                struct stat	st;

                /* Don't strip for an erroneous file name. */
                if (!stripping_disabled)
                {
                    /* If the preceding component does not exist in the file
                     * system, we strip it.  On Unix, we don't accept a symbolic
                     * link that refers to a non-existent file. */
                    saved_char = p[-1];
                    p[-1] = EX_NUL;
#if ( EX_PLATFORM == EX_LINUX )
                    if (lstat((char *)_in_out_filename, &st) < 0)
#else
                    if (ex::stat((char *)_in_out_filename, &st) < 0)
#endif // end EX_PLATFORM 
                            do_strip = true;
                    p[-1] = saved_char;

                    --p;
                    /* Skip back to after previous '/'. */
                    while (p > start && !ex::str::afterPathSep(start, p))
                        --p; // XXX: mb_ptr_back(start, p); 

                    if (!do_strip)
                    {
                        /* If the component exists in the file system, check
                         * that stripping it won't change the meaning of the
                         * file name.  first get information about the
                         * unstripped file name.  This may fail if the component
                         * to strip is not a searchable directory (but a regular
                         * file, for instance), since the trailing "/.." cannot
                         * be applied then.  We don't strip it then since we
                         * don't want to replace an erroneous file name by
                         * a valid one, and we disable stripping of later
                         * components. */
                        saved_char = *tail;
                        *tail = EX_NUL;
                        if (ex::stat((char *)_in_out_filename, &st) >= 0)
                            do_strip = true;
                        else
                            stripping_disabled = true;
                        *tail = saved_char;
#if ( EX_PLATFORM == EX_LINUX )
                        if (do_strip)
                        {
                            struct stat	new_st;

                            /* On Unix, the check for the unstripped file name
                             * above works also for a symbolic link pointing to
                             * a searchable directory.  But then the parent of
                             * the directory pointed to by the link must be the
                             * same as the stripped file name.  (The latter
                             * exists in the file system since it is the
                             * component's parent directory.) */
                            if (p == start && relative)
                                (void)ex::stat(".", &new_st);
                            else
                            {
                                saved_char = *p;
                                *p = EX_NUL;
                                (void)ex::stat((char *)_in_out_filename, &new_st);
                                *p = saved_char;
                            }

                            if (new_st.st_ino != st.st_ino ||
                                new_st.st_dev != st.st_dev)
                            {
                                do_strip = false;
                                /* We don't disable stripping of later
                                 * components since the unstripped path name is
                                 * still valid. */
                            }
                        }
#endif // end EX_PLATFORM 
                    }
                }

                if (!do_strip)
                {
                    /* Skip the ".." or "../" and reset the counter for the
                     * components that might be stripped later on. */
                    p = tail;
                    components = 0;
                }
                else
                {
                    /* Strip previous component.  If the result would get empty
                     * and there is no trailing path separator, leave a single
                     * "." instead.  If we are at the end of the file name and
                     * there is no trailing path separator and a preceding
                     * component is left after stripping, strip its trailing
                     * path separator as well. */
                    if (p == start && relative && tail[-1] == '.')
                    {
                        *p++ = '.';
                        *p = EX_NUL;
                    }
                    else
                    {
                        if (p > start && tail[-1] == '.')
                            --p;
                        str::move(p, tail);	/* strip previous component */
                    }

                    --components;
                }
            }
            else if (p == start && !relative)	/* leading "/.." or "/../" */
                str::move(p, tail);		/* strip ".." or "../" */
            else
            {
                if (p == start + 2 && p[-2] == '.')	/* leading "./../" */
                {
                    str::move(p - 2, p);			/* strip leading "./" */
                    tail -= 2;
                }
                p = tail;		/* skip to char after ".." or "../" */
            }
        }
        else
        {
            ++components;		/* simple path component */
            p = ex::str::getNextPathComp(p);
        }
    } while (*p != EX_NUL);
}

// wchar
void simplify( wchar* _in_out_filename, bool _stripAll )
{
    int		components = 0;
    wchar	*p, *tail, *start;
    bool    stripping_disabled = false;
    bool    relative = true;

    //
    p = _in_out_filename;

    //
    if (p[1] == L':')	    /* skip "x:" */
        p += 2;

    if (str::isPathSep(*p))
    {
        relative = false;
        do
            ++p;
        while (str::isPathSep(*p));
    }
    start = p;	    /* remember start after "c:/" or "/" or "///" */

    do
    {
        /* At this point "p" is pointing to the char following a single "/"
         * or "p" is at the "start" of the (absolute or relative) path name. */
        if (str::isPathSep(*p))
            str::move(p, p + 1);		/* remove duplicate "/" */
        else if (p[0] == L'.' && (str::isPathSep(p[1]) || p[1] == EX_NUL))
        {
            if (p == start && relative && !_stripAll )
                p += 1 + (p[1] != EX_NUL);	/* keep single "." or leading "./" */
            else
            {
                /* Strip "./" or ".///".  If we are at the end of the file name
                 * and there is no trailing path separator, either strip "/." if
                 * we are after "start", or strip "." if we are at the beginning
                 * of an absolute path name . */
                tail = p + 1;
                if (p[1] != EX_NUL)
                    while (str::isPathSep(*tail))
                        ++tail;
                else if (p > start)
                    --p;		/* strip preceding path separator */
                str::move(p, tail);
            }
        }
        else if (p[0] == L'.' && p[1] == '.' &&
                 (str::isPathSep(p[2]) || p[2] == EX_NUL))
        {
            /* Skip to after ".." or "../" or "..///". */
            tail = p + 2;
            while (str::isPathSep(*tail))
                ++tail;

            if (components > 0)		/* strip one preceding component */
            {
                bool    do_strip = false;
                wchar   saved_char;
                struct _stat st;

                /* Don't strip for an erroneous file name. */
                if (!stripping_disabled)
                {
                    /* If the preceding component does not exist in the file
                     * system, we strip it.  On Unix, we don't accept a symbolic
                     * link that refers to a non-existent file. */
                    saved_char = p[-1];
                    p[-1] = EX_NUL;
#if ( EX_PLATFORM == EX_LINUX )
                    if (lstat((wchar *)_in_out_filename, &st) < 0)
#else
                    if (ex::stat((wchar *)_in_out_filename, &st) < 0)
#endif // end EX_PLATFORM 
                            do_strip = true;
                    p[-1] = saved_char;

                    --p;
                    /* Skip back to after previous '/'. */
                    while (p > start && !ex::str::afterPathSep(start, p))
                        --p; // XXX: mb_ptr_back(start, p); 

                    if (!do_strip)
                    {
                        /* If the component exists in the file system, check
                         * that stripping it won't change the meaning of the
                         * file name.  first get information about the
                         * unstripped file name.  This may fail if the component
                         * to strip is not a searchable directory (but a regular
                         * file, for instance), since the trailing "/.." cannot
                         * be applied then.  We don't strip it then since we
                         * don't want to replace an erroneous file name by
                         * a valid one, and we disable stripping of later
                         * components. */
                        saved_char = *tail;
                        *tail = EX_NUL;
                        if (ex::stat((wchar *)_in_out_filename, &st) >= 0)
                            do_strip = true;
                        else
                            stripping_disabled = true;
                        *tail = saved_char;
#if ( EX_PLATFORM == EX_LINUX )
                        if (do_strip)
                        {
                            struct stat	new_st;

                            /* On Unix, the check for the unstripped file name
                             * above works also for a symbolic link pointing to
                             * a searchable directory.  But then the parent of
                             * the directory pointed to by the link must be the
                             * same as the stripped file name.  (The latter
                             * exists in the file system since it is the
                             * component's parent directory.) */
                            if (p == start && relative)
                                (void)ex::stat(".", &new_st);
                            else
                            {
                                saved_char = *p;
                                *p = EX_NUL;
                                (void)ex::stat((wchar *)_in_out_filename, &new_st);
                                *p = saved_char;
                            }

                            if (new_st.st_ino != st.st_ino ||
                                new_st.st_dev != st.st_dev)
                            {
                                do_strip = false;
                                /* We don't disable stripping of later
                                 * components since the unstripped path name is
                                 * still valid. */
                            }
                        }
#endif // end EX_PLATFORM 
                    }
                }

                if (!do_strip)
                {
                    /* Skip the ".." or "../" and reset the counter for the
                     * components that might be stripped later on. */
                    p = tail;
                    components = 0;
                }
                else
                {
                    /* Strip previous component.  If the result would get empty
                     * and there is no trailing path separator, leave a single
                     * "." instead.  If we are at the end of the file name and
                     * there is no trailing path separator and a preceding
                     * component is left after stripping, strip its trailing
                     * path separator as well. */
                    if (p == start && relative && tail[-1] == L'.')
                    {
                        *p++ = L'.';
                        *p = EX_NUL;
                    }
                    else
                    {
                        if (p > start && tail[-1] == L'.')
                            --p;
                        str::move(p, tail);	/* strip previous component */
                    }

                    --components;
                }
            }
            else if (p == start && !relative)	/* leading "/.." or "/../" */
                str::move(p, tail);		/* strip ".." or "../" */
            else
            {
                if (p == start + 2 && p[-2] == L'.')	/* leading "./../" */
                {
                    str::move(p - 2, p);			/* strip leading "./" */
                    tail -= 2;
                }
                p = tail;		/* skip to char after ".." or "../" */
            }
        }
        else
        {
            ++components;		/* simple path component */
            p = ex::str::getNextPathComp(p);
        }
    } while (*p != EX_NUL);
}

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

// ======================================================== 
// char ver 
// ======================================================== 

int idx ( const char* _str, const char* _needle, int _start_idx )
{
    char* haystack;
    char* save_haystack;
    char* pos;

    save_haystack = haystack = const_cast<char*>(_str);
    int ret = -1;

    if ( _needle == NULL || haystack == NULL )
        return -1;		/* type error; errmsg already given */

    if ( _start_idx >= int(str::len(haystack)) )
        return -1;

    if ( _start_idx >= 0 )
        haystack += _start_idx;

    pos	= strstr(haystack, _needle);
    if ( pos != NULL )
        ret = int(pos - save_haystack);

    return ret;
}

// ======================================================== 
// wchar ver 
// ======================================================== 

int idx ( const wchar* _str, const wchar* _needle, int _start_idx )
{
    wchar* haystack;
    wchar* save_haystack;

    save_haystack = haystack = const_cast<wchar*>(_str);
    int ret = -1;

    if ( _needle == NULL || haystack == NULL )
        return -1;		/* type error; errmsg already given */

    if ( _start_idx >= int(str::len(haystack)) )
        return -1;

    if ( _start_idx >= 0 )
        haystack += _start_idx;

    const wchar* pos = str::str(haystack, _needle);
    if ( pos != NULL )
        ret = int(pos - save_haystack);

    return ret;
}

// ------------------------------------------------------------------ 
// Desc: str::ridx 
// ------------------------------------------------------------------ 

// ======================================================== 
// char ver 
// ======================================================== 

int ridx ( const char* _str, const char* _needle, int _start_idx )
{
    char* haystack;
    char* rest;
    char* lastmatch = NULL;
    int haystack_len, end_idx;

    haystack = const_cast<char*>(_str);
    int ret = -1;

    if ( _needle == NULL || haystack == NULL )
        return -1;		/* type error; errmsg already given */

    haystack_len = int(str::len(haystack));

    /* Third argument: upper limit for index */
    if ( _start_idx == -1 || _start_idx > haystack_len )
    {
        end_idx = haystack_len;
    }
    else
    {
        end_idx = _start_idx;
    }

	/* can never find a match */
    if ( end_idx < 0 )
        return -1;

    if ( *_needle == NULL )
    {
        /* empty string matches past the end. */
        lastmatch = haystack + end_idx;
    }
    else
    {
        for ( rest = haystack; *rest != '\0'; ++rest )
        {
            rest = strstr(rest, _needle);
            if (rest == NULL || rest > haystack + end_idx)
                break;
            lastmatch = rest;
        }
    }

    if (lastmatch == NULL)
        ret = -1;
    else
        ret = (int)(lastmatch - haystack);

    return ret;
}

// ======================================================== 
// wchar ver 
// ======================================================== 

int ridx ( const wchar* _str, const wchar* _needle, int _start_idx )
{
    wchar* haystack;
    const wchar* rest;
    const wchar* lastmatch = NULL;
    int haystack_len, end_idx;

    haystack = const_cast<wchar*>(_str);
    int ret = -1;

    if ( _needle == NULL || haystack == NULL )
        return -1;		/* type error; errmsg already given */

    haystack_len = int(str::len(haystack));

    /* Third argument: upper limit for index */
    if ( _start_idx == -1 || _start_idx > haystack_len )
    {
        end_idx = haystack_len;
    }
    else
    {
        end_idx = _start_idx;
    }

	/* can never find a match */
    if ( end_idx < 0 )
        return -1;

    if ( *_needle == NULL )
    {
        /* empty string matches past the end. */
        lastmatch = haystack + end_idx;
    }
    else
    {
        for ( rest = haystack; *rest != '\0'; ++rest )
        {
            rest = str::str(rest, _needle);
            if (rest == NULL || rest > haystack + end_idx)
                break;
            lastmatch = rest;
        }
    }

    if (lastmatch == NULL)
        ret = -1;
    else
        ret = (int)(lastmatch - haystack);

    return ret;
}

// ######################### 
} // end namespace str 
// ######################### 

// #########################
} // end namespace ex 
// #########################


