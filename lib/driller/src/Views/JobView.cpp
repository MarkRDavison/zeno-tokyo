#include <tokyo/Driller/Views/JobView.hpp>

namespace drl
{

	JobView::JobView(
		const JobData& _jobData,
		const IJobPrototypeService& _jobPrototypeService,
		const tokyo::TextureManager& _textureManager
	) :
		m_TextureManager(_textureManager),
		m_JobData(_jobData),
		m_JobPrototypeService(_jobPrototypeService)
	{

	}

	void JobView::update(float)
	{

	}
	void JobView::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
	{
		_states.texture = &m_TextureManager.getTexture(Constants::TileSpriteSheetTextureName);
		sf::CircleShape c(0.1f, 8);
		c.setOrigin({ c.getRadius(), c.getRadius() });
		sf::CircleShape o(0.05f, 8);
		o.setFillColor(sf::Color::Blue);
		o.setOrigin({ o.getRadius(), o.getRadius() });

		for (const auto& j : m_JobData.jobs)
		{
			const sf::Vector2f tile(j.tile);
			sf::RenderStates states(_states);
			states.transform.translate(sf::Vector2f{ tile.x, -tile.y - 0.5f });
			c.setFillColor(j.allocatedWorkerId != 0
				? sf::Color::Green
				: sf::Color::Red);
			_target.draw(c, states);
			states.transform.translate({ j.offset.x, -j.offset.y });
			_target.draw(o, states);
		}
	}
}