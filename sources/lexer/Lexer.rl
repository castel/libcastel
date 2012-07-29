#include "p9/lexer/Exception.hh"
#include "p9/lexer/Lexeme.hh"
#include "p9/lexer/Lexer.hh"
#include "p9/lexer/Token.hh"

using namespace p9;
using namespace p9::lexer;

%% machine p9lexer;
%% write data;

Lexer::Lexer          ( char const * p, std::size_t n )
    : mP              ( p      )
    , mPe             ( mP + n )
    , mEof            ( mPe    )
    , mTs             ( 0      )
    , mTe             ( 0      )
    , mCs             ( 0      )
    , mAct            ( mCs    )
    , mPendingLexemes (        )
    , mLastNewline    (        )
    , mCurrentLevel   ( 0      )
    , mPosition       ( 1, 1   )
    , mNLInjected     ( false  )
{
}

Lexeme * Lexer::consume( void )
{
    %%{

        Function     = 'function';
        Return       = 'return';
        Var          = 'var';

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

            Add          => { type = lexer::TAdd;          fbreak; };
            Substract    => { type = lexer::TSubstract;    fbreak; };
            Multiply     => { type = lexer::TMultiply;     fbreak; };
            Divide       => { type = lexer::TDivide;       fbreak; };
            Modulo       => { type = lexer::TModulo;       fbreak; };
            Assign       => { type = lexer::TAssign;       fbreak; };

            LParenthesis => { type = lexer::TLParenthesis; fbreak; };
            RParenthesis => { type = lexer::TRParenthesis; fbreak; };

            Colon        => { type = lexer::TColon;        fbreak; };

            Number       => { type = lexer::TNumber;       fbreak; };
            Identifier   => { type = lexer::TIdentifier;   fbreak; };

            Spaces       => { type = lexer::TSpaces;       fbreak; };
            Newline      => { type = lexer::TNewline;      fbreak; };

            any          => { fbreak; };

        *|;

    }%%;

    // Nommage des diverses variables de Ragel. Nous utilisons
    // des variables membres afin de conserver l'état de la machine
    // entre les appels à la méthode consume()

    %% variable p   mP   ;
    %% variable pe  mPe  ;
    %% variable eof mEof ;

    %% variable ts  mTs  ;
    %% variable te  mTe  ;

    %% variable cs  mCs  ;
    %% variable act mAct ;

    // Tant que des lexemes n'ont pas été consommés,
    // pas besoin de lancer la machine

    if ( ! mPendingLexemes.empty( ) ) {

        lexer::Lexeme * lexeme = mPendingLexemes.front( );
        mPendingLexemes.pop( );

        return lexeme;

    }

    lexer::Token type;

    // Si l'on est à la fin de la chaine d'entrée, on
    // renvoie un jeton de fin d'entrée

    if ( mP == mPe ) {

        mTs = mTe = mP;

        if ( ! mNLInjected ) {

            type = lexer::TNewline;
            mNLInjected = true;

        } else {

            type = lexer::TEOF;

        }

    } else {

        // Lancement de la machine

        %% write init;
        %% write exec;

        // Si le symbole est inconnu, on jette une exception

        if ( type == lexer::TInvalid )
            throw lexer::Exception( "Invalid symbol" );

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

    // Construction du lexème à partir des informations récupérées par
    // la machine

    lexer::Lexeme * lexeme = new lexer::Lexeme( type, std::string( mTs, size ), mPosition );

    // Si le lexème est une nouvelle ligne, on l'enregistre puis on
    // vérifie le type du lexème suivant

    if ( lexeme->type( ) == lexer::TNewline ) {

        mLastNewline.reset( lexeme );

        return this->consume( );

    }

    // Si le lexème n'est pas une nouvelle ligne et qu'une nouvelle ligne
    // a déjà été trouvée, nous générons les incrémentations ou décrémentations
    // qui s'imposent

    if ( mLastNewline.get( ) ) {

        std::string str = mLastNewline->as< std::string >( );

        std::size_t start = str.find_first_of( '\t' );
        std::size_t end = str.find_last_of( '\t' );

        unsigned int level = start != std::string::npos ? 1 + end - start : 0;

        if ( mCurrentLevel == level )
            mPendingLexemes.push( mLastNewline.release( ) );

        for ( ; mCurrentLevel < level; ++ mCurrentLevel )
            mPendingLexemes.push( new lexer::Lexeme( lexer::TIndent, mLastNewline->position( ) ) );

        for ( ; mCurrentLevel > level; -- mCurrentLevel ) {
            mPendingLexemes.push( new lexer::Lexeme( lexer::TDedent, mLastNewline->position( ) ) );
            mPendingLexemes.push( new lexer::Lexeme( lexer::TNewline, mLastNewline->position( ) ) );
        }

        mPendingLexemes.push( lexeme );
        mLastNewline.reset( );

        return this->consume( );

    }

    // Pas de comportement spécial relatif à l'offside rule, nous pouvons
    // renvoyer le lexème généré.

    return lexeme;
}
