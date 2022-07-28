#include "stdafx.h"

PicoCat::PicoCat()
{
	// col �� parent �ɾ����� Ȯ��
	// reverseLR = false; �� �⺻ (������ ����)
	col->isFilled = false;
	col->collider = COLLIDER::RECT;
	col->pivot = OFFSET_B;
	col->SetWorldPos(Vector2(0.0f, 0.0f));
	col->scale = Vector2(25.0f, 50.0f);
	col->color = Color(1.0f, 0.0f, 0.0f, 1.0f);


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

	scalar = 100.0f;
	gravity = 50.0f;
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

	gravity += 50.0f * DELTA;
	//gravity = Utility::Saturate(gravity, 0.0f, 500.0f);

	//��� vv �Ʒ��� �߷¹��� (�ٴ� �ո��� ������)
	col->MoveWorldPos(DOWN * gravity * DELTA);

	if (isOn)
	{
		jump->visible = false;
		stand->visible = true;

		col->SetWorldPosY(Utility::Saturate(col->GetWorldPos().y,blockOn,1000.0f));
		//col->SetLocalPosY(blockOn);
	}


	//����������
	if (INPUT->KeyPress(VK_RIGHT)|| INPUT->KeyPress('D'))
	{
		col->MoveWorldPos(RIGHT * scalar * DELTA);

		stand->visible = false;
		jump->visible = false;

		walk->visible = true;

		stand->reverseLR = false;
		walk->reverseLR = false;
	}
	//��������
	else if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress('S'))
	{
		col->MoveWorldPos(LEFT * scalar * DELTA);

		stand->visible = false;
		jump->visible = false;

		walk->visible = true;

		stand->reverseLR = true;
		walk->reverseLR = true;
	}

	//������ Ű ���� �� :: ������
	if (INPUT->KeyUp(VK_RIGHT) || INPUT->KeyUp('D'))
	{
		jump->visible = false;
		walk->visible = false;

		stand->visible = true;

		jump->reverseLR = false;
		stand->reverseLR = false;
		walk->reverseLR = false;
	}
	//����
	else if (INPUT->KeyUp(VK_LEFT) || INPUT->KeyUp('S'))
	{
		stand->visible = false;
		walk->visible = false;

		jump->visible = true;

		jump->reverseLR = true;
		stand->reverseLR = true;
		walk->reverseLR = true;
	}

	//�� �� �ƴҶ��� ���� << �ٵ� �̰� �̷��� �ϴ��� �׳� ... �� ���� Ű�� ���� �ִ°� ������
	if (INPUT->KeyDown(VK_UP) || INPUT->KeyDown('W'))
	{
		isOn = false;
		gravity = -100.0f;

		//stand ����� ���� �¿���� ���ֱ�
		//if (jump->reverseLR != stand->reverseLR) jump->reverseLR = stand->reverseLR;

		stand->visible = false;
		walk->visible = false;

		jump->visible = true;
	}


#if 0 
	//������
	if (stat == CATSTAT::STAND)
	{
		//����->�ȱ�
		//����������
		if (INPUT->KeyDown(VK_RIGHT) || INPUT->KeyDown('D'))
		{
			stat = CATSTAT::WALK;
			stand->visible = false;
			stand->reverseLR = false;

			walk->visible = true;
			walk->reverseLR = false;
		}
		//��������
		else if (INPUT->KeyDown(VK_LEFT) || INPUT->KeyDown('S'))
		{
			stat = CATSTAT::WALK;

			stand->visible = false;
			stand->reverseLR = true;

			walk->visible = true;
			walk->reverseLR = true;
		}

		//�� �� �ƴҶ��� ���� << �ٵ� �̰� �̷��� �ϴ��� �׳� ... �� ���� Ű�� ���� �ִ°� ������
		if (INPUT->KeyDown(VK_UP) || INPUT->KeyDown('W'))
		{
			stat = CATSTAT::JUMP;

			//stand ����� ���� �¿���� ���ֱ�
			if (jump->reverseLR != stand->reverseLR) jump->reverseLR = stand->reverseLR;

			stand->visible = false;
			jump->visible = true;
		}


		//������->����ȣ�ۿ�
		if (INPUT->KeyDown(VK_DOWN) || INPUT->KeyDown('S'))
		{

		}

	}
	//�ȱ�0
	else if (stat == CATSTAT::WALK)
	{

		if (INPUT->KeyPress(VK_RIGHT) || INPUT->KeyPress('D'))
		{
			col->MoveWorldPos(RIGHT * scalar * DELTA);
		}
		//��������
		if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress('S'))
		{
			col->MoveWorldPos(LEFT * scalar * DELTA);
		}



		// �������� ���ٰ� ��ȸ�� �� �� ��� ���缭�� �̽� .. �̰Ͷ����� �� ������ ��� ��������
		//�ȱ�->���� :: Ű ����
		if (INPUT->KeyUp(VK_RIGHT) || INPUT->KeyUp(VK_LEFT))
		{
			stat = CATSTAT::STAND;

			walk->visible = false;
			stand->visible = true;
		}

		//�ȱ�->����
		if (INPUT->KeyUp(VK_RIGHT) || INPUT->KeyUp(VK_LEFT))
		{
			stat = CATSTAT::STAND;

			walk->visible = false;
			stand->visible = true;
		}

		//�ȱ�->�б� :: �翷���� ���𰡿� �浹�������� bool��(true)�� if ������ �ֱ�
		if (INPUT->KeyDown(VK_UP) || INPUT->KeyDown('W'))
		{
			stat = CATSTAT::JUMP;

			//stand ����� ���� �¿���� ���ֱ�
			if (jump->reverseLR != walk->reverseLR) jump->reverseLR = walk->reverseLR;

			walk->visible = false;
			jump->visible = true;
		}

		//�ȱ�->����ȣ�ۿ�

	}
	//����
	else if (stat == CATSTAT::JUMP)
	{
		//gravity = -700.0f;
		//�����ϸ鼭 �����̱�(Ű �Է� ���� ���� ��,���)
		if (INPUT->KeyPress(VK_RIGHT) || INPUT->KeyPress('D'))
		{
			jump->reverseLR = false;
			col->MoveWorldPos(RIGHT * scalar * DELTA);
		}
		//��������
		if (INPUT->KeyPress(VK_LEFT) || INPUT->KeyPress('S'))
		{
			jump->reverseLR = true;
			col->MoveWorldPos(LEFT * scalar * DELTA);
		}



		//����->���߱� :: �̺κ� �̽� ����
		if (INPUT->KeyUp(VK_UP) || INPUT->KeyUp('W'))
		{
			stat = CATSTAT::STAND;

			jump->visible = false;
			stand->visible = true;
		}


		//����->����ȣ�ۿ�? �ǳ�?
	}

	//�б�
	else if (stat == CATSTAT::PUSH)
	{

	//�б�->���߱�

	//�б�->����

	//�б�->����ȣ�ۿ�

	}

#endif




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

void PicoCat::onBlock(float obPosY)
{
	blockOn = obPosY;
	isOn = true;
}

void PicoCat::offBlock()
{
	isOn = false;

}

