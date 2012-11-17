#pragma once

#include "castel/ast/tools/Linked.hh"
#include "castel/ast/Token.hh"

namespace castel
{

    namespace ast
    {

        class Expression : public ast::Token, public ast::tools::Linked< Expression >
        {

        };

    }

}
