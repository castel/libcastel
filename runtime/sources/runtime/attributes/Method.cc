#include "castel/runtime/attributes/Method.hh"
#include "castel/runtime/boxes/Binding.hh"

using namespace castel;
using runtime::attributes::Method;
using runtime::Attribute;

runtime::Box * Method::get( runtime::Context * context, runtime::Box * instance ) const
{
    auto argv = context->createArray< runtime::Box * >( 1 );
    argv[ 0 ] = instance;

    return context->create< runtime::boxes::Binding >( mFunction, 1, argv );
}

Attribute & Method::set( runtime::Context * context, runtime::Box * instance, runtime::Box * value )
{
    context->fatal( "Class methods cannot be modified" );

    return * this;
}
