#include "DIPaCUS/base/Shapes.h"

namespace DIPaCUS
{
    Shapes::DigitalSet Shapes::NGon(double h,
                                    double x0,
                                    double y0,
                                    double radius,
                                    int sides,
                                    double rotation)
    {
        typedef DGtal::Z2i::Space Space;
        DGtal::NGon2D<Space> ngon(x0,y0,radius,sides,rotation);
        return digitizeShape(ngon,h);
    }

    Shapes::DigitalSet Shapes::square(double h,
                                      double x0,
                                      double y0,
                                      double radius,
                                      double rotation)
    {
        return NGon(h,x0,y0,radius,4,rotation);
    }

    Shapes::DigitalSet Shapes::triangle(double h,
                                        double x0,
                                        double y0,
                                        double radius,
                                        double rotation)
    {
        return NGon(h,x0,y0,radius,3,rotation);
    }

    Shapes::DigitalSet Shapes::ball(double h,
                                    double x0,
                                    double y0,
                                    double radius)
    {
        typedef DGtal::Z2i::Space Space;
        DGtal::Ball2D<Space> ball(x0,y0,radius);
        return digitizeShape(ball,h);
    }

    Shapes::DigitalSet Shapes::flower(double h,
                                      double x0,
                                      double y0,
                                      double radius,
                                      double smallRadius,
                                      int k,
                                      double rotation)
    {
        typedef DGtal::Z2i::Space Space;
        DGtal::AccFlower2D<Space> flower(x0,y0,radius,smallRadius,k,rotation);
        return digitizeShape(flower,h);
    }

    Shapes::DigitalSet Shapes::ellipse(double h,
                                       double x0,
                                       double y0,
                                       double largerRadius,
                                       double smallerRadius,
                                       double rotation)
    {
        typedef DGtal::Z2i::Space Space;
        DGtal::Ellipse2D<Space> ellipse(x0,y0,largerRadius,smallerRadius,rotation);
        return digitizeShape(ellipse,h);
    }

    Shapes::DigitalSet Shapes::wave(double h,
                                    double maxX,
                                    double maxWidth,
                                    double maxHeight,
                                    double minHeight)
    {
        WaveShape wave(maxX,maxWidth,maxHeight,minHeight);
        return digitizeShape(wave,h);
    }

    Shapes::DigitalSet Shapes::bean(double h, double x, double y, double k)
    {
   	BeanShape bean(x,y,k);
	return digitizeShape(bean,h);
    }
}

