#include <iostream>
#include <vector>
#include <utility>
#include <math.h>

#include "FileManagement.h"


using namespace std;


float hypothesis(float x, float t0, float t1) {
	return t1 * x + t0;
}

double cost(vector<pair<int, double>>& content, float t0, float t1 ) {

	double totalCost{ 0.f };

	for (auto i = content.begin(); i != content.end(); i++) {
		float hypo = hypothesis(float(i->first), t0, t1);
		double cost{ pow(hypo - i->second, 2.f) };
		totalCost += cost;
	}

	double averageCost{ totalCost / content.size() };
	return averageCost;
}

void gradient(vector<pair<int, double>>& content, float& t0, float& t1, float step) {

	float totalError0{ 0.f };
	float totalError1{ 0.f };
	int dataSize{ int(content.size()) };

	//loop training sur notre dataset
	for (auto i = content.begin(); i != content.end(); i++) {
		//hypothese
		float hypo{ hypothesis(i->first, t0, t1) };
		// differences
		const double errorDiff0{hypo - i->second };
		const double errorDiff1 =  (hypo - i->second) * i->first;
		//on augmente les totaux
		totalError0 += errorDiff0;
		totalError1 += errorDiff1;
	}

	// assigne nouvelles valeurs aux thetas
	float temp0 = (step / dataSize) * totalError0;
	float temp1 = (step / dataSize) * totalError1;
	t0 -= temp0;
	t1 -= temp1;
}


void findThetas(float &t0, float &t1, float stop, float step, vector<pair<int, double>> &content) {
	int iter{ 1 };
	int dataSize{ int(content.size()) };
	double diff;
	
	do {
		cout << "###############   Iteration " << iter << " ############################" << endl;
		cout << "Theta0 = " << t0 << " ; Theta1 = " << t1 << endl;

		double initialCost{cost(content, t0, t1)};


		cout << "Initial cost = " << initialCost << endl;

		gradient(content, t0, t1, step);

		double newCost {cost(content, t0, t1) };

		cout << "--- GRADIENT ---" << endl;
		cout << "Theta0 = " << t0 << " ; Theta1 = " << t1 << endl;
		cout << "New cost = " << newCost << endl;
		cout << endl;
		iter++;

		diff = initialCost - newCost;
	} while (diff>stop);	
}


int main() {

	//on récupere les datas pour les mettre dans une map
	string filePath{ "./ressources/test.csv" };

	vector<pair<int, double>> content{ FileManagement::returnAsVec(filePath) };

	int x = 8;
	float t0{ 0.f };
	float t1{ 0.f };

	cout << endl;
	cout << "########## START GRADIENT ##########" << endl;
	findThetas(t0, t1, 0.001, 0.0001, content);
	

	// print datas
	/*
	cout << endl;
	cout << "######### DATA SET ########" << endl;
	for (auto i = content.begin(); i != content.end(); i++)
	{
		std::cout << i->first << " " << i->second << endl;
	}
	*/
	return 0;
}