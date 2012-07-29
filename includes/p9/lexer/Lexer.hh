#pragma once

#include <cstddef>
#include <memory>
#include <queue>
#include <stack>

#include "p9/lexer/Lexeme.hh"
#include "p9/lexer/Position.hh"

namespace p9
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
