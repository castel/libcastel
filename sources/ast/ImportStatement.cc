#include <string>

#include "p9/ast/ImportStatement.hh"

using namespace p9;
using namespace p9::ast;

std::string ImportStatement::toString( void ) const
{
	std::string result;
	
	if ( mFromClause.get( ) )
	{
		std::list< std::string >::const_iterator it;
		for ( it = mFromClause->begin( ); it != mFromClause->end( ); ++ it )
		{
			if ( it != mFromClause->begin( ) ) {
				result += "." + *it;
			} else {
				result += *it;
			}
		}
	}
	
	if ( mImportClause.get( ) )
	{
		result += "import " + *mImportClause;
	}
	
	if ( mAsClause.get( ) )
	{
		result += " as " + *mAsClause;
	}
	
	result += ";";
	
	return result;
}
