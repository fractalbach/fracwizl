#ifndef GLOBAL_H
#define GLOBAL_H
#include <chrono>

const int g_defaultScreenWidth = 680;
const int g_defaultScreenHeight = 480;

double g_timeMs() {
	const auto p1 = std::chrono::system_clock::now();
	return double( std::chrono::duration_cast<std::chrono::milliseconds>(p1.time_since_epoch()).count() ) / 1000.0f;
}

#endif // #define GLOBAL_H