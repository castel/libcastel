# Castel libraries

Please see the [official homepage](http://castel.github.com) for more informations.

Bug reports should be reported on the bug tracker of the [castel compiler](https://github.com/castel/castel) repository.

## Compilation

You will need LLVM 3.2, Ragel, Lemon, Clang and CMake.

*Note: When compiling with Clang, you will probably need the `libunwind` package if you get errors about an `_Unwind_Exception` structure*

    $> git clone git@github.com:castel/libcastel
    $> mkdir libcastel/build
    $> cd libcastel/build
    $> cmake ..
    $> make

The libraries will be generated in the `lib/` directory, and their headers will be in the `includes` directory.

## Libraries

### CastelParse

Contains the classes allowing to convert a castel source code into an AST. Includes a lexer, a parser and AST headers.

### CastelCompile

Contains the helper classes used to create LLVM data structure from Castel AST.

### CastelRuntime

Contains the runtime symbols used by castel applications.

## License

```
* -------------------------------------------------------------------------------
* "THE BEER/PIZZA-WARE LICENSE" (Revision 42):
* <nison.mael@gmail.com> wrote these files. As long as you retain this notice you
* can do whatever you want with this stuff. If we meet some day, and you think
* this stuff is worth it, you can buy me a beer or a pizza in return Maël Nison
* -------------------------------------------------------------------------------
```
