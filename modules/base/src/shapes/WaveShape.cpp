#include "DIPaCUS/base/shapes/WaveShape.h"

namespace DIPaCUS
{
    namespace Shapes
    {
        WaveShape::WaveShape(double maxX,double maxWidth, double maxHeight, double minHeight)
        {
            lb = Point(20,-maxHeight);
            ub = Point(maxWidth,maxHeight);

            xMap = linearMap(0,maxWidth,0,maxX);
            yMap = linearMap(0,maxHeight,0,1+minHeight);
            this->minHeight = minHeight;
        }

        DGtal::Orientation WaveShape::orientation(const RealPoint& aPoint) const
        {
            double x = aPoint[0];
            double y = aPoint[1];

            if(y<0) y=-y;

            if( yMap(y) < f(xMap(x),minHeight) )
            {
                return DGtal::Orientation::INSIDE;
            }else if (yMap(y) > f(xMap(x),minHeight))
            {
                return DGtal::Orientation::OUTSIDE;
            }else
            {
                return DGtal::Orientation::ON;
            }
        }


        double WaveShape::f(double x,double minHeight) const
        {
            double PI = 3.14159265359;
            return ( 1+sin(PI/2.0*sqrt(x)) )/(1+sqrt(x)) + minHeight;
        }

        WaveShape::LinearMap WaveShape::linearMap(double minValue, double maxValue, double mapMin, double mapMax)
        {
            double m = minValue;
            double M = maxValue;

            double w = mapMin;
            double W = mapMax;


            return [m,M,w,W](double t){ return w + (W-w)/(M-m)*(t-m); };
        }

    }
}