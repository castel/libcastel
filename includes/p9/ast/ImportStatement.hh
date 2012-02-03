#pragma once

#include <list>
#include <string>
#include <memory>

#include "p9/ast/Statement.hh"

namespace p9
{
	
	namespace ast
	{
		
		class ImportStatement : public Statement {
			
		public:
			
			ImportStatement & setFromClause( std::list< std::string > * fromClause )
			{ mFromClause.reset( fromClause ); return * this; }
			
			ImportStatement & setImportClause( std::string * importClause )
			{ mImportClause.reset( importClause ); return * this; }
			
			ImportStatement & setAsClause( std::string * asClause )
			{ mAsClause.reset( asClause ); return * this; }
			
		public:
			
			std::list< std::string > * fromClause( void ) const
			{ return mFromClause.get( ); }
			
			std::string * importClause( void ) const
			{ return mImportClause.get( ); }
			
			std::string * asClause( void ) const
			{ return mAsClause.get( ); }
			
		public:
			
			std::string toString( void ) const;
			
		private:
			
			std::auto_ptr< std::list< std::string > > mFromClause;
			
			std::auto_ptr< std::string > mImportClause;
			
			std::auto_ptr< std::string > mAsClause;
			
		};
		
	}
	
}
