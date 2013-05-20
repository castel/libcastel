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

                class Variables;

            }

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

        class SVisitor : public ast::tools::Visitor
        {

        public:

            inline SVisitor( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, gen::Scope & scope );

        public:

            inline void run( ast::Token & token );

        public:

            virtual void visit( ast::stmt::ctrl::ForIn & astForInStatement );

            virtual void visit( ast::stmt::ctrl::If & astIfStatement );

            virtual void visit( ast::stmt::ctrl::Try & astTryStatement );

            virtual void visit( ast::stmt::ctrl::Until & astUntilStatement );

            virtual void visit( ast::stmt::ctrl::While & astWhileStatement );

            virtual void visit( ast::stmt::decl::Variables & astVariableDeclaration );

            virtual void visit( ast::stmt::Expression & astExpressionStatement );

            virtual void visit( ast::stmt::Return & astReturnStatement );

            virtual void visit( ast::stmt::Throw & astThrowStatement );

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

        void SVisitor::run( ast::Token & token )
        {
            token.accept( * this );
        }

    }

}
