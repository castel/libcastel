#include <stdexcept>

#include "castel/ast/stmt/ctrl/Until.hh"
#include "castel/gen/SVisitor.hh"

using namespace castel;
using gen::SVisitor;

void SVisitor::visit( ast::stmt::ctrl::Until const & untilControlAst )
{
    throw new std::runtime_error( "Unimplemented" );
}
