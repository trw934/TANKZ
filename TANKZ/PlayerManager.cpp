#include <assert.h>
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "ShapeDraw.h"
#include "collInfo.h"
#include "object.h"
//#include "inputmapper.h"
#include "PlayerManager.h"
#include "field.h"
#include "ArenaManager.h"
#include "gamedefs.h"
#include "gameobjects.h"
#include "random.h"
#include "stateManager.h"
#include "inputmanager.h"

#include "SpriteDemoManager.h"
#include "SpriteManager.h"




PlayerManagerC* PlayerManagerC::sInstance = NULL;


PlayerManagerC* PlayerManagerC::CreateInstance()
{
	if (sInstance == nullptr)
	{
		sInstance = new PlayerManagerC();
	}
	return sInstance;
}


PlayerManagerC::PlayerManagerC()
{
	//init();
};
PlayerManagerC::~PlayerManagerC()
{
};

void PlayerManagerC::updatePlayerManager(DWORD milliseconds)
{
	//Update movement timers for both Players
	mCurrentTime[0] += milliseconds;
	mCurrentTime[1] += milliseconds;
}

bool PlayerManagerC::CollideArena(int playerX, int playerY)
{
	/*FieldC* field = FieldManagerC::GetInstance()->getFieldPtr();

	float_t rightSide = field->getPosition()->x + ((float_t)field->getWidth());
	float_t leftSide = field->getPosition()->x - ((float_t)field->getWidth());
	float_t topSide = field->getPosition()->y + ((float_t)field->getHeight());
	float_t bottomSide = field->getPosition()->y - ((float_t)field->getHeight());

	if (playerPosX[0] - mRadius <= leftSide)
	{
		return false;
	}
	if (playerPosX[0] + 6 * (mRadius) >= rightSide)
	{
		return false;
	}
	if (playerPosY[0] - mRadius <= bottomSide)
	{
		return false;
	}
	if (playerPosY[0] + 6*(mRadius) >= topSide)
	{
		return false;
	}

	return true;*/
	int playerLeft = playerX;
	int playerRight = playerX + mRadius;
	int playerTop = playerY;
	int playerBottom = playerY - mRadius;

	ArenaManager* arena = ArenaManager::GetInstance();
	Block* blocks = arena->getBlocks();

	for (int i = 0; i < 13; i++)
	{
		Block block = blocks[i];
		if (playerLeft < block.rightX && playerRight > block.leftX && playerTop > block.bottomY && playerBottom < block.topY)
		{
			return false;
		}
	}
	return true;
};

bool PlayerManagerC::CollidePlayer(int playerX, int playerY, int playerNum)
{
	int otherPlayer = 0;
	if (playerNum == 0)
	{
		otherPlayer = 1;
	}

	int playerLeft = playerX;
	int playerRight = playerX + mRadius;
	int playerTop = playerY;
	int playerBottom = playerY - mRadius;
	int otherLeft = playerPosX[otherPlayer];
	int otherRight = otherLeft + mRadius;
	int otherTop = playerPosY[otherPlayer];
	int otherBottom = otherTop - mRadius;

	if (playerLeft < otherRight && playerRight > otherLeft && playerTop > otherBottom && playerBottom < otherTop) 
	{
		return false;
	}
	else
	{
		return true;
	}
};

void PlayerManagerC::moveUp(int player)
{
	if (CollideArena(playerPosX[player], playerPosY[player] + speed) && CollidePlayer(playerPosX[player], playerPosY[player] + speed,player))
	{
		playerPosY[player] += speed;
		SpriteManager::getInstance()->getSpritePtrs()[player]->setPosition(playerPosX[player], playerPosY[player]);
		SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(0, speed);
	}
};

void PlayerManagerC::moveDown(int player)
{
	if (CollideArena(playerPosX[player], playerPosY[player] - speed) && CollidePlayer(playerPosX[player], playerPosY[player] - speed, player))
	{
		playerPosY[player] -= speed;
		SpriteManager::getInstance()->getSpritePtrs()[player]->setPosition(playerPosX[player], playerPosY[player]);
		SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(0, -speed);
	}
};

void PlayerManagerC::moveLeft(int player)
{
	if (CollideArena(playerPosX[player] - speed, playerPosY[player]) && CollidePlayer(playerPosX[player] - speed, playerPosY[player], player))
	{
		playerPosX[player] -= speed;
		SpriteManager::getInstance()->getSpritePtrs()[player]->setPosition(playerPosX[player], playerPosY[player]);
		SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(-speed, 0);
	}
};

void PlayerManagerC::moveRight(int player)
{
	if (CollideArena(playerPosX[player] + speed, playerPosY[player]) && CollidePlayer(playerPosX[player] + speed, playerPosY[player], player))
	{
		playerPosX[player] += speed;
		SpriteManager::getInstance()->getSpritePtrs()[player]->setPosition(playerPosX[player], playerPosY[player]);
		SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(speed, 0);
	}
};


void PlayerManagerC::rotateCannonLeft(int player)
{
	if (mCurrentTime[player] - mLastUpdateTime[player] > 200)
	{
		
		
		switch (cannonRotation[player])
		{
			case CANNON_RIGHT:
				//set rotation
				cannonRotation[player] += 45;
				SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setRotation(cannonRotation[player]);

				//update position
				SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(-12, -25);

				//
				break;
			case CANNON_UP_RIGHT:
				//set rotation
				cannonRotation[player] += 45;
				SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setRotation(cannonRotation[player]);
				//update position
				SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(10, -25);
				break;
			case CANNON_UP:
				//set rotation
				cannonRotation[player] += 45;
				SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setRotation(cannonRotation[player]);
				//update position
				SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(23, -10);
				break;
			case CANNON_UP_LEFT:
				//set rotation
				cannonRotation[player] += 45;
				SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setRotation(cannonRotation[player]);
				//update position
				SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(23, 12);
				break;
			case CANNON_LEFT:
				//set rotation
				cannonRotation[player] += 45;
				SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setRotation(cannonRotation[player]);
				//update position
				SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(10, 25);
				break;
			case CANNON_DOWN_LEFT:
				//set rotation
				cannonRotation[player] += 45;
				SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setRotation(cannonRotation[player]);
				//update position
				SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(-10, 25);
				break;
			case CANNON_DOWN:
				//set rotation
				cannonRotation[player] += 45;
				SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setRotation(cannonRotation[player]);
				//update position
				SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(-25, 10);
				break;
			case CANNON_DOWN_RIGHT:
				cannonRotation[player] = -90;
				SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setRotation(cannonRotation[player]);
				SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setPosition(playerPosX[player] + 4, playerPosY[player] + 48);
				break;
		}

		mLastUpdateTime[player] = mCurrentTime[player];
	}
};

void PlayerManagerC::rotateCannonRight(int player)
{
	if (mCurrentTime[player] - mLastUpdateTime[player] > 200)
	{


		switch (cannonRotation[player])
		{
		case CANNON_RIGHT:
			//set rotation
			cannonRotation[player] = 225;
			SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setRotation(cannonRotation[player]);
			
			//update position
			SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(20, 12);
			break;
		case CANNON_UP_RIGHT:
			//set rotation
			cannonRotation[player] -= 45;
			SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setRotation(cannonRotation[player]);
			//update position
			SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setPosition(playerPosX[player] + 4, playerPosY[player] + 48);
			break;
		case CANNON_UP:
			//set rotation
			cannonRotation[player] -= 45;
			SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setRotation(cannonRotation[player]);
			//update position
			SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(-10, 25);
			break;
		case CANNON_UP_LEFT:
			//set rotation
			cannonRotation[player] -= 45;
			SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setRotation(cannonRotation[player]);
			//update position
			SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(-23, 10);
			break;
		case CANNON_LEFT:
			//set rotation
			cannonRotation[player] -= 45;
			SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setRotation(cannonRotation[player]);
			//update position
			SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(-23, -12);
			break;
		case CANNON_DOWN_LEFT:
			//set rotation
			cannonRotation[player] -= 45;
			SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setRotation(cannonRotation[player]);
			//update position
			SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(-10, -25);
			break;
		case CANNON_DOWN:
			//set rotation
			cannonRotation[player] -= 45;
			SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setRotation(cannonRotation[player]);
			//update position
			SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(10, -25);
			break;
		case CANNON_DOWN_RIGHT:
			cannonRotation[player] -= 45;
			SpriteManager::getInstance()->getSpritePtrs()[8 + player]->setRotation(cannonRotation[player]);
			//update position
			SpriteManager::getInstance()->getSpritePtrs()[8 + player]->incrementPosition(25, -10);
			break;
		}

		mLastUpdateTime[player] = mCurrentTime[player];
	}
};



float PlayerManagerC::getPlayerXPos(int player)
{
	return playerPosX[player];
}

float PlayerManagerC::getPlayerYPos(int player)
{
	return playerPosY[player];
}

int PlayerManagerC::getCannonRotation(int player)
{
	return cannonRotation[player];
}

void PlayerManagerC::renderAimIndicators()
{
	
}

void PlayerManagerC::init()
{
	//Set Player 1 position
	playerPosX[0] = -400;
	playerPosY[0] = -25;
	SpriteManager::getInstance()->getSpritePtrs()[0]->setPosition(playerPosX[0], playerPosY[0]);
	
	cannonRotation[0] = -90;
	SpriteManager::getInstance()->getSpritePtrs()[8]->setRotation(cannonRotation[0]);
	SpriteManager::getInstance()->getSpritePtrs()[8]->setPosition(playerPosX[0] + 4, playerPosY[0] + 48);




	//Set Player 2 position
	playerPosX[1] = 350;
	playerPosY[1] = -25;
	SpriteManager::getInstance()->getSpritePtrs()[1]->setPosition(playerPosX[1], playerPosY[1]);


	cannonRotation[1] = -90;
	SpriteManager::getInstance()->getSpritePtrs()[9]->setRotation(cannonRotation[1]);
	SpriteManager::getInstance()->getSpritePtrs()[9]->setPosition(playerPosX[1] + 4, playerPosY[1] + 48);

	mRadius = 50.0;


	playerHealth[0] = 3;
	playerHealth[1] = 3;

	mEnabled = true;

}