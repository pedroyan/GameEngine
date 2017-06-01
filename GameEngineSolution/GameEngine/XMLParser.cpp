#include "XMLParser.h"
#include <fstream>
#include "StringLibrary.h"
#include "Logger.h"
#include "Game.h"
#include "Portal.h"
#include "FileLibrary.h"

using std::ifstream;
XMLParser::XMLParser(string fileName) {
	tmx = loadTMXtoMemory(fileName);
	if (tmx == nullptr) {
		throw std::exception();
	}
}


XMLParser::~XMLParser() {
	free(tmx);
}

char * XMLParser::loadTMXtoMemory(string fileName) {
	ifstream file;
	string outError;
	if (!FileLibrary::VerifyFile(fileName.c_str(), "tmx", "Engine aceita somente formato TMX como mapa", &file, outError)) {
		Logger::LogError(outError);
		return nullptr;
	}

	string line;
	string input_TMX;
	while (getline(file, line))
		input_TMX += line + "\n";

	char* chr = _strdup(input_TMX.c_str());
	return chr;
}

vector<GameObject*> XMLParser::LoadMapObjects() {
	xml_document<> doc;
	vector<GameObject*> vec;

	doc.parse<0>(tmx);
	auto mapNode = doc.first_node("map", 0U, true);

	xml_node<>* Node = mapNode->first_node("objectgroup");
	while (Node != nullptr) {
		Node = ParseObjectLayer(Node, vec);
	}

	return vec;
}

char * XMLParser::GetStoredTmx() {
	return tmx;
}

xml_node<>* XMLParser::ParseObjectLayer(xml_node<>* objLayer, vector<GameObject*>& objectsToAdd) {
	auto ObjectNode = objLayer->first_node("object");
	if (ObjectNode == nullptr) {
		return objLayer->next_sibling(); //Caso não tenha Object
	}

	while (ObjectNode != nullptr) {
		Rect dimensions;
		string objectType, id;

		dimensions.X = atof(ObjectNode->first_attribute("x")->value());
		dimensions.Y = atof(ObjectNode->first_attribute("y")->value());

		auto widthAtt = ObjectNode->first_attribute("width");
		dimensions.W = widthAtt != nullptr ? atof(widthAtt->value()) : 0;
		auto heightAtt = ObjectNode->first_attribute("height");
		dimensions.H = heightAtt != nullptr ? atof(heightAtt->value()) : 0;

		id = ObjectNode->first_attribute("id")->value();
		auto typeAttribute = ObjectNode->first_attribute("type");

		if (typeAttribute == nullptr) {
			Logger::LogError("WARNING: Objeto de id" + id + " sem tipo");
			return objLayer->next_sibling();
		}
		objectType = StringLibrary::ToLower(typeAttribute->value());
		auto properties = GetObjectProperties(ObjectNode);

		//new o objeto louco passando o dicionario de propriedades como parametro
		//insere esse new louco no object array do currentState
		//printf("damn son");
		auto obj = CreateMapObject(objectType, dimensions, properties);
		if (obj!=nullptr) {
			objectsToAdd.push_back(obj);
		}
		ObjectNode = ObjectNode->next_sibling();
	}

	return objLayer->next_sibling();
}

unordered_map<string, string> XMLParser::GetObjectProperties(xml_node<>* objectNode) {
	unordered_map<string, string> toReturn;

	auto propertiesNode = objectNode->first_node("properties");
	if (propertiesNode == nullptr) {
		return toReturn;
	}

	auto prop = propertiesNode->first_node();
	while (prop != nullptr) {
		auto valueAtrib = prop->first_attribute("value");
		string value = valueAtrib == nullptr ? prop->value() : valueAtrib->value();
		toReturn.emplace(std::make_pair(prop->first_attribute("name")->value(), value));
		prop = prop->next_sibling();
	}

	return toReturn;
}

GameObject* XMLParser::CreateMapObject(string type, Rect dimensions, unordered_map<string, string> properties) {
	if (type == "portal") {
		return new Portal(properties["Message"], dimensions);
	} else {
		Logger::LogError("Objeto " + type + " não suportado");
		return nullptr;
	}
}
