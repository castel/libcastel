#pragma once

#include <cstring>
#include <string>

#include "castel/runtime/boxes/Binding.hh"
#include "castel/runtime/boxes/Function.hh"
#include "castel/runtime/boxes/Number.hh"
#include "castel/runtime/boxes/Resource.hh"
#include "castel/runtime/boxes/String.hh"
#include "castel/runtime/helper/create.hh"
#include "castel/runtime/helper/malloc.hh"
#include "castel/runtime/helper/unwrap.hh"

namespace castel
{

    namespace runtime
    {

        namespace helper
        {

            runtime::boxes::Number * wrap( double value );

            runtime::boxes::String * wrap( std::string const & value );

            template < typename Return, typename ... Parameters >
            runtime::boxes::Binding * wrap( Return ( * fn )( Parameters ... ) );

            namespace detail
            {

                template < unsigned ... >
                struct Indices { };

                template < unsigned N, unsigned ... Rest >
                struct IndicesGenerator : IndicesGenerator< N - 1, N - 1, Rest ... > { };

                template < unsigned ... Rest >
                struct IndicesGenerator< 0, Rest ... > : Indices< Rest ... > { };

                template < typename Return, typename ... Parameters, unsigned ... Indices >
                runtime::Box * forward( Return ( * fn )( Parameters ... ), int argc, runtime::Box ** argv, runtime::helper::detail::Indices< Indices ... > )
                {
                    return runtime::helper::wrap( fn( runtime::helper::unwrap< Parameters >( argv[ Indices ] )... ) );
                }

                template < typename Return, typename ... Parameters >
                runtime::Box * forward( runtime::Box ***, unsigned int argc, runtime::Box ** argv )
                {
                    Return ( * fn )( Parameters ... ) = static_cast< runtime::boxes::Resource< Return ( * )( Parameters ... ) > * >( argv[ 0 ] )->value( );
                    return runtime::helper::detail::forward( fn, argc - 1, argv + 1, runtime::helper::detail::IndicesGenerator< sizeof...( Parameters ) >( ) );
                }

            }

            runtime::boxes::Number * wrap( double value )
            {
                return runtime::helper::create< runtime::boxes::Number >( value );
            }

            runtime::boxes::String * wrap( std::string const & value )
            {
                char * copy = runtime::helper::malloc< char >( value.length( ) + 1 );
                std::strcpy( copy, value.c_str( ) );

                return runtime::helper::create< runtime::boxes::String >( copy, value.length( ) );
            }

            template < typename Return, typename ... Parameters >
            runtime::boxes::Binding * wrap( Return ( * fn )( Parameters ... ) )
            {
                runtime::boxes::Function::Signature * forwarder = & runtime::helper::detail::forward< Return, Parameters ... >;
                runtime::boxes::Function * accessor = runtime::helper::create< runtime::boxes::Function >( forwarder, sizeof...( Parameters ), nullptr );
                return runtime::helper::create< runtime::boxes::Binding >( accessor, 1, runtime::helper::malloc< runtime::Box * >( {
                    runtime::helper::create< runtime::boxes::Resource< Return ( * )( Parameters ... ) > >( fn )
                } ) );
            }

        }

    }

}
