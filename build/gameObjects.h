#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <SFML/System/Vector2.hpp>

#include "gameObjects.cpp"

#include <chrono>

enum objectID {
	nothing,
	bullet1, bullet1_destroy,
	bullet2, bullet2_destroy,
	guardian_bullet, guardian_bullet_destroy,
	large_guardian_bullet, large_guardian_bullet_destroy,
	T2_bullet,
	throne_beam_charge_particle,

	idpd_bullet, idpd_bullet_destroy,

	toxic_gas,
	toxic_gas_destroy,

	the_wind,

	flame,



	static_effect,


	scorch,
	idpd_explosion,
	idpd_nade, idpd_nade_remove,
	idpd_portal_charge,
	idpd_spawn,

	rogue_strike,

	explosion,

	player,
	player_corpse,

	rebel_ally,

	crystal_shield,

	melt_splat,

	meat_explosion,

	plant_tangle_seed,
	plant_tangle,

	throne_2, throne_2_death,

	popup_text,

	feather_raven, 
	feather, 
	money,

	stress_sweat,

	rad, rad_destroy,

	ammo_pack, health_pack,
	ammo_pack_destroy, heal_FX,
	weapon_drop,
	lust_FX,
	laser_brain_FX,

	bandit, enemy_corpse, 
	scorpion,
	gold_scorpion,

	idpd_freak, idpd_freak_corpse, idpd_freak_revive,

	player_bullet, player_bullet_destroy,
	player_bouncer_bullet, player_bouncer_bullet_destroy,

	plasma_huge, plasma_big, 
	plasma, plasma_impact,
	plasma_particle,
	plasma_hit,

	ultra_slash,

	horror_bullet, horror_bullet_destroy,

	portal_clear,
	portal,
	portal_lightning,

	prop,
	prop_dead,

	//effects
	debris,
	dust,
	smoke,
	deflect,
	detail,

	//floors variations
	floor_1,
	floor_2,
	floor_3,
	floor_4,
	floor_5,
	floor_6,
	floor_7,
	floor_8,

};

enum prop_ID {
	//area 0
	cactus_0_1,
	cactus_0_2,
	cactus_0_3,
	bones_0_1,

	//area 1
	cactus_1_1,
	cactus_1_2,
	cactus_1_3,
	cactus_1_1b,
	cactus_1_2b,
	cactus_1_3b,
	barrel_1_1,
	bones_1_1,
	skull_1_1,

	//area 2
	pipe_2_1,
	toxic_barrel_2_1,

	//area 3
	tires_3_1,
	car_3_1,
	
	//area 4
	egg_4_1,
	crystal_4_1,
	crystal_4_2,
	crystal_4_3,

	//area 5
	fire_hydrant_5_1,
	icicle_5_1,
	news_stand_5_1,
	vending_machine_5_1,
	snowman_5_1,
	car_5_1,
	street_light_5_1,

	//area 6
	terminal_6_1,
	mutant_tube_6_1,
	tube_6_1,
	server_6_1,

	//area 7
	small_generator_7_1,
	nuclear_pillar_7_1,
};

enum enemy_corpses {
	//used for offsets when drawing corpse
	bandit_CORPSE,
	idpd_freak_CORPSE,	//filler, not actually used
	scorpion_CORPSE,
	golden_scorpion_CORPSE,

	rebel_ally_CORPSE = 4,
};

enum ground_material {
	sand_mat,
	rock_mat,
	metal_mat,
	slime_rock_mat,
	slime_sand_mat,
};

enum player_material {
	org,
	pla,
	met,
	sho,
	no_footstep
};

enum sound_ID {
	snd_none_ID,

	snd_foot_1,
	snd_foot_2,
	snd_foot_3,
	snd_foot_4,

	snd_wall_break_ID,

	snd_player_specific_1_ID,

	snd_player_loop_1_ID,

	//end of sounds that will be used, not just in buffers

	snd_music_ID,

	snd_lose_strong_spirit_ID,
	snd_gain_strong_spirit_ID,

	snd_portal_open_ID,
	snd_portal_loop_ID,
	snd_portal_close_ID,

	snd_throne_2_hurt_ID,
	snd_throne_2_die_ID,

	snd_shoot_1_ID,
	snd_horror_portal_ID, snd_horror_portal_pan_ID,

	snd_big_ball_fire_ID,
	snd_big_ball_explode_ID,

	snd_throne_2_appear_ID,
	snd_throne_2_laser_ID, snd_throne_2_laser_fire_ID,
	snd_throne_2_half_hp_ID,
	snd_explo_guardian_fire_ID,

	snd_throne_2_dead_start_ID,
	snd_throne_2_dead_end_ID,
	snd_throne_2_explode_ID,

	snd_bandit_hurt_ID,
	snd_bandit_die_ID,

	snd_idpd_freak_hurt_ID,
	snd_idpd_freak_die_ID,
	snd_idpd_freak_enter_ID,
	snd_idpd_freak_revive_ID,
	snd_idpd_freak_revive_area_ID,

	snd_grunt_fire_ID,

	snd_rad_pickup_ID,

	snd_horror_beam_start_ID,
	snd_horror_beam_hold_ID,

	snd_hit_wall_ID,
	snd_hit_rock_ID,
	snd_hit_plant_ID,
	snd_hit_metal_ID,
	snd_hit_flesh_ID,

	snd_sewer_pipe_break_ID,
	snd_toxic_barrel_gas_ID,
	snd_car_explosion_ID,
	snd_crystal_prop_break_ID,
	snd_coccon_break_ID,
	snd_icicle_break_ID,
	snd_hydrant_break_ID,
	snd_street_light_break_ID,
	snd_vending_machine_break_ID,
	snd_snowman_break_ID,
	snd_server_break_ID,
	snd_tube_break_ID,
	snd_mutant_tube_break_ID,
	snd_generator_break_ID,
	snd_pillar_break_ID,

	snd_wall_break_rock_ID,
	snd_wall_break_brick_ID,
	snd_wall_break_scrap_ID,
	snd_wall_break_crystal_ID,
	snd_wall_break_labs_ID,

	snd_IDPD_explosion_ID,
	snd_plasma_hit_ID,


	snd_player_hurt_ID,

	snd_horror_hurt_ID,
	snd_fish_hurt_ID,
	snd_crystal_hurt_ID,
	snd_eyes_hurt_ID,
	snd_melting_hurt_ID,
	snd_plant_hurt_ID,
	snd_YV_hurt_ID,
	snd_steroids_hurt_ID,
	snd_robot_hurt_ID,
	snd_chicken_hurt_ID,
	snd_rebel_hurt_ID,
	snd_rogue_hurt_ID,
	snd_frog_hurt_ID,
	snd_skeleton_hurt_ID,
	

	snd_fish_roll_ID,

	snd_crystal_shield_ID,

	snd_eyes_TK_ID,

	snd_corpse_explode_ID,
	snd_corpse_explode_TB_ID,


	snd_pickup_disappear_ID,
	snd_ammo_pickup_ID,
	snd_hp_pickup_ID,
	snd_lust_proc_ID,

	snd_empty_ID,

	snd_melee_flip_ID,
	snd_plasma_reload_ID,
	snd_plasma_reload_upgrade_ID,
	
	snd_ultra_shovel_ID,
	snd_plasma_huge_ID, snd_plasma_huge_upgrade_ID,
	snd_plasma_split_ID, snd_plasma_split_upgrade_ID,
	snd_hammer_swap_ID,
	snd_energy_swap_ID,
	snd_explosion_ID,
	snd_explosion_s_ID,
	snd_nade_hit_wall_ID,
	snd_IDPD_nade_load_ID,
	snd_IDPD_nade_almost_ID,

	snd_idpd_spawn_ID,
	snd_idpd_spawn_elite_ID,


	snd_foot_metmetal_1_ID,
	snd_foot_metmetal_2_ID,
	snd_foot_metmetal_3_ID,
	snd_foot_metmetal_4_ID,
	snd_foot_metmetal_5_ID,
	snd_foot_metmetal_6_ID,

	snd_foot_metrock_1_ID,
	snd_foot_metrock_2_ID,
	snd_foot_metrock_3_ID,
	snd_foot_metrock_4_ID,
	snd_foot_metrock_5_ID,
	snd_foot_metrock_6_ID,

	snd_foot_metsand_1_ID,
	snd_foot_metsand_2_ID,
	snd_foot_metsand_3_ID,
	snd_foot_metsand_4_ID,
	snd_foot_metsand_5_ID,
	snd_foot_metsand_6_ID,

	snd_foot_orgmetal_1_ID,
	snd_foot_orgmetal_2_ID,
	snd_foot_orgmetal_3_ID,
	snd_foot_orgmetal_4_ID,
	snd_foot_orgmetal_5_ID,
	snd_foot_orgmetal_6_ID,

	snd_foot_orgrock_1_ID,
	snd_foot_orgrock_2_ID,
	snd_foot_orgrock_3_ID,
	snd_foot_orgrock_4_ID,
	snd_foot_orgrock_5_ID,
	snd_foot_orgrock_6_ID,

	snd_foot_orgsand_1_ID,
	snd_foot_orgsand_2_ID,
	snd_foot_orgsand_3_ID,
	snd_foot_orgsand_4_ID,
	snd_foot_orgsand_5_ID,
	snd_foot_orgsand_6_ID,

	snd_foot_plametal_1_ID,
	snd_foot_plametal_2_ID,
	snd_foot_plametal_3_ID,
	snd_foot_plametal_4_ID,
	snd_foot_plametal_5_ID,
	snd_foot_plametal_6_ID,

	snd_foot_plarock_1_ID,
	snd_foot_plarock_2_ID,
	snd_foot_plarock_3_ID,
	snd_foot_plarock_4_ID,
	snd_foot_plarock_5_ID,
	snd_foot_plarock_6_ID,

	snd_foot_plasand_1_ID,
	snd_foot_plasand_2_ID,
	snd_foot_plasand_3_ID,
	snd_foot_plasand_4_ID,
	snd_foot_plasand_5_ID,
	snd_foot_plasand_6_ID,

	snd_foot_shometal_1_ID,
	snd_foot_shometal_2_ID,
	snd_foot_shometal_3_ID,
	snd_foot_shometal_4_ID,
	snd_foot_shometal_5_ID,
	snd_foot_shometal_6_ID,

	snd_foot_shorock_1_ID,
	snd_foot_shorock_2_ID,
	snd_foot_shorock_3_ID,
	snd_foot_shorock_4_ID,
	snd_foot_shorock_5_ID,
	snd_foot_shorock_6_ID,

	snd_foot_shosand_1_ID,
	snd_foot_shosand_2_ID,
	snd_foot_shosand_3_ID,
	snd_foot_shosand_4_ID,
	snd_foot_shosand_5_ID,
	snd_foot_shosand_6_ID,

	snd_foot_slime_1_ID,
	snd_foot_slime_2_ID,
	snd_foot_slime_3_ID,
	snd_foot_slime_4_ID,
	snd_foot_slime_5_ID,
	snd_foot_slime_6_ID,
};

enum gridType { out_of_bounds, wall, exlpo_tile, boarder , floor_tile, void_tile, T2_boarder }; //, secret_wall, secret_explotile, vault_wall, vault_explotile};
enum subWallType{upLeft, up, upRight, right, downRight, down, downLeft, left, middle };	//which sprite to use for a wall

enum character{ fish, crystal, eyes, melting, plant, YV, steroids, robot, chicken, rebel, horror, rogue, frog, skeleton };

enum weapon_types {		//cutoffs for weapon types
	melee_weps = 11,
	energy_weps = 41,
};

enum what_team {
	no_team = 0,
	player_team = 1,
	enemy_team = 2,
	idpd_team = 3,
};

//for circular hitboxes, radius
enum hitboxes {
	no_hitbox = 0,
	player_hitbox = 4,	//4 default
	bandit_hitbox = 8, enemy_bullet_hitbox = 3, plasma_hitbox = 5, guardian_bullet_hitbox = 4,
	plasma_impact_hitbox = 32,
	idpd_explosion_hitbox = 48,
	explosion_hitbox = 24,
	small_explosion_hitbox = 12,
	meat_explosion_hitbox = 12,
	idpd_nade_hitbox = 2,
	idpd_freak_hitbox = 7,
	wall_hitbox = 8,
	portal_hitbox = 16,
	portal_clear_hitbox = 32,
	ammo_hitbox = 4,

	small_prop_hitbox = 7,
	medium_prop_hitbox = 12,
	crystal_shield_hitbox = 24,
	plant_tangle_hitbox = 24,
};
 
struct gameObject{
	sf::Vector2f position;
	sf::Vector2f speed;

	float direction = 0.0f;
	float speeddir = 0.0f;	//speed based on direction
	float friction = 0.0f;

	float rotation = 0.0f;
	float gun_angle = 0.0f;
	float walk_direction = 0.0f;
	float scale = 0.0f;
	float growspeed = 0.0f;

	objectID my_id = nothing;

	int image_index = 0;	//doesnt necicarily mean what sprite should be used so for explosions 0 1 2 are the first frame and 3 4 are the second frame of animation
	int next_hurt = 0;
	int next_melee = 0;
	int rad_drop = 0;
	int my_hp = 0;
	int max_hp = 0;
	int team = 0;
	int size = 0;

	int damage = 0;

	int corpse_id = 0;

	enum hitboxes my_hitbox;

	enum sound_ID hurt_ID;
	enum sound_ID die_ID;

	int alarm1 = 0;
	int alarm2 = 0;
	int alarm3 = 0;

	int walk_frames = 0;

	bool facing_right = true;

	void reset_variables() {
		position = {0,0};
		speed = {0,0};

		direction = 0.0f;
		speeddir = 0.0f;	//speed based on direction
		friction = 0.0f;

		rotation = 0.0f;
		gun_angle = 0.0f;
		walk_direction = 0.0f;
		scale = 0.0f;
		growspeed = 0.0f;

		my_id = nothing;
		image_index = 0;	//doesnt necicarily mean what sprite should be used so for explosions 0 1 2 are the first frame and 3 4 are the second frame of animation
		next_hurt = 0;
		rad_drop = 0;
		my_hp = 0;
		team = 0;		//0 = none 1 = player 2 = enemy 3 = idpd

		alarm1 = 0;
		alarm2 = 0;
		alarm3 = 0;

		walk_frames = 0;

		facing_right = true;

	}
};

struct gridTile {
	std::vector<int> object_indexes;
	gridType my_grid_type = out_of_bounds;
	//bool has_line_of_sight = false;
};

struct wallTile {
	sf::Texture texture;
	sf::VertexArray vertex_array;
	int array_index = 0;
};

struct coordPair {
	float x;
	float y;
};

struct level_generator {
	int x;
	int y;
	int spdx;
	int spdy;
	bool active = false;
	bool Btile = false;
}; 

struct sound_sound_buffer {
	sf::Sound sound;
	float pitch_variance;
};

struct portal_spiral {
	sf::Vector2f position = {0, 0};
	float grow = 0.0f;
	float langle = 0.0f;
	float lanim = 0.0f;
	int lsound = 0;

	float image_scale = 0.0f;
	float image_angle = 0.0f;

	bool active = false;
};

struct debug_timer {
	std::chrono::steady_clock::time_point start;

	long long time_elapsed;

	void inline timing_us_start() {
		start = std::chrono::high_resolution_clock::now();
	}

	void inline timing_us_end() {

		std::chrono::nanoseconds elapsed = std::chrono::high_resolution_clock::now() - start;

		time_elapsed = std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
	}
};