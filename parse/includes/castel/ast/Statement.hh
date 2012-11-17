#pragma once

#include "castel/ast/tools/Linked.hh"
#include "castel/ast/Token.hh"

namespace castel
{

    namespace ast
    {

        class Statement : public ast::Token, public ast::tools::Linked< Statement >
        {

        };

    }

}
