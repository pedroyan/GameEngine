#include "XMLParser.h"
#include <fstream>
#include "StringLibrary.h"
#include "Logger.h"
#include "Game.h"
#include "Portal.h"
#include "FileLibrary.h"
#include "Barrier.h"
#include "Player.h"
#include "Camera.h"

using std::ifstream;
XMLParser::XMLParser(string fileName) {
	parseTMX(fileName);
}


XMLParser::~XMLParser() {
	free(tmx);
}

vector<GameObject*>& XMLParser::GetMapObjects() {
	return objectsParsed;
}

void XMLParser::GetTileDimensions(int * const tileHeight, int * const tileWidth) {
	*tileHeight = this->tileHeight;
	*tileWidth = this->tileWidth;
}

xml_node<char>* XMLParser::GetMapNode() {
	return mapnode;
}

int XMLParser::GetPlayerLayer() {
	auto it = propertyTable.find("playerLayer");
	if (it == propertyTable.end()) {
		return 2;
	} else {
		return std::stoi(it->second);
	}
}

bool XMLParser::PlayerDefinedOnMap() {
	return hasPlayer;
}

float XMLParser::GetHordeZoom() {
	return zoomTo;
}

void XMLParser::parseTMX(string fileName) {
	ifstream file;
	string outError;
	this->fileName = fileName;

	if (!FileLibrary::VerifyFile(fileName.c_str(), "tmx", "Engine aceita somente formato TMX como mapa", &file, outError)) {
		Logger::LogError(outError);
		throw std::exception();
	}

	string line;
	string input_TMX;
	while (getline(file, line))
		input_TMX += line + "\n";

	tmx = StringLibrary::Strdup(input_TMX.c_str());
	doc.parse<0>(tmx);
	mapnode = doc.first_node("map", 0U, true);
	LoadMapObjects();
	LoadTileDimensions();
	LoadMapProperties();
}

void XMLParser::LoadMapObjects() {

	xml_node<>* Node = mapnode->first_node("objectgroup");
	while (Node != nullptr) {
		Node = ParseObjectLayer(Node, objectsParsed);
	}

}

void XMLParser::LoadTileDimensions() {
	auto tileSetNode = mapnode->first_node("tileset");

	if (tileSetNode == nullptr) {
		Logger::LogError("É obrigatório definir um tileset para o mapa " + fileName);
		throw std::exception();
	}

	this ->tileHeight = atoi(tileSetNode->first_attribute("tileheight")->value());
	this ->tileWidth = atoi(tileSetNode->first_attribute("tilewidth")->value());
}

void XMLParser::LoadMapProperties() {
	xml_node<>* Node = mapnode->first_node("properties");
	auto propNode = Node->first_node("property");
	while (propNode != nullptr) {
		auto keyAtrib = propNode->first_attribute("name");
		auto valueAtrib = propNode->first_attribute("value");
		string value = valueAtrib == nullptr ? propNode->value() : valueAtrib->value();
		propertyTable.emplace(std::make_pair(keyAtrib->value(), value));
		propNode = propNode->next_sibling();
	}
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

GameObject* XMLParser::CreateMapObject(string type, Rect dimensions, unordered_map<string, string>& properties) {
	if (type == "portal") {
		if (properties.find("Message") == properties.end()) {
			return new Portal(properties["NextMap"], properties["NextTileset"], dimensions);
		} else {
			return new Portal(properties["NextMap"], properties["NextTileset"], dimensions);
		}
	} else if (type == "playerspawn") {
		hasPlayer = true;
		auto player =  new Player(dimensions.X, dimensions.Y);
		Camera::Follow(player);
		return player;
	} else if (type == "barrier") {
		int hp;
		hp = properties.find("HP") == properties.end() ? 100 : stoi(properties["HP"]);
		return new Barrier(hp, dimensions);
	} else {
		Logger::LogError("Objeto " + type + " não suportado");
		return nullptr;
	}
}
