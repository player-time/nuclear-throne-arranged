#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <SFML/System/Vector2.hpp>

#include "gameObjects.cpp"

#include <chrono>

#include "C:\Users\svt16\Desktop\Nuclear Throne Arranged\cmake-sfml-project\src\my_vector.cpp"

enum objectID {
	nothing,
	bullet1, bullet1_destroy,
	bullet2, bullet2_destroy,
	guardian_bullet, guardian_bullet_destroy,
	large_guardian_bullet, large_guardian_bullet_destroy,
	T2_bullet,
	throne_beam_charge_particle,

	frog_bullet,

	revenge_bullet, revenge_bullet_spawner,

	idpd_bullet, idpd_bullet_destroy,

	toxic_gas,
	toxic_gas_destroy,

	devastator_bullet,

	the_wind,

	flame,

	static_effect,

	shell_effect,


	scorch,
	idpd_explosion,
	idpd_nade, idpd_nade_remove,
	idpd_portal_charge,
	idpd_spawn,

	nade,
	explosive_burst,

	rogue_strike,

	explosion,


	player_laser,
	player_laser_burst,

	player_lightning,
	player_lightning_spawn,
	player_lightning_orb,

	player_bolt_burst,

	player_flame,

	player,
	player_corpse,

	rebel_ally,

	crystal_shield,

	melt_splat,

	meat_explosion,

	plant_tangle_seed,
	plant_tangle,

	chicken_head,

	throne_2, throne_2_death,

	popup_text,

	feather_raven, 
	feather, 
	money,

	stress_sweat,

	weapon_drop,
	thrown_wep,


	chest,


	rad, rad_destroy,

	ammo_pack, health_pack,
	ammo_pack_destroy, heal_FX,
	lust_FX,
	laser_brain_FX,

	bandit, enemy_corpse, 
	big_enemy,

	idpd_freak, idpd_freak_corpse, idpd_freak_revive,

	player_bullet, player_bullet_destroy,
	player_bouncer_bullet, player_bouncer_bullet_destroy,
	player_bullet_burst,

	player_shell_burst,

	player_bolt,
	player_bolt_stick,
	bolt_trail,

	player_shell, player_shell_destroy,
	player_shell_hyper,

	rogue_bullet,

	plasma_huge, plasma_big, 
	plasma, plasma_impact,
	plasma_particle,
	plasma_hit,

	melee_slash,
	melee_shank,

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
	rad_canister_prop,
};

enum enemy_corpses {
	//used for offsets when drawing corpse
	bandit_CORPSE,
	idpd_freak_CORPSE,	//filler, not actually used
	scorpion_CORPSE,
	rebel_ally_CORPSE = 3,
	golden_scorpion_CORPSE,

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

enum campfire_character_state_ {
	idle, select__, selected, deselect
};

enum mutation_icon {
	none_mut_icon,
	rhino_skin_icon,
	extra_feet_icon,
	plutonium_hunger_icon,
	rabbit_paw_icon,
	throne_butt_icon,
	lucky_shot_icon,
	bloodlust_icon,
	gamma_guts_icon,
	second_stomach_icon,
	back_muscle_icon,
	scarier_face_icon,
	euphoria_icon,
	long_arms_icon,
	boiling_veins_icon,
	laser_brain_icon,
	bolt_marrow_icon,
	stress_icon,
	trigger_fingers_icon,
	hammerhead_icon,
	strong_spirit_icon,
	//ultras
	fish_ultra_A_icon,
	fish_ultra_B_icon,

	crystal_ultra_A_icon,
	crystal_ultra_B_icon,

	eyes_ultra_A_icon,
	eyes_ultra_B_icon,

	melting_ultra_A_icon,
	melting_ultra_B_icon,

	plant_ultra_A_icon,
	plant_ultra_B_icon,

	YV_ultra_A_icon,
	YV_ultra_B_icon,

	steroids_ultra_A_icon,
	steroids_ultra_B_icon,

	robot_ultra_A_icon,
	robot_ultra_B_icon,

	chicken_ultra_A_icon,
	chicken_ultra_B_icon,

	rebel_ultra_A_icon,
	rebel_ultra_B_icon,

	horror_ultra_A_icon,
	horror_ultra_B_icon,
	horror_ultra_C_icon,

	rogue_ultra_A_icon,
	rogue_ultra_B_icon,

	frog_ultra_A_icon,
	frog_ultra_B_icon,

	skeleton_ultra_A_icon,
	skeleton_ultra_B_icon,

	cuz_ultra_A_icon,
	cuz_ultra_B_icon
};

enum sound_ID {
	snd_none_ID,
	snd_none_2_ID,

	snd_wep_pickup_ID,

	snd_pistol_swap_ID,
	snd_machine_gun_swap_ID,
	snd_hammer_swap_ID,
	snd_shotgun_swap_ID,
	snd_bow_swap_ID,
	snd_guitar_swap_ID,
	snd_explosive_swap_ID,
	snd_energy_swap_ID,
	snd_motorized_swap_ID,
	snd_sword_swap_ID,
	snd_flame_swap_ID,
	snd_dragon_swap_ID,
	snd_gold_swap_ID,

	snd_player_shoot_A_ID,
	snd_player_shoot_B_ID,

	snd_devastator_explo_ID,
	snd_lightning_orb_explo_ID,

	snd_revenge_bullet,

	snd_laser_cannon_ID,
	snd_laser_cannon_up_ID,

	snd_machinegun_ID,
	snd_gold_machinegun_ID,
	snd_heavy_machinegun_ID,
	snd_rogue_rifle_ID,
	snd_hyper_rifle_ID,

	snd_lightning_reload_ID,

	snd_lightning_cannon_loop_ID,

	snd_bullet_bounce_ID,

	snd_crossbow_reload_ID,
	snd_shotgun_reload_ID,

	snd_super_splinter_ID,

	snd_soda_hit_ID,
	snd_soda_hit_2_ID,

	snd_toxic_bolt_gas_ID,

	snd_shotgun_hit_wall_ID,

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

	snd_flak_explode_ID,
	snd_super_flak_explode_ID,

	snd_slugger_ID,

	snd_wave_gun_ID,

	snd_explosion_ID,
	snd_explosion_s_ID,
	snd_explosion_l_ID,
	snd_nade_hit_wall_ID,
	snd_IDPD_nade_load_ID,
	snd_IDPD_nade_almost_ID,

	snd_nade_stick_ID,

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
	snd_throne_2_taunt_ID,

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

	snd_wall_break_rock_ID,
	snd_wall_break_brick_ID,
	snd_wall_break_scrap_ID,
	snd_wall_break_crystal_ID,
	snd_wall_break_labs_ID,

	snd_IDPD_explosion_ID,
	snd_plasma_hit_ID,

	snd_sewer_drip_ID,


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
	snd_YC_hurt_ID,

	//death snds
	snd_fish_die_ID,
	snd_crystal_die_ID,
	snd_eyes_die_ID,
	snd_melting_die_ID,
	snd_plant_die_ID,
	snd_YV_die_ID,
	snd_steroids_die_ID,
	snd_robot_die_ID,
	snd_chicken_die_ID,
	snd_rebel_die_ID,
	snd_horror_die_ID,
	snd_rogue_die_ID,
	snd_frog_die_ID,
	snd_skeleton_die_ID,
	snd_YC_die_ID,

	

	snd_fish_roll_ID,
	snd_fish_roll_TB_ID,
	snd_gun_warrant_end_ID,

	snd_crystal_shield_ID,
	snd_crystal_teleport_ID,
	snd_crystal_deflect_ID,

	snd_eyes_TK_ID,

	snd_corpse_explode_ID,
	snd_corpse_explode_TB_ID,

	snd_plant_power_ID,
	snd_plant_tangle_ID,
	snd_plant_tangle_TB_ID,
	snd_plant_fire_seed_ID,
	snd_plant_fire_seed_TB_ID,
	snd_plant_fire_seed_trapper_ID,
	snd_plant_fire_seed_trapper_TB_ID,
	snd_plant_TB_kill_ID,

	snd_YV_pop_ID,
	snd_YV_brap_ID,

	snd_robot_eat_ID,
	snd_robot_eat_fast_ID,
	snd_robot_eat_TB_ID,

	snd_chicken_headless_loop_ID,
	snd_chicken_lose_head_ID,
	snd_chicken_regen_head_ID,

	snd_chicken_throw_ID,
	snd_chicken_B_ID,

	snd_stalker_ID,
	snd_horror_beam_hold_TB_ID,
	snd_spawn_ally_ID,
	snd_ally_spawn_ID,
	snd_ally_spawn_TB_ID,

	snd_ally_hurt_ID,
	snd_ally_die_ID,

	snd_horror_empty_ID,

	snd_rogue_strike_ID,
	snd_rogue_strike_TB_ID,
	snd_rogue_strike_empty_ID,
	snd_rogue_aim_ID,

	snd_rogue_canister_ID,

	snd_skeleton_gamble_TB_ID,
	snd_skeleton_gamble_ID,

	snd_frog_start_ID,
	snd_frog_start_TB_ID,
	snd_frog_end_ID,
	snd_frog_end_TB_ID,
	snd_frog_gas_release_ID,
	snd_frog_gas_release_TB_ID,

	snd_bolt_stick_ID,
	snd_melee_wall_ID,
	snd_burn_ID,

	snd_pickup_disappear_ID,
	snd_ammo_pickup_ID,
	snd_hp_pickup_ID,
	snd_hp_pickup_big_ID,
	snd_lust_proc_ID,
	snd_lucky_shot_proc_ID,
	snd_hammerhead_proc_ID,
	snd_hammerhead_end_ID,

	snd_gamma_guts_proc_ID,
	snd_gamma_guts_kill_ID,

	//chest
	snd_ammo_chest_ID,
	snd_weapon_chest_ID,
	snd_hp_chest_ID,
	snd_hp_chest_big_ID,
	snd_rad_canister_break_ID,

	snd_empty_ID,

	snd_melee_flip_ID,
	snd_plasma_reload_ID,
	snd_plasma_reload_upgrade_ID,
	
	snd_ultra_shovel_ID,
	snd_plasma_huge_ID, snd_plasma_huge_upgrade_ID,
	snd_plasma_split_ID, snd_plasma_split_upgrade_ID,


	snd_idpd_spawn_ID,
	snd_idpd_spawn_elite_ID,

	snd_meat_explo_ID,
	
	//weapon fire snds
	snd_sword_ID,
	snd_black_sword_ID,
	snd_wrench_ID,
	snd_shovel_ID,
	snd_sledge_ID,

	snd_guitar_ID,
	snd_lightning_hammer_ID,
	snd_energy_sword_ID,
	snd_energy_sword_up_ID,
	snd_energy_hammer_ID,
	snd_energy_hammer_up_ID,
	snd_energy_screw_ID,
	snd_energy_screw_up_ID,

	snd_plasma_cannon_ID,
	snd_plasma_cannon_up_ID,
	snd_plasma_gun_ID,
	snd_plasma_gun_up_ID,
	snd_plasma_rifle_ID,
	snd_plasma_rifle_up_ID,
	snd_plasma_mini_ID,
	snd_plasma_mini_up_ID,
	snd_gold_plasma_gun_ID,
	snd_gold_plasma_gun_up_ID,
	snd_devastator_ID,
	snd_devastator_up_ID,

	snd_laser_ID,
	snd_laser_up_ID,
	snd_golden_laser_ID,
	snd_golden_laser_up_ID,
	snd_ultra_laser_ID,
	snd_ultra_laser_up_ID,

	snd_laser_cannon_charge_ID,

	snd_lightning_pistol_ID,
	snd_lightning_pistol_up_ID,
	snd_lightning_rifle_ID,
	snd_lightning_rifle_up_ID,
	snd_lightning_shotgun_ID,
	snd_lightning_shotgun_up_ID,
	snd_lightning_cannon_ID,
	snd_lightning_cannon_up_ID,

	snd_revolver_ID,
	snd_gold_revolver_ID,
	snd_rusty_revolver_ID,
	snd_triple_machinegun_ID,
	snd_minigun_ID,
	snd_smart_gun_ID,
	snd_quadruple_machinegun_ID,
	snd_double_minigun_ID,
	snd_heavy_revolver_ID,
	snd_bouncer_SMG_ID,
	snd_bouncer_shotgun_ID,
	snd_ultra_revolver_ID,
	snd_gold_frog_pistol_ID,
	snd_incinerator_ID,

	snd_crossbow_ID,
	snd_super_crossbow_ID,
	snd_gold_crossbow_ID,
	snd_heavy_crossbow_ID,
	snd_splinter_ID,
	snd_splinter_pistol_ID,
	
	snd_gold_splinter_ID,
	snd_ultra_crossbow_ID, 
	snd_seeker_pistol_ID,
	snd_seeker_shotgun_ID,


	snd_shotgun_ID,
	snd_double_shotgun_ID,
	snd_sawed_off_shotgun_ID,
	snd_eraser_ID,
	snd_golden_shotgun_ID,
	snd_flame_shotgun_ID,
	snd_double_flame_shotgun_ID,
	snd_super_slugger_ID,
	snd_gold_slugger_ID,
	snd_heavy_slugger_ID,
	snd_hyper_slugger_ID,
	snd_flak_cannon_ID,
	snd_super_flak_cannon_ID,
	snd_ultra_shotgun_ID,


	//explosives
	snd_grenade_launcher_ID,
    snd_gold_grenade_launcher_ID,
    snd_heavy_grenade_launcher_ID,
    snd_toxic_launcher_ID,
    snd_grenade_shotgun_ID,
    snd_grenade_rifle_ID,
    snd_cluster_launcher_ID,
    snd_cluster_open_ID,

    snd_bazooka_ID,
    snd_rocket_fly_ID,
    snd_super_bazooka_ID,
    snd_gold_bazooka_ID,
    snd_gold_rocket_fly_ID,

    snd_nuke_launcher_ID,
    snd_nuke_explode_ID,
    snd_gold_nuke_launcher_ID,

    snd_blood_launcher_ID,
    snd_blood_launcher_explode_ID,

    snd_blood_cannon_ID,
    snd_blood_cannon_end_ID,
    snd_blood_cannon_loop_ID,

    snd_flamethrower_ID,
    snd_flamethrower_end_ID,
    snd_flamethrower_loop_ID,

    snd_dragon_ID,
    snd_dragon_end_ID,
    snd_dragon_loop_ID,

    snd_flare_gun_ID,
    snd_flare_explode_ID,

    snd_flame_cannon_ID,
    snd_flame_cannon_end_ID,
    snd_flame_cannon_loop_ID,

    snd_hyper_launcher_ID,

    snd_ultra_grenade_launcher_ID,
    snd_ultra_grenade_launcher_suck_ID,

    snd_jackhammer_ID,

	snd_explosive_reload_ID,

	snd_not_enough_rads_ID,

	snd_level_up_ID,
	snd_level_ultra_ID,

	//some looping sounds
	snd_eyes_loop_ID,
	snd_eyes_TB_loop_ID,
	snd_frog_loop_ID,
	snd_frog_TB_loop_ID,
	snd_portal_strike_loop_ID,
	snd_snow_bot_slide_loop_ID,
	snd_salamander_fire_loop_ID,
	snd_logo_loop_ID,
	snd_nothing_beam_loop_ID,
	snd_ball_mom_loop_ID,

	snd_frog_ultra_B_loop_ID,
	snd_throne_1_idle_loop_ID,
	snd_fish_TB_loop_ID,

	//mutation get sfx
	snd_get_plutonium_hunger_ID,
	snd_get_long_arms_ID,
	snd_get_trigger_fingers_ID,
	snd_get_laser_brain_ID,
	snd_get_second_stomach_ID,
	snd_get_stress_ID,
	snd_get_bloodlust_ID,
	snd_get_lucky_shot_ID,
	snd_get_hammerhead_ID,
	snd_get_boiling_veins_ID,
	snd_get_gamma_guts_ID,
	snd_get_rhino_skin_ID,
	snd_get_extra_feet_ID,
	snd_get_euphoria_ID,
	snd_get_rabbit_paw_ID,
	snd_get_bolt_marrow_ID,
	snd_get_spirit_ID,
	snd_get_scarier_face_ID,
	snd_get_throne_butt_ID,
	snd_get_back_muscle_ID,

	snd_fish_ultra_A_ID,
	snd_crystal_ultra_A_ID,
	snd_eyes_ultra_A_ID,
	snd_melting_ultra_A_ID,
	snd_plant_ultra_A_ID,
	snd_YV_ultra_A_ID,
	snd_steroids_ultra_A_ID,
	snd_robot_ultra_A_ID,
	snd_chicken_ultra_A_ID,
	snd_rebel_ultra_A_ID,
	snd_horror_ultra_A_ID,
	snd_rogue_ultra_A_ID,
	snd_frog_ultra_A_ID,
	snd_skeleton_ultra_A_ID,
	snd_YC_ultra_A_ID,

	snd_fish_ultra_B_ID,
	snd_crystal_ultra_B_ID,
	snd_eyes_ultra_B_ID,
	snd_melting_ultra_B_ID,
	snd_plant_ultra_B_ID,
	snd_YV_ultra_B_ID,
	snd_steroids_ultra_B_ID,
	snd_robot_ultra_B_ID,
	snd_chicken_ultra_B_ID,
	snd_rebel_ultra_B_ID,
	snd_horror_ultra_B_ID,
	snd_rogue_ultra_B_ID,
	snd_frog_ultra_B_ID,
	snd_skeleton_ultra_B_ID,
	snd_YC_ultra_B_ID,

	snd_horror_ultra_C_ID,

	//menu campfire
	snd_fish_select_ID,
	snd_crystal_select_ID,
	snd_eyes_select_ID,
	snd_melting_select_ID,
	snd_plant_select_ID,
	snd_YV_select_ID,
	snd_steroids_select_ID,
	snd_robot_select_ID,
	snd_chicken_select_ID,
	snd_rebel_select_ID,
	snd_horror_select_ID,
	snd_rogue_select_ID,
	snd_frog_select_ID,
	snd_skeleton_select_ID,
	snd_YC_select_ID,

	snd_fish_confirm_ID,
	snd_crystal_confirm_ID,
	snd_eyes_confirm_ID,
	snd_melting_confirm_ID,
	snd_plant_confirm_ID,
	snd_YV_confirm_ID,
	snd_steroids_confirm_ID,
	snd_robot_confirm_ID,
	snd_chicken_confirm_ID,
	snd_rebel_confirm_ID,
	snd_horror_confirm_ID,
	snd_rogue_confirm_ID,
	snd_frog_confirm_ID,
	snd_skeleton_confirm_ID,
	snd_YC_confirm_ID,



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

enum gridType : uint8_t { out_of_bounds, wall, exlpo_tile, boarder , floor_tile, void_tile, T2_boarder }; //, secret_wall, secret_explotile, vault_wall, vault_explotile};
enum subWallType{upLeft, up, upRight, right, downRight, down, downLeft, left, middle };	//which sprite to use for a wall

enum character{ fish, crystal, eyes, melting, plant, YV, steroids, robot, chicken, rebel, horror, rogue, frog, skeleton, YC, none_character, go_button };

enum weapon_types {		//cutoffs for weapon types
	melee_weps = 8,
	energy_weps = 29,
	bullet_weps = 52,
	bolt_weps = 66,
	shell_weps = 86,
	explosive_weps = 200,
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
	bandit_hitbox = 7, enemy_bullet_hitbox = 3, plasma_hitbox = 5, guardian_bullet_hitbox = 4,
	player_bullet_hitbox = 5,
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

	gamma_guts_hitbox = 16,

	hyper_slugger_hitbox = 1,

	small_prop_hitbox = 7,
	medium_prop_hitbox = 12,
	crystal_shield_hitbox = 24,
	plant_tangle_hitbox = 24,

	weapon_hitbox = 7,

	devastator_hitbox = 8,

	lightning_hitbox = 5,

	chest_hitbox = 9,

	revenge_bullet_hitbox = -2,

};

enum gamestate {
	gs_character_selection,
	gs_in_game,
};
 
struct gameObject{
	sf::Vector2f position = {0, 0};
	sf::Vector2f position_PREV = {0, 0};
	sf::Vector2f speed = { 0, 0 };

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

	int melee_damage = 0;

	int corpse_id = 0;

	enum hitboxes my_hitbox = no_hitbox;

	enum sound_ID hurt_ID = snd_bandit_hurt_ID;
	enum sound_ID die_ID = snd_bandit_die_ID;

	int alarm1 = 0;
	int alarm2 = 0;
	int alarm3 = 0;

	int walk_frames = 0;

	bool facing_right = true;

	bool dead = false;

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

		dead = false;

	}
};

struct gridTile {
	std::vector<int> object_indexes;
	uint8_t my_grid_type = out_of_bounds;
	//bool has_line_of_sight = false;
};

struct wallTile {
	sf::Texture texture;
	sf::VertexArray vertex_array;
	int array_index = 0;
};

struct coordPair {
	float x = 0.0f;
	float y = 0.0f;
};

struct level_generator {
	int x = 0;
	int y = 0;
	int spdx = 0;
	int spdy = 0;
	bool active = false;
	bool Btile = false;
}; 

struct sound_sound_buffer {
	float pitch_variance = 0.0f;
	float volume = 100.0f;
	float attenuation = 0.0f;
};

struct portal_spiral {
	sf::Vector2f position = {0, 0};
	float grow = 0.0f;
	//float langle = 0.0f;
	//float lanim = 0.0f;
	//int lsound = 0;

	float image_scale = 0.0f;
	float image_angle = 0.0f;

	bool active = false;
	bool circle = false;
};

struct flashing_gray_text {
	mutation_icon mut_text;
	bool active = false;
	int active_frames = 0;
};

struct colored_text {
	std::vector<sf::Text> text_string;

	void set_string(std::string str, sf::Font &font, sf::Color start_col = sf::Color::White) {
		text_string.clear();

		std::string string_block;	//block of characters that have the same color and y pos

		for (int i = 0; i < str.size(); i++) {
			if (str[i] == *"*") {
				str[i] = *"0";
			}
		}

		str.push_back(*"*");

		sf::Color next_col = start_col;
		float y_off = 0;

		for (int i = 0; i < str.length(); i++) {
			if (str[i] == *"*") {
				sf::Text add_me;
				add_me.setCharacterSize(8);
				add_me.setFont(font);
				add_me.setString(string_block);
				add_me.setColor(next_col);
				text_string.push_back(add_me);

				sf::Text add_me_nl;
				add_me_nl.setString("~");
				text_string.push_back(add_me_nl);//newline
				break;
			}
			if (str[i] != *"@" && str[i] != *"#") {
				string_block.push_back(str[i]);
			}
			else {

				if (str[i] == *"#") {
					sf::Text add_me;
					add_me.setCharacterSize(8);
					add_me.setFont(font);
					add_me.setString(string_block);
					add_me.setColor(next_col);
					text_string.push_back(add_me);
					string_block.clear();
					sf::Text add_me_nl;
					add_me_nl.setString("~");
					text_string.push_back(add_me_nl);//newline
				}
				else {
					sf::Text add_me;
					add_me.setCharacterSize(8);
					add_me.setFont(font);
					add_me.setString(string_block);
					add_me.setColor(next_col);
					text_string.push_back(add_me);
					string_block.clear();

					if (str[i + 1] == *"r") {
						next_col = sf::Color::Red;
					}
					else if (str[i + 1] == *"b") {
						next_col = sf::Color::Blue;
					}
					else if (str[i + 1] == *"w") {
						next_col = sf::Color::White;
					}
					else if (str[i + 1] == *"g") {
						next_col = sf::Color::Green;
					}
					else if (str[i + 1] == *"q") {
						next_col = sf::Color{ 86, 34, 110, 255 };//purple
					}
					else if (str[i + 1] == *"s") {
						next_col = sf::Color{ 128, 128, 128, 255 };//gray
					}
					else if (str[i + 1] == *"p") {
						next_col = sf::Color{ 86, 34, 110, 255 };//purple
					}
					else if (str[i + 1] == *"y") {
						next_col = sf::Color{ 250, 171, 0, 255 };//yellow
					}
					i++;
				}
			}
		}
	}

	void set_position(sf::Vector2f pos, bool centered = true) {
		float letter_spacing = 8;
		float x_off = 0;
		float y_off = 0;
		int idx_go_back = 0;
		for (int i = 0; i < text_string.size(); i++) {
			if (text_string[i].getString() != "~") {
				text_string[i].setPosition(pos.x + x_off, pos.y + y_off);
				x_off += text_string[i].getString().getSize() * 8;
			}
			else if (centered) {
				//center text
				for (int j = idx_go_back; j < i; j++) {
					if (text_string[j].getString() != "~") {
						text_string[j].setPosition(160 - x_off / 2, pos.y + y_off);
						x_off -= text_string[j].getString().getSize() * 16;
					}
				}
				idx_go_back = i;
				y_off += 8;
				x_off = 0;
			}
		}
	}

	void set_character_col(int start_char, int end_char) {

	}
};

struct replay_input {
	std::uint16_t keyboard_n_mouse_input = 0x0000;
	std::uint16_t mouse_x = 0x0000;
	std::uint8_t mouse_y = 0x00;
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

