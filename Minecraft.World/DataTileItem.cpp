#include "net.minecraft.world.level.tile.h"


DataTileItem::DataTileItem(int id) : TileItem(id)
{
	setMaxDamage(0);
	setStackedByData(true);
}


int DataTileItem::getLevelDataForAuxValue(int auxValue) 
{
	return auxValue;
}