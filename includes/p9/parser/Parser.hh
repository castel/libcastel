#pragma once

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
			
			~Parser( void );
			
		public:
			
			ast::Token * exec( void );
			
		private:
			
			void * _lparse;
			
			lexer::Lexer & _lexer;
			
		};
		
	}
	
}
