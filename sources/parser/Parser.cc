#include <cstdlib>

#include <p9/parser/Parser.hh>
#include <p9/lexer/Lexer.hh>
#include <p9/lexer/Lexeme.hh>

using namespace p9;
using namespace p9::parser;

#include "./sources/parser/parse.cc"

Parser::Parser( lexer::Lexer & lexer )
: _lexer( lexer )
{
}

ast::Token * Parser::exec( void )
{
	lexer::Lexeme lexeme;
	ast::Token * token = 0;
	
	void * lparse = ParseAlloc( malloc );
	
 loop:
	lexeme = _lexer.consume( );
	
	if ( lexeme == lexer::Lexeme::invalid )
		goto invalidLexeme;
	
	p9parserIsValid = true;
	Parse( lparse, lexeme, 0 );
	
	if ( ! p9parserIsValid )
		goto syntaxError;
	
	if ( lexeme == lexer::Lexeme::endOfFile )
		goto endOfFile;
	
	goto loop;
	
 invalidLexeme:
	goto end;
	
 syntaxError:
	goto end;
	
 endOfFile:
	token = p9parserRootToken;
	goto end;
	
 end:
	ParseFree( lparse, free );
	return token;
}
