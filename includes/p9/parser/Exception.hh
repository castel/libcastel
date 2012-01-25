#pragma once

#include "p9/parser/Parser.hh"

namespace p9
{
	
	namespace parser
	{
		
		class Exception {
			
		public:
			
			Exception( Parser::Position const & position, std::string const & message );
			
		public:
			
			Parser::Position const & position( void ) const
			{ return mPosition; }
			
			std::string const & message( void ) const
			{ return mMessage; }
			
		private:
			
			Parser::Position mPosition;
			
			std::string mMessage;
			
		};
		
	}
	
}
