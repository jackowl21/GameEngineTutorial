#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "sprite.h"
#include "Vector3.h"


class GameObject
{
private:
	Vector3 m_position; // Position of the gameobject
	float m_rotation; // Rotation of the gameobject
	float m_scale; // Scale of the gameobject
	
	Vector3 m_velocity; // Velocity of the gameobject
	
public:
	Sprite* m_sprite;
	Color m_color;
	enumBlend m_blendMode;

	GameObject();
	//! Constructor of Gameobject with sprite setting only.
	GameObject(Sprite* sprite);
	//! Constructor of Gameobject with sprite, position, velocity, rotataion, scale, color and blend mode settings on.
	GameObject(Sprite* sprite, Vector3 position, Vector3 velocity, float rotation, float scale, Color color, enumBlend blendMode);
	virtual ~GameObject();

	void SetPos(Vector3 pos);
	const Vector3& GetPos();
	
	void SetRotation(float rotate);
	float GetRotation();
	
	void SetScale(float scale);
	float GetScale();

	void SetVelocity(Vector3 velocity);
	const Vector3& GetVelocity();
	
	void SetSprite(Sprite* sprite);
	Sprite* GetSprite();

	void SetColor(const Color& color);
	const Color& GetColor();

	void SetBlendingMode(enumBlend blend);
	enumBlend GetBlendingMode();

	void draw(); // Draw gameobject.
	void move(); // Move gameobject.
	void bounce();
	virtual void update();
};

#endif // ! GAMEOBJECT_H