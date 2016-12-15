//------------------------------------------------------
//		ピクセルシェーダー	
//------------------------------------------------------

//	白黒
float4 PS_NegaPosi( VS_2D In ) : COLOR
{
	//	出力
	float4	OUT;

	//	ピクセル色決定
	OUT = In.Color * tex2D( DecaleSamp, In.Tex );

	//	白黒化
	OUT.rgb = 1.0f - OUT.rgb;

	return OUT;
}

//------------------------------------------------------
//		テクニック
//------------------------------------------------------

//	白黒
technique negaPosi
{
	pass P0
	{
		AlphaBlendEnable = true;
		BlendOp = Add;
		SrcBlend = SrcAlpha;
		DestBlend = InvSrcAlpha;
		CullMode = None;
		ZEnable = false;

		PixelShader = compile ps_2_0 PS_NegaPosi();
	}
}