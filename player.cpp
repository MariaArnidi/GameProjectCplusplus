#include "player.h"
#include "graphics.h"
#include "game.h"
Player::Player(const Game& mygame)
	: GameObject(mygame)
{
}

void Player::update()
{

	if (graphics::getKeyState(graphics::SCANCODE_LEFT))
	{
		pos_x -= speed * graphics::getDeltaTime() / 10.0f;
	
	}

	if (graphics::getKeyState(graphics::SCANCODE_RIGHT))
	{
		pos_x += speed * graphics::getDeltaTime() / 10.0f;
		
	}

	if (pos_x < 0) pos_x = 0;
	if (pos_x > CANVAS_WIDTH) pos_x = CANVAS_WIDTH;
	if (pos_y < 0) pos_y = 0;
	if (pos_y > CANVAS_HEIGHT) pos_y = CANVAS_HEIGHT;

}

void Player::draw()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "emoji.png";
	br.outline_opacity = 0.0f; 
	graphics::setOrientation(0.f);
	graphics::setScale(height, height);
	graphics::drawRect(pos_x, pos_y, 60, 60, br);
	graphics::setOrientation(0.f);
}

void Player::init()
{
}

Disk Player::getCollisionHull() const
{
	Disk disk;
	disk.cx = pos_x;
	disk.cy = pos_y;
	disk.radius = 55.0f;
	return disk;
}
