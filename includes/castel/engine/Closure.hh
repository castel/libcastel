#pragma once

#include <map>
#include <string>

#include <llvm/Function.h>
#include <llvm/Value.h>

#include "castel/engine/GenerationEngine.hh"

namespace castel
{

    namespace engine
    {

        class Closure
        {

        private:

            class Variable;
            class Descriptor;

        public:

            Closure             ( engine::GenerationEngine & generationEngine, llvm::Function & llvmFunction, engine::Closure * parentClosure = nullptr         )
            : mGenerationEngine ( generationEngine                                                                                                              )
            , mLLVMFunction     ( llvmFunction                                                                                                                  )
            , mParentClosure    ( parentClosure                                                                                                                 )
            , mLevel            ( parentClosure ? parentClosure->level( ) + 1 : 0                                                                               )
            , mEnvironmentTable ( new llvm::LoadInst( llvm::ConstantPointerNull::get( mpllvm::get< engine::Value **** >( mGenerationEngine.llvmContext( ) ) ) ) )
            {
            }

        public:

            void finalize( void );

        public:

            unsigned int level( void ) const
            {
                return mLevel;
            }

            llvm::Value * environmentTable( void ) const
            {
                return mEnvironmentTable;
            }

        public:

            void declare ( std::string const & name, llvm::Value * initializer = nullptr );

        public:

            llvm::Value * get ( std::string const & name );
            llvm::Value * set ( std::string const & name, llvm::Value * );

        private:

            engine::Closure::Descriptor * descriptor                ( std::string const & name );

            engine::Closure::Descriptor * createDescriptor          ( std::string const & name, int depth = 0 );
            engine::Closure::Descriptor * recurseDescriptorCreation ( std::string const & name, int depth );

        private:

            unsigned int mLevel;

            engine::GenerationEngine & mGenerationEngine;
            llvm::Function &  mLLVMFunction;

            engine::Closure * mParentClosure;

            std::map< std::string, std::unique_ptr< engine::Closure::Variable > >   mVariables;
            std::map< std::string, std::unique_ptr< engine::Closure::Descriptor > > mDescriptors;

            llvm::Value * mEnvironmentTable;

        };

    }

}

#include "castel/engine/Closure/Descriptor.hh"
#include "castel/engine/Closure/Variable.hh"
