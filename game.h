#pragma once
#include "player.h"
#include "enemy.h"
#include "bullet.h"

class Game
{
public: float ppos_x;
public: float ppos_y;
	
	typedef enum { STATUS_START, STATUS_PLAYING, STATUS_LEVEL2, STATUS_END } status_t;
	Player* player = nullptr;
	bool player_initialized = false;
	bool debug_mode = false;
	Enemy* enemy = nullptr;
	Bullet *bullet=nullptr;
	int size = 10;
	int fade_time = 0;
	float tpos_x;
	int score = 0;
	

	  void spawnBullet();
	  void checkBullet();
	  void spawnEnemy();
	  void checkEnemy();
	  bool checkCollision();
	  bool checkDeath();
	  status_t status = STATUS_START;

	  
	  void updateStartScreen();
	  void updateLevel1Screen();
	  void updateLevel2Screen();
	  void updateEndScreen();
	  void drawStartScreen();
	  void drawLevel1Screen();
	  void drawLevel2Screen();
	  void drawEndScreen();
	 
public:
	void update();
	void draw();
	void init();
	Game();
	~Game();

};