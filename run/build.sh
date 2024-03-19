echo "________________________________________"
echo "Build The Game                          "
echo "========================================"
echo "pwd=$(pwd)"


# Hexify Shaders
# xxd -i -c 256 -g 0 src/shaders/basic.vert > out/shaders/basic.vert

echo "Running Clang++"

mkdir -p out

clang++ \
	-std=c++17 \
	-fcolor-diagnostics \
	-fansi-escape-codes \
	-fstack-protector-all \
	-fsanitize=address \
	-g \
	-lSDL2 \
	-lGLEW \
	-framework OpenGL \
	src/main.cpp \
	-o out/fwizl.out

echo "Build Ended"

# cmake -B out -S src -D CMAKE_BUILD_TYPE=Debug \
# && cmake --build out