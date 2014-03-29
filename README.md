
Better exception declaration and use
====================================

A C++ exception class and macros with easy nested declaration and localisation
data.

The point of this system is to permits to easily add to exceptions instances
some informations about _where_ (in the source code) the exceptions are thrown.

It also ease declaration of new exception classes and their use.


Example
-------

```cpp

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
    } catch( Existential_Observation & e ) {
        std::cerr << e.what() << std::endl;
    }
}
```

Will output:
```
[:~/code/exceptions] master* ± g++ example.cpp && ./a.out
Shit happens with 3.14 noodly appendages (<Pastafarism_Observation> in main at example.cpp:18)
```


Explanations
============

Declaration
-----------

It permits a one-line declaration of new exceptions, derived from
existing ones.

Example:
```cpp
EXCEPTION( Exception, Existential_Observation );
    EXCEPTION( Existential_Observation, Pastafarism_Observation );
```

If you catch an `Existential_Observation`, you may thus catch an `Pastafarism_Observation` also.

Note that the base `Exception` class derivate from `std::exception` and uses the standard `what` interface (more or less
like `std::runtime_error` and `std::logical_error`).


Location
--------

To add location information, it uses compilers macros that indicates the current function, file and line
(`__FUNCTION__`, `__FILE__` and `__LINE__` for g++) and merge those information with the given description returned by
the `what` standard method.

You did not need to remember the name of those macros, they are available in the `E_INFOS` macro, that fit with the
constructor of the `Exception` class.

Example:
```cpp
throw Existential_Observation( "Shit happens", E_INFOS );
```


Use
---

It also provides a macro to easily throw an exception that permits to use
dynamic streamed messages inline and without having to specify `E_INFOS`.

Example:
```cpp
RAISE( Pastafarism_Observation, "Shit happens with " << 42 << " noodly appendages" );
```

