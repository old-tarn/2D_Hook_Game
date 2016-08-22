#ifndef __TILE_H__
#define __TILE_H__

#include "entity.h"


class Tile : public Entity
{
public:
	Tile();
	~Tile();

	enum Type
	{
		GRASS,
		DAMAGE,
		BOUNCE,
		ENTER,
		EXIT
	};

	void SetType(Type t);

public:
	Type type;

	

};

#endif // __TILE_H__