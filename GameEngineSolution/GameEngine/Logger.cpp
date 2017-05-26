#include "Logger.h"
#include <iostream>
#include <fstream>

using std::string;

ofstream Logger::myfile;

void Logger::LogError(string error) {
	if (!myfile.is_open()) {
		myfile.open("ErrorDump.txt");
	}
	myfile << error + "\n";
}

Logger::Logger() {
}

