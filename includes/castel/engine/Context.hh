#pragma once

#include <llvm/Context.h>
#include <llvm/Types.h>

namespace castel
{

    namespace engine
    {

        class Context : public llvm::Context
        {

        public:

            Context( void )
            {
                this->initValueStructType( );
            }

        public:

            llvm::StructType * valueStructType( void ) const
            {
                return mValueStructType;
            }

        private:

            void initValueStructType( void )
            {
                std::vector< llvm::Type * > fields;
                fields.push_back( llvm::Type::Int32Ty );
                mValueStructType = llvm::StructType::create( *this );
                mValueStructType->setBody( fields );
            }

        private:

            llvm::StructType * mValueStructType;

        };

    }

}
