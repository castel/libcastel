#include <cstdlib>

#include <p9/parser/Parser.hh>
#include <p9/lexer/TokenDefinitions.hh>
#include <p9/lexer/Lexer.hh>
#include <p9/lexer/Token.hh>

using namespace p9::parser;

using p9::lexer::Token;
using p9::lexer::Lexer;

#include "./sources/parser/parse.cc"

Parser::Parser( Lexer & lexer )
: _lparse( ParseAlloc( malloc ) )
, _lexer( lexer )
{
}

Parser::~Parser( void )
{
	ParseFree( _lparse, free );
}

bool Parser::exec( void ) const
{
	Token token;
	
	while ( 1 ) {
		
		token = _lexer.consume( );
		
		if ( ! token.valid( ) )
			return false;
		
		p9parserIsValid = true;
		Parse( _lparse, token, 0 );
		if ( ! p9parserIsValid )
			return false;
		
		if ( token == Eof )
			return true;
	}
}
