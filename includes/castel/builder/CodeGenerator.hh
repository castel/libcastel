#pragma once

#include <memory>

#include <llvm/Value.h>

#include "castel/ast/tools/Visitor.hh"

namespace castel
{

    namespace ast
    {

        namespace stmt
        {

            namespace decl
            {

                class Variables;

            }

            class Expression;

            class If;

            class Return;

        }

        class Statement;

    }

    namespace builder
    {

        class Context;

        class Scope;

        /**
         * This class allows to generate the IR code corresponding to a list of statements.
         */

        class CodeGenerator : public ast::tools::Visitor
        {

        public:

            /**
             * Constructs a CodeGenerator instance.
             */

            inline CodeGenerator( builder::Scope & scope );

        public:

            /**
             * @param astStatement AST statement
             *
             * Generates the IR code corresponding to the specified statement (or list of statements).
             */

            inline void run( ast::Statement & astStatement );

        public:

            /**
             * This method should only be called by instances of ast::stmt::decl::Variables.
             */

            virtual void visit( ast::stmt::decl::Variables & astVariableDeclaration );

            /**
             * This method should only be called by instances of ast::stmt::Expression.
             */

            virtual void visit( ast::stmt::Expression & astExpressionStatement );

            /**
             * This method should only be called by instances of ast::stmt::If.
             */

            virtual void visit( ast::stmt::If & astIfStatement );

            /**
             * This method should only be called by instances of ast::stmt::Return.
             */

            virtual void visit( ast::stmt::Return & astReturnStatement );

        private:

            builder::Context & mContext;

            builder::Scope & mScope;

        };

    }

}

#include "castel/ast/stmt/decl/Variables.hh"
#include "castel/ast/stmt/Expression.hh"
#include "castel/ast/stmt/If.hh"
#include "castel/ast/stmt/Return.hh"
#include "castel/ast/Statement.hh"
#include "castel/builder/Context.hh"
#include "castel/builder/Scope.hh"

namespace castel
{

    namespace builder
    {

        CodeGenerator::CodeGenerator( builder::Scope & scope )
            : mContext( scope.context( ) )
            , mScope( scope )
        {
        }

        void CodeGenerator::run( ast::Statement & astStatement )
        {
            for ( auto & astStatementNode : & astStatement ) {
                astStatementNode.accept( * this );
            }
        }

    }

}
