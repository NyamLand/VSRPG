#ifndef _CSVREADER_H__
#define _CSVREADER_H__

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
	 * �R���X�g���N�^
	 * @param stream �t�@�C���X�g���[��
	 * @comment �Z�p���[�^(,), �G���N�I�[�g(")
	 */
	CSVReader(fstream& stream);

	/**
	 * �R���X�g���N�^
	 * @param stream �t�@�C���X�g���[��
	 * @param sep �Z�p���[�^
 	 * @comment �G���N�I�[�g(")
	 */
	CSVReader(fstream& stream, const char sep);

	/**
	 * �R���X�g���N�^
	 * @param stream �t�@�C���X�g���[��
	 * @param sep �Z�p���[�^
 	 * @param quo �G���N�I�[�g
	 */
	CSVReader(fstream& stream, const char sep, const char quo);

	/**
	 * �f�X�g���N�^
	 */
	virtual ~CSVReader(void);

	/**
	 * CSV�t�@�C�����P�s�ǂݍ���ŁA�������Ĕz��ŕԂ��܂��B
	 * @param tokens �g�[�N��(OUT)
	 * @return 0:���� -1:EOF
	 */
	int Read(vector<string>& tokens);

	/**
	 * �t�@�C���X�g���[�����N���[�Y���܂��B
	 * @return 0:���� -1:�ُ�
	 */
	int Close(void);

private:

	/**
	 * �t�@�C������P�s�ǂݍ��݂܂��B
	 * @param line �s�f�[�^
	 * @return >=0�F�ǂݍ��񂾃f�[�^�� -1�FEOF
	 */
	int GetNextLine(string& line);

	/**
	 * �f�[�^���p�[�X���܂��B
	 * @param nextLine �s�f�[�^
	 * @param tokens �p�[�X�����f�[�^�̔z��(OUT)
	 * @return 0
	 */
	int Parse(string& nextLine, vector<string>& tokens);

	int GetParam(string& status);

	std::fstream* pstream;
	char SEPARATOR;
	char QUOTE;

};

#endif
