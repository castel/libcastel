#pragma once

#include <memory>
#include <stack>

#include <llvm/Support/IRBuilder.h>
#include <llvm/Function.h>
#include <llvm/LLVMContext.h>
#include <llvm/Value.h>

#include "castel/ast/expr/Boolean.hh"
#include "castel/ast/expr/Binary.hh"
#include "castel/ast/expr/Function.hh"
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
#include "castel/builder/Closure.hh"
#include "castel/builder/Context.hh"
#include "castel/utils/Visitor.hh"

namespace castel
{

    namespace builder
    {

        class CodeGenerator : public utils::Visitor
        {

        public:

            CodeGenerator ( builder::Context & context )
            : mContext    ( context )
            {
            }

        public:

            llvm::Function * codegen( ast::Statement & );

        private:

            virtual void visit( ast::expr::Boolean         & );
            virtual void visit( ast::expr::Binary          & );
            virtual void visit( ast::expr::Function        & );
            virtual void visit( ast::expr::Multary         & );
            virtual void visit( ast::expr::Null            & );
            virtual void visit( ast::expr::Number          & );
            virtual void visit( ast::expr::Unary           & );
            virtual void visit( ast::expr::Undefined       & );
            virtual void visit( ast::expr::Variable        & );

        public:

            virtual void visit( ast::stmt::decl::Variables & );
            virtual void visit( ast::stmt::Expression      & );
            virtual void visit( ast::stmt::If              & );
            virtual void visit( ast::stmt::Return          & );

        private:

            builder::Context & mContext;

            std::stack< builder::Closure * > mClosureStack;

            std::unique_ptr< llvm::Value > mValue;

        };

    }

}
