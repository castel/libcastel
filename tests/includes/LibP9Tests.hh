#pragma once

#include <memory>
#include <string>

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <castel/lexer/Lexer.hh>
#include <castel/parser/Parser.hh>

class LibP9Tests : public CppUnit::TestFixture
{

public:

    typedef std::string (*Method)( std::string const & );

public:

    void tearDown( void );

public:

    void initSource( Method method, std::string const & data );

    void initLexer( Method method, std::string const & data );

    void initParser( Method method, std::string const & data );

public:

    castel::lexer::Lexer & lexer( void ) const
    { return *mLexer; }

    castel::parser::Parser & parser( void ) const
    { return *mParser; }

protected:

    static std::string fromString( std::string const & string );

    static std::string fromFile( std::string const & file );

private:

    std::unique_ptr< std::string > mSource;

    std::unique_ptr< castel::lexer::Lexer > mLexer;

    std::unique_ptr< castel::parser::Parser > mParser;

};
