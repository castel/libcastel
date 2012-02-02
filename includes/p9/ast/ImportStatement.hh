#pragma once

#include <list>
#include <string>

#include "p9/ast/Statement.hh"

namespace p9
{
	
	namespace ast
	{
		
		class ImportStatement : public Statement {
			
		public:
			
			ImportStatement & setFromClause( std::list< std::string > * fromClause )
			{ mFromClause = fromClause; return * this; }
			
			ImportStatement & setImportClause( std::string * importClause )
			{ mImportClause = importClause; return * this; }
			
			ImportStatement & setAsClause( std::string * asClause )
			{ mAsClause = asClause; return * this; }
			
		public:
			
			std::list< std::string > * fromClause( void ) const
			{ return mFromClause; }
			
			std::string * importClause( void ) const
			{ return mImportClause; }
			
			std::string * asClause( void ) const
			{ return mAsClause; }
			
		public:
			
			std::string toString( void ) const;
			
		private:
			
			std::list< std::string > * mFromClause;
			
			std::string * mImportClause;
			
			std::string * mAsClause;
			
		};
		
	}
	
}
