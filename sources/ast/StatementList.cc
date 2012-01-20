#include "p9/ast/StatementList.hh"

using namespace p9::ast;

StatementList::StatementList( void )
{
}

StatementList & StatementList::merge( Statement * statement )
{
	mStlList.push_back( statement );
	return *this;
}

StatementList & StatementList::merge( StatementList * other )
{
	mStlList.splice( mStlList.end( ), other->mStlList );
	delete other;
	return *this;
}
