#include "DIPaCUS/components/Neighborhood.h"

using namespace DIPaCUS::Neighborhood;



EightNeighborhoodPredicate::EightNeighborhoodPredicate(const DigitalSet &DS):myDigitalSet(DS)
{
    lowerBound = DS.domain().lowerBound();
    upperBound = DS.domain().upperBound();
};


bool EightNeighborhoodPredicate::operator()(const Point &aPoint) const
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


bool EightNeighborhoodPredicate::operator()(const Domain::ConstIterator &it) const
{
    return (*this)(*it);
}




FourNeighborhoodPredicate::FourNeighborhoodPredicate(const DigitalSet &DS): myDigitalSet(DS)
{
    lowerBound = DS.domain().lowerBound();
    upperBound = DS.domain().upperBound();
}


bool FourNeighborhoodPredicate::operator()(const Point &aPoint) const
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


bool FourNeighborhoodPredicate::operator()(const Domain::ConstIterator &it) const
{
    return (*this)(*it);
}