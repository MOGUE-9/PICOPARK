#pragma once
#define FMAX 8
#define RMAX 3

class Main : public Scene
{
private:
	
	ObRect* block;


	PicoCat* player;




public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
