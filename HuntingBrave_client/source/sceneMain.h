//*****************************************************************************************************************************
//
//		���C���V�[��
//
//*****************************************************************************************************************************

//	class�O���錾

//	class
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
	static		void	ThreadFunction( void );
};


