
//------------------------------------------------------
//		ピクセルシェーダー	
//------------------------------------------------------

float3	center = float3( 0.0f, 0.0f, 0.0f );	//	画像の中心
float		radian = 0.0f;	//	角度( -PI ~ PI )
float		shadow = 0.5f;	//	影の薄さ

//------------------------------------------------------
//		ピクセルシェーダー	
//------------------------------------------------------

//	白黒
float4 PS_CircleShadow( VS_2D In, float2 pPos : VPOS ) : COLOR
{
	//	出力
	float4	OUT;

	//	ピクセル色決定
	OUT = In.Color * tex2D( DecaleSamp, In.Tex );

	//	角度を取得
	float r = atan2( pPos.x - center.x, pPos.y - center.y );

	//	設定した角度以上の点を暗くする( yが下向きなので-r )
	if ( -r > radian ) OUT.rgb *= shadow;

	return OUT;
}

//------------------------------------------------------
//		テクニック
//------------------------------------------------------

//	白黒
technique circleShadow
{
	pass P0
	{
		AlphaBlendEnable = true;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		CullMode = None;
		ZEnable = false;

		PixelShader = compile ps_3_0 PS_CircleShadow();
	}
}