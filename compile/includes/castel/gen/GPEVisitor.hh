#pragma once

#include <llvm/IRBuilder.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Value.h>

#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            namespace literal
            {

                class Boolean;

                class Class;

                class Dict;

                class Function;

                class List;

                class Null;

                class Number;

                class String;

                class Undefined;

            }

            class Binary;

            class External;

            class Multary;

            class Unary;

            class Variable;

        }

        class Expression;

        class Token;

    }

    namespace gen
    {

        class Scope;

        class GPEVisitor : public ast::tools::ConstVisitor
        {

        public:

            inline GPEVisitor( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, gen::Scope & scope );

        public:

            inline llvm::Value * lastReturnedValue( void ) const;

        public:

            inline llvm::Value * run( ast::Token const & token );

        public:

            virtual void visit( ast::expr::literal::Boolean const & boolLiteralAst );

            virtual void visit( ast::expr::literal::Class const & classLiteralAst );

            virtual void visit( ast::expr::literal::Dict const & dictLiteralAst );

            virtual void visit( ast::expr::literal::Function const & functionLiteralAst );

            virtual void visit( ast::expr::literal::List const & listLiteralAst );

            virtual void visit( ast::expr::literal::Null const & nullLiteralAst );

            virtual void visit( ast::expr::literal::Number const & numberLiteralAst );

            virtual void visit( ast::expr::literal::String const & stringLiteralAst );

            virtual void visit( ast::expr::literal::Undefined const & undefinedLiteralAst );

            virtual void visit( ast::expr::Binary const & binaryExpressionAst );

            virtual void visit( ast::expr::External const & externalExpressionAst );

            virtual void visit( ast::expr::Multary const & multaryExpressionAst );

            virtual void visit( ast::expr::Unary const & unaryExpressionAst );

            virtual void visit( ast::expr::Variable const & variableExpressionAst );

        private:

            llvm::LLVMContext & mContext;

            llvm::Module * mModule;

            llvm::IRBuilder< > & mIRBuilder;

            gen::Scope & mScope;

            llvm::Value * mLastReturnedValue;

        };

    }

}

#include "castel/ast/expr/literal/Boolean.hh"
#include "castel/ast/expr/literal/Class.hh"
#include "castel/ast/expr/literal/Dict.hh"
#include "castel/ast/expr/literal/Function.hh"
#include "castel/ast/expr/literal/List.hh"
#include "castel/ast/expr/literal/Null.hh"
#include "castel/ast/expr/literal/Number.hh"
#include "castel/ast/expr/literal/String.hh"
#include "castel/ast/expr/literal/Undefined.hh"
#include "castel/ast/expr/Binary.hh"
#include "castel/ast/expr/External.hh"
#include "castel/ast/expr/Multary.hh"
#include "castel/ast/expr/Unary.hh"
#include "castel/ast/expr/Variable.hh"
#include "castel/ast/Expression.hh"
#include "castel/ast/Token.hh"
#include "castel/gen/Scope.hh"

namespace castel
{

    namespace gen
    {

        GPEVisitor::GPEVisitor( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, gen::Scope & scope )
            : mContext( context )
            , mModule( module )
            , mIRBuilder( irBuilder )
            , mScope( scope )
            , mLastReturnedValue( nullptr )
        {
        }

        llvm::Value * GPEVisitor::lastReturnedValue( void ) const
        {
            return mLastReturnedValue;
        }

        llvm::Value * GPEVisitor::run( ast::Token const & token )
        {
            token.accept( * this );

            return this->lastReturnedValue( );
        }

    }

}
