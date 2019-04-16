#include "data.h"

namespace DIPaCUS{ namespace Test{ namespace Misc{ namespace Data{

    Image2D square = DGtal::GenericReader<Image2D>::import(IMAGE_INPUT_PATH + "/square.pgm");
    Image2D squareConcavity = DGtal::GenericReader<Image2D>::import(IMAGE_INPUT_PATH + "/square_one_pixel_concavity.pgm");
    Image2D squareHole = DGtal::GenericReader<Image2D>::import(IMAGE_INPUT_PATH + "/square_potential_hole.pgm");
    Image2D squareShorts = DGtal::GenericReader<Image2D>::import(IMAGE_INPUT_PATH + "/square_shorts.pgm");

}}}}