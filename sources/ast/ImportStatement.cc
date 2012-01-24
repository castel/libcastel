#include <string>

#include "p9/ast/AsClause.hh"
#include "p9/ast/FromClause.hh"
#include "p9/ast/Identifier.hh"
#include "p9/ast/ImportStatement.hh"

using namespace p9;
using namespace p9::ast;

std::string ImportStatement::toString( void ) const
{
	std::string result;
	
	if ( mFromClause )
		result += mFromClause->toString( ) + " ";
	
	result += "import " + mLabel->toString( );
	
	if ( mAsClause )
		result += " " + mAsClause->toString( );
	
	result += ";";
	
	return result;
}
