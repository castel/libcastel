#include "castel/runtime/attributes/Method.hh"
#include "castel/runtime/boxes/Binding.hh"

using namespace castel;
using runtime::attributes::Method;
using runtime::Attribute;

runtime::Box * Method::get( runtime::Box * instance ) const
{
    auto argv = reinterpret_cast< runtime::Box ** >( ::castel_malloc( sizeof( runtime::Box * ), 1 ) );
    argv[ 0 ] = instance;

    return runtime::boxes::Binding::create( mFunction, 1, argv );
}

Attribute & Method::set( runtime::Box * instance, runtime::Box * value )
{
    ::castel_fatal( "Class methods cannot be modified" );

    return * this;
}
