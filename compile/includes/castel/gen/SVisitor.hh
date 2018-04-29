#pragma once

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>

#include "castel/ast/tools/ConstVisitor.hh"

namespace castel
{

    namespace ast
    {

        namespace stmt
        {

            namespace ctrl
            {

                class ForIn;

                class If;

                class Try;

                class Until;

                class While;

            }

            namespace decl
            {

                class Class;

                class Function;

                class Variables;

            }

            class Block;

            class Expression;

            class Return;

            class Throw;

        }

        class Statement;

        class Token;

    }

    namespace gen
    {

        class Scope;

        class SVisitor : public ast::tools::ConstVisitor
        {

        public:

            inline SVisitor( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, gen::Scope & scope );

        public:

            inline void run( ast::Token const & token );

        public:

            virtual void visit( ast::stmt::ctrl::ForIn const & astForInStatement );

            virtual void visit( ast::stmt::ctrl::If const & astIfStatement );

            virtual void visit( ast::stmt::ctrl::Try const & astTryStatement );

            virtual void visit( ast::stmt::ctrl::Until const & astUntilStatement );

            virtual void visit( ast::stmt::ctrl::While const & astWhileStatement );

            virtual void visit( ast::stmt::decl::Class const & astClassDeclaration );

            virtual void visit( ast::stmt::decl::Function const & astFunctionDeclaration );

            virtual void visit( ast::stmt::decl::Variables const & astVariableDeclaration );

            virtual void visit( ast::stmt::Block const & astBlockStatement );

            virtual void visit( ast::stmt::Expression const & astExpressionStatement );

            virtual void visit( ast::stmt::Return const & astReturnStatement );

            virtual void visit( ast::stmt::Throw const & astThrowStatement );

        private:

            llvm::LLVMContext & mContext;

            llvm::Module * mModule;

            llvm::IRBuilder< > & mIRBuilder;

            gen::Scope & mScope;

        };

    }

}

#include "castel/ast/stmt/ctrl/ForIn.hh"
#include "castel/ast/stmt/ctrl/If.hh"
#include "castel/ast/stmt/ctrl/Try.hh"
#include "castel/ast/stmt/ctrl/Until.hh"
#include "castel/ast/stmt/ctrl/While.hh"
#include "castel/ast/stmt/decl/Variables.hh"
#include "castel/ast/stmt/Expression.hh"
#include "castel/ast/stmt/Return.hh"
#include "castel/ast/Statement.hh"
#include "castel/ast/Token.hh"
#include "castel/gen/Scope.hh"

namespace castel
{

    namespace gen
    {

        SVisitor::SVisitor( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, gen::Scope & scope )
            : mContext( context )
            , mModule( module )
            , mIRBuilder( irBuilder )
            , mScope( scope )
        {
        }

        void SVisitor::run( ast::Token const & token )
        {
            token.accept( * this );
        }

    }

}
