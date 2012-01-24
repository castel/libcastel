#pragma once

#include <string>

namespace p9
{
	
	namespace lexer
	{
		
		class Lexer;
		
	}
	
	namespace ast
	{
		
		class Token;
		
	}
	
	namespace parser
	{
		
		class Parser {
			
		public:
			
			Parser( lexer::Lexer & lexer );
			
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
