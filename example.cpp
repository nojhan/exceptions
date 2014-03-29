
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>

#include "exceptions.h" 

// Use this macro to build up your hierarchy of exceptions
EXCEPTION( Exception, Existential_Observation );
    EXCEPTION( Existential_Observation, Buddhist_Observation );
        EXCEPTION( Buddhist_Observation, Zen_Observation );
    EXCEPTION( Existential_Observation, Pastafarism_Observation );


// A somewhat similar code without this tool would be:
// Inherit from runtime_error, because it has a virtual `what` interface.
class _Existential_Observation : public std::runtime_error
{ public:
    // Pass through constructors
    _Existential_Observation( const std::string & what_arg ) : std::runtime_error(what_arg) {}
};

class _Buddhist_Observation : public _Existential_Observation
{ public:
    _Buddhist_Observation( const std::string & what_arg ) : _Existential_Observation(what_arg) {}
};


int main()
{
    try {
        double pi = 3.1415926535;
        // Use this macro to easily throw an exception with a dynamic message
        RAISE( Pastafarism_Observation, std::setprecision(3) << "Shit happens with " << pi << " noodly appendages" );

        // Or, if you prefer, use the standard `throw` function, but you'll have to indicate E_INFOS by yourself
        throw( Zen_Observation( "What is the sound of shit happening?", E_INFOS) );

    } catch( Existential_Observation & e ) {
        std::cerr << e.what() << std::endl;
    }


    // Using the standard way, you will have to do
    try {
        std::ostringstream msg;
        double vacuity = 0;
        // Beware of the hard-coded class name...
        msg << "There is " << vacuity << " shit happening (<_Buddhist_Observation in " << __FUNCTION__ << " at " << __FILE__ << ":" << __LINE__ << ")";
        // And don't forget the string conversion.
        throw( _Buddhist_Observation( msg.str() ) );

    } catch( _Existential_Observation & e ) {
        std::cerr << e.what() << std::endl;
    }
}

