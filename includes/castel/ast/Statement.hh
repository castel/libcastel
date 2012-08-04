#pragma once

#include "castel/ast/Token.hh"
#include "castel/utils/Linked.hh"

namespace castel
{

    namespace ast
    {

        class Statement : public ast::Token, public utils::Linked< Statement >
        {

        };

    }

}
