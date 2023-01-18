#include "bullet.h"
#include "graphics.h"
#include "config.h"
#include "utility.h"
#include "player.h"
#include "gameObject.h"
#include "enemy.h"
#include "game.h"

using namespace std;

Bullet::Bullet(const Game & mygame)
	: GameObject(mygame) 
{
	init();
}

Bullet::~Bullet()
{
}



void Bullet::update()
{
	pos_by += speed* graphics::getDeltaTime();
	rotation += 0.3f * graphics::getDeltaTime();
	rotation = fmodf(rotation, 360);	
	if (pos_by < -size) 

	{
		active = false;
	}
	
}

void Bullet::draw()
{
	graphics::setOrientation(rotation);
	br.texture = std::string(ASSET_PATH) + "syringe.png";
	graphics::drawRect(pos_bx, pos_by, size, size, br);
	br.outline_opacity = 0.0f;
	graphics::resetPose();
}

void Bullet::init()
{
	speed = 0.5f;
	size = 80.f;
}
Disk Bullet::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_bx;
	disk.cy = pos_by;
	disk.radius = size*0.45f;
	return disk;
	return Disk(); 
}

