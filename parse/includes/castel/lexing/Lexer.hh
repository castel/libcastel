#pragma once

#include <queue>
#include <stack>
#include <utility>

#include "castel/lexing/Lexeme.hh"

namespace castel
{

    namespace lexing
    {

        class Lexer
        {

        public:

            Lexer( char const * p, int n );

        public:

            lexing::Lexeme * consume( void );

        private:

            void computeNextLexemes( void );

            lexing::Lexeme * fetchNextLexeme( void );

        private:

            std::queue< lexing::Lexeme * > mLexemeQueue;

            std::stack< unsigned int > mLevelStack;

            std::pair< int, int > mPosition;

        private:

            char const * mP;

            char const * mPe;

            char const * mEof;

            char const * mTs;

            char const * mTe;

            int mCs;

            int mAct;

        };

    }

}
