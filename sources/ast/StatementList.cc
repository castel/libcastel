#include <algorithm>

#include "p9/ast/Statement.hh"
#include "p9/ast/StatementList.hh"

using namespace p9;
using namespace p9::ast;

StatementList & StatementList::clear( void )
{
	std::for_each( mInternalList.begin( ), mInternalList.end( ), &Token::deleter );
	mInternalList.clear( );
	return * this;
}

StatementList & StatementList::merge( Statement * statement )
{
	mInternalList.push_back( statement );
	return * this;
}

StatementList & StatementList::merge( StatementList * other )
{
	mInternalList.splice( mInternalList.end( ), other->mInternalList );
	delete other;
	return * this;
}

std::string StatementList::toString( void ) const
{
	std::string result;
	
	const_iterator cit;
	for ( cit = begin( ); cit != end( ); ++ cit )
		result += (*cit)->toString( );
	
	return result;
}
