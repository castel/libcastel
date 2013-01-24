#include <stdexcept>

#include "castel/ast/stmt/ctrl/While.hh"
#include "castel/gen/SVisitor.hh"

using namespace castel;
using gen::SVisitor;

void SVisitor::visit( ast::stmt::ctrl::While & whileControlAst )
{
    throw new std::runtime_error( "Unimplemented" );
}
