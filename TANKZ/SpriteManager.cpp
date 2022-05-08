#include "SpriteManager.h"
//#include "baseTypes.h"
#include "openGLFramework.h"
#include "PlayerManager.h"
#include "openGLStuff.h"
//#include "Collider.h"

#include <malloc.h>
#include <windows.h>
#include<assert.h>

SpriteManager* SpriteManager::sInstance = nullptr;

SpriteManager* SpriteManager::createInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new SpriteManager();
	}
	return sInstance;
}

SpriteManager* SpriteManager::getInstance()
{
	return sInstance;
}

void SpriteManager::init()
{
	// Allocate memory for all the sprites
	spritePtrs = (Sprite**)malloc(NUM_SPRITES * sizeof(Sprite*));


	//Display loading screen while creating sprites
	spritePtrs[SpriteName::LOADING] = new Sprite(-515, -400, 1024, 800, "Sprites/SmallLoad.png", 4);
	spritePtrs[SpriteName::LOADING]->init();
	startOpenGLDrawing();
	spritePtrs[SpriteName::LOADING]->render();
	SwapBuffers(g_window->hDC);


	// Generate all sprites for the game
	initBackgroundSpritePtrs();
	initPlayerSpritePtrs();
	initBulletSpritePtrs();
	initIndicatorSpritePtrs();
	initBlockSpritePtrs();
	initLivesSpritePtrs();
	initGameDisplay();
	// 
	// 
	// Initialize all sprites
	spritePtrs[SpriteName::BULLET_A_1]->init();
	spritePtrs[SpriteName::BULLET_A_2]->init();
	spritePtrs[SpriteName::BULLET_A_3]->init();

	spritePtrs[SpriteName::BULLET_B_1]->init();
	spritePtrs[SpriteName::BULLET_B_2]->init();
	spritePtrs[SpriteName::BULLET_B_3]->init();

	spritePtrs[SpriteName::PLANE_A_1]->init();
	spritePtrs[SpriteName::PLANE_B_1]->init();

	spritePtrs[SpriteName::INDICATOR_A]->init();
	spritePtrs[SpriteName::INDICATOR_B]->init();

	spritePtrs[SpriteName::GAME_END_1]->init();
	spritePtrs[SpriteName::GAME_END_2]->init();
	spritePtrs[SpriteName::START_SCREEN]->init();

	spritePtrs[SpriteName::BACKGROUND]->init();



	for (int i = 0; i < numBlocks; i++) {
		spritePtrs[SpriteName::BLOCK_1 + i]->init();
	}


	// Initialize sprite rotations
	spritePtrs[SpriteName::INDICATOR_A]->setRotation(-90.0f);
	spritePtrs[SpriteName::INDICATOR_B]->setRotation(-90.0f);
}

void SpriteManager::initBackgroundSpritePtrs()
{
	spritePtrs[SpriteName::BACKGROUND] = new Sprite(-510, -380, 1024, 780, "Sprites/bg_glitchGarden-1920x1080.jpg", 0);
	
}

void SpriteManager::initPlayerSpritePtrs()
{
	// Initialize Player 1
	spritePtrs[SpriteName::PLANE_A_1] = new Sprite(0, 0, 50, 50, "Sprites/P1BaseRedTank.png", 1);
	
	// Initialize Player 2
	spritePtrs[SpriteName::PLANE_B_1] = new Sprite(100, 100, 50, 50, "Sprites/P2 BlueTank.png", 1);
}

void SpriteManager::initBulletSpritePtrs()
{
	// Initialize bullets for turret A
	for (uint8_t i = SpriteName::BULLET_A_1; i <= SpriteName::BULLET_A_3; i++)
	{
		spritePtrs[i] = new Sprite(25, 25, 25, 25, "Sprites/LivesA.png", 2);
	}
	// Initialize bullets for turret B
	for (uint8_t i = SpriteName::BULLET_B_1; i <= SpriteName::BULLET_B_3; i++)
	{
		spritePtrs[i] = new Sprite(890, 47, 25, 25, "Sprites/LivesB.png", 2);
	}
}

void SpriteManager::initIndicatorSpritePtrs()
{
	// Initialize Player 1
	//spritePtrs[SpriteName::INDICATOR_A] = new Sprite(4, 48, 50, 100, "Sprites/TurretNew4.png", 1);
	spritePtrs[SpriteName::INDICATOR_A] = new Sprite(-396, 23, 50, 65, "Sprites/TurretP1.png", 1);



	// Initialize Player 2
	//spritePtrs[SpriteName::INDICATOR_B] = new Sprite(104, 148, 50, 100, "Sprites/TurretNew4.png", 1);
	spritePtrs[SpriteName::INDICATOR_B] = new Sprite(354, 23, 50, 65, "Sprites/TurretP2.png", 1);
}

void SpriteManager::initBlockSpritePtrs()
{
	// Initialize all Blocks
	for (int i = 0; i < numBlocks; i++) {
		spritePtrs[SpriteName::BLOCK_1 + i] = new Sprite(150, 150, 50, 50, "Sprites/tanks_crateWood.png", 1);
	}
}

void SpriteManager::initLivesSpritePtrs()
{

	spritePtrs[SpriteName::LIFE_A_1] = new Sprite(-445, 345, 45, 45, "Sprites/LivesA.png", 3);
	spritePtrs[SpriteName::LIFE_A_2] = new Sprite(-395, 345, 45, 45, "Sprites/LivesA.png", 3);
	spritePtrs[SpriteName::LIFE_A_3] = new Sprite(-345, 345, 45, 45, "Sprites/LivesA.png", 3);
	//spritePtrs[SpriteName::LIFE_A_4] = new Sprite(100, 5, 20, 20, "Sprites/LivesA.png", 3);
//	spritePtrs[SpriteName::LIFE_A_5] = new Sprite(130, 5, 20, 20, "Sprites/LivesA.png", 3);

	spritePtrs[SpriteName::LIFE_B_1] = new Sprite(505, 345, 45, 45, "Sprites/LivesB.png", 3);
	spritePtrs[SpriteName::LIFE_B_2] = new Sprite(455, 345, 45, 45, "Sprites/LivesB.png", 3);
	spritePtrs[SpriteName::LIFE_B_3] = new Sprite(405, 345, 45, 45, "Sprites/LivesB.png", 3);
//	spritePtrs[SpriteName::LIFE_B_4] = new Sprite(1024-120, 5, 20, 20, "Sprites/LivesB.png", 3);
//	spritePtrs[SpriteName::LIFE_B_5] = new Sprite(1024-150, 5, 20, 20, "Sprites/LivesB.png", 3);
}

void SpriteManager::initGameDisplay()
{
	//spritePtrs[SpriteName::GAME_END_1] = new Sprite(-515, -200, 1024, 500, "Sprites/GameEnd.png", 4);
	//spritePtrs[SpriteName::GAME_END_2] = new Sprite(-515, -200, 1024, 500, "Sprites/GameEnd.png", 4);
	spritePtrs[SpriteName::GAME_END_1] = new Sprite(-515, -400, 1024, 800, "Sprites/Player Two Wins.png", 4);
	spritePtrs[SpriteName::GAME_END_2] = new Sprite(-515, -400, 1024, 800, "Sprites/Player One Wins.png", 4);

	//spritePtrs[SpriteName::START_SCREEN] = new Sprite(-515, -200, 1024, 500, "Sprites/GameEnd.png", 4);
	spritePtrs[SpriteName::START_SCREEN] = new Sprite(-515, -400, 1024, 800, "Sprites/TitleScreen.png", 4);

	
	//spritePtrs[SpriteName::LOADING] = new Sprite(-515, -400, 1024, 800, "Sprites/Alex.png", 4);
}

void SpriteManager::initRotations()
{
	// Rotate turrets such that they face towards center on starting the game
	//spritePtrs[SpriteName::TURRET_A]->setRotation(5.0f);
	//spritePtrs[SpriteName::TURRET_B]->setRotation(45.0f);
}

/*void SpriteManager::initColliders()
{
	// Colliders for planes
	spritePtrs[SpriteName::PLANE_A_1]->createCollider(0, 20, 100, 35, ColliderTag::PLANE_A, spritePtrs[SpriteName::PLANE_A_1]);
	spritePtrs[SpriteName::PLANE_A_2]->createCollider(0, 20, 100, 35, ColliderTag::PLANE_A, spritePtrs[SpriteName::PLANE_A_2]);
	
	spritePtrs[SpriteName::PLANE_B_1]->createCollider(0, 20, 100, 28, ColliderTag::PLANE_B, spritePtrs[SpriteName::PLANE_B_1]);
	spritePtrs[SpriteName::PLANE_B_2]->createCollider(0, 20, 100, 28, ColliderTag::PLANE_B, spritePtrs[SpriteName::PLANE_B_2]);
	// Colliders for bullets
	for (uint8_t i = SpriteName::BULLET_A_1; i <= SpriteName::BULLET_A_3; i++)
	{
		spritePtrs[i]->createCollider(0, 0, 6, 6, ColliderTag::BULLET_A, spritePtrs[i]);
	}
	
	for (uint8_t i = SpriteName::BULLET_B_1; i <= SpriteName::BULLET_B_3; i++)
	{
		spritePtrs[i]->createCollider(0, 0, 6, 6, ColliderTag::BULLET_B, spritePtrs[i]);
	}
}*/

void SpriteManager::update(DWORD milliseconds)
{
	currentFrameTime = milliseconds;
	for (uint8_t i = 0; i < NUM_SPRITES; i++)
	{
		spritePtrs[i]->updateSprite(milliseconds);
	}
}

void SpriteManager::renderSprites()
{
	//for (uint8_t i = 0; i < NUM_SPRITES; i++)
	//{
		//spritePtrs[i]->render();
		
		if (renderFlag == -1)
		{
			spritePtrs[SpriteName::BACKGROUND]->render();
			
			spritePtrs[SpriteName::BULLET_A_1]->render();
			spritePtrs[SpriteName::BULLET_A_2]->render();
			spritePtrs[SpriteName::BULLET_A_3]->render();
			spritePtrs[SpriteName::BULLET_B_1]->render();
			spritePtrs[SpriteName::BULLET_B_2]->render();
			spritePtrs[SpriteName::BULLET_B_3]->render();

			spritePtrs[SpriteName::PLANE_A_1]->render();
			spritePtrs[SpriteName::PLANE_B_1]->render();

			spritePtrs[SpriteName::INDICATOR_A]->render();
			spritePtrs[SpriteName::INDICATOR_B]->render();

			for (int i = 0; i < numBlocks; i++) {
				spritePtrs[SpriteName::BLOCK_1 + i]->render();
			}

			PlayerManagerC* player = PlayerManagerC::GetInstance();
			for (int i = 0; i < 3; i++)
			{
				if (i < player->playerHealth[0])
				{
					spritePtrs[SpriteName::LIFE_A_1 + i]->render();
				}
			}
			for (int i = 0; i < 3; i++)
			{
				if (i < player->playerHealth[1])
				{
					spritePtrs[SpriteName::LIFE_B_1 + i]->render();
				}
			}
		}
		else if (renderFlag == 0)
		{
			spritePtrs[SpriteName::GAME_END_1]->render();
		}
		else if (renderFlag == 1)
		{
			spritePtrs[SpriteName::GAME_END_2]->render();
		}
		else if (renderFlag == 2)
		{
			spritePtrs[SpriteName::START_SCREEN]->render();
		}
	//}
	//spritePtrs[SpriteName::PLANE_A_1]->getCollider()->renderCollider();
}

void SpriteManager::shutDown()
{
	for (uint8_t i = 0; i < NUM_SPRITES; i++)
	{
		delete spritePtrs[i];
	}
	free(spritePtrs);
}

Sprite** SpriteManager::getSpritePtrs()
{
	return spritePtrs;
}

int32_t SpriteManager::getNumberOfSprites()
{
	return NUM_SPRITES;
}

void  SpriteManager::resetSprites()
{
	for (uint8_t i = 0; i < NUM_SPRITES; i++)
	{
		spritePtrs[i]->setRotation(0);
		spritePtrs[i]->setVelocity(0, 0);
		spritePtrs[i]->enableSprite();
	}
	spritePtrs[SpriteName::PLANE_A_1]->setPosition(-100, 700);
	//spritePtrs[SpriteName::PLANE_A_2]->setPosition(-100, 500);
	spritePtrs[SpriteName::PLANE_B_1]->setPosition(1024, 700);
	//spritePtrs[SpriteName::PLANE_B_2]->setPosition(1024, 500);
	for (uint8_t i = SpriteName::BULLET_A_1; i <= SpriteName::BULLET_A_3; i++)
	{
		spritePtrs[i]->setPosition(124, 47);
	}
	for (uint8_t i = SpriteName::BULLET_B_1; i <= SpriteName::BULLET_B_3; i++)
	{
		spritePtrs[i]->setPosition(890,47);
	}
	initRotations();
	spritePtrs[SpriteName::GAME_END_1]->disableSprite();
}