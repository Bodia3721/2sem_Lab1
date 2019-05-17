#define CONVEX_LAYERS_EXPORTS 
#include "dllexports.h"

#include <math.h>
#include <iostream>

#include <Windows.h>

using namespace std;

int MostLeft(Points points){
	int most_left = 0;
	for (int i = 1; i < points.size(); i++) if (points[i].first < points[most_left].first ||
		points[i].first == points[most_left].first && points[i].second < points[most_left].second) most_left = i;
	return most_left;
}

double Angle(Point point1, Point angle, Point point2){
	double vector1_x = point1.first - angle.first, vector2_x = point2.first - angle.first;
	double vector1_y = point1.second - angle.second, vector2_y = point2.second - angle.second;
	double length1 = sqrt(vector1_x * vector1_x + vector1_y * vector1_y);
	double length2 = sqrt(vector2_x * vector2_x + vector2_y * vector2_y);
	return acos((vector1_x * vector2_x + vector1_y * vector2_y) / (length1 * length2));
}

double VectorLen(Point begin, Point end){
	double vector_x = end.first - begin.first;
	double vector_y = end.second - begin.second;
	return sqrt(vector_x * vector_x + vector_y *  vector_y);
}

double Angle(Point angle, Point point2){
	//first vector is (0,1)
	double vector2_x = point2.first - angle.first;
	double vector2_y = point2.second - angle.second;
	double length2 = sqrt(vector2_x * vector2_x + vector2_y * vector2_y);
	return acos((vector2_y) / (length2));
}

void SeparateLayer(Points *points, Points *layer){
	if ((*points).size() < 3) return;
	unsigned int most_left = MostLeft((*points));
	(*layer).push_back((*points)[most_left]);
	(*points).erase((*points).begin() + most_left);
	double etalon_angle = Angle((*layer)[0], (*points)[0]);
	double etalon_len = VectorLen((*layer)[0], (*points)[0]);
	int second_layer_point = 0;
	for (int i = 1; i < (*points).size(); i++){
		double angle = Angle((*layer)[0], (*points)[i]);
		double len = VectorLen((*layer)[0], (*points)[i]);
		if (etalon_angle < angle || etalon_angle == angle && len < etalon_len){
			etalon_angle = angle;
			etalon_len = len;
			second_layer_point = i;
		}
	}
	(*layer).push_back((*points)[second_layer_point]);
	(*points).erase((*points).begin() + second_layer_point);
	while (true){
		etalon_angle = 0;
		int next_layer_point = -1;
		for (int i = 0; i < (*points).size(); i++){
			double angle = Angle((*layer)[(*layer).size() - 2], (*layer)[(*layer).size() - 1], (*points)[i]);
			double len = VectorLen((*layer)[(*layer).size() - 1], (*points)[i]);
			if (etalon_angle < angle || etalon_angle == angle && len < etalon_len){
				etalon_angle = angle;
				etalon_len = len;
				next_layer_point = i;
			}
		}
		if (next_layer_point == -1) break;
		if (Angle((*layer)[(*layer).size() - 2], (*layer)[(*layer).size() - 1], (*layer)[0]) > etalon_angle) break;
		(*layer).push_back((*points)[next_layer_point]);
		(*points).erase((*points).begin() + next_layer_point);
	}
}


BOOL APIENTRY DllMain(HANDLE hModule, DWORD  fdwReason, LPVOID lpReserved)
{
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		//cout << "ConvexLayers.dll succesfully loaded!\n";
		break;
	case DLL_THREAD_ATTACH:
		//cout << "ConvexLayers.dll succesfully loaded!\n";
		break;
	case DLL_THREAD_DETACH:
		//cout << "ConvexLayers.dll succesfully detached!\n";
		break;
	case DLL_PROCESS_DETACH:
		//cout << "ConvexLayers.dll succesfully detached!\n";
		break;
	}
	return TRUE;
}

