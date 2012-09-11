#pragma once

#include <map>
#include <memory>
#include <string>

#include <llvm/Support/TypeBuilder.h>
#include <llvm/Constants.h>
#include <llvm/Function.h>
#include <llvm/Instructions.h>
#include <llvm/Value.h>

#include "castel/builder/Context.hh"
#include "castel/runtime/Box.hh"

namespace castel
{

    namespace builder
    {

        class Closure
        {

        private:

            class Variable;
            class Descriptor;

        public:

            Closure             ( builder::Context & context, llvm::Function & llvmFunction, builder::Closure * parentClosure = nullptr                                 )
            : mContext          ( context                                                                                                                               )
            , mLLVMFunction     ( llvmFunction                                                                                                                          )
            , mParentClosure    ( parentClosure                                                                                                                         )
            , mLevel            ( parentClosure ? parentClosure->level( ) + 1 : 0                                                                                       )
            , mEnvironmentTable ( new llvm::LoadInst( llvm::ConstantPointerNull::get( llvm::TypeBuilder< runtime::Box ****, false >::get( mContext.llvmContext( ) ) ) ) )
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

            builder::Closure::Descriptor * descriptor                ( std::string const & name );

            builder::Closure::Descriptor * createDescriptor          ( std::string const & name, int depth = 0 );
            builder::Closure::Descriptor * recurseDescriptorCreation ( std::string const & name, int depth );

        private:

            unsigned int mLevel;

            builder::Context & mContext;
            llvm::Function &  mLLVMFunction;

            builder::Closure * mParentClosure;

            std::map< std::string, std::unique_ptr< builder::Closure::Variable > >   mVariables;
            std::map< std::string, std::unique_ptr< builder::Closure::Descriptor > > mDescriptors;

            llvm::Value * mEnvironmentTable;

        };

    }

}

#include "castel/builder/Closure/Descriptor.hh"
#include "castel/builder/Closure/Variable.hh"
