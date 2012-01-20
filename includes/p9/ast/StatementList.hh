#pragma once

#include <list>

#include "p9/ast/Token.hh"

namespace p9
{
	
	namespace ast
	{
		
		class Statement;
		
		class StatementList : public Token {
			
		public:
			
			StatementList( void );
			
		public:
			
			StatementList & merge( Statement * );
			
			StatementList & merge( StatementList * );
			
		private:
			
			std::list< Statement * > mStlList;
			
		};
		
	}
	
}
