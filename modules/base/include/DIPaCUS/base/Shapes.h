#ifndef DIPACUS_BASE_SHAPES_H
#define DIPACUS_BASE_SHAPES_H

#include <boost/assert.hpp>

#include <DGtal/helpers/StdDefs.h>

#include <DGtal/shapes/GaussDigitizer.h>
#include <DGtal/shapes/Shapes.h>
#include <DGtal/shapes/parametric/NGon2D.h>
#include <DGtal/shapes/parametric/Ball2D.h>
#include <DGtal/shapes/parametric/AccFlower2D.h>
#include <DGtal/shapes/parametric/Ellipse2D.h>

#include "DIPaCUS/base/shapes/WaveShape.h"

namespace DIPaCUS
{
    /**
    * \brief Digitization of 2D euclidean shapes commonly used
     * during experiments
     *
     *
    * \author Daniel Martins Antunes
    * \version 0.1
    * \date 2018/11/24
    *
    */
    namespace Shapes
    {
        static double PI=3.1416;
        typedef DGtal::Z2i::DigitalSet DigitalSet;

        /**
         * \brief General Gauss digitization method.
         *
         *
         * @tparam TShape An euclidean bounded shape type
         * @param shape The euclidean bounded shape
         * @param h Grid step
         * @return Digitization of the euclidean shape
         */
        template<typename TShape>
        DigitalSet digitizeShape(const TShape& shape,
                                 double h);

        /**
         * /brief General digitization of 2D polygons.
         *
         *
         * @param h Grid Step
         * @param x0 Circumscribed circle center x-coordinate
         * @param y0 Circumscribed circle center y-coordinate
         * @param radius Radius of circumscribed circle
         * @param sides Number of polygon sides
         * @param rotation Rotation angle with respect to circunscrit polygon
         * @return Polygon digitization.
         */
        DigitalSet NGon(double h,
                        int x0,
                        int y0,
                        double radius,
                        int sides,
                        double rotation=0);


        /**
         * /brief Triangle digitization
         *
         * @param h Grid Step
         * @param x0 Circumscribed circle center x0 x-coordinate
         * @param y0 Circumscribed circle center y0 y-coordinate
         * @param radius Radius of circumscribed circle
         * @param rotation Rotation angle with respect to circunscrit polygon
         * @return Triangle digitization
         */
        DigitalSet triangle(double h=1.0,
                            int x0=0,
                            int y0=0,
                            double radius=10,
                            double rotation=7*PI/6);

        /**
         * /brief Square digitization
         *
         * @param h Grid Step
         * @param x0 Circumscribed circle center x-coordinate
         * @param y0 Circumscribed circle center y-coordinate
         * @param radius Radius of circumscribed circle
         * @param rotation Rotation angle with respect to circunscrit polygon
         * @return Square digitization
         */
        DigitalSet square(double h=1.0,
                          int x0=0,
                          int y0=0,
                          double radius=10,
                          double rotation=PI/4.0);

        /**
         * /brief Ball digitization
         *
         * @param h Grid Step
         * @param x0 Circumscribed circle center x-coordinate
         * @param y0 Circumscribed circle center y-coordinate
         * @param Ball radius
         * @return Ball digitization
         */
        DigitalSet ball(double h=1.0,
                        int x0=0,
                        int y0=0,
                        double radius=10);

        /**
         * /brief Flower digitization
         *
         * @param h Grid Step
         * @param x0 Circumscribed circle center x-coordinate
         * @param y0 Circumscribed circle center y-coordinate
         * @param radius
         * @param smallradius
         * @param k
         * @param rotation
         * @return Flower digitization
         */
        DigitalSet flower(double h=1.0,
                          int x0=0,
                          int y0=0,
                          double radius=10,
                          double smallRadius=5,
                          int k=3,
                          double rotation=0);

        /**
         * /brief Ellipse digitization
         *
         * @param h Grid Step
         * @param x0 Circumscribed circle center x-coordinate
         * @param y0 Circumscribed circle center y-coordinate
         * @param larger radius
         * @param smaller radius
         * @param rotation
         * @return Ellipse digitization
         */
        DigitalSet ellipse(double h=1.0,
                          int x0=0,
                          int y0=0,
                          double largerRadius=10,
                          double smallerRadius=5,
                          double rotation=0);


        /**
         * /brief Wave shape digitization
         * The wave shape is defined by a sinus function. It has various degrees of
         * convexity and non-convex regions.
         *
         * @param h Grid Step
         * @param maxWidth Domain width (also maximum value of x in function evaluation)
         * @param maxHeight Domain height
         * @param minHeight Controls the thickness of the shape
         * @return Wave shape digitization
         */
        DigitalSet wave(double h,
                        double maxWidth,
                        double maxHeight,
                        double minHeight);
    }
}

#include "Shapes.hpp"

#endif //DIPACUS_BASE_SHAPES_H
