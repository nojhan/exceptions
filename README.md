
A C++ exception class and macros with easy nested declaration and localisation
data.

The point of this system is to permits to easily add to exceptions instances
some informations about _where_ the exceptions are thrown.

To do so, it uses compilers macros that indicates the current function, file and
line (`__FUNCTION__`, `__FILE__` and `__LINE__` for g++) and merge those
information with the given description returned by the `what` standard method.

Example:
```cpp
throw Existential_Observation( "Shit happens", E_INFOS );
```

Additionaly, it permits a one-line declaration of new exceptions, derived from
existing ones.

Example:
```cpp
EXCEPTION( Exception, Existential_Observation );
    EXCEPTION( Existential_Observation, Pastafarism_Observation );
```

Note that the base `Exception` class derivate from `std::exception`.

It also provides a macro to easily throw an exception that permits to use
dynamic streamed messages inline and without having to specify `E_INFOS`.

Example:
```cpp
RAISE( Pastafarism_Observation, "Shit happens with " << 42 << " noodly appendages" );
```

