#ifndef WORMY_H
#define WORMY_H

#ifndef NDEBUG
#include <press.h>
#define logger(...) press::writeln(__VA_ARGS__)
#else
#define logger(...)
#endif

#include <random>
#include <time.h>

inline struct random_global_object
{
	random_global_object() : g(time(NULL)) {}
	std::mt19937 g;

	float operator()(float low, float high)
	{
		return std::uniform_real_distribution<float>(low, high)(g);
	}

	int operator()(int low, int high)
	{
		return std::uniform_int_distribution<int>(low, high)(g);
	}
} random;

#include <win.h>
#include <Entity.h>
#include <Renderer.h>
#include <World.h>

#endif
