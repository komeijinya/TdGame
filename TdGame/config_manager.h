#ifndef _CONFIG_MANAGER_H_
#define _CONFIG_MANAGER_H_

#include "map.h"
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

private:
	ConfigManager() = default;
	~ConfigManager() = default;
};


#endif // !_CONFIG_MANAGER_H_
