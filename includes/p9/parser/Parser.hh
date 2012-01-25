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
			
			std::string const & errorString( void ) const
			{ return mErrorString; }
			
		public:
			
			ast::Token * exec( void );
			
		protected:
			
			void triggerError( std::string const & message );
			
		private:
			
			lexer::Lexer & mLexer;
			
			std::string mErrorString;
			
			unsigned int mLineNo;
			
		};
		
	}
	
}
