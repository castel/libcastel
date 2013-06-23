#include <algorithm>
#include <cstdint>
#include <vector>

#include "castel/runtime/boxes/Dict.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using runtime::boxes::Dict;

struct Comparator
{

    static bool predicate( runtime::Box * a, runtime::Box * b )
    {
        return a->operatorEqual( b )->operatorBoolCast( );
    }

    Comparator( std::vector< runtime::Box * > const & base ) : mBase( base ) { }
    std::vector< runtime::Box * > const & mBase;

    bool operator()( std::pair< std::vector< runtime::Box * >, runtime::Box * > const & test )
    {
        auto const & key = test.first;
        if ( key.size( ) != mBase.size( ) ) return false;
        return std::mismatch( mBase.begin( ), mBase.end( ), key.begin( ), predicate ).first == mBase.end( );
    }

};

bool Dict::operatorBoolCast( void )
{
    return true;
}

runtime::Box * Dict::item( std::vector< runtime::Box * > const & key ) const
{
    auto begin = mItems.begin( );
    auto end = mItems.end( );

    auto it = std::find_if( begin, end, Comparator( key ) );

    if ( it == mItems.end( ) ) {
        return runtime::helper::create< runtime::boxes::Undefined >( );
    } else {
        return it->second;
    }
}

Dict & Dict::item( std::vector< runtime::Box * > const & key, runtime::Box * value )
{
    auto it = std::find_if( mItems.begin( ), mItems.end( ), Comparator( key ) );

    if ( it == mItems.end( ) ) {
        mItems[ key ] = value;
    } else {
        it->second = value;
    }

    return * this;
}

runtime::Box * Dict::operatorSubscript( std::uint32_t argc, runtime::Box ** argv )
{
    std::vector< runtime::Box * > key;
    key.assign( argv, argv + argc );

    return this->item( key );
}
