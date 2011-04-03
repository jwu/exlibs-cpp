// ======================================================================================
// File         : enums.h
// Author       : Wu Jie 
// Last Change  : 08/14/2010 | 14:14:55 PM | Saturday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef ENUMS_H_1250525275
#define ENUMS_H_1250525275
// #################################################################################

// #########################
namespace ex { 
// #########################

///////////////////////////////////////////////////////////////////////////////
// enums 
///////////////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------------
// Desc: EResult 
// ------------------------------------------------------------------

namespace EResult 
{
    enum Enum {
        // general
        unknown     = 0x00000000,
        ok          = 0x00000001,
        failed,
        invalid_input,
        invalid_output,

        // container operations
        not_found,
        already_existed,
        already_freed,
        out_of_range,

        // math
        infinity,
        nan,

        // file and directory
        end_of_file,
        read_failed,
        write_failed,
        serialize_failed,
        parse_failed,
        not_exists,

        // createion,init,destroy.
        create_failed,
        init_failed,
        destroy_failed,
        verify_failed,
        no_change,

        // thread, buffer
        lock_failed,

        // graphics
        render_paused,
        device_lost,
        device_resetfailed,

        // code process
        compile_failed,
    }; // end enum  
} // end namespace

typedef EResult::Enum result_t;

// ------------------------------------------------------------------
// Desc: EMemop  
// ------------------------------------------------------------------

namespace EMemop
{
    enum Enum {
        // Unknown
        unknown       = -1,

        // alloc Type
        cpp_new             = 1<<0,
        cpp_new_array       = 1<<1,
        c_malloc            = 1<<2,
        c_calloc            = 1<<3,
        c_realloc           = 1<<4,

        // Dealloc Type
        cpp_delete          = 1<<5,
        cpp_delete_array    = 1<<6,
        c_free              = 1<<7,

        // flags for memop check
        check_new           = cpp_new|cpp_delete,
        check_new_array     = cpp_new_array|cpp_delete_array,
        check_malloc        = c_malloc|c_free,
        check_calloc        = c_calloc|c_free,
        check_realloc       = c_realloc|c_free,
        check_realloc_ptr   = c_realloc|c_malloc|c_calloc,
    }; // end enum
} // end namespace

// ------------------------------------------------------------------ 
// Desc: ERotate 
// ------------------------------------------------------------------ 

namespace ERot 
{
    enum Enum {
        cw,
        ccw
    }; // end enum
} // end namespace

// ------------------------------------------------------------------
// Desc: ESingletonLevel for SingletonHolder in exlibs project 
//  Any project depends on the last project, should inherit the Level
//  NUM from the last one.
//  for example: if a Engine Project depends on exlibs, then
//      ESingletonLevel::Engine_lowest = ESingletonLevel::exlibs_lowest
// ------------------------------------------------------------------

namespace ESingletonLevel
{
    enum exlibs {
        exlibs_lv_0 = 0, 
        exlibs_lv_1,
        exlibs_lv_2,
        exlibs_lv_3,
        exlibs_lv_4,
        exlibs_lv_5,
        exlibs_lv_6,

        // get the total num of the level
        exlibs_count         
    }; // end enum
} // end namespace

// ------------------------------------------------------------------ 
// Desc: EKeys 
// ------------------------------------------------------------------ 

namespace EKeys
{
    enum Enum {
        // The keyboard syms have been cleverly chosen to map to ASCII {
        Unknown         = 0,
        first		    = 0,
        Backspace	    = 8,
        Tab		        = 9,
        clear		    = 12,
        Return		    = 13,
        Pause		    = 19,
        Escape		    = 27,
        Space		    = 32,
        Exclaim		    = 33,
        Quotedbl	    = 34,
        Hash		    = 35,
        Dollar		    = 36,
        Ampersand	    = 38,
        Quote		    = 39,
        LeftParen       = 40,
        RightParen	    = 41,
        Asterisk	    = 42,
        Plus		    = 43,
        Comma		    = 44,
        Minus		    = 45,
        Period		    = 46,
        Slash		    = 47,
        D0			    = 48,
        D1			    = 49,
        D2			    = 50,
        D3			    = 51,
        D4			    = 52,
        D5			    = 53,
        D6			    = 54,
        D7			    = 55,
        D8			    = 56,
        D9			    = 57,
        Colon		    = 58,
        Semicolon	    = 59,
        Less		    = 60,
        Equals		    = 61,
        Greater		    = 62,
        Question	    = 63,
        At			    = 64,
        A			    = 65,
        B			    = 66,
        C			    = 67,
        D			    = 68,
        E			    = 69,
        F			    = 70,
        G			    = 71,
        H			    = 72,
        I			    = 73,
        J			    = 74,
        K			    = 75,
        L			    = 76,
        M			    = 77,
        N			    = 78,
        O			    = 79,
        P			    = 80,
        Q			    = 81,
        R			    = 82,
        S			    = 83,
        T			    = 84,
        U			    = 85,
        V			    = 86,
        W			    = 87,
        X			    = 88,
        Y			    = 89,
        Z			    = 90,
        LeftBracket	    = 91,
        Backslash	    = 92,
        RightBracket    = 93,
        Caret		    = 94,
        Underscore	    = 95,
        BackQuote	    = 96,
        a			    = 97,
        b			    = 98,
        c			    = 99,
        d			    = 100,
        e			    = 101,
        f			    = 102,
        g			    = 103,
        h			    = 104,
        i			    = 105,
        j			    = 106,
        k			    = 107,
        l			    = 108,
        m			    = 109,
        n			    = 110,
        o			    = 111,
        p			    = 112,
        q			    = 113,
        r			    = 114,
        s			    = 115,
        t			    = 116,
        u			    = 117,
        v			    = 118,
        w			    = 119,
        x			    = 120,
        y			    = 121,
        z			    = 122,
        Delete		    = 127,
        // } ASCII end 

        // International keyboard { 
        World_0		    = 160,		/* 0xA0 */
        World_1		    = 161,
        World_2		    = 162,
        World_3		    = 163,
        World_4		    = 164,
        World_5		    = 165,
        World_6		    = 166,
        World_7		    = 167,
        World_8		    = 168,
        World_9		    = 169,
        World_10		= 170,
        World_11		= 171,
        World_12		= 172,
        World_13		= 173,
        World_14		= 174,
        World_15		= 175,
        World_16		= 176,
        World_17		= 177,
        World_18		= 178,
        World_19		= 179,
        World_20		= 180,
        World_21		= 181,
        World_22		= 182,
        World_23		= 183,
        World_24		= 184,
        World_25		= 185,
        World_26		= 186,
        World_27		= 187,
        World_28		= 188,
        World_29		= 189,
        World_30		= 190,
        World_31		= 191,
        World_32		= 192,
        World_33		= 193,
        World_34		= 194,
        World_35		= 195,
        World_36		= 196,
        World_37		= 197,
        World_38		= 198,
        World_39		= 199,
        World_40		= 200,
        World_41		= 201,
        World_42		= 202,
        World_43		= 203,
        World_44		= 204,
        World_45		= 205,
        World_46		= 206,
        World_47		= 207,
        World_48		= 208,
        World_49		= 209,
        World_50		= 210,
        World_51		= 211,
        World_52		= 212,
        World_53		= 213,
        World_54		= 214,
        World_55		= 215,
        World_56		= 216,
        World_57		= 217,
        World_58		= 218,
        World_59		= 219,
        World_60		= 220,
        World_61		= 221,
        World_62		= 222,
        World_63		= 223,
        World_64		= 224,
        World_65		= 225,
        World_66		= 226,
        World_67		= 227,
        World_68		= 228,
        World_69		= 229,
        World_70		= 230,
        World_71		= 231,
        World_72		= 232,
        World_73		= 233,
        World_74		= 234,
        World_75		= 235,
        World_76		= 236,
        World_77		= 237,
        World_78		= 238,
        World_79		= 239,
        World_80		= 240,
        World_81		= 241,
        World_82		= 242,
        World_83		= 243,
        World_84		= 244,
        World_85		= 245,
        World_86		= 246,
        World_87		= 247,
        World_88		= 248,
        World_89		= 249,
        World_90		= 250,
        World_91		= 251,
        World_92		= 252,
        World_93		= 253,
        World_94		= 254,
        World_95		= 255,		/* 0xFF */
        // } International keyboard end 

        // Numeric keypad { 
        NumPad_0		= 256,
        NumPad_1		= 257,
        NumPad_2		= 258,
        NumPad_3		= 259,
        NumPad_4		= 260,
        NumPad_5		= 261,
        NumPad_6		= 262,
        NumPad_7		= 263,
        NumPad_8		= 264,
        NumPad_9		= 265,
        NumPad_Period	= 266,
        NumPad_Divide	= 267,
        NumPad_Multiply	= 268,
        NumPad_Minus	= 269,
        NumPad_Plus		= 270,
        NumPad_Enter	= 271,
        NumPad_Equals	= 272,
        // } Numeric keypad end 

        // Arrows + Home/end pad { 
        Up			    = 273,
        Down		    = 274,
        Right		    = 275,
        Left		    = 276,
        insert		    = 277,
        Home		    = 278,
        end		        = 279,
        PageUp		    = 280,
        PageDown		= 281,
        // } Arrows + Home/end pad end 

        // function keys { 
        F1			    = 282,
        F2			    = 283,
        F3			    = 284,
        F4			    = 285,
        F5			    = 286,
        F6			    = 287,
        F7			    = 288,
        F8			    = 289,
        F9			    = 290,
        F10		        = 291,
        F11		        = 292,
        F12		        = 293,
        F13		        = 294,
        F14		        = 295,
        F15		        = 296,
        // } function keys end 

        // key state modifier { 
        NumLock		    = 300,
        CapsLock		= 301,
        ScrollLock		= 302,
        RShift		    = 303,
        LShift		    = 304,
        RCtrl		    = 305,
        LCtrl		    = 306,
        RAlt		    = 307,
        LAlt		    = 308,
        RMeta		    = 309,
        LMeta		    = 310,
        LSuper		    = 311,		// Left "Windows" key
        RSuper		    = 312,		// Right "Windows" key
        Mode		    = 313,		// "Alt Gr" key
        Compose		    = 314,		// Multi-key compose key
        // } key state modifier end 

        // Miscellaneous function keys { 
        Help		    = 315,
        Print		    = 316,
        Sysreq		    = 317,
        Break		    = 318,
        Menu		    = 319,
        Power		    = 320,		// Power Macintosh power key
        Euro		    = 321,		// Some european keyboards
        Undo		    = 322,		// Atari keyboard has Undo
        // } Miscellaneous function keys end 

        // Add any other keys here
        count

    }; // end enum Enum

} // namespace EKeys

// ------------------------------------------------------------------ 
// Desc: 
// ------------------------------------------------------------------ 

namespace EModifier
{
    enum Enum {
        None        = 0,
        Shift       = 1 << 0,
        Control     = 1 << 1,
        Alt         = 1 << 2,
        Meta        = 1 << 3,
    }; // end enum Enum
} // namespace EModifier

// ------------------------------------------------------------------ 
// Desc: EMouseButton 
// ------------------------------------------------------------------ 

namespace EMouseButton
{
    enum Enum {
        None        = 0,
        Left        = 1 << 0,
        Middle      = 1 << 1,
        Right       = 1 << 2,
        X1          = 1 << 3,
        X2          = 1 << 4,
        Mask        = 0xff
    }; // end Enum
}

// #########################
} // end namespace ex 
// #########################

// #################################################################################
#endif // END ENUMS_H_1250525275
// #################################################################################

