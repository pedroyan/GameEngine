#pragma once
#include <string>
#include <iostream>
#include <fstream>

using std::string;
using std::ofstream;

class Logger {
	public:
		static void LogError(string error);
	private:
		// N�o � possivel instanciar essa classe
		Logger();
		static ofstream myfile;
};

