//------------------------------------------------------
//		ピクセルシェーダー	
//------------------------------------------------------

	//	白黒
	float4 PS_BlackWhite( VS_2D In ) : COLOR
	{
		//	出力
		float4	OUT;

		//	ピクセル色決定
		OUT = In.Color * tex2D( DecaleSamp, In.Tex );

		//	白黒化
		OUT.rgb = ( OUT.r + OUT.g + OUT.b ) * 0.3333f;

		return OUT;
	}

//------------------------------------------------------
//		テクニック
//------------------------------------------------------

	//	白黒
	technique blackWhite
	{
		pass P0
		{
			AlphaBlendEnable = true;
			BlendOp = Add;
			SrcBlend = SrcAlpha;
			DestBlend = InvSrcAlpha;
			CullMode = None;
			ZEnable = false;

			PixelShader = compile ps_2_0 PS_BlackWhite();
		}
	}