#pragma once


namespace GameUtil {

	
	class gameObject {
	protected:
		float x, y;
		bool active;
	public:
		gameObject(float a, float b) {
			x = a;
			y = b;
			active = true;
		}
		virtual void draw(vector<char>& screenBuffer) {

		}
	};

	

	class Player : public gameObject {
	public:
		Player(float a, float b) : gameObject(a, b) {}

		virtual void draw(vector<char>& screenBuffer) {

		}

		void jump() {

		}
	};

	class BackGround : public gameObject {
	private:
		int type;		// 0 : road   1 : cloud   2 : mountain
	public:
		BackGround(float a, float b, int c) : gameObject(a, b) {
			this->type = c;
		}

		virtual void draw(vector<char>& screenBuffer) {

		}
	};

	class Block : public gameObject {
	private:
		int type;			// 0 : fixedBlock    1 : moveBlock
		
	public:
		Block(float a, float b, int c) : gameObject(a, b) {
			this->type = c;
			this->active = false;
			
		}

		virtual void draw(vector<char>& screenBuffer) {
		}
	};

	class gameManager {
	private:
		int score;
		float speed;
		vector<GameUtil::gameObject*> objectPool;

		vector<Block*> blockPool;
	public:
		gameManager() {

		}
		int update() {

		}


		int GetKeyDown(int a) {			// return    0 : spacebar    1: p      2 : q     7 : default
			switch (a)
			{
			case 32:
				return 0;
				
				break;
			case 'p':
				return 1;
				break;
			case 'q':
				return 2;
				break;
			default:
				break;
			}
		}

		void init(vector<GameUtil::gameObject*>& objPool) {
			
			score = 0;
			blockPool.push_back(dynamic_cast<Block*>(objectPool[5]));
			blockPool.push_back(dynamic_cast<Block*>(objectPool[6]));
			blockPool.push_back(dynamic_cast<Block*>(objectPool[7]));

		}
	};
}