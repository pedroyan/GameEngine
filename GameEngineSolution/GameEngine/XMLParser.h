#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "RapidXML\rapidxml.hpp"
#include "GameObject.h"

using std::string;
using std::vector;
using std::unordered_map;
using namespace rapidxml;
class XMLParser {
	public:
		XMLParser(string fileName);
		~XMLParser();

		/// <summary>
		/// Carrega o arquivo XML para a memória.
		/// </summary>
		/// <param name="fileName">Nome do arquivo a ser carregado</param>
		/// <returns>string contendo o XML carregado</returns>
		static char* loadTMXtoMemory(string fileName);

		/// <summary>
		/// Obtem os objetos a partir do TMX
		/// </summary>
		/// <returns>vetor de objetos</returns>
		vector<GameObject*> LoadMapObjects();


	private:
		char* tmx;

		/// <summary>
		/// Faz o parsing da layer de objetos
		/// </summary>
		/// <param name="objLayer">XML contendo a layer</param>
		/// <param name="objectsToAdd">Vetor de objetos para armazenas os gameObjects lidos</param>
		/// <returns></returns>
		xml_node<>* ParseObjectLayer(xml_node<>* objLayer, vector<GameObject*>& objectsToAdd);

		/// <summary>
		/// Extrai as propriedades do objeto
		/// </summary>
		/// <param name="objectNode">Nó xml do objeto</param>
		/// <returns>propriedades do objeto extraidas</returns>
		unordered_map<string, string> GetObjectProperties(xml_node<>* objectNode);

		/// <summary>
		/// Cria um objeto gerado no TMX
		/// </summary>
		/// <param name="type">Tipo do objeto</param>
		/// <param name="dimensions">dimensões do objeto</param>
		/// <param name="properties">propriedades do objeto</param>
		/// <returns>Objeto alocado</returns>
		GameObject* CreateMapObject(string type, Rect dimensions, unordered_map<string, string> properties);
};

