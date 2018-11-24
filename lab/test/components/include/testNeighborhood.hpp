#include "testNeighborhood.h"

namespace Test {namespace Neighborhood{
    template<typename TPredicate>
    DigitalSet Internal::digitalBoundary(const DigitalSet& ds)
    {
        TPredicate NP(ds);
        DigitalSet boundary(ds.domain());

        for(auto it=ds.begin();it!=ds.end();++it)
        {
            if( !NP(*it) ) boundary.insert(*it);
        }

        return boundary;
    }
}}