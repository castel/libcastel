#pragma once

#include <utility>

#include "castel/ast/tools/Hold.hh"
#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            class ConstVisitor;

            class Visitor;

        }

        namespace expr
        {

            class Binary : public ast::Expression
            {

            public:

                enum class Operator {

                    Assignment,

                    Addition,
                    Substraction,
                    Multiplication,
                    Division,
                    Modulo,

                    AdditionAssignment,
                    SubstractionAssignment,
                    MultiplicationAssignment,
                    DivisionAssignment,
                    ModuloAssignment,

                    BitwiseAnd,
                    BitwiseOr,
                    BitwiseXOr,
                    LeftShift,
                    RightShift,

                    BitwiseAndAssignment,
                    BitwiseOrAssignment,
                    BitwiseXOrAssignment,
                    LeftShiftAssignment,
                    RightShiftAssignment,

                    Lesser,
                    Greater,
                    LesserOrEqual,
                    GreaterOrEqual,
                    Equal,
                    NotEqual,

                    LogicalAnd,
                    LogicalOr,

                    Member,

                };

            public:

                inline Binary( ast::expr::Binary::Operator type );

                inline Binary( ast::expr::Binary::Operator type, ast::tools::Hold< ast::Expression > && leftOperand, ast::tools::Hold< ast::Expression > && rightOperand );

            public:

                inline ast::expr::Binary::Operator type( void ) const;

                inline Binary & type( ast::expr::Binary::Operator type );

            public:

                inline ast::tools::Hold< ast::Expression > const & leftOperand( void ) const;

                inline ast::tools::Hold< ast::Expression > & leftOperand( void );

                inline Binary & leftOperand( ast::tools::Hold< ast::Expression > && expression );

            public:

                inline ast::tools::Hold< ast::Expression > const & rightOperand( void ) const;

                inline ast::tools::Hold< ast::Expression > & rightOperand( void );

                inline Binary & rightOperand( ast::tools::Hold< ast::Expression > && expression );

            public:

                virtual inline void accept( ast::tools::ConstVisitor & visitor ) const;

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                ast::expr::Binary::Operator mType;

                ast::tools::Hold< ast::Expression > mLeftOperand;

                ast::tools::Hold< ast::Expression > mRightOperand;

            };

        }

    }

}

#include "castel/ast/tools/ConstVisitor.hh"
#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            Binary::Binary( ast::expr::Binary::Operator type )
                : mType( type )
                , mLeftOperand( )
                , mRightOperand( )
            {
            }

            Binary::Binary( ast::expr::Binary::Operator type, ast::tools::Hold< ast::Expression > && leftOperand, ast::tools::Hold< ast::Expression > && rightOperand )
                : mType( type )
                , mLeftOperand( std::move( leftOperand ) )
                , mRightOperand( std::move( rightOperand ) )
            {
            }

            ast::expr::Binary::Operator Binary::type( void ) const
            {
                return mType;
            }

            Binary & Binary::type( ast::expr::Binary::Operator type )
            {
                mType = type;

                return * this;
            }

            ast::tools::Hold< ast::Expression > const & Binary::leftOperand( void ) const
            {
                return mLeftOperand;
            }

            ast::tools::Hold< ast::Expression > & Binary::leftOperand( void )
            {
                return mLeftOperand;
            }

            Binary & Binary::leftOperand( ast::tools::Hold< ast::Expression > && leftOperand )
            {
                mLeftOperand = std::move( leftOperand );

                return * this;
            }

            ast::tools::Hold< ast::Expression > const & Binary::rightOperand( void ) const
            {
                return mRightOperand;
            }

            ast::tools::Hold< ast::Expression > & Binary::rightOperand( void )
            {
                return mRightOperand;
            }

            Binary & Binary::rightOperand( ast::tools::Hold< ast::Expression > && rightOperand )
            {
                mRightOperand = std::move( rightOperand );

                return * this;
            }

            void Binary::accept( ast::tools::ConstVisitor & visitor ) const
            {
                visitor.visit( * this );
            }

            void Binary::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
