#pragma once
#include "gameObject.h"
#include "graphics.h"
class Enemy : public GameObject, public Collidable
{
public: float pos_x, pos_y; 
	float speed;
	float size;
	float rotation;
	class graphics::Brush brush;
	bool active = true; 
	

public:
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }
	Enemy(const class Game& mygame);
	~Enemy();
	Disk getCollisionHull() const override;
};
