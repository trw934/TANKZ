#define GAME_CPP
#include <windows.h>											// Header File For Windows
#include <stdio.h>												// Header File For Standard Input / Output
#include <stdarg.h>												// Header File For Variable Argument Routines
#include <math.h>												// Header File For Math Operations
#include <gl\gl.h>												// Header File For The OpenGL32 Library
#include <gl\glu.h>												// Header File For The GLu32 Library
#include "glut.h"
#include "baseTypes.h"
#include "openglframework.h"	
#include "gamedefs.h"
#include "collInfo.h"
#include "object.h"
#include "ball.h"
#include "field.h"
#include "random.h"
#include "gameObjects.h"
#include "openGLStuff.h"
#include "game.h"
#include "StateManager.h"
#include "BallManager.h"
#include "PlayerManager.h"
#include "FieldManager.h"
#include "InputManager.h"
#include "SpriteDemoManager.h"
#include "SpriteManager.h"
#include "BulletManager.h"
#include "ArenaManager.h"
#include "AudioManager.h"

// Declarations
const char8_t CGame::mGameTitle[] = "Framework1";
CGame* CGame::sInstance = NULL;
BOOL Initialize(GL_Window* window, Keys* keys)					// Any OpenGL Initialization Goes Here
{
	initOpenGLDrawing(window, keys, 0.0f, 0.0f, 0.0f);
	CGame::CreateInstance();
	CGame::GetInstance()->init();
	return TRUE;
}

void CGame::init()
{
	if (!spritesLoaded)
	{
		SpriteManager::createInstance();
		SpriteManager::getInstance()->init();
		spritesLoaded = true;
	}

	//PlaySound(TEXT("Sounds/Mercury.wav"), NULL, SND_ASYNC | SND_LOOP);
	
	FieldManagerC::CreateInstance();
	FieldManagerC::GetInstance()->init();


	AudioManager::createInstance();
	AudioManager::getInstance()->init();
	AudioManager::getInstance()->playBackground();

	
	PlayerManagerC::CreateInstance();
	BulletManager::CreateInstance();
	ArenaManager::CreateInstance();

	PlayerManagerC::GetInstance()->init();
	BulletManager::GetInstance()->init();
	ArenaManager::GetInstance()->init();

	//BallManagerC::CreateInstance();
	//StateManagerC::CreateInstance();
	//InputManagerC::CreateInstance();
	//InputManagerC::GetInstance()->init();

	//BallManagerC::GetInstance()->init();
	//StateManagerC::GetInstance()->setState(StateManagerC::HALF_BALLS_FILLED);
	//SpriteDemoManagerC::GetInstance()->init(5, 5);
	//SpriteDemoManagerC::CreateInstance();
}
void CGame::UpdateFrame(DWORD milliseconds)
{
	keyProcess();
	BulletManager::GetInstance()->updateBullets(milliseconds);
	PlayerManagerC::GetInstance()->updatePlayerManager(milliseconds);

	timerForRestart -= milliseconds;
}

void CGame::DrawScene(void)
{
	startOpenGLDrawing();
	//SpriteDemoManagerC::GetInstance()->renderSprites();
	SpriteManager::getInstance()->renderSprites();
	//BallManagerC::GetInstance()->renderBalls();
	FieldManagerC::GetInstance()->renderField();
	PlayerManagerC::GetInstance()->renderAimIndicators();


}


CGame* CGame::CreateInstance()
{
	sInstance = new CGame();
	return sInstance;
}
void CGame::shutdown()
{
	//BallManagerC::GetInstance()->shutdown();
	//StateManagerC::GetInstance()->shutdown();
	FieldManagerC::GetInstance()->shutdown();
	AudioManager::getInstance()->shutdown();
	//SpriteManager::getInstance()->shutDown();

}
void CGame::DestroyGame(void)
{
	//delete BallManagerC::GetInstance();
	//delete StateManagerC::GetInstance();
	delete FieldManagerC::GetInstance();
	delete PlayerManagerC::GetInstance();
	delete SpriteManager::getInstance();
	delete BulletManager::GetInstance();
	delete ArenaManager::GetInstance();
	delete AudioManager::getInstance();
}

void CGame::RestartGame()
{
	if (timerForRestart > 0)return;

	shutdown();
	//DestroyGame();
	init();
	gameStart = false;
	timerForRestart = 3000;
	SpriteManager::getInstance()->renderFlag = 2;
}

void CGame::gameOver(int player)
{
	SpriteManager::getInstance()->renderFlag = player;
}

void CGame::startGame()
{
	SpriteManager::getInstance()->renderFlag = -1;
	gameStart = true;
}