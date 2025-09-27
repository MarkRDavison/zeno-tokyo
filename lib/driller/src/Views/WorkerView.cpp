#include <tokyo/Driller/Views/WorkerView.hpp>

namespace drl
{

	WorkerView::WorkerView(
		const WorkerData& _workerData,
		const IWorkerPrototypeService& _workerPrototypeService,
		const tokyo::TextureManager& _textureManager
	) :
		m_WorkerData(_workerData),
		m_WorkerPrototypeService(_workerPrototypeService),
		m_TextureManager(_textureManager)
	{

	}

	void WorkerView::update(float _delta)
	{

	}
	void WorkerView::draw(sf::RenderTarget& _target, sf::RenderStates _states) const
	{
		const sf::Vector2f size{ 0.4f, 0.8f };
		sf::VertexArray workers(sf::PrimitiveType::Triangles);

		if (m_WorkerData.workers.size() > 0)
		{
			for (const auto& w : m_WorkerData.workers)
			{
				const auto& prototype = m_WorkerPrototypeService.getPrototype(w.prototypeId);

				workers.append(sf::Vertex(sf::Vector2f{ w.position.x, -w.position.y } + sf::Vector2f(-size.x / 2.0f, 0.0f), sf::Color::Green));
				workers.append(sf::Vertex(sf::Vector2f{ w.position.x, -w.position.y } + sf::Vector2f(+size.x / 2.0f, 0.0f), sf::Color::Green));
				workers.append(sf::Vertex(sf::Vector2f{ w.position.x, -w.position.y } + sf::Vector2f(+size.x / 2.0f, size.y), sf::Color::Red));
										  
				workers.append(sf::Vertex(sf::Vector2f{ w.position.x, -w.position.y } + sf::Vector2f(-size.x / 2.0f, 0.0f), sf::Color::Green));
				workers.append(sf::Vertex(sf::Vector2f{ w.position.x, -w.position.y } + sf::Vector2f(+size.x / 2.0f, size.y), sf::Color::Red));
				workers.append(sf::Vertex(sf::Vector2f{ w.position.x, -w.position.y } + sf::Vector2f(-size.x / 2.0f, size.y), sf::Color::Red));
			}

			_target.draw(workers, _states);
		}
	}
}