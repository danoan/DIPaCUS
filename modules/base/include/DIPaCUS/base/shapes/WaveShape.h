#ifndef DIPACUS_WAVESHAPE_H
#define DIPACUS_WAVESHAPE_H

#include <functional>
#include <DGtal/helpers/StdDefs.h>

namespace DIPaCUS
{
    namespace Shapes
    {
        class WaveShape
        {

        public:
            typedef DGtal::Z2i::RealPoint RealPoint;

        private:
            typedef DGtal::Z2i::Point Point;
            typedef DGtal::Z2i::Domain domain;

            typedef std::function<double(double)> LinearMap;

        public:
            WaveShape(double maxX,double maxWidth, double maxHeight, double minHeight);

            DGtal::Orientation orientation(const RealPoint& aPoint) const;

            RealPoint getLowerBound() const { return lb; }
            RealPoint getUpperBound() const { return ub; }

        private:
            double f(double x,double minHeight) const;

            LinearMap linearMap(double minValue, double maxValue, double mapMin, double mapMax);

        private:
            Point lb,ub;
            double minHeight;
            LinearMap yMap;
            LinearMap xMap;

        };
    }
}


#endif //DIPACUS_WAVESHAPE_H
