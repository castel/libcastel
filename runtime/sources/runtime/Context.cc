#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "castel/runtime/Box.hh"
#include "castel/runtime/Context.hh"
#include "castel/runtime/Loader.hh"

using namespace castel;
using runtime::Context;

runtime::Box * Context::load( std::string const & locator )
{
    std::string::size_type pos = locator.find( ':' );

    if ( pos == std::string::npos || pos == 0 || pos == locator.length( ) )
        throw std::runtime_error( "Invalid locator" );

    std::string name = locator.substr( 0, pos );
    std::string path = locator.substr( pos + 1 );

    auto it = mLoaders.find( name );

    if ( it == mLoaders.end( ) )
        throw std::runtime_error( "Loader '" + name + "' does not exists" );

    return it->second->load( * this, path );
}

void Context::fatal( std::string const & errorMessage )
{
    std::cerr << "Fatal : " << errorMessage << std::endl;
    std::exit( - 1 );
}
