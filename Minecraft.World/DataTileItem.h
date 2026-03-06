#include "TileItem.h"

class ItemInstance;

class DataTileItem : public TileItem
{

public:
	DataTileItem(int id, bool stackedByData);
	virtual int getLevelDataForAuxValue(int auxValue);
};
