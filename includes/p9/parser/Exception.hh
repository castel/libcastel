#pragma once

#include "p9/lexer/Lexeme.hh"
#include "p9/parser/Parser.hh"

namespace p9
{
	
	namespace parser
	{
		
		class Exception {
			
		public:
			
			Exception( Parser::Position const & position, std::string const & message, lexer::Lexeme * lexeme );
			
		public:
			
			Parser::Position const & position( void ) const
			{ return mPosition; }
			
			std::string const & message( void ) const
			{ return mMessage; }
			
			lexer::Lexeme * lexeme( void ) const
			{ return mLexeme; }
			
		private:
			
			Parser::Position mPosition;
			
			std::string mMessage;
			
			lexer::Lexeme * mLexeme;
			
		};
		
	}
	
}
