# Presentation ![Continuous integration](https://travis-ci.com/danoan/DIPaCUS.svg?branch=master)

DIPaCUS is a collection of digital image processing 
functions built on the top of the DGtal library.

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

# Dependencies

1. [libboost1.66.0-dev](https://www.boost.org/users/history/version_1_66_0.html)
2. [opencv-3.3.0](https://opencv.org/releases.html)
3. [eigen-3.36](http://eigen.tuxfamily.org/index.php?title=Main_Page)
4. [DGtal0.9](https://dgtal.org/download/)

# Installation
```
mkdir build
cd build
cmake ..
(ccmake ..) - environment variables configuration
make install
```
