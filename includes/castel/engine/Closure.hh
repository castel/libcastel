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

        public:

            Closure             ( engine::GenerationEngine & generationEngine, llvm::Function * llvmFunction, engine::Closure * parentClosure = nullptr )
            : mFinalized        ( false            )
            , mGenerationEngine ( generationEngine )
            , mLLVMFunction     ( llvmFunction     )
            , mParentClosure    ( parentClosure    )
            {
            }

        public:

            void finalize( void );

        public:

            void declare( std::string const & name, llvm::Value * initializer = nullptr );
            llvm::Value * get( std::string const & name );
            llvm::Value * set( std::string const & name, llvm::Value * );

        private:

            llvm::Value * recurseAddressorSearch( std::string const & name );

            llvm::Value * variableAddressor( std::string const & name );
            llvm::Value * escapedVariableAddressor( std::string const & name );

        private:

            bool mFinalized;

            engine::GenerationEngine & mGenerationEngine;

            llvm::Function * mLLVMFunction;

            engine::Closure * mParentClosure;

            std::map< std::string, llvm::Value * > mLocalValues;
            std::map< std::string, llvm::Value * > mEscapingValues;

        };

    }

}
