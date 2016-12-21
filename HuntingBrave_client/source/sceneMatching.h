
//*****************************************************************************************************************************
//
//		���C���V�[��
//
//*****************************************************************************************************************************

#include	"GameData.h"
#include	"NameInput.h"
#include	"ItemSelect.h"
#include	"GameWait.h"
#include	<memory>
using namespace std;

class	sceneMatching : public Scene
{
private:
	int step;
	char	nextScene;
	char name[17];
	char	addr[64];
	NameInput*	nameInput;
	ItemSelect*	itemSelect;
	GameWait*	gameWait;

public:
	~sceneMatching( void );
	//	������
	bool Initialize( void );
	
	//	�X�V�E�`��
	void Update( void );	//	�X�V
	void Render( void );	//	�`��

	//	����֐�
	void	ObjUpdate( void );
	void	CheckComplete( void );
	void	DebugRender( void );
	void	MyInfoRender( void );
};


