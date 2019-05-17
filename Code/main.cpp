#include <iostream>
#include <algorithm>
#include <Windows.h>
#include <vector>
#include <utility>
#include <crtdbg.h>

using namespace std;

typedef pair<double, double> Point;
typedef vector<Point> Points;
typedef void(*PSeparateLayer)(Points *, Points *);

int main(int argc, char** argv) {
	if (argc < 2) return 0;

	PSeparateLayer SeparateLayerFunc = nullptr;
	HMODULE hModule = nullptr;
	if ((hModule = LoadLibrary("ConvexLayers.dll")) == nullptr ||
		(SeparateLayerFunc = (PSeparateLayer)GetProcAddress(hModule, "SeparateLayer")) == nullptr)
	{
		cout << "DLL import error.\n";
		return 1;
	}	

	Points points;
	Points layer;

	int points_N = atoi(argv[1]);
	if (argc != points_N * 2 + 2) {
		cout << "Input error.\n"; 
		return 1;
	}

	for (int i = 2; i < points_N * 2 + 2;) {
		points.emplace_back(atoi(argv[i++]), atoi(argv[i++]));
	}

	SeparateLayerFunc(&points, &layer);
	for (int i = 0; i < (int)layer.size(); i++) {
		cout << layer[i].first << ", " << layer[i].second << ";\n";
	}

	while (true){
		layer.clear();
		SeparateLayerFunc(&points, &layer);
		if (layer.size() == 0) break;

		for (int i = 0; i < (int)layer.size(); i++){
			cout << layer[i].first << ", " << layer[i].second << ";\n";
		}
		cout << "---\n";
	}
    /*
	BOOL b = FreeLibrary(hModule);
	if (b != TRUE) return 1;*/
	
	//system("pause");
	return 0;
}

/*
19
-1 -3
3 -2
1 -2
-1 -2
3 -1
1 -1
-1 0
7 1
0 1
2 1
1 1
5 2
2 2
-1 2
3 3
-2 3
2 4
1 5
5 6
*/