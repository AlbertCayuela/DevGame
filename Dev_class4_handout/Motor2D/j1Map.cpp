#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include <math.h>
#include <string>

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

	for (int i = 1; i <= tileset_num; i++) 
	{

	}

}

// Called before quitting
bool j1Map::CleanUp()
{
	LOG("Unloading map");

	// TODO 2: Make sure you clean up any memory allocated
	// from tilesets / map
	

	map_file.reset();

	return true;
}

// Load new map
bool j1Map::Load(const char* file_name)
{
	bool ret = true;
	p2SString tmp("%s%s", folder.GetString(), file_name);

	pugi::xml_parse_result result = map_file.load_file(tmp.GetString());

	if(result == NULL)
	{
		LOG("Could not load map xml file %s. pugi error: %s", file_name, result.description());
		ret = false;
	}

	if(ret == true)
	{
		// TODO 3: Create and call a private function to load and fill
		// all your map data
		LoadMap();
	}

	// TODO 4: Create and call a private function to load a tileset
	// remember to support more any number of tilesets!
	
	LoadTileSet();

	if(ret == true)
	{
		// TODO 5: LOG all the data loaded
		// iterate all tilesets and LOG everything
		for (int i = 1; i <= tileset_num; i++) 
		{
			LOG("MAP VERSION: %f", map_info.version);
			LOG("MAP ORIENTATION: %s", map_info.orientation.GetString());
			LOG("MAP RENDERORDER: %s", map_info.renderorder.GetString());
			LOG("MAP WIDTH: %i", map_info.width);
			LOG("MAP HEIGHT: %i", map_info.height);
			LOG("MAP TILEWIDTH: %i", map_info.tilewidth);
			LOG("MAP TILEHEIGHT: %i", map_info.tileheight);
			LOG("MAP NEXTOBJECTID: %i", map_info.nextobjectid);
			LOG("TILESET FIRSTGID: %i", tileset.firstgid);
			LOG("TILESET NAME: %s", tileset.name.GetString());
			LOG("TILESET TILEWIDTH: %i", tileset.tilewidth);
			LOG("TILESET TILEHEIGHT: %i", tileset.tileheight);
			LOG("TILESET SPACING: %i", tileset.spacing);
			LOG("TILESET MARGIN: %i", tileset.margin);
		}
	}

	map_loaded = ret;

	return ret;
}

bool j1Map::LoadMap()
{
	pugi::xml_parse_result res;

	res = hello2.load_file("\maps/hello2.tmx");
	
	if (res == NULL)
	{
		LOG("Could not load hello2.tmx file. ERROR: %s", res.description());

		return false;
	}
	else
	{
		LOG("file hello2.tmx loaded correctly");
		map = hello2.child("map");
		map_info.version = map.attribute("version").as_float();
		map_info.orientation = map.attribute("orientation").as_string();
		map_info.renderorder = map.attribute("renderorder").as_string();
		map_info.width = map.attribute("width").as_int();
		map_info.height = map.attribute("height").as_int();
		map_info.tilewidth = map.attribute("tilewidth").as_int();
		map_info.tileheight = map.attribute("tileheight").as_int();
		map_info.nextobjectid = map.attribute("nextobjectid").as_int();

		return true;
	}
}

bool j1Map::LoadTileSet()
{


	pugi::xml_node tile_set = map.child("tileset");

	

	for (tile_set; tile_set; tile_set = tile_set.next_sibling("tileset")) 
	{
		tileset_num += 1;

		tileset.firstgid = tile_set.attribute("first_gid").as_int();
		tileset.name = tile_set.attribute("name").as_string();
		tileset.tilewidth = tile_set.attribute("tilewidth").as_int();
		tileset.tileheight = tile_set.attribute("tileheight").as_int();
		tileset.spacing = tile_set.attribute("spacing").as_int();
		tileset.margin = tile_set.attribute("margin").as_int();
	
	}


	return true;
}

