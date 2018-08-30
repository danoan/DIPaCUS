#include "Neighborhood.h"

using namespace DIPaCUS::Neighborhood;

template<typename DigitalSet>
FourNeighborhoodPredicate<DigitalSet>::FourNeighborhoodPredicate(const DigitalSet &DS):myDigitalSet(DS)
{
    lowerBound = DS.domain().lowerBound();
    upperBound = DS.domain().upperBound();
};

template<typename DigitalSet>
bool FourNeighborhoodPredicate<DigitalSet>::operator()(const Point &aPoint) const
{
    Point np;
    int s = 0;
    for (int i = 0; i < 4; ++i) {
        np = aPoint + filter[i];
        if (np[0] < lowerBound[0] || np[1] < lowerBound[1]) continue;
        if (np[0] > upperBound[0] || np[1] > upperBound[1]) continue;


        s += myDigitalSet(np) ? 1 : 0;
    }

    return !(s > 0 && s < 4);
}

template<typename DigitalSet>
bool FourNeighborhoodPredicate<DigitalSet>::operator()(const Domain::ConstIterator &it) const
{
    return (*this)(*it);
}




template<typename DigitalSet>
EightNeighborhoodPredicate<DigitalSet>::EightNeighborhoodPredicate(const DigitalSet &DS): myDigitalSet(DS)
{
    lowerBound = DS.domain().lowerBound();
    upperBound = DS.domain().upperBound();
}


template<typename DigitalSet>
bool EightNeighborhoodPredicate<DigitalSet>::operator()(const Point &aPoint) const
{
    Point np;
    int s = 0;
    for (int i = 0; i < 8; ++i) {
        np = aPoint + filter[i];
        if (np[0] < lowerBound[0] || np[1] < lowerBound[1]) continue;
        if (np[0] > upperBound[0] || np[1] > upperBound[1]) continue;


        s += myDigitalSet(np) ? 1 : 0;
    }

    return !(s > 0 && s < 8);
}

template<typename DigitalSet>
bool EightNeighborhoodPredicate<DigitalSet>::operator()(const Domain::ConstIterator &it) const
{
    return (*this)(*it);
}