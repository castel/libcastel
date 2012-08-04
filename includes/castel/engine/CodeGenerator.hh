#pragma once

#include <memory>
#include <stack>

#include <llvm/Support/IRBuilder.h>
#include <llvm/Function.h>
#include <llvm/LLVMContext.h>
#include <llvm/Value.h>

#include "castel/ast/expr/Binary.hh"
#include "castel/ast/expr/Call.hh"
#include "castel/ast/expr/Function.hh"
#include "castel/ast/expr/Number.hh"
#include "castel/ast/expr/Variable.hh"
#include "castel/ast/stmt/decl/Variables.hh"
#include "castel/ast/stmt/Expression.hh"
#include "castel/ast/stmt/If.hh"
#include "castel/ast/stmt/Return.hh"
#include "castel/ast/Statement.hh"
#include "castel/engine/Closure.hh"
#include "castel/engine/GenerationEngine.hh"
#include "castel/engine/LLVMHelpers.hh"
#include "castel/utils/Visitor.hh"

namespace castel
{

    namespace engine
    {

        class CodeGenerator : public castel::utils::Visitor
        {

        public:

            CodeGenerator ( engine::GenerationEngine & engine );

        public:

            llvm::Function * codegen( castel::ast::Statement & );

        private:

            virtual void visit( castel::ast::expr::Binary          & );
            virtual void visit( castel::ast::expr::Call            & );
            virtual void visit( castel::ast::expr::Function        & );
            virtual void visit( castel::ast::expr::Number          & );
            virtual void visit( castel::ast::expr::Variable        & );

            virtual void visit( castel::ast::stmt::decl::Variables & );
            virtual void visit( castel::ast::stmt::Expression      & );
            virtual void visit( castel::ast::stmt::If              & );
            virtual void visit( castel::ast::stmt::Return          & );

        private:

            engine::GenerationEngine & mGenerationEngine;
            engine::LLVMHelpers mLLVMHelpers;

            std::stack< engine::Closure * > mClosureStack;

            std::unique_ptr< llvm::Value > mValue;

        };

    }

}
