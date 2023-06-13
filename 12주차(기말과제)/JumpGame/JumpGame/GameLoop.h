#pragma once
#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <Windows.h>
#include <conio.h>


using namespace std;

#include "GameUtil.h"

enum GameState {
	ready,
	running,
	stop,
	end
};

namespace GameLoop
{

	class Scene {
	private:
		GameUtil::gameManager* gm;
		vector<GameUtil::gameObject*> objectPool;

		vector<char> screenBuffer;

		const int SCREEN_WIDTH = 80;    // 화면 가로 크기
		const int SCREEN_HEIGHT = 20;   // 화면 세로 크기

		vector<int> ranking;
		string filename = "ranking.txt";
		string mapName = "map.txt";



		void ClearScreenBuffer(vector<char>& screenBuffer) {
			// 스크린 버퍼를 공백으로 초기화
			screenBuffer.assign((SCREEN_WIDTH+1) * SCREEN_HEIGHT, ' ');
			for (int a = 0; a < SCREEN_HEIGHT; ++a) {
				screenBuffer[SCREEN_WIDTH * a] = '\n';
			}
		}

		void DrawScreenBuffer(const vector<char>& screenBuffer) {
			// 스크린 버퍼를 화면에 그리기
			std::cout.write(screenBuffer.data(), screenBuffer.size());
			std::cout << std::endl;
		}

		void updateRanking(std::vector<int>& ranking, int newScore) {
			ranking.push_back(newScore);
			std::sort(ranking.begin(), ranking.end(), std::greater<int>());
			if (ranking.size() > 10) {
				ranking.resize(10);
			}
		}

		void recordRanking(const std::vector<int>& ranking, const std::string& filename) {
			std::ofstream outputFile(filename);
			if (outputFile.is_open()) {
				for (const int& score : ranking) {
					outputFile << score << std::endl;
				}
				outputFile.close();
			}
		}

	public:
		Scene() {
			screenBuffer.resize((SCREEN_WIDTH+1) * SCREEN_HEIGHT);
			ifstream mapFile(mapName);
			string line;
			getline(mapFile, line);
			mapFile.close();
			

			objectPool.clear();
			objectPool.push_back(new GameUtil::Player(4, 12));			//player
			objectPool.push_back(new GameUtil::BackGround(0, 0, 0, 0));	// 바닥
			objectPool.push_back(new GameUtil::BackGround(20, 3, 1, 0.6f));	// 구름
			objectPool.push_back(new GameUtil::BackGround(60, 3, 1, 0.6f));	// 구름
			objectPool.push_back(new GameUtil::BackGround(40, 8, 2, 0.2f));	// 산
			objectPool.push_back(new GameUtil::Block(80, 80, 0));		//장애물
			objectPool.push_back(new GameUtil::Block(80, 80, 0));		//장애물
			objectPool.push_back(new GameUtil::Block(80, 80, 0));		//장애물

			gm = new GameUtil::gameManager(objectPool, line);
		}
		~Scene() {}

		int update() {
			switch (gm->update())		//0 : 정상   1 : 게임 오버
			{
			case 0:
				return 0;
				break;
			case 1:
				ifstream inputFile(filename);
				ranking.clear();
				if (inputFile.is_open()) {
					string line;
					while (std::getline(inputFile, line)) {
						int score = std::stoi(line);
						ranking.push_back(score);
					}
					inputFile.close();
				}


				updateRanking(ranking, gm->getScore());
				recordRanking(ranking, filename);
				return 1;
				break;
			}
			
		}

		void GetKeyDown(int a) {
			gm->GetKeyDown(a);
		}

		void draw() {
			ClearScreenBuffer(screenBuffer);

			system("cls");
			for (int i = 0; i < objectPool.size(); i++) {
				objectPool[i]->draw(screenBuffer);
			}
			
			DrawScreenBuffer(screenBuffer);
			gm->printScore();
			
		}

		void printGaO() {
			system("cls");
			system("color 0f");
			int raw = 2;
			COORD cursorPos = { (SHORT)35, (SHORT)raw };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
			cout << "GAME OVER";



			for (int i = 0; i < ranking.size(); i++) {
				raw++;
				COORD cursorPos = { (SHORT)36, (SHORT)raw };
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
				cout << i + 1 << ". " << ranking[i];
			}
			cursorPos = { (SHORT)15, (SHORT)(raw+2) };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
			cout << "다시 시작하려면 스페이스바, 종료하려면 q를 입력하세요";
		}

		void printOpen() {
			system("cls");
			COORD cursorPos = { (SHORT)35, (SHORT)10 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
			cout << "JUMP GAME";
			cursorPos = { (SHORT)26, (SHORT)12 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
			cout << "스페이스바를 눌러 시작하세요";
		}

		void init() {
			ranking.clear();
			gm->init();
		}
	};


	class MGameLoop
	{
	private:
		GameState Gstate;
		Scene scene;
		bool _isGameRunning;
		//MConsoleRenderer cRenderer;

	public:
		MGameLoop() { 
			system("mode con cols=80 lines=23");
			CONSOLE_CURSOR_INFO cursorInfo = { 0, };
			cursorInfo.dwSize = 1;
			cursorInfo.bVisible = FALSE;
			SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
			Gstate = GameState::ready; 
		}
		~MGameLoop() {}

		void Run()
		{
			_isGameRunning = true;
			Initialize();

			while (_isGameRunning)
			{

				Input();
				Update();
				Render();

			}
			Release();
		}
		void Stop()
		{
			_isGameRunning = false;
		}

	private:
		void Initialize()
		{
			scene.init();
		}

		void Input()
		{
			if (_kbhit() != 0) {
				int a = _getch();	

				switch (Gstate)
				{
				case GameState::ready:
					if (a == 32) {
						scene.init();
						Gstate = GameState::running;
					}
					break;
				case GameState::running:
					scene.GetKeyDown(a);
					if (a == 'p') {
						Gstate = GameState::stop;
						COORD cursorPos = { (SHORT)70, (SHORT)3 };
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
						cout << "PAUSE";
					}
					else if (a == 'q') {
						this->Stop();
					}
					break;
				case GameState::stop:
					if (a == 32) {
						Gstate = GameState::running;
					}
					else if (a == 'q')
						this->Stop();
					break;
				case GameState::end:
					if (a == 32) {
						scene.init();
						Gstate = GameState::running;
					}
					else if(a == 'q')
						this->Stop();
					break;
				}

			}

		}
		void Update()
		{
			if (Gstate != GameState::running) return;

			switch (scene.update())			//0: 정상    1: 게임오버
			{
			case 0:
				break;
			case 1:
				Gstate = GameState::end;
			default:
				break;
			}
			
		}
		void Render()
		{
			switch (Gstate)
			{
			case GameState::ready:
				scene.printOpen();
				break;
			case GameState::running:
				scene.draw();
				break;
			case GameState::end:
				scene.printGaO();
				break;
			}
			

			Sleep(100/6);
		}




	};

	
}