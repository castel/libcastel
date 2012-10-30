#pragma once

#include <memory>
#include <stdexcept>
#include <string>

#include <llvm/Support/TypeBuilder.h>
#include <llvm/BasicBlock.h>
#include <llvm/Constants.h>
#include <llvm/Instructions.h>
#include <llvm/Value.h>

#include "castel/builder/Context.hh"

namespace castel
{

    namespace builder
    {

        class Scope
        {

        private:

            class Descriptor;
            class Variable;

        public:

            /**
             * @param context Compiler context
             * @param firstBasicBlock First basic block
             *
             * Initialize a scope.
             *
             * Every scope-related instructions will be prepend into this block.
             *
             * The default parent environment table will be set as the environment table of the parent
             * scope if applicable, or nullptr. This choice can be overriden by calling the
             * parentEnvironmentTable setter.
             *
             * @throws std::runtime_error When the parent scope is not in the same context.
             */

            inline Scope( builder::Context & context, llvm::BasicBlock & basicBlock, builder::Scope * parent = nullptr );

            /**
             * Update the basic block with the scope-related instructions.
             *
             * Link every accessed variables with their correct values.
             */

            ~Scope( void );

        public:

            /**
             * @return Scope context
             */

            inline builder::Context & context( void ) const;

        public:

            /**
             * This function has a constant-time complexity.
             *
             * __Q/A__ : Why not using 'depth' ?
             * Because level means that the 0 is the first element, whereas depth means that the 0 is
             * the last element. We are using the name 'depth' inside the descriptors (which are a
             * private interface) and there is a subtle difference between their values.
             *
             * @return Scope level
             */

            inline unsigned int level( void ) const;

        public:

            /**
             * @return Parent scope environment table value
             */

            inline llvm::Value * parentEnvironmentTable( void ) const;

            /**
             * @param parentEnvironementTable Parent scope environment table value
             *
             * You may eventually want to feed the scope with a custom environment. You way use
             * this setter for this purpose.
             */

            inline Scope & parentEnvironmentTable( llvm::Value * parentEnvironmentTable );

        public:

            /**
             * Please note that the value actually returned by this function is a dummy value : it will
             * be replaced in every LLVM code by the actual value when the scope will be destroyed. For
             * this reason, there is no setter (it does not make sense, since the setter will be
             * replaced in the whole program by the new environment table).
             *
             * @return Scope environment table
             */

            inline llvm::Value * environmentTable( void ) const;

        public:

            /**
             * @param name Variable name
             * @param initializer Variable default value
             *
             * Declare a variable into the scope. If this variable is used only within the local
             * scope, then it will be stored into the stack. Otherwise, it will be store into the
             * heap, in an entry of the scope's environment table.
             */

            Scope & declare( std::string const & name, llvm::Value * initializer = nullptr );

        public:

            /**
             * Get the value of a declared variable.
             *
             * @throws std::runtime_error When the variable is not declared.
             */

            llvm::Value * get( std::string const & name );

            /**
             * Set the value of a declared variable.
             *
             * @throws std::runtime_error When the variable is not declared.
             */

            llvm::Value * set( std::string const & name, llvm::Value * value );

        private:

            /**
             * Explicitely ask to preserve the environment table, even if no variables
             * from this scope are required. We use this if the child functions need to use
             * an environment table later.
             *
             * Asking to preserve an environment table for a scope will automatically ask to
             * preserve the environment table from its parent.
             */

            void preserveEnvironmentTable( void );

            /**
             * Fetch a descriptor for the given variable.
             * If the variable exists somewhere but doesn't have yet any descriptor, a new one will be
             * created and returned.
             *
             * @throws std::runtime_error When the variable is not declared.
             * @returns Variable descriptor
             */

            builder::Scope::Descriptor * descriptor( std::string const & name );

            /**
             * Create a descriptor for the given variable. It will not be stored anywhere, so you
             * probably don't want to use this method.
             *
             * @throws std::runtime_error When the variable is not declared.
             * @returns Variable descriptor
             */

            builder::Scope::Descriptor * createDescriptor( std::string const & name, int depth = 0 );

            /**
             * Forward the research of a variable to the parent scope.
             *
             * @throws std::runtime_error When the variable is not declared.
             * @returns Variable descriptor.
             */

            builder::Scope::Descriptor * recurseDescriptorCreation( std::string const & name, int depth );

        private:

            builder::Context & mContext;
            llvm::BasicBlock & mBasicBlock;

            builder::Scope * mParentScope;
            unsigned int mLevel;

            bool mPreserveEnvironmentTable;
            llvm::Value * mParentEnvironmentTable;
            std::unique_ptr< llvm::Value > mEnvironmentTable;

            std::map< std::string, std::unique_ptr< builder::Scope::Variable > > mVariables;
            std::map< std::string, std::unique_ptr< builder::Scope::Descriptor > > mDescriptors;

        };

        /**
         * This class represents a scope variable.
         */

        class Scope::Variable
        {

        public:

            /**
             * List of variable status.
             *
             * - Local means that the variable is accessed only in its declaration scope
             * - Escaping means that subscopes have requested to access to this variable
             */

            enum class Status {
                Local,
                Escaping
            };

        public:

            /**
             * Constructs a Variable instance.
             */

            inline Variable( llvm::LLVMContext & llvmContext );

        public:

            /**
             * The value returned is a dummy value which will be later replaced by an i64 value : the
             * index of the variable inside its container.
             *
             * @returns Dummy value for the variable index
             */

            inline llvm::Value * dummy( void ) const;

        public:

            /**
             * @return Variable status
             */

            inline builder::Scope::Variable::Status status( void ) const;

            /**
             * @param status Variable status
             */

            inline Scope::Variable & status( builder::Scope::Variable::Status status );

        private:

            std::unique_ptr< llvm::Value > mDummy;
            builder::Scope::Variable::Status mStatus;

        };

        /**
         * This class represents a variable inside a scope. It allows to cache the lookup when
         * accessing to the same variable multiple times.
         */

        class Scope::Descriptor
        {

        public:

            /**
             * Constructs a descriptor instance.
             */

            inline Descriptor( llvm::LLVMContext & llvmContext, builder::Scope::Variable & variable, unsigned int depth );

        public:

            /**
             * The value returned is a dummy value which will be replaced later by the address where
             * the get and set methods will need to load (or store) data.
             *
             * Please note that these addresses will use the dummy value of the variable (see above),
             * which will only be resolved when the variables' scopes will be destroyed.
             *
             * @return Dummy value for the variable
             */

            inline llvm::Value * dummy( void ) const;

        public:

            /**
             * @return Variable targeted by the descriptor
             */

            inline builder::Scope::Variable & variable( void ) const;

        public:

            /**
             * @return Depth of the variable scope inside the scope stack
             */

            inline unsigned int depth( void ) const;

        private:

            std::unique_ptr< llvm::Value > mDummy;
            builder::Scope::Variable & mVariable;
            unsigned int mDepth;

        };

    }

}

namespace castel
{

    namespace builder
    {

        Scope::Variable::Variable( llvm::LLVMContext & llvmContext )
            : mDummy( new llvm::LoadInst( llvm::ConstantPointerNull::get( llvm::TypeBuilder< int *, false >::get( llvmContext ) ) ) )
            , mStatus( builder::Scope::Variable::Status::Local )
        {
        }

        llvm::Value * Scope::Variable::dummy( void ) const
        {
            return mDummy.get( );
        }

        builder::Scope::Variable::Status Scope::Variable::status( void ) const
        {
            return mStatus;
        }

        Scope::Variable & Scope::Variable::status( builder::Scope::Variable::Status status )
        {
            mStatus = status;

            return * this;
        }

        Scope::Descriptor::Descriptor( llvm::LLVMContext & llvmContext, builder::Scope::Variable & variable, unsigned int depth )
            : mDummy( new llvm::LoadInst( llvm::ConstantPointerNull::get( llvm::TypeBuilder< runtime::Box ***, false >::get( llvmContext ) ) ) )
            , mVariable( variable )
            , mDepth( depth )
        {
        }

        llvm::Value * Scope::Descriptor::dummy( void ) const
        {
            return mDummy.get( );
        }

        builder::Scope::Variable & Scope::Descriptor::variable( void ) const
        {
            return mVariable;
        }

        unsigned int Scope::Descriptor::depth( void ) const
        {
            return mDepth;
        }

        Scope::Scope( builder::Context & context, llvm::BasicBlock & basicBlock, builder::Scope * parent )
            : mContext( context )
            , mBasicBlock( basicBlock )
            , mParentScope( parent )
            , mLevel( parent ? parent->mLevel + 1 : 0 )
            , mPreserveEnvironmentTable( false )
            , mParentEnvironmentTable( parent ? parent->mEnvironmentTable.get( ) : nullptr )
            , mEnvironmentTable( new llvm::LoadInst( llvm::ConstantPointerNull::get( llvm::TypeBuilder< runtime::Box ****, false >::get( mContext.llvmContext( ) ) ) ) )
            , mVariables( )
            , mDescriptors( )
        {
            if ( parent && & ( context ) != & ( parent->mContext ) ) {
                throw std::runtime_error( "Invalid context in scope creation" );
            }
        }

        builder::Context & Scope::context( void ) const
        {
            return mContext;
        }

        unsigned int Scope::level( void ) const
        {
            return mLevel;
        }

        llvm::Value * Scope::parentEnvironmentTable( void ) const
        {
            return mParentEnvironmentTable;
        }

        Scope & Scope::parentEnvironmentTable( llvm::Value * parentEnvironmentTable )
        {
            mParentEnvironmentTable = parentEnvironmentTable;

            return * this;
        }

        llvm::Value * Scope::environmentTable( void ) const
        {
            return mEnvironmentTable.get( );
        }

    }

}
