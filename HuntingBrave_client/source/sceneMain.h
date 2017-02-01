//*****************************************************************************************************************************
//
//		���C���V�[��
//
//*****************************************************************************************************************************

//	class�O���錾
#include	"Stage.h"
class TimeUpUI;

//	class
class	sceneMain : public Scene
{
private:
	Stage*	stage;
	
	//	�o�b�N�o�b�t�@
	Surface*	backBuffer;
	iex2DObj*	mainScreen;

	//	�^�C���A�b�v�p
	TimeUpUI*	timeUp;

	float	blackWhitePercentage;
	static	bool	threadState;

public:
	~sceneMain( void );
	//	������
	bool Initialize( void );
	//	�X�V�E�`��
	void Update( void );	//	�X�V
	void Render( void );	//	�`��

	//	����֐�
	void	DebugRender( void );
	void	MyInfoRender( void );
	void	DeadScreen( void );
	static void	ThreadFunction( void* ptr );
};


