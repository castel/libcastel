#include <cstdlib>
#include <memory>

#include "castel/ast/Statement.hh"
#include "castel/lexer/Lexeme.hh"
#include "castel/lexer/Lexer.hh"
#include "castel/parser/Exception.hh"
#include "castel/parser/Parser.hh"
#include <iostream>
using namespace castel;
using namespace castel::parser;

#include "sources/parser/parse.cc"

Parser::Parser( lexer::Lexer & lexer )
    : mLexer( lexer )
{
}

ast::Statement * Parser::exec( void )
{
    std::unique_ptr< lexer::Lexeme > lexeme;

    void * lemonParser = ParseAlloc( malloc );

 loop:
    lexeme.reset( mLexer.consume( ) );

    if ( lexeme->type( ) == lexer::Lexeme::Type::Spaces )
        goto loop;

    castelparserIsValid = true;
    std::cout << lexer::Lexeme::constTypeString( * lexeme ) << std::endl;
    Parse( lemonParser, static_cast< int >( lexeme->type( ) ), lexeme.get( ) );

    if ( ! castelparserIsValid )
        goto syntaxError;

    if ( lexeme->type( ) == lexer::Lexeme::Type::End )
        goto endOfFile;

    lexeme.release( );

    goto loop;

 syntaxError:
    ParseFree( lemonParser, free );

    throw Exception( "Unexpected token", lexeme.release( ) );

 endOfFile:
    ParseFree( lemonParser, free );

    return castelparserRootStatement;
}
