#include "castel/runtime/attributes/Member.hh"

using namespace castel;
using runtime::attributes::Member;

runtime::Box * Member::get( runtime::Box * ) const
{
    return mValue;
}

void Member::set( runtime::Box * instance, runtime::Box * value )
{
    mValue = value;
}
