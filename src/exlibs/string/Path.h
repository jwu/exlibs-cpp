// ======================================================================================
// File         : Path.h
// Author       : Wu Jie 
// Last Change  : 08/18/2009 | 00:25:57 AM | Tuesday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef PATH_H_1250526359
#define PATH_H_1250526359
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// includes 
///////////////////////////////////////////////////////////////////////////////

// #########################
namespace ex { 
// #########################

// char
template < typename T >
struct Character {
    INLINE static const T* empty_str () { return ""; }

    INLINE static T slash () { return '/'; }
    INLINE static T back_slash () { return '\\'; }
    INLINE static T str_end () { return '\0'; }
    INLINE static T colon () { return ':'; }
}; // end class Character

// wchar
template <>
struct Character<wchar> {
    INLINE static const wchar* empty_str () { return W(""); }

    INLINE static wchar slash () { return L'/'; }
    INLINE static wchar back_slash () { return L'\\'; }
    INLINE static wchar str_end () { return L'\0'; }
    INLINE static wchar colon () { return L':'; }
}; // end class Character

///////////////////////////////////////////////////////////////////////////////
// class Path 
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

template < typename T, template <class> class TAllocator_T = Managed<EX_ALLOCATOR>::TAllocator >
class Path : protected String<T,TAllocator_T>  
{
    ///////////////////////////////////////////////////////////////////////////////
    // typedefs
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    typedef String< T, TAllocator_T > base_t;
    typedef Path< T, TAllocator_T > self_t;
    typedef Pair< self_t, self_t > pair_t;

    //
	typedef typename base_t::size_type          sz_t;          
    typedef typename base_t::value_type         value_t;       
	typedef typename base_t::pointer            ptr_t;         
	typedef typename base_t::const_pointer      const_ptr_t;   
	typedef typename base_t::reference          ref_t;         
	typedef typename base_t::const_reference    const_ref_t;   
	typedef typename base_t::allocator_type     allocator_t;   

    //
    typedef typename base_t::iterator           iterator;      
    typedef typename base_t::r_iterator          r_iterator;     
    typedef typename base_t::c_iterator      c_iterator; 
    typedef typename base_t::c_r_iterator     c_r_iterator;

    //
    typedef Array<Path<T,Managed<EX_ALLOCATOR>::TAllocator>, Managed<EX_ALLOCATOR>::TAllocator > path_results_t;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor
    ///////////////////////////////////////////////////////////////////////////////

public:
    //
    explicit Path()
        : base_t()
    {
    }

    //
    Path( const self_t& _path )
        : base_t(_path)
    {
    }

    //
    template < typename U, template <class> class TAllocator_U >
    Path( const Path<U,TAllocator_U>& _path )
        : base_t( _path.c_str() )
    {
    }

    //
    Path( const base_t& _string )
        : base_t( _string )
    {
        internalFormat ();
    }

    //
    template < typename U, template <class> class TAllocator_U >
    Path( const String<U,TAllocator_U>& _string )
        : base_t( _string.c_str() )
    {
        internalFormat ();
    }

    // 
    Path( const T* _c_str )
        : base_t( _c_str )
    {
        internalFormat ();
    }

    //
    Path( const T* _c_str, sz_t _count )
        : base_t( _c_str, _count )
    {
        internalFormat ();
    }

    // 
    ~Path()
    {
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public static member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    // NOTE: _name_to_convert and _result can be same address, cause the Character<T>::slash() to Character<T>::back_slash() are same size in memory.
    static void formatPath( const T* _name_to_convert, T (&_result)[ex::MaxPath], bool _useBackSlash = false )
    {
        // make the path with forward-slashes
        uint path_count = 0;
        if ( _useBackSlash )
        {
            for ( ; *_name_to_convert; ++_name_to_convert, ++path_count )
            {
                if (*_name_to_convert == Character<T>::slash() )
                {
                    _result[path_count] = Character<T>::back_slash();
                }
                else
                    _result[path_count] = *_name_to_convert;
            }
        }
        else
        {
            for ( ; *_name_to_convert; ++_name_to_convert, ++path_count )
            {
                if (*_name_to_convert == Character<T>::back_slash())
                {
                    _result[path_count] = Character<T>::slash();
                }
                else
                    _result[path_count] = *_name_to_convert;
            }
        }
        ex_assert( path_count <= ex::MaxPath, "out of max path: %d > %d", path_count, ex::MaxPath );
        _result[path_count] = Character<T>::str_end();
    }

    // NOTE: _filename and _result can be same address, it will do copy the _filename to _result first.
    static void simplify( const T* _filename, T (&_result)[ex::MaxPath] )
    {
        ex::str::ncpy( _result, ex::MaxPath, _filename, ex::MaxPath );
        ex::str::simplify( _result );
    }

    // Internal truncate
    // NOTE: this operations will simplify the path first. which make the input passed by value.
    static self_t truncate ( self_t _path1, self_t _path2 ) 
    {
        _path1.simplify();
        _path2.simplify();

        bool pre_slash = false;
        if ( _path1[0] == Character<T>::slash() )
            pre_slash = true;
        _path1.base_t::operator -= (_path2); 

        // case 1: if we don't have pre-slash, after truncate it appear, it is
        // case 2: if we have pre-slash, after truncate it have two Character<T>::slash(), same as above.
        // reason: the path2 is not end with Character<T>::slash(), so we remove the head slash
        if ( pre_slash == false && _path1[0] == Character<T>::slash() ||
             pre_slash == true && _path1[1] == Character<T>::slash() )
            return _path1.substr(1);

        return _path1; 
    }

    // Internal join
    static self_t join ( const self_t& _path1, const self_t& _path2 ) 
    {
        Path result (_path1);
#if ( EX_PLATFORM == EX_WIN32 )
        bool path2_wins = false;
        if ( _path1.empty() )
        {
            path2_wins = true;
        }
        else if ( _path2.empty() ) // joint a empty path means nothing.
        {
            return _path1;
        }
        else if ( _path2.isAbsPath () ) 
        {
            // This probably wipes out path so far.  However, it's more
            // complicated if path begins with a drive letter:
            //     1. join('c:', '/a') == 'c:/a'
            //     2. join('c:/', '/a') == 'c:/a'
            //     3. join('c:/a', 'b/c') == 'c:/a/b/c'
            // But
            //     4. join('c:/a', '/b') == '/b'
            //     5. join('c:', 'd:/') = 'd:/'
            //     6. join('c:/', 'd:/') = 'd:/'

            // Path doesn't start with a drive letter, or cases 5 and 6.
            if ( _path1[1] != Character<T>::colon() || _path2[1] == Character<T>::colon() )
            {
                path2_wins = true;
            }
            // Else _path1 has a drive letter, and _path2 doesn't but is absolute.
            // case 4
            else if ( _path1.size() > 3 || (_path1.size() == 3 && _path1[2] != Character<T>::slash()) )
            {
                path2_wins = true;
            }
        }

        //
        if ( path2_wins )
        {
            result = _path2;
        }
        else
        {
            ex_assert ( _path1.size() > 0, "_path1 is empty" );
            if ( _path1[_path1.size()-1] == Character<T>::slash() )
            {
                if ( !_path2.empty() && _path2[0] == Character<T>::slash() )
                {
                    result.append ( _path2.subpath(1).c_str() );
                }
                else
                {
                    result.append ( _path2.c_str() );
                }
            }
            else if ( _path1[_path1.size()-1] == Character<T>::colon() )
            {
                result.append ( _path2.c_str() );
            }
            else if ( !_path2.empty() )
            {
                if ( _path2[0] == Character<T>::slash() )
                    result.append ( _path2.c_str() );
                else
                {
                    result.append ( Character<T>::slash() );
                    result.append ( _path2.c_str() );
                }
            }
            else 
            {
                // path is not empty and does not end with a backslash,
                // but b is empty; since, e.g., split('a/') produces
                // ('a', ''), it's best if join() adds a backslash in
                // this case.
                result.append ( Character<T>::slash() );
            }
        }
#else
        if ( _path2[0] == Character<T>::slash() )
        {
            result = _path2;
        }
        else if ( _path1.empty() || _path1[_path1.size()-1] == Character<T>::slash() )
        {
            result.append ( _path2.c_str() );
        }
        else
        {
            result.append ( Character<T>::slash() );
            result.append ( _path2.c_str() );
        }
#endif
        return result;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public general member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    // similar common functions
    INLINE allocator_t get_allocator()                          { return base_t::get_allocator(); }
    INLINE iterator begin()                                     { return base_t::begin();         }
    INLINE c_iterator begin() const                             { return base_t::begin();         }
    INLINE iterator end()                                       { return base_t::end();           }
    INLINE c_iterator end() const                               { return base_t::end();           }
    INLINE r_iterator rbegin()                                  { return base_t::rbegin();        }
    INLINE c_r_iterator rbegin() const                          { return base_t::rbegin();        }
    INLINE r_iterator rend()                                    { return base_t::rend();          }
    INLINE c_r_iterator rend() const                            { return base_t::rend();          }
    INLINE bool empty() const                                   { return base_t::empty();         }
    INLINE sz_t size() const                                    { return base_t::size();          }
    INLINE sz_t max_size() const                                { return base_t::max_size();      }
    INLINE void clear()                                         { base_t::clear();                }
    INLINE void swap( self_t& _container )                      { base_t::swap( _container );     }

    ///////////////////////////////////////////////////////////////////////////////
    // public member functions
    ///////////////////////////////////////////////////////////////////////////////

public:

    //
    INLINE self_t& set ( const self_t& _path ) { base_t::assign( _path ); return *this; }
    INLINE self_t& formatSet ( const T* _str ) { base_t::assign( _str ); internalFormat(); return *this; }

    //
    INLINE self_t& operator = ( const self_t& _path ) { base_t::operator = (_path); return *this; } 

    //
    INLINE void reserve( sz_t _count = 0 ) { base_t::reserve(_count); } 

    //
    INLINE sz_t capacity() const { return base_t::capacity(); }

    //
    INLINE ref_t operator [] ( sz_t _idx ) { return base_t::operator [] (_idx); }
    INLINE const_ref_t operator [] ( sz_t _idx ) const { return base_t::operator [] (_idx); }

    //
    INLINE ref_t At ( sz_t _idx ) { return base_t::At(_idx); }
    INLINE const_ref_t At ( sz_t _idx ) const { return base_t::At(_idx); }

    //
    INLINE self_t& operator += ( const self_t& _path ) { *this = self_t::join( *this, _path ); return *this; } 
    INLINE self_t& operator -= ( const self_t& _path ) { *this = self_t::truncate( *this, _path ); return *this; } 

    //
    INLINE self_t& insert( sz_t _pos, const self_t& _path ) { base_t::insert( _pos, _path ); return *this; }

    // TODO: insert path by separate

    //
    INLINE self_t& erase( sz_t _pos = 0, sz_t _count = base_t::npos ) { base_t::erase( _pos, _count ); return *this; }
    INLINE iterator erase( iterator _pos ) { return base_t::erase(_pos); }
    INLINE iterator erase( iterator _first, iterator _last ) { return base_t::erase(_first,_last); }

    //
    INLINE self_t& replace( sz_t _pos, sz_t _count, const self_t& _path ) { base_t::replace( _pos, _count, _path ); return *this; }
    INLINE self_t& replace( iterator _first, iterator _last, const self_t& _path ) { base_t::replace( _first, _last, _path ); return *this; }

    //
    INLINE const T* c_str() const { return base_t::c_str(); }
    // just use c_str(), they are the same
    // INLINE const T* Data() const { return base_t::data(); }
    INLINE T* rawData() { return base_t::rawData(); }

    //
    INLINE sz_t find( const self_t& _path, sz_t _pos = 0 ) const { return base_t::find( _path, _pos ); }
    INLINE sz_t rfind( const self_t& _path, sz_t _pos = base_t::npos ) const { return base_t::rfind( _path, _pos ); }
    INLINE sz_t findFirstOf( const self_t& _path, sz_t _pos = 0 ) const { return base_t::findFirstOf( _path, _pos ); }
    INLINE sz_t findLastOf( const self_t& _path, sz_t _pos = base_t::npos ) const { return base_t::findLastOf( _path, _pos ); }
    INLINE sz_t findFirstNotOf( const self_t& _path, sz_t _pos = 0 ) const { return base_t::findFirstNotOf( _path, _pos ); }
    INLINE sz_t findLastNotOf( const self_t& _path, sz_t _pos = base_t::npos ) const { return base_t::findLastNotOf( _path, _pos ); }

    //
    INLINE base_t substr( sz_t _pos = 0, sz_t _count = base_t::npos ) const { return base_t::substr( _pos, _count ); }
    INLINE Path subpath( sz_t _pos = 0, sz_t _count = base_t::npos ) const { self_t result_path; result_path.set( base_t::substr( _pos, _count ) ); return result_path; }

    //
    INLINE int compare( const self_t& _path ) const { return base_t::compare(_path); }
    INLINE int compare( sz_t _pos1, sz_t _count1, const self_t& _path ) const { return base_t::compare( _pos1, _count1, _path ); }
    INLINE int compare( sz_t _pos1, sz_t _count1, const self_t& _path, sz_t _pos2, sz_t _count2 ) const { return base_t::compare( _pos1, _count1, _path, _pos2, _count2 ); }

    base_t nativePath () const
    {
#if (EX_PLATFORM == EX_WIN32)
        T win32_path[ex::MaxPath];
        self_t::formatPath( this->c_str(), win32_path, true );
        return base_t ( win32_path );
#else
        return *this;
#endif
    }

    //
    self_t& printf( const T* _fmt, ... )
    {
        int     result = -1;
        int     buffer_count = 1024;
        T*      pBuffer = NULL;

        // keep get va string until success 
        while ( result == -1 )
        {
            pBuffer = (T*)allocator_t().reallocate( pBuffer, buffer_count );
            EX_GET_VA_STRING_WITH_RESULT( pBuffer, buffer_count, _fmt, &result );
            buffer_count *= 2;
        }
        pBuffer[result] = 0;

        // 
        this->set( self_t(pBuffer,result) );

        // free the temp buffer
        allocator_t().deallocate( pBuffer, buffer_count );
        return (*this);
    }

    //
    self_t left( sz_t _count ) const { return base_t::left (); }
    self_t right( sz_t _count ) const { return base_t::right (); }

    //
    Path getSimplify () const
    {
        Path path(*this);
        ex::str::simplify( path.rawData () ); 
        path.resize ( str::len( path.c_str() ) );
        return path;
    }
    void simplify () 
    {
        ex::str::simplify( rawData () ); 
        base_t::resize ( str::len( c_str() ) );
    }

    //
    // c:/test1/test2/test.cpp = c: + /test1/test2/test.cpp
    pair_t splitDriver () const
    {
        pair_t pair;
#if ( EX_PLATFORM == EX_WIN32 )
        if ( size() > 2 && At(1) == Character<T>::colon() )
        {
            pair.first = subpath(0,2);
            pair.second = subpath(2);
        }
        else
        {
            pair.first = self_t(Character<T>::empty_str());
            pair.second = self_t(*this);
        }
#else
        pair.first = self_t(Character<T>::empty_str());
        pair.second = self_t(c_str());
#endif
        return pair;
    }

    //
    // c:/test1/test2/test.cpp = c:/test1/test2/test + cpp
    pair_t splitExt () const
    {
        pair_t pair;
        sz_t idx = rfind ( Gen_TString<T>(".") );
        sz_t idx_slash = rfind ( Gen_TString<T>("/") );
        if ( idx == sz_t(ex::IndexNone) || (idx_slash != sz_t(ex::IndexNone) && idx <= idx_slash) )
        {
            pair.first = self_t(*this);
            pair.second = self_t(Character<T>::empty_str());
        }
        else
        {
            pair.first = subpath(0,idx);
            pair.second = subpath(idx+1);
        }
        return pair;
    }

    //
    // c:/test1/test2/test.cpp = c:/test1/test2 + test.cpp
    pair_t split () const
    {
        pair_t pair;
        sz_t idx = rfind ( Gen_TString<T>("/") );
        if ( idx != sz_t(ex::IndexNone) )
        {
            pair.first = subpath(0,idx);
            pair.second = subpath(idx+1);
        }
        else
        {
            pair.first = self_t(*this);
            pair.second = self_t(Character<T>::empty_str());
        }
        return pair;
    }

    //
    bool isAbsPath () const 
    {
#if ( EX_PLATFORM == EX_WIN32 )
        pair_t result = splitDriver ();
        bool ret = ( !result.second.empty() && result.second.At(0) == Character<T>::slash() ); 
		return ret;
#else
        return At(0) == Character<T>::slash()
#endif
    }

    // return an absolute path
    Path absPath () const 
    {
        Path resultPath (*this);

        //
        if ( !isAbsPath () )
        {
            T c_path[ex::MaxPath];
            ex::getcwd( c_path, int(ex::MaxPath) );
            Path workingPath ( c_path );
            resultPath = workingPath + resultPath; 
        }

        //
        resultPath.simplify ();
        return resultPath; 
    }

    // return the head (dirname) part of a path.
    Path dirName () const
    {
        pair_t result = split ();
        return result.first;
    }

    // return the tail (basename) part of a path
    Path baseName () const
    {
        pair_t result = split ();
        return result.second;
    }

    // return the ext name a file
    Path extName () const
    {
        pair_t result = splitExt ();
        return result.second;
    }

    // return the full-path without ext name
    Path pathWithoutExt () const
    {
        pair_t result = splitExt ();
        return result.first;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < class SELF_TYPE > friend class PropertyInstance;
    void serialize ( ISerializeNode* _pNode );
    template < uint FLAGS > INLINE string_t to_str() const
    {
        return *this;
    }
    static const string_id_t& type_name () 
    {
        static const string_id_t strID ("Path");
        return strID;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // protected member functions
    ///////////////////////////////////////////////////////////////////////////////

protected:

    //
    void internalFormat ()
    {
        T result[ex::MaxPath];
        self_t::formatPath( c_str(), result );
        base_t::assign ( result );
    }

    // Internal Assignment, the format function will not call 
    INLINE self_t& set ( const base_t& _string ) { base_t::assign( _string ); return *this; }
    INLINE self_t& set ( const T* _c_str ) { base_t::assign( _c_str ); return *this; }
    INLINE self_t& set ( const T* _c_str, sz_t _count ) { base_t::assign( _c_str, _count ); return *this; }

}; // end class Path

///////////////////////////////////////////////////////////////////////////////
// operator +
// NOTE: only Path + Path = Path // it will use join function
//       Path + others = String
//       others + Path = String
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Path + Path
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE Path<T,TAllocator_T> operator + ( const Path<T,TAllocator_T>& _path1, const Path<T,TAllocator_T>& _path2 )
{
    return Path<T,TAllocator_T>::join ( _path1, _path2 ); 
}

// ------------------------------------------------------------------
// Desc: String + Path
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator + ( const String<T,TAllocator_T>& _string1, const Path<T,TAllocator_T>& _path2 )
{
    return 
        (
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string1)) +
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_path2)) 
        );
}

// ------------------------------------------------------------------
// Desc: Path + String 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator + ( const Path<T,TAllocator_T>& _path1, const String<T,TAllocator_T>& _string2 )
{
    return 
        ( 
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_path1)) +
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string2))
        ); 
}

// ------------------------------------------------------------------
// Desc: char_type* + Path<char_type>
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator + ( const T* _c_str1, const Path<T,TAllocator_T>& _path2 )
{
    return 
        (
         _c_str1 + 
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_path2)) 
        );
}

// ------------------------------------------------------------------
// Desc: Path<char_type> + char_type*
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator + ( const Path<T,TAllocator_T>& _path1, const T* _c_str2 )
{
    return 
        ( 
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_path1)) +
         _c_str2 
        ); 
}

// ------------------------------------------------------------------
// Desc: char_type + Path<char_type>
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator + ( const T _char1, const Path<T,TAllocator_T>& _path2 )
{
    return  
        (
         _char1 + 
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_path2)) 
        );
}

// ------------------------------------------------------------------
// Desc: Path<char_type> + char_type
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator + ( const Path<T,TAllocator_T>& _path1, const T _char2 )
{
    return 
        (
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_path1)) +
         _char2
        ); 
}

///////////////////////////////////////////////////////////////////////////////
// operator -
// NOTE: only Path - Path = Path
//       Path - others = String
//       others - Path = String
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Path - Path
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE Path<T,TAllocator_T> operator - ( const Path<T,TAllocator_T>& _path1, const Path<T,TAllocator_T>& _path2 )
{
    return Path<T,TAllocator_T>::truncate ( _path1, _path2 ); 
}

// ------------------------------------------------------------------
// Desc: String - Path
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator - ( const String<T,TAllocator_T>& _string1, const Path<T,TAllocator_T>& _path2 )
{
    return 
        (
         _string1 - 
         *(reinterpret_cast< const String<T,TAllocator_T>* >(&_path2))
        );
}

// ------------------------------------------------------------------
// Desc: Path - String 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator - ( const Path<T,TAllocator_T>& _path1, const String<T,TAllocator_T>& _string2 )
{
    return 
        ( 
         *(reinterpret_cast< const String<T,TAllocator_T>* >(&_path1)) +
         _string2
        ); 
}

// ------------------------------------------------------------------
// Desc: char_type* + Path<char_type>
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator - ( const T* _c_str1, const Path<T,TAllocator_T>& _path2 )
{
    return 
        (
         _c_str1 + 
         *(reinterpret_cast< const String<T,TAllocator_T>* >(&_path2))
        );
}

// ------------------------------------------------------------------
// Desc: Path<char_type> + char_type*
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE String<T,TAllocator_T> operator - ( const Path<T,TAllocator_T>& _path1, const T* _c_str2 )
{
    return 
        ( 
         *(reinterpret_cast< const String<T,TAllocator_T>* >(&_path1)) +
         _c_str2 
        ); 
}

///////////////////////////////////////////////////////////////////////////////
// operator ==
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Path == Path 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator == ( const Path<T,TAllocator_T>& _path1, const Path<T,TAllocator_T>& _path2 )
{
    return 
        (
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_path1)) ==
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_path2))
        ); 
}

// ------------------------------------------------------------------
// Desc: String == Path<char_type> 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator == ( const String<T,TAllocator_T>& _string1, const Path<T,TAllocator_T>& _path2 )
{
    return
        ( 
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string1)) ==
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_path2))
        ); 
}

// ------------------------------------------------------------------
// Desc: Path<char_type> == String 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator == ( const Path<T,TAllocator_T>& _path1, const String<T,TAllocator_T>& _string2 )
{
    return 
        (
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_path1)) ==
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_string2))
        ); 
}

// ------------------------------------------------------------------
// Desc: char_type* == Path<char_type> 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator == ( const T* _c_str1, const Path<T,TAllocator_T>& _path2 )
{
    return
        ( 
         _c_str1 == 
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_path2))
        ); 
}

// ------------------------------------------------------------------
// Desc: Path<char_type> == char_type* 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator == ( const Path<T,TAllocator_T>& _path1, const T* _c_str2 )
{
    return 
        (
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_path1)) ==
         _c_str2 
        ); 
}

///////////////////////////////////////////////////////////////////////////////
// operator !=
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Path != Path 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator != ( const Path<T,TAllocator_T>& _path1, const Path<T,TAllocator_T>& _path2 )
{
    return !(_path1 == _path2); 
}

// ------------------------------------------------------------------
// Desc: String != Path<char_type> 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator != ( const String<T,TAllocator_T>& _string1, const Path<T,TAllocator_T>& _path2 )
{
    return !(_string1 == _path2); 
}

// ------------------------------------------------------------------
// Desc: Path<char_type> != String 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator != ( const Path<T,TAllocator_T>& _path1, const String<T,TAllocator_T>& _string2 )
{
    return !(_path1 == _string2); 
}

// ------------------------------------------------------------------
// Desc: char_type* != Path<char_type> 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator != ( const T* _c_str1, const Path<T,TAllocator_T>& _path2 )
{
    return !(_c_str1 == _path2); 
}

// ------------------------------------------------------------------
// Desc: Path<char_type> != char_type* 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator != ( const Path<T,TAllocator_T>& _path1, const T* _c_str2 )
{
    return !(_path1 == _c_str2); 
}

///////////////////////////////////////////////////////////////////////////////
// operator ^=
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Path ^= Path 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator ^= ( const Path<T,TAllocator_T>& _path1, const Path<T,TAllocator_T>& _path2 )
{
    return (ex::str::icmp( _path1.c_str(), _path2.c_str() ) == 0);
}

// ------------------------------------------------------------------
// Desc: String ^= Path<char_type> 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator ^= ( const String<T,TAllocator_T>& _string1, const Path<T,TAllocator_T>& _path2 )
{
    return (ex::str::icmp( _string1.c_str(), _path2.c_str() ) == 0);
}

// ------------------------------------------------------------------
// Desc: Path<char_type> ^= String
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator ^= ( const Path<T,TAllocator_T>& _path1, const String<T,TAllocator_T>& _string2 )
{
    return (ex::str::icmp( _path1.c_str(), _string2.c_str() ) == 0);
}

// ------------------------------------------------------------------
// Desc: char_type* ^= Path<char_type> 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator ^= ( const T* _c_str1, const Path<T,TAllocator_T>& _path2 )
{
    return (ex::str::icmp( _c_str1, _path2.c_str() ) == 0);
}

// ------------------------------------------------------------------
// Desc: Path<char_type> ^= char_type* 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator ^= ( const Path<T,TAllocator_T>& _path1, const T* _c_str2 )
{
    return (ex::str::icmp( _path1.c_str(), _c_str2 ) == 0);
}

///////////////////////////////////////////////////////////////////////////////
// operator <
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: Path < Path 
// ------------------------------------------------------------------

template < typename T, template <class> class TAllocator_T >
INLINE bool operator < ( const Path<T,TAllocator_T>& _path1, const Path<T,TAllocator_T>& _path2 )
{
    return 
        (
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_path1)) <
         *(reinterpret_cast< const std::basic_string<T,std::char_traits<T>, ContainerAllocator<T,TAllocator_T> >* >(&_path2))
        ); 
}

// ######################### 
} // end namespace ex 
// ######################### 

// #################################################################################
#endif // END PATH_H_1250526359
// #################################################################################

