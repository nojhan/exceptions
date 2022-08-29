#ifndef __EXCEPTIONS_H__
#define __EXCEPTIONS_H__

#include <string>
#include <sstream>
#include <exception>

//! This macro should be used when calling an exception
/*!   for example :
     throw( Exception( "Shit happens", E_INFOS );
*/
#define E_INFOS __FUNCTION__,__FILE__,__LINE__


//! This macro should be used to declare an exception
/*! The second argument is the name of the exception class
    The first argument is the name of the base class
    for example :
      EXCEPTION(Exception,Buddhist_Observation);
      creates an new exception class "Buddhist_Observation", derived from the base "Exception"
*/
#define EXCEPTION(Super,Current) class Current : public Super {public: Current ( const std::string & desc, const std::string & func="?", const std::string & f="?", const int l=-1, const std::string & n=#Current ) : Super (desc,func,f,l,n) {} }


/** A shortcut to throw an exception without having to type ",E_INFOS"
 * and that could take streamed-formatted input instead of plain strings.
 *
 * Example:
 *      RAISE( Buddhist_Observation, "There is " << 0 << " shit that happens" );
 */
#define RAISE( Err, msg ) {std::ostringstream oss; oss << msg; throw( Err(oss.str(), E_INFOS) );}


//! This is the base class for all exceptions in oMetah
class Exception : public std::exception
{
protected:
    //! Name of the current exception class
    std::string name;

    //! Description of the exception
    std::string description;

    //! Function where the exception has been raised
    std::string function;

    //! File where the exception has been raised
    std::string file;

    //! Line where the exception has been raised
    int line;

    //! Assembled message
    std::string message;

public:
    //! Constructor of the exception
    /*!
        This constructor is not supposed to be used with hand-made location arguments
        but with metadata provided by the compiler.

        Use the E_INFOS macro to raise the exception, for example :
            throw( Exception( "Shit evolves", E_INFOS );
    */
    Exception( const std::string & desc, const std::string & func, const std::string & f, const int l, const std::string & n = "Exception" )
        : description(desc), function(func), file(f), line(l), name(n)
        {
            std::ostringstream msg;
            msg << "<" << name << "> " << description << "\t\t" << function << " @ " << file << ":" << line << "";
            message = msg.str();
        }

    //! The destructor is not allowed to throw exceptions
    virtual ~Exception() throw () {}

    //! The method to use for printing the complete description of the exception
    const char* what() const noexcept
    {
        return message.c_str();
    }
};

#endif // __EXCEPTIONS_H__

