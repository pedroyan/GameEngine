#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "./RapidXML/rapidxml.hpp"
#include "GameObject.h"
#include <memory>

using std::string;
using std::vector;
using std::unordered_map;

using namespace rapidxml;
class XMLParser {
	public:
		XMLParser(string fileName);
		~XMLParser();

		

		/// <summary>
		/// Obtem os objetos a partir do TMX
		/// </summary>
		/// <returns>vetor de objetos</returns>
		vector<GameObject*>& GetMapObjects();

		/// <summary>
		/// Busca as dimensões do Tileset
		/// </summary>
		/// <param name="tileHeight">Endereço de memoria da variável que armazena a altura do tile</param>
		/// <param name="tileWidth">Endereco de memoria da variável que armazena a largura do tile</param>
		void GetTileDimensions(int* const tileHeight, int* const tileWidth);

		/// <summary>
		/// Retorna o mapnode
		/// IMPORTANTE: Não é necessário dar free no ponteiro retornado, uma vez
		/// que ele é liberado quando o parser for deletado
		/// </summary>
		/// <returns></returns>
		xml_node<char>*  GetMapNode();

		bool PlayerDefinedOnMap();

		float GetHordeZoom();
	private:
		//Variaveis que mantem o ciclo de vida do parser
		char* tmx;
		xml_document<> doc;
		xml_node<char>* mapnode;
		unordered_map<string, string> propertyTable;
		float zoomTo;

		bool hasPlayer;

		string fileName;
		vector<GameObject*> objectsParsed;
		int tileHeight,tileWidth;

		/// <summary>
		/// Carrega o arquivo XML para a memória.
		/// </summary>
		/// <param name="fileName">Nome do arquivo a ser carregado</param>
		/// <returns>string contendo o XML carregado</returns>
		void parseTMX(string fileName);


		/// <summary>
		/// Obtem os objetos a partir do TMX
		/// </summary>
		/// <returns>vetor de objetos</returns>
		void LoadMapObjects();

		
		void LoadTileDimensions();

		void LoadMapProperties();

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
		GameObject* CreateMapObject(string type, Rect dimensions, unordered_map<string, string>& properties);
};

