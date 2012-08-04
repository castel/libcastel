#include <fstream>
#include <sstream>
#include <string>

#include <castel/lexer/Lexer.hh>
#include <castel/parser/Parser.hh>

#include "LibP9Tests.hh"

void LibP9Tests::tearDown( void )
{
    mParser.reset( );
    mLexer.reset( );
    mSource.reset( );
}

void LibP9Tests::initSource( Method method, std::string const & data )
{
    mSource.reset( new std::string( method( data ) ) );
}

void LibP9Tests::initLexer( Method method, std::string const & data )
{
    this->initSource( method, data );

    mLexer.reset( new castel::lexer::Lexer( mSource->c_str( ), mSource->size( ) ) );
}

void LibP9Tests::initParser( Method method, std::string const & data )
{
    this->initLexer( method, data );

    mParser.reset( new castel::parser::Parser( * mLexer ) );
}

std::string LibP9Tests::fromString( std::string const & string )
{
    return string;
}

std::string LibP9Tests::fromFile( std::string const & file )
{
    std::ifstream fstream( file.c_str( ), std::ios_base::binary | std::ios_base::in );

    std::stringstream sstream;
    sstream << fstream.rdbuf( );

    return sstream.str( );
}
