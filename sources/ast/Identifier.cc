#include <string>

#include "p9/ast/Identifier.hh"

using namespace p9;
using namespace p9::ast;

std::string Identifier::toString( void ) const
{
	return mIdentifier;
}
