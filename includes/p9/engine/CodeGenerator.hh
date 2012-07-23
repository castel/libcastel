#pragma once

#include <memory>

#include <llvm/Support/IRBuilder.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Value.h>

#include "p9/ast/expr/Binary.hh"
#include "p9/ast/expr/Call.hh"
#include "p9/ast/expr/Function.hh"
#include "p9/ast/expr/Number.hh"
#include "p9/ast/expr/Variable.hh"
#include "p9/ast/stmt/Expression.hh"
#include "p9/ast/stmt/If.hh"
#include "p9/ast/stmt/Return.hh"
#include "p9/ast/Token.hh"
#include "p9/utils/Visitor.hh"

namespace p9
{

    namespace engine
    {

        class CodeGenerator : public p9::utils::Visitor
        {

        public:

            CodeGenerator ( llvm::LLVMContext & context, llvm::IRBuilder< > & builder, llvm::Module & module );

        public:

            llvm::Value * codegen( p9::ast::Token & );

        private:

            virtual void visit( p9::ast::expr::Binary     & );
            virtual void visit( p9::ast::expr::Call       & );
            virtual void visit( p9::ast::expr::Function   & );
            virtual void visit( p9::ast::expr::Number     & );
            virtual void visit( p9::ast::expr::Variable   & );

            virtual void visit( p9::ast::stmt::Expression & );
            virtual void visit( p9::ast::stmt::If         & );
            virtual void visit( p9::ast::stmt::Return     & );

        private:

            llvm::LLVMContext & mContext;
            llvm::IRBuilder< > & mBuilder;
            llvm::Module & mModule;

            std::unique_ptr< llvm::Value > mValue;

        };

    }

}
