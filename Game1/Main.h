#pragma once
#define FMAX 8
#define RMAX 3

enum class STAGE
{
	TITLE,
	ST_1,
	ST_2
};

class Main : public Scene
{
private:
	
	Title*		titleMap;
	Map1*		firstMap;

	PicoCat*	player;

	STAGE		stage{ STAGE::TITLE };


public:
	virtual void Init() override;
	virtual void Release() override; //����
	virtual void Update() override;
	virtual void LateUpdate() override;//����
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
