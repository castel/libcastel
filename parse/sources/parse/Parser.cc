#include <cstdlib>
#include <memory>

#include "castel/ast/Statement.hh"
#include "castel/lex/Lexeme.hh"
#include "castel/lex/Lexer.hh"
#include "castel/parse/Exception.hh"
#include "castel/parse/Parser.hh"

using namespace castel;
using parse::Parser;

#include "sources/parse/lemon-parser.cc"

ast::Statement * Parser::exec( void )
{
    std::unique_ptr< lex::Lexeme > lexeme;

    void * lemonParser = ParseAlloc( malloc );

 loop:

    lexeme.reset( mLexer.consume( ) );

    if ( lexeme->type( ) == lex::Lexeme::Type::Spaces )
        goto loop;

    castelparserIsValid = true;
    Parse( lemonParser, static_cast< int >( lexeme->type( ) ), lexeme.get( ) );

    if ( ! castelparserIsValid )
        goto syntaxError;

    if ( lexeme->type( ) == lex::Lexeme::Type::End )
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
