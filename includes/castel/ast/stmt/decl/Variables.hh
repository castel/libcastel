#pragma once

#include <memory>

#include "castel/ast/Statement.hh"
#include "castel/utils/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace stmt
        {

            namespace decl
            {

                class Variables : public ast::Statement
                {

                public:

                    class Variable;

                public:

                    Variables    ( ast::stmt::decl::Variables::Variable * variables = nullptr )
                    : mVariables ( variables )
                    {
                    }

                public:

                    ast::stmt::decl::Variables::Variable * variables( void ) const
                    {
                        return mVariables.get( );
                    }

                    Variables & variables( ast::stmt::decl::Variables::Variable * variables )
                    {
                        mVariables.reset( variables );

                        return *this;
                    }

                    ast::stmt::decl::Variables::Variable * takeVariables( void )
                    {
                        return mVariables.get( );
                    }

                public:

                    void accept( utils::Visitor & visitor )
                    {
                        visitor.visit( *this );
                    }

                private:

                    std::unique_ptr< ast::stmt::decl::Variables::Variable > mVariables;

                };

            }

        }

    }

}

#include "castel/ast/stmt/decl/Variables/Variable.hh"
