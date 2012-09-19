#pragma once

#include <memory>
#include <string>

#include <llvm/Support/TypeBuilder.h>
#include <llvm/Function.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>

#include "castel/builder/IRBuilder.hh"
#include "castel/runtime/api/boolean.hh"
#include "castel/runtime/api/dict.hh"
#include "castel/runtime/api/function.hh"
#include "castel/runtime/api/list.hh"
#include "castel/runtime/api/null.hh"
#include "castel/runtime/api/number.hh"
#include "castel/runtime/api/string.hh"
#include "castel/runtime/api/undefined.hh"
#include "castel/runtime/api.hh"
#include "castel/utils/LLVMExtensions.hh"

namespace castel
{

    namespace builder
    {

        class Context
        {

        public:

            Context        ( std::string const & name                 )
            : mParent      ( nullptr                                  )
            , mLLVMContext ( new llvm::LLVMContext( )                 )
            , mLLVMModule  ( new llvm::Module( name, * mLLVMContext ) )
            , mIRBuilder   ( * mLLVMContext, * mLLVMModule            )
            {
                llvm::StructType::create( this->llvmContext( ), "Box" );

                #define TO_STRING( X ) #X
                #define REGISTER_FUNCTION( NAME ) this->declareGlobalFunction< decltype( ::NAME ) >( TO_STRING( NAME ), llvm::GlobalValue::ExternalLinkage );

                REGISTER_FUNCTION( castel_allocate );

                REGISTER_FUNCTION( castel_crash );

                REGISTER_FUNCTION( castel_unaryOperatorMissing );
                REGISTER_FUNCTION( castel_binaryOperatorMissing );

                REGISTER_FUNCTION( castel_positiveOperator );
                REGISTER_FUNCTION( castel_negativeOperator );

                REGISTER_FUNCTION( castel_preIncrementationOperator );
                REGISTER_FUNCTION( castel_postIncrementationOperator );
                REGISTER_FUNCTION( castel_preDecrementationOperator );
                REGISTER_FUNCTION( castel_postDecrementationOperator );

                REGISTER_FUNCTION( castel_additionOperator );
                REGISTER_FUNCTION( castel_substractionOperator );
                REGISTER_FUNCTION( castel_multiplicationOperator );
                REGISTER_FUNCTION( castel_divisionOperator );
                REGISTER_FUNCTION( castel_moduloOperator );

                REGISTER_FUNCTION( castel_lesserOperator );
                REGISTER_FUNCTION( castel_greaterOperator );
                REGISTER_FUNCTION( castel_lesserOrEqualOperator );
                REGISTER_FUNCTION( castel_greaterOrEqualOperator );
                REGISTER_FUNCTION( castel_equalOperator );
                REGISTER_FUNCTION( castel_notEqualOperator );

                REGISTER_FUNCTION( castel_additionAssignmentOperator );
                REGISTER_FUNCTION( castel_substractionAssignmentOperator );
                REGISTER_FUNCTION( castel_multiplicationAssignmentOperator );
                REGISTER_FUNCTION( castel_divisionAssignmentOperator );
                REGISTER_FUNCTION( castel_moduloAssignmentOperator );

                REGISTER_FUNCTION( castel_callOperator );
                REGISTER_FUNCTION( castel_subscriptOperator );

                REGISTER_FUNCTION( castel_booleanOperator );

                REGISTER_FUNCTION( castelBoolean_create );
                REGISTER_FUNCTION( castelDict_create );
                REGISTER_FUNCTION( castelFunction_create );
                REGISTER_FUNCTION( castelList_create );
                REGISTER_FUNCTION( castelNull_create );
                REGISTER_FUNCTION( castelNumber_create );
                REGISTER_FUNCTION( castelString_create );
                REGISTER_FUNCTION( castelUndefined_create );

                #undef REGISTER_FUNCTION
                #undef TO_STRING
            }

            Context        ( builder::Context & parent                   )
            : mParent      ( & parent                                    )
            , mLLVMContext ( nullptr                                     )
            , mLLVMModule  ( nullptr                                     )
            , mIRBuilder   ( parent.llvmContext( ), parent.llvmModule( ) )
            {
            }

        public:

            llvm::LLVMContext & llvmContext( void ) const
            {
                return * ( ( mParent ? mParent : this )->mLLVMContext );
            }

            llvm::Module & llvmModule( void ) const
            {
                return * ( ( mParent ? mParent : this )->mLLVMModule );
            }

            builder::IRBuilder & irBuilder( void )
            {
                return mIRBuilder;
            }

        public:

            llvm::Function * declareGlobalFunction( llvm::FunctionType * functionType, std::string const & name, llvm::GlobalValue::LinkageTypes linkageType )
            {
                return llvm::Function::Create( functionType, linkageType, name, mLLVMModule.get( ) );
            }

            template < typename Type >
            llvm::Function * declareGlobalFunction( std::string const & name, llvm::GlobalValue::LinkageTypes linkageType )
            {
                return this->declareGlobalFunction( llvm::TypeBuilder< Type, false >::get( this->llvmContext( ) ), name, linkageType );
            }

        private:

            builder::Context * mParent;

            std::unique_ptr< llvm::LLVMContext > mLLVMContext;
            std::unique_ptr< llvm::Module > mLLVMModule;

            builder::IRBuilder mIRBuilder;

        };

    }

}
