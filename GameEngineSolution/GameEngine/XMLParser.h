#pragma once
#include <string>
using std::string;

class XMLParser {
	public:
		XMLParser();
		~XMLParser();

		/// <summary>
		/// Carrega o arquivo XML para a memória.
		/// </summary>
		/// <param name="fileName">Nome do arquivo a ser carregado</param>
		/// <returns>string contendo o XML carregado</returns>
		static char* loadTMXtoMemory(string fileName);
};

