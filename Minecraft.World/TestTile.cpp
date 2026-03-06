#include "stdafx.h"
#include "TestTile.h"

TestTile::TestTile(int id) : Tile(id, Material::stone)
{
	m_colors[0] = 1973019;
	m_colors[1] = 11743532;
	m_colors[2] = 3887386;
	m_colors[3] = 5320730;
	m_colors[4] = 2437522;
	m_colors[5] = 8073150;
	m_colors[6] = 2651799;
	m_colors[7] = 11250603;
	m_colors[8] = 4408131;
	m_colors[9] = 14188952;
	m_colors[10] = 4312372;
	m_colors[11] = 14602026;
	m_colors[12] = 6719955;
	m_colors[13] = 12801229;
	m_colors[14] = 15435844;
	m_colors[15] = 15790320;
}

int TestTile::getResource(int data, Random *random, int playerBonusLevel)
{
	return Tile::testBlock_Id;
}

int TestTile::getResourceCount(Random* random)
{
	return 1;
}

int TestTile::getColor(int auxData)
{
	return m_colors[auxData];
}

int TestTile::getColor(LevelSource *level, int x, int y, int z)
{
	return getColor(level->getData(x, y, z));
}

int TestTile::getColor(LevelSource *level, int x, int y, int z, int data)
{
	return getColor(level->getData(x, y, z));
}