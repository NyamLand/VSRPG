
#include	"iextreme.h"
#include	"GlobalFunction.h"
#include	"DrawShape.h"
#include	"GameParam.h"
#include	"Sound.h"
#include	"PlayerManager.h"
#include	"Collision.h"

#include	"Enemy.h"

//***************************************************************
//
//	Enemyクラス
//
//***************************************************************

//------------------------------------------------------------------------------------
//	グローバル
//------------------------------------------------------------------------------------

#define	ANGLEADJUST_SPEED 1.0f
#define	DEAD_LENGTH	50.0f

//------------------------------------------------------------------------------------
//	初期化・解放
//------------------------------------------------------------------------------------

	//	コンストラクタ
	Enemy::Enemy( void ):
		targetPos( 0.0f, 0.0f, 0.0f ),
		interpolationParam(0.0f), searchDist(0.0f), attackDist(0.0f), runLength(0.0f),
		count(40), 
		cooltime(40)
	{
	}

	//	デストラクタ
	Enemy::~Enemy( void )
	{

	}

//------------------------------------------------------------------------------------
//	更新・描画
//------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------
	
	//	移動
	void	Enemy::Move( float speed )
	{
		float	length = 0.0f;
		if ( DistCheck( length ) )	return;
		runLength++;

		if ( length <= searchDist && runLength<=20.0f )
		{

			//	プレイヤーの方を向く
			FacingPlayer();

			//	向いてる方向に前進
			Advance( speed );
		}
		else
		{
			runLength = 0.0f;
			//	モーション設定
			SetMotion( 0 );	//	待機モーション
		}
	}

	//	プレイヤーの方を向く
	void	Enemy::FacingPlayer( void )
	{
		//	プレイヤーへのベクトルを求める
		int id = gameParam->GetMyIndex();
		Vector3	targetVec = playerManager->GetPlayer( id )->GetPos() - pos;
		targetVec.Normalize();

		AngleAdjust( targetVec, ANGLEADJUST_SPEED );
	}

	//	前進
	void	Enemy::Advance( float speed )
	{
		SetMotion( 1 );
		Vector3	moveVec = Vector3( sinf( angle ), 0.0f, cosf( angle ) );
		AddMove(moveVec);
		SetMove( moveVec * speed );

	}

	//	プレイヤーとの距離チェック
	bool	Enemy::DistCheck( float& length )
	{
		Vector3	vec = playerManager->GetPlayer( gameParam->GetMyIndex() )->GetPos() - pos;
		length = vec.Length();

		//	一定の距離まで近づくと攻撃
		if ( length <= attackDist )
		{
			if (mode != MODE::WAIT){
				SetMode(MODE::ATTACK);
				return	true;
			}
		}

		else if (length>DEAD_LENGTH)
		{
			SetMode(MODE::DEAD);
		}
		return false;
	}

	//	ライフチェック（ ０以下なら死亡モードに移行 ）
	void	Enemy::LifeCheck( void )
	{
		if ( !lifeInfo.active )	return;

		if ( lifeInfo.life <= 0 )
		{
			lifeInfo.active = false;
			sound->PlaySE(SE::ENEMY_DEAD);
			SetMode( MODE::DEAD );

			//	討伐情報送信
			SendHuntInfo();
		}
	}

	//	向き調整（ カメラ影響なし ）
	void	Enemy::AngleAdjust( const Vector3& moveVec, float adjustSpeed )
	{
		//	移動方向を求める
		float	moveAngle = atan2f( moveVec.x, moveVec.z );

		//	親に投げる
		AngleAdjustParent(
			Vector3( sinf( moveAngle ), 0.0f, cosf( moveAngle ) ),
			adjustSpeed);
	}

//------------------------------------------------------------------------------------
//	動作関数
//------------------------------------------------------------------------------------
	void	Enemy::Update()
	{
		
	}

	void	Enemy::StageCheck()
	{

	}

	//	送信
	void	Enemy::SendHuntInfo( void )
	{
		static	struct 
		{
			char com;
			char infoType;
			char enemyType;
		} sendInfo;

		//	情報設定
		sendInfo.com = SEND_COMMAND::ENEMY_INFO;
		sendInfo.infoType = SEND_ENEMY_COMMAND::SMALL_ENEMY_HUNT;
		sendInfo.enemyType = enemyType;

		//	送信
		gameParam->send( ( char* )&sendInfo, sizeof( sendInfo ) );
	}

//------------------------------------------------------------------------------------
//	モード関数
//------------------------------------------------------------------------------------

	//仮(後で消す)
	void	Enemy::DamageMode(void)
	{
		lifeInfo.active = false;
		count--;
		if (count <= 0){
			count = 40;
			lifeInfo.active = true;
			SetMode(MODE::MOVE);
		}

	}

	//　待機時モード動作
	void	Enemy::WaitMode(void)
	{
		SetMotion(0);
		cooltime--;
		if (cooltime >= 0)return;
		cooltime = 40;
		SetMode(MODE::MOVE);
	}

	//	移動値加算
	void	Enemy::AddMove(Vector3& move)
	{
		collision->CheckWall(pos, move, 100.0f);
		//pos.y = collision->CheckDown(pos);
	}
//------------------------------------------------------------------------------------
//	情報設定
//------------------------------------------------------------------------------------
	
	//	ターゲットの位置を設定
	void	Enemy::SetTargetPos( const Vector3& pos )
	{
		targetPos = pos;
	}

	//	敵タイプ設定
	void	Enemy::SetEnemyType( char enemyType )
	{
		this->enemyType = enemyType;
	}
	
//------------------------------------------------------------------------------------
//	情報取得
//------------------------------------------------------------------------------------

	//	敵タイプ取得
	char	Enemy::GetEnemyType( void )const
	{
		return	enemyType;
	}

	int		Enemy::GetMode( void )const
	{
		return mode;
	}