#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "Player.h"
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

	folder.create(config.attribute("file").as_string());

	return ret;
}

void j1Map::Draw(int time)
{
	if(map_loaded == false)
		return;

	p2List_item<MapLayer*>* item = mapdata.layers.start;

	for (; item != mapdata.layers.end->next; item = item->next)
	{
		MapLayer* layer = item->data;

		if (time == -1)
		{
			for (int y = 0; y < mapdata.height; ++y)
			{
				for (int x = 0; x < mapdata.width; ++x)
				{
					int tile_id = layer->Get(x, y);
					if (tile_id > 0)
					{
						TileSet* tileset = GetTilesetFromTileId(tile_id);

						SDL_Rect r = tileset->GetTileRect(tile_id);
						iPoint pos = MapToWorld(x, y);

						if (App->player->CanFollowPlayer())
						{
							if (App->player->GetDirection() == LEFT)
							{
								posBackground.x += 0.0001;
								App->render->Blit(tileset->texture, pos.x + posBackground.x, pos.y, &r);
							}
							else if (App->player->GetDirection() == RIGHT)
							{
								posBackground.x -= 0.0001;
								App->render->Blit(tileset->texture, pos.x + posBackground.x, pos.y, &r);
							}
						}
						else
						{
							App->render->Blit(tileset->texture, pos.x + posBackground.x, pos.y, &r);
						}
					}
				}
			}
			return;
		}
		else
		{
			if (layer->properties.Get("Background") != 0)
				continue;

			if (layer->properties.Get("Draw") != 1)
				continue;

			if (time == 1)
			{
				if (layer->properties.Get("NoDraw") != 1)
					continue;
			}
			else
			{
				if (layer->properties.Get("NoDraw") != 0)
					continue;
			}
			for (int y = 0; y < mapdata.height; ++y)
			{
				for (int x = 0; x < mapdata.width; ++x)
				{
					int tile_id = layer->Get(x, y);
					if (tile_id > 0)
					{
						TileSet* tileset = GetTilesetFromTileId(tile_id);

						SDL_Rect r = tileset->GetTileRect(tile_id);
						iPoint pos = MapToWorld(x, y);

						App->render->Blit(tileset->texture, pos.x, pos.y, &r);
					}
				}
			}
		}
	}
}

int Properties::Get(const char* value, int default_value) const
{
	p2List_item<Property*>* item = properties.start;
	while (item != properties.end->next)
	{
		if (strcmp(item->data->name.GetString(), value) == 0)
			return item->data->value;
		item = item->next;
	}

	return default_value;
}

TileSet* j1Map::GetTilesetFromTileId(int id) const
{
	TileSet* set = mapdata.tilesets.start->data;
	p2List_item<TileSet*>* item = mapdata.tilesets.start;
	for (uint i = 0; i < mapdata.tilesets.count(); i++)
	{
		if (id < item->data->firstgid)
		{
			set = item->prev->data;
			break;
		}
		set = item->data;
		item = item->next;
	}
	return set;
}

SDL_Rect TileSet::GetTileRect(int id) const
{
	int relative_id = id - firstgid;
	SDL_Rect rect;
	rect.w = tile_width;
	rect.h = tile_height;
	rect.x = margin + ((rect.w + spacing) * (relative_id % num_tiles_width));
	rect.y = margin + ((rect.h + spacing) * (relative_id / num_tiles_width));
	return rect;
}

iPoint j1Map::MapToWorld(int x, int y) const
{
	iPoint ret;

	if (mapdata.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x * mapdata.tile_width;
		ret.y = y * mapdata.tile_height;
	}
	else if (mapdata.type == MAPTYPE_ISOMETRIC)
	{
		ret.x = (x - y) * (mapdata.tile_width * 0.5f);
		ret.y = (x + y) * (mapdata.tile_height * 0.5f);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
}

iPoint j1Map::WorldToMap(int x, int y) const
{
	iPoint ret(0, 0);

	if (mapdata.type == MAPTYPE_ORTHOGONAL)
	{
		ret.x = x / mapdata.tile_width;
		ret.y = y / mapdata.tile_height;
	}
	else if (mapdata.type == MAPTYPE_ISOMETRIC)
	{

		float half_width = mapdata.tile_width * 0.5f;
		float half_height = mapdata.tile_height * 0.5f;
		ret.x = int((x / half_width + y / half_height) / 2) - 1;
		ret.y = int((y / half_height - (x / half_width)) / 2);
	}
	else
	{
		LOG("Unknown map type");
		ret.x = x; ret.y = y;
	}

	return ret;
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

	p2List_item<MapLayer*>* layeritem;
	layeritem = mapdata.layers.start;

	while (layeritem != NULL)
	{
		RELEASE(layeritem->data);
		layeritem = layeritem->next;
	}
	mapdata.layers.clear();

	map_file.reset();

	return true;
}

bool j1Map::NextLvl(int x, int y, int width, int height) const //TODO ELLIOT NEED FIX
{
	int blue_nextlvl = mapdata.tilesets.start->next->data->firstgid + 1; // RED TILE

	iPoint center = WorldToMap(x + width / 2, y + height / 2); //left position

	const MapLayer* meta_layer = mapdata.layers.start->next->next->next->data;

	int center_player = meta_layer->Get(center.x, center.y);

	if (center_player == blue_nextlvl)
		return true;

	return false;
}

bool j1Map::MovementCost(int x, int y, int width, int height, Direction dir) const //TODO ELLIOT NEED FIX
{
	int red_wall = mapdata.tilesets.start->next->data->firstgid; // RED TILE
	bool ret = true;

	iPoint up_left = WorldToMap(x, y); //left position
	iPoint up_right = WorldToMap(x + width, y); //left position
	iPoint down_right = WorldToMap(x + width, y + height); //left position
	iPoint down_left = WorldToMap(x, y + height); //left position


	const MapLayer* meta_layer = mapdata.layers.start->next->next->next->data;

	int up = meta_layer->Get(up_left.x, up_left.y);
	int left = meta_layer->Get(up_left.x, up_left.y);
	int right = meta_layer->Get(down_right.x, down_right.y);
	int down = meta_layer->Get(down_right.x, down_right.y);
	//Special
	int up_right_special = meta_layer->Get(up_right.x, up_right.y);
	int down_left_special = meta_layer->Get(down_left.x, down_left.y);

	if (dir == UP)
	{
		if (up == red_wall || up_right_special == red_wall)
		{
			ret = false;
		}

	}
	if (dir == LEFT)
	{
		if (left == red_wall)
		{
			ret = false;
		}
	}
	if (dir == RIGHT)
	{
		if (right == red_wall)
		{
			ret = false;
		}
	}
	if (dir == DOWN)
	{
		if (down == red_wall || down_left_special == red_wall)
		{
			ret = false;
		}
	}


	return ret;
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
		TileSet* tileset = new TileSet();

		if (ret == true)
		{
			loadTileSet(tiledata, tileset);
		}
		if (ret == true)
		{
			ret = LoadTilesetImage(tiledata, tileset);
		}

		mapdata.tilesets.add(tileset);

	}

	// Load layer info ----------------------------------------------
	pugi::xml_node layer;
	for (layer = map_file.child("map").child("layer"); layer && ret; layer = layer.next_sibling("layer"))
	{
		MapLayer* lay = new MapLayer();

		ret = LoadLayer(layer, lay);

		if (ret == true)
			mapdata.layers.add(lay);
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
			mapdata.type = MAPTYPE_ORTHOGONAL;
		}
		else if (types == "isometric")
		{
			mapdata.type = MAPTYPE_ISOMETRIC;
		}
		else if (types == "staggered")
		{
			mapdata.type = MAPTYPE_STAGGERED;
		}
		else
		{
			mapdata.type = MAPTYPE_UNKNOWN;
		}

		/*p2SString orientation(map.attribute("renderorder").as_string());

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
		}*/

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
	pugi::xml_node offset = tilest_data.child("tileoffset");
	//struct terrain type
	//set->terraintype.name.create(tile_data.attribute("name").as_string());
	//set->terraintype.tile = tile_data.attribute("tile").as_int();
	if (offset != NULL)
	{
		set->offset_x = offset.attribute("x").as_int();
		set->offset_y = offset.attribute("y").as_int();
	}
	else
	{
		set->offset_x = 0;
		set->offset_y = 0;
	}
	//struct tiletype
	/*Tile* tile = new Tile;
	for (pugi::xml_node point = tilest_data.child("tile"); point != NULL; point = point.next_sibling("tile"))
	{
		set->LoadTile(point, tile);
		set->tiles.add(tile);
	}*/

	return flag;
}

bool j1Map::LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set)
{
	bool ret = true;
	pugi::xml_node image = tileset_node.child("image");

	if (image == NULL)
	{
		LOG("Error parsing tileset xml file: Cannot find 'image' tag.");
		ret = false;
	}
	else
	{
		set->texture = App->tex->Load(PATH(folder.GetString(), image.attribute("source").as_string()));
		int w, h;
		SDL_QueryTexture(set->texture, NULL, NULL, &w, &h);
		set->tex_width = image.attribute("width").as_int();

		if (set->tex_width <= 0)
		{
			set->tex_width = w;
		}

		set->tex_height = image.attribute("height").as_int();

		if (set->tex_height <= 0)
		{
			set->tex_height = h;
		}

		set->num_tiles_width = set->tex_width / (set->tile_width + set->margin);
		set->num_tiles_height = set->tex_height / (set->tile_height + set->margin);
	}

	return ret;
}

bool j1Map::LoadLayer(pugi::xml_node& node, MapLayer* layer)
{
	bool ret = true;

	layer->name = node.attribute("name").as_string();
	layer->width = node.attribute("width").as_int();
	layer->height = node.attribute("height").as_int();
	LoadProperties(node, layer->properties);
	pugi::xml_node layer_data = node.child("data");

	if (layer_data == NULL)
	{
		LOG("Error parsing map xml file: Cannot find 'layer/data' tag.");
		ret = false;
		RELEASE(layer);
	}
	else
	{
		layer->data = new uint[layer->width*layer->height];
		memset(layer->data, 0, layer->width*layer->height);

		int i = 0;
		for (pugi::xml_node tile = layer_data.child("tile"); tile; tile = tile.next_sibling("tile"))
		{
			layer->data[i++] = tile.attribute("gid").as_int(0);
		}
	}

	return ret;
}

// Load a group of properties from a node and fill a list with it
bool j1Map::LoadProperties(pugi::xml_node& node, Properties& properties)
{
	bool ret = false;

	pugi::xml_node data = node.child("properties");

	if (data != NULL)
	{
		pugi::xml_node prop;

		for (prop = data.child("property"); prop; prop = prop.next_sibling("property"))
		{
			Properties::Property* p = new Properties::Property();

			p->name = prop.attribute("name").as_string();
			p->value = prop.attribute("value").as_int();

			properties.properties.add(p);
		}
	}

	return ret;
}

/*bool TileSet::LoadTile(pugi::xml_node &node, Tile *tile)
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
}*/


