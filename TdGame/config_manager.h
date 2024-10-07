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
		std::string window_title = u8"��ׯ����ս";
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
		std::ifstream file(path);

		if (!file.good()) return false;

		std::stringstream str_stream;
		str_stream << file.rdbuf(); file.close();

		cJSON* json_root = cJSON_Parse(str_stream.str().c_str());
		if (!json_root) return false;

		if (json_root->type != cJSON_Array)
		{
			cJSON_Delete(json_root);
			return false;
		}

		cJSON* json_wave = nullptr;
		cJSON_ArrayForEach(json_wave, json_root)
		{
			if (json_wave->type != cJSON_Object)
				continue;
			wave_list.emplace_back();
			Wave& wave = wave_list.back();

			cJSON* json_wave_rewards = cJSON_GetObjectItem(json_wave, "rewards");
			if (json_wave_rewards && json_wave_rewards->type == cJSON_Number)
				wave.rawards = json_wave_rewards->valuedouble;

			cJSON* json_wave_interval = cJSON_GetObjectItem(json_wave, "interval");
			if (json_wave_interval && json_wave_interval->type == cJSON_Number)
				wave.interval = json_wave_interval->valuedouble;

			cJSON* json_wave_spawn_list = cJSON_GetObjectItem(json_wave, "spawn_list");
			if (json_wave_spawn_list && json_wave_spawn_list->type == cJSON_Array);
			{
				cJSON* json_spawn_event = nullptr;
				cJSON_ArrayForEach(json_spawn_event, json_wave_spawn_list)
				{
					if (json_spawn_event->type != cJSON_Object)
						continue;

					wave.spawn_enevt_list.emplace_back();
					Wave::SpawnEvent& spawn_event = wave.spawn_enevt_list.back();

					cJSON* json_spawn_event_interval = cJSON_GetObjectItem(json_spawn_event, "interval");
					if (json_spawn_event_interval && json_spawn_event_interval->type == cJSON_Number)
						spawn_event.interval = json_spawn_event_interval->valuedouble;

					cJSON* json_spawn_event_spawn_point = cJSON_GetObjectItem(json_spawn_event, "point");
					if (json_spawn_event_spawn_point && json_spawn_event_spawn_point->type == cJSON_Number);
					spawn_event.spawn_point = json_spawn_event_spawn_point->valueint;
					
					cJSON* json_spawn_event_enemy_type = cJSON_GetObjectItem(json_spawn_event, "enemy");
					if (json_spawn_event_enemy_type && json_spawn_event_enemy_type->type == cJSON_String)
					{
						const std::string str_enemy_type = json_spawn_event_enemy_type->valuestring;
						if (str_enemy_type == "Slim")
							spawn_event.enemy_type = EnemyType::Slim;
						else if (str_enemy_type == "KingSlim")
							spawn_event.enemy_type = EnemyType::KingSlim;
						else if (str_enemy_type == "Skeleton")
							spawn_event.enemy_type = EnemyType::Skeleton;
						else if (str_enemy_type == "Goblin")
							spawn_event.enemy_type = EnemyType::Goblin;
						else if (str_enemy_type == "GoblinPriest")
							spawn_event.enemy_type = EnemyType::GoblinPriest;
					}
				}

				if (wave.spawn_enevt_list.empty())
					wave_list.pop_back();
			}

			
		}
		cJSON_Delete(json_root);

		if (wave_list.empty())
			return false;

		return true;

	}

	bool load_game_config(const std::string& path)
	{

	}

private:
	ConfigManager() = default;
	~ConfigManager() = default;
};


#endif // !_CONFIG_MANAGER_H_
