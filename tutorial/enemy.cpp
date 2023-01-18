#include "enemy.h"
#include "graphics.h"
#include "config.h"
#include <random>
#include "utility.h"
#include "game.h"


void Enemy::update()
{	
	pos_y -= speed * graphics::getDeltaTime();
	rotation += 0.05f * graphics::getDeltaTime();
	rotation = fmodf(rotation, 360);

	if (pos_y < -size)
	{
		active = false; 
	}
}

void Enemy::draw()
{
	if (game.status == Game::STATUS_PLAYING)
	{
		graphics::setOrientation(rotation);
		brush.texture = std::string(ASSET_PATH) + "covid1.png";
		graphics::drawRect(pos_x, pos_y, size, size, brush);
		brush.outline_opacity = 0.0f;
		graphics::resetPose();
	}
	else if (game.status == Game::STATUS_LEVEL2)
	{
		graphics::setOrientation(rotation);
		brush.texture = std::string(ASSET_PATH) + "covid2.png";
		graphics::drawRect(pos_x, pos_y, size, size, brush);
		brush.outline_opacity = 0.0f;
		graphics::resetPose();
	}
}

void Enemy::init()
{
	if (game.status == Game::STATUS_PLAYING) 
	{
		speed = 0.3f;
		size = 50 + 100 * rand0to1();
		pos_x = CANVAS_WIDTH * rand0to1();
		pos_y = CANVAS_HEIGHT + 1.1f * size;
		rotation = 360 * rand0to1();
	}
	else if (game.status == Game::STATUS_LEVEL2)
	{
		speed = 0.5f;
		size = 50 + 100 * rand0to1();
		pos_x = CANVAS_WIDTH * rand0to1();
		pos_y = CANVAS_HEIGHT + 1.1f * size;
		rotation = 360 * 0.75f;
	}

}

Enemy::Enemy(const Game& mygame)
	: GameObject(mygame)
{
	init();
}



Enemy::~Enemy()
{
}

Disk Enemy::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = size*0.45f;
	return disk;
	
}
