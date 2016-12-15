
#pragma once

#include <string>
#include <vector>
#include <fstream>
using namespace std;

#define DEFAULT_SEPARATOR	','
#define DEFAULT_QUOTE_CHARACTER	'"'

class CSVReader
{
public:

	/**
	 * コンストラクタ
	 * @param stream ファイルストリーム
	 * @comment セパレータ(,), エンクオート(")
	 */
	CSVReader( fstream& stream );

	/**
	 * コンストラクタ
	 * @param stream ファイルストリーム
	 * @param sep セパレータ
 	 * @comment エンクオート(")
	 */
	CSVReader( fstream& stream, const char sep );

	/**
	 * コンストラクタ
	 * @param stream ファイルストリーム
	 * @param sep セパレータ
 	 * @param quo エンクオート
	 */
	CSVReader( fstream& stream, const char sep, const char quo );

	/**
	 * デストラクタ
	 */
	virtual ~CSVReader( void );

	/**
	 * CSVファイルを１行読み込んで、分割して配列で返します。
	 * @param tokens トークン(OUT)
	 * @return 0:正常 -1:EOF
	 */
	int Read( vector<string>& tokens );

	/**
	 * ファイルストリームをクローズします。
	 * @return 0:正常 -1:異常
	 */
	int Close( void );

private:

	/**
	 * ファイルから１行読み込みます。
	 * @param line 行データ
	 * @return >=0：読み込んだデータ長 -1：EOF
	 */
	int GetNextLine( string& line );

	/**
	 * データをパースします。
	 * @param nextLine 行データ
	 * @param tokens パースしたデータの配列(OUT)
	 * @return 0
	 */
	int Parse( string& nextLine, vector<string>& tokens );

	int GetParam( string& status );

	std::fstream* pstream;
	char SEPARATOR;
	char QUOTE;
};

