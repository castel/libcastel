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

                Binary          ( ast::expr::Binary::Operator type, ast::Expression * leftOperand = nullptr, ast::Expression * rightOperand = nullptr )
                : mType         ( type         )
                , mLeftOperand  ( leftOperand  )
                , mRightOperand ( rightOperand )
                {
                }

            public:

                ast::expr::Binary::Operator type( void ) const
                {
                    return mType;
                }

                Binary & type( ast::expr::Binary::Operator type )
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

                ast::expr::Binary::Operator mType;

                std::unique_ptr< ast::Expression > mLeftOperand;
                std::unique_ptr< ast::Expression > mRightOperand;

            };

        }

    }

}
