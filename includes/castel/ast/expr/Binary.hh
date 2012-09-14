#pragma once

#include <memory>

#include "castel/ast/Expression.hh"
#include "castel/lexer/Lexeme.hh"
#include "castel/utils/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class Binary : public ast::Expression
            {

            public:

                Binary          ( lexer::Lexeme::Type type = lexer::Lexeme::Type::Invalid, ast::Expression * leftOperand = nullptr, ast::Expression * rightOperand = nullptr )
                : mType         ( type         )
                , mLeftOperand  ( leftOperand  )
                , mRightOperand ( rightOperand )
                {
                }

            public:

                lexer::Lexeme::Type type( void ) const
                {
                    return mType;
                }

                Binary & type( lexer::Lexeme::Type type )
                {
                    mType = type;

                    return * this;
                }

            public:

                ast::Expression * leftOperand( void ) const
                {
                    return mLeftOperand.get( );
                }

                Binary & leftOperand( ast::Expression * expression )
                {
                    mLeftOperand.reset( expression );

                    return * this;
                }

                ast::Expression * takeLeftOperand( void )
                {
                    return mLeftOperand.release( );
                }

            public:

                ast::Expression * rightOperand( void ) const
                {
                    return mRightOperand.get( );
                }

                Binary & rightOperand( ast::Expression * expression )
                {
                    mRightOperand.reset( expression );

                    return *this;
                }

                ast::Expression * takeRightOperand( void )
                {
                    return mRightOperand.release( );
                }

            public:

                virtual void accept( utils::Visitor & visitor )
                {
                    visitor.visit( *this );
                }

            private:

                lexer::Lexeme::Type mType;

                std::unique_ptr< ast::Expression > mLeftOperand;
                std::unique_ptr< ast::Expression > mRightOperand;

            };

        }

    }

}
