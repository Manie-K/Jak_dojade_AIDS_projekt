#include <iostream>
#include "InputManager.h"
#include "OutputManager.h"

using namespace std;

int main()
{
	int w, h, testCount;
	clock_t begin, end;

	cin >> w >> h;

	begin = clock();
	InputManager input(w, h);
	input.run();
	end = clock();

	double inputTime = double(end - begin) / CLOCKS_PER_SEC;
	

	cout << "\n\n\n";
	cout << "Input time: " << inputTime << '\n';

	cin >> testCount;
	begin = clock();
	OutputManager output(testCount,input.getGraph());
	output.run();
	end = clock();

	double outputTime = double(end - begin) / CLOCKS_PER_SEC;

	cout << "\n\n\n";
	cout << "Output time: " << outputTime << '\n';

	return 1;
}