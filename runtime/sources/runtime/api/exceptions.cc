#include <cstdint>
#include <cstdlib>
#include <unwind.h>

#include "castel/runtime/api/exceptions.hh"

static std::uint64_t const Castel_exceptionClass = ( ( ( ( ( ( ( (
    ( std::uint64_t ) 'C'  ) << 8 |
    ( std::uint64_t ) 'A'  ) << 8 |
    ( std::uint64_t ) 'S'  ) << 8 |
    ( std::uint64_t ) 'T'  ) << 8 |
    ( std::uint64_t ) 'E'  ) << 8 |
    ( std::uint64_t ) 'L'  ) << 8 |
    ( std::uint64_t ) 'C'  ) << 8 |
    ( std::uint64_t )  0   );

static void Castel_exceptionCleanup( _Unwind_Reason_Code code, _Unwind_Exception * exception )
{
    delete exception;
}

void Castel_throw( castel::runtime::Box * exception )
{
    _Unwind_Exception * unwindHeader = static_cast< _Unwind_Exception * >( std::malloc( sizeof( _Unwind_Exception ) ) );
    unwindHeader->exception_class = Castel_exceptionClass;
    unwindHeader->exception_cleanup = Castel_exceptionCleanup;

    _Unwind_RaiseException( unwindHeader );
    std::terminate( );
}
