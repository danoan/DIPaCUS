#ifndef DIPACUS_BEANSHAPE_H
#define DIPACUS_BEANSHAPE_H

#include <functional>
#include <DGtal/helpers/StdDefs.h>

namespace DIPaCUS
{
    namespace Shapes
    {
        class BeanShape
        {

        public:
            typedef DGtal::Z2i::RealPoint RealPoint;

        private:
            typedef DGtal::Z2i::Point Point;

            typedef std::function<bool(const RealPoint& p)> CirclePredicate;

        public:
            BeanShape(const RealPoint& center, double curvature);

            DGtal::Orientation orientation(const RealPoint& aPoint) const;

            RealPoint getLowerBound() const { return lb; }
            RealPoint getUpperBound() const { return ub; }

	private:
	    CirclePredicate circle(const RealPoint& center, const double radius, const bool aboveYCenter);
	    CirclePredicate outerCircle(const RealPoint& center, const double radius);

        public:
            RealPoint lb,ub;
	    RealPoint center;

	    double r1,r2;
	    RealPoint a1,b1,c1;
	    RealPoint a2,b2,c2;
	    RealPoint a3,b3,c3;
	    RealPoint a4,b4,c4;

	    CirclePredicate f1,f2,f3,f4;
        };
    }
}


#endif //DIPACUS_BEANSHAPE_H
