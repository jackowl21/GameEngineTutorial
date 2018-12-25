#include "gameobject.h"
#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

GameObject::GameObject()
{

}

GameObject::GameObject(Sprite* sprite)
{
	m_sprite = sprite;
	m_rotation = 0;
	m_scale = 0.025;
	m_color = m_color.white;

	m_blendMode = BLEND_ALPHA;
	m_position = Vector3(100, 100, 100);
	//std::cout << "Created" << endl;
}

GameObject::GameObject(Sprite* sprite, Vector3 position, Vector3 velocity, float rotation, float scale, Color color, enumBlend blendMode)
{
	SetSprite(sprite);
	SetPos(position);
	SetVelocity(velocity);
	SetRotation(rotation);
	SetScale(scale);
	SetColor(color);
	SetBlendingMode(blendMode);
}

GameObject::~GameObject()
{

}

void GameObject::SetPos(Vector3 pos)
{
	m_position = pos;
}

const Vector3& GameObject::GetPos()
{
	return m_position;
}

void GameObject::SetRotation(float rotation)
{
	m_rotation = rotation;
}

float GameObject::GetRotation()
{
	return m_rotation;
}

void GameObject::SetScale(float scale)
{
	m_scale = scale;
}

float GameObject::GetScale()
{
	return m_scale;
}

void GameObject::SetSprite(Sprite* sprite)
{
	m_sprite = sprite;
}

Sprite* GameObject::GetSprite()
{
	return m_sprite;
}

void GameObject::SetColor(const Color& color)
{
	m_color = color;
}

const Color& GameObject::GetColor()
{
	return m_color;
}

void GameObject::SetBlendingMode(enumBlend blend)
{
	m_blendMode = blend;
}

enumBlend GameObject::GetBlendingMode()
{
	return m_blendMode;
}

void GameObject::SetVelocity(Vector3 velocity)
{
	m_velocity = velocity;
}

const Vector3& GameObject::GetVelocity()
{
	return m_velocity;
}

void GameObject::draw()
{
	m_sprite->draw(m_position.m_x, m_position.m_y, m_scale, m_rotation, m_color, m_blendMode);
}

void GameObject::move()
{
	m_position = m_position + m_velocity;
}

void GameObject::bounce()
{

	// Check Horizontal Border
	if (GetPos().m_x >= WINDOW_WIDTH - GetSprite()->halfWidth(GetScale()))
	{
		SetVelocity(Vector3(-GetVelocity().m_x,GetVelocity().m_y, 0.0f));
	}
	else if (GetPos().m_x <= 0 + GetSprite()->halfWidth(GetScale()))
	{
		SetVelocity(Vector3(GetVelocity().m_x * -1.0f, GetVelocity().m_y, 0.0f));
	}

	// Check Vertical Border
	if (GetPos().m_y >= WINDOW_HEIGHT - GetSprite()->halfHeight(GetScale()))
	{
		SetVelocity(Vector3(GetVelocity().m_x, -GetVelocity().m_y, 0.0f));
	}
	else if (GetPos().m_y <= 0 + GetSprite()->halfHeight(GetScale()))
	{
		SetVelocity(Vector3(GetVelocity().m_x, GetVelocity().m_y * -1.0f, 0.0f));
	}
}

void GameObject::update()
{
	draw();
}