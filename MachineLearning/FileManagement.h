#pragma once
#include <vector>
#include <string>
#include <utility>

class FileManagement {

public:
	static std::vector<std::pair<int, double>> returnAsVec(std::string filePathP);
};
