#pragma once

#include <string>

#include "p9/lexer/Lexer.hh"

namespace p9
{
	
	namespace ast
	{
		
		class Token;
		
	}
	
	namespace parser
	{
		
		class Parser {
			
		public:
			
			typedef lexer::Lexer::Position Position;
			
		public:
			
			Parser( lexer::Lexer & lexer );
			
		public:
			
			Position const & position( void ) const
			{ return mLexer.position( ); }
			
		public:
			
			ast::Token * exec( void );
			
		private:
			
			lexer::Lexer & mLexer;
			
			std::string mErrorString;
			
			unsigned int mLineNo;
			
		};
		
	}
	
}
