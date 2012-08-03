#pragma once

#include <memory>
#include <stack>

#include <llvm/Support/IRBuilder.h>
#include <llvm/Function.h>
#include <llvm/LLVMContext.h>
#include <llvm/Value.h>

#include "p9/ast/expr/Binary.hh"
#include "p9/ast/expr/Call.hh"
#include "p9/ast/expr/Function.hh"
#include "p9/ast/expr/Number.hh"
#include "p9/ast/expr/Variable.hh"
#include "p9/ast/stmt/decl/Variables.hh"
#include "p9/ast/stmt/Expression.hh"
#include "p9/ast/stmt/If.hh"
#include "p9/ast/stmt/Return.hh"
#include "p9/ast/Statement.hh"
#include "p9/engine/Closure.hh"
#include "p9/engine/GenerationEngine.hh"
#include "p9/engine/LLVMHelpers.hh"
#include "p9/utils/Visitor.hh"

namespace p9
{

    namespace engine
    {

        class CodeGenerator : public p9::utils::Visitor
        {

        public:

            CodeGenerator ( engine::GenerationEngine & engine );

        public:

            llvm::Function * codegen( p9::ast::Statement & );

        private:

            virtual void visit( p9::ast::expr::Binary          & );
            virtual void visit( p9::ast::expr::Call            & );
            virtual void visit( p9::ast::expr::Function        & );
            virtual void visit( p9::ast::expr::Number          & );
            virtual void visit( p9::ast::expr::Variable        & );

            virtual void visit( p9::ast::stmt::decl::Variables & );
            virtual void visit( p9::ast::stmt::Expression      & );
            virtual void visit( p9::ast::stmt::If              & );
            virtual void visit( p9::ast::stmt::Return          & );

        private:

            engine::GenerationEngine & mGenerationEngine;
            engine::LLVMHelpers mLLVMHelpers;

            std::stack< engine::Closure * > mClosureStack;

            std::unique_ptr< llvm::Value > mValue;

        };

    }

}
