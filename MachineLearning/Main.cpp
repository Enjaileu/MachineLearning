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

double cost(map<int, float>& content, float t0, float t1 ) {

	double totalCost{ 0.f };

	for (auto i = content.begin(); i != content.end(); i++) {
		float hypo = hypothesis(float(i->first), t0, t1);
		double cost{ pow(hypo - i->second, 2.f) };
		totalCost += cost;
	}

	double averageCost{ totalCost / content.size() };
	return averageCost;
}

void gradient(map<int, float>& content, float& t0, float& t1, float step) {
	/*
	float totalErrorDiff0{0.f};
	float totalErrorDiff1{0.f};
	int dataSize{ int(content.size()) };

	for (auto i = content.begin(); i != content.end(); i++) {
		float hypoY{ hypothesis(i->first, t0, t1) };
		const float errorDiff0{ hypoY - i->second };
		totalErrorDiff0 += errorDiff0;
		const float errorDiff1{ (hypoY - i->second) * i->first };
		totalErrorDiff1 += errorDiff1;
	}

	float temp0 = (step / dataSize) * totalErrorDiff0;
	float temp1 = (step / dataSize) * totalErrorDiff1;

	t0 -= temp0;
	t1 -= temp1;

	*/

	//float totalError0{ 0.f };
	float totalError1{ 0.f };
	int dataSize{ int(content.size()) };

	for (auto i = content.begin(); i != content.end(); i++) {
		float hypo{ hypothesis(i->first, t0, t1) };
		//const float errorDiff{ hypo - i->second };
		const float errorDiff1 =  (hypo - i->second) * i->first;
		//totalError0 += errorDiff;
		totalError1 += errorDiff1;
	}

	//float temp0 = (step / dataSize) * totalError0;
	float temp1 = (step / dataSize) * totalError1;
	//t0 -= temp0;
	t1 -= temp1;
}


void findThetas(float &t0, float &t1, float stop, float step, map<int, float> &content) {
	int iter{ 1 };
	int dataSize{ int(content.size()) };
	float diff;

	
	do {
		cout << "###############   Iteration " << iter << " ############################" << endl;
		cout << "Theta0 = " << t0 << " ; Theta1 = " << t1 << endl;

		double initialCost{cost(content, t0, t1)};


		cout << "Initial cost = " << initialCost << endl;

		gradient(content, t0, t1, step);

		double newCost{ cost(content, t0, t1) };

		cout << "--- GRADIENT ---" << endl;
		cout << "Theta0 = " << t0 << " ; Theta1 = " << t1 << endl;
		cout << "New cost = " << newCost << endl;
		cout << endl;
		iter++;
	} while (iter <10);
	//while(diff > stop
	
}

int main() {

	string filePath{ "./ressources/test.csv" };

	map<int, float> content{ FileManagement::returnAsIF(filePath) };

	int x = 8;
	float t0{ 0.f };
	float t1{ 0.f };


	cout << "##### FIRST HYPOTHESIS #####" << endl;
	cout << "For x = " + to_string(x) + ", theta0 and theta1 = " << t0 << endl;
	cout << "y in database = " + to_string(content[x]) << endl;
	cout << "y hypothesis = " + to_string(hypothesis(x, t0, t1)) << endl;
	cout << "cost = " + to_string(cost(content, t0, t1)) << endl;

	cout << endl;
	cout << "########## START GRADIENT ##########" << endl;
	findThetas(t0, t1, 0.001, 0.001, content);

	// print datas
	cout << endl;
	cout << "######### DATA SET ########" << endl;
	for (const auto& elem : content)
	{
		std::cout << elem.first << " " << elem.second << endl;
	}
	
	return 0;
}