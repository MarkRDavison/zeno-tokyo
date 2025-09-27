#include <tokyo/Driller/Services/TerrainAlterationService.hpp>

namespace drl
{
	TerrainAlterationService::TerrainAlterationService(
		TerrainData& _terrainData
	) :
		m_TerrainData(_terrainData)
	{
	}

	bool TerrainAlterationService::digShaft(int _level)
	{
		if (m_TerrainData.shaftLevel == _level - 1)
		{
			m_TerrainData.shaftLevel = _level;
			if (m_TerrainData.shaftLevel >= m_TerrainData.rows.size())
			{
				m_TerrainData.rows.emplace_back();
			}
			return true;
		}

		return false;
	}

	Tile* getTileInternal(TerrainData& _terrainData, int _level, int _column)
	{
		if (_column == 0)
		{
			return nullptr;
		}

		while (static_cast<int>(_terrainData.rows.size()) <= _level)
		{
			_terrainData.rows.emplace_back();
		}

		if (static_cast<int>(_terrainData.rows.size()) > _level)
		{
			TerrainRow& row = _terrainData.rows[static_cast<unsigned>(_level)];
			const unsigned xCoord = static_cast<unsigned>(std::abs(_column) - (_column == 0 ? 0 : 1));
			if (_column > 0)
			{
				while (row.rightTiles.size() <= xCoord)
				{
					row.rightTiles.emplace_back();
				}
				return &row.rightTiles[xCoord];
			}

			if (_column < 0)
			{
				while (row.leftTiles.size() <= xCoord)
				{
					row.leftTiles.emplace_back();
				}
				return &row.leftTiles[xCoord];
			}
		}

		return nullptr;
	}

	bool TerrainAlterationService::digTile(int _level, int _column)
	{
		if (_column == 0)
		{
			return false;
		}

		while (static_cast<int>(m_TerrainData.rows.size()) <= _level)
		{
			m_TerrainData.rows.emplace_back();
		}

		TerrainRow& row = m_TerrainData.rows[static_cast<unsigned>(_level)];
		const unsigned xCoord = static_cast<unsigned>(std::abs(_column) - (_column == 0 ? 0 : 1));
		if (_column > 0)
		{
			if (row.rightTiles.size() == xCoord)
			{
				// Need to append a new tile
				Tile& t = row.rightTiles.emplace_back();
				t.jobReserved = false;
				t.dugOut = true;
				return true;
			}
			if (row.rightTiles.size() > xCoord)
			{
				// There is already a tile, just need to dig it out
				Tile& t = row.rightTiles[xCoord];
				if (t.dugOut)
				{
					return false;
				}
				t.jobReserved = false;
				t.dugOut = true;
				return true;
			}

			return false;
		}

		if (_column < 0)
		{
			if (row.leftTiles.size() == xCoord)
			{
				// Need to append a new tile
				Tile& t = row.leftTiles.emplace_back();
				t.jobReserved = false;
				t.dugOut = true;
				return true;
			}
			if (row.leftTiles.size() > xCoord)
			{
				// There is already a tile, just need to dig it out
				Tile& t = row.leftTiles[xCoord];
				if (t.dugOut)
				{
					return false;
				}
				t.jobReserved = false;
				t.dugOut = true;
				return true;
			}

			return false;
		}

		return false;
	}

	bool TerrainAlterationService::createTile(int _levelMin, int _levelMax, int _columnMin, int _columnMax)
	{
		if (_columnMin < 0 && _columnMax < 0)
		{
			for (int level = _levelMin; level <= _levelMax; ++level)
			{
				for (int column = _columnMin; column >= _columnMax; --column)
				{
					getTileInternal(m_TerrainData, level, column);
				}
			}
		}
		else
		{
			for (int level = _levelMin; level <= _levelMax; ++level)
			{
				for (int column = _columnMin; column <= _columnMax; ++column)
				{
					getTileInternal(m_TerrainData, level, column);
				}
			}
		}

		return true;
	}

	bool TerrainAlterationService::doesTileExist(int _level, int _column) const
	{
		if (_column == 0)
		{
			return false;
		}
		const unsigned xCoord = static_cast<unsigned>(std::abs(_column) - 1);
		if (_level < 0 || _level >= static_cast<int>(m_TerrainData.rows.size()))
		{
			return false;
		}
		const TerrainRow& row = m_TerrainData.rows[static_cast<unsigned>(_level)];

		if (_column > 0)
		{
			if (static_cast<int>(row.rightTiles.size()) > xCoord)
			{
				return true;
			}
		}
		else
		{
			if (static_cast<int>(row.leftTiles.size()) > xCoord)
			{
				return true;
			}
		}

		return false;
	}

	Tile& TerrainAlterationService::getTile(int _level, int _column)
	{
		if (_level < 0)
		{
			throw std::runtime_error("Cannot retrieve above ground TerrainTile");
		}

		if (_column != 0)
		{
			if (!doesTileExist(_level, _column))
			{
				createTile(_level, _level, _column, _column);
			}

			const unsigned xCoord = static_cast<unsigned>(std::abs(_column)) - (_column == 0 ? 0 : 1);
			if (_column < 0)
			{
				return m_TerrainData.rows[static_cast<unsigned>(_level)].leftTiles[xCoord];
			}
			if (_column > 0)
			{
				return m_TerrainData.rows[static_cast<unsigned>(_level)].rightTiles[xCoord];
			}
		}

		throw std::runtime_error("Cannot retrieve shaft TerrainTile");
	}

	const Tile& TerrainAlterationService::getTile(int _level, int _column) const
	{
		if (_level < 0)
		{
			throw std::runtime_error("Cannot retrieve above ground TerrainTile");
		}

		const unsigned xCoord = static_cast<unsigned>(std::abs(_column)) - (_column == 0 ? 0 : 1);
		if (_column < 0)
		{
			return m_TerrainData.rows[static_cast<unsigned>(_level)].leftTiles[xCoord];
		}
		if (_column > 0)
		{
			return m_TerrainData.rows[static_cast<unsigned>(_level)].rightTiles[xCoord];
		}

		throw std::runtime_error("Cannot retrieve shaft TerrainTile");
	}

	bool TerrainAlterationService::isTileDugOut(int _level, int _column) const
	{
		if (doesTileExist(_level, _column))
		{
			return getTile(_level, _column).dugOut;
		}
		return false;
	}

	void TerrainAlterationService::initialiseTile(int _level, int _column)
	{
		if (doesTileExist(_level, _column))
		{
			return;
		}

		while (static_cast<int>(m_TerrainData.rows.size()) <= _level)
		{
			m_TerrainData.rows.emplace_back();
		}

		TerrainRow& row = m_TerrainData.rows[_level];
		const int xCoord = std::abs(_column) - 1;

		if (_column > 0)
		{
			while (static_cast<int>(row.rightTiles.size()) <= xCoord)
			{
				row.rightTiles.emplace_back();
			}
		}

		if (_column < 0)
		{
			while (static_cast<int>(row.leftTiles.size()) <= xCoord)
			{
				row.leftTiles.emplace_back();
			}
		}
	}

	bool TerrainAlterationService::doesLevelExist(int _level) const
	{
		return m_TerrainData.shaftLevel >= _level;
	}
	bool TerrainAlterationService::canTileBeReached(int _level, int _column) const
	{
		if (_level < 0)
		{
			return true;
		}

		if (!doesLevelExist(_level))
		{
			return false;
		}

		bool valid = _column == 0;
		for (int x = 1; x <= std::abs(_column); ++x)
		{
			const auto column = _column < 0
				? -x
				: +x;
			if (doesTileExist(_level, column))
			{
				auto tile = getTile(_level, column);
				if (!tile.dugOut)
				{
					if (column != _column || !tile.jobReserved)
					{
						return false;
					}
				}
				valid = true;
			}
			else
			{
				return false;
			}
		}

		return valid;
	}

	bool TerrainAlterationService::isLevelNextShaftLevel(int _level) const
	{
		return m_TerrainData.shaftLevel == _level - 1;
	}

}