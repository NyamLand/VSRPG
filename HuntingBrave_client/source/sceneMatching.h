
//*****************************************************************************************************************************
//
//		���C���V�[��
//
//*****************************************************************************************************************************

#include	"GameData.h"
#include	"WaitLoad.h"
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
	WaitLoad*	waitLoad;
	NameInput*	nameInput;
	ItemSelect*	itemSelect;
	GameWait*	gameWait;
	static	bool	threadState;

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

	//	thread
	static	void	ThreadFunc( void* ptr );
	static	void	WaitThread( void );
	static	void	ServerInitThread( bool& out, char* addr, int* name );
};


