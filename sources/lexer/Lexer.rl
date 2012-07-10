#include <iostream>
#include <iterator>

#include "build/generated/lexemes"

#include "p9/lexer/Exception.hh"
#include "p9/lexer/Lexeme.hh"
#include "p9/lexer/Lexer.hh"

using namespace p9;
using namespace p9::lexer;

%% machine p9lexer;
%% write data;

Lexer::Lexer( char const * p, std::size_t n )
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
{
}

Lexeme * Lexer::consume( void )
{
    %%{

        Add       = '+';
        Substract = '-';
        Multiply  = '*';
        Divide    = '/';
        Modulo    = '%';

        Number = ('0'[xX][0-9a-fA-F]+|'0'[bB][01]+|[0-9]+('.'[0-9]*)?|[0-9]*'.'[0-9]+);

        Spaces = [ ]+;
        Newline = ('\r''\n'|'\r'|'\n')('\t'*);

        main := |*

            Add       => { type = T_Add;       fbreak; };
            Substract => { type = T_Substract; fbreak; };
            Multiply  => { type = T_Multiply;  fbreak; };
            Divide    => { type = T_Divide;    fbreak; };
            Modulo    => { type = T_Modulo;    fbreak; };

            Number    => { type = T_Number; fbreak; };
            Spaces    => { type = T_Spaces; fbreak; };

            Newline   => { type = T_Newline; fbreak; };

            any       => { fbreak; };

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

    // Si l'on est à la fin de la chaine d'entrée, on
    // renvoie un jeton de fin d'entrée

    if ( mP == mPe ) {

        if ( mCurrentLevel ) {

            -- mCurrentLevel;

            return new lexer::Lexeme( T_Dedent, mPosition );

        } else {

            return new lexer::Lexeme( T_EOF, mPosition );

        }

    }

    // Variable qui contiendra le type du lexème à la fin
    // de l'exécution de la machine

    int type = 0;

    // Lancement de la machine

    %% write init;
    %% write exec;

    // Si le symbole est inconnu, on jette une exception

    if ( ! type )
        throw lexer::Exception( "Invalid symbol" );

    // Calcul de la taille total du texte contenu dans le lexème

    unsigned int size = mTe - mTs;

    // Modification de la position interne de la machine. N'est
    // utilisé qu'à des fins informatives (par exemple en cas d'erreur
    // de parsing)

    if ( type == T_Newline ) {

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

    if ( lexeme->type( ) == T_Newline ) {

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

        for ( ; mCurrentLevel < level; ++ mCurrentLevel )
            mPendingLexemes.push( new lexer::Lexeme( T_Indent, mLastNewline->position( ) ) );
        for ( ; mCurrentLevel > level; -- mCurrentLevel )
            mPendingLexemes.push( new lexer::Lexeme( T_Dedent, mLastNewline->position( ) ) );

        mPendingLexemes.push( lexeme );
        mLastNewline.reset( );

        return this->consume( );

    }

    // Pas de comportement spécial relatif à l'offside rule, nous pouvons
    // renvoyer le lexème généré.

    return lexeme;
}
