//--------------------------------------------------------------------------------------
// Sprite Rendering Effect - 2011 - Bobby Anguelov
//--------------------------------------------------------------------------------------

//color map texture
Texture2D colorMap;
int2 screenDimensions;

//texture sampler state
SamplerState linearSampler
{
    Filter = min_mag_mip_linear;
    AddressU = Clamp;
    AddressV = Clamp;
    MaxAnisotropy = 16;
};

//blend state
BlendState SrcAlphaBlendingAdd 
{ 
	BlendEnable[0] = TRUE; 
	SrcBlend = SRC_ALPHA; 
	DestBlend = INV_SRC_ALPHA; 
	BlendOp = ADD; 
	SrcBlendAlpha = ZERO; 
	DestBlendAlpha = ZERO; 
	BlendOpAlpha = ADD; 
	RenderTargetWriteMask[0] = 0x0F; 
}; 

//VERTEX AND PIXEL SHADER INPUTS
//--------------------------------------------------------------------------------------
struct SPRITE_INPUT
{
	uint spriteType   : SPRITETYPE;
	int2 topLeft      : ANCHOR;
	int2 dimensions   : DIMENSIONS;
	float uvLeft      : UVLEFT;
	float uvTop       : UVTOP;
	float uvRight     : UVRIGHT;
	float uvBottom    : UVBOTTOM;
	float opacity     : OPACITY;
};

//pixel shader inputs
struct PS_INPUT
{
	float4 p      : SV_POSITION; 
	float2 t      : TEXCOORD;
	float opacity : OPACITY;	
};

//--------------------------------------------------------------------------------------
// VERTEX SHADER
//--------------------------------------------------------------------------------------
SPRITE_INPUT VS( SPRITE_INPUT input )
{
	return input;  
}

float4 toClip(int x, int y)
{
	return float4((float)x/screenDimensions[0]*2 -1, (float)y/screenDimensions[1]*2 -1, 0, 1);
}

//--------------------------------------------------------------------------------------
// GEOMETRY SHADER
//--------------------------------------------------------------------------------------
[maxvertexcount(4)]
void GS( point SPRITE_INPUT sprite[1], inout TriangleStream<PS_INPUT> triStream )
{
	PS_INPUT v;
	// set the opacity
	v.opacity = sprite[0].opacity;

	//create sprite quad
	//--------------------------------------------

	//bottom left
	v.p = toClip(sprite[0].topLeft[0], sprite[0].topLeft[1]-sprite[0].dimensions[1]);
	v.t = float2(sprite[0].uvLeft, sprite[0].uvBottom);
	triStream.Append(v);
	
	//top left
	v.p = toClip(sprite[0].topLeft[0],sprite[0].topLeft[1]);
	v.t = float2(sprite[0].uvLeft, sprite[0].uvTop);
	triStream.Append(v);

	//bottom right
	v.p = toClip(sprite[0].topLeft[0]+sprite[0].dimensions[0],sprite[0].topLeft[1]-sprite[0].dimensions[1]);
	v.t = float2(sprite[0].uvRight, sprite[0].uvBottom);
	triStream.Append(v);

	//top right
	v.p = toClip(sprite[0].topLeft[0]+sprite[0].dimensions[0],sprite[0].topLeft[1]);
	v.t = float2(sprite[0].uvRight, sprite[0].uvTop);
	triStream.Append(v);
}
//--------------------------------------------------------------------------------------
// PIXEL SHADER
//--------------------------------------------------------------------------------------
float4 PS( PS_INPUT input ) : SV_Target
{ 
	float4 color = colorMap.Sample(linearSampler, input.t);
	color[3] = min(color[3],input.opacity);
	return color;      
}
//--------------------------------------------------------------------------------------
// Techniques
//--------------------------------------------------------------------------------------
technique10 RENDER
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_4_0, VS() ) );
        SetGeometryShader( CompileShader( gs_4_0, GS() ) );		
        SetPixelShader( CompileShader( ps_4_0, PS() ) );
        SetBlendState( SrcAlphaBlendingAdd, float4( 0.0f, 0.0f, 0.0f, 0.0f ), 0xFFFFFFFF );
    }    
}