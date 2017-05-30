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
		// Não é possivel instanciar essa classe
		Logger();
		static ofstream myfile;
};

