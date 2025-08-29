#pragma once

#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Vector3.hpp>

namespace tokyo
{
	class Camera
	{
	public:
		virtual ~Camera() = default;

		virtual void Start() {}
		virtual void Update(float delta) {}

		const sf::Transform& GetViewMatrix() const { return viewMatrix; }

		const sf::Transform& GetProjectionMatrix() const { return projectionMatrix; }

		const virtual sf::Vector3f& GetPosition() const { return pos; }

	protected:
		sf::Transform viewMatrix;
		sf::Transform projectionMatrix;

	private:
		const sf::Vector3f pos;
	};

}