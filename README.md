# Castel libraries

Please see the [official homepage](http://castel.github.com) for more informations.

Bug reports should be reported on the bug tracker of the [castel compiler](https://github.com/castel/castel) repository.

## Compilation

You will need LLVM 3.7, Ragel, Lemon, Clang and CMake.

*Note: When compiling with Clang, you will probably need the `libunwind` package if you get errors about an `_Unwind_Exception` structure*

    $> git clone git@github.com:castel/libcastel
    $> mkdir libcastel/build
    $> cd libcastel/build
    $> cmake ..
    $> make

The libraries will be generated in the `lib/` directory, and their headers will be in the `includes` directory.

## Libraries

### CastelParse

Contains the utilities allowing to convert a castel source code into an AST. Includes a lexer, a parser, the AST headers, and various utilities such as visitors.

### CastelCompile

Contains the compiler engine itself, that will take a Castel AST and produce an actual LLVM module. Also provides some utilities to easily run these modules.

### CastelRuntime

Contains the Castel runtime, required to run Castel applications.

## License

> **Copyright © 2016 Castel Project**
>
> Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
>
> The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
>
> THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
