#include <stdexcept>

#include "castel/ast/Token.hh"
#include "castel/builder/SetterGenerator.hh"

using namespace castel;
using builder::SetterGenerator;

void SetterGenerator::defaultAction( ast::Token & token )
{
    throw std::runtime_error( "Invalid lvalue" );
}
