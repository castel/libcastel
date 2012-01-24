#pragma once

#include <cstddef>

#include "p9/lexer/Lexeme.hh"

namespace p9
{
	
	namespace lexer
	{
		
		class Lexer {
			
		public:
			
			Lexer( char const * p, std::size_t n );
			
		public:
			
			Lexeme consume( void );
			
		private:
			
			char const * _p;
			char const * _pe;
			char const * _eof;
			
			char const * _ts;
			char const * _te;
			
			int _cs;
			int _act;
			
		};
		
	}
	
}
