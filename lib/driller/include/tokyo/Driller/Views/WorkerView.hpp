#pragma once

#include <tokyo/Driller/Entities/Data/WorkerData.hpp>
#include <tokyo/Core/Infrastructure/TextureManager.hpp>
#include <tokyo/Driller/Services/Worker/WorkerPrototypeService.hpp>
#include <tokyo/Driller/Views/View.hpp>

namespace drl
{

	class WorkerView : public View
	{
	public:
		WorkerView(
			const WorkerData& _workerData,
			const WorkerPrototypeService& _workerPrototypeService,
			const tokyo::TextureManager& _textureManager
		);
		~WorkerView(void) override = default;

		void update(float _delta) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	private:
		const WorkerData& m_WorkerData;
		const WorkerPrototypeService& m_WorkerPrototypeService;
		const tokyo::TextureManager& m_TextureManager;
	};

}