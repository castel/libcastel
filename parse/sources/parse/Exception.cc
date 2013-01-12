#include <list>
#include <sstream>
#include <string>

#include "castel/lex/Lexeme.hh"
#include "castel/parse/Exception.hh"
#include "castel/parse/Parser.hh"

using namespace castel;
using parse::Exception;

Exception::Exception( std::string const & message, lex::Lexeme const & lexeme, std::list< std::string > const & expectedTokens )
    : mMessage( message )
    , mLexeme( lexeme  )
    , mExpectedTokens( expectedTokens )
{
    std::ostringstream stringstream;
    stringstream << mMessage << " " << lex::Lexeme::constTypeString( mLexeme.type( ) ) << " at line " << mLexeme.position( ).second << ", column " << mLexeme.position( ).first;

    if ( ! mExpectedTokens.empty( ) ) {
        auto lastExpectation = ( ++ mExpectedTokens.rbegin( ) ).base( );

        stringstream << " (expected ";

        for ( auto it = mExpectedTokens.begin( ); it != mExpectedTokens.end( ); ++ it ) {

            if ( it != mExpectedTokens.begin( ) ) {
                if ( it != lastExpectation ) {
                    stringstream << ", ";
                } else if ( it == lastExpectation ) {
                    stringstream << " or ";
                }
            }

            stringstream << * it;
        }

        stringstream << ")";
    }

    mWhat = stringstream.str( );
}
