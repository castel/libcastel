#include "p9/lexer/Exception.hh"
#include "p9/lexer/Lexeme.hh"
#include "p9/lexer/Lexer.hh"
#include "p9/lexer/Token.hh"

using namespace p9;
using namespace p9::lexer;

%% machine p9lexer;
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
            return new lexer::Lexeme( lexer::TInvalid );
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

        if ( lexeme->type( ) == lexer::TNewline ) {
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
                mLexemeQueue.push( new lexer::Lexeme( lexer::TIndent, lastNewline->position( ) ) );
            }
        }

        else if ( currentLevel > expectedLevel ) {
            mLexemeQueue.push( new lexer::Lexeme( lexer::TNewline, lastNewline->position( ) ) );
            for ( ; currentLevel > expectedLevel; -- currentLevel ) {
                mLexemeQueue.push( new lexer::Lexeme( lexer::TDedent, lastNewline->position( ) ) );
            }
        }

        mLevelStack.top( ) = currentLevel;

    }

    //

    if ( lexeme->type( ) == lexer::TLParenthesis ) {

        mLevelStack.push( mLevelStack.top( ) );

    } else if ( lexeme->type( ) == lexer::TRParenthesis || lexeme->type( ) == lexer::TEOF ) {

        unsigned int currentLevel = mLevelStack.top( ); mLevelStack.pop( );
        unsigned int expectedLevel = ! mLevelStack.empty( ) ? mLevelStack.top( ) : 0;

        if ( lexeme->type( ) == lexer::TEOF || currentLevel > expectedLevel ) {
            mLexemeQueue.push( new lexer::Lexeme( lexer::TNewline, lexeme->position( ) ) );
        }

        for ( int t = currentLevel; t > expectedLevel; -- t ) {
            mLexemeQueue.push( new lexer::Lexeme( lexer::TDedent, lexeme->position( ) ) );
        }

    }

    // Pas de comportement spécial relatif à l'offside rule, nous pouvons
    // renvoyer le lexème généré.

    mLexemeQueue.push( lexeme );
}

lexer::Lexeme * Lexer::fetchNextLexeme( void )
{
    %%{

        Function     = 'function';
        Return       = 'return';
        Var          = 'var';
        If           = 'if';
        Else         = 'else';

        Add          = '+';
        Substract    = '-';
        Multiply     = '*';
        Divide       = '/';
        Modulo       = '%';
        Assign       = '=';

        LParenthesis = '(';
        RParenthesis = ')';

        Colon        = ':';
        Comma        = ',';

        Number       = ('0'[xX][0-9a-fA-F]+|'0'[bB][01]+|[0-9]+('.'[0-9]*)?|[0-9]*'.'[0-9]+);
        Identifier   = [a-zA-Z]+[0-9a-zA-Z_]*;

        Spaces       = [ ]+;
        Newline      = ('\r''\n'|'\r'|'\n')('\t'*);

        main := |*

            Function     => { type = lexer::TFunction;     fbreak; };
            Return       => { type = lexer::TReturn;       fbreak; };
            Var          => { type = lexer::TVar;          fbreak; };
            If           => { type = lexer::TIf;           fbreak; };
            Else         => { type = lexer::TElse;         fbreak; };

            Add          => { type = lexer::TAdd;          fbreak; };
            Substract    => { type = lexer::TSubstract;    fbreak; };
            Multiply     => { type = lexer::TMultiply;     fbreak; };
            Divide       => { type = lexer::TDivide;       fbreak; };
            Modulo       => { type = lexer::TModulo;       fbreak; };
            Assign       => { type = lexer::TAssign;       fbreak; };

            LParenthesis => { type = lexer::TLParenthesis; fbreak; };
            RParenthesis => { type = lexer::TRParenthesis; fbreak; };

            Colon        => { type = lexer::TColon;        fbreak; };
            Comma        => { type = lexer::TComma;        fbreak; };

            Number       => { type = lexer::TNumber;       fbreak; };
            Identifier   => { type = lexer::TIdentifier;   fbreak; };

            Spaces       => { type = lexer::TSpaces;       fbreak; };
            Newline      => { type = lexer::TNewline;      fbreak; };

            any          => { fbreak; };

        *|;

    }%%;

    // Variable qui contiendra le type du lexème à la fin de l'itération

    lexer::Token type;

    if ( mP == mPe ) {

        // Nous avons atteint la fin du flux, le lexème est donc de type EOF

        mTs = mTe = mP;
        type = lexer::TEOF;

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

        if ( type == lexer::TInvalid ) {
            throw lexer::Exception( "Invalid symbol" );
        }

    }

    // Calcul de la taille total du texte contenu dans le lexème

    unsigned int size = mTe - mTs;

    // Modification de la position interne de la machine. N'est
    // utilisé qu'à des fins informatives (par exemple en cas d'erreur
    // de parsing)

    if ( type == lexer::TNewline ) {

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

    // Dans le cas contraire, un symbole valide est émis.

    return new lexer::Lexeme( type, std::string( mTs, size ), mPosition );

}
