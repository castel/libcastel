#pragma once

#include <string>

#include <llvm/IRBuilder.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Value.h>

#include "castel/ast/expr/Class.hh"

namespace castel
{

    namespace gen
    {

        class Scope;

        class ClassBuilder
        {

        public:

            inline ClassBuilder( std::string const & name = "" );

        public:

            inline std::string const & name( void ) const;

            inline ClassBuilder & name( std::string const & name );

        public:

            inline llvm::Value * parent( void ) const;

            inline ClassBuilder & parent( llvm::Value * parent );

        public:

            inline ast::expr::Class::Member * members( void ) const;

            inline ClassBuilder & members( ast::expr::Class::Member * members );

        public:

            llvm::Value * build( llvm::LLVMContext & context, llvm::Module * module, llvm::IRBuilder< > & irBuilder, gen::Scope & parentScope ) const;

        private:

            llvm::Value * createInitializer( llvm::LLVMContext & context, llvm::Module * module, gen::Scope & parentScope ) const;

        private:

            std::string mName;

            llvm::Value * mParent;

            ast::expr::Class::Member * mMembers;

        };

    }

}

#include "castel/gen/Scope.hh"

namespace castel
{

    namespace gen
    {

        ClassBuilder::ClassBuilder( std::string const & name )
            : mName( name )
            , mParent( nullptr )
            , mMembers( nullptr )
        {
        }

        std::string const & ClassBuilder::name( void ) const
        {
            return mName;
        }

        ClassBuilder & ClassBuilder::name( std::string const & name )
        {
            mName = name;

            return * this;
        }

        llvm::Value * ClassBuilder::parent( void ) const
        {
            return mParent;
        }

        ClassBuilder & ClassBuilder::parent( llvm::Value * parent )
        {
            mParent = parent;

            return * this;
        }

        ast::expr::Class::Member * ClassBuilder::members( void ) const
        {
            return mMembers;
        }

        ClassBuilder & ClassBuilder::members( ast::expr::Class::Member * members )
        {
            mMembers = members;

            return * this;
        }

    }

}
