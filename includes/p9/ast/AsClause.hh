#pragma once

#include <string>

#include "p9/ast/Token.hh"

namespace p9
{
	
	namespace ast
	{
		
		class Identifier;
		
		class AsClause : public Token {
			
		public:
			
			AsClause & setTarget( Identifier * target )
			{ mTarget = target; return * this; }
			
		public:
			
			Identifier * target( void ) const
			{ return mTarget; }
			
		public:
			
			std::string toString( void ) const;
			
		private:
			
			Identifier * mTarget;
			
		};
		
	}
	
}
