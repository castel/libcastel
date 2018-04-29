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
    , mPosition( std::make_pair( 1, 1 ) )
{
}

lex::Lexeme * Lexer::consume( void )
{
    return this->fetchNextLexeme( );
}

lex::Lexeme * Lexer::fetchNextLexeme( void )
{
    %%{

        Constructor                = 'constructor';
        Undefined                  = 'undefined';
        Protected                  = 'protected';
        Extending                  = 'extending';
        Operator                   = 'operator';
        Function                   = 'function';
        Private                    = 'private';
        Require                    = 'require';
        Extern                     = 'extern';
        Return                     = 'return';
        Public                     = 'public';
        Throw                      = 'throw';
        False                      = 'false';
        Class                      = 'class';
        While                      = 'while';
        Until                      = 'until';
        True                       = 'true';
        Else                       = 'else';
        Null                       = 'null';
        Try                        = 'try';
        New                        = 'new';
        For                        = 'for';
        Let                        = 'let';
        If                         = 'if';
        In                         = 'in';

        Incrementation             = '++';
        Decrementation             = '--';
        Equal                      = '==';
        NotEqual                   = '!=';
        LesserOrEqual              = '<=';
        GreaterOrEqual             = '>=';
        AdditionAssignment         = '+=';
        SubstractionAssignment     = '-=';
        MultiplicationAssignment   = '*=';
        DivisionAssignment         = '/=';
        ModuloAssignment           = '%=';

        Lesser                     = '<';
        Greater                    = '>';
        Plus                       = '+';
        Minus                      = '-';
        Multiplication             = '*';
        Division                   = '/';
        Modulo                     = '%';
        Assignment                 = '=';

        LParenthesis               = '(';
        RParenthesis               = ')';

        LBracket                   = '[';
        RBracket                   = ']';

        DLBrace                    = '{{';
        DRBrace                    = '}}';

        LBrace                     = '{';
        RBrace                     = '}';

        QuestionMark               = '?';
        Colon                      = ':';
        Comma                      = ',';
        Dot                        = '.';
        Semicolon                  = ';';

        Quote                      = '\'';

        String                     = '"'([^\"]|'\\' any)*'"';
        Number                     = ('0'[xX][0-9a-fA-F]+|'0'[bB][01]+|'0'[0-9]*|[1-9][0-9]*('.'[0-9]*)?|[0-9]*'.'[0-9]+);
        Identifier                 = [a-zA-Z][0-9a-zA-Z_]*;

        Spaces                     = (' '|'\t')+;
        Newline                    = ('\r''\n'|'\r'|'\n');

        main := |*

            False                      => { type = lex::Lexeme::Type::False;                      fbreak; };
            True                       => { type = lex::Lexeme::Type::True;                       fbreak; };

            Null                       => { type = lex::Lexeme::Type::Null;                       fbreak; };
            Undefined                  => { type = lex::Lexeme::Type::Undefined;                  fbreak; };

            Function                   => { type = lex::Lexeme::Type::Function;                   fbreak; };

            Class                      => { type = lex::Lexeme::Type::Class;                      fbreak; };
            Extending                  => { type = lex::Lexeme::Type::Extending;                  fbreak; };
            Public                     => { type = lex::Lexeme::Type::Public;                     fbreak; };
            Protected                  => { type = lex::Lexeme::Type::Protected;                  fbreak; };
            Private                    => { type = lex::Lexeme::Type::Private;                    fbreak; };
            Constructor                => { type = lex::Lexeme::Type::Constructor;                fbreak; };
            Operator                   => { type = lex::Lexeme::Type::Operator;                   fbreak; };

            If                         => { type = lex::Lexeme::Type::If;                         fbreak; };
            While                      => { type = lex::Lexeme::Type::While;                      fbreak; };
            Until                      => { type = lex::Lexeme::Type::Until;                      fbreak; };
            For                        => { type = lex::Lexeme::Type::For;                        fbreak; };
            In                         => { type = lex::Lexeme::Type::In;                         fbreak; };
            Try                        => { type = lex::Lexeme::Type::Try;                        fbreak; };
            Else                       => { type = lex::Lexeme::Type::Else;                       fbreak; };

            Let                        => { type = lex::Lexeme::Type::Let;                        fbreak; };

            Return                     => { type = lex::Lexeme::Type::Return;                     fbreak; };
            Throw                      => { type = lex::Lexeme::Type::Throw;                      fbreak; };

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

            Plus                       => { type = lex::Lexeme::Type::Plus;                       fbreak; };
            Minus                      => { type = lex::Lexeme::Type::Minus;                      fbreak; };
            Multiplication             => { type = lex::Lexeme::Type::Multiplication;             fbreak; };
            Division                   => { type = lex::Lexeme::Type::Division;                   fbreak; };
            Modulo                     => { type = lex::Lexeme::Type::Modulo;                     fbreak; };

            Assignment                 => { type = lex::Lexeme::Type::Assignment;                 fbreak; };

            LParenthesis               => { type = lex::Lexeme::Type::LParenthesis;               fbreak; };
            RParenthesis               => { type = lex::Lexeme::Type::RParenthesis;               fbreak; };

            LBracket                   => { type = lex::Lexeme::Type::LBracket;                   fbreak; };
            RBracket                   => { type = lex::Lexeme::Type::RBracket;                   fbreak; };

            DLBrace                    => { type = lex::Lexeme::Type::DLBrace;                    fbreak; };
            DRBrace                    => { type = lex::Lexeme::Type::DRBrace;                    fbreak; };

            LBrace                     => { type = lex::Lexeme::Type::LBrace;                     fbreak; };
            RBrace                     => { type = lex::Lexeme::Type::RBrace;                     fbreak; };

            QuestionMark               => { type = lex::Lexeme::Type::QuestionMark;               fbreak; };
            Colon                      => { type = lex::Lexeme::Type::Colon;                      fbreak; };
            Comma                      => { type = lex::Lexeme::Type::Comma;                      fbreak; };
            Dot                        => { type = lex::Lexeme::Type::Dot;                        fbreak; };
            Semicolon                  => { type = lex::Lexeme::Type::Semicolon;                  fbreak; };

            String                     => { type = lex::Lexeme::Type::String;                     fbreak; };
            Number                     => { type = lex::Lexeme::Type::Number;                     fbreak; };
            Extern                     => { type = lex::Lexeme::Type::Extern;                     fbreak; };
            Identifier                 => { type = lex::Lexeme::Type::Identifier;                 fbreak; };
            Require                    => { type = lex::Lexeme::Type::Require;                    fbreak; };

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
