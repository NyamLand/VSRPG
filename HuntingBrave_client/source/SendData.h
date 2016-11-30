
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
				HUNT_INFO
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
		float	axisX, axisY;	//	8byte
		int 	frame;			//	4byte
		//	13byte
		SendPlayerData( float axisX, float axisY, int frame ) : 
			axisX( axisX ), axisY( axisY ), frame( frame ){}
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
		int		keyType;
		int		keyState;
		SendInputData( void ){};
		SendInputData( int keyType, int keyState ) :
			keyType( keyType ), keyState( keyState ){}
	};

	//	���x�����
	struct SendLevelData
	{
		char com = SEND_COMMAND::LEVEL_INFO;
		char levelType;
		SendLevelData( char levelType ) : levelType( levelType ){}
	};

	//	�o���l���
	struct SendHuntData
	{
		char com = SEND_COMMAND::HUNT_INFO;
		char	enemyType;
		SendHuntData( char enemyType ) : enemyType( enemyType ){}
	};