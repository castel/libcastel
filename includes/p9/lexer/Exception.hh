#pragma once

#include "p9/lexer/Lexer.hh"

namespace p9
{
	
	namespace lexer
	{
		
		class Exception {
			
		public:
			
			Exception( Lexer::Position const & position, std::string const & message );
			
		public:
			
			Lexer::Position const & position( void ) const
			{ return mPosition; }
			
			std::string const & message( void ) const
			{ return mMessage; }
			
		private:
			
			Lexer::Position mPosition;
			
			std::string mMessage;
			
		};
		
	}
	
}
