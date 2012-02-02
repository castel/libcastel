#pragma once

#include <string>

namespace p9
{
	
	namespace lexer
	{
		
		class Lexeme {
			
		public:
			
			Lexeme( void )
			: _type( 0 )
			{
			}
			
			Lexeme( int type, char const * s, std::size_t n )
			: _type( type )
			, _text( s, n )
			{
			}
			
		public:
			
			bool eof( void ) const
			{
				return _type == 0;
			}
			
		public:
			
			int type( void ) const
			{
				return _type;
			}
			
			std::string const & text( void ) const
			{
				return _text;
			}
			
		private:
			
			int _type;
			
			std::string _text;
			
		};
		
	}
	
}
