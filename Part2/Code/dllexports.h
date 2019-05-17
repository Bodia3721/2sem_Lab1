#include <utility>
#include <vector>
#ifndef CONVEX_LAYERS_H
#define CONVEX_LAYERS_H

#ifdef CONVEX_LAYERS_EXPORTS 
#define CONVEX_LAYERS_API __declspec(dllexport) 
#else
#define CONVEX_LAYERS_API __declspec(dllimport)
#endif

extern "C"{
typedef std::pair<double, double> CONVEX_LAYERS_API Point;
typedef std::vector<Point> CONVEX_LAYERS_API Points;

CONVEX_LAYERS_API void SeparateLayer(Points *points, Points *layer);
}

#endif