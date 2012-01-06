#pragma once

namespace p9
{
	
	namespace lexer
	{
		
		class Lexer;
		
	}
	
	namespace parser
	{
		
		class Parser {
			
		public:
			
			Parser( lexer::Lexer & lexer );
			
			~Parser( void );
			
		public:
			
			bool exec( void ) const;
			
		private:
			
			void * _lparse;
			
			lexer::Lexer & _lexer;
			
		};
		
	}
	
}
