# Presentation ![Continuous integration](https://travis-ci.com/danoan/DIPaCUS.svg?branch=master)

DIPaCUS is a collection of digital image processing 
functions built on the top of the DGtal library. 
This library is part
of the project [BTools](https://github.com/danoan/BTools), developped to
support the publication [1].

DIPaCUS is composed of three modules. Each model 
depends only of those above it.

1. **Base**: Creation of digital shapes and 
conversion between different representations of
images and digital sets.
2.  **Components**: Set of six packages containing
functions to work with Morphology, SetOperations and 
many other common tasks.
3. **Derivates**: Collection of complex tasks that
demands one or more components' function.


[1] Antunes, D., Lachaud, J.O., Talbot H.: Digital 
 curvature evolution model for image segmentation. In:
 Couprie, M., Cousty, J., Kenmochi, Y., Mustafa, N. (eds.) 
 Discrete Geometry for Computer Imagery. pp 15-26. Springer
 International Publishing, Cham (2019).

# Dependencies

1. [libboost1.66.0-dev](https://www.boost.org/users/history/version_1_66_0.html)
2. [opencv-3.3.0](https://opencv.org/releases.html)
3. [eigen-3.36](http://eigen.tuxfamily.org/index.php?title=Main_Page)
4. [DGtal1.1](https://dgtal.org/download/)

# Installation
```
mkdir build
cd build
cmake ..
(ccmake ..) - environment variables configuration
make install
```

# How to use
Check the code in lab/test
