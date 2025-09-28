#pragma once

#include <tokyo/Driller/Entities/TerrainRow.hpp>
#include <stdexcept>
#include <cmath>

namespace drl
{

	struct TerrainData
	{

		std::vector<TerrainRow> rows;

		int shaftLevel{ -1 };

		bool tileExists(int _level, int _column) const
		{
			if (_column == 0)
			{
				return false;
			}
			const unsigned xCoord = static_cast<unsigned>(std::abs(_column) - 1);
			if (_level >= static_cast<int>(rows.size()))
			{
				return false;
			}
			const TerrainRow& row = rows[static_cast<unsigned>(_level)];

			if (_column > 0)
			{
				if (static_cast<unsigned>(row.rightTiles.size()) > xCoord)
				{
					return true;
				}
			}
			else
			{
				if (static_cast<unsigned>(row.leftTiles.size()) > xCoord)
				{
					return true;
				}
			}

			return false;
		}

		const Tile& getTile(int _level, int _column) const
		{
			const unsigned xCoord = static_cast<unsigned>(std::abs(_column)) - (_column == 0 ? 0 : 1);

			if (_column < 0)
			{
				return rows[static_cast<unsigned>(_level)].leftTiles[xCoord];
			}

			if (_column > 0)
			{
				return rows[static_cast<unsigned>(_level)].rightTiles[xCoord];
			}

			throw std::runtime_error("Cannot retrieve shaft Tile");
		}

		Tile& getTile(int _level, int _column)
		{
			const unsigned xCoord = static_cast<unsigned>(std::abs(_column)) - (_column == 0 ? 0 : 1);

			if (_column < 0)
			{
				return rows[static_cast<unsigned>(_level)].leftTiles[xCoord];
			}

			if (_column > 0)
			{
				return rows[static_cast<unsigned>(_level)].rightTiles[xCoord];
			}

			throw std::runtime_error("Cannot retrieve shaft Tile");
		}

	};

}