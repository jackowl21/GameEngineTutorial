#pragma once
#include <iostream>
#include <cmath>

using namespace std;

class Vector3
{
	public:

		float m_x = 0;
		float m_y = 0;
		float m_z = 0;

		Vector3();
		Vector3(float x, float y, float z);

		Vector3 operator+ (const Vector3& vec);
		Vector3 operator- (const Vector3& vec);

		Vector3 operator* (const float value);
		Vector3 operator/ (const float value);
		Vector3 crossVector(const Vector3& vec);

		float getLength();
		float dot(const Vector3& vec);
	
		void Normalize();
		void Display();
};