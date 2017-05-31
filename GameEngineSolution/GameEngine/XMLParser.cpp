#include "XMLParser.h"
#include <fstream>
#include "StringLibrary.h"
#include "Logger.h"
#include "Game.h"
#include "Portal.h"

using std::ifstream;
XMLParser::XMLParser(string fileName) {
	tmx = loadTMXtoMemory(fileName);
}


XMLParser::~XMLParser() {
	free(tmx);
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

vector<GameObject*> XMLParser::LoadMapObjects() {
	xml_document<> doc;
	vector<GameObject*> vec;

	doc.parse<0>(tmx);
	auto mapNode = doc.first_node("map", 0U, true);

	xml_node<>* Node = mapNode->first_node("objectgroup");
	while (Node != nullptr) {
		Node = ParseObjectLayer(Node);
	}
	return vec;
}

xml_node<>* XMLParser::ParseObjectLayer(xml_node<>* objLayer) {
	auto ObjectNode = objLayer->first_node("object");
	if (ObjectNode == nullptr) {
		return objLayer->next_sibling(); //Caso não tenha Object
	}

	while (ObjectNode != nullptr) {
		Rect dimensions;
		float x, y, w, h;
		string objectType, id;

		dimensions.X = atof(ObjectNode->first_attribute("x")->value());
		dimensions.Y = atof(ObjectNode->first_attribute("y")->value());
		dimensions.W = atof(ObjectNode->first_attribute("width")->value());
		dimensions.H = atof(ObjectNode->first_attribute("height")->value());

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
		CreateMapObject(objectType, dimensions, properties);
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
		toReturn.emplace(std::make_pair(prop->first_attribute("name")->value(), prop->first_attribute("value")->value()));
		prop = prop->next_sibling();
	}

	return toReturn;
}

void XMLParser::CreateMapObject(string type, Rect dimensions, unordered_map<string, string> properties) {
	if (type == "portal") {
		Game::GetInstance().GetCurrentState().AddObject(new Portal(properties["Message"], dimensions));
	} else {
		Logger::LogError("Objeto " + type + " não suportado");
	}
}
