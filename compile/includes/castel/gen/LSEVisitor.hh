#pragma once

#include <llvm/IRBuilder.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Value.h>

#include "castel/ast/tools/ConstVisitor.hh"

namespace castel
{

    namespace ast
    {

        namespace expr
        {

            class Binary;

            class Variable;

        }

        class Expression;

        class Token;

    }

    namespace gen
    {

        class Scope;

        class LSEVisitor : public ast::tools::ConstVisitor
        {

        public:

            inline LSEVisitor( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, gen::Scope & scope, llvm::Value * value );

        public:

            inline void run( ast::Token const & token );

        public:

            virtual void visit( ast::expr::Binary const & astBinaryExpression );

            virtual void visit( ast::expr::Variable const & astVariableExpression );

        private:

            llvm::LLVMContext & mContext;

            llvm::Module * mModule;

            llvm::IRBuilder< > & mIRBuilder;

            gen::Scope & mScope;

            llvm::Value * mValue;

        };

    }

}

#include "castel/ast/expr/Binary.hh"
#include "castel/ast/expr/Variable.hh"
#include "castel/ast/Expression.hh"
#include "castel/ast/Token.hh"
#include "castel/gen/Scope.hh"

namespace castel
{

    namespace gen
    {

        LSEVisitor::LSEVisitor( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, gen::Scope & scope, llvm::Value * value )
            : mContext( context )
            , mModule( module )
            , mIRBuilder( irBuilder )
            , mScope( scope )
            , mValue( value )
        {
        }

        void LSEVisitor::run( ast::Token const & token )
        {
            token.accept( * this );
        }

    }

}
