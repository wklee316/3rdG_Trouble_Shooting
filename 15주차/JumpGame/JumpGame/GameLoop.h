#pragma once
#include <chrono>
#include <thread>
#include <iostream>
#include <string>
#include <vector>
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
		GameUtil::gameManager gm;
		vector<GameUtil::gameObject*> objectPool;

		vector<char> screenBuffer;

		const int SCREEN_WIDTH = 80;    // 화면 가로 크기
		const int SCREEN_HEIGHT = 20;   // 화면 세로 크기



		void ClearScreenBuffer(vector<char>& screenBuffer) {
			// 스크린 버퍼를 공백으로 초기화
			screenBuffer.assign(SCREEN_WIDTH * SCREEN_HEIGHT, ' ');
		}

		void DrawScreenBuffer(const std::vector<char>& screenBuffer) {
			// 스크린 버퍼를 화면에 그리기
			for (int y = 0; y < SCREEN_HEIGHT; ++y) {
				for (int x = 0; x < SCREEN_WIDTH; ++x) {
					std::cout << screenBuffer[y * SCREEN_WIDTH + x];
				}
				std::cout << '\n';
			}
		}

	public:
		Scene() {
			screenBuffer.resize(SCREEN_WIDTH * SCREEN_HEIGHT);

		}
		~Scene() {}

		int update() {
			switch (gm.update())		//0 : 정상   1 : 게임 오버
			{
			case 0:
				return 0;
				break;
			case 1:
				return 1;
				break;
			default:
				break;
			}
			
		}

		int GetKeyDown(int a) {
			switch (gm.GetKeyDown(a))			// 0 : spacebar    1: p  2: q  7 : default
			{
			case 0:
				return 0;
				break;
			case 1:
				return 1;
				break;
			case 2:
				return 2;
				break;
			default:
				return 7;
				break;
			}
		}

		void draw() {
			ClearScreenBuffer(screenBuffer);

			system("cls");
			DrawScreenBuffer(screenBuffer);
		}

		void init() {
			objectPool.clear();
			objectPool.push_back(new GameUtil::Player(2,10));			//player
			objectPool.push_back(new GameUtil::BackGround(0, 0, 0));	// 바닥
			objectPool.push_back(new GameUtil::BackGround(20, 4, 1));	// 구름
			objectPool.push_back(new GameUtil::BackGround(60, 4, 1));	// 구름
			objectPool.push_back(new GameUtil::BackGround(40, 8, 2));	// 산
			objectPool.push_back(new GameUtil::Block(80, 80, 0));		//장애물
			objectPool.push_back(new GameUtil::Block(80, 80, 0));		//장애물
			objectPool.push_back(new GameUtil::Block(80, 80, 0));		//장애물
			gm.init(objectPool);
		}
	};


	class MGameLoop
	{
	private:
		GameState Gstate;
		Scene scene;
		bool _isGameRunning;
		//MConsoleRenderer cRenderer;
		chrono::system_clock::time_point startRenderTimePoint;
		chrono::duration<double> renderDuration;

	public:
		MGameLoop() { Gstate = GameState::ready; }
		~MGameLoop() {}

		void Run()
		{
			_isGameRunning = true;
			Initialize();

			startRenderTimePoint = chrono::system_clock::now();
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
		void Release()
		{
		}

		void Input()
		{
			if (_kbhit() != 0) {
				int a = _getch();	
				switch (scene.GetKeyDown(a))			//  0 : spacebar  1: p  2:q  7 : default
				{
				case 0:
					if (Gstate == GameState::end || Gstate == GameState::ready) {
						Gstate == GameState::running;
					}
					else if (Gstate == GameState::stop) {
						Gstate == GameState::running;
					}
					break;
				case 1:
					if (Gstate == GameState::running) {
						Gstate == GameState::stop;
					}
					break;
				case 2:
					this->Stop();
					break;
				default:
					break;
				}
			}

		}
		void Update()
		{
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

			scene.draw();


			renderDuration = chrono::system_clock::now() - startRenderTimePoint;
			startRenderTimePoint = chrono::system_clock::now();
			string fps = "FPS : " + to_string(1.0 / renderDuration.count());
			//cRenderer.DrawString(fps);

			this_thread::sleep_for(chrono::milliseconds(20));
		}




	};

	
}