
//********************************************************************
//
//		基本３Ｄシェーダー		
//
//********************************************************************

//------------------------------------------------------
//		色情報手動設定用
//------------------------------------------------------

float3	color = float3( 1.0f, 1.0f, 1.0f );
float		alpha = 1.0f;

//------------------------------------------------------
//		ピクセルシェーダー	
//------------------------------------------------------
float4 PS_ColorChange( VS_OUTPUT In ) : COLOR
{
	float4	OUT;

	//	ピクセル色決定
	OUT = In.Color * tex2D( DecaleSamp, In.Tex );

	//	色適用
	OUT.rgb += color;
	OUT.a = alpha;

	return OUT;
}

//	ランバート拡散照明

//------------------------------------------------------
//		通常描画テクニック
//------------------------------------------------------
technique colorChange
{
	pass P0
	{
		AlphaBlendEnable = true;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		CullMode = CCW;
		ZEnable = true;

		VertexShader = compile vs_2_0 VS_Basic();
		PixelShader = compile ps_2_0 PS_ColorChange();
	}
}
