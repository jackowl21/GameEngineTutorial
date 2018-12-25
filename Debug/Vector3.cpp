#include <iostream>
#include "Vector3.h"
#include "Windows.h"
#include "math.h"

Vector3::Vector3()
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
}

Vector3::Vector3(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

Vector3 Vector3::operator+ (const Vector3& vec)
{
	return Vector3(m_x + vec.m_x, m_y + vec.m_y, m_z + vec.m_z);
}

Vector3 Vector3::operator- (const Vector3& vec)
{
	return Vector3(m_x - vec.m_x, m_y - vec.m_y, m_z - vec.m_z);
}

Vector3 Vector3::operator* (const float value)
{
	return Vector3(m_x * value, m_y * value, m_z * value);
}

Vector3 Vector3::operator/ (const float value)
{
	return Vector3(m_x / value, m_y / value, m_z / value);
}

float Vector3::getLength()
{
	float tempValue = m_x * m_x + m_y * m_y + m_z * m_z;

	if (tempValue > 0.0f)
	{
		return sqrt(tempValue);
	}
	else
	{
		return NULL;
	}

}

Vector3 Vector3::crossVector(const Vector3& vec)
{
	return Vector3(m_y * vec.m_z - m_z * vec.m_y, m_z * vec.m_x - m_x * vec.m_z, m_x * vec.m_y - m_y * vec.m_x);
}

float Vector3::dot(const Vector3& vec)
{
	return m_x * vec.m_x + m_y * vec.m_y + m_z * vec.m_z;
}


void Vector3::Normalize()
{
	float magnitude = getLength();
	if (magnitude > 0)
	{
		m_x /= magnitude;
		m_y /= magnitude;
		m_z /= magnitude;
	}
}

void Vector3::Display()
{
	cout << "X: " << m_x << endl;
	cout << "Y: " << m_y << endl;
	cout << "Z: " << m_z << endl;
	cout << endl;
}