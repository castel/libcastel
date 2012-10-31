#pragma once

#include <memory>

#include <llvm/Value.h>

#include "castel/ast/expr/Boolean.hh"
#include "castel/ast/expr/Binary.hh"
#include "castel/ast/expr/Class.hh"
#include "castel/ast/expr/Function.hh"
#include "castel/ast/expr/List.hh"
#include "castel/ast/expr/Multary.hh"
#include "castel/ast/expr/Null.hh"
#include "castel/ast/expr/Number.hh"
#include "castel/ast/expr/Unary.hh"
#include "castel/ast/expr/Undefined.hh"
#include "castel/ast/expr/Variable.hh"
#include "castel/ast/stmt/decl/Variables.hh"
#include "castel/ast/stmt/Expression.hh"
#include "castel/ast/stmt/If.hh"
#include "castel/ast/stmt/Return.hh"
#include "castel/ast/Statement.hh"
#include "castel/builder/Context.hh"
#include "castel/builder/Scope.hh"
#include "castel/utils/Visitor.hh"

namespace castel
{

    namespace builder
    {

        class CodeGenerator : public utils::Visitor
        {

        public:

            /**
             * Constructs a CodeGenerator instance.
             */

            inline CodeGenerator( builder::Context & context, builder::Scope & scope );

        public:

            /**
             * Return a LLVM value resulting from the specified AST evaluation.
             */

            inline llvm::Value * expression( ast::Expression * expression );

            /**
             * Generate code corresponding to the specified AST.
             */

            inline void statement( ast::Statement * statement );

        public:

            virtual void visit( ast::expr::Boolean & );
            virtual void visit( ast::expr::Binary & );
            virtual void visit( ast::expr::Class & );
            virtual void visit( ast::expr::Dict & );
            virtual void visit( ast::expr::Function & );
            virtual void visit( ast::expr::List & );
            virtual void visit( ast::expr::Multary & );
            virtual void visit( ast::expr::Null & );
            virtual void visit( ast::expr::Number & );
            virtual void visit( ast::expr::String & );
            virtual void visit( ast::expr::Unary & );
            virtual void visit( ast::expr::Undefined & );
            virtual void visit( ast::expr::Variable & );

        public:

            virtual void visit( ast::stmt::decl::Variables & );
            virtual void visit( ast::stmt::Expression & );
            virtual void visit( ast::stmt::If & );
            virtual void visit( ast::stmt::Return & );

        private:

            builder::Context & mContext;
            builder::Scope & mScope;

            std::unique_ptr< llvm::Value > mValue;

        };

    }

}

namespace castel
{

    namespace builder
    {

        CodeGenerator::CodeGenerator( builder::Context & context, builder::Scope & scope )
            : mContext( context )
            , mScope( scope )
        {
        }

        llvm::Value * CodeGenerator::expression( ast::Expression * expression )
        {
            expression->accept( * this );

            return mValue.release( );
        }

        void CodeGenerator::statement( ast::Statement * statement )
        {
            statement->accept( * this );
        }

    }

}
