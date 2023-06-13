#pragma once


namespace GameUtil {

	void SetCharacter(vector<char>& screenBuffer, int width, int height, int x, int y, char c) {
		// 주어진 좌표에 문자를 설정
		if (x < 0 || x >= width || y < 0 || y >= height) {
			return;
		}
		screenBuffer[y * width + x] = c;
	}
	
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
		virtual void update() {

		}
		virtual void draw(vector<char>& screenBuffer) {

		}

		virtual void init() {

		}

		virtual void increSpeed(float s) {

		}
	};

	

	class Player : public gameObject {
	private:
		float oriY;
		bool isJumping;
		bool isPeek;

	public:
		Player(float a, float b) : gameObject(a, b) {
			oriY = b;
			isJumping = false;
			isPeek = false;
		}

		virtual void draw(vector<char>& screenBuffer) {
			SetCharacter(screenBuffer, 80, 20, int(x)-1, int(y)-1, 'o');
			SetCharacter(screenBuffer, 80, 20, int(x), int(y)-1, 'o');
			SetCharacter(screenBuffer, 80, 20, int(x)+1, int(y)-1, 'o');

			SetCharacter(screenBuffer, 80, 20, int(x)-1, int(y), 'o');
			SetCharacter(screenBuffer, 80, 20, int(x), int(y), 'o');
			SetCharacter(screenBuffer, 80, 20, int(x)+1, int(y), 'o');

		}
		virtual void update() {
			if (isJumping) {
				// 최고 지점에 이르지 않았다면
				if (this->y > oriY - 4 && isPeek == false) {
					y -= 0.6f;
					
				}
				// 최고 지점에 도달 후 점프가 끝났다면
				else if (isPeek && y >= oriY)
				{
					isJumping = false;
					isPeek = false;
					y = oriY;
					
				}
				// 최고 지점에 도달 후라면 (중력을 표현)
				else if (isPeek)
					y += 0.4f;
				// 최고 지점에 도달했다면
				else if (y <= oriY - 4)
					isPeek = true;
			}
		}

		virtual void init() {

		}

		void jump() {
			isJumping = true;
		}

		float getX() {
			return this->x;
		}
		float getY() {
			return this->y;
		}
	};

	class BackGround : public gameObject {
	private:
		int type;		// 0 : road   1 : cloud   2 : mountain
		float speed;
		float OriSpeed;
		float oriX, oriY;
	public:
		BackGround(float a, float b, int c, float s) : gameObject(a, b) {
			this->type = c;
			this->speed = s;
			this->OriSpeed = s;
			this->oriX = a;
			this->oriY = b;
		}

		virtual void update() {
			this->x -= speed;
			if (this->x < 1) {
				this->x = 80;
			}
		}

		virtual void init() {
			this->speed = this->OriSpeed;
			this->x = this->oriX;
			this->y = this->oriY;
		}

		virtual void draw(vector<char>& screenBuffer) {
			switch (type)
			{
			case 0:
				for (int i = 0; i < 80; i++) {
					SetCharacter(screenBuffer, 80, 20, i+1, 13, 'a');
				}
				break;
			case 1:
				SetCharacter(screenBuffer, 80, 20, int(x), int(y), '8');
				SetCharacter(screenBuffer, 80, 20, int(x) + 1, int(y), '8');
				SetCharacter(screenBuffer, 80, 20, int(x) + 2, int(y), '8');
				SetCharacter(screenBuffer, 80, 20, int(x) + 3, int(y), '8');
				break;
			case 2:
				SetCharacter(screenBuffer, 80, 20, int(x), int(y), 'M');
				SetCharacter(screenBuffer, 80, 20, int(x) + 1, int(y), 'M');
				SetCharacter(screenBuffer, 80, 20, int(x) + 1, int(y)-1, 'M');
				SetCharacter(screenBuffer, 80, 20, int(x) + 2, int(y), 'M');
				break;
			}
		}

		virtual void increSpeed(float s) {
			this->speed = this->speed * s;
		}
	};

	class Block : public gameObject {
	private:
		int type;			// 0 : fixedBlock    1 : moveBlock
		float peek;
		float speed;
		float upSpeed;
	public:
		Block(float a, float b, int c) : gameObject(a, b) {
			this->type = c;
			this->active = false;
			peek = 8;
			this->init();
		}

		virtual void draw(vector<char>& screenBuffer) {
			if (!(this->active)) return;

			SetCharacter(screenBuffer, 80, 20, int(x), int(y), '4');
			SetCharacter(screenBuffer, 80, 20, int(x), int(y)+1, '4');
		}

		virtual void update() {
			if (!(this->active)) return;
			if (type == 1) {
				if (this->y >= peek) {
					this->y -= this->upSpeed;
				}
			}

			this->x -= this->speed;

			if (x < 1) {
				this->active = false;
			}
		}

		virtual void init() {
			this->active = false;
			this->x = 79;
			this->y = 11;
			this->speed = 0.4f;
			this->upSpeed = 0.05f;
		}

		void inGinit() {
			this->active = false;
			this->x = 79;
			this->y = 11;
		}


		bool getActive() {
			return active;
		}

		void setActive(bool a) {
			active = a;
		}

		void setType(int a) {
			this->type = a;
		}

		float getX() {
			return this->x;
		}
		float getY() {
			return this->y;
		}

		virtual void increSpeed(float s) {
			this->speed = this->speed * s;
			this->upSpeed = this->upSpeed * s;
		}
	};

	class gameManager {
	private:
		int score;
		int stageState;
		float speed;
		float x;
		Player* p1;
		vector<GameUtil::gameObject*> objectPool;
		string mapStr;

		vector<Block*> blockPool;
	public:

		gameManager(vector<GameUtil::gameObject*>& objPool, string mS) {
			score = 0;
			speed = 1;
			x = 0;
			stageState = 0;
			objectPool = objPool;
			mapStr = mS;
			blockPool.push_back(dynamic_cast<Block*>(objPool[5]));
			blockPool.push_back(dynamic_cast<Block*>(objPool[6]));
			blockPool.push_back(dynamic_cast<Block*>(objPool[7]));
			p1 = dynamic_cast<Player*>(objPool[0]);
		}

		void changeStage() {
			stageState++;
			switch (stageState)
			{
			case 0:
				system("color 0f");
				break;
			case 1:
				system("color 05");
				break;
			case 2:
				system("color 09");
				break;
			case 3:
				system("color 0a");
				stageState = 0;
				break;
			}
		}
		int update() {
			//점수 증가, 점수 증가에 따른 속도, 오브젝트 update 문 돌리기, 충돌 판정 확인, 장애물 소환

			for (int i = 0; i < objectPool.size(); i++) {
				objectPool[i]->update();
			}

			


			score += 1;
			if (score % 10 == 0) {
				x++;
				if (x >= mapStr.length()) {
					x = 0;
				}
				else 
				{
					if (mapStr[int(x)] != '0') {
						createBlock(int(mapStr[int(x)]) - '0');
					}
					
				}
			}
			if (score % 200 == 0) {
				if(speed <= 1.6f)
					speed += 0.2f;

				for (int i = 1; i < objectPool.size(); i++) {
					objectPool[i]->increSpeed(speed);
				}
				changeStage();
			}

			if (isCollision())
				return 1;

			return 0;
		}

		int createBlock(int a) {
			int flag = 0;
			for (int i = 0; i < blockPool.size(); i++) {
				if (!(blockPool[i]->getActive())) {
					blockPool[i]->inGinit();
					blockPool[i]->setType(a-1);
					blockPool[i]->setActive(true);
					flag++;
					break;
				}
			}
			if (flag == 0)
				return -1;
			else
				return 1;
		}

		bool isCollision() {
			int flag = 0;
			for (int i = 0; i < blockPool.size(); i++) {
				if (!(blockPool[i]->getActive())) continue;

				if (p1->getX() + 1 < blockPool[i]->getX() || p1->getX() - 1 > blockPool[i]->getX()) continue;
				if (p1->getY() < blockPool[i]->getY() || p1->getY() - 1 > blockPool[i]->getY() + 1) continue;

				flag++;

			}
			if (flag == 0) return false;
			else return true;
		}
		void GetKeyDown(int a) {			// return    0 : spacebar    1: p      2 : q     7 : default
			switch (a)
			{
			case 32:
				p1->jump();
				break;
			case 'p':
				break;
			case 'q':
				break;
			}
		}

		void init() {
			score = 0;
			speed = 1;
			x = 0;
			stageState = 0;
			for (int i = 0; i < objectPool.size(); i++) {
				objectPool[i]->init();
			}
		}

		int getScore() {
			return this->score;
		}

		void printScore() {
			COORD cursorPos = { (SHORT)65, (SHORT)1 };
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cursorPos);
			cout << "SCORE : " << this->score;

		}
	};
}