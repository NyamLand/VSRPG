#include "CSVReader.h"

CSVReader::CSVReader(fstream& stream):
SEPARATOR(DEFAULT_SEPARATOR),
QUOTE(DEFAULT_QUOTE_CHARACTER),
pstream(&stream)
{
}

CSVReader::CSVReader(fstream& stream, const char sep):
SEPARATOR(sep),
QUOTE(DEFAULT_QUOTE_CHARACTER),
pstream(&stream)
{
}

CSVReader::CSVReader(fstream& stream, const char sep, const char quo):
SEPARATOR(sep),
QUOTE(quo),
pstream(&stream)
{
}

CSVReader::~CSVReader(void)
{
}

int CSVReader::Read(vector<string>& tokens) {
	tokens.clear();

	string nextLine;
	if( GetNextLine(nextLine)<=0 ) {
		return -1;
	}
	Parse(nextLine, tokens);
	return 0;
}

int CSVReader::GetNextLine(string& line) {

	if( !pstream || pstream->eof() ) {
		return -1;
	}
	std::getline( *pstream, line );
	return (int)line.length();
}

int CSVReader::Parse(string& nextLine, vector<string>& tokens) {
	string token;
	bool interQuotes = false;
	do {
		if (interQuotes) {
			token += '\n';
			if (GetNextLine(nextLine)<0) {
				break;
			}
		}
		
		for (int i = 0; i < (int)nextLine.length(); i++) {

			char c = nextLine.at(i);
			if (c == QUOTE) {
               	if( interQuotes
               	    && (int)nextLine.length() > (i+1)
               	    && nextLine.at(i+1) == QUOTE ){
               		token += nextLine.at(i+1);
               		i++;
               	}else{
               		interQuotes = !interQuotes;
               		if(i>2 
               			&& nextLine.at(i-1) != SEPARATOR
               			&& (int)nextLine.length()>(i+1) 
               			&& nextLine.at(i+1) != SEPARATOR
               		){
               			token += c;
               		}
               	}
			} else if (c == SEPARATOR && !interQuotes) {
				tokens.push_back(token);
				token.clear();
			} else {
				token += c;
			}
		}
	} while (interQuotes);
	tokens.push_back(token);
	return 0;
}

/**
 * ファイルストリームをクローズします。
 * @return 0:正常 -1:異常
 */
int CSVReader::Close(void) {
	if(pstream) {
		pstream->close();
		pstream = NULL;
	}
	return 0;
}


int CSVReader::GetParam(string &status)
{
	//std::fstream r("DATA\\test.csv", std::ios::in);
	//if (!r.is_open())
	//{
	//	return -1;
	//}

	//CSVReader csv(r);
	//vector<string> tokens;
	//while (!csv.Read(tokens)) 
	//{
	//	for (unsigned int i = 0; i<tokens.size(); i++)
	//	{
	//		if (tokens[i].c_str() == status)
	//		{
	//			return std::atoi(tokens[i + 1].c_str());
	//		}
	//	}
	//}
	//csv.Close();
	return 0;
}
