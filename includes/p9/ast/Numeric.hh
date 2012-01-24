#pragma once

#include <string>

#include "p9/ast/Token.hh"

namespace p9
{
	
	namespace ast
	{
		
		class Numeric {
			
		public:
			
			static Numeric fromString( std::string const & str );
			
		public:
			
			Numeric & setNumeric( double numeric )
			{ mNumeric = numeric; return * this; }
			
		public:
			
			double numeric( void ) const
			{ return mNumeric; }
			
		public:
			
			std::string toString( void ) const;
			
		private:
			
			double mNumeric;
			
		};
		
	}
	
}
