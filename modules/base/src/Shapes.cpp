#include "DIPaCUS/base/Shapes.h"

namespace DIPaCUS
{
    Shapes::DigitalSet Shapes::NGon(double h,
                                    int x0,
                                    int y0,
                                    double radius,
                                    int sides,
                                    double rotation)
    {
        typedef DGtal::Z2i::Space Space;
        DGtal::NGon2D<Space> ngon(x0,y0,radius,sides,rotation);
        return digitizeShape(ngon,h);
    }

    Shapes::DigitalSet Shapes::square(double h,
                                      int x0,
                                      int y0,
                                      double radius,
                                      double rotation)
    {
        return NGon(h,x0,y0,radius,4,rotation);
    }

    Shapes::DigitalSet Shapes::triangle(double h,
                                        int x0,
                                        int y0,
                                        double radius,
                                        double rotation)
    {
        return NGon(h,x0,y0,radius,3,rotation);
    }

    Shapes::DigitalSet Shapes::ball(double h,
                                    int x0,
                                    int y0,
                                    double radius)
    {
        typedef DGtal::Z2i::Space Space;
        DGtal::Ball2D<Space> ball(x0,y0,radius);
        return digitizeShape(ball,h);
    }

    Shapes::DigitalSet Shapes::flower(double h,
                                      int x0,
                                      int y0,
                                      double radius,
                                      double smallradius,
                                      int k,
                                      double rotation)
    {
        typedef DGtal::Z2i::Space Space;
        DGtal::AccFlower2D<Space> flower(x0,y0,radius,smallradius,k,rotation);
        return digitizeShape(flower,h);
    }
}

