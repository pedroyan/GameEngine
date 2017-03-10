#include "Logger.h"
#include <iostream>
#include <fstream>

using std::string;
using std::ofstream;

void Logger::LogError(string error) {
	ofstream myfile;
	myfile.open("ErrorDump.txt");
	myfile << error;
	myfile.close();
}

Logger::Logger() {
}

