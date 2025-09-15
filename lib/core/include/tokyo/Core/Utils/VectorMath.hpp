#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/System/Vector3.hpp>

namespace tokyo {

	template <typename T>
	T length(const sf::Vector2<T>& _vec)
	{
		return static_cast<T>(std::sqrt(_vec.x * _vec.x + _vec.y * _vec.y));
	}

	template <typename T>
	T length(const sf::Vector3<T>& _vec)
	{
		return static_cast<T>(std::sqrt(_vec.x * _vec.x + _vec.y * _vec.y + _vec.z * _vec.z));
	}

	template <typename T>
	T distance(const sf::Vector2<T>& _vec1, const sf::Vector2<T>& _vec2)
	{
		return length(_vec2 - _vec1);
	}

	template <typename T>
	T distance(const sf::Vector3<T>& _vec1, const sf::Vector3<T>& _vec2)
	{
		return length(_vec2 - _vec1);
	}


	template <typename T>
	T lengthSquared(const sf::Vector2<T>& _vec)
	{
		return _vec.x * _vec.x + _vec.y * _vec.y;
	}

	template <typename T>
	T lengthSquared(const sf::Vector3<T>& _vec)
	{
		return _vec.x * _vec.x + _vec.y * _vec.y + _vec.z * _vec.z;
	}

	template <typename T>
	sf::Vector2<T>& normalise(sf::Vector2<T>& _vec)
	{
		const T l = length(_vec);
		_vec.x /= l;
		_vec.y /= l;

		return _vec;
	}
	template <typename T>
	sf::Vector2<T> normalise(const sf::Vector2<T>& _vec)
	{
		const T l = length(_vec);

		return sf::Vector2<T>(_vec.x / l, _vec.y / l);
	}

	template <typename T>
	sf::Vector3<T>& normalise(sf::Vector3<T>& _vec)
	{
		_vec /= length(_vec);

		return _vec;
	}

	template <typename T>
	sf::Vector3<T> cross(const sf::Vector3<T>& _left, const sf::Vector3<T>& _right)
	{
		return sf::Vector3<T>(_left.y * _right.z - _left.z * _right.y,
			_left.z * _right.x - _left.x * _right.z,
			_left.x * _right.y - _left.y * _right.x);
	}

	template <typename T>
	T dot(const sf::Vector2<T>& _left, const sf::Vector2<T>& _right)
	{
		return _left.x * _right.x + _left.y * _right.y;
	}

	template <typename T>
	T dot(const sf::Vector3<T>& _left, const sf::Vector3<T>& _right)
	{
		return _left.x * _right.x + _left.y * _right.y + _left.z * _right.z;
	}

	inline float toAngle(const sf::Vector2<float>& _vec)
	{
		const float Radians = std::atan2(_vec.y, _vec.x);
		return Radians * 180.0f / static_cast<float>(3.14159265f);
	}

	inline sf::Vector2<float> toDirection(float _angle)
	{
		_angle = _angle * static_cast<float>(3.14159265f) / 180.0f;
		return sf::Vector2<float>(cosf(_angle), sinf(_angle));
	}

}       