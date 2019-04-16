#Presentation
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

#Dependencies

1. DGtal (>=0.8)
2. OpenCV (4.0.1)
3. Magick++ (>=6.0)
4. boost (>=1.69)
5. ccmake (>= 3.2)

#Installation
```
mkdir build
cd build
cmake ..
(ccmake ..) - environment variables configuration
make install
```