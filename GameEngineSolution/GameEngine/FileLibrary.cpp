#include "FileLibrary.h"
#include "StringLibrary.h"

bool FileLibrary::VerifyFile(const char * fileName, const char * extension, const char * extensionErrorMessage, ifstream* stream, string& outError) {
	string fileNameS(fileName);
	size_t extensionIndex = fileNameS.find_last_of(".");
	outError = "";
	if (extensionIndex == string::npos) {
		outError = "O arquivo passado nao possui extensao. ";
		return false;
	}

	string fileExtension = StringLibrary::ToLower(fileNameS.substr(extensionIndex + 1));

	if (fileExtension != extension) {
		outError = string(extensionErrorMessage) + "\nExtensao do arquivo passado: " + fileExtension;
		return false;
	}

	stream->open(fileName, ifstream::in);
	if (!stream->is_open()) {
		outError = "O arquivo especificado " + fileNameS + " nao existe";
		return false;
	}

	return true;
}

string FileLibrary::GetNextLine(istream & stream){
	string formatedLine;
	std::getline(stream, formatedLine);
	return StringLibrary::RemoveExcessiveSpaces(formatedLine);
	
}

string FileLibrary::JumpForNextLine(vector<string> members, ifstream & fp){
	string line;
	FileLibrary leitor;
		do {
			line = leitor.GetNextLine(fp);
			StringLibrary::Tokenize(line, " ", members);
		} while (members.size() == 0);
	

	return line;
}

