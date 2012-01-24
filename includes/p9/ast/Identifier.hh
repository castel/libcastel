#pragma once

#include <string>

#include "p9/ast/Token.hh"

namespace p9
{
	
	namespace ast
	{
		
		class Identifier : public Token {
			
		public:
			
			Identifier & setIdentifier( std::string const & identifier )
			{ mIdentifier = identifier; return * this; }
			
		public:
			
			std::string const & identifier( void ) const
			{ return mIdentifier; }
			
		public:
			
			std::string toString( void ) const;
			
		private:
			
			std::string mIdentifier;
			
		};
		
	}
	
}
