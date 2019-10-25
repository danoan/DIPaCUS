#include "DIPaCUS/base/Shapes.h"

namespace DIPaCUS
{
    template<typename TShape>
    Shapes::DigitalSet Shapes::digitizeShape(const TShape &shape, double h)
    {
        BOOST_CONCEPT_ASSERT(( DGtal::concepts::CEuclideanBoundedShape<TShape> ));

        typedef DGtal::Z2i::Space Space;
        typedef DGtal::Z2i::Domain Domain;
        typedef DGtal::Z2i::Point Point;


        DGtal::GaussDigitizer<Space,TShape> gd;
        gd.attach(shape);
        gd.init(shape.getLowerBound(), shape.getUpperBound(),h);

        Domain domain(gd.getDomain().lowerBound() - Point(1,1),gd.getDomain().upperBound() + Point(1,1));
        DigitalSet output(domain);
        DGtal::Shapes<Domain>::digitalShaper(output,gd);

        return output;

    }
}