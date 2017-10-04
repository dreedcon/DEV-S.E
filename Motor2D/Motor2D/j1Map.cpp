#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>

j1Map::j1Map() : j1Module(), map_loaded(false)
{
	name.create("map");
}

// Destructor
j1Map::~j1Map()
{}

// Called before render is available
bool j1Map::Awake(pugi::xml_node& config)
{
	LOG("Loading Map Parser");
	bool ret = true;

	folder.create(config.child("folder").child_value());

	return ret;
}

void j1Map::Draw()
{
	if(map_loaded == false)
		return;

	// TODO 6: Iterate all tilesets and draw all their 
	// images in 0,0 (you should have only one tileset for now)
	App->render->Blit(App->tex->Load("maps/tmw_desert_spacing.png"), 0, 0);
}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");
	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map
	p2List_item<TileSet*>*  tileitem;
	tileitem = mapdata.tilesets.start;

	while (tileitem != NULL)
	{
		RELEASE(tileitem->data);
		tileitem = tileitem->next;
	}
	mapdata.tilesets.clear();

	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{

	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if (result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if (ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		LoadMap();
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	pugi::xml_node tiledata;
	tiledata = map_file.child("map");
	for (tiledata = tiledata.child("tileset"); tiledata && ret; tiledata = tiledata.next_sibling("tileset"))
	{
		TileSet* tileset = new TileSet;

		if (ret == true)
		{
			loadTileSet(tiledata, tileset);
		}

		mapdata.tilesets.add(tileset);

	}


	// TODO 5: LOG all the data loaded
	// iterate all tilesets and LOG everything

	map_loaded = ret;

	return ret;
}

bool j1Map::LoadMap()
{
	bool flag = true;
	pugi::xml_node map = map_file.child("map");

	if (map == NULL)
	{
		LOG("couldn`t access to the .tmx for read the map propierties");
		flag = false;
	}
	else
	{
		mapdata.width = map.attribute("width").as_int();
		mapdata.height = map.attribute("height").as_int();
		mapdata.tile_width = map.attribute("tilewidth").as_int();
		mapdata.tile_height = map.attribute("tileheight").as_int();

		p2SString types(map.attribute("orientation").as_string());

		if (types == "orthogonal")
		{
			mapdata.map_type = MAPTYPE_ORTHOGONAL;
		}
		else if (types == "isometric")
		{
			mapdata.map_type = MAPTYPE_ISOMETRIC;
		}
		else if (types == "staggered")
		{
			mapdata.map_type = MAPTYPE_STAGGERED;
		}
		else
		{
			mapdata.map_type = MAPTYPE_UNKNOWN;
		}

		p2SString orientation(map.attribute("renderorder").as_string());

		if (orientation == "right-down")
		{
			mapdata.pos_type = RIGHT_DOWN;
		}
		else if (orientation == "right-up")
		{
			mapdata.pos_type = RIGHT_UP;
		}
		else if (orientation == "left-down")
		{
			mapdata.pos_type = LEFT_DOWN;
		}
		else if (orientation == "left-up")
		{
			mapdata.pos_type = LEFT_UP;
		}

	}


	return flag;
}

bool j1Map::loadTileSet(pugi::xml_node &tilest_data, TileSet* set)
{
	bool flag = true;


	//load all data from the tileset of map
	//strings
	set->name.create(tilest_data.attribute("name").as_string());
	//ints
	set->firstgid = tilest_data.attribute("firstgid").as_int();
	set->margin = tilest_data.attribute("margin").as_int();
	set->spacing = tilest_data.attribute("spacing").as_int();
	set->tile_width = tilest_data.attribute("tilewidth").as_int();
	set->tile_height = tilest_data.attribute("tileheight").as_int();
	//struct terrain type
	//set->terraintype.name.create(tile_data.attribute("name").as_string());
	//set->terraintype.tile = tile_data.attribute("tile").as_int();

	//struct tiletype
	Tile* tile = new Tile;
	for (pugi::xml_node point = tilest_data.child("tile"); point != NULL; point = point.next_sibling("tile"))
	{
		set->LoadTile(point, tile);
		set->tiles.add(tile);
	}

	return flag;
}

bool TileSet::LoadTile(pugi::xml_node &node, Tile *tile)
{
	bool flag = true;

	tile->id = node.attribute("id").as_int();

	char* pointer;
	p2SString terrainvalue;
	terrainvalue.create(node.attribute("terrain").value());
	for (int i = 1; i<4; i++)
	{
		tile->terrain[0] = atoi(strtok_s((char*)terrainvalue.GetString(), ",", &pointer));
	}




	return flag;
}


