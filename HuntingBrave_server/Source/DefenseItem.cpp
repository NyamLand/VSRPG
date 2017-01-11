
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"GameParam.h"
#include	"DefenseItem.h"

//**************************************************************************
//
//	DefenseItem�N���X
//
//**************************************************************************

//----------------------------------------------------------------------------------------------
//	�O���[�o��
//----------------------------------------------------------------------------------------------

#define	EFFECTIVE_TIME		10.0f
#define	DOUBLE_PARAM		2.0f

//----------------------------------------------------------------------------------------------
//	�������E���
//----------------------------------------------------------------------------------------------

	//	�R���X�g���N�^
	DefenseItem::DefenseItem( int id ) : Item( id )
	{
	
	}

	//	�f�X�g���N�^
	DefenseItem::~DefenseItem( void )
	{

	}

//----------------------------------------------------------------------------------------------
//	�X�V
//----------------------------------------------------------------------------------------------

	//	�X�V
	void	DefenseItem::Update( void )
	{
		if ( timer->Update() )
		{
			//	����������
			if ( state )
			{
				//	�L��������
				gameParam->GetPlayerStatus( id ).defense =
					gameParam->GetPlayerStatus( id ).saveDefense;

				//	�X�e�[�^�X�𖳌�
				state = false;

				//	���M
				SendStatusData sendData( SEND_STATUS::DEFENSE, ( float )gameParam->GetPlayerStatus( id ).defense );
				gameParam->send( id, ( LPSTR )&sendData, sizeof( sendData ) );
			}
		}
		else
		{
			//	�L��������
			gameParam->GetPlayerStatus( id ).defense =
				( int )( gameParam->GetPlayerStatus( id ).saveDefense * DOUBLE_PARAM );

			//	���M
			SendStatusData sendData( SEND_STATUS::DEFENSE, ( float )gameParam->GetPlayerStatus( id ).defense );
			gameParam->send( id, ( LPSTR )&sendData, sizeof( sendData ) );
		}
	}

//----------------------------------------------------------------------------------------------
//	����֐�
//----------------------------------------------------------------------------------------------

	//	�A�C�e���g�p
	void	DefenseItem::UseItem( void )
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

