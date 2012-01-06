#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

#include <p9/lexer/Lexer.hh>
#include <p9/parser/Parser.hh>

int main( int argc, char ** argv )
{
	std::stringstream sstream;
	sstream << std::cin.rdbuf( );
	
	std::string content;
	content = sstream.str( );
	
	p9::lexer::Lexer lexer( content.c_str( ), content.size( ) );
	p9::parser::Parser parser( lexer );
	
	std::cout << parser.exec( ) << std::endl;
	
	return 0;
}
