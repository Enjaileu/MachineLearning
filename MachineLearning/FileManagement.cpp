#include "FileManagement.h"

#include <fstream>
#include <sstream>
#include <ctype.h>
#include <iostream>

using namespace std;

map<int, float> FileManagement::returnAsIF(string filePathP)
{
	map<int, float> content;

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
				content[stoi(token1)] = stof(line);
			}
		}
	}
	else {
		cout << "No file in this directory [" + filePathP + "]" << endl;
	}
	stream.close();


	return content;
}
