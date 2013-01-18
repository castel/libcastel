#include <cstddef>
#include <memory>
#include <string>
#include <utility>

#include "castel/lex/Exception.hh"
#include "castel/lex/Lexeme.hh"
#include "castel/lex/Lexer.hh"

using namespace castel;
using namespace castel::lex;

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

lex::Lexeme * Lexer::consume( void )
{
    if ( mLexemeQueue.empty( ) ) {
        if ( ! mLevelStack.empty( ) ) {
            this->computeNextLexemes( );
        } else {
            return new lex::Lexeme( lex::Lexeme::Type::Invalid, "", std::make_pair( - 1, - 1 ) );
        }
    }

    lex::Lexeme * front = mLexemeQueue.front( );
    mLexemeQueue.pop( );

    return front;
}

void Lexer::computeNextLexemes( void )
{

    lex::Lexeme * lexeme;

    std::unique_ptr< lex::Lexeme > lastNewline;

    while ( true ) {

        lexeme = this->fetchNextLexeme( );

        if ( lexeme->type( ) == lex::Lexeme::Type::Newline ) {
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
                mLexemeQueue.push( new lex::Lexeme( lex::Lexeme::Type::Indent, "", lastNewline->position( ) ) );
            }
        }

        else if ( currentLevel > expectedLevel ) {
            mLexemeQueue.push( new lex::Lexeme( lex::Lexeme::Type::Newline, "", lastNewline->position( ) ) );
            for ( ; currentLevel > expectedLevel; -- currentLevel ) {
                mLexemeQueue.push( new lex::Lexeme( lex::Lexeme::Type::Dedent, "", lastNewline->position( ) ) );
            }
        }

        mLevelStack.top( ) = currentLevel;

    }

    if ( lexeme->type( ) == lex::Lexeme::Type::LParenthesis ) {

        mLevelStack.push( mLevelStack.top( ) );

    } else if ( lexeme->type( ) == lex::Lexeme::Type::RParenthesis || lexeme->type( ) == lex::Lexeme::Type::End ) {

        unsigned int currentLevel = mLevelStack.top( ); mLevelStack.pop( );
        unsigned int expectedLevel = ! mLevelStack.empty( ) ? mLevelStack.top( ) : 0;

        if ( lexeme->type( ) == lex::Lexeme::Type::End || currentLevel > expectedLevel ) {
            mLexemeQueue.push( new lex::Lexeme( lex::Lexeme::Type::Newline, "", lexeme->position( ) ) );
        }

        for ( int t = currentLevel; t > expectedLevel; -- t ) {
            mLexemeQueue.push( new lex::Lexeme( lex::Lexeme::Type::Dedent, "", lexeme->position( ) ) );
        }

    }

    mLexemeQueue.push( lexeme );
}

lex::Lexeme * Lexer::fetchNextLexeme( void )
{
    %%{

        Undefined                  = 'undefined';
        Protected                  = 'protected';
        Extending                  = 'extending';
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
        External                   = '%'[a-zA-Z][0-9a-zA-Z_]*;
        Identifier                 = [a-zA-Z][0-9a-zA-Z_]*;

        Spaces                     = [ ]+;
        Newline                    = ('\r''\n'|'\r'|'\n')('\t'*);

        main := |*

            Function                   => { type = lex::Lexeme::Type::Function;                   fbreak; };
            Dict                       => { type = lex::Lexeme::Type::Dict;                       fbreak; };
            List                       => { type = lex::Lexeme::Type::List;                       fbreak; };
            Class                      => { type = lex::Lexeme::Type::Class;                      fbreak; };

            Extending                  => { type = lex::Lexeme::Type::Extending;                  fbreak; };

            Public                     => { type = lex::Lexeme::Type::Public;                     fbreak; };
            Protected                  => { type = lex::Lexeme::Type::Protected;                  fbreak; };
            Private                    => { type = lex::Lexeme::Type::Private;                    fbreak; };

            Operator                   => { type = lex::Lexeme::Type::Operator;                   fbreak; };

            Var                        => { type = lex::Lexeme::Type::Var;                        fbreak; };
            Require                    => { type = lex::Lexeme::Type::Require;                    fbreak; };
            As                         => { type = lex::Lexeme::Type::As;                         fbreak; };

            Return                     => { type = lex::Lexeme::Type::Return;                     fbreak; };

            If                         => { type = lex::Lexeme::Type::If;                         fbreak; };
            Else                       => { type = lex::Lexeme::Type::Else;                       fbreak; };

            False                      => { type = lex::Lexeme::Type::False;                      fbreak; };
            True                       => { type = lex::Lexeme::Type::True;                       fbreak; };

            Null                       => { type = lex::Lexeme::Type::Null;                       fbreak; };
            Undefined                  => { type = lex::Lexeme::Type::Undefined;                  fbreak; };

            And                        => { type = lex::Lexeme::Type::And;                        fbreak; };
            Or                         => { type = lex::Lexeme::Type::Or;                         fbreak; };

            New                        => { type = lex::Lexeme::Type::New;                        fbreak; };

            Incrementation             => { type = lex::Lexeme::Type::Incrementation;             fbreak; };
            Decrementation             => { type = lex::Lexeme::Type::Decrementation;             fbreak; };

            LesserOrEqual              => { type = lex::Lexeme::Type::LesserOrEqual;              fbreak; };
            GreaterOrEqual             => { type = lex::Lexeme::Type::GreaterOrEqual;             fbreak; };
            Lesser                     => { type = lex::Lexeme::Type::Lesser;                     fbreak; };
            Greater                    => { type = lex::Lexeme::Type::Greater;                    fbreak; };
            Equal                      => { type = lex::Lexeme::Type::Equal;                      fbreak; };
            NotEqual                   => { type = lex::Lexeme::Type::NotEqual;                   fbreak; };

            AdditionAssignment         => { type = lex::Lexeme::Type::AdditionAssignment;         fbreak; };
            SubstractionAssignment     => { type = lex::Lexeme::Type::SubstractionAssignment;     fbreak; };
            MultiplicationAssignment   => { type = lex::Lexeme::Type::MultiplicationAssignment;   fbreak; };
            DivisionAssignment         => { type = lex::Lexeme::Type::DivisionAssignment;         fbreak; };
            ModuloAssignment           => { type = lex::Lexeme::Type::ModuloAssignment;           fbreak; };

            PositiveAddition           => { type = lex::Lexeme::Type::PositiveAddition;           fbreak; };
            NegativeSubstractionHyphen => { type = lex::Lexeme::Type::NegativeSubstractionHyphen; fbreak; };
            Multiplication             => { type = lex::Lexeme::Type::Multiplication;             fbreak; };
            Division                   => { type = lex::Lexeme::Type::Division;                   fbreak; };
            Modulo                     => { type = lex::Lexeme::Type::Modulo;                     fbreak; };

            Assignment                 => { type = lex::Lexeme::Type::Assignment;                 fbreak; };

            LParenthesis               => { type = lex::Lexeme::Type::LParenthesis;               fbreak; };
            RParenthesis               => { type = lex::Lexeme::Type::RParenthesis;               fbreak; };

            LBracket                   => { type = lex::Lexeme::Type::LBracket;                   fbreak; };
            RBracket                   => { type = lex::Lexeme::Type::RBracket;                   fbreak; };

            QuestionMark               => { type = lex::Lexeme::Type::QuestionMark;               fbreak; };
            Colon                      => { type = lex::Lexeme::Type::Colon;                      fbreak; };
            Comma                      => { type = lex::Lexeme::Type::Comma;                      fbreak; };
            Dot                        => { type = lex::Lexeme::Type::Dot;                        fbreak; };
            Quote                      => { type = lex::Lexeme::Type::Quote;                      fbreak; };

            String                     => { type = lex::Lexeme::Type::String;                     fbreak; };
            Number                     => { type = lex::Lexeme::Type::Number;                     fbreak; };
            External                   => { type = lex::Lexeme::Type::External;                   fbreak; };
            Identifier                 => { type = lex::Lexeme::Type::Identifier;                 fbreak; };

            Spaces                     => { type = lex::Lexeme::Type::Spaces;                     fbreak; };
            Newline                    => { type = lex::Lexeme::Type::Newline;                    fbreak; };

            any                        => {                                                       fbreak; };

        *|;

    }%%;

    lex::Lexeme::Type type;

    if ( mP == mPe ) {

        mTs = mTe = mP;
        type = lex::Lexeme::Type::End;

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

        if ( type == lex::Lexeme::Type::Invalid ) {
            throw lex::Exception( "Invalid symbol" );
        }

    }

    unsigned int size = mTe - mTs;

    std::pair< int, int > position = mPosition;

    if ( type == lex::Lexeme::Type::Newline ) {

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

    return new lex::Lexeme( type, std::string( mTs, size ), position );
}
