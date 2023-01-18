#include "game.h"
#include "graphics.h"
#include "config.h""

void Game::spawnBullet() 
{
	if (!bullet)
	{
		bullet = new Bullet(*this);

	}
} 

void Game::checkBullet() 
{
	if (bullet && !bullet->isActive())
	{
		delete bullet;
		bullet = nullptr; 
	}
}

void Game::spawnEnemy()
{
	if (!enemy) 
	{
			enemy = new Enemy(*this);
	}
}

void Game::checkEnemy()
{
	if (enemy && !enemy->isActive())
	{
		delete enemy;
		enemy = nullptr;
	}
}

bool Game::checkCollision() // check collision between player & enemy 
{
	if (!player || !enemy) 
	{
		return false;
	}
	Disk d1 = player->getCollisionHull();
	Disk d2 = enemy->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;
	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
	{
		player->drainLife(0.1f);
		return true;
	}
	else
		return false;

}

bool Game::checkDeath() // check collision between bullet & enemy
{
	if (!player || !bullet || !enemy)
		return false;
	Disk d3 = enemy->getCollisionHull();
	Disk d4 = bullet->getCollisionHull();
	float dx = d3.cx - d4.cx; 
	float dy = d3.cy - d4.cy;
	if (sqrt(dx * dx + dy * dy) < d3.radius + d4.radius)
	{
		
		return true;
	}
	else
		return false;
}

void Game::updateStartScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_TAB))
	{
		status = STATUS_PLAYING; 
	}

}

void Game::updateLevel1Screen()
{
	
	if (!player_initialized && graphics::getGlobalTime() > 1000)
	{
		player = new Player(*this);
		player_initialized = true;
	}
	if (player) {
		player->update();
		ppos_x = player->getPosX();
		ppos_y = player->getPosY();
		
	}
	
	checkEnemy();
	spawnEnemy();
	if (enemy)
		enemy->update();

	checkBullet();
	spawnBullet();
	
	
	if((graphics::getKeyState(graphics::SCANCODE_SPACE)) && !(bullet->isActive())) // shoot & initialize bullet 
	{			
		bullet->pos_bx = ppos_x;
		bullet->pos_by = ppos_y;
		bullet->shot = true; 
		bullet->active = true;
	}
	
	if (bullet->shot) 
	{
		bullet->update();
	}
	
	if ((checkDeath()) || (bullet->getPosbY() > + 500)) // check if there was a collision or if bullet is out of canvas 
	{
		bullet->shot = false;
		bullet->active = false;
	} 
	if (checkCollision())
	{
		graphics::playSound(std::string(ASSET_PATH) + "boom.mp3", 0.3f, false); // sound effect for collision between player & enemy 
		delete enemy; // enemy disappears 
		enemy = nullptr;
	}
	if (checkDeath()) // bullet and enemy disappear after their collision 
	{
		delete bullet; 
		bullet = nullptr; 
		delete enemy; 
		enemy = nullptr;
		score++;
	}
	if (player->life <= 0) 
	{
		graphics::playSound(std::string(ASSET_PATH) + "sad.mp3", 0.3f, false); // sound effect for player's death 
		status = STATUS_END; // end of level screen 
	}
	if (score >=  10) 
	{
		status = STATUS_LEVEL2;
	}
}

void Game::updateLevel2Screen()
{
	if (!player_initialized && graphics::getGlobalTime() > 1000)
	{
		player = new Player(*this);
		player_initialized = true;
	}
	if (player) {
		player->update();
		ppos_x = player->getPosX();
		ppos_y = player->getPosY();

	}

	checkEnemy();
	spawnEnemy();
	if (enemy)
		enemy->update();

	checkBullet();
	spawnBullet();


	if ((graphics::getKeyState(graphics::SCANCODE_SPACE)) && !(bullet->isActive())) // shoot & initialize bullet 
	{
		bullet->pos_bx = ppos_x;
		bullet->pos_by = ppos_y;
		bullet->shot = true;
		bullet->active = true;
	}

	if (bullet->shot)
	{
		bullet->update();
	}

	if ((checkDeath()) || (bullet->getPosbY() > +500)) // check if there was a collision or if bullet is out of canvas 
	{
		bullet->shot = false;
		bullet->active = false;
	}
	if (checkCollision())
	{
		graphics::playSound(std::string(ASSET_PATH) + "boom.mp3", 0.3f, false); // sound effect for collision between player & enemy 
		delete enemy; // enemy disappears 
		enemy = nullptr;
	}
	if (checkDeath()) // bullet and enemy disappear after their collision 
	{
		delete bullet;
		bullet = nullptr;
		delete enemy;
		enemy = nullptr;
		score++;
	}
	if (player->life <= 0)
	{
		graphics::playSound(std::string(ASSET_PATH) + "sad.mp3", 0.3f, false); // sound effect for player's death 
		status = STATUS_END; // end of level screen 
	}
}

void Game::updateEndScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_TAB)) //restart game 
	{
		player->life = 1.0f;
		status	= STATUS_PLAYING;
		score = 0;
	}

}

void Game::drawStartScreen()
{
	graphics::Brush br1;
	char info[40];
	char info1[40];

	
	br1.fill_color[0] = 0.0f;
	br1.fill_color[1] = 0.0f;
	br1.fill_color[2] = 0.6f;
	br1.fill_opacity = 1.0f;
	br1.gradient = false;
	//draw starting text 
	sprintf_s(info1, "Welcome to KUNGFLU-21.");
	sprintf_s(info, "Press TAB to start!");
	graphics::drawText(CANVAS_WIDTH /3, CANVAS_HEIGHT /3, 30, info1, br1);
	graphics::drawText(CANVAS_WIDTH/ 3 , CANVAS_HEIGHT/2 , 30, info, br1);

	//draw background
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "bg1.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
}

void Game::drawLevel1Screen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "bg2.png";
	br.outline_opacity = 0.0f;

	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	// draw background
	graphics::Brush br2;
	char info2[60];

	br2.fill_color[0] = 0.0f;
	br2.fill_color[1] = 0.0f;
	br2.fill_color[2] = 0.6f;
	br2.fill_opacity = 1.0f;
	br2.gradient = false;
	//draw starting text 
	sprintf_s(info2, "Press SPACE to shoot the virus and save the city!");
	tpos_x += (CANVAS_WIDTH / 6) + ( 2.0f * graphics::getDeltaTime() / 10.0f) ;
	graphics::drawText(tpos_x, CANVAS_HEIGHT / 3, 30, info2, br2);

	
	// draw player , draw enemy 
	if (player)
	{
		player->draw();
		
	}

	if (enemy)
		enemy->draw();

	if (bullet)
		bullet->draw();


	float player_life = player ? player->getRemainingLife() : 0.0f;

	// draw 2 rectangles for life function 
	br.outline_opacity = 0.0f;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.2f;
	br.texture = "";
	br.fill_secondary_color[0] = 1.0f * (1.0f - player_life) + player_life * 0.2f;
	br.fill_secondary_color[1] = 0.2f * (1.0f - player_life) + player_life * 1.0f;
	br.fill_secondary_color[2] = 0.2f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 100 - ((1.0f - player_life) * 120 / 2), 30, player_life * 120, 20, br);

	br.outline_opacity = 1.0f;
	br.gradient = false;
	br.fill_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 100, 30, 120, 20, br);

	// draw heart 
	graphics::Brush brh;
	brh.texture = std::string(ASSET_PATH) + "heart1.png";
	brh.outline_opacity = 0.0f;
	graphics::setOrientation(0.f);
	graphics::drawRect(CANVAS_WIDTH - 153, 25, 60, 60, brh);

	// draw score 
	char info3[20];
	sprintf_s(info3, "SCORE: %d " ,score);
	graphics::drawText(30, 30, 20, info3, br2);


	//draw level text 
	char info4[40];
	sprintf_s(info4, "LEVEL 1");
	graphics::drawText(30, 480, 30, info4, br2);


}

void Game::drawLevel2Screen()
{
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "bg2.png";
	br.outline_opacity = 0.0f;

	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);
	// draw background
	graphics::Brush br2;
	char info4[40];

	br2.fill_color[0] = 0.0f;
	br2.fill_color[1] = 0.0f;
	br2.fill_color[2] = 0.6f;
	br2.fill_opacity = 1.0f;
	br2.gradient = false;
	//draw starting text 
	sprintf_s(info4, "LEVEL 2");

	graphics::drawText(tpos_x, CANVAS_HEIGHT / 2, 50, info4, br2);


	// draw player , draw enemy 
	if (player)
	{
		player->draw();

	}

	if (enemy)
		enemy->draw();

	if (bullet)
		bullet->draw();


	float player_life = player ? player->getRemainingLife() : 0.0f;

	// draw 2 rectangles for life function 
	br.outline_opacity = 0.0f;
	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.2f;
	br.texture = "";
	br.fill_secondary_color[0] = 1.0f * (1.0f - player_life) + player_life * 0.2f;
	br.fill_secondary_color[1] = 0.2f * (1.0f - player_life) + player_life * 1.0f;
	br.fill_secondary_color[2] = 0.2f;
	br.gradient = true;
	br.gradient_dir_u = 1.0f;
	br.gradient_dir_v = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 100 - ((1.0f - player_life) * 120 / 2), 30, player_life * 120, 20, br);

	br.outline_opacity = 1.0f;
	br.gradient = false;
	br.fill_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH - 100, 30, 120, 20, br);

	// draw heart 
	graphics::Brush brh;
	brh.texture = std::string(ASSET_PATH) + "heart1.png";
	brh.outline_opacity = 0.0f;
	graphics::setOrientation(0.f);
	graphics::drawRect(CANVAS_WIDTH - 153, 25, 60, 60, brh);

	// draw score 
	char info3[20];
	sprintf_s(info3, "SCORE: %d ", score);
	graphics::drawText(30, 30, 20, info3, br2);

	//draw level text 
	char info5[40];
	sprintf_s(info5, "LEVEL 2");
	graphics::drawText(30, 480, 30, info5, br2);

}

void Game::drawEndScreen()
{
	graphics::Brush br1;
	char info[40];
	char info1[40];

	br1.fill_color[0] = 0.0f;
	br1.fill_color[1] = 0.0f;
	br1.fill_color[2] = 0.6f;
	br1.fill_opacity = 1.0f;
	br1.gradient = false;
	//draw starting text 
	sprintf_s(info1, "You lost. You failed to save the city!");
	sprintf_s(info, "Press TAB to play again!");
	graphics::drawText(CANVAS_WIDTH / 4, CANVAS_HEIGHT / 3, 30, info1, br1);
	graphics::drawText(CANVAS_WIDTH / 4, CANVAS_HEIGHT / 2, 30, info, br1);

	//draw background
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "bg1.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);



	
}

void Game::update()


{
	if (status == STATUS_START)
	{
		updateStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		updateLevel1Screen();
	}
	else if (status == STATUS_LEVEL2)
	{
		updateLevel2Screen();
	}
	else if (status == STATUS_END)
	{
		updateEndScreen();
	}
	
}

void Game::draw()
{
	if (status == STATUS_START)
	{
		drawStartScreen();
	}
	else if (status == STATUS_PLAYING)
	{
		drawLevel1Screen();
	}
	else if (status == STATUS_LEVEL2)
	{
		drawLevel2Screen();
	}
	else if (status == STATUS_END)
	{
		drawEndScreen(); 
	}

}

void Game::init()
{
	graphics::setFont(std::string(ASSET_PATH) + "myfont.otf");
	
}


Game::Game()
{
}

Game::~Game()
{
	if (player) 
	{
		delete player;
	}
}
