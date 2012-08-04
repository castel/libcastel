#pragma once

#include <cstddef>
#include <memory>
#include <queue>
#include <stack>

#include "castel/lexer/Lexeme.hh"
#include "castel/lexer/Position.hh"

namespace castel
{

    namespace lexer
    {

        class Lexer
        {

        public:

            Lexer( char const * p, std::size_t n );

        public:

            lexer::Lexeme * consume( void );

        private:

            void computeNextLexemes( void );
            lexer::Lexeme * fetchNextLexeme( void );

        private:

            char const * mP;
            char const * mPe;
            char const * mEof;

            char const * mTs;
            char const * mTe;

            int mCs;
            int mAct;

        private:

            std::queue< Lexeme * > mLexemeQueue;
            std::stack< unsigned int > mLevelStack;

            lexer::Position mPosition;

        };

    }

}
