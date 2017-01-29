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

	//	外部設定用
	float	percentage = 0.0f;

	float4	PS_BlackWhiteOutSet( VS_2D In ) : COLOR
	{
		//	出力
		float4	OUT;

		//	ピクセル色決定
		OUT = In.Color * tex2D( DecaleSamp, In.Tex );

		//	白黒化
		float3 start = float3( OUT.r, OUT.g, OUT.b );
		float3 end = ( OUT.r + OUT.g + OUT.b ) * 0.333f;
		float3 sub = start - end;

		OUT.rgb = start - ( sub * percentage );

		return	OUT;
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

	//	白黒(外部設定)
	technique blackWhiteOutSet
	{
		pass P0
		{
			AlphaBlendEnable = true;
			BlendOp = Add;
			SrcBlend = SrcAlpha;
			DestBlend = InvSrcAlpha;
			CullMode = None;
			ZEnable = false;

			PixelShader = compile ps_2_0 PS_BlackWhiteOutSet();
		}
	}