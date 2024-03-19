#ifndef LOADER_H
#define LOADER_H
#include <string>
#include <fstream>
#include <sstream>
namespace loader {

std::string loadFile( const char* path ) {
	std::ifstream f(path);
	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}

} // namespace loader
#endif // #ifndef LOADER_H