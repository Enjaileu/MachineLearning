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
float hypothesis(float x, float t0, float t1) {
	return t1 * x + t0;
}


float sum(int m, int x, map<int, float>& content, float t0, float t1) {
	double sum{ 0.0 };
	for (int i = 1; i <= m; i++) {
		float hypo = hypothesis(float(x), t0, t1);
		float result{ content[x] };
		double it{ pow(hypo - result, 2) };
		sum += it;
	}
	return sum;
}

float sumt0(int m, int x, map<int, float>& content, float t0, float t1) {
	double sum{ 0.0 };
	for (int i = 1; i <= m; i++) {
		float hypo{ hypothesis(float(x), t0, t1) };
		float result{ content[x] };
		double it{ hypo - result };
		sum += it;
	}
	return sum;
}

float sumt1(int m, int x, map<int, float>& content, float t0, float t1) {
	double sum{ 0.0 };
	for (int i = 1; i <= m; i++) {
		float hypo{ hypothesis(float(x), t0, t1) };
		float result{ content[x] };
		double it{ (hypo - result)*hypo };
		sum += it;
	}
	return sum;

}

float cost(int m, float x, map<int, float>& content, float t0, float t1 ) {
	double cost{ (1.f / (2.f * m)) * sum(m, x, content, t0, t1) };
	return cost;
}


void gradientT0(float &t0, float &t1, float alpha, map<int, float> &content, int itNb) {
	cout << "init : " << t0 << " - " << t1 << endl;
	float t0b{ t0 };
	float t1b{ t1 }; 
	float temp0{ t0 - 1 };
	float temp1{ t1 - 1 };
	int m{ 1 };
	int x{ itNb };
	while (abs(temp0 - t0) > 0.001 || abs(temp1 -1) > 0.001) {
		cout << "iteration " << m << " ; t0 = " << t0 << " ; t1 = " << t1 << endl;
		temp0 = t0 - alpha * (1 / m) * cost(m, x, content, t0, t1);
		temp1 = t1 - alpha * (1 / m) * sumt1(m, x, content, t0, t1);
		float diff0 = abs(temp0 - t0);
		float diff1 = abs(temp1 - t1);
		cout << "iteration " << m << " ; temp0 = " << temp0 << " ; temp1 = " << temp1 << endl;
		cout << "iteration " << m << " ; temp0 = " << temp0 << " ; t0 = " << t0 << endl;
		cout << "diff0 = " << diff0 << endl;
		cout << "diff1 = " << diff1 << endl;
		if (diff0 > 0.001 || diff1 > 0.001) {
			t0 = temp0;
			t1 = temp1;
		}
		m++;
	}
}


int main() {
	cout << "Main.cpp executed." << endl;

	string filePath{ "./ressources/test.csv" };

	map<int, float> content{ FileManagement::returnAsIF(filePath) };

	int x = 1;
	float t0{ 0.f };
	float t1{ 0.f };

	cout << "##### ONE ITERATION #####" << endl;
	cout << "pour x = " + to_string(x) + ", en une iteration :" << endl;
	cout << "y vrai = " + to_string(content[x]) << endl;
	cout << "y hypothese = " + to_string(hypothesis(x, t0, t1)) << endl;
	cout << "cost = " + to_string(cost(1, x, content, t0, t1)) << endl;

	cout << "t0 = " << t0 << endl;
	cout << "t1 = " << t1 << endl;
	gradientT0(t0, t1, 0.1, content, x);
	cout << "t0 = " << t0 << endl;
	cout << "t1 = " << t1 << endl;


	// print datas
	cout << "######### DATA SET ########" << endl;
	for (const auto& elem : content)
	{
		std::cout << elem.first << " " << elem.second << endl;
	}
	
	return 0;
}