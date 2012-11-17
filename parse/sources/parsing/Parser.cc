#include <cstdlib>
#include <memory>

#include "castel/ast/Statement.hh"
#include "castel/lexing/Lexeme.hh"
#include "castel/lexing/Lexer.hh"
#include "castel/parsing/Exception.hh"
#include "castel/parsing/Parser.hh"

using namespace castel;
using parsing::Parser;

#include "sources/parsing/lemon-parser.cc"

ast::Statement * Parser::exec( void )
{
    std::unique_ptr< lexing::Lexeme > lexeme;

    void * lemonParser = ParseAlloc( malloc );

 loop:

    lexeme.reset( mLexer.consume( ) );

    if ( lexeme->type( ) == lexing::Lexeme::Type::Spaces )
        goto loop;

    castelparserIsValid = true;
    Parse( lemonParser, static_cast< int >( lexeme->type( ) ), lexeme.get( ) );

    if ( ! castelparserIsValid )
        goto syntaxError;

    if ( lexeme->type( ) == lexing::Lexeme::Type::End )
        goto endOfFile;

    lexeme.release( );

    goto loop;

 syntaxError:

    ParseFree( lemonParser, free );

    throw Exception( "Unexpected token", * lexeme, castelparserExpectedTokens );

 endOfFile:

    ParseFree( lemonParser, free );

    return castelparserRootStatement;
}
