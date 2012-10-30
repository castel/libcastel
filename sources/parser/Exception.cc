#include <list>
#include <sstream>
#include <string>

#include "castel/lexer/Lexeme.hh"
#include "castel/lexer/Position.hh"
#include "castel/parser/Exception.hh"
#include "castel/parser/Parser.hh"

using namespace castel;
using namespace castel::parser;

Exception::Exception( std::string const & message, lexer::Lexeme * lexeme, std::list< std::string > const & expectedTokens )
    : mMessage( message )
    , mLexeme( lexeme  )
{
    if ( lexeme ) {

        lexer::Position const & position = mLexeme->position( );

        std::ostringstream stringstream;
        stringstream << message << " " << lexer::Lexeme::constTypeString( lexeme->type( ) ) << " at " << position.toString( );

        if ( ! expectedTokens.empty( ) ) {
            auto lastExpectation = ( ++ expectedTokens.rbegin( ) ).base( );

            stringstream << " (expected ";

            for ( auto it = expectedTokens.begin( ); it != expectedTokens.end( ); ++ it ) {

                if ( it != expectedTokens.begin( ) ) {
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

    } else {

        mWhat = message;

    }

}
