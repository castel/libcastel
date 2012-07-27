#pragma once

#include "p9/ast/Token.hh"
#include "p9/utils/Linked.hh"

namespace p9
{

    namespace ast
    {

        class Expression : public ast::Token, public utils::Linked< Expression >
        {

        };

    }

}
