#include <string>

#include "p9/ast/AsClause.hh"
#include "p9/ast/Identifier.hh"

using namespace p9;
using namespace p9::ast;

std::string AsClause::toString( void ) const
{
	return std::string( "as " ) + mTarget->toString( );
}
