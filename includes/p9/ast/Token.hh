#pragma once

#include <string>

namespace p9
{
	
	namespace ast
	{
		
		class Token {
			
		public:
			
			static void deleter( Token * token )
			{ delete token; }
			
		public:
			
			virtual ~Token( void ) { }
			
		public:
			
			virtual std::string toString( void ) const = 0;
			
		};
		
	}
	
}
