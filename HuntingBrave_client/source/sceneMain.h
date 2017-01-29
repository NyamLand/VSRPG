//*****************************************************************************************************************************
//
//		���C���V�[��
//
//*****************************************************************************************************************************

//	class�O���錾
#include	"Stage.h"

//	class
class	sceneMain : public Scene
{
private:
	Stage*	stage;
	
	//	�o�b�N�o�b�t�@
	Surface*	backBuffer;
	iex2DObj*	mainScreen;

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


