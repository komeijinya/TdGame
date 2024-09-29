#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

#include "map.h"
#include "wave.h"
#include "manager.h"

#include <SDL.h>
#include <string>
#include <sstream>
#include <cJSON.h>
#include <fstream>
#include <iostream>

class ConfigManager : public Manager<ConfigManager>
{

	friend class Manager<ConfigManager>;
public:

	struct BasicTemplate
	{
		std::string window_title = u8"´å×¯±£ÎÀÕ½";
		int window_width = 1280;
		int window_height = 720;
	};


	struct PlayerTemplate
	{
		double speed = 3;
		double normal_attack_interval = 0.5;
		double normal_attack_damage = 0;
		double skill_interval = 0;
		double skill_damage = 1;

	};

	struct TowerTemplate
	{
		double interval[10] = { 1 };
		double damage[10] = { 25 };
		double view_range[10] = { 5 };
		double cost[10] = { 50 };
		double upgrade_cost[9] = { 75 };
	};

	struct EneyTemplate
	{
		double hp = 100;
		double speed = 1;
		double reward_ratio = 0.5;
		double recover_interval  = 10;
		double recover_range = 0;
		double recover_intensity = 25;
	};

public:
	Map map;
	std::vector<Wave> wave_list;

	int level_archer = 0;
	int level_axman = 0;
	int level_gunner = 0;

	bool is_game_win = true;
	bool is_game_over = false;
	SDL_Rect rect_tile_map = { 0 };

	BasicTemplate basic_template;

	PlayerTemplate player_templata;

	TowerTemplate archer_template;
	TowerTemplate axman_template;
	TowerTemplate gunner_template;

	EnemyType slim_template;
	EnemyType king_slim_template;
	EnemyType skeleton_template;
	EnemyType goblin_template;
	EnemyType goblin_priesst_template;

	const double num_initial_hp = 10;
	const double num_initial_coin = 100;
	const double num_coin_per_prop = 10;

public:
	bool load_level_config(const std::string& path)
	{

	}

	bool load_game_config(const std::string& path)
	{

	}

private:
	ConfigManager() = default;
	~ConfigManager() = default;
};


#endif // !_CONFIG_MANAGER_H_
