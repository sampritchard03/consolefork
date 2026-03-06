#include "stdafx.h"
#include "net.minecraft.world.level.tile.h"
#include "SimpleColoredTileItem.h"
#include "LangEN.h"

SimpleColoredTileItem::SimpleColoredTileItem(int id) : TileItem(id)
{        
	setMaxDamage(0);
	setStackedByData(true);
}

int SimpleColoredTileItem::getLevelDataForAuxValue(int auxValue)
{
	return auxValue;
}

unsigned int SimpleColoredTileItem::getDescriptionId(shared_ptr<ItemInstance> instance) 
{
	return ID_PLANKS_BLACK+instance->getAuxValue();
}
