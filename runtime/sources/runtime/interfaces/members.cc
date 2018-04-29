#include "castel/runtime/attributes/Member.hh"
#include "castel/runtime/attributes/Method.hh"
#include "castel/runtime/boxes/Class.hh"
#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/boxes/String.hh"
#include "castel/runtime/helper/Fatal.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/Box.hh"

using namespace castel;

void Castel_addMember( runtime::Box * instance, char const * name, runtime::Box * value )
{
    instance->attribute( std::make_pair( runtime::Box::PropertyNS::Standards, name ), runtime::helper::create< runtime::attributes::Member >( value ) );
}

void Castel_addMethod( runtime::Box * instance, char const * name, runtime::boxes::Function * function )
{
    instance->attribute( std::make_pair( runtime::Box::PropertyNS::Standards, name ), runtime::helper::create< runtime::attributes::Method >( function ) );
}

runtime::Attribute * Castel_getAttribute( runtime::Box * instance, runtime::Box * operand )
{
    std::string propertyName = dynamic_cast< runtime::boxes::String * >( operand )->toStdString( );
    auto key = std::make_pair( runtime::Box::PropertyNS::Standards, std::string( propertyName ) );

    runtime::Attribute * attribute = nullptr;

    runtime::Box * currentContainer = instance;
    runtime::boxes::Class * nextContainer = instance->type( );

    while ( currentContainer != nullptr && attribute == nullptr ) {
        attribute = currentContainer->attribute( key );
        currentContainer = nextContainer;
        nextContainer = nextContainer
            ? nextContainer->parent( )
            : nullptr
        ;
    }

    if ( ! attribute )
        runtime::helper::Fatal( )
            << "Cannot read property '" << propertyName << "'" << std::endl;

    return attribute;
}

runtime::Box * Castel_getProperty( runtime::Box * instance, runtime::Box * operand )
{
    return Castel_getAttribute( instance, operand )->get( instance );
}

runtime::Box * Castel_setProperty( runtime::Box * instance, runtime::Box * operand, runtime::Box * value )
{
    Castel_getAttribute( instance, operand )->set( instance, value );

    return value;
}
