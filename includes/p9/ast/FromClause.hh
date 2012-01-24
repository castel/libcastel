#pragma once

#include <list>
#include <string>

#include "p9/ast/Token.hh"

namespace p9
{
	
	namespace ast
	{
		
		class Identifier;
		
		class FromClause : public Token {
			
		private:
			
			typedef std::list< Identifier * > InternalList;
			
		public:
			
			typedef InternalList::const_iterator const_iterator;
			
			typedef InternalList::iterator iterator;
			
		public:
			
			FromClause & clear( void )
			{ mInternalList.clear( ); return * this; }
			
		public:
			
			FromClause & addSegment( Identifier * segment )
			{ mInternalList.push_back( segment ); return * this; }
			
		public:
			
			iterator begin( void )
			{ return mInternalList.begin( ); }
			
			const_iterator begin( void ) const
			{ return mInternalList.begin( ); }
			
		public:
			
			iterator end( void )
			{ return mInternalList.end( ); }
			
			const_iterator end( void ) const
			{ return mInternalList.end( ); }
			
		public:
			
			std::string toString( void ) const;
			
		private:
			
			InternalList mInternalList;
			
		};
		
	}
	
}
