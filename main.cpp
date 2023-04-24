#include <iostream>
#include "InputManager.h"
#include "OutputManager.h"

using namespace std;

int main()
{
	int w, h, testCount;

	cin >> w >> h;
	InputManager input(w, h);
	input.run();

	cin >> testCount;
	OutputManager output(testCount,input.getGraph());
	output.run();

	return 1;
}