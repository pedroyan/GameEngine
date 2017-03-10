#pragma once
#include <string>

using std::string;

class Logger {
	public:
		static void LogError(string error);
	private:
		// Não é possivel instanciar essa classe
		Logger();
};

