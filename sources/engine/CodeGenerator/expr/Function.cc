#include <stdexcept>
#include <vector>

#include <llvm/Analysis/Verifier.h>
#include <llvm/BasicBlock.h>
#include <llvm/DerivedTypes.h>
#include <llvm/Function.h>
#include <llvm/Type.h>

#include "p9/ast/expr/Function.hh"
#include "p9/engine/CodeGenerator.hh"

using namespace p9;
using namespace p9::engine;

void CodeGenerator::visit( ast::expr::Function & function )
{
    if ( ! function.statements( ) )
        throw std::runtime_error( "Missing body" );

    llvm::Type * doubleType = llvm::Type::getDoubleTy(mContext);

    llvm::Type * returnType = doubleType;
    std::vector< llvm::Type * > parametersTypes;

    llvm::FunctionType * functionType = llvm::FunctionType::get( returnType, parametersTypes, false );
    llvm::Function * llvmFunction = llvm::Function::Create( functionType, llvm::Function::ExternalLinkage, "", &mModule );

    llvm::BasicBlock * basicBlock = llvm::BasicBlock::Create( mContext, "", llvmFunction );
    mBuilder.SetInsertPoint( basicBlock );

    function.statements( )->accept( *this );
    mValue.release( );

    llvm::verifyFunction( * llvmFunction );
    mValue.reset( llvmFunction );
}
