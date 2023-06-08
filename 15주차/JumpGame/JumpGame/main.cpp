#include "GameLoop.h"

#define PRINTLN(STR)	{printf(STR);printf("\n");}

constexpr int KEY_ESC = 27;			// ESC Ű
constexpr int KEY_SPACE = 32;		// SpaceBar Ű

constexpr int MAX_JUMP = 6;			// �ִ� ���� ����
constexpr int Y_BASE = 10;			// ������ �ʱ� Y�� ��ġ
constexpr int Y_COLLISION = 4;		// Y���� �浹 ���� ��ġ
constexpr int TREE_COLLISION = 7;	// ������ ����� �浹 ������ X�� ��ġ
constexpr int TREE_START = 80;		// ������ �����Ǵ� ��ġ
constexpr int TREE_END = -6;		// ������ ������� ��ġ
constexpr int SLEEP_TIME = 35;		// ���� ���� �ֱ�


/**
Ű ���� Ȯ��
@param
@return
*/
int GetKeyDown()
{
	if (_kbhit() != 0)
		return _getch();

	return 0;
}

/**
Ŀ�� ���� ���� (Ŀ�� �Ⱥ��̱�)
@param
@return
*/
void CursorSettings()
{
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

/**
Ŀ�� �ű��
@param		_nX		X��ġ
@param		_nY		Y��ġ
@return
*/
void SetKeyCursor(int _nX, int _nY)
{
	COORD cursorPos = { (SHORT)_nX, (SHORT)_nY };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
}

/**
������ �׸���
@param		nScore	����
@return
*/
void DrawScore(int nScore)
{
	SetKeyCursor(0, 0);
	printf("Score : %d\n", nScore);
}

/**
���� �׸���
@param		nY		������ Y��ġ
@return
*/
void DrawDino(int nY)
{
	static bool bFootToggle = false;	// ���� �׸��Ⱑ ���ŵ� �� ���� ��ġ�� �ٲ�
	SetKeyCursor(0, Y_BASE - nY);		// ������ �׸��� ��ġ ����

	PRINTLN("    ���");
	PRINTLN("    ��");
	PRINTLN("�����");
	if (bFootToggle)
		PRINTLN("  ��")
	else
		PRINTLN("    ��")

		bFootToggle = !bFootToggle;
}

/**
���� �׸���
@param		nX		������ X��ġ
@return
*/
void DrawTree(int nX)
{
	if (nX >= 0)
	{
		SetKeyCursor(nX, Y_BASE);
		PRINTLN("    ��");
		SetKeyCursor(nX, Y_BASE + 1);
		PRINTLN("��  ��");
		SetKeyCursor(nX, Y_BASE + 2);
		PRINTLN("����");
		SetKeyCursor(nX, Y_BASE + 3);
		PRINTLN("  ��");
	}
	else if (nX >= -2)
	{
		nX = 0;
		SetKeyCursor(nX, Y_BASE);
		PRINTLN("  ��");
		SetKeyCursor(nX, Y_BASE + 1);
		PRINTLN("  ��");
		SetKeyCursor(nX, Y_BASE + 2);
		PRINTLN("���");
		SetKeyCursor(nX, Y_BASE + 3);
		PRINTLN("��");
	}
	else if (nX >= -4)
	{
		nX = 0;
		SetKeyCursor(nX, Y_BASE);
		PRINTLN("��");
		SetKeyCursor(nX, Y_BASE + 1);
		PRINTLN("��");
		SetKeyCursor(nX, Y_BASE + 2);
		PRINTLN("��");
		SetKeyCursor(nX, Y_BASE + 3);
		PRINTLN("");
	}
}

/**
���� ����
@param
@return
*/
void GameStart()
{
	int nScore = 0;				// ����
	int nCurKey = -1;			// ���� ���� Ű

	int nYPos = 0;				// ������ Y��ġ (������ ����)
	int nTreePos = TREE_START;	// ������ �����Ǵ� �ʱ� X��ġ

	bool bIsJumpping = false;	// ���� ������ ���� ���ΰ�
	bool bIsJumpped = false;	// ���� ������ �����Ͽ� �ְ� ������ �ö��°�
	bool bIsCollision = false;	// ���� ������ ������ �浹�Ͽ��°�

	while (true)
	{
		// ���� ���
		DrawScore(nScore);

		// Ű �Է� Ȯ��
		nCurKey = GetKeyDown();
		switch (nCurKey)
		{
		case KEY_ESC:		// ESC Ű
			return;
		case KEY_SPACE:		// SPACE BAR Ű
			bIsJumpping = true;
			break;
		default:
			break;
		}

		// ���� ����
		// ���� ���ΰ�
		if (bIsJumpping)
		{
			// �ְ� ������ �̸��� �ʾҴٸ�
			if (nYPos < MAX_JUMP &&
				bIsJumpped == false)
				nYPos++;
			// �ְ� ������ ���� �� ������ �����ٸ�
			else if (bIsJumpped &&
				nYPos == 0)
			{
				bIsJumpped = false;
				bIsJumpping = false;
			}
			// �ְ� ������ ���� �Ķ�� (�߷��� ǥ��)
			else if (bIsJumpped)
				nYPos--;
			// �ְ� ������ �����ߴٸ�
			else if (nYPos == MAX_JUMP)
				bIsJumpped = true;
		}
		// ���� ���� �ƴ϶��
		else
		{
			if (nYPos > 0)
				nYPos--;
		}

		// ���� ��ġ ����
		if (nTreePos > TREE_END)
			nTreePos -= 2;
		else
			nTreePos = TREE_START;

		// �浹 ����
		// ������ X��ġ�� �浹 ���� X��ġ���
		if (nTreePos < TREE_COLLISION)
		{
			// ������ Y��ġ�� �浹 ���� ��ġ�̰�
			// ������ X��ġ�� �浹 ���� ��ġ���
			if (nYPos < Y_COLLISION &&
				nTreePos > TREE_END + 1)
				bIsCollision = true;
		}

		// ���� �׸���
		DrawTree(nTreePos);
		// ���� �׸���
		DrawDino(nYPos);

		Sleep(SLEEP_TIME);
		system("cls");

		// �浹 �� ���� ����
		if (bIsCollision)
		{
			printf("\n");
			printf("\n");
			printf("            Game Over\n");
			printf("           Score : %d\n", nScore);
			system("pause");
			return;
		}
		// �浹 ���°� �ƴ� ���� ���� ����
		else
		{
			nScore += 1;
		}
	}
}

int main(void)
{
	CursorSettings();
	GameStart();
	GameStart();




	return 0;
}