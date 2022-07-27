#include "stdafx.h"

PicoCat::PicoCat()
{
	// col �� parent �ɾ���
	// reverseLR = false; �� �⺻ (������ ���Ⱑ��)
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

	//��� vv �Ʒ��� �߷¹��� (�ٴ� �ո��� ������)
	//col->MoveWorldPos(UP * scalar + DOWN * gravity * DELTA);


	//������
	if (stat == CATSTAT::STAND)
	{
		//����->�ȱ�
		//����������
		if (INPUT->KeyDown(VK_RIGHT)|| INPUT->KeyDown('D'))
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



		//����->���߱� :: �̺κ� ���� ����
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
