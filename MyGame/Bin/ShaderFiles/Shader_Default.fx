


texture g_BaseTexture;
float	g_Alpha;

sampler BaseSampler = sampler_state
{
	texture = g_BaseTexture;
};

vector PS_Default(float4 _vPosition : POSITION, float2 _vTexUV : TEXCOORD0, float4 _vWinPos : TEXCOORD1) : COLOR0
{
	vector vColor = (vector)0.f;

	vColor = tex2D(BaseSampler, _vTexUV);

	return vColor;

}

vector PS_Transparent(float4 _vPosition : POSITION, float2 _vTexUV : TEXCOORD0, float4 _vWinPos : TEXCOORD1) : COLOR0
{
	vector vColor = (vector)0.f;

	vColor = tex2D(BaseSampler, _vTexUV);

	//투명하지 않은 부분만 반투명화
	vColor.a *= 0.5f;

	return vColor;

}

vector PS_Red(float4 _vPosition : POSITION, float2 _vTexUV : TEXCOORD0, float4 _vWinPos : TEXCOORD1) : COLOR0
{
	vector vColor = (vector)0.f;

	vColor = tex2D(BaseSampler, _vTexUV);

	vColor.r = 1.f;

	return vColor;

}

vector PS_BLINK(float4 _vPosition : POSITION, float2 _vTexUV : TEXCOORD0, float4 _vWinPos : TEXCOORD1) : COLOR0
{
	vector vColor = (vector)0.f;

vColor = tex2D(BaseSampler, _vTexUV);

	vColor.rgb = 1.f;
	
	return vColor;
}

vector PS_ALPHA(float4 _vPosition : POSITION, float2 _vTexUV : TEXCOORD0, float4 _vWinPos : TEXCOORD1) : COLOR0
{
	vector vColor = (vector)0.f;

vColor = tex2D(BaseSampler, _vTexUV);

vColor.a = g_Alpha;

return vColor;
}

technique DefaultTechnique
{

	pass Default
	{
		VertexShader = NULL;
		PixelShader = compile ps_3_0 PS_Default();
	}
	pass Transparent
	{
		VertexShader = NULL;
		PixelShader = compile ps_3_0 PS_Transparent();
	}
	pass Red
	{
		VertexShader = NULL;
		PixelShader = compile ps_3_0 PS_Red();
	}
	pass BLINK
	{
		VertexShader = NULL;
		PixelShader = compile ps_3_0 PS_BLINK();
	}
	pass Alpha
	{
		VertexShader = NULL;
		PixelShader = compile ps_3_0 PS_ALPHA();
	}

}