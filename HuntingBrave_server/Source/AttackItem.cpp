
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"AttackItem.h"

//**************************************************************************
//
//	AttackItem�N���X
//
//**************************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

#define	EFFECTIVE_TIME		5.0f
#define	DOUBLE_PARAM		1.5f

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	AttackItem::AttackItem( int id ) : Item( id )
	{
	
	}

	//	�f�X�g���N�^
	AttackItem::~AttackItem( void ) 
	{
		
	}

//----------------------------------------------------------------------------------------------
//	�X�V
//----------------------------------------------------------------------------------------------

	//	�X�V
	void	AttackItem::Update( void )
	{
		if ( timer->Update() )
		{
			//	����������
			if ( state )
			{
				//	�L��������
				gameParam->GetPlayerStatus( id ).power =
					gameParam->GetPlayerStatus( id ).savePower;
				
				//	�X�e�[�^�X�𖳌�
				state = false;

				//	���M
				SendStatusData sendData( SEND_STATUS::ATTACK, gameParam->GetPlayerStatus( id ).power );
				gameParam->send( id, ( LPSTR )&sendData, sizeof( sendData ) );
			}
		}
		else
		{
			//	�L��������
			gameParam->GetPlayerStatus( id ).power = 
				( int )( gameParam->GetPlayerStatus( id ).savePower * DOUBLE_PARAM );

			//	���M
			SendStatusData sendData( SEND_STATUS::ATTACK, gameParam->GetPlayerStatus( id ).power );
			gameParam->send( id, ( LPSTR )&sendData, sizeof( sendData ) );
		}
	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

	//	�A�C�e���g�p
	void	AttackItem::UseItem( void )
	{
		timer->Start( EFFECTIVE_TIME );
		state = true;
	}

//----------------------------------------------------------------------------------------------
//	
//----------------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

