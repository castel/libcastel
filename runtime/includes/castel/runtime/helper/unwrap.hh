#pragma once

#include "castel/runtime/boxes/Boolean.hh"
#include "castel/runtime/boxes/Number.hh"
#include "castel/runtime/boxes/String.hh"
#include "castel/runtime/helper/Fatal.hh"
#include "castel/runtime/Box.hh"

namespace castel
{

    namespace runtime
    {

        namespace helper
        {

            template < typename T >
            class unwrap;

            template < >
            class unwrap< bool >
            {
                private: runtime::Box * box;
                public: unwrap( runtime::Box * box ) : box( box ) { }
                public: operator bool( void )
                {
                    auto booleanBox = dynamic_cast< runtime::boxes::Boolean * >( box );

                    if ( booleanBox == nullptr )
                        runtime::helper::Fatal( )
                            << "Parameter type mismatch" << std::endl;

                    return booleanBox->value( );
                }
            };

            template < >
            class unwrap< double >
            {
                private: runtime::Box * box;
                public: unwrap( runtime::Box * box ) : box( box ) { }
                public: operator double( void )
                {
                    auto numberBox = dynamic_cast< runtime::boxes::Number * >( box );

                    if ( numberBox == nullptr )
                        runtime::helper::Fatal( )
                            << "Parameter type mismatch" << std::endl;

                    return numberBox->value( );
                }
            };

            template < >
            class unwrap< char const * >
            {
                private: runtime::Box * box;
                public: unwrap( runtime::Box * box ) : box( box ) { }
                public: operator char const *( void )
                {
                    auto stringBox = dynamic_cast< runtime::boxes::String * >( box );

                    if ( stringBox == nullptr )
                        runtime::helper::Fatal( )
                            << "Parameter type mismatch" << std::endl;

                    return reinterpret_cast< char const * >( stringBox->value( ) );
                }
            };

            template < >
            class unwrap< std::string >
            {
                private: runtime::Box * box;
                public: unwrap( runtime::Box * box ) : box( box ) { }
                public: operator std::string( void )
                {
                    auto stringBox = dynamic_cast< runtime::boxes::String * >( box );

                    if ( stringBox == nullptr )
                        runtime::helper::Fatal( )
                            << "Parameter type mismatch" << std::endl;

                    return stringBox->toStdString( );
                }
            };

            template < >
            class unwrap< std::string const & > : public unwrap< std::string >
            { using unwrap< std::string >::unwrap; };

        }

    }

}
