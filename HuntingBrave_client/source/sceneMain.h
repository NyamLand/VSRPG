//*****************************************************************************************************************************
//
//		���C���V�[��
//
//*****************************************************************************************************************************

//	�N���X�O���錾
class GameParam;

class	sceneMain : public Scene
{
private:

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
};


