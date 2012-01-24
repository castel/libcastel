#pragma once

#include <string>

namespace p9
{
	
	namespace lexer
	{
		
		class Lexeme {
			
		public:
			
			static Lexeme const endOfFile;
			
			static Lexeme const invalid;
			
		public:
			
			Lexeme( void )
			: _type( 0 )
			{
			}
			
			Lexeme( int type )
			: _type( type )
			{
			}
			
			Lexeme( int type, char const * s, std::size_t n )
			: _type( type )
			, _value( s, n )
			{
			}
			
		public:
			
			bool valid( void ) const
			{
				return _type != 0;
			}
			
		public:
			
			operator int( void ) const
			{
				return _type;
			}
			
		public:
			
			std::string const & value( void ) const
			{
				return _value;
			}
			
		private:
			
			int _type;
			
			std::string _value;
			
		};
		
	}
	
}
