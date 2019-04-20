
#!/bin/sh

$SCRIPT_BEGIN

#############################
#     cmake
#############################
#Build directory
cd "$BUILD_DIR"

# Cmake
echo "Using C++ = $CXXCOMPILER"
cmake "$SRC_DIR" -DCMAKE_PREFIX_PATH="${DEPS_DIR}" -DCMAKE_INSTALL_PREFIX="$DEPS_DIR" \
-DBOOST_LIBS_DIR="${DEPS_DIR}/lib" -DBUILD_TESTS="ON"

make -j $BJOBS
make install

$SCRIPT_END
