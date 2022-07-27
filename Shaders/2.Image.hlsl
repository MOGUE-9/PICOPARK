
struct VertexInput
{
    float4 position : POSITION0;
    float2 uv : UV0;
};

// PI
struct PixelInput
{
    float4 position : SV_POSITION; //화면좌표계 포지션
    float2 uv : UV0; //매핑된 좌표
    float4 color : COLOR0; //섞을색상
};

//상수버퍼 크기는 16byte배수로 만들어야한다.

cbuffer VS_WVP : register(b0)
{
    matrix WVP;
}
cbuffer VS_COLOR : register(b1)
{
    //4 개의 4바이트
    float4 color;
}
cbuffer VS_UV : register(b2)
{
    float4 uv;
}

cbuffer PS_LIGHT : register(b0)
{
	float2 screenPos; //스크린좌표
	float radius; //반지름크기
	float select; //남는값
	float4 lightColor; //조명 색
	float4 outColor; //외곽 색
};

//버텍스 쉐이더
//반환형  함수이름(매개변수)
// VertexInput(in) ->  VS  -> PixelInput (out)
PixelInput VS(VertexInput input)
{
    //공간변환이 있을 예정인 곳
    PixelInput output;
    //output.Position * input.Position;
    //L-W
    output.position = mul(input.position, WVP);
    
    output.color = color;
    
    //매핑된 좌표 사용
    output.uv = input.uv;
    
    [branch]
    if (output.uv.x == 0.0f)
        output.uv.x = uv.x;
    else
        output.uv.x = uv.z;
    
    [branch]
    if (output.uv.y == 0.0f)
        output.uv.y = uv.y;
    else
        output.uv.y = uv.w;

    return output;
}

//텍스쳐 자원  (srv) 에서 연결
Texture2D Texture : register(t0);

//추출기
SamplerState Sampler : register(s0);

//픽셀쉐이더 진입 함수
float4 PS(PixelInput input) : SV_TARGET //SV_TARGET 은 타겟이될 색깔 
{
    float4 TextureColor =
    // 매핑된 좌표로 텍스쳐 로드
    Texture.Sample(Sampler, input.uv);
    
    //읽어온 그림파일의 픽셀색상을 조건문으로 비교
    [flatten]
    if (TextureColor.r == 1.0f &&
        TextureColor.g == 0.0f &&
        TextureColor.b == 1.0f)
    {
        discard;
    }
    
    TextureColor = TextureColor + (input.color * 2.0f - 1.0f);
	TextureColor = saturate(TextureColor);
    
    
    
    
    
	float2 minus = input.position.xy - screenPos;
	float dis = minus.x * minus.x + minus.y * minus.y;
	dis = sqrt(dis);
    
	if (select == 0.0f)
	{
		if (dis > radius)
		{
			TextureColor.rgb += (outColor.rgb * 2.0f - 1.0f);
		}
		else
		{
			TextureColor.rgb += (lightColor.rgb * 2.0f - 1.0f);
		}
	}
	else
	{
		float temp = 1.0f - saturate(dis / radius);
		TextureColor.rgb += (lightColor.rgb * 2.0f - 1.0f);
		TextureColor.rgb *= temp;
	}
    
	TextureColor = saturate(TextureColor);

    return TextureColor;
}