#include "DIPaCUS/base/Objects.h"

using namespace DIPaCUS::Objects;

DigitalRectangle::DigitalRectangle(DigitalSet &dsRect,
                                   Domain domain,
                                   Point bottomLeftCorner,
    unsigned int s1,
    unsigned int s2) {
    for (int w = 0; w < s1; ++w) {
        for (int h = 0; h < s2; ++h) {
        dsRect.insert(bottomLeftCorner + Point(w, h));
        }
    }
}