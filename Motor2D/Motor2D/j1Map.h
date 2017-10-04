#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"

// TODO 2: Create a struct to hold information for a TileSet
// Ignore Terrain Types and Tile Types for now, but we want the image!
// ----------------------------------------------------
struct Image
{

	p2SString source;
	int width;
	int height;

};

struct TerrainType
{

	p2SString name;
	int tile;

};

struct Tile
{

	int id;
	p2SString terrain[4];

};

struct TileSet
{
	p2SString name;
	int firstgid;
	int margin;
	int spacing;
	int tile_width;
	int tile_height;
	Image image;
	TerrainType terraintype;
	p2List<Tile*> tiles;
	bool LoadTile(pugi::xml_node&, Tile*);

};


// TODO 1: Create a struct needed to hold the information to Map node
enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};

enum RenderOrder
{
	RIGHT_DOWN = 0,
	RIGHT_UP,
	LEFT_DOWN,
	LEFT_UP
};

struct MapData
{

	int width;
	int height;
	int tile_width;
	int tile_height;
	MapTypes map_type;
	RenderOrder pos_type;
	p2List<TileSet*>	tilesets;
};


// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

private:
	
	//Load map function are private alone map can acces
	bool LoadMap();
	bool loadTileSet(pugi::xml_node&, TileSet*);

public:

	// TODO 1: Add your struct for map info as public for now
	MapData mapdata;
	TileSet tileset;
private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded;
};

#endif // __j1MAP_H__