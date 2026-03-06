#pragma once
#include "Tile.h"

class Random;

class ColoredPlanksTile : public Tile
{
private:
	int m_colors[16];
public:
	ColoredPlanksTile(int id);
    virtual int getResource(int data, Random *random, int playerBonusLevel);
	virtual int getResourceCount(Random *random);
	virtual int getSpawnResourcesAuxValue(int data);
	virtual int getColor(int auxData);
	virtual int getColor(LevelSource *level, int x, int y, int z);
	virtual int getColor(LevelSource *level, int x, int y, int z, int data);

};//pragma once
