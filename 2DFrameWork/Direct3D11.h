#pragma once

class Direct3D11 : public Singleton<Direct3D11>
{
private:
	//인터페이스
	//new 로 생성이 안됨 -> 추상클래스
	//create 함수를 이용해서 생성된 주소를 받아옴
	ID3D11Device*						device; //버퍼 생성
	ID3D11DeviceContext*				deviceContext; //렌더링 파이프라인 바인딩
	IDXGISwapChain*						swapChain; 
	ID3D11Texture2D*					backBuffer;
	ID3D11RenderTargetView*				renderTargetView;
	ID3D11BlendState *					blendState;
	//ID3D11DepthStencilView*				depthStencilView;

	vector<struct D3DEnumAdapterInfo*>	adapterInfos;
	UINT								numerator;
	UINT								denominator;
	bool								isCreated;

public:
	Direct3D11();
	~Direct3D11();

private:
	void CreateBackBuffer(float width, float height);
	void DeleteBackBuffer();

public:
	void Create();
	void SetRenderTarget(ID3D11RenderTargetView* rtv = nullptr,
		ID3D11DepthStencilView* dsv = nullptr);
	//
	void Clear(Color color = Color(0.7f,0.7f,0.7f,1.0f), ID3D11RenderTargetView* rtv = nullptr, ID3D11DepthStencilView* dsv = nullptr);
	//
	void Present();

	void ResizeScreen(float width, float height);
	
public:
	//Getter
	ID3D11Device*			GetDevice()		{ return device; }
	ID3D11DeviceContext*	GetDC()			{ return deviceContext; }
	IDXGISwapChain*			GetSwapChain()	{ return swapChain; }
	ID3D11RenderTargetView* GetRTV()		{ return renderTargetView; }
	bool					GetCreated()	{ return isCreated; }
	//ID3D11DepthStencilView* GetDSV() { return depthStencilView; }
};

struct D3DEnumOutputInfo
{
	IDXGIOutput*		output; //어뎁터 출력
	DXGI_OUTPUT_DESC	outputDesc;
	UINT				numerator;
	UINT				denominator;
	D3DEnumOutputInfo();
	~D3DEnumOutputInfo();
};

struct D3DEnumAdapterInfo
{
	UINT				adapterOrdinal;
	IDXGIAdapter1*		adapter;
	//어뎁터 서술형 구조체
	DXGI_ADAPTER_DESC1	adapterDesc;
	D3DEnumOutputInfo*	outputInfo;
	D3DEnumAdapterInfo();
	~D3DEnumAdapterInfo();
};

