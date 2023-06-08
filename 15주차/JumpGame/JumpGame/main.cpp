#include "GameLoop.h"

#define PRINTLN(STR)	{printf(STR);printf("\n");}

constexpr int KEY_ESC = 27;			// ESC 키
constexpr int KEY_SPACE = 32;		// SpaceBar 키

constexpr int MAX_JUMP = 6;			// 최대 점프 높이
constexpr int Y_BASE = 10;			// 공룡의 초기 Y축 위치
constexpr int Y_COLLISION = 4;		// Y축의 충돌 기준 위치
constexpr int TREE_COLLISION = 7;	// 나무가 공룡과 충돌 가능한 X축 위치
constexpr int TREE_START = 80;		// 나무가 생성되는 위치
constexpr int TREE_END = -6;		// 나무가 사라지는 위치
constexpr int SLEEP_TIME = 35;		// 게임 갱신 주기


/**
키 눌림 확인
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
커서 관련 설정 (커서 안보이기)
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
커서 옮기기
@param		_nX		X위치
@param		_nY		Y위치
@return
*/
void SetKeyCursor(int _nX, int _nY)
{
	COORD cursorPos = { (SHORT)_nX, (SHORT)_nY };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
}

/**
점수판 그리기
@param		nScore	점수
@return
*/
void DrawScore(int nScore)
{
	SetKeyCursor(0, 0);
	printf("Score : %d\n", nScore);
}

/**
공룡 그리기
@param		nY		공룡의 Y위치
@return
*/
void DrawDino(int nY)
{
	static bool bFootToggle = false;	// 공룡 그리기가 갱신될 때 발의 위치를 바꿈
	SetKeyCursor(0, Y_BASE - nY);		// 공룡의 그리기 위치 변경

	PRINTLN("    ■■");
	PRINTLN("    ■");
	PRINTLN("■■■■");
	if (bFootToggle)
		PRINTLN("  ■")
	else
		PRINTLN("    ■")

		bFootToggle = !bFootToggle;
}

/**
나무 그리기
@param		nX		나무의 X위치
@return
*/
void DrawTree(int nX)
{
	if (nX >= 0)
	{
		SetKeyCursor(nX, Y_BASE);
		PRINTLN("    ■");
		SetKeyCursor(nX, Y_BASE + 1);
		PRINTLN("■  ■");
		SetKeyCursor(nX, Y_BASE + 2);
		PRINTLN("■■■");
		SetKeyCursor(nX, Y_BASE + 3);
		PRINTLN("  ■");
	}
	else if (nX >= -2)
	{
		nX = 0;
		SetKeyCursor(nX, Y_BASE);
		PRINTLN("  ■");
		SetKeyCursor(nX, Y_BASE + 1);
		PRINTLN("  ■");
		SetKeyCursor(nX, Y_BASE + 2);
		PRINTLN("■■");
		SetKeyCursor(nX, Y_BASE + 3);
		PRINTLN("■");
	}
	else if (nX >= -4)
	{
		nX = 0;
		SetKeyCursor(nX, Y_BASE);
		PRINTLN("■");
		SetKeyCursor(nX, Y_BASE + 1);
		PRINTLN("■");
		SetKeyCursor(nX, Y_BASE + 2);
		PRINTLN("■");
		SetKeyCursor(nX, Y_BASE + 3);
		PRINTLN("");
	}
}

/**
게임 시작
@param
@return
*/
void GameStart()
{
	int nScore = 0;				// 점수
	int nCurKey = -1;			// 현재 눌린 키

	int nYPos = 0;				// 공룡의 Y위치 (점프에 쓰임)
	int nTreePos = TREE_START;	// 나무가 생성되는 초기 X위치

	bool bIsJumpping = false;	// 현재 공룡이 점프 중인가
	bool bIsJumpped = false;	// 현재 공룡이 점프하여 최고 지점에 올랐는가
	bool bIsCollision = false;	// 현재 공룡이 나무와 충돌하였는가

	while (true)
	{
		// 점수 출력
		DrawScore(nScore);

		// 키 입력 확인
		nCurKey = GetKeyDown();
		switch (nCurKey)
		{
		case KEY_ESC:		// ESC 키
			return;
		case KEY_SPACE:		// SPACE BAR 키
			bIsJumpping = true;
			break;
		default:
			break;
		}

		// 점프 관련
		// 점프 중인가
		if (bIsJumpping)
		{
			// 최고 지점에 이르지 않았다면
			if (nYPos < MAX_JUMP &&
				bIsJumpped == false)
				nYPos++;
			// 최고 지점에 도달 후 점프가 끝났다면
			else if (bIsJumpped &&
				nYPos == 0)
			{
				bIsJumpped = false;
				bIsJumpping = false;
			}
			// 최고 지점에 도달 후라면 (중력을 표현)
			else if (bIsJumpped)
				nYPos--;
			// 최고 지점에 도달했다면
			else if (nYPos == MAX_JUMP)
				bIsJumpped = true;
		}
		// 점프 중이 아니라면
		else
		{
			if (nYPos > 0)
				nYPos--;
		}

		// 나무 위치 관련
		if (nTreePos > TREE_END)
			nTreePos -= 2;
		else
			nTreePos = TREE_START;

		// 충돌 관련
		// 나무의 X위치가 충돌 가능 X위치라면
		if (nTreePos < TREE_COLLISION)
		{
			// 공룡의 Y위치가 충돌 가능 위치이고
			// 나무의 X위치가 충돌 가능 위치라면
			if (nYPos < Y_COLLISION &&
				nTreePos > TREE_END + 1)
				bIsCollision = true;
		}

		// 나무 그리기
		DrawTree(nTreePos);
		// 공룡 그리기
		DrawDino(nYPos);

		Sleep(SLEEP_TIME);
		system("cls");

		// 충돌 시 게임 오버
		if (bIsCollision)
		{
			printf("\n");
			printf("\n");
			printf("            Game Over\n");
			printf("           Score : %d\n", nScore);
			system("pause");
			return;
		}
		// 충돌 상태가 아닐 때는 점수 증가
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