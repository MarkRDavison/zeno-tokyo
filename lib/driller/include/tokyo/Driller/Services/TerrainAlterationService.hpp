#pragma once

#include <tokyo/Driller/Entities/Data/TerrainData.hpp>

namespace drl
{

	class ITerrainAlterationService
	{
	public:
		virtual ~ITerrainAlterationService(void) = 0;

		virtual bool digShaft(int _level) = 0;
		virtual bool digTile(int _level, int _column) = 0;
		virtual bool createTile(int _levelMin, int _levelMax, int _columnMin, int _columnMax) = 0;
		virtual bool doesTileExist(int _level, int _column) const = 0;
		virtual Tile& getTile(int _level, int _column) = 0;
		virtual const Tile& getTile(int _level, int _column) const = 0;
		virtual bool isTileDugOut(int _level, int _column) const = 0;
		virtual void initialiseTile(int _level, int _column) = 0;
		virtual bool doesLevelExist(int _level) const = 0;
		virtual bool canTileBeReached(int _level, int _column) const = 0;
		virtual bool isLevelNextShaftLevel(int _level) const = 0;

	};

	inline ITerrainAlterationService::~ITerrainAlterationService(void) = default;

	class TerrainAlterationService : public ITerrainAlterationService
	{
	public:
		TerrainAlterationService(
			TerrainData& _terrainData
		);
		~TerrainAlterationService(void) override = default;

		bool digShaft(int _level) override;
		bool digTile(int _level, int _column) override;
		bool createTile(int _levelMin, int _levelMax, int _columnMin, int _columnMax) override;
		bool doesTileExist(int _level, int _column) const override;
		Tile& getTile(int _level, int _column) override;
		const Tile& getTile(int _level, int _column) const override;
		bool isTileDugOut(int _level, int _column) const override;
		void initialiseTile(int _level, int _column) override;
		bool doesLevelExist(int _level) const override;
		bool canTileBeReached(int _level, int _column) const override;
		bool isLevelNextShaftLevel(int _level) const override;

	private:
		TerrainData& m_TerrainData;
	};
}