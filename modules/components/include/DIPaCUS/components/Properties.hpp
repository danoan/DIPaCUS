#include "Properties.h"

using namespace DIPaCUS::Properties;

template<class TSCellIterator>
CurveBoundingBox<TSCellIterator>::CurveBoundingBox(BoundingBox& bb,
                                                   TSCellIterator itb,
                                                   TSCellIterator ite)
{
    TSCellIterator it = itb;
    Point currP;
    bb.lb = it->preCell().coordinates;
    bb.ub = bb.lb;
    do{
        currP = it->preCell().coordinates;

        bb.lb[0] = currP[0] < bb.lb[0]?currP[0]:bb.lb[0];
        bb.lb[1] = currP[1] < bb.lb[1]?currP[1]:bb.lb[1];

        bb.ub[0] = currP[0] > bb.ub[0]?currP[0]:bb.ub[0];
        bb.ub[1] = currP[1] > bb.ub[1]?currP[1]:bb.ub[1];

        ++it;
    }while(it!=ite);

    //Convert to normal coordinates( before was KCoordinates)
    bb.lb/=2;
    bb.ub/=2;
}