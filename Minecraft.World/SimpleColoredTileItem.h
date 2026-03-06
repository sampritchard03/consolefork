#include "TileItem.h"

class ItemInstance;

class SimpleColoredTileItem : public TileItem
{
public:
	SimpleColoredTileItem(int id);
	virtual int getLevelDataForAuxValue(int auxValue);
	virtual unsigned int getDescriptionId(shared_ptr<ItemInstance> instance);
};
