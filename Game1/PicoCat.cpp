#include "stdafx.h"

PicoCat::PicoCat()
{
	// col 에 parent 걸었는지 확인
	// reverseLR = false; 가 기본 (오른쪽 방향)
	col->isFilled = false;
	col->collider = COLLIDER::RECT;
	col->pivot = OFFSET_B;
	col->SetWorldPos(Vector2(0.0f, 0.0f)); // y값 == 바닥윗면 값
	col->scale = Vector2(25.0f, 40.0f);
	col->color = Color(1.0f, 0.0f, 0.0f, 1.0f);

	headCol-> isFilled = false;
	headCol->collider = COLLIDER::RECT;
	headCol->SetParentRT(*col);
	headCol->pivot = OFFSET_B;
	headCol->SetLocalPos(Vector2(0.0f, 15.0f)); // y값 == 바닥윗면 값
	headCol->scale = Vector2(48.0f, 32.0f);
	headCol->color = Color(1.0f, 0.0f, 0.0f, 1.0f);

	stand->SetParentRT(*col);
	stand->visible = true;
	stand->pivot = OFFSET_B;
	stand->scale = Vector2(50.0f, 50.0f);

	walk->SetParentRT(*col);
	walk->visible = false;
	walk->pivot = OFFSET_B;
	walk->scale = Vector2(50.0f, 50.0f);
	walk->maxFrame.x = 8;
	walk->ChangeAnim(ANIMSTATE::LOOP,0.1f);

	jump->SetParentRT(*col);
	jump->visible = false;
	jump->pivot = OFFSET_B;
	jump->scale = Vector2(50.0f, 50.0f);

	push->SetParentRT(*col);
	push->visible = false;
	push->pivot = OFFSET_B;
	push->scale = Vector2(50.0f, 50.0f);
	push->maxFrame.x = 8;
	push->ChangeAnim(ANIMSTATE::LOOP, 0.1f);

	scalar = 100.0f; //좌우 이동속도
	gravity = 0.0f; //아래로 떨어지는 중력값
	gravityPlus = 0.0f; //누르는 시간에 따라서 더해지는 중력플러스 값

	stat = CATSTAT::STAND;

	//SOUND->AddSound("jumSFX.mp3", "jump", false);

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
	//cout << col->GetWorldPivot().y << endl;

	//gravity = Utility::Saturate(gravity, 0.0f, 500.0f);

	//계속 vv 아래로 중력받음 (바닥 뚫리면 떨어짐)
	col->MoveWorldPos(direction * scalar * DELTA + DOWN * gravity * DELTA);
	//col->MoveWorldPos(DOWN * gravity * DELTA);

	//바닥으로 떨어져도 위에서 자동 리스폰 되게
	if (col->GetWorldPos().y < -app.GetHalfHeight())
	{
		col->SetWorldPosX(col->GetWorldPos().x - 200.0f);
		col->SetWorldPosY(app.GetHalfHeight() + 240.0f);
	}

	//블럭 충돌-> 높이 고정
	if (isOn)
	{
		jump->visible = false;
		stand->visible = true;

		gravity = 0.0f;
		//scalar = 0.0f;

		isJump = false;

		col->SetWorldPosY(blockOn);
		//col->SetLocalPosY(blockOn);
	}
	else
	{
		gravity += 100.0f * DELTA;
		if (gravity > 300.0f) gravity = 300.0f;
	}

	//벽 충돌-> X고정
	if (isWall)
	{
		col->SetWorldPosX(wallOn);
	}

	if (isEnd)
	{
		Endgame();
	}
	else
	{
		//오른쪽으로
		if (stat == CATSTAT::RIGHTPRESS)
		{
			direction = RIGHT;
			//col->MoveWorldPos(RIGHT * 100.0f * DELTA);

			stand->visible = false;
			jump->visible = false;

			walk->visible = true;

			stand->reverseLR = false;
			walk->reverseLR = false;
		}
		//왼쪽으로
		else if (stat == CATSTAT::LEFTPRESS)
		{
			direction = LEFT;
			//col->MoveWorldPos(LEFT * 100.0f * DELTA);

			stand->visible = false;
			jump->visible = false;

			walk->visible = true;

			stand->reverseLR = true;
			walk->reverseLR = true;
		}
		else if (stat == CATSTAT::STAND) direction = Vector2(0.0f, 0.0f);

		//점프중에 움직임 키 뗐을 때 :: 오른쪽
		if (stat == CATSTAT::RIGHTUP)
		{
			stand->visible = false;
			walk->visible = false;

			jump->visible = true;

			jump->reverseLR = false;
			stand->reverseLR = false;
			walk->reverseLR = false;
		}
		else if (stat == CATSTAT::LEFTUP)
		{
			stand->visible = false;
			walk->visible = false;

			jump->visible = true;

			jump->reverseLR = true;
			stand->reverseLR = true;
			walk->reverseLR = true;
		}

		//누르는 시간 따라서 올라가는 힘추가
		if (INPUT->KeyPress(VK_UP) || INPUT->KeyPress('W'))
		{
		}

		if (stat == CATSTAT::JUMPDOWN)
		{
			if (!isJump)
			{
				SOUND->Stop("jump");
				SOUND->Play("jump");

				//바닥충돌 off
				isOn = false;

				gravity = -150.0f;

				stand->visible = false;
				walk->visible = false;

				jump->visible = true;
			}

		}

		//키 떼면 점프 1회 판정
		if (stat == CATSTAT::JUMPUP)
		{
			//isJump = true;
		}
	}


#if 0  //키조종   
	//오른쪽으로
	if (INPUT->KeyPress(VK_RIGHT) || INPUT->KeyPress('D'))
	{
		direction = RIGHT;
		//col->MoveWorldPos(RIGHT * 100.0f * DELTA);

		stand->visible = false;
		jump->visible = false;

		walk->visible = true;

		stand->reverseLR = false;
		walk->reverseLR = false;
	}
	//왼쪽으로
	else if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress('S'))
	{
		direction = LEFT;
		//col->MoveWorldPos(LEFT * 100.0f * DELTA);

		stand->visible = false;
		jump->visible = false;

		walk->visible = true;

		stand->reverseLR = true;
		walk->reverseLR = true;
	}
	else direction = Vector2(0.0f, 0.0f);

	//움직임 키 뗐을 때 :: 오른쪽
	if (INPUT->KeyUp(VK_RIGHT) || INPUT->KeyUp('D'))
	{
		stand->visible = false;
		walk->visible = false;

		jump->visible = true;

		jump->reverseLR = false;
		stand->reverseLR = false;
		walk->reverseLR = false;
	}
	//점프
	else if (INPUT->KeyUp(VK_LEFT) || INPUT->KeyUp('S'))
	{
		stand->visible = false;
		walk->visible = false;

		jump->visible = true;

		jump->reverseLR = true;
		stand->reverseLR = true;
		walk->reverseLR = true;
	}

 	//누르는 시간 따라서 올라가는 힘추가
 	if (INPUT->KeyPress(VK_UP) || INPUT->KeyPress('W'))
 	{

 		//if (gravityPlus <= 5.0f)
 		//{
 		//	if (TIMER->GetTick(jumpTime, 5.0f))
 		//	{
 		//		gravityPlus += 1.0f * DELTA;
 		//	}
 		//}
 		//else
 		//{
 		//	gravityPlus = 5.0f * DELTA;
 		//}

 		//scalar += 1.0f;
 		//scalar = Utility::Saturate(scalar,0.0f,50.0f);
 	}

 	//문 앞 아닐때만 점프 << 근데 이거 이렇게 하느니 그냥 ... 문 여는 키를 따로 주는게 나을듯
 	if (INPUT->KeyDown(VK_UP) || INPUT->KeyDown('W'))
 	{

 		if (!isJump)
 		{
 			//바닥충돌 off
 			isOn = false;

 			gravity = -150.0f;

 			//stand 방향과 같게 좌우반전 해주기
 			//if (jump->reverseLR != stand->reverseLR) jump->reverseLR = stand->reverseLR;

 			stand->visible = false;
 			walk->visible = false;

 			jump->visible = true;
		}

 	}

 	//키 떼면 점프 1회 판정
 	if (INPUT->KeyUp(VK_UP) || INPUT->KeyUp('W'))
 	{
 		//isJump = true;
 	}

#endif


#if 0 
	//가만히
	if (stat == CATSTAT::STAND)
	{
		//가만->걷기
		//오른쪽으로
		if (INPUT->KeyDown(VK_RIGHT) || INPUT->KeyDown('D'))
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
		//gravity = -700.0f;
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



		//점프->멈추기 :: 이부분 이슈 있음
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

#endif

//-------------------------------------
	col->Update();
	headCol->Update();
	stand->Update();
	walk->Update();
	jump->Update();
	push->Update();

}

void PicoCat::Render()
{
	col->Render();
	headCol->Render();
	stand->Render();
	walk->Render();
	jump->Render();
	push->Render();

}

//블럭 밟고 있을 때 돌려줄 값 :: 계속 블럭의 윗쪽에 고정되어 있어야 함
void PicoCat::onBlock(float obPosY)
{
	blockOn = obPosY;
	isOn = true;
}

void PicoCat::offBlock()
{
	isOn = false;
}

//col이 벽이나 계단 블럭의 Y좌표보다 낮게 있을때 조건이면 들어옴

void PicoCat::onWall(float obPosX, float obScaleX)
{
	//좌측
	if (col->GetWorldPivot().x < obPosX)
	{
			// 내 scale *0.5 ..인데! 왜 24냐면 애니메이션 때문에 줄임
		wallOn = obPosX - obScaleX * 0.5f - 24.0f;
	}
	//우측
	else if (col->GetWorldPivot().x > obPosX)
	{
		wallOn = obPosX + obScaleX * 0.5f + 24.0f;
	}

	isWall = true;
}

void PicoCat::offWall()
{
	isWall = false;
}

void PicoCat::Endgame()
{
	col->SetWorldPos(Vector2(2600.0f, 270.0f));
	stand->visible = false;
	walk->visible = false;
	push->visible = false;
	jump->visible = false;
}

