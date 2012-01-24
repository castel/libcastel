#pragma once

#include <list>

#include "p9/ast/Token.hh"

namespace p9
{
	
	namespace ast
	{
		
		class Statement;
		
		class StatementList : public Token {
			
		private:
			
			typedef std::list< Statement * > InternalList;
			
		public:
			
			typedef InternalList::iterator iterator;
			
			typedef InternalList::const_iterator const_iterator;
			
		public:
			
			~StatementList( void )
			{ clear( ); }
			
		public:
			
			const_iterator begin( void ) const
			{ return mInternalList.begin( ); }
			
			iterator begin( void )
			{ return mInternalList.begin( ); }
			
			const_iterator end( void ) const
			{ return mInternalList.end( ); }
			
			iterator end( void )
			{ return mInternalList.end( ); }
			
		public:
			
			unsigned int size( void ) const
			{ return mInternalList.size( ); }
			
		public:
			
			StatementList & clear( void );
			
		public:
			
			StatementList & merge( Statement * statement );
			
			StatementList & merge( StatementList * other );
			
		public:
			
			std::string toString( void ) const;
			
		private:
			
			InternalList mInternalList;
			
		};
		
	}
	
}
