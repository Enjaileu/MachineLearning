#include "FileManagement.h"

#include <fstream>
#include <sstream>
#include <ctype.h>
#include <iostream>

using namespace std;

vector<pair<int, double>> FileManagement::returnAsVec(string filePathP)
{
	cout << "DATA READ ################################################" << endl;
	vector<pair<int, double>>  content;

	// open stream
	ifstream stream{ filePathP };
	if (stream) {
		string line;
		string delim = ",";
		//for each line
		while (getline(stream, line)) {

			// if it's numbers
			char c{ line[0] };
			if (isdigit(c)) {

				// change content
				size_t pos{ 0 };
				string token1;
				while ((pos = line.find(delim)) != std::string::npos) {
					token1 = line.substr(0, pos);
					line.erase(0, pos + delim.length());
				}
				pair<int, double> pair0( stoi(token1), stod(line) );
				content.push_back(pair0);

			}
		}
	}
	else {
		cout << "No file in this directory [" + filePathP + "]" << endl;
	}
	stream.close();


	return content;
}
