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
	static void	ThreadFunction( void* ptr );
};


