#pragma once

#include <tokyo/Driller/Entities/Data/JobData.hpp>
#include <tokyo/Core/Infrastructure/TextureManager.hpp>
#include <tokyo/Driller/Services/Job/JobPrototypeService.hpp>
#include <tokyo/Driller/Views/View.hpp>

namespace drl
{

	class JobView : public View
	{
	public:
		JobView(
			const JobData& _jobData,
			const IJobPrototypeService& _jobPrototypeService,
			const tokyo::TextureManager& _textureManager
		);
		~JobView(void) override = default;

		void update(float _delta) override;
		void draw(sf::RenderTarget& _target, sf::RenderStates _states) const override;

	private:
		const JobData& m_JobData;
		const IJobPrototypeService& m_JobPrototypeService;
		const tokyo::TextureManager& m_TextureManager;
	};

}