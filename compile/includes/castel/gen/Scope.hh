#pragma once

#include <map>
#include <memory>
#include <string>

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Constants.h>
#include <llvm/IR/Instructions.h>
#include <llvm/IR/Value.h>

#include "castel/gen/helper/null.hh"

namespace castel
{

    namespace gen
    {

        struct ValueDeleter
        {

        public:

            void operator()(llvm::Value * ptr) const
            {
                ptr->deleteValue();
            }

        };

        class Scope
        {

        private:

            class Descriptor;

            class Variable;

        public:

            inline Scope( llvm::LLVMContext & context, llvm::Module * module, llvm::BasicBlock * basicBlock );

            inline Scope( llvm::LLVMContext & context, llvm::Module * module, llvm::BasicBlock * basicBlock, gen::Scope & parent, llvm::Value * parentEnvironmentTable );

            ~Scope( void );

        public:

            inline llvm::Value * environmentTable( void ) const;

        public:

            Scope & declare( llvm::IRBuilder< > & irBuilder, std::string const & name, llvm::Value * initializer = nullptr );

            llvm::Value * get( llvm::IRBuilder< > & irBuilder, std::string const & name );

            llvm::Value * set( llvm::IRBuilder< > & irBuilder, std::string const & name, llvm::Value * value );

        private:

            void preserveEnvironmentTable( void );

            gen::Scope::Descriptor * descriptor( std::string const & name );

            gen::Scope::Descriptor * createDescriptor( std::string const & name, int depth = 0 );

            gen::Scope::Descriptor * recurseDescriptorCreation( std::string const & name, int depth );

        private:

            llvm::LLVMContext & mContext;

            llvm::Module * mModule;

            llvm::BasicBlock * mBasicBlock;

            gen::Scope * mParentScope;

            llvm::Value * mParentEnvironmentTable;

            unsigned int mScopeLevel;

            bool mPreserveEnvironmentTable;

            std::unique_ptr< llvm::Value, gen::ValueDeleter > mEnvironmentTable;

            std::map< std::string, std::unique_ptr< gen::Scope::Variable > > mVariables;

            std::map< std::string, std::unique_ptr< gen::Scope::Descriptor > > mDescriptors;

        };

        class Scope::Variable
        {

        public:

            enum class Status {
                Local,
                Escaping
            };

        public:

            inline Variable( llvm::LLVMContext & context );

        public:

            inline llvm::Value * dummy( void ) const;

        public:

            inline gen::Scope::Variable::Status status( void ) const;

            inline Scope::Variable & status( gen::Scope::Variable::Status status );

        private:

            std::unique_ptr< llvm::Value, gen::ValueDeleter > mDummy;

            gen::Scope::Variable::Status mStatus;

        };

        class Scope::Descriptor
        {

        public:

            inline Descriptor( llvm::LLVMContext & context, gen::Scope::Variable & variable, unsigned int depth );

        public:

            inline llvm::Value * dummy( void ) const;

        public:

            inline gen::Scope::Variable & variable( void ) const;

        public:

            inline unsigned int depth( void ) const;

        private:

            std::unique_ptr< llvm::Value, gen::ValueDeleter > mDummy;

            gen::Scope::Variable & mVariable;

            unsigned int mDepth;

        };

    }

}

#include "castel/runtime/Box.hh"

namespace castel
{

    namespace gen
    {

        Scope::Variable::Variable( llvm::LLVMContext & context )
            : mDummy( new llvm::LoadInst( gen::helper::null< int * >( context ) ) )
            , mStatus( gen::Scope::Variable::Status::Local )
        {
        }

        llvm::Value * Scope::Variable::dummy( void ) const
        {
            return mDummy.get( );
        }

        gen::Scope::Variable::Status Scope::Variable::status( void ) const
        {
            return mStatus;
        }

        Scope::Variable & Scope::Variable::status( gen::Scope::Variable::Status status )
        {
            mStatus = status;

            return * this;
        }

        Scope::Descriptor::Descriptor( llvm::LLVMContext & context, gen::Scope::Variable & variable, unsigned int depth )
            : mDummy( new llvm::LoadInst( gen::helper::null< runtime::Box *** >( context ) ) )
            , mVariable( variable )
            , mDepth( depth )
        {
        }

        llvm::Value * Scope::Descriptor::dummy( void ) const
        {
            return mDummy.get( );
        }

        gen::Scope::Variable & Scope::Descriptor::variable( void ) const
        {
            return mVariable;
        }

        unsigned int Scope::Descriptor::depth( void ) const
        {
            return mDepth;
        }

        Scope::Scope( llvm::LLVMContext & context, llvm::Module * module, llvm::BasicBlock * basicBlock )
            : mContext( context )
            , mModule( module )
            , mBasicBlock( basicBlock )

            , mParentScope( nullptr )
            , mParentEnvironmentTable( nullptr )
            , mScopeLevel( 0 )

            , mPreserveEnvironmentTable( false )
            , mEnvironmentTable( new llvm::LoadInst( gen::helper::null< runtime::Box **** >( context ) ) )

            , mVariables( )
            , mDescriptors( )
        {
        }

        Scope::Scope( llvm::LLVMContext & context, llvm::Module * module, llvm::BasicBlock * basicBlock, gen::Scope & parentScope, llvm::Value * parentEnvironmentTable )
            : mContext( context )
            , mModule( module )
            , mBasicBlock( basicBlock )

            , mParentScope( & parentScope )
            , mParentEnvironmentTable( parentEnvironmentTable )
            , mScopeLevel( parentScope.mScopeLevel + 1 )

            , mPreserveEnvironmentTable( false )
            , mEnvironmentTable( new llvm::LoadInst( gen::helper::null< runtime::Box **** >( context ) ) )

            , mVariables( )
            , mDescriptors( )
        {
        }

        llvm::Value * Scope::environmentTable( void ) const
        {
            return mEnvironmentTable.get( );
        }

    }

}
