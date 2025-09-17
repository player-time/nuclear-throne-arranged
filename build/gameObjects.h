#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <SFML/System/Vector2.hpp>

enum objectID {
	nothing,
	bullet1, bullet1_destroy,
	bullet2, bullet2_destroy,

	idpd_bullet, idpd_bullet_destroy,

	idpd_explosion,
	idpd_nade, idpd_nade_remove,
	idpd_portal_charge,

	player,

	throne_2,

	popup_text,

	rad, rad_destroy,

	ammo_pack, health_pack,
	ammo_pack_destroy, heal_FX,

	bandit, bandit_corpse, 
	scorpion, scorpion_corpse,
	gold_scorpion, gold_scorpion_corpse,

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

enum sound {
	snd_music_ID,

	snd_shoot_1_ID,
	snd_horror_portal_ID, snd_horror_portal_pan_ID,

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
	snd_wall_break_rock_ID,

	snd_IDPD_explosion_ID,
	snd_plasma_hit_ID,

	snd_player_hurt_ID,
	snd_horror_hurt_ID,

	snd_pickup_disappear_ID,
	snd_ammo_pickup_ID,
	snd_hp_pickup_ID,

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
	snd_nade_hit_wall_ID,
	snd_IDPD_nade_load_ID,
	snd_IDPD_nade_almost_ID,
};

enum gridType { out_of_bounds, wall, exlpo_tile, boarder , floor_tile }; //, secret_wall, secret_explotile, vault_wall, vault_explotile};
enum subWallType{upLeft, up, upRight, right, downRight, down, downLeft, left, middle };	//which sprite to use for a wall

enum character{ fish, crystal, eyes, melting, plant, YV, steroids, robot, chicken, rebel, horror, rogue, frog, skeleton };

enum weapon_types {		//cutoffs for weapon types
	melee_weps = 11,
	energy_weps = 41,
};

//for circular hitboxes
enum hitboxes {
	player_hitbox = 4,
	bandit_hitbox = 8, enemy_bullet_hitbox = 3, plasma_hitbox = 5,
	idpd_freak_hitbox = 7,
	wall_hitbox = 8,
	portal_hitbox = 16,
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
	int team = 0;		//0 = none 1 = player 2 = enemy 3 = idpd
	int size = 0;

	enum hitboxes my_hitbox;

	enum sound hurt_ID;
	enum sound die_ID;

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
	sf::Music music;
	sf::Sound sound;
	sf::SoundBuffer sound_buffer;
	float pitch_variance;
};