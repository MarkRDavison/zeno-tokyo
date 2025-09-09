#include <tokyo/Driller/Services/Shuttle/ShuttlePrototypeService.hpp>

namespace drl
{

	ShuttlePrototypeService::ShuttlePrototypeService(
		tokyo::IIdentificationService<IdType>& _identificationService
	) :
		PrototypeService<ShuttlePrototype, ShuttleInstance, ShuttlePrototypeId>(_identificationService)
	{

	}

	ShuttleInstance ShuttlePrototypeService::createInstance(const ShuttlePrototype& _prototype) const
	{
		ShuttleInstance shuttle{};
		shuttle.Id = m_IdentificationService.generateId();
		shuttle.prototypeId = getPrototypeId(_prototype.name);
		shuttle.state = ShuttleState::Idle;

		shuttle.startingPosition = { -50.0f, -20.0f }; // TODO: Constants/from prototype
		shuttle.surfacePosition = { -4.0f, 0.0f };// TODO: Constants/from prototype
		shuttle.leavingPosition = { +50.0f, -20.0f };// TODO: Constants/from prototype

		shuttle.position = shuttle.startingPosition;

		return shuttle;
	}

}