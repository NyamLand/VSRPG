
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"UIManager.h"
#include	"Random.h"
//***************************************************************
//
//	UIManager�N���X
//
//***************************************************************

//---------------------------------------------------------------------------------------
//	�O���[�o��	
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	�������E���
//---------------------------------------------------------------------------------------

//	�R���X�g���N�^
UIManager::UIManager(void)
{

}

//	�f�X�g���N�^
UIManager::~UIManager(void)
{
	Release();
}

//	������
bool	UIManager::Initialize( void )
{
	//---------------------------------------
	//	HP�o�[�̃|�W�V�������Z�b�g(�����j
	//---------------------------------------
	int width = (int)(HP_MAX::WIDTH / 2.5f);			//	�X�P�[��1/2.5
	int height = (int)(HP_MAX::HEIGHT / 2.5f);			//	�X�P�[��1/2.5
	int posx = width / 2;								//	���S����[�܂ł̋���
	int posy = iexSystem::ScreenHeight - height / 2;	//	��ʒ[����摜�̒��S����[�܂ł̋�������

	timerUI = new TimerUI();
	hpUI = new HpUI(posx, posy, width, height);
	itemUI = new ItemUI(posx, posy, width, height);

	//---------------------------------------
	//	EXP�̃|�W�V�������Z�b�g
	//---------------------------------------
	width = width / 6;
	height = height;
	posx = posx + width / 2;
	posy = posy - height / 2 - width / 6;

	expUI = new ExpUI(posx, posy, width, height);

	//---------------------------------------
	//	SCORE�̃|�W�V�������Z�b�g
	//---------------------------------------
	Image* EXP = expUI->GetImageExp();					//	�o���l�̃|�W�V�������l��
	scoreUI = new ScoreUI(EXP->x, EXP->y - EXP->w / 2 - EXP->w / 6, EXP->w, EXP->h);

	//---------------------------------------
	//	�}�b�v�̃|�W�V�������Z�b�g(�E��j
	//---------------------------------------
	width = (int)(MAP_MAX::WIDTH / 2.5f);			//	�X�P�[��1/2.5
	height = (int)(MAP_MAX::HEIGHT / 2.5f);			//	�X�P�[��1/2.5
	posx = iexSystem::ScreenWidth - (width / 2);	//	���S����[�܂ł̋���
	posy = height / 2;								//	��ʒ[����摜�̒��S����[�܂ł̋�������

	mapUI = new MapUI(posx, posy, width, height);

	//---------------------------------------
	//	�X�R�A�{�[�h�̃|�W�V�������Z�b�g(���S�j
	//---------------------------------------
	width = (int)(BOARD_MAX::BOARD_WIDTH / BOARD_PER);
	height = (int)(BOARD_MAX::BOARD_HEIGHT / BOARD_PER);
	posx = iexSystem::ScreenWidth / 2;				//	��ʂ̒��S
	posy = iexSystem::ScreenHeight / 2;				//	��ʂ̒��S

	boardUI = new ScoreBoardUI(posx, posy, width, height);

	//	neta
	yaju = new Image();
	yaju->Initialize("DATA/UI/main_UI/Yaju.png", posx, posy, 0, 0, 0, 0, 960, 540);
	yaju->SetScaling(0.01f);
	check = false;
	return	true;
}

//	���
void	UIManager::Release(void)
{
	SafeDelete( timerUI );
	SafeDelete( hpUI );
	SafeDelete( expUI );
	SafeDelete( itemUI );
	SafeDelete( mapUI );
	SafeDelete( scoreUI );
	SafeDelete( boardUI );
}

//---------------------------------------------------------------------------------------
//	�X�V�E�`��
//---------------------------------------------------------------------------------------

//	�X�V
void	UIManager::Update(void)
{
	timerUI->Update();
	hpUI->Update();
	expUI->Update();
	itemUI->Update();
	mapUI->Update();
	scoreUI->Update();
	boardUI->Update();
	if (KEY_Get(KEY_SPACE) == 1 && random->GetInt(0, 20) == 1)	check = true;
	if (check){
		//	neta
		if (yaju->scalingState != IMAGE_SCALING::SMALL)
		{
			yaju->ScalingUpdate(iexSystem::ScreenHeight);
		}
		else
		{
			yaju->renderflag = false;
		}
	}
}

//	�`��
void	UIManager::Render(void)
{
	timerUI->Render();
	hpUI->Render();
	expUI->Render();
	itemUI->Render();
	mapUI->Render();
	scoreUI->Render();
	boardUI->Render();
	yaju->Render(IMAGE_MODE::SCALING);
}

//---------------------------------------------------------------------------------------
//	����֐�
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	���ݒ�
//---------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------
//	���擾
//---------------------------------------------------------------------------------------

