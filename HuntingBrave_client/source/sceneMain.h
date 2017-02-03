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

	//	�V�F�[�_�[�p
	iex2DObj*	diffuse;
	iex2DObj*	specular;
	iex2DObj*	depth;
	iex2DObj*	normal;
	iex2DObj*	light;

	float	blackWhitePercentage;
	static	bool	threadState;

public:
	~sceneMain( void );
	//	������
	bool Initialize( void );
	void	DifferedInitialize( void );

	//	�X�V�E�`��
	void Update( void );	//	�X�V
	void Render( void );	//	�`��

	//	����֐�
	void	DebugRender( void );
	void	MyInfoRender( void );
	void	DeadScreen( void );
	static void	ThreadFunction( void* ptr );
};


