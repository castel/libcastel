#pragma once

#include <cstddef>
#include <utility>

#include "p9/lexer/Lexeme.hh"

namespace p9
{
	
	namespace lexer
	{
		
		class Lexer {
			
		public:
			
			typedef std::pair< unsigned int, unsigned int > Position;
			
		public:
			
			Lexer( char const * p, std::size_t n );
			
		public:
			
			Position const & position( void ) const
			{ return mPosition; }
			
		public:
			
			Lexeme consume( void );
			
		private:
			
			char const * mP;
			char const * mPe;
			char const * mEof;
			
			char const * mTs;
			char const * mTe;
			
			int mCs;
			int mAct;
			
			Position mPosition;
			
		};
		
	}
	
}
