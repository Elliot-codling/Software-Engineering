#ifndef _MATH_HELPERS_H
#define _MATH_HELPERS_H

#include <cmath>
#include <SFML\Graphics.hpp>

#define PI 3.14159265359

namespace MathHelpers
{
	inline float RadToDeg(float angle)
	{
		return angle * (float)(180.0 / PI);
	}

	inline float DegToRad(float angle)
	{
		return angle * (float)(PI / 180.0);
	}

	inline float Length(const sf::Vector2f& vector)
	{
		return sqrtf((vector.x * vector.x) + (vector.y * vector.y));
	}

	inline float LengthSquared(const sf::Vector2f& vector)
	{
		return (vector.x * vector.x) + (vector.y * vector.y);
	}
	
	inline sf::Vector2f Normalise(const sf::Vector2f& vector)
	{
		float length = Length(vector);
		return sf::Vector2f(vector.x / length, vector.y / length);

	}

	inline float Dot(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
	{
		return (vec1.x*vec2.x + vec1.y*vec2.y);
	}

	inline sf::Vector3f Cross(const sf::Vector3f& vec1, const sf::Vector3f& vec2)
	{
		sf::Vector3f retVector;

		retVector.x = vec1.y * vec2.z - vec2.y * vec1.z;
		retVector.y = vec1.z * vec2.x - vec2.z * vec1.x;
		retVector.z = vec1.x * vec2.y - vec2.x * vec1.y;

		return retVector;
	}

	inline float AngleBetweenVectors(const sf::Vector2f& vec1, const sf::Vector2f& vec2)
	{
		float angle = acos(Dot(vec1, vec2) / (Length(vec1) * Length(vec2)));
		return RadToDeg(angle);
	}

}

#endif
