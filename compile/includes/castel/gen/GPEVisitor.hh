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

            class Binary;

            class Bool;

            class Class;

            class Dict;

            class Function;

            class List;

            class Multary;

            class Null;

            class Number;

            class String;

            class Unary;

            class Undefined;

            class Variable;

        }

        class Expression;

        class Token;

    }

    namespace gen
    {

        class Scope;

        class GPEVisitor : public ast::tools::Visitor
        {

        public:

            inline GPEVisitor( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, gen::Scope & scope );

        public:

            inline llvm::Value * lastReturnedValue( void ) const;

        public:

            inline llvm::Value * run( ast::Token & token );

        public:

            virtual void visit( ast::expr::Bool & astBoolExpression );

            virtual void visit( ast::expr::Binary & astBinaryExpression );

            virtual void visit( ast::expr::Class & astClassExpression );

            virtual void visit( ast::expr::Dict & astDictExpression );

            virtual void visit( ast::expr::Function & astFunctionExpression );

            virtual void visit( ast::expr::List & astListExpression );

            virtual void visit( ast::expr::Multary & astMultaryExpression );

            virtual void visit( ast::expr::Null & astNullExpression );

            virtual void visit( ast::expr::Number & astNumberExpression );

            virtual void visit( ast::expr::String & astStringExpression );

            virtual void visit( ast::expr::Unary & astUnaryExpression );

            virtual void visit( ast::expr::Undefined & astUndefinedExpression );

            virtual void visit( ast::expr::Variable & astVariableExpression );

        private:

            llvm::LLVMContext & mContext;

            llvm::Module * mModule;

            llvm::IRBuilder< > & mIRBuilder;

            gen::Scope & mScope;

            llvm::Value * mLastReturnedValue;

        };

    }

}

#include "castel/ast/expr/Binary.hh"
#include "castel/ast/expr/Bool.hh"
#include "castel/ast/expr/Class.hh"
#include "castel/ast/expr/Dict.hh"
#include "castel/ast/expr/Function.hh"
#include "castel/ast/expr/List.hh"
#include "castel/ast/expr/Multary.hh"
#include "castel/ast/expr/Null.hh"
#include "castel/ast/expr/Number.hh"
#include "castel/ast/expr/String.hh"
#include "castel/ast/expr/Unary.hh"
#include "castel/ast/expr/Undefined.hh"
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

        llvm::Value * GPEVisitor::run( ast::Token & token )
        {
            token.accept( * this );

            return this->lastReturnedValue( );
        }

    }

}
