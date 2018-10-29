#include <DGtal/io/boards/Board2D.h>
#include "Representation/data.h"

using namespace Test::Representation;

DigitalSet Intern::createSquareDS()
{
    NGon2D square(0,0,7,4,3.1415/4.0);
    DGtal::GaussDigitizer<Space,NGon2D> gd;
    gd.attach(square);
    gd.init(square.getLowerBound(),square.getUpperBound(),1.0);

    Domain squareDomain = Domain( square.getLowerBound(),square.getUpperBound() );
    DigitalSet squareDS( squareDomain );
    for(auto it=squareDomain.begin();it!=squareDomain.end();++it)
    {
        if(gd.operator()(*it)) squareDS.insert(*it);
    }

    DGtal::Board2D board;
    board << squareDS;
    board.saveEPS("ds.eps");

    return squareDS;
}

namespace Test
{
    namespace Representation
    {
        namespace Data
        {
            GrayscaleImageInstance giSquare(IMAGE_INPUT_PATH + "/square.pgm", 169);
            DigitalSet dsSquare= Intern::createSquareDS();
        }
    }
}
