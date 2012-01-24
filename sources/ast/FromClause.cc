#include <algorithm>
#include <string>

#include "p9/ast/FromClause.hh"
#include "p9/ast/Identifier.hh"

using namespace p9;
using namespace p9::ast;

std::string FromClause::toString( void ) const
{
	std::string result;
	
	if ( mInternalList.size( ) ) {
		
		result += "from ";
		
		const_iterator cit;
		
		for ( cit = begin( ); cit != end( ); ++ cit ) {
			
			if ( cit != begin( ) )
				
				result += '.';
			
			result += ( *cit )->toString( );
			
		}
		
	}
	
	return result;
}
