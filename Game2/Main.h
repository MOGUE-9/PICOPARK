#pragma once
class Main : public Scene
{
private:
	ObImage* bg;
	ST_Player* pl;
	Enemy* en;

public:
	virtual void Init() override;
	virtual void Release() override; //해제
	virtual void Update() override;
	virtual void LateUpdate() override;//갱신
	virtual void Render() override;
	virtual void ResizeScreen() override;
};
