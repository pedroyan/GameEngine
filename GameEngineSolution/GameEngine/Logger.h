#pragma once
#include <string>

using std::string;

class Logger {
	public:
		static void LogError(string error);
	private:
		// N�o � possivel instanciar essa classe
		Logger();
};

