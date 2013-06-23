#include <memory>

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            template < typename T >
            using Hold = std::unique_ptr< T >;

        }

    }

}
