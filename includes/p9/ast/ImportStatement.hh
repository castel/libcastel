#pragma once

#include <string>

#include "p9/ast/Statement.hh"

namespace p9
{
	
	namespace ast
	{
		
		class FromClause;
		
		class AsClause;
		
		class Identifier;
		
		class ImportStatement : public Statement {
			
		public:
			
			ImportStatement & setFromClause( FromClause * fromClause )
			{ mFromClause = fromClause; return * this; }
			
			ImportStatement & setAsClause( AsClause * asClause )
			{ mAsClause = asClause; return * this; }
			
			ImportStatement & setLabel( Identifier * label )
			{ mLabel = label; return * this; }
			
		public:
			
			FromClause * fromClause( void ) const
			{ return mFromClause; }
			
			AsClause * asClause( void ) const
			{ return mAsClause; }
			
			Identifier * label( void ) const
			{ return mLabel; }
			
		public:
			
			std::string toString( void ) const;
			
		private:
			
			FromClause * mFromClause;
			
			AsClause * mAsClause;
			
			Identifier * mLabel;
			
		};
		
	}
	
}
