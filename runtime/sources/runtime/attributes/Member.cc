#include "castel/runtime/attributes/Member.hh"

using namespace castel;
using runtime::attributes::Member;
using runtime::Attribute;

runtime::Box * Member::get( runtime::Context *, runtime::Box * ) const
{
    return mValue;
}

Attribute & Member::set( runtime::Context *, runtime::Box * instance, runtime::Box * value )
{
    mValue = value;

    return * this;
}
