#pragma once
#include "graphics.h"
#include "config.h"
#include "gameObject.h"
#include "player.h";
#include "utility.h"

using namespace std; 
class Bullet : public GameObject, public Collidable 
{
public:bool shot = false;
public:float pos_bx = -100.0f;
public:float pos_by = -100.0f;
	float speed;
	float size;
	bool active = false; 
	class graphics::Brush br;
	float rotation;


	public:
	Bullet(const class Game& mygame);
	~Bullet();
	void update() override;
	void draw() override;
	void init() override;
	bool isActive() { return active; }
	float getPosbY() { return pos_by; }
	float getPosbX() { return pos_bx; }
	Disk getCollisionHull() const override;
	
};