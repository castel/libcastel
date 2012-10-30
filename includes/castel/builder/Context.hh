#pragma once

#include <memory>
#include <string>

#include <llvm/Support/TypeBuilder.h>
#include <llvm/Function.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

#include "castel/builder/IRBuilder.hh"
#include "castel/runtime/capi/bool.hh"
#include "castel/runtime/capi/class.hh"
#include "castel/runtime/capi/dict.hh"
#include "castel/runtime/capi/function.hh"
#include "castel/runtime/capi/list.hh"
#include "castel/runtime/capi/null.hh"
#include "castel/runtime/capi/number.hh"
#include "castel/runtime/capi/string.hh"
#include "castel/runtime/capi/undefined.hh"
#include "castel/runtime/capi.hh"
#include "castel/utils/LLVMExtensions.hh"

namespace castel
{

    namespace builder
    {

        class Context
        {

        public:

            inline Context( std::string const & name = "" );

            inline Context( builder::Context & parent );

        public:

            inline llvm::LLVMContext & llvmContext( void ) const;

            inline llvm::Module & llvmModule( void ) const;

            inline builder::IRBuilder & irBuilder( void );

        public:

            inline llvm::Function * declareGlobalFunction( llvm::FunctionType * functionType, std::string const & name, llvm::GlobalValue::LinkageTypes linkageType );

            template < typename Type >
            inline llvm::Function * declareGlobalFunction( std::string const & name, llvm::GlobalValue::LinkageTypes linkageType );

        private:

            void registerFunctions( void );

        private:

            builder::Context * mParent;

            std::unique_ptr< llvm::LLVMContext > mLLVMContext;
            std::unique_ptr< llvm::Module > mLLVMModule;

            builder::IRBuilder mIRBuilder;

        };

    }

}

namespace castel
{

    namespace builder
    {

        Context::Context( std::string const & name )
            : mParent( nullptr )
            , mLLVMContext( new llvm::LLVMContext( ) )
            , mLLVMModule( new llvm::Module( name, * mLLVMContext ) )
            , mIRBuilder( * mLLVMContext, * mLLVMModule )
        {
            llvm::StructType::create( this->llvmContext( ), "Box" );

            this->registerFunctions( );
        }

        Context::Context( builder::Context & parent )
            : mParent      ( & parent )
            , mLLVMContext ( nullptr )
            , mLLVMModule  ( nullptr )
            , mIRBuilder   ( parent.llvmContext( ), parent.llvmModule( ) )
        {
        }

        llvm::LLVMContext & Context::llvmContext( void ) const
        {
            return * ( ( mParent ? mParent : this )->mLLVMContext );
        }

        llvm::Module & Context::llvmModule( void ) const
        {
            return * ( ( mParent ? mParent : this )->mLLVMModule );
        }

        builder::IRBuilder & Context::irBuilder( void )
        {
            return mIRBuilder;
        }

        llvm::Function * Context::declareGlobalFunction( llvm::FunctionType * functionType, std::string const & name, llvm::GlobalValue::LinkageTypes linkageType )
        {
            return llvm::Function::Create( functionType, linkageType, name, mLLVMModule.get( ) );
        }

        template < typename Type >
        llvm::Function * Context::declareGlobalFunction( std::string const & name, llvm::GlobalValue::LinkageTypes linkageType )
        {
            return this->declareGlobalFunction( llvm::TypeBuilder< Type, false >::get( this->llvmContext( ) ), name, linkageType );
        }

    }

}
