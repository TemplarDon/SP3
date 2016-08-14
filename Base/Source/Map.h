#ifndef MAP_H
#define MAP_H

#include <vector>
#include <fstream>
#include <string>
#include <sstream>

#include "GameObject.h"

class Map
{
public:
	Map()
	{}
	~Map()
	{}

	std::vector<std::vector<int>> m_ScreenMap;

	void Init(int ScreenHeight, int ScreenWidth, int NumOfTiles_ScreenHeight, int NumOfTiles_ScreenWidth, int MapHeight, int MapWidth, int TileSize = 25)
	{
		m_ScreenHeight = ScreenHeight;
		m_ScreenWidth = ScreenWidth;

		m_NumOfTiles_ScreenHeight = NumOfTiles_ScreenHeight;
		m_NumOfTiles_ScreenWidth = NumOfTiles_ScreenWidth;

		m_MapHeight = MapHeight;
		m_MapWidth = MapWidth;

		m_NumOfTiles_MapHeight = m_MapHeight / m_TileSize;
		m_NumOfTiles_MapWidth = m_MapWidth / m_TileSize;

		m_ScreenMap.resize(m_NumOfTiles_MapHeight);

		for (int i = 0; i < m_NumOfTiles_MapHeight; ++i)
		{
			m_ScreenMap[i].resize(m_NumOfTiles_MapWidth);
		}
	}

	bool LoadMap(const std::string mapName)
	{
		if (LoadFile(mapName))
		{
			printf("Map (%s) has been successfully loaded!\n", mapName.c_str());
			return true;
		}
		return false;
	}

	int GetNumOfTiles_ScreenHeight()
	{
		return m_NumOfTiles_ScreenHeight;
	}

	int GetNumOfTiles_ScreenWidth()
	{
		return m_NumOfTiles_ScreenWidth;
	}

	int GetTileSize()
	{
		return m_TileSize;
	}

	int GetNumOfTiles_MapHeight()
	{
		return m_NumOfTiles_MapHeight;
	}

	int GetNumOfTiles_MapWidth()
	{
		return m_NumOfTiles_MapWidth;
	}

private:
	int m_ScreenHeight;
	int m_ScreenWidth;
		
	int m_NumOfTiles_ScreenHeight;
	int m_NumOfTiles_ScreenWidth;
		
	int m_TileSize;

	int m_MapHeight;
	int m_MapWidth;

	int m_NumOfTiles_MapHeight;
	int m_NumOfTiles_MapWidth;

	bool LoadFile(const std::string mapName)
	{
		int LineCounter = 0;
		int MaxNumofColumns = 0;

		std::ifstream file(mapName.c_str());
		if (file.is_open())
		{
			int i = 0, k = 0;
			while (file.good())
			{
				std::string aLineOfText = "";
				std::getline(file, aLineOfText);

				if (LineCounter >= m_NumOfTiles_MapHeight)
					break;

				// If this line is not a comment line, then process it
				if (!(aLineOfText.find("//*") == NULL) && aLineOfText != "")
				{
					if (LineCounter == 0)
					{
						// This is the first line of the map data file
						std::string token;
						std::istringstream iss(aLineOfText);
						while (std::getline(iss, token, ','))
						{
							// Count the number of columns
							MaxNumofColumns = atoi(token.c_str());
						}
						if (MaxNumofColumns != m_NumOfTiles_MapWidth)
							return false;
					}
					else
					{
						int ColumnCounter = 0;

						std::string token;
						std::istringstream iss(aLineOfText);
						while (std::getline(iss, token, ',') && (ColumnCounter < m_NumOfTiles_MapWidth))
						{
							m_ScreenMap[LineCounter][ColumnCounter++] = atoi(token.c_str());
						}
					}
				}

				LineCounter++;
			}
		}
		return true;
	}
};


#endif // !MAP_H
