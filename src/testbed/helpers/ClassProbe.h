// ======================================================================================
// File         : ClassProbe.h
// Author       : Wu Jie 
// Last Change  : 08/15/2010 | 18:00:07 PM | Sunday,August
// Description  : 
// ======================================================================================

// #################################################################################
#ifndef CLASSPROBE_H_1250526489
#define CLASSPROBE_H_1250526489
// #################################################################################

///////////////////////////////////////////////////////////////////////////////
// class ClassProbe
// 
// Purpose: 
// 
///////////////////////////////////////////////////////////////////////////////

class ClassProbe
{
public:
    // internal typedef
    typedef ClassProbe self_t;
    static const ex::uint MAX_LEN = 128;

    ///////////////////////////////////////////////////////////////////////////////
    // constructor & destructor 
    ///////////////////////////////////////////////////////////////////////////////

public:
    // con/de-structor
    ClassProbe ( const char* _name = "DefaultName" )
    {
        strncpy( Name, _name, strlen(_name)+1 );
        printf("ClassProbe %#.8lX:%s Construct\n", (unsigned long int)(size_t(this)), Name );
    }
    virtual ~ClassProbe ()
    {
        printf("ClassProbe %#.8lX:%s Destroyed\n", (unsigned long int)(size_t(this)), Name );
    }

public:
    // copy constructor
    ClassProbe ( const self_t& _copy )
    {
        strncpy( Name, _copy.Name, MAX_LEN );
        printf("ClassProbe %#.8lX:%s CopyConstruct\n", (unsigned long int)(size_t(this)), Name );
    }
    self_t& operator = ( const self_t& _copy )
    {
        strncpy( Name, _copy.Name, MAX_LEN );
        printf("ClassProbe %#.8lX:%s AssignMent\n", (unsigned long int)(size_t(this)), Name );
        return *this;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public generic functions 
    ///////////////////////////////////////////////////////////////////////////////

public:

    template < ex::uint FLAGS >
    const char* to_str() const
    {
        return Name;
    }

    ///////////////////////////////////////////////////////////////////////////////
    // public member data 
    ///////////////////////////////////////////////////////////////////////////////

public:
    char Name[MAX_LEN];

}; // end class ClassProbe

// #################################################################################
#endif // END CLASSPROBE_H_1250526489
// #################################################################################
