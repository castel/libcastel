#include "castel/runtime/boxes/Bool.hh"

using namespace castel;
using runtime::boxes::Bool;

bool Bool::operatorBool( void )
{
    return mValue;
}
