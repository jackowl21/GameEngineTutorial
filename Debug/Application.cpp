#include "Application.h"

float rotator = 0;

Application::Application()
{
	m_dummySprite = new Sprite("../media/star.png");
	m_dummySprite2 = new Sprite("../media/smoke.png");
	m_dummySprite3 = new Sprite("../media/SimpleRadial.png");
	m_dummySprite4 = new Sprite("../media/rocket.png");
	m_dummySprite5 = new Sprite("../media/loadingball.png");;
	
	m_particleSystem = new ParticleSystem(m_dummySprite, Vector3(300, 300, 0), 3, 0.01f, 0.05f, 5.0f, 0.005f, 1.0f);
	m_particleSystem2 = new ParticleSystem(m_dummySprite2, Vector3(300, 300, 0), 5, 0.01f, 0.025f, 1.0f, 1.0f, 2.0f);
	m_particleSystem3 = new ParticleSystem(m_dummySprite3, Vector3(400, 300, 0), 1, 0.01f, 0.025f, 1.0f, 0.005f, 1.0f);
	m_particleSystem4 = new ParticleSystem(m_dummySprite3, Vector3(100, 100, 0), 2, 0.01f, 0.025f, 1.2f, 0.005f, 1.0f);
	m_particleSystem5 = new ParticleSystem(m_dummySprite3, Vector3(540, 100, 0), 2, 0.01f, 0.025f, 1.2f, 0.005f, 1.0f);

	m_gameobject = new GameObject(m_dummySprite4, Vector3(100, 100, 0), Vector3(0, 2, 0), 0, 0.1, Color::white, BLEND_ONE);
	m_gameobject2 = new GameObject(m_dummySprite4, Vector3(540, 100, 0), Vector3(0, 2, 0), 0, 0.1, Color::white, BLEND_ONE);
	
	m_particleSystem6 = new ParticleSystem(m_dummySprite, Vector3(320, 240, 0), 1, 0.001, 0.1f, 60.0f, 0.5f, 1.0f);
	m_particleSystem7 = new ParticleSystem(m_dummySprite2, Vector3(140, 240, 0), 10, 0.001, 0.1, 10.0f, 0.1f, 0.05f);
	m_particleSystem8 = new ParticleSystem(m_dummySprite2, Vector3(500, 240, 0), 10, 0.001, 0.1, 10.0f, 0.1f, 0.05f);

	m_gameobject3 = new GameObject(m_dummySprite5, Vector3(320, 240, 0), Vector3(0,0,0), 0, 0.2, Color::white, BLEND_MULTIPLY);

	m_particleSystem9 = new ParticleSystem(m_dummySprite3, Vector3(320, 240, 0), 10, 0.015, 0.025, 10.0f, 0.05f, 1.0f);
	m_particleSystem10 = new ParticleSystem(m_dummySprite3, Vector3(140, 140, 0), 5, 0.015, 0.025, 3.0f, 0.05f, 1.0f);
	m_particleSystem11 = new ParticleSystem(m_dummySprite3, Vector3(500, 360, 0), 5, 0.015, 0.025, 8.0f, 0.05f, 1.0f);
	m_particleSystem12 = new ParticleSystem(m_dummySprite3, Vector3(140, 360, 0), 5, 0.015, 0.025, 8.0f, 0.05f, 1.0f);
}

Application::~Application()
{

}

void Application::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void Application::SimulateParticleSystemWithMouseInput()
{
	if (isClicked)
	{
		
		if (appMode == APP_PARTICLE_SPAWN)
		{
			m_tempPS = new ParticleSystem(m_dummySprite2, Vector3(mouseX, mouseY, 0), 5, 0.01, 0.025, 0.5f, 0.00005f, 0.095f);
			m_tempPS->addEmitter(new CircleEmitter(50, -10, 10, -10, 10, 0, 0, 0, 0));
			m_tempPS->m_emissionMode = E_BURST;
			m_tempPS->addAffector(new ScaleAffector(S_INTERPOLATE, 0.01f, 1.0f));
			m_tempPS->addAffector(new ColorAffector(Color::red, Color::yellow));
			m_tempPS->addAffector(new RotationAffector(-1.0f, 1.0));
			m_tempPS->addAffector(new VelocityAffector(2.0f, -2.0f, 2.0f, -2.0f));
			m_particleSystemList.push_back(m_tempPS);

			m_tempPS = new ParticleSystem(m_dummySprite3, Vector3(mouseX, mouseY, 0), 10, 0.01, 0.025, 0.5f, 0.00005f, 0.095f);
			m_tempPS->addEmitter(new PointEmitter(-5, 5, -5, 5, 0, 0, 0, 0));
			m_tempPS->m_emissionMode = E_BURST;
			m_tempPS->addAffector(new ScaleAffector(S_INTERPOLATE, 0.05f, 0.001f));
			m_tempPS->addAffector(new ColorAffector(Color::yellow, Color::black));
			m_tempPS->addAffector(new GravityAffector(0.01f, -1));
			m_particleSystemList.push_back(m_tempPS);

			m_tempPS = nullptr;
		}
		
		if (appMode == APP_PARTICLE_DISPLAY_3)
		{
			m_particleSystem9->clearAllAffector();
			m_particleSystem9->addAffector(new ColorAffector(Color::red, Color::blue));
			m_tempPA = new GravityAffector(0.1f, Vector3(mouseX, mouseY, 0), G_TYPE_2);
			m_particleSystem9->addAffector(m_tempPA);
		}
		
		isClicked = false;
	}
}

void Application::CreateParticleSystemAt(Vector3 position)
{
	m_tempPS = new ParticleSystem(m_dummySprite3, position, 80, 0.01, 0.025, 3.0f, 0.005f, 0.095f);
	m_tempPS->addEmitter(new PointEmitter(-15.0f, 15.0f, -15.0f, 15.0f, 0, 0, 0, 0));
	m_tempPS->m_emissionMode = E_BURST;
	m_tempPS->addAffector(new ScaleAffector(S_INTERPOLATE, 0.02f, 0.0001f));
	m_tempPS->addAffector(new ColorAffector(Color::yellow, Color(1.0f, 0.3f, 0.0f, 0.0f)));
	m_tempPS->addAffector(new VelocityAffector(100, -100, 100, -100));
	m_particleSystemList.push_back(m_tempPS);

	m_tempPS = new ParticleSystem(m_dummySprite3, position, 200, 0.01, 0.025, 2.0f, 0.005f, 5.0f);
	m_tempPS->addEmitter(new CircleEmitter(100.0f, -3.0f, 3.0f, -3.0f, 3.0f, 0, 0, 0, 0));
	m_tempPS->m_emissionMode = E_BURST;
	m_tempPS->addAffector(new ScaleAffector(S_INTERPOLATE, 0.05f, 0.001f));
	m_tempPS->addAffector(new ColorAffector(2.0f, 1.0f, 1.0f));
	m_tempPS->addAffector(new GravityAffector(0.05f, -1));
	m_particleSystemList.push_back(m_tempPS);
}

void Application::SwitchMode()
{
	if (isKeyPressed)
	{
		if (appMode == APP_PARTICLE_SPAWN)
		{
			appMode = APP_PARTICLE_DISPLAY_1;
		}	
		else if (appMode == APP_PARTICLE_DISPLAY_1)
		{
			appMode = APP_PARTICLE_DISPLAY_2;
		}
		else if (appMode == APP_PARTICLE_DISPLAY_2)
		{
			appMode = APP_PARTICLE_DISPLAY_3;
		}
		else if (appMode == APP_PARTICLE_DISPLAY_3)
		{
			appMode = APP_PARTICLE_SPAWN;
		}
		
		m_particleSystemList.clear();
		isKeyPressed = false;
	}
	
}

void Application::ReceiveKey(GLFWwindow * window)
{
	if (glfwGetKey(window, 'X')) keyCount++;
	if (glfwGetKey(window, 'X') == GLFW_RELEASE) keyCount = 0;

	if (keyCount == 1)
		isKeyPressed = true;
}

void Application::ReceiveMouseInput(GLFWwindow * window)
{
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		mouseClickCount++;
		glfwGetCursorPos(window, &mouseX, &mouseY);
		mouseY = WINDOW_HEIGHT - mouseY;
	}

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
	{
		mouseClickCount = 0;
	}

	if (mouseClickCount == 1)
	{	
		isClicked = true;
	}
}


void Application::start()
{
	//Display 1 Setup
	m_particleSystem->addEmitter(new RingEmitter(50));
	m_particleSystem->addAffector(new ColorAffector(Color(0.0, 0.5, 1.0, 1.0), Color(1.0, 0.2, 0.0, 1.0)));
	m_particleSystem->addAffector(new ScaleAffector(S_INTERPOLATE, 0.05f, 0.001f));
	m_particleSystem->addAffector(new RotationAffector(10.0f));
	m_particleSystem->addAffector(new GravityAffector(0.0005f, Vector3(300, 240, 0), G_TYPE_1));
	m_particleSystem->m_emissionMode = E_OVERTIME;

	m_particleSystem2->addEmitter(new PointEmitter(-0.1, 0.1, -0.1, 0.1, 0, 0, 0, 0));
	m_particleSystem2->addAffector(new ColorAffector(Color::green, Color::black));
	m_particleSystem2->addAffector(new ScaleAffector(S_INTERPOLATE, 0.5f, 0.001f));
	m_particleSystem2->addAffector(new RotationAffector(-10.0f));
	m_particleSystem2->m_emissionMode = E_OVERTIME;

	m_particleSystem3->addEmitter(new PointEmitter(0, 0, 0, 0, 0, 0, 0, 0));
	m_particleSystem3->addAffector(new ColorAffector(Color::red, Color::yellow));
	m_particleSystem3->addAffector(new ScaleAffector(S_INTERPOLATE, 0.025f, 0.05f));
	m_particleSystem3->addAffector(new VelocityAffector(-10, 10, -10, 10));
	m_particleSystem3->m_emissionMode = E_OVERTIME;

	m_particleSystem4->addEmitter(new PointEmitter(-0.1, 0.1, -0.1, 0, 0, 0, 0, 0));
	m_particleSystem4->addAffector(new ColorAffector(Color::blue, Color::white));
	m_particleSystem4->addAffector(new ScaleAffector(S_INTERPOLATE, 0.02f, 0.001f));
	m_particleSystem4->m_emissionMode = E_OVERTIME;

	m_particleSystem5->addEmitter(new PointEmitter(-0.1, 0.1, -0.1, 0, 0, 0, 0, 0));
	m_particleSystem5->addAffector(new ColorAffector(Color::green, Color::yellow));
	m_particleSystem5->addAffector(new ScaleAffector(S_INTERPOLATE, 0.02f, 0.001f));
	m_particleSystem5->m_emissionMode = E_OVERTIME;

	//Display 2 Setup
	m_particleSystem6->addEmitter(new PointEmitter(-5, 5, -5, 5, 0, 0, 0, 0));
	m_particleSystem6->addAffector(new ColorAffector(0.5f, 0.5f, 1.0f));
	m_particleSystem6->addAffector(new VelocityAffector(0.8f, 5, -5));
	m_particleSystem6->addAffector(new ScaleAffector(S_PULSATE, 0.08f, 0.1f));
	m_particleSystem6->addAffector(new RotationAffector(-10.0f, 10.0f));

	m_particleSystem7->addEmitter(new SquareEmitter(200, 200, -1, 1, -1, 1, 0, 0, 0, 0));
	m_particleSystem7->addAffector(new ColorAffector(Color::red, Color(0.0f, 0.8f, 1.0f, 1.0f)));
	m_particleSystem7->addAffector(new VelocityAffector(Vector3(1, 0, 0), Vector3(10, 10, 0)));
	m_particleSystem7->addAffector(new GravityAffector(0.015f, Vector3(m_particleSystem7->GetPosition()), G_TYPE_1));
	m_particleSystem7->addAffector(new ScaleAffector(S_INTERPOLATE, 0.08f, 0.005f));
	
	m_particleSystem8->addEmitter(new SquareEmitter(200, 200, -1, 1, -1, 1, 0, 0, 0, 0));
	m_particleSystem8->addAffector(new ColorAffector(Color(1.0f, 0.5f, 0.0f, 1.0f), Color(0.0f, 0.8f, 1.0f, 1.0f)));
	m_particleSystem8->addAffector(new VelocityAffector(Vector3(-1, 0, 0), Vector3(-10, -10, 0)));
	m_particleSystem8->addAffector(new GravityAffector(0.015f, Vector3(m_particleSystem8->GetPosition()), G_TYPE_1));
	m_particleSystem8->addAffector(new ScaleAffector(S_INTERPOLATE, 0.08f, 0.001f));

	//Display 3 setup
	m_particleSystem9->addEmitter(new SquareEmitter(100, 100, 0, 0, 0, 0, 0, 0, 0, 0));
	m_particleSystem9->addAffector(new ColorAffector(Color::red, Color::blue));
	m_particleSystem9->addAffector(new ScaleAffector(S_INTERPOLATE, 0.01f, 0.001f));

	m_particleSystem10->addEmitter(new RingEmitter(60, 0, 0, 0, 0, 0, 0, 0, 0));
	m_particleSystem10->addAffector(new ColorAffector(Color(0.0f, 0.8f, 1.0f, 1.0f), Color::black));
	m_particleSystem10->addAffector(new ScaleAffector(S_INTERPOLATE, 0.01f, 0.0001f));
	m_particleSystem10->addAffector(new GravityAffector(0.005f, Vector3(m_particleSystem10->GetPosition()),G_TYPE_2));

	m_particleSystem12->addEmitter(new RingEmitter(60, 0, 0, 0, 0, 0, 0, 0, 0));
	m_particleSystem12->addAffector(new ColorAffector(Color(0.0f, 1.0f, 0.5f, 1.0f), Color::black));
	m_particleSystem12->addAffector(new ScaleAffector(S_INTERPOLATE, 0.01f, 0.0001f));
	m_particleSystem12->addAffector(new GravityAffector(0.005f, Vector3(m_particleSystem12->GetPosition()), G_TYPE_1));

	m_particleSystem11->addEmitter(new RingEmitter(60, -1, 1, -1, 1, 0, 0, 0, 0));
	m_particleSystem11->addAffector(new ColorAffector(Color(1.0f, 0.8f, 0.0f, 1.0f), Color::red));
	m_particleSystem11->addAffector(new ScaleAffector(S_PULSATE, 0.01f, 0.001f));
	m_particleSystem11->addAffector(new GravityAffector(0.005f, Vector3(m_particleSystem11->GetPosition() + Vector3(0, -100, 0)), G_TYPE_1));
}

void Application::update()
{
	
}

void Application::update(float deltaTime)
{
	SwitchMode();

	if (appMode == APP_PARTICLE_SPAWN)
	{
		SimulateParticleSystemWithMouseInput();

		for (list<ParticleSystem*>::iterator i = m_particleSystemList.begin(); i != m_particleSystemList.end(); i++)
		{
			(*i)->update(deltaTime);
		}
	}
	else if (appMode == APP_PARTICLE_DISPLAY_1)
	{
		if (m_particleSystem4->GetPosition().m_y >= 350)
		{
			CreateParticleSystemAt(m_particleSystem4->GetPosition());
			m_particleSystem4->SetPosition(Vector3(m_particleSystem4->GetPosition().m_x, 100, 0));
			m_gameobject->SetPos(Vector3(m_gameobject->GetPos().m_x, 105, 0));
		}
		else
		{
			m_gameobject->move();
			m_particleSystem4->move(Vector3(0, 2.0f, 0));
		}

		if (m_particleSystem5->GetPosition().m_y >= 350)
		{
			CreateParticleSystemAt(m_particleSystem5->GetPosition());
			m_particleSystem5->SetPosition(Vector3(m_particleSystem5->GetPosition().m_x, 100, 0));
			m_gameobject2->SetPos(Vector3(m_gameobject2->GetPos().m_x, 105, 0));
		}
		else
		{
			m_gameobject2->move();
			m_particleSystem5->move(Vector3(0, 2.0f, 0));
		}

		rotator += 2.0f * deltaTime;

		m_particleSystem->rotateAround(Vector3(300, 240, 0), 100, rotator);
		m_particleSystem2->rotateAround(Vector3(300, 240, 0), 100, rotator);
		m_particleSystem3->rotateAround(Vector3(300, 240, 0), 100, rotator);

		m_particleSystem->update(deltaTime);
		m_particleSystem2->update(deltaTime);
		m_particleSystem3->update(deltaTime);
		m_particleSystem4->update(deltaTime);
		m_particleSystem5->update(deltaTime);

		m_gameobject->update();
		m_gameobject2->update();

		for (list<ParticleSystem*>::iterator i = m_particleSystemList.begin(); i != m_particleSystemList.end(); i++)
		{
			(*i)->update(deltaTime);
		}
	}
	else if(appMode == APP_PARTICLE_DISPLAY_2)
	{
		rotator += deltaTime;
		
		m_particleSystem7->rotateAround(Vector3(320, 240, 0), 180, rotator);
		m_particleSystem8->rotateAround(Vector3(320, 240, 0), -180, rotator);
		m_gameobject3->SetRotation(m_gameobject3->GetRotation() + rotator);
		
		m_particleSystem6->update(deltaTime);
		m_particleSystem7->update(deltaTime);
		m_particleSystem8->update(deltaTime);
		m_gameobject3->update();
	}
	else if (appMode == APP_PARTICLE_DISPLAY_3)
	{
		SimulateParticleSystemWithMouseInput();

		m_particleSystem9->update(deltaTime);
		m_particleSystem10->update(deltaTime);
		m_particleSystem11->update(deltaTime);
		m_particleSystem12->update(deltaTime);
	}
	
}
