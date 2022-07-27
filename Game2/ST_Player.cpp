#include "stdafx.h"

ST_Player::ST_Player()
{
	col = new ObRect();
	col->scale = Vector2(224.0f / 7.0f, 40.0f) * 2.5f;
	col->pivot = OFFSET_T;
	col->isFilled = false;

	LR = new ObImage(L"LeftRight.png");
	LR->SetParentRT(*col);
	LR->pivot = OFFSET_T;
	LR->scale = Vector2(224.0f / 7.0f, 40.0f) * 2.5f;
	LR->maxFrame.x = 7;

	boost = new ObImage(L"Start.png");
	boost->SetParentRT(*col);
	boost->pivot = OFFSET_T;
	boost->maxFrame.x = 11;
	boost->scale = Vector2(352.0f / 11.0f, 120.0f) * 2.5f;
	boost->visible = false;
	boost->ChangeAnim(ANIMSTATE::LOOP, 0.1f);

	isBoosting = false;
	LRkey = 0.0f;
	level = 0;
}

ST_Player::~ST_Player()
{
	SafeDelete(col);
	SafeDelete(LR);
	SafeDelete(boost);
}

void ST_Player::Update()
{
	ImGui::SliderFloat("PlayerAlpha", &LR->color.w, 0.0f, 1.0f);
	ImGui::SliderInt("Level", &level, 0, 3);

	dir = Vector2(0.0f, 0.0f);

	if (INPUT->KeyPress(VK_LEFT))
	{
		LRkey -= DELTA * 3.0f;
		LRkey = Utility::Saturate(LRkey, -3.0f, 3.0f);

		dir.x = -1.0f;
	}
	else if (INPUT->KeyPress(VK_RIGHT))
	{
		LRkey += DELTA * 3.0f;
		LRkey = Utility::Saturate(LRkey, -3.0f, 3.0f);

		dir.x = 1.0f;
	}
	else
	{
		if (LRkey < -DELTA * 1.5f)
		{
			LRkey += DELTA * 1.5f;
		}
		else if (LRkey > DELTA * 1.5f)
		{
			LRkey -= DELTA * 1.5f;
		}
		else
		{
			LRkey = 0.0f;
		}
	}

	if (INPUT->KeyPress(VK_UP))
	{
		dir.y = 1.0f;
	}
	else if (INPUT->KeyPress(VK_DOWN))
	{
		dir.y = -1.0f;
	}

	if (INPUT->KeyPress(VK_SPACE))
	{
		if (!isBoosting)
		{
			boost->frame.x = 0;
			boost->visible = true;
			LR->visible = false;
		}
		isBoosting = true;
		app.deltaScale = 3.0f;
	}
	else //부스팅 끝낫을 때
	{
		if (isBoosting)
		{
			boost->visible = false;
			LR->visible = true;
			LRkey = 0.0f;
		}
		app.deltaScale = 1.0f;
		isBoosting = false;
	}

	//발사
	if (INPUT->KeyDown('Z'))
	{
		for (int i = 0; i < MAX; i++)
		{
			if (!bullet[i].isfire)
			{
				if (level != bullet[i].GetLevel())
				{
					bullet[i].ChangeLevel(level);
				}
				//bullet[i].col->visible = true;
				bullet[i].Shoot(UP, 200.0f, col->GetWorldPos());

				break;
			}
		}
	}

	dir.Normalize();
	col->MoveWorldPos(dir * 200.0f * DELTA);


	LR->frame.x = (int)(LRkey + 3.0f);


	col->Update();
	LR->Update();
	boost->Update();

	for (int i = 0; i < MAX; i++)
	{
		bullet[i].Update();
	}
}

void ST_Player::Render()
{
	col->Render();
	LR->Render();
	boost->Render();
	for (int i = 0; i < MAX; i++)
	{
		bullet[i].Render();
	}
}
