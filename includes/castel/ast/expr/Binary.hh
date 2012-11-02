#pragma once

#include <memory>

#include "castel/ast/Expression.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class Binary : public ast::Expression
            {

            public:

                enum class Operator {

                    Assignment,

                    NumericAddition,
                    NumericSubstraction,
                    NumericMultiplication,
                    NumericDivision,
                    NumericModulo,

                    NumericAssignmentAddition,
                    NumericAssignmentSubstraction,
                    NumericAssignmentMultiplication,
                    NumericAssignmentDivision,
                    NumericAssignmentModulo,

                    BinaryAnd,
                    BinaryOr,
                    BinaryXOr,
                    BinaryLShift,
                    BinaryRShift,

                    BinaryAssignmentAnd,
                    BinaryAssignmentOr,
                    BinaryAssignmentXOr,
                    BinaryAssignmentLShift,
                    BinaryAssignmentRShift,

                    ComparisonLesser,
                    ComparisonGreater,
                    ComparisonLesserOrEqual,
                    ComparisonGreaterOrEqual,
                    ComparisonEqual,
                    ComparisonNotEqual,

                    LogicAnd,
                    LogicOr,

                    Member,

                };

            public:

                inline Binary( ast::expr::Binary::Operator type, ast::Expression * leftOperand = nullptr, ast::Expression * rightOperand = nullptr );

            public:

                inline ast::expr::Binary::Operator type( void ) const;

                inline Binary & type( ast::expr::Binary::Operator type );

            public:

                inline ast::Expression * leftOperand( void ) const;

                inline Binary & leftOperand( ast::Expression * expression );

                inline ast::Expression * takeLeftOperand( void );

            public:

                inline ast::Expression * rightOperand( void ) const;

                inline Binary & rightOperand( ast::Expression * expression );

                inline ast::Expression * takeRightOperand( void );

            public:

                virtual inline void accept( ast::tools::Visitor & visitor );

            private:

                ast::expr::Binary::Operator mType;

                std::unique_ptr< ast::Expression > mLeftOperand;
                std::unique_ptr< ast::Expression > mRightOperand;

            };

        }

    }

}

#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            Binary::Binary( ast::expr::Binary::Operator type, ast::Expression * leftOperand, ast::Expression * rightOperand )
                : mType( type )
                , mLeftOperand( leftOperand )
                , mRightOperand( rightOperand )
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

            ast::Expression * Binary::leftOperand( void ) const
            {
                return mLeftOperand.get( );
            }

            Binary & Binary::leftOperand( ast::Expression * leftOperand )
            {
                mLeftOperand.reset( leftOperand );

                return * this;
            }

            ast::Expression * Binary::takeLeftOperand( void )
            {
                return mLeftOperand.release( );
            }

            ast::Expression * Binary::rightOperand( void ) const
            {
                return mRightOperand.get( );
            }

            Binary & Binary::rightOperand( ast::Expression * rightOperand )
            {
                mRightOperand.reset( rightOperand );

                return * this;
            }

            ast::Expression * Binary::takeRightOperand( void )
            {
                return mRightOperand.release( );
            }

            void Binary::accept( ast::tools::Visitor & visitor )
            {
                visitor.visit( * this );
            }

        }

    }

}
