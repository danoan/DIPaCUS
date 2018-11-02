#include "boundingBox.h"

namespace Test{ namespace Utils{


    template<typename TPointFilterIterator>
    void Intern::boundingBox(BoundingBox& bb,
                             TPointFilterIterator itb,
                             TPointFilterIterator ite)
    {
        TPointFilterIterator it = itb;
        while(!itb->valid) ++itb;

        if(itb->valid)
        {
            Point currP = itb->point;
            bb.lb = currP;
            bb.ub = currP;

            do{
                if(it->valid)
                {
                    currP = it->point;

                    bb.lb[0] = currP[0] < bb.lb[0] ? currP[0] : bb.lb[0];
                    bb.lb[1] = currP[1] < bb.lb[1] ? currP[1] : bb.lb[1];

                    bb.ub[0] = currP[0] > bb.ub[0] ? currP[0] : bb.ub[0];
                    bb.ub[1] = currP[1] > bb.ub[1] ? currP[1] : bb.ub[1];
                }

                ++it;
            }while(it!=ite);
        }
        else
        {
            bb.lb = Point(0,0);
            bb.ub = Point(0,0);
        }

    }

}}