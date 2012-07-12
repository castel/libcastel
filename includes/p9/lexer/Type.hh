#pragma once

namespace p9
{

    namespace lexer
    {

        enum Type {

            T_EOF = 0,

            T_Add,
            T_Substract,
            T_Multiply,
            T_Divide,
            T_Modulo,
            T_Spaces,
            T_Newline,
            T_Indent,
            T_Dedent,
            T_Number,

            T_Invalid,

        };

    }

}
