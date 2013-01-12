#pragma once

#include <queue>
#include <stack>
#include <utility>

#include "castel/lex/Lexeme.hh"

namespace castel
{

    namespace lex
    {

        class Lexer
        {

        public:

            Lexer( char const * p, int n );

        public:

            lex::Lexeme * consume( void );

        private:

            void computeNextLexemes( void );

            lex::Lexeme * fetchNextLexeme( void );

        private:

            std::queue< lex::Lexeme * > mLexemeQueue;

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
