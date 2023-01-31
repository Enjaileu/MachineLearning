#include <iostream>
#include <map>
#include <math.h>

#include "FileManagement.h"


using namespace std;

/// <summary>
/// calculates the predicted values (or predicted targets) for a given set of inputs and thetas.
/// </summary>
/// <param name="x">param x : inputs(feature values) - Numpy array of floats</param>
/// <param name="t0">param theta_0 : intercept - float</param>
/// <param name="t1">param theta_1 : slope - float</param>
/// <returns>predicted targets - Numpy array of floats</returns>
float hypothesis(float x, float t0=0, float t1=0) {
	return t1 * x + t0;
}


float sum(int m, int x, float result) {
	float sum{ 0 };
	for (int i = 1; i <= m; i++) {
		float hypo{ hypothesis(float(x), 0, 0) };
		float it{ pow(5.7) };
		sum += it;
	}
	return sum;
}

float cost(int m, float x,  map<int, float> &content) {
	float vResult{ content[x] };
	float cost{ (1.f / 2.f * m) * sum(m, x, vResult) };

	return cost;
}



int main() {
	cout << "Main.cpp executed." << endl;

	string filePath{ "./ressources/test.csv" };

	map<int, float> content{ FileManagement::returnAsIF(filePath) };

	int x = 15;

	cout << "pour x = " + to_string(x) + ", en une iteration :" << endl;
	cout << "y vrai = " + to_string(content[x]) << endl;
	cout << "y hypothese = " + to_string(hypothesis(x)) << endl;
	cout << "cost = " + to_string(cost(1, x, content)) << endl;

	float alpha = 0.1;
	float tempT0 = 0;

	// print datas
	/*
	for (const auto& elem : content)
	{
		std::cout << elem.first << " " << elem.second << endl;
	}
	*/
	return 0;
}