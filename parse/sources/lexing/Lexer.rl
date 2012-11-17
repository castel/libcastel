#include <cstddef>
#include <memory>
#include <string>
#include <utility>

#include "castel/lexing/Exception.hh"
#include "castel/lexing/Lexeme.hh"
#include "castel/lexing/Lexer.hh"

using namespace castel;
using namespace castel::lexing;

%% machine castellexer;
%% write data;

Lexer::Lexer( char const * p, int n )
    : mP( p )
    , mPe( mP + n )
    , mEof( mPe )
    , mTs( 0 )
    , mTe( 0 )
    , mCs( 0 )
    , mAct( mCs )
    , mLexemeQueue( )
    , mLevelStack( )
    , mPosition( std::make_pair( 1, 1 ) )
{
    mLevelStack.push( 0 );
}

lexing::Lexeme * Lexer::consume( void )
{
    if ( mLexemeQueue.empty( ) ) {
        if ( ! mLevelStack.empty( ) ) {
            this->computeNextLexemes( );
        } else {
            return new lexing::Lexeme( lexing::Lexeme::Type::Invalid, "", std::make_pair( - 1, - 1 ) );
        }
    }

    lexing::Lexeme * front = mLexemeQueue.front( );
    mLexemeQueue.pop( );

    return front;
}

void Lexer::computeNextLexemes( void )
{

    lexing::Lexeme * lexeme;

    std::unique_ptr< lexing::Lexeme > lastNewline;

    while ( true ) {

        lexeme = this->fetchNextLexeme( );

        if ( lexeme->type( ) == lexing::Lexeme::Type::Newline ) {
            lastNewline.reset( lexeme );
        } else {
            break;
        }

    }

    if ( lastNewline.get( ) ) {

        std::string str = lastNewline->as< std::string >( );

        std::size_t start = str.find_first_of( '\t' );
        std::size_t end = str.find_last_of( '\t' );

        unsigned int currentLevel = mLevelStack.top( );
        unsigned int expectedLevel = start != std::string::npos ? 1 + end - start : 0;

        if ( currentLevel == expectedLevel )
            mLexemeQueue.push( lastNewline.release( ) );

        else if ( currentLevel < expectedLevel ) {
            for ( ; currentLevel < expectedLevel; ++ currentLevel ) {
                mLexemeQueue.push( new lexing::Lexeme( lexing::Lexeme::Type::Indent, "", lastNewline->position( ) ) );
            }
        }

        else if ( currentLevel > expectedLevel ) {
            mLexemeQueue.push( new lexing::Lexeme( lexing::Lexeme::Type::Newline, "", lastNewline->position( ) ) );
            for ( ; currentLevel > expectedLevel; -- currentLevel ) {
                mLexemeQueue.push( new lexing::Lexeme( lexing::Lexeme::Type::Dedent, "", lastNewline->position( ) ) );
            }
        }

        mLevelStack.top( ) = currentLevel;

    }

    if ( lexeme->type( ) == lexing::Lexeme::Type::LParenthesis ) {

        mLevelStack.push( mLevelStack.top( ) );

    } else if ( lexeme->type( ) == lexing::Lexeme::Type::RParenthesis || lexeme->type( ) == lexing::Lexeme::Type::End ) {

        unsigned int currentLevel = mLevelStack.top( ); mLevelStack.pop( );
        unsigned int expectedLevel = ! mLevelStack.empty( ) ? mLevelStack.top( ) : 0;

        if ( lexeme->type( ) == lexing::Lexeme::Type::End || currentLevel > expectedLevel ) {
            mLexemeQueue.push( new lexing::Lexeme( lexing::Lexeme::Type::Newline, "", lexeme->position( ) ) );
        }

        for ( int t = currentLevel; t > expectedLevel; -- t ) {
            mLexemeQueue.push( new lexing::Lexeme( lexing::Lexeme::Type::Dedent, "", lexeme->position( ) ) );
        }

    }

    mLexemeQueue.push( lexeme );
}

lexing::Lexeme * Lexer::fetchNextLexeme( void )
{
    %%{

        Undefined                  = 'undefined';
        Protected                  = 'protected';
        Operator                   = 'operator';
        Function                   = 'function';
        Private                    = 'private';
        Require                    = 'require';
        Return                     = 'return';
        Public                     = 'public';
        False                      = 'false';
        Class                      = 'class';
        True                       = 'true';
        Else                       = 'else';
        Dict                       = 'dict';
        List                       = 'list';
        Null                       = 'null';
        New                        = 'new';
        Var                        = 'var';
        And                        = 'and';
        Or                         = 'or';
        As                         = 'as';
        If                         = 'if';

        Incrementation             = '++';
        Decrementation             = '--';

        LesserOrEqual              = '<=';
        GreaterOrEqual             = '>=';
        Lesser                     = '<';
        Greater                    = '>';
        Equal                      = '==';
        NotEqual                   = '!=';

        AdditionAssignment         = '+=';
        SubstractionAssignment     = '-=';
        MultiplicationAssignment   = '*=';
        DivisionAssignment         = '/=';
        ModuloAssignment           = '%=';

        PositiveAddition           = '+';
        NegativeSubstractionHyphen = '-';
        Multiplication             = '*';
        Division                   = '/';
        Modulo                     = '%';

        Assignment                 = '=';

        LParenthesis               = '(';
        RParenthesis               = ')';

        LBracket                   = '[';
        RBracket                   = ']';

        QuestionMark               = '?';
        Colon                      = ':';
        Comma                      = ',';
        Dot                        = '.';
        Quote                      = '\'';

        String                     = '"'([^\"]|'\\' any)*'"';
        Number                     = ('0'[xX][0-9a-fA-F]+|'0'[bB][01]+|[0-9]+('.'[0-9]*)?|[0-9]*'.'[0-9]+);
        Identifier                 = [a-zA-Z]+[0-9a-zA-Z_]*;

        Spaces                     = [ ]+;
        Newline                    = ('\r''\n'|'\r'|'\n')('\t'*);

        main := |*

            Function                   => { type = lexing::Lexeme::Type::Function;                   fbreak; };
            Dict                       => { type = lexing::Lexeme::Type::Dict;                       fbreak; };
            List                       => { type = lexing::Lexeme::Type::List;                       fbreak; };
            Class                      => { type = lexing::Lexeme::Type::Class;                      fbreak; };

            Public                     => { type = lexing::Lexeme::Type::Public;                     fbreak; };
            Protected                  => { type = lexing::Lexeme::Type::Protected;                  fbreak; };
            Private                    => { type = lexing::Lexeme::Type::Private;                    fbreak; };

            Operator                   => { type = lexing::Lexeme::Type::Operator;                   fbreak; };

            Var                        => { type = lexing::Lexeme::Type::Var;                        fbreak; };
            Require                    => { type = lexing::Lexeme::Type::Require;                    fbreak; };
            As                         => { type = lexing::Lexeme::Type::As;                         fbreak; };

            Return                     => { type = lexing::Lexeme::Type::Return;                     fbreak; };

            If                         => { type = lexing::Lexeme::Type::If;                         fbreak; };
            Else                       => { type = lexing::Lexeme::Type::Else;                       fbreak; };

            False                      => { type = lexing::Lexeme::Type::False;                      fbreak; };
            True                       => { type = lexing::Lexeme::Type::True;                       fbreak; };

            Null                       => { type = lexing::Lexeme::Type::Null;                       fbreak; };
            Undefined                  => { type = lexing::Lexeme::Type::Undefined;                  fbreak; };

            And                        => { type = lexing::Lexeme::Type::And;                        fbreak; };
            Or                         => { type = lexing::Lexeme::Type::Or;                         fbreak; };

            New                        => { type = lexing::Lexeme::Type::New;                        fbreak; };

            Incrementation             => { type = lexing::Lexeme::Type::Incrementation;             fbreak; };
            Decrementation             => { type = lexing::Lexeme::Type::Decrementation;             fbreak; };

            LesserOrEqual              => { type = lexing::Lexeme::Type::LesserOrEqual;              fbreak; };
            GreaterOrEqual             => { type = lexing::Lexeme::Type::GreaterOrEqual;             fbreak; };
            Lesser                     => { type = lexing::Lexeme::Type::Lesser;                     fbreak; };
            Greater                    => { type = lexing::Lexeme::Type::Greater;                    fbreak; };
            Equal                      => { type = lexing::Lexeme::Type::Equal;                      fbreak; };
            NotEqual                   => { type = lexing::Lexeme::Type::NotEqual;                   fbreak; };

            AdditionAssignment         => { type = lexing::Lexeme::Type::AdditionAssignment;         fbreak; };
            SubstractionAssignment     => { type = lexing::Lexeme::Type::SubstractionAssignment;     fbreak; };
            MultiplicationAssignment   => { type = lexing::Lexeme::Type::MultiplicationAssignment;   fbreak; };
            DivisionAssignment         => { type = lexing::Lexeme::Type::DivisionAssignment;         fbreak; };
            ModuloAssignment           => { type = lexing::Lexeme::Type::ModuloAssignment;           fbreak; };

            PositiveAddition           => { type = lexing::Lexeme::Type::PositiveAddition;           fbreak; };
            NegativeSubstractionHyphen => { type = lexing::Lexeme::Type::NegativeSubstractionHyphen; fbreak; };
            Multiplication             => { type = lexing::Lexeme::Type::Multiplication;             fbreak; };
            Division                   => { type = lexing::Lexeme::Type::Division;                   fbreak; };
            Modulo                     => { type = lexing::Lexeme::Type::Modulo;                     fbreak; };

            Assignment                 => { type = lexing::Lexeme::Type::Assignment;                 fbreak; };

            LParenthesis               => { type = lexing::Lexeme::Type::LParenthesis;               fbreak; };
            RParenthesis               => { type = lexing::Lexeme::Type::RParenthesis;               fbreak; };

            LBracket                   => { type = lexing::Lexeme::Type::LBracket;                   fbreak; };
            RBracket                   => { type = lexing::Lexeme::Type::RBracket;                   fbreak; };

            QuestionMark               => { type = lexing::Lexeme::Type::QuestionMark;               fbreak; };
            Colon                      => { type = lexing::Lexeme::Type::Colon;                      fbreak; };
            Comma                      => { type = lexing::Lexeme::Type::Comma;                      fbreak; };
            Dot                        => { type = lexing::Lexeme::Type::Dot;                        fbreak; };
            Quote                      => { type = lexing::Lexeme::Type::Quote;                      fbreak; };

            String                     => { type = lexing::Lexeme::Type::String;                     fbreak; };
            Number                     => { type = lexing::Lexeme::Type::Number;                     fbreak; };
            Identifier                 => { type = lexing::Lexeme::Type::Identifier;                 fbreak; };

            Spaces                     => { type = lexing::Lexeme::Type::Spaces;                     fbreak; };
            Newline                    => { type = lexing::Lexeme::Type::Newline;                    fbreak; };

            any                        => {                                                         fbreak; };

        *|;

    }%%;

    lexing::Lexeme::Type type;

    if ( mP == mPe ) {

        mTs = mTe = mP;
        type = lexing::Lexeme::Type::End;

    } else {

        %% variable p   mP   ;
        %% variable pe  mPe  ;
        %% variable eof mEof ;

        %% variable ts  mTs  ;
        %% variable te  mTe  ;

        %% variable cs  mCs  ;
        %% variable act mAct ;

        %% write init;
        %% write exec;

        if ( type == lexing::Lexeme::Type::Invalid ) {
            throw lexing::Exception( "Invalid symbol" );
        }

    }

    unsigned int size = mTe - mTs;

    std::pair< int, int > position = mPosition;

    if ( type == lexing::Lexeme::Type::Newline ) {

        mPosition.second += 1;
        mPosition.first = size;

        if ( size >= 2 && mTs[ 0 ] == '\r' && mTs[ 1 ] == '\n' ) {
            mPosition.first -= 2;
        } else {
            mPosition.first -= 1;
        }

    } else {

        mPosition.first += size;

    }

    return new lexing::Lexeme( type, std::string( mTs, size ), position );
}
