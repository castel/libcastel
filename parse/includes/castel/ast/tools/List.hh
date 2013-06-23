#include <list>

#include "castel/ast/tools/Hold.hh"

namespace castel
{

    namespace ast
    {

        namespace tools
        {

            template < typename T >
            using List = std::list< ast::tools::Hold< T > >;

        }

    }

}
