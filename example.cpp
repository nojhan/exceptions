
#include <iostream>
#include <iomanip>

#include "exceptions.h" 

// Use this macro to build up your hierarchy of exceptions
EXCEPTION( Exception, Existential_Observation );
    EXCEPTION( Existential_Observation, Buddhist_Observation );
        EXCEPTION( Buddhist_Observation, Zen_Observation );
    EXCEPTION( Existential_Observation, Pastafarism_Observation );

int main()
{
    try {
        double pi = 3.1415926535;
        // Use this macro to easily throw an exception with a dynamic message
        RAISE( Pastafarism_Observation, std::setprecision(3) << "Shit happens with " << pi << " noodly appendages" );

        // Or, if you prefer, use the standard way, but you'll have to indicate E_INFOS yourself
        throw( Zen_Observation( "What is the sound of shit happening?", E_INFOS) );

    } catch( Existential_Observation & e ) {
        std::cerr << e.what() << std::endl;
    }
}

