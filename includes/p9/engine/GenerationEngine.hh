#pragma once

#include <string>
#include <vector>

#include <llvm/Support/IRBuilder.h>
#include <llvm/DerivedTypes.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/Type.h>

namespace p9
{

    namespace engine
    {

        class GenerationEngine
        {

        public:

            GenerationEngine ( std::string const & name )
            : mContext       (                )
            , mBuilder       ( mContext       )
            , mModule        ( name, mContext )
            {
                this->initValueStructType( );
            }

        public:

            llvm::LLVMContext & context( void )
            {
                return mContext;
            }

            llvm::IRBuilder< > & builder( void )
            {
                return mBuilder;
            }

            llvm::Module & module( void )
            {
                return mModule;
            }

        public:

            llvm::Type * valueStructType( void ) const
            {
                return mValueStructType;
            }

        private:

            void initValueStructType( void )
            {
                std::vector< llvm::Type * > fields = { llvm::Type::getInt32Ty( mContext ) };
                mValueStructType = llvm::StructType::create( mContext, fields );
            }

        private:

            llvm::LLVMContext mContext;
            llvm::IRBuilder< > mBuilder;
            llvm::Module mModule;

            llvm::Type * mValueStructType;

        };

    }

}
