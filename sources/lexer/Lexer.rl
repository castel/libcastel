#include "castel/lexer/Exception.hh"
#include "castel/lexer/Lexeme.hh"
#include "castel/lexer/Lexer.hh"

using namespace castel;
using namespace castel::lexer;

%% machine castellexer;
%% write data;

Lexer::Lexer       ( char const * p, std::size_t n )
    : mP           ( p      )
    , mPe          ( mP + n )
    , mEof         ( mPe    )
    , mTs          ( 0      )
    , mTe          ( 0      )
    , mCs          ( 0      )
    , mAct         ( mCs    )
    , mLexemeQueue (        )
    , mLevelStack  (        )
    , mPosition    ( 1, 1   )
{
    mLevelStack.push( 0 );
}

Lexeme * Lexer::consume( void )
{
    if ( mLexemeQueue.empty( ) ) {
        if ( ! mLevelStack.empty( ) ) {
            this->computeNextLexemes( );
        } else {
            return new lexer::Lexeme( lexer::Lexeme::Type::Invalid );
        }
    }

    lexer::Lexeme * front = mLexemeQueue.front( );
    mLexemeQueue.pop( );

    return front;
}

void Lexer::computeNextLexemes( void )
{

    lexer::Lexeme * lexeme;

    // Si le lexème est une nouvelle ligne, on l'enregistre puis on
    // vérifie le type du lexème suivant

    std::unique_ptr< lexer::Lexeme > lastNewline;

    while ( true ) {

        lexeme = this->fetchNextLexeme( );

        if ( lexeme->type( ) == lexer::Lexeme::Type::Newline ) {
            lastNewline.reset( lexeme );
        } else {
            break;
        }

    }

    // Si le lexème n'est pas une nouvelle ligne et qu'une nouvelle ligne
    // a déjà été trouvée, nous générons les incrémentations ou décrémentations
    // qui s'imposent

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
                mLexemeQueue.push( new lexer::Lexeme( lexer::Lexeme::Type::Indent, lastNewline->position( ) ) );
            }
        }

        else if ( currentLevel > expectedLevel ) {
            mLexemeQueue.push( new lexer::Lexeme( lexer::Lexeme::Type::Newline, lastNewline->position( ) ) );
            for ( ; currentLevel > expectedLevel; -- currentLevel ) {
                mLexemeQueue.push( new lexer::Lexeme( lexer::Lexeme::Type::Dedent, lastNewline->position( ) ) );
            }
        }

        mLevelStack.top( ) = currentLevel;

    }

    //

    if ( lexeme->type( ) == lexer::Lexeme::Type::LParenthesis ) {

        mLevelStack.push( mLevelStack.top( ) );

    } else if ( lexeme->type( ) == lexer::Lexeme::Type::RParenthesis || lexeme->type( ) == lexer::Lexeme::Type::End ) {

        unsigned int currentLevel = mLevelStack.top( ); mLevelStack.pop( );
        unsigned int expectedLevel = ! mLevelStack.empty( ) ? mLevelStack.top( ) : 0;

        if ( lexeme->type( ) == lexer::Lexeme::Type::End || currentLevel > expectedLevel ) {
            mLexemeQueue.push( new lexer::Lexeme( lexer::Lexeme::Type::Newline, lexeme->position( ) ) );
        }

        for ( int t = currentLevel; t > expectedLevel; -- t ) {
            mLexemeQueue.push( new lexer::Lexeme( lexer::Lexeme::Type::Dedent, lexeme->position( ) ) );
        }

    }

    // Pas de comportement spécial relatif à l'offside rule, nous pouvons
    // renvoyer le lexème généré.

    mLexemeQueue.push( lexeme );
}

lexer::Lexeme * Lexer::fetchNextLexeme( void )
{
    %%{

        Function                   = 'function';
        Dict                       = 'dict';
        List                       = 'list';

        Return                     = 'return';
        Var                        = 'var';
        If                         = 'if';
        Else                       = 'else';

        False                      = 'false';
        True                       = 'true';

        Null                       = 'null';
        Undefined                  = 'undefined';

        And                        = 'and';
        Or                         = 'or';

        Incrementation             = '++';
        Decrementation             = '--';

        LesserOrEqual              = '<=';
        GreaterOrEqual             = '>=';
        Lesser                     = '<';
        Greater                    = '>';

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

        Colon                      = ':';
        Comma                      = ',';

        String                     = '"'([^\"]|'\\' any)*'"';
        Number                     = ('0'[xX][0-9a-fA-F]+|'0'[bB][01]+|[0-9]+('.'[0-9]*)?|[0-9]*'.'[0-9]+);
        Identifier                 = [a-zA-Z]+[0-9a-zA-Z_]*;

        Spaces                     = [ ]+;
        Newline                    = ('\r''\n'|'\r'|'\n')('\t'*);

        main := |*

            Function                   => { type = lexer::Lexeme::Type::Function;                   fbreak; };
            Dict                       => { type = lexer::Lexeme::Type::Dict;                       fbreak; };
            List                       => { type = lexer::Lexeme::Type::List;                       fbreak; };

            Return                     => { type = lexer::Lexeme::Type::Return;                     fbreak; };
            Var                        => { type = lexer::Lexeme::Type::Var;                        fbreak; };
            If                         => { type = lexer::Lexeme::Type::If;                         fbreak; };
            Else                       => { type = lexer::Lexeme::Type::Else;                       fbreak; };

            False                      => { type = lexer::Lexeme::Type::False;                      fbreak; };
            True                       => { type = lexer::Lexeme::Type::True;                       fbreak; };

            Null                       => { type = lexer::Lexeme::Type::Null;                       fbreak; };
            Undefined                  => { type = lexer::Lexeme::Type::Undefined;                  fbreak; };

            And                        => { type = lexer::Lexeme::Type::And;                        fbreak; };
            Or                         => { type = lexer::Lexeme::Type::Or;                         fbreak; };

            Incrementation             => { type = lexer::Lexeme::Type::Incrementation;             fbreak; };
            Decrementation             => { type = lexer::Lexeme::Type::Decrementation;             fbreak; };

            LesserOrEqual              => { type = lexer::Lexeme::Type::LesserOrEqual;              fbreak; };
            GreaterOrEqual             => { type = lexer::Lexeme::Type::GreaterOrEqual;             fbreak; };
            Lesser                     => { type = lexer::Lexeme::Type::Lesser;                     fbreak; };
            Greater                    => { type = lexer::Lexeme::Type::Greater;                    fbreak; };

            AdditionAssignment         => { type = lexer::Lexeme::Type::AdditionAssignment;         fbreak; };
            SubstractionAssignment     => { type = lexer::Lexeme::Type::SubstractionAssignment;     fbreak; };
            MultiplicationAssignment   => { type = lexer::Lexeme::Type::MultiplicationAssignment;   fbreak; };
            DivisionAssignment         => { type = lexer::Lexeme::Type::DivisionAssignment;         fbreak; };
            ModuloAssignment           => { type = lexer::Lexeme::Type::ModuloAssignment;           fbreak; };

            PositiveAddition           => { type = lexer::Lexeme::Type::PositiveAddition;           fbreak; };
            NegativeSubstractionHyphen => { type = lexer::Lexeme::Type::NegativeSubstractionHyphen; fbreak; };
            Multiplication             => { type = lexer::Lexeme::Type::Multiplication;             fbreak; };
            Division                   => { type = lexer::Lexeme::Type::Division;                   fbreak; };
            Modulo                     => { type = lexer::Lexeme::Type::Modulo;                     fbreak; };

            Assignment                 => { type = lexer::Lexeme::Type::Assignment;                 fbreak; };

            LParenthesis               => { type = lexer::Lexeme::Type::LParenthesis;               fbreak; };
            RParenthesis               => { type = lexer::Lexeme::Type::RParenthesis;               fbreak; };

            Colon                      => { type = lexer::Lexeme::Type::Colon;                      fbreak; };
            Comma                      => { type = lexer::Lexeme::Type::Comma;                      fbreak; };

            String                     => { type = lexer::Lexeme::Type::String;                     fbreak; };
            Number                     => { type = lexer::Lexeme::Type::Number;                     fbreak; };
            Identifier                 => { type = lexer::Lexeme::Type::Identifier;                 fbreak; };

            Spaces                     => { type = lexer::Lexeme::Type::Spaces;                     fbreak; };
            Newline                    => { type = lexer::Lexeme::Type::Newline;                    fbreak; };

            any                        => {                                                         fbreak; };

        *|;

    }%%;

    // Variable qui contiendra le type du lexème à la fin de l'itération

    lexer::Lexeme::Type type;

    if ( mP == mPe ) {

        // Nous avons atteint la fin du flux, le lexème est donc de type EOF

        mTs = mTe = mP;
        type = lexer::Lexeme::Type::End;

    } else {

        // Nommage des diverses variables de Ragel. Nous utilisons
        // des variables membres afin de conserver l'état de la machine
        // entre les différents appels à la méthode

        %% variable p   mP   ;
        %% variable pe  mPe  ;
        %% variable eof mEof ;

        %% variable ts  mTs  ;
        %% variable te  mTe  ;

        %% variable cs  mCs  ;
        %% variable act mAct ;

        // Déclenchement de la machine du lexer afin de connaitre le type du lexème

        %% write init;
        %% write exec;

        // Si le symbole est inconnu, on jette une exception

        if ( type == lexer::Lexeme::Type::Invalid ) {
            throw lexer::Exception( "Invalid symbol" );
        }

    }

    // Calcul de la taille total du texte contenu dans le lexème

    unsigned int size = mTe - mTs;

    // Modification de la position interne de la machine. N'est
    // utilisé qu'à des fins informatives (par exemple en cas d'erreur
    // de parsing)

    lexer::Position position = mPosition;

    if ( type == lexer::Lexeme::Type::Newline ) {

        mPosition.line += 1;
        mPosition.column = size;

        if ( size >= 2 && mTs[ 0 ] == '\r' && mTs[ 1 ] == '\n' ) {
            mPosition.column -= 2;
        } else {
            mPosition.column -= 1;
        }

    } else {

        mPosition.column += size;

    }

    // Emission du symbole final

    return new lexer::Lexeme( type, std::string( mTs, size ), position );

}
