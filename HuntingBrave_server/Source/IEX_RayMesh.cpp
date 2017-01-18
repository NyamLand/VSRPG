#include	"iextreme.h"
#include	"IEX_RayMesh.h"

//**************************************************************************************************
//
//
//
//**************************************************************************************************

//------------------------------------------------------
//	コンストラクタ
//------------------------------------------------------
iexRayMesh::iexRayMesh( char* filename )
{
	Vertices = NULL;
	Faces = NULL;

	Normals = NULL;
	Positions = NULL;

	bflag = LoadIMO(filename);
}

//------------------------------------------------------
//	デストラクタ
//------------------------------------------------------
iexRayMesh::~iexRayMesh()
{
	if( Vertices != NULL ) delete[] Vertices;
	if( Faces != NULL ) delete[] Faces;

	if( Normals != NULL ) delete[] Normals;
	if( Positions != NULL ) delete[] Positions;
}

//**************************************************************************************************
//
//	レイピック
//
//**************************************************************************************************
int	iexRayMesh::RayPickUD( Vector3* out, Vector3* pos, Vector3* vec, float *Dist )
{
	float	t, neart;
	float	vy;
	int		ret = -1;

	Vector3	p = *pos;
	vy = vec->y;

	neart = 1000.0f;//*Dist;

	Vector	l1, l2, l3;
	Vector	p1, p2, p3;
	Vector v[3];
	Vector n;

	for( u32 j=0 ; j<NumFace ; j++ )
	{
		int a = Faces[j*3+0];
		int b = Faces[j*3+1];
		int c = Faces[j*3+2];

		v[0].x = Vertices[a].x;	v[1].x = Vertices[b].x;	v[2].x = Vertices[c].x;
		if( v[0].x > p.x && v[1].x > p.x && v[2].x > p.x ) continue;

		v[0].z = Vertices[a].z;	v[1].z = Vertices[b].z;	v[2].z = Vertices[c].z;
		if( v[0].z > p.z && v[1].z > p.z && v[2].z > p.z ) continue;

		v[0].y = Vertices[a].y;	v[1].y = Vertices[b].y;	v[2].y = Vertices[c].y;

		//	内点判定（全外積がマイナス）		
		l1.x = v[1].x - v[0].x;
		l1.z = v[1].z - v[0].z;
		p1.x = v[0].x - p.x;
		p1.z = v[0].z - p.z;
		if( (p1.x*l1.z - p1.z*l1.x)*vy < 0 ) continue;

		l2.x = v[2].x - v[1].x;
		l2.z = v[2].z - v[1].z;
		p2.x = v[1].x - p.x;
		p2.z = v[1].z - p.z;
		if( (p2.x*l2.z - p2.z*l2.x)*vy < 0 ) continue;

		l3.x = v[0].x - v[2].x;
		l3.z = v[0].z - v[2].z;
		p3.x = v[2].x - p.x;
		p3.z = v[2].z - p.z;
		if( (p3.x*l3.z - p3.z*l3.x)*vy < 0 ) continue;

		//	外積による法線算出		
		n = Normals[j];
		//	表裏判定
		if( vy*n.y >= 0 ) continue;

		//	交点算出
		p1.y = v[0].y - p.y;
		t = Vector3Dot( n, p1 ) / (n.y*vy);
		if( t < .0f || t > neart ) continue;

		*vec = n;
		ret = j;
		neart = t;
	}
	out->y = neart*vy + p.y;
	out->x = pos->x;
	out->z = pos->z;
	*Dist = neart;

	return	ret;
}

int	iexRayMesh::RayPick( Vector3* out, Vector3* pos, Vector3* vec, float *Dist )
{
	int		ret = -1;

	if( vec->x == .0f && vec->z == .0f ) return RayPickUD( out, pos, vec, Dist );

	Vector3 p = *pos;
	Vector3 vv = *vec;

	float neart = *Dist;
	float dist = *Dist;
	dist = dist*dist;
	*out = p;

	Vector3 v1, v2, v3;
	Vector3	n;
	Vector3	l1, l2, l3;
	Vector3	temp;
	Vector3	cp;

	Vector3 p1, p2, p3;

	for( u32 j=0 ; j<NumFace ; j++ )
	{
		int a = Faces[j*3+0];
		int b = Faces[j*3+1];
		int c = Faces[j*3+2];

		v1.x = Vertices[a].x;	v1.y = Vertices[a].y;	v1.z = Vertices[a].z;
		v2.x = Vertices[b].x;	v2.y = Vertices[b].y;	v2.z = Vertices[b].z;
		v3.x = Vertices[c].x;	v3.y = Vertices[c].y;	v3.z = Vertices[c].z;

		//	距離判定
		//Vector3	ss = (v1 + v2 + v3) / 3.0f - p;
		//if( ss.LengthSq() > dist ) continue;
		l1.x = v2.x - v1.x;
		l1.y = v2.y - v1.y;
		l1.z = v2.z - v1.z;
		l2.x = v3.x - v2.x;
		l2.y = v3.y - v2.y;
		l2.z = v3.z - v2.z;
		
		//	外積による法線算出		
		n = Normals[j];
		//	内積の結果がプラスならば裏向き
		float dot = Vector3Dot( vv, n );
		if( dot >= 0 ) continue;
		//	交点算出
		p1.x = v1.x - p.x;
		p1.y = v1.y - p.y;
		p1.z = v1.z - p.z;
		float t = Vector3Dot( n, p1 ) / dot;
		if( t < .0f || t > neart ) continue;

		cp.x = vv.x*t + p.x;
		cp.y = vv.y*t + p.y;
		cp.z = vv.z*t + p.z;
		//	内点判定
		p1.x = v1.x - cp.x;
		p1.y = v1.y - cp.y;
		p1.z = v1.z - cp.z;
		
		Vector3Cross( temp, p1, l1 );
		if( Vector3Dot(temp, n) < .0f ) continue;

		p2.x = v2.x - cp.x;
		p2.y = v2.y - cp.y;
		p2.z = v2.z - cp.z;
		Vector3Cross( temp, p2, l2 );
		if( Vector3Dot(temp, n) < .0f ) continue;

		l3.x = v1.x - v3.x;
		l3.y = v1.y - v3.y;
		l3.z = v1.z - v3.z;
		p3.x = v3.x - cp.x;
		p3.y = v3.y - cp.y;
		p3.z = v3.z - cp.z;
		Vector3Cross( temp, p3, l3 );
		if( Vector3Dot(temp, n) < .0f ) continue;

		*out = cp;
		*vec = n;
		ret = j;
		neart = t;
	}
	*Dist = neart;

	return	ret;
}

//**************************************************************************************************
//
//	ファイル読み込み
//
//**************************************************************************************************
//	IMOオブジェクト
typedef struct tagIMOOBJ {
	DWORD		id;	
	int			type;
	DWORD		NumVertex;
	LPLVERTEX	lpVertex;

	DWORD		NumFace;
	LPWORD		lpFace;
	LPDWORD		lpAtr;

	DWORD			NumMaterial;	//	マテリアル数
	D3DMATERIAL9	Material[32];	//	マテリアル
	char			Texture[32][32];//	テクスチャファイル

} IMOOBJ, *LPIMOOBJ;


//------------------------------------------------------
//	ＩＭＯ読み込み
//------------------------------------------------------
bool iexRayMesh::LoadIMO( LPSTR filename )
{
	IMOOBJ		imo;
	//	ファイル読み込み
	HANDLE	hfile;
	DWORD	dum;

	int		version = 1;

	hfile = CreateFile( filename, GENERIC_READ, FILE_SHARE_READ, (LPSECURITY_ATTRIBUTES)NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL );
	if( hfile == INVALID_HANDLE_VALUE ) return false;

	ReadFile( hfile, &imo, sizeof(IMOOBJ), &dum, NULL );

	NumVertex = imo.NumVertex;
	NumFace   = imo.NumFace;

	MESHVERTEX2*	workV2 = new MESHVERTEX2[NumVertex];

	Faces = new u16[NumFace*3];
	Vertices = new Vector[NumVertex];

	//	頂点読み込み
	ReadFile( hfile, workV2, sizeof(MESHVERTEX2)*NumVertex, &dum, NULL );
	//	インデックス読み込み
	ReadFile( hfile, Faces, sizeof(u16)*NumFace*3, &dum, NULL );

	for( u32 v=0 ; v<NumVertex ; v++ )
	{
		Vertices[v].x = workV2[v].x;
		Vertices[v].y = workV2[v].y;
		Vertices[v].z = workV2[v].z;
	}

	CloseHandle(hfile);
	delete[]	workV2;

	//	法線・重心計算
	Normals   = new Vector[NumFace];
	Positions = new Vector3[NumFace];

	for( u32 j=0 ; j<NumFace*3 ; j+=3 ){
		Vector3 v1 = Vertices[ Faces[j+0] ];
		Vector3 v2 = Vertices[ Faces[j+1] ];
		Vector3 v3 = Vertices[ Faces[j+2] ];
		//	外積による法線算出		
		Vector3Cross( Normals[j/3], v2-v1, v3-v1 ); 
		//	距離判定
		Vector3	p = (v2+v3) / 2;	//２→３の中点
		Vector3	v = p - v1;
		Positions[j/3] = v1 + v*0.66666f;
	}		



	return true;
}

