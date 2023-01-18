#pragma once
#include "gameObject.h"
#include "config.h"
#include <algorithm> 

class Player : public GameObject, public Collidable
{
	float speed = 5.0f;
	public:float pos_x = CANVAS_WIDTH / 2;
	public:float pos_y = CANVAS_HEIGHT /6 ;
	float height = 1.0f;
	float life = 1.0f;
	float size = 60.0f;
public:
	Player(const class Game& mygame);
	void update() override;
	void draw() override;
	void init() override;
	float getPosY() { return pos_y; }
	float getPosX() { return pos_x; }
	Disk getCollisionHull() const override;
	float getRemainingLife() const { return life; }
	void drainLife(float amount) 
	{ 
		life = std::max<float>(0.0f, life - amount);
	}
}; 