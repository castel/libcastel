#include "castel/runtime/boxes/Boolean.hh"

using namespace castel;
using runtime::boxes::Boolean;

bool Boolean::operatorBoolCast( void )
{
    return mValue;
}
