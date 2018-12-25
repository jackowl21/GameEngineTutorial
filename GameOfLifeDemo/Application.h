#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <iostream>
#include <list>

#include "sprite.h"
#include "particleSystem.h"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define OBJ_NUM 10000

enum AppMode
{
	APP_PARTICLE_SPAWN = 0,
	APP_PARTICLE_DISPLAY_1,
	APP_PARTICLE_DISPLAY_2,
	APP_PARTICLE_DISPLAY_3
};

class Application
{
private:
	Sprite* m_dummySprite;
	Sprite* m_dummySprite2;
	Sprite* m_dummySprite3;
	Sprite* m_dummySprite4;
	Sprite* m_dummySprite5;

	GameObject* m_gameobject;
	GameObject* m_gameobject2;
	GameObject* m_gameobject3;

	ParticleSystem* m_particleSystem;
	ParticleSystem* m_particleSystem2;
	ParticleSystem* m_particleSystem3;
	ParticleSystem* m_particleSystem4;
	ParticleSystem* m_particleSystem5;

	ParticleSystem* m_particleSystem6;
	ParticleSystem* m_particleSystem7;
	ParticleSystem* m_particleSystem8;

	ParticleSystem* m_particleSystem9;
	ParticleSystem* m_particleSystem10;
	ParticleSystem* m_particleSystem11;
	ParticleSystem* m_particleSystem12;

	ParticleSystem* m_tempPS;

	ParticleAffector* m_tempPA;

	list<ParticleSystem*> m_particleSystemList;

public:

	AppMode appMode = APP_PARTICLE_SPAWN;

	bool isClicked = false; //! Is mouse button clicked.
	bool isKeyPressed = false; //! Is keyboard key clicked.
	int keyCount = 0;
	int mouseClickCount = 0;
	double mouseX, mouseY; //! X and Y mouse position on screen.

	Application();
	virtual ~Application();
	
	//!Initialization of the application.
	virtual void start();
	//!Update application with frame.
	virtual void update();
	//!Update application with deltaTime.
	virtual void update(float deltaTime);
	//!Draw application.
	virtual void draw();

	//! Receive key input from window.
	void ReceiveKey(GLFWwindow* window);
	//! Receive mouse input from window.
	void ReceiveMouseInput(GLFWwindow* window);

	void SimulateParticleSystemWithMouseInput();
	void CreateParticleSystemAt(Vector3 position);
	void SwitchMode();
	
};


#endif
