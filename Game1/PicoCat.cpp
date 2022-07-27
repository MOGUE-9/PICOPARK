#include "stdafx.h"

PicoCat::PicoCat()
{
	// col 에 parent 걸었니
	// reverseLR = false; 가 기본 (오른쪽 방향가기)
	col->isFilled = false;
	col->scale = Vector2(50.0f, 50.0f);

	stand->SetParentRT(*col);
	stand->visible = true;
	stand->scale = Vector2(50.0f, 50.0f);

	walk->SetParentRT(*col);
	walk->visible = false;
	walk->scale = Vector2(50.0f, 50.0f);
	walk->maxFrame.x = 8;
	walk->ChangeAnim(ANIMSTATE::LOOP,0.1f);

	jump->SetParentRT(*col);
	jump->visible = false;
	jump->scale = Vector2(50.0f, 50.0f);

	push->SetParentRT(*col);
	push->visible = false;
	push->scale = Vector2(50.0f, 50.0f);
	push->maxFrame.x = 8;
	push->ChangeAnim(ANIMSTATE::LOOP, 0.1f);

	scalar = 100.0f;
	gravity = 100.0f;
}

PicoCat::~PicoCat()
{
	SafeDelete(col);
	SafeDelete(stand);
	SafeDelete(walk);
	SafeDelete(jump);
	SafeDelete(push);
}

void PicoCat::Update()
{
	gravity += 100.0f;

	//계속 vv 아래로 중력받음 (바닥 뚫리면 떨어짐)
	//col->MoveWorldPos(UP * scalar + DOWN * gravity * DELTA);


	//가만히
	if (stat == CATSTAT::STAND)
	{
		//가만->걷기
		//오른쪽으로
		if (INPUT->KeyDown(VK_RIGHT)|| INPUT->KeyDown('D'))
		{
			stat = CATSTAT::WALK;
			stand->visible = false;
			stand->reverseLR = false;

			walk->visible = true;
			walk->reverseLR = false;
		}
		//왼쪽으로
		else if (INPUT->KeyDown(VK_LEFT) || INPUT->KeyDown('S'))
		{
			stat = CATSTAT::WALK;

			stand->visible = false;
			stand->reverseLR = true;

			walk->visible = true;
			walk->reverseLR = true;
		}

		//문 앞 아닐때만 점프 << 근데 이거 이렇게 하느니 그냥 ... 문 여는 키를 따로 주는게 나을듯
		if (INPUT->KeyDown(VK_UP) || INPUT->KeyDown('W'))
		{
			stat = CATSTAT::JUMP;

			//stand 방향과 같게 좌우반전 해주기
			if (jump->reverseLR != stand->reverseLR) jump->reverseLR = stand->reverseLR;

			stand->visible = false;
			jump->visible = true;
		}


		//가만히->문상호작용
		if (INPUT->KeyDown(VK_DOWN) || INPUT->KeyDown('S'))
		{

		}

	}
	//걷기0
	else if (stat == CATSTAT::WALK)
	{

		if (INPUT->KeyPress(VK_RIGHT) || INPUT->KeyPress('D'))
		{
			col->MoveWorldPos(RIGHT * scalar * DELTA);
		}
		//왼쪽으로
		if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress('S'))
		{
			col->MoveWorldPos(LEFT * scalar * DELTA);
		}



		// 왼쪽으로 가다가 급회전 할 때 잠깐 멈춰서는 이슈 .. 이것때문인 것 같은데 어떻게 수정할지
		//걷기->서기 :: 키 떼면
		if (INPUT->KeyUp(VK_RIGHT) || INPUT->KeyUp(VK_LEFT))
		{
			stat = CATSTAT::STAND;

			walk->visible = false;
			stand->visible = true;
		}

		//걷기->점프
		if (INPUT->KeyUp(VK_RIGHT) || INPUT->KeyUp(VK_LEFT))
		{
			stat = CATSTAT::STAND;

			walk->visible = false;
			stand->visible = true;
		}

		//걷기->밀기 :: 양옆으로 무언가와 충돌했을때의 bool값(true)을 if 문으로 넣기
		if (INPUT->KeyDown(VK_UP) || INPUT->KeyDown('W'))
		{
			stat = CATSTAT::JUMP;

			//stand 방향과 같게 좌우반전 해주기
			if (jump->reverseLR != walk->reverseLR) jump->reverseLR = walk->reverseLR;

			walk->visible = false;
			jump->visible = true;
		}

		//걷기->문상호작용

	}
	//점프
	else if (stat == CATSTAT::JUMP)
	{
		//점프하면서 움직이기(키 입력 방향 따라 좌,우로)
		if (INPUT->KeyPress(VK_RIGHT) || INPUT->KeyPress('D'))
		{
			jump->reverseLR = false;
			col->MoveWorldPos(RIGHT * scalar * DELTA);
		}
		//왼쪽으로
		if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress('S'))
		{
			jump->reverseLR = true;
			col->MoveWorldPos(LEFT * scalar * DELTA);
		}



		//점프->멈추기 :: 이부분 문제 많음
		if (INPUT->KeyUp(VK_UP) || INPUT->KeyUp('W'))
		{
			stat = CATSTAT::STAND;

			jump->visible = false;
			stand->visible = true;
		}


		//점프->문상호작용? 되나?
	}

	//밀기
	else if (stat == CATSTAT::PUSH)
	{

	//밀기->멈추기

	//밀기->점프

	//밀기->문상호작용

	}





//-------------------------------------
	col->Update();
	stand->Update();
	walk->Update();
	jump->Update();
	push->Update();

}

void PicoCat::Render()
{
	col->Render();
	stand->Render();
	walk->Render();
	jump->Render();
	push->Render();

}
