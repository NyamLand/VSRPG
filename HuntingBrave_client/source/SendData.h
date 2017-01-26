
#pragma once

//****************************************************************
//
//	SendData
//
//****************************************************************

	//	���M�R�}���h
	namespace
	{
		namespace SEND_COMMAND
		{
			enum 
			{
				NO_COMMAND = -1,
				PLAYER_INFO = 1,
				ATTACK_INFO,
				INPUT_INFO,
				LEVEL_INFO,
				ENEMY_INFO,
				ITEM_INFO
			};
		}

		namespace SEND_ENEMY_COMMAND
		{
			enum
			{
				NO_COMMAND = -1,
				BIG_ENEMY_HUNT = 1,
				SMALL_ENEMY_HUNT,
				PLAYER_HIT,
				CLIENT_OK,
				DEAD_END
			};
		}
	}

//----------------------------------------------------------------------------------------------
//	���M�p�\����
//----------------------------------------------------------------------------------------------

	//	�v���C���[�f�[�^���M�p
	struct SendPlayerData
	{
		char	com = SEND_COMMAND::PLAYER_INFO;	//1byte
		float	axisX, axisY;		//	8byte
		float	cameraAngle;	//	4byte
		int 	frame;				//	4byte
		//	13byte
		SendPlayerData( float axisX, float axisY, float cameraAngle, int frame ) : 
			axisX( axisX ), axisY( axisY ), cameraAngle( cameraAngle ), frame( frame ){}
	};

	//	�U�����
	struct SendAttackData
	{
		char			com = SEND_COMMAND::ATTACK_INFO;		//	1byte
		char			shape;		//	1byte
		float			radius;		//	4byte
		Vector3	vec1;		//	12byte
		Vector3	vec2;		//	12byte
		SendAttackData( char shape, float radius, const Vector3& vec1, const Vector3& vec2 ) : 
			shape( shape ), radius( radius ), vec1( vec1 ), vec2( vec2 ){}
	};

	//	���͏��
	struct SendInputData
	{
		char		com = SEND_COMMAND::INPUT_INFO;
		char		key;
		char		keyState;
		SendInputData( void ){};
		SendInputData( char key, char keyState ) :
			key( key ), keyState( keyState ){}
	};

	//	���x�����
	struct SendLevelData
	{
		char com = SEND_COMMAND::LEVEL_INFO;
		char levelType;
		SendLevelData( char levelType ) : levelType( levelType ){}
	};

	//	�A�C�e���g�p���
	struct SendItemData
	{
		char com = SEND_COMMAND::ITEM_INFO;
		char itemPos;
		SendItemData( char itemPos ) : itemPos( itemPos ) {}
	};