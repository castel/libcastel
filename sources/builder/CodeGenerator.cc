#include <stdexcept>

#include "castel/ast/Token.hh"
#include "castel/builder/CodeGenerator.hh"

using namespace castel;
using builder::CodeGenerator;

void CodeGenerator::defaultAction( ast::Token & )
{
    throw std::runtime_error( "Invalid visitor : node missing" );
}
