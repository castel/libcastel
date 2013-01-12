#include "castel/runtime/attributes/Method.hh"
#include "castel/runtime/boxes/Binding.hh"
#include "castel/runtime/helper/Fatal.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/helper/malloc.hh"
#include "castel/runtime/Attribute.hh"
#include "castel/runtime/Box.hh"

using namespace castel;
using runtime::attributes::Method;
using runtime::Attribute;

runtime::Box * Method::get( runtime::Box * instance ) const
{
    runtime::Box ** argv = runtime::helper::malloc( { instance } );
    return runtime::helper::create< runtime::boxes::Binding >( mFunction, 1, argv );
}

Attribute & Method::set( runtime::Box * instance, runtime::Box * value )
{
    runtime::helper::Fatal( ) << "Class methods cannot be modified" << std::endl;
}
