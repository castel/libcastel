#include <stdexcept>

#include "castel/ast/stmt/ctrl/ForIn.hh"
#include "castel/gen/SVisitor.hh"

using namespace castel;
using gen::SVisitor;

void SVisitor::visit( ast::stmt::ctrl::ForIn const & forInControlAst )
{
    throw new std::runtime_error( "Unimplemented" );
}
