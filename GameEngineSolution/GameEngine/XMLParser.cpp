#include "XMLParser.h"
#include <fstream>

using std::ifstream;

XMLParser::XMLParser() {

}


XMLParser::~XMLParser() {
}

char * XMLParser::loadTMXtoMemory(string fileName) {
	ifstream file(fileName);

	if (!file.is_open()) {
		printf("Nao foi possivel abrir o arquivo %s", fileName.c_str());
		throw new std::exception();
		exit(0);
	}

	string line;
	string input_TMX;
	while (getline(file, line))
		input_TMX += line + "\n";

	char* chr = _strdup(input_TMX.c_str());
	return chr;
}
