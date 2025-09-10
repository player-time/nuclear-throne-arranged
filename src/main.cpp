//NUCLEAR THRONE ARRANGED

//TODO !!!
//1 sound system
//2 aiming moves camera and works at different window sizes
//3 multithreading
//4 fully create everything needed for T2 fight
//5 change everything to use friction and speed normally
//6 add batching to high count objects

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <windows.h>
#include <ctime>
#include <cstdlib>
#include <thread>

#include <random>

#include <stdint.h>

#include "C:\Users\svt16\Desktop\Nuclear Throne Arranged\cmake-sfml-project\build\gameObjects.h"
#include "C:\Users\svt16\Desktop\Nuclear Throne Arranged\cmake-sfml-project\build\sprites.h"

#include ".\SFML\SimpleSpriteBatcher.hpp"

//temp debug variables

int bandit_choice1 = 0;
int draw_mult = 5;
//

int seed = time(NULL);

std::vector<gameObject> allObjects;

std::vector <sf::Sprite> allFloors;
int max_floors = 200;
int gen_curr_floor_index = 0;

std::vector<sf::Sprite> bullet_2_batchable;
int bullet_2_batchable_max = 25000;

std::vector<sf::Sprite> all_enemy_sprites;  //all enemy sprites that fit into a 32x32 box
int all_enemy_sprites_max = 5000;

std::vector<sf::Sprite> all_enemy_corpses;  //all enemy corpse sprites that fit into a 32x32 box
int all_enemy_corpses_max = 5000;

std::vector<sf::Sprite> rotateable_sprites_bullets;
int rotateable_sprites_bullets_max = 13000;

//for SPC
std::vector<sf::Sprite> rotateable_sprites_bullets_huge;
int rotateable_sprites_bullets_huge_max = 100;
std::vector<sf::Sprite> rotateable_sprites_bullets_huge_bloom;
int rotateable_sprites_bullets_huge_bloom_max = 100;

//for SPC
std::vector<sf::Sprite> rotateable_sprites_bullets_big;
int rotateable_sprites_bullets_big_max = 1000;
std::vector<sf::Sprite> rotateable_sprites_bullets_big_bloom;
int rotateable_sprites_bullets_big_bloom_max = 1000;

//explosions
std::vector<sf::Sprite> idpd_explosions_sprites;
int idpd_explosions_sprites_max = 100;

std::vector<sf::Sprite> plasma_impact_sprites;
int plasma_impact_sprites_max = 1800;

std::vector<sf::Sprite> rotateable_sprites_guns;
int rotateable_sprites_guns_max = 1000 * draw_mult;


//small effects 8x8 unrotateable
std::vector<sf::Sprite> rotateable_effects_small_bloom;
int rotateable_effects_small_bloom_max = 7500;
//small effects 8x8
std::vector<sf::Sprite> rotateable_effects_small;
int rotateable_effects_small_max = 2000;
//small effects 8x8 underneath
std::vector<sf::Sprite> under_effects_small;
int under_effects_small_max = 500;

//medium effects 16x16
std::vector<sf::Sprite> rotateable_effects_medium;
int rotateable_effects_medium_max = 6000;

//large effects 24x24
std::vector<sf::Sprite> rotateable_effects_large;
int rotateable_effects_large_max = 4000;

static float degreestoradians = 57.2957795f;

sf::Vector2f offset8 = { -4, -4 };
sf::Vector2f offset16 = {-8, -8};
sf::Vector2f offset18 = { -9, -9 };
sf::Vector2f offset24 = { -12, -12 };
sf::Vector2f offset32 = { -16, -16 };
sf::Vector2f offset48 = { -24, -24 };
sf::Vector2f offset64 = { -32, -32 };

static int gridSize = 3000;
static int max_objects = 262144;
int current_create_start = 1;
//int curr_objcount = 1;   this is now redundant as threads break it   //important to keep this equal to the amount of objects active so increase when "adding" object and decrease when "removing" an object (setting it to "nothing" type) starts at one for the player object
int current_frame = 0;      //used for stuff like i-frames, reset this each area
int LOOPS = 0;
//game logic stuff
int area = 1;
int sub_area = 1;


unsigned int MAXFPS = 30;

//contants
float e_constant = 2.71828f;

bool GAME_PAUSED = false;
int FRAME_ADVANCE = 0; //debug

int top_physics = 1499;
int bottom_physics = 1501;
int left_physics = 1499;        //static at the moment, should expand dyamically to fit when walls break
int right_physics = 1501;       //these confine thea area where physics take place which goes from the top most wall above the highest explo_tile to the bottom -1, same with left to right
int extra_physics = 20;

std::vector<std::vector<gridTile>> game_area(gridSize, std::vector<gridTile>(gridSize));

//player stuff
int player_level = 1;
int player_rads = 99999;

int player_bullets = 255;
int player_bolts = 55;
int player_shells = 55;
int player_explosives = 55;
int player_energy = 55;

int player_max_rads = 60;
int player_hp = 8;
int player_max_hp = 8;
float player_max_speed = 4.0f;      //max should be less than 5.0f or else walls can be cliped through
bool is_Bskin = false;

int player_is_facing_right = 1;

int wep = 0;    //ushov
int bwep = 11;  //SPC

float wep_reload = 0.0f;
float bwep_reload = 0.0f;

float reload_speed = 1.0f;

//player
bool player_move_up = false;
bool player_move_down = false;
bool player_move_left = false;
bool player_move_right = false;

bool player_held_LMB = false;
bool player_held_RMB = false;

bool LMB_pressed = false;
bool RMB_pressed = false;
bool SPACE_pressed = false;

bool player_swap_weps = false;
int change_window_scale = 0;
float playerDiagonalSpeedMult = 9.656855f / 4.0f;

bool player_prev_speed_greater_than_zero = false;

sf::Sprite player_sprite;

sf::Sprite wep_sprite;
sf::Sprite bwep_sprite;

sf::Sprite cursor_sprite;
sf::Cursor naitive_cursor_sprite;

bool naitive_cursor_active = true;

int crosshair_selected = 0;

int wep_shine_frame = 0;
float wep_angle = (rand() % 2 * 2 - 1) * 120.0f; //this is the offset used for melee
float wep_kick = 0.0f;
int swapmove = 0;

//check if key has been released
bool P_released = true;
bool L_released = true;
bool R_released = true;
bool SPACE_released = true;
bool LMB_released = true;
bool RMB_released = true;
bool SHIFT_held = false;

//horror
float horror_beam_strength = 0.0f;

//camera
float camera_want_x = 0.0f;
float camera_want_y = 0.0f;
sf::Vector2i mousepos = { 0, 0 };
float direction_to_mouse = 0.0f;
int weapon_camera_type = 5;     //0 = melee 2 = normal 4 = bolt
float window_size_x = 640.0f;
float window_size_y = 480.0f;
int window_scale = 2;
sf::Vector2f cameraOffset = { -window_size_x / (window_scale * 2), -window_size_y / (window_scale * 2) };

int mouse_offset_window_center_x = 0;
int mouse_offset_window_center_y = 0;

//mutations
int plutonium_hunger = 150;       //set to 150 when mutation got 90 when not
int plutonium_hunger_ammo = 70;
int impact_wrists = 0;
float long_arms = 1.0f;         //0.0f if no long arms, 1.0f if long arms
float trigger_fingers = 0.6f;
float laser_brain = 1.2f;

//ultras
int ultra_picked = 2;   //0 = no ultra

int meltdown = 1;       //set to 2 when meltdown is picked

character player_character = horror;

//sounds

//these two are for 2d sound
std::vector<sf::Vector3f> play_sounds_this_frame_pos;
std::vector<int> play_sounds_this_frame_count;

//generation
bool want_gen = true;

float random_360_radians() {    //dont use in multithreaded for more randomness
    return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (360.0f / degreestoradians)));
}
float random_360_degrees() {    //dont use in multithreaded for more randomness
    return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (360.0f)));
}

float random_180_radians() {    //dont use in multithreaded for more randomness
    return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (180.0f / degreestoradians)));
}
float random_180_degrees() {    //dont use in multithreaded for more randomness
    return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (180.0f)));
}

float random(float max_value) {    //dont use in multithreaded for more randomness
    return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max_value)));
}

float angle_to_player_radians(sf::Vector2f position) {
    return atan2f(allObjects[0].position.y - position.y, allObjects[0].position.x - position.x);
}

void play_sound_relative_to_player(sound sound_id, float x, float y) {
    play_sounds_this_frame_pos[sound_id].x += x - allObjects[0].position.x;
    play_sounds_this_frame_pos[sound_id].y += y - allObjects[0].position.y;
    play_sounds_this_frame_count[sound_id]++;
}

void play_sound_random_pitch(sf::Sound _sound, float variance, int i) {
    float pitch_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f*variance))) - variance;
    _sound.setPitch(1 + pitch_offset);
    _sound.setPosition(play_sounds_this_frame_pos[i].x / play_sounds_this_frame_count[i], 0, play_sounds_this_frame_pos[i].y / play_sounds_this_frame_count[i]);
    _sound.play();
}

void create_object(float x, float y, float xspd, float yspd, objectID obj_id, float direction, int image_index) {
    int I = current_create_start;
    float tmpdir = 0.0f;
    for (int i = I; i < max_objects; i++) {
        if (allObjects[i].my_id == nothing) {
            switch (obj_id) {
            case bullet1:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].direction = direction * degreestoradians + 180.0f;
                allObjects[i].image_index = 0;
                allObjects[i].team = 2;     //enemy team
                break;
            case bullet2:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].direction = direction * degreestoradians + 180.0f;
                allObjects[i].image_index = 0;
                allObjects[i].team = 2;     //enemy team
                break;
            case rad:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].image_index = 60 + ((150 + rand() % 30) / ((4 + LOOPS) / 4));   //60 is when the rad starts to blink
                allObjects[i].alarm1 = rand() % 12;
                allObjects[i].next_hurt = current_frame + 7 + rand() % 7;       //how much time to not be attracted to the player
                allObjects[i].rotation = random_360_degrees();
                break;
            case rad_destroy:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].image_index = 0;
                break;
            case ammo_pack:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].speed = { 0, 0 };
                allObjects[i].image_index = 0;
                allObjects[i].alarm1 = 60 + ((200 + rand() % 30) / ((5 + LOOPS) / 5));
                break;
            case bandit:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].speed = { 0, 0 };

                allObjects[i].speeddir = 0.0f;
                allObjects[i].direction = random_360_radians();
                allObjects[i].friction = 0.2f;

                allObjects[i].alarm1 = 30 + rand() % 90;

                allObjects[i].walk_frames = 0;

                allObjects[i].next_hurt = 0;
                allObjects[i].my_hp = round(4 * (1 + (LOOPS * 0.05f)));
                allObjects[i].image_index = rand() % 17;
                allObjects[i].team = 2;     //enemy team
                allObjects[i].rad_drop = 1;
                break;
            case scorpion:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].speed = { 0, 0 };

                allObjects[i].speeddir = 0.0f;
                allObjects[i].direction = random_360_radians();
                allObjects[i].friction = 0.2f;

                allObjects[i].alarm1 = 30 + rand() % 90;

                allObjects[i].walk_frames = 0;

                allObjects[i].next_hurt = 0;
                allObjects[i].my_hp = round(15 * (1 + (LOOPS * 0.05f)));
                break;
            case idpd_freak:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].speed = { 0, 0 };

                allObjects[i].speeddir = 0.0f;
                allObjects[i].walk_direction = random_360_radians();
                allObjects[i].gun_angle = random_360_radians();
                allObjects[i].friction = 0.2f;

                allObjects[i].alarm1 = 20 + rand() % 10;
                allObjects[i].alarm2 = 0;

                allObjects[i].next_hurt = 0;
                allObjects[i].my_hp = round(30 * (1 + (LOOPS * 0.05f)));
                allObjects[i].image_index = rand() % 17;
                allObjects[i].team = 2;     //enemy team
                allObjects[i].rad_drop = 25;
                break;
            case player_bullet:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].direction = direction * degreestoradians;
                allObjects[i].image_index = 0;
                allObjects[i].team = 1;     //player team
                break;
            case player_bullet_destroy:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].image_index = 0;
                allObjects[i].rotation = random_360_degrees();
                break;
            case horror_bullet:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].direction = direction * degreestoradians;
                allObjects[i].image_index = 0;
                allObjects[i].team = 1;     //player team
                break;
            case plasma_huge:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].scale = laser_brain; //bigger if laser brain
                allObjects[i].direction = direction * degreestoradians;
                allObjects[i].image_index = 0;
                allObjects[i].team = 1;     //player team
                allObjects[i].alarm1 = 0;
                allObjects[i].alarm2 = 0;   //tunneled
                break;
            case plasma_big:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].scale = 1.0f; //bigger if laser brain
                allObjects[i].direction = direction * degreestoradians;
                allObjects[i].image_index = image_index;
                allObjects[i].team = 1;     //player team
                allObjects[i].alarm1 = 0;
                allObjects[i].alarm2 = 0;   //tunneled
                break;
            case plasma:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].scale = 1.0f; //bigger if laser brain
                allObjects[i].direction = direction * degreestoradians;
                allObjects[i].image_index = image_index;
                allObjects[i].team = 1;     //player team
                allObjects[i].alarm1 = 0;
                allObjects[i].alarm2 = 0;   //tunneled
                break;
            case plasma_particle:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].image_index = 0;
                allObjects[i].alarm1 = 3 + (rand() % 2);    //3 or 4
                break;
            case plasma_impact:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].image_index = 0;
                allObjects[i].team = 2;     //enemy team
                play_sound_relative_to_player(snd_plasma_hit_ID, x, y);
                break;
            case plasma_hit:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].image_index = 0;
                allObjects[i].rotation = random_360_degrees();
                break;
            case ultra_slash:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].image_index = 0;
                allObjects[i].team = 1;     //player team
                allObjects[i].direction = direction;
                allObjects[i].speeddir = xspd;
                allObjects[i].friction = 0.1f;
                allObjects[i].alarm3 = 0;
                break;
            case idpd_explosion:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].image_index = 0;
                allObjects[i].team = 2;     //enemy team
                play_sound_relative_to_player(snd_explosion_ID, x, y);
                break;
            case idpd_nade:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].team = 2;     //enemy team, depends on what created it
                allObjects[i].direction = direction;
                allObjects[i].speeddir = xspd;
                allObjects[i].alarm1 = 0;
                allObjects[i].friction = 0.0f;
                allObjects[i].rotation = random_360_degrees(); //the random angle that the nade is drawn at
                break;
            case idpd_portal_charge:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].speed.x = xspd;
                allObjects[i].speed.y = yspd;
                allObjects[i].image_index = image_index;
                allObjects[i].alarm1 = int(direction); //how long til it disappears
                break;
            case debris:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].alarm1 = 200 + rand() % 90;
                allObjects[i].alarm2 = 0;
                allObjects[i].speeddir = 6.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f)));
                allObjects[i].direction = random_360_radians();
                allObjects[i].friction = random_360_degrees(); //what direction its facing
                allObjects[i].image_index = rand() % 4;
                break;
            case dust:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                tmpdir = random_360_radians();
                allObjects[i].speed.x = cos(tmpdir) * xspd;
                allObjects[i].speed.y = sin(tmpdir) * yspd;
                allObjects[i].direction = random_360_degrees();
                allObjects[i].rotation = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3.0f))) + 1.0f) * ((rand() % 2) * 2 - 1);  //rotation speed
                allObjects[i].growspeed = 0.05f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.05f)));  //growspeed
                allObjects[i].scale = 0.7f;  //image scale
                allObjects[i].image_index = rand() % 5;
                break;
            case smoke:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                tmpdir = random_360_radians();
                allObjects[i].speed.x = cos(tmpdir) * xspd;
                allObjects[i].speed.y = sin(tmpdir) * yspd;
                allObjects[i].direction = random_360_degrees();
                allObjects[i].rotation = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (3.0f))) + 1.0f) * ((rand() % 2) * 2 - 1);  //rotation speed
                allObjects[i].growspeed = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.005f)));  //growspeed
                allObjects[i].scale = 0.8f;  //image scale
                allObjects[i].image_index = rand() % 5;
                break;
            case deflect:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].direction = direction;
                allObjects[i].image_index = 0;
                break;
            case detail:
                allObjects[i].my_id = obj_id;
                allObjects[i].position = { x, y };
                allObjects[i].scale = rand() % 2 - 1;  //image scale
                if (area < 5) {
                    allObjects[i].image_index = rand() % 5;
                }
                if (area == 2) {    // sewers
                    allObjects[i].image_index = rand() % 6;
                }
                if (area >= 5) {    // city/labs
                    allObjects[i].image_index = rand() % 3;
                }
                break;
            }
            current_create_start = i + 1;       //helps alot with high object counts
            return;
        }
    }
}

bool has_line_of_sight(float x, float y) {

    //return true;
    float prev_x_pos = x - allObjects[0].position.x;
    float prev_y_pos = y - allObjects[0].position.y;

    float angle_to_player = atan2f(prev_y_pos, prev_x_pos);
    float x_spd = cos(angle_to_player) * -16.0f;
    float y_spd = sin(angle_to_player) * -16.0f;

    while (int(x / 16) != int(allObjects[0].position.x / 16) || int(y / 16) != int(allObjects[0].position.y / 16)) {
        prev_x_pos = x;
        prev_y_pos = y;

        x += x_spd;
        y += y_spd;


        if (int(x / 16) != int(prev_x_pos / 16) && int(y / 16) != int(prev_y_pos / 16)) {
            if (game_area[int(prev_x_pos / 16)][int(y / 16)].my_grid_type == wall && game_area[int(x / 16)][int(prev_y_pos / 16)].my_grid_type == wall) {   //block diagonal
                return false;
            }
            //do smaller steps, could be faster
            else if (game_area[int(prev_x_pos / 16)][int(y / 16)].my_grid_type == wall || game_area[int(x / 16)][int(prev_y_pos / 16)].my_grid_type == wall) {
                for (int i = 0; i < 16; i++) {
                    prev_x_pos += x_spd / 16;
                    prev_y_pos += y_spd / 16;

                    if (game_area[int(prev_x_pos / 16)][int(prev_y_pos / 16)].my_grid_type == wall) {
                        return false;
                    }
                }
            }
        }

        if (game_area[int(x / 16)][int(y / 16)].my_grid_type == wall) {
            return false;
        }

    }
    return true;
}

sf::Vector2f wep_get_origin(int wep_id){
    switch (wep_id) {
    case 0: //ushov
        return sf::Vector2f( 5, 6 );
        break;
    case 11:    //SPC
        return sf::Vector2f( 3, 6 );
        break;
    }
}

void play_swap_sound(int wep_id) {
    switch (wep_id) {
    case 0: //ushov
        play_sounds_this_frame_count[snd_hammer_swap_ID] = 1;
        break;
    case 11:    //SPC
        play_sounds_this_frame_count[snd_energy_swap_ID] = 1;
        break;
    }
}

void bounce_in_wall(int currOBJ) {
    bool bouncedV = false;
    bool bouncedH = false;
    allObjects[currOBJ].position -= allObjects[currOBJ].speed;
    if (game_area[int((allObjects[currOBJ].position.x + allObjects[currOBJ].speed.x) / 16)][int(allObjects[currOBJ].position.y / 16)].my_grid_type != wall) {
        bouncedV = true;
    }
    if (game_area[int(allObjects[currOBJ].position.x / 16)][int((allObjects[currOBJ].position.y + allObjects[currOBJ].speed.y) / 16)].my_grid_type != wall) {
        bouncedH = true;
    }
    if ((bouncedH && bouncedV) || (!bouncedH && !bouncedV)) {
        allObjects[currOBJ].speed.x *= -1;
        allObjects[currOBJ].speed.y *= -1;
    }
    else if (bouncedH) {
        allObjects[currOBJ].speed.x *= -1;
    }
    else if (bouncedV) {
        allObjects[currOBJ].speed.y *= -1;
    }
    allObjects[currOBJ].position += allObjects[currOBJ].speed;
    allObjects[currOBJ].direction = atan2f(allObjects[currOBJ].speed.y, allObjects[currOBJ].speed.x);
}

void bounce_in_corner_wall(int currOBJ) {
    allObjects[currOBJ].position -= allObjects[currOBJ].speed;
    allObjects[currOBJ].speed.x *= -1;
    allObjects[currOBJ].speed.y *= -1;
    allObjects[currOBJ].direction = atan2f(allObjects[currOBJ].speed.y, allObjects[currOBJ].speed.x);
}

void object_bounce_wall(int O, int h, int w, int width, int height, int i, int j) {

    //the width and height are effetively the radius of the square
    //x -> width
    //y -> height

    float diffx = (allObjects[O].position.x) - ((i * 16) + 8);    //distance from the center of the wall
    float diffy = (allObjects[O].position.y) - ((j * 16) + 8);    //distance from the center of the wall

    if (h == 0) {
        if (w == 1 && diffx > 0 && diffx < 8 + width && abs(diffy) < 8 + height) {
            allObjects[O].position.x = (i * 16) + 16 + width;
            //allObjects[O].speed.x *= -1;
            allObjects[O].direction = 180 / degreestoradians - allObjects[O].direction;        //mirror over y axis
            allObjects[O].facing_right = !allObjects[O].facing_right;
        }
        else if (w == -1 && diffx < 0 && diffx > -8 - width && abs(diffy) < 8 + height) {
            allObjects[O].position.x = (i * 16) - width;
            allObjects[O].direction = 180 / degreestoradians - allObjects[O].direction;        //mirror over y axis
            allObjects[O].facing_right = !allObjects[O].facing_right;
        }

    }

    if (w == 0) {
        if (h == 1 && diffy > 0 && diffy < 8 + height && abs(diffx) < 8 + width) {
            allObjects[O].position.y = (j * 16) + 16 + height;
            allObjects[O].direction = -allObjects[O].direction;     //mirror over x axis
        }
        else if (h == -1 && diffy < 0 && diffy > -8 - height && abs(diffx) < 8 + width) {
            allObjects[O].position.y = (j * 16) - height;
            allObjects[O].direction = -allObjects[O].direction;     //mirror over x axis
        }
    }

    if (w == 0 && h == 0) {
        if (diffx > 0 && diffy > 0) {
            if (diffx > diffy) {
                allObjects[O].position.x = (i * 16) + 16 + width;
            }
            else {
                allObjects[O].position.y = (j * 16) + 16 + height;
            }
        }
        else if (diffx > 0 && diffy < 0) {
            if (diffx > abs(diffy)) {
                allObjects[O].position.x = (i * 16) + 16 + width;
            }
            else {
                allObjects[O].position.y = (j * 16) - height;
            }
        }
        else if (diffx < 0 && diffy > 0) {
            if (abs(diffx) > diffy) {
                allObjects[O].position.x = (i * 16) - width;
            }
            else {
                allObjects[O].position.y = (j * 16) + 16 + height;
            }
        }
        else if (diffx < 0 && diffy < 0) {
            if (diffx < diffy) {
                allObjects[O].position.x = (i * 16) - width;
            }
            else {
                allObjects[O].position.y = (j * 16) - height;
            }
        }
        allObjects[O].direction = 180 / degreestoradians + allObjects[O].direction;        //mirror over x and y axis
        allObjects[O].facing_right = !allObjects[O].facing_right;
    }
}

void collide_wall(int object_index, int i, int j, int h, int w, int width) {
    bool horizontalcontact = false;
    bool verticalcontact = false;
    float diffx = (allObjects[object_index].position.x) - ((i * 16) + 8);    //distance from the center of the wall
    float diffy = (allObjects[object_index].position.y) - ((j * 16) + 8);    //distance from the center of the wall
    if (h == 0) {
        if (w == 1 && diffx > 0 && diffx < 13 && abs(diffy) < 13) {
            allObjects[object_index].position.x = (i * 16) + 16 + width;
        }
        if (w == -1 && diffx < 0 && diffx > -13 && abs(diffy) < 13) {
            allObjects[object_index].position.x = (i * 16) - width;
        }
    }

    if (w == 0) {
        if (h == 1 && diffy > 0 && diffy < 13 && abs(diffx) < 13) {
            allObjects[object_index].position.y = (j * 16) + 16 + width;
        }
        if (h == -1 && diffy < 0 && diffy > -13 && abs(diffx) < 13) {
            allObjects[object_index].position.y = (j * 16) - width;
        }
    }

    if (w == 0 && h == 0) {
        if (diffx > 0 && diffy > 0) {
            if (diffx > diffy) {
                allObjects[object_index].position.x = (i * 16) + 16 + width;
            }
            else {
                allObjects[object_index].position.y = (j * 16) + 16 + width;
            }
        }
        if (diffx > 0 && diffy < 0) {
            if (diffx > abs(diffy)) {
                allObjects[object_index].position.x = (i * 16) + 16 + width;
            }
            else {
                allObjects[object_index].position.y = (j * 16) - width;
            }
        }
        if (diffx < 0 && diffy > 0) {
            if (abs(diffx) > diffy) {
                allObjects[object_index].position.x = (i * 16) - width;
            }
            else {
                allObjects[object_index].position.y = (j * 16) + 16 + width;
            }
        }
        if (diffx < 0 && diffy < 0) {
            if (diffx < diffy) {
                allObjects[object_index].position.x = (i * 16) - width;
            }
            else {
                allObjects[object_index].position.y = (j * 16) - width;
            }
        }
    }
}

void motion_add_dir(float direction, float speed, int index) {

    //direction in radians
    float spd_add_x = cos(direction) * speed;
    float spd_add_y = sin(direction) * speed;

    float spd_curr_x = cos(allObjects[index].direction) * allObjects[index].speeddir;
    float spd_curr_y = sin(allObjects[index].direction) * allObjects[index].speeddir;

    spd_curr_x += spd_add_x;
    spd_curr_y += spd_add_y;

    float new_angle = atan2f(spd_curr_y, spd_curr_x);
    float new_speed = sqrt((spd_curr_y * spd_curr_y) + (spd_curr_x * spd_curr_x));

    allObjects[index].speeddir = new_speed;
    allObjects[index].direction = new_angle;
}

void motion_add_XY_speed(float xspd, float yspd, int index) {

    float spd_curr_x = cos(allObjects[index].direction) * allObjects[index].speeddir;
    float spd_curr_y = sin(allObjects[index].direction) * allObjects[index].speeddir;

    spd_curr_x += xspd;
    spd_curr_y += yspd;

    float new_angle = atan2f(spd_curr_y, spd_curr_x);
    float new_speed = sqrt((spd_curr_y * spd_curr_y) + (spd_curr_x * spd_curr_x));

    allObjects[index].speeddir = new_speed;
    allObjects[index].direction = new_angle;
}

void destroy_horror_bullet(int object_index) {
    allObjects[object_index].my_id = horror_bullet_destroy;    //turn into a on hit effect
    allObjects[object_index].image_index = 0;
    allObjects[object_index].direction = random_360_degrees();
}

void destroy_player_bullet(int object_index) {
    allObjects[object_index].my_id = player_bullet_destroy;    //turn into a on hit effect
    allObjects[object_index].image_index = 0;
    allObjects[object_index].direction = random_360_degrees();
}

void destroy_bullet_1(int object_index) {
    allObjects[object_index].my_id = bullet1_destroy;    //turn into a on hit effect
    allObjects[object_index].image_index = 0;
    allObjects[object_index].direction = random_360_degrees();
}

void destroy_bullet_2(int object_index) {
    allObjects[object_index].my_id = bullet2_destroy;    //turn into a on hit effect
    allObjects[object_index].image_index = rand() % 2;   //makes alot of them being destroyed look smoother
    allObjects[object_index].direction = random_360_degrees();
}

void detonate_IDPD_nade(int object_index, int image_index) {
    allObjects[object_index].my_id = idpd_explosion;
    allObjects[object_index].image_index = image_index;  //make sure the first 3 frames are non-damaging

    float tmpSPD = 0.0f;
    for (int i = 0; i < 8; i++) {
        tmpSPD = 1.0f + random(2.0f);
        create_object(allObjects[object_index].position.x, allObjects[object_index].position.y, tmpSPD, tmpSPD, smoke, 0, 0);    //smoke
    }
    for (int i = 0; i < 17; i++) {
        tmpSPD = 5.0f + random(1.0f);
        create_object(allObjects[object_index].position.x, allObjects[object_index].position.y, tmpSPD, tmpSPD, dust, 0, 0);    //dust
    }
    play_sound_relative_to_player(snd_explosion_ID, allObjects[object_index].position.x, allObjects[object_index].position.y);
}

void clear_idpd_nade(int object_index) {
    allObjects[object_index].my_id = idpd_nade_remove;
    allObjects[object_index].image_index = rand() % 3;
    allObjects[object_index].scale = rand() % 2 * 2 - 1;
    allObjects[object_index].rotation = random_360_degrees();
}

void destroy_plasma(int object_index, int image_index) {
    allObjects[object_index].my_id = plasma_impact;
    allObjects[object_index].image_index = image_index;  //make sure the first 3 frames are non-damaging

    for (int i = 0; i < 3; i++) {
        create_object(allObjects[object_index].position.x, allObjects[object_index].position.y, 2, 2, smoke, 0, 0);    //smoke
    }

    play_sound_relative_to_player(snd_plasma_hit_ID, allObjects[object_index].position.x, allObjects[object_index].position.y);
}

int create_floor(int x, int y, bool Btile) {
    int removedwall = 0;
    if (game_area[x][y].my_grid_type == wall) {
        removedwall = 1;
        //create detail
        if (!Btile && rand() % 32 == 0) {
            create_object(x * 16 + 4 + (rand() % 8),
                          y * 16 + 4 + (rand() % 8), 0, 0, detail, 0.0f, 0);
        }
    }
    game_area[x][y].my_grid_type = floor_tile;
    if (x > right_physics) {
        right_physics = x;
    }
    if (x < left_physics) {
        left_physics = x;
    }
    if (y > bottom_physics) {
        bottom_physics = y;
    }
    if (y < top_physics) {
        top_physics = y;
    }
    return removedwall;
}

int create_explo_tile(int x, int y) {
    int removedwall = 0;
    if (game_area[x][y].my_grid_type == wall) {
        removedwall = 1;
    }
    game_area[x][y].my_grid_type = exlpo_tile;
    if (x > right_physics) {
        right_physics = x;
    }
    if (x < left_physics) {
        left_physics = x;
    }
    if (y > bottom_physics) {
        bottom_physics = y;
    }
    if (y < top_physics) {
        top_physics = y;
    }
    //sound of wall breaking position, + 8 to center on block
    play_sound_relative_to_player(snd_wall_break_rock_ID, x * 16 + 8, y * 16 + 8);

    create_object(x * 16 + 8, y * 16 + 8, 0, 0, debris, 0, 0);
    return removedwall;
}

void vector2D_reset(int top, int bottom, int left, int right){
    for (int i = left; i < right; i++) {
        for (int j = top; j < bottom; j++) {
            game_area[i][j].object_indexes.clear();
            //game_area[i][j].current_object_index = 0;
            //game_area[i][j].has_line_of_sight = false;
        }
    }
}

void add_sprite_8(int idx, sf::Vector2f pos, sf::VertexArray& sprites) {
    int const i = 4 * idx;

    sprites[i + 0].position = pos;
    sprites[i + 1].position = { pos.x + 8, pos.y + 0 };
    sprites[i + 2].position = { pos.x + 8, pos.y + 8 };
    sprites[i + 3].position = { pos.x + 0, pos.y + 8 };

    sprites[i + 0].color = { 255, 255, 255, 255 };
    sprites[i + 1].color = { 255, 255, 255, 255 };
    sprites[i + 2].color = { 255, 255, 255, 255 };
    sprites[i + 3].color = { 255, 255, 255, 255 };
}

void add_sprite_16(int idx, sf::Vector2f pos, sf::VertexArray& sprites) {
    int const i = 4 * idx;

    sprites[i + 0].position = pos;
    sprites[i + 1].position = { pos.x + 16, pos.y + 0 };
    sprites[i + 2].position = { pos.x + 16, pos.y + 16 };
    sprites[i + 3].position = { pos.x + 0, pos.y + 16 };

    sprites[i + 0].color = { 255, 255, 255, 255 };
    sprites[i + 1].color = { 255, 255, 255, 255 };
    sprites[i + 2].color = { 255, 255, 255, 255 };
    sprites[i + 3].color = { 255, 255, 255, 255 };
}

void add_sprite_18(int idx, sf::Vector2f pos, sf::VertexArray& sprites) {
    int const i = 4 * idx;

    sprites[i + 0].position = pos;
    sprites[i + 1].position = { pos.x + 18, pos.y + 0 };
    sprites[i + 2].position = { pos.x + 18, pos.y + 18 };
    sprites[i + 3].position = { pos.x + 0, pos.y + 18 };

    sprites[i + 0].color = { 255, 255, 255, 255 };
    sprites[i + 1].color = { 255, 255, 255, 255 };
    sprites[i + 2].color = { 255, 255, 255, 255 };
    sprites[i + 3].color = { 255, 255, 255, 255 };
}

void add_sprite_24(int idx, sf::Vector2f pos, sf::VertexArray& sprites) {
    int const i = 4 * idx;

    sprites[i + 0].position = pos;
    sprites[i + 1].position = { pos.x + 24, pos.y + 0 };
    sprites[i + 2].position = { pos.x + 24, pos.y + 24 };
    sprites[i + 3].position = { pos.x + 0, pos.y + 24 };

    sprites[i + 0].color = { 255, 255, 255, 255 };
    sprites[i + 1].color = { 255, 255, 255, 255 };
    sprites[i + 2].color = { 255, 255, 255, 255 };
    sprites[i + 3].color = { 255, 255, 255, 255 };
}

void add_sprite_32(int idx, sf::Vector2f pos, sf::VertexArray& sprites) {
    int const i = 4 * idx;

    sprites[i + 0].position = pos;
    sprites[i + 1].position = { pos.x + 32, pos.y + 0 };
    sprites[i + 2].position = { pos.x + 32, pos.y + 32 };
    sprites[i + 3].position = { pos.x + 0, pos.y + 32 };

    sprites[i + 0].color = { 255, 255, 255, 255 };
    sprites[i + 1].color = { 255, 255, 255, 255 };
    sprites[i + 2].color = { 255, 255, 255, 255 };
    sprites[i + 3].color = { 255, 255, 255, 255 };
}

void add_sprite_36(int idx, sf::Vector2f pos, sf::VertexArray& sprites) {
    int const i = 4 * idx;

    sprites[i + 0].position = pos;
    sprites[i + 1].position = { pos.x + 36, pos.y + 0 };
    sprites[i + 2].position = { pos.x + 36, pos.y + 36 };
    sprites[i + 3].position = { pos.x + 0, pos.y + 36 };

    sprites[i + 0].color = { 255, 255, 255, 255 };
    sprites[i + 1].color = { 255, 255, 255, 255 };
    sprites[i + 2].color = { 255, 255, 255, 255 };
    sprites[i + 3].color = { 255, 255, 255, 255 };
}

void add_sprite_48(int idx, sf::Vector2f pos, sf::VertexArray& sprites) {
    int const i = 4 * idx;

    sprites[i + 0].position = pos;
    sprites[i + 1].position = { pos.x + 48, pos.y + 0 };
    sprites[i + 2].position = { pos.x + 48, pos.y + 48 };
    sprites[i + 3].position = { pos.x + 0, pos.y + 48 };

    sprites[i + 0].color = { 255, 255, 255, 255 };
    sprites[i + 1].color = { 255, 255, 255, 255 };
    sprites[i + 2].color = { 255, 255, 255, 255 };
    sprites[i + 3].color = { 255, 255, 255, 255 };
}

void add_sprite_64(int idx, sf::Vector2f pos, sf::VertexArray& sprites) {
    int const i = 4 * idx;

    sprites[i + 0].position = pos;
    sprites[i + 1].position = { pos.x + 64, pos.y + 0 };
    sprites[i + 2].position = { pos.x + 64, pos.y + 64 };
    sprites[i + 3].position = { pos.x + 0, pos.y + 64 };

    sprites[i + 0].color = { 255, 255, 255, 255 };
    sprites[i + 1].color = { 255, 255, 255, 255 };
    sprites[i + 2].color = { 255, 255, 255, 255 };
    sprites[i + 3].color = { 255, 255, 255, 255 };
}

void inline add_rotateable_sprite(int index, sf::Vector2f position, float angle, std::vector<sf::Sprite> &sprites, sf::Texture texture) {
    sprites[index].setTexture(texture);
    sprites[index].setColor({ 255, 255, 255, 255 });
    sprites[index].setPosition(position);
    sprites[index].setRotation(angle);
}

void clear_extra_vertex_array(sf::VertexArray& sprites, int start) {
    int count = sprites.getVertexCount();
    start *= 4;
    for (int i = start; i < count; i++) {
        sprites[i].color = { 1, 1, 1, 0 };
    }
}

sf::VertexArray create_vertex_array(sf::Texture texture, int size) {
    sf::Vector2f const textureSize = static_cast<sf::Vector2f>(texture.getSize());

    sf::VertexArray tempVA{ sf::PrimitiveType::Quads, size_t(4 * size)};

    for (int i = 0; i < size; i++) {
        int const idx = i * 4;
        tempVA[idx + 0].texCoords = { 0.0f, 0.0f };
        tempVA[idx + 1].texCoords = { textureSize.x, 0.0f };
        tempVA[idx + 2].texCoords = { textureSize.x, textureSize.y };
        tempVA[idx + 3].texCoords = { 0.0f, textureSize.y };
    }
    return tempVA;
}

bool inline is_within_circle(sf::Vector2f pos1, sf::Vector2f pos2, float distance) {
    return (distance * distance) > ((pos1.x - pos2.x) * (pos1.x - pos2.x)) + ((pos1.y - pos2.y) * (pos1.y - pos2.y));
}

bool is_within_melee_slash(sf::Vector2f melee_pos, sf::Vector2f otherpos, int other_size, float melee_angle) {
    //4 circles the should make up an acurate recreation of the original hitbox
    if (is_within_circle(melee_pos, otherpos, (other_size + 24))) {
        return true;
    }
    melee_pos.x += cos(melee_angle) * -16;
    melee_pos.y += sin(melee_angle) * -16;
    if (is_within_circle(melee_pos, otherpos, (other_size + 15))) {
        return true;
    }
    melee_pos.x += cos(melee_angle) * 6;
    melee_pos.y += sin(melee_angle) * 6;

    melee_angle += 90.0f / degreestoradians;

    melee_pos.x += cos(melee_angle) * 5;
    melee_pos.y += sin(melee_angle) * 5;
    if (is_within_circle(melee_pos, otherpos, (other_size + 15))) {
        return true;
    }
    melee_pos.x += cos(melee_angle) * -10;
    melee_pos.y += sin(melee_angle) * -10;
    if (is_within_circle(melee_pos, otherpos, (other_size + 15))) {
        return true;
    }
    return false;
}

void bandit_hurt(int BANDIT, int PROJ) {
    allObjects[BANDIT].next_hurt = current_frame + 6;
    allObjects[BANDIT].image_index = -6;        //resets their ai effectively stunning them whenever hit
    motion_add_XY_speed(allObjects[PROJ].speed.x, allObjects[PROJ].speed.y, BANDIT);   //knockback
    play_sound_relative_to_player(snd_bandit_hurt_ID, allObjects[BANDIT].position.x, allObjects[BANDIT].position.y);
}

void bandit_die(int BANDIT, int PROJ, int threadNUM) {
    //convert into corpse
    allObjects[BANDIT].my_id = bandit_corpse;
    allObjects[BANDIT].speed = allObjects[PROJ].speed;
    allObjects[BANDIT].image_index = 0;
    allObjects[BANDIT].friction = 0.7f;
    motion_add_XY_speed(allObjects[PROJ].speed.x, allObjects[PROJ].speed.y, BANDIT);   //knockback
    //create rads
    float tempSpdx = 0.0f;
    float tempSpdy = 0.0f;
    for (int i = allObjects[BANDIT].rad_drop; i > 0; i--) {
        tempSpdx = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 6.0f)) - 3.0f;
        tempSpdy = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 6.0f)) - 3.0f;
        create_object(allObjects[BANDIT].position.x, allObjects[BANDIT].position.y, tempSpdx, tempSpdy, rad, 0.0f, threadNUM);
    }


    //debug start
    float tmpdir = 0.0f;
    float tmpSpd = 0.0f;
    for (int i = 0; i < 10; i++) {
        tmpdir = random_360_radians();
        tmpSpd = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 2.0f)) + 3.0f;
        tempSpdx = cos(tmpdir) * tmpSpd;
        tempSpdy = sin(tmpdir) * tmpSpd;
        create_object(allObjects[BANDIT].position.x,
            allObjects[BANDIT].position.y,
            tempSpdx,
            tempSpdy, bullet2, tmpdir + 180.0f / degreestoradians, 0);
    }
    if (rand() % 110 == 0) { 
        create_object(allObjects[BANDIT].position.x, allObjects[BANDIT].position.y, tmpSpd * 2, 0, idpd_nade, tmpdir, 0);
        create_object(allObjects[BANDIT].position.x, allObjects[BANDIT].position.y, 0, 0, ammo_pack, 0, 0);
    }
    //debug end


    //reload
    wep_reload *= trigger_fingers;
    bwep_reload *= trigger_fingers;

    play_sound_relative_to_player(snd_bandit_die_ID, allObjects[BANDIT].position.x, allObjects[BANDIT].position.y);
}

void bandit_die_anomaly(int OBJ_ID) {
    //convert into corpse
    allObjects[OBJ_ID].my_id = bandit_corpse;
    if (allObjects[OBJ_ID].speed.x == 0.0f && allObjects[OBJ_ID].speed.y == 0.0f) {
        allObjects[OBJ_ID].direction = random_360_radians();
    }

    allObjects[OBJ_ID].image_index = 0;
    allObjects[OBJ_ID].friction = 0.7f;
    //create rads
    float tempSpdx = 0.0f;
    float tempSpdy = 0.0f;
    for (int i = allObjects[OBJ_ID].rad_drop; i > 0; i--) {
        tempSpdx = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 6.0f)) - 3.0f;
        tempSpdy = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 6.0f)) - 3.0f;
        create_object(allObjects[OBJ_ID].position.x, allObjects[OBJ_ID].position.y, tempSpdx, tempSpdy, rad, 0.0f, 0);
    }
    //reload
    wep_reload *= trigger_fingers;
    bwep_reload *= trigger_fingers;
    play_sound_relative_to_player(snd_bandit_hurt_ID, allObjects[OBJ_ID].position.x, allObjects[OBJ_ID].position.y);
    //second sound that plays with anolmaly sound that pans
    play_sound_relative_to_player(snd_horror_portal_ID, allObjects[OBJ_ID].position.x, allObjects[OBJ_ID].position.y);
}

void resize_window(int change, sf::RenderWindow &window) {
    window_size_x += 320 * change;
    window_size_y += 240 * change;
    window.setSize(sf::Vector2u(window_size_x, window_size_y));
    window.setPosition(window.getPosition() - sf::Vector2i(160 * change, 120 * change));
    cameraOffset = { -window_size_x / (window_scale * 2), -window_size_y / (window_scale * 2) };

    if (window_size_x == 320) {
        sf::Image cursor_pixels_1_16;
        cursor_pixels_1_16.loadFromFile("res/player/sprCrosshair_1_16.png");
        naitive_cursor_sprite.loadFromPixels(cursor_pixels_1_16.getPixelsPtr(), sf::Vector2u(16, 16), sf::Vector2u(8, 8));
    }
    if (window_size_x == 640) {
        sf::Image cursor_pixels_1_32;
        cursor_pixels_1_32.loadFromFile("res/player/sprCrosshair_1_32.png");
        naitive_cursor_sprite.loadFromPixels(cursor_pixels_1_32.getPixelsPtr(), sf::Vector2u(32, 32), sf::Vector2u(16, 16));
    }
    if (window_size_x == 960) {
        sf::Image cursor_pixels_1_48;
        cursor_pixels_1_48.loadFromFile("res/player/sprCrosshair_1_48.png");
        naitive_cursor_sprite.loadFromPixels(cursor_pixels_1_48.getPixelsPtr(), sf::Vector2u(48, 48), sf::Vector2u(24, 24));
    }
    if (window_size_x == 1280) {
        sf::Image cursor_pixels_1_64;
        cursor_pixels_1_64.loadFromFile("res/player/sprCrosshair_1_64.png");
        naitive_cursor_sprite.loadFromPixels(cursor_pixels_1_64.getPixelsPtr(), sf::Vector2u(64, 64), sf::Vector2u(32, 32));
    }
    window.setMouseCursor(naitive_cursor_sprite);
}

void clear_all_bullets() {      //clear all enemy bullets
    objectID curr_id = nothing;
    for (int i = 1; i < max_objects; i++) {
        curr_id = allObjects[i].my_id;
        switch (curr_id) {
        case bullet1:
            destroy_bullet_1(i);
            break;
        case bullet2:
            destroy_bullet_2(i);
            break;
        case idpd_nade:
            clear_idpd_nade(i);
            break;
        default:
            break;
        }
    }
}

void plasma_huge_destroy(int huge_plasma, int i, int j) {
    if (allObjects[huge_plasma].alarm1 == 0) {
        float tmpdir = 0.0f;
        float tempSpdx = 0.0f;
        float tempSpdy = 0.0f;
        for (int w = -2; w < 3; w++) {      //plasma_huge collison, has a bigger area to cover, maybe choose closest if needed?
            for (int h = -2; h < 3; h++) {
                if (game_area[i + w][j + h].my_grid_type == wall && is_within_circle(sf::Vector2f((i + w) * 16 + 8, (j + h) * 16 + 8), allObjects[huge_plasma].position, 36)) {
                    create_explo_tile(i + w, j + h);
                }
            }
        }
        //create 4 big plasmas
        tmpdir = random_360_radians();
        for (int I = 0; I < 4; I++) {
            tempSpdx = cos(tmpdir) * 6;
            tempSpdy = sin(tmpdir) * 6;
            create_object(allObjects[huge_plasma].position.x, allObjects[huge_plasma].position.y, tempSpdx, tempSpdy, plasma_big, tmpdir, 2);
            tmpdir += 90.0f / degreestoradians;
        }
        allObjects[huge_plasma].alarm1 = 1;     //destroy next frame
    }
}

void plasma_huge_collison(int huge_plasma, int i, int j) {
    float tmpdir = 0.0f;
    float tempSpdx = 0.0f;
    float tempSpdy = 0.0f;
    if (allObjects[huge_plasma].image_index > 1 && allObjects[huge_plasma].alarm1 == 0) {
        for (int w = -2; w < 3; w++) {      //plasma_huge collison, has a bigger area to cover, maybe choose closest bandit if needed?
            for (int h = -2; h < 3; h++) {
                for (int O : game_area[i + w][j + h].object_indexes) {
                    switch (allObjects[O].my_id) {
                    case bandit:
                        if (is_within_circle(allObjects[O].position, allObjects[huge_plasma].position, (bandit_hitbox + allObjects[huge_plasma].scale * plasma_hitbox))) {
                            allObjects[O].my_hp -= round(25 * allObjects[huge_plasma].scale);
                            if (allObjects[O].my_hp > 0) {
                                bandit_hurt(O, huge_plasma);
                            }
                            else {  //dead
                                bandit_die(O, huge_plasma, 0);
                            }
                            //create on hit effect
                            create_object(allObjects[huge_plasma].position.x, allObjects[huge_plasma].position.y, 0, 0, player_bullet_destroy, 0, 0);
                            create_object(allObjects[O].position.x, allObjects[O].position.y, 0, 0, plasma_hit, 0, 0);

                            allObjects[huge_plasma].scale -= 0.1f;
                            //allObjects[huge_plasma].alarm1 = 1;      //dont move next frame
                            allObjects[huge_plasma].position -= allObjects[huge_plasma].speed;
                            goto exit_huge_plasma;
                        }
                        break;
                    default:
                        break;
                    }
                }
                //collision with wall
                if (game_area[i + w][j + h].my_grid_type == wall && is_within_circle(sf::Vector2f(((i + w) * 16) + 8, ((j + h) * 16) + 8), allObjects[huge_plasma].position, (wall_hitbox + allObjects[huge_plasma].alarm2 + allObjects[huge_plasma].scale * plasma_hitbox))) {
                    allObjects[huge_plasma].scale -= 0.1f;
                    allObjects[huge_plasma].position -= allObjects[huge_plasma].speed;      //only move back if its going into wall
                    create_object(allObjects[huge_plasma].position.x, allObjects[huge_plasma].position.y, 0.5, 0.5, dust, 0, 0);    //dust
                    goto exit_huge_plasma;
                }
            }
        }
        exit_huge_plasma:
        //create plasma trails
        create_object(allObjects[huge_plasma].position.x + rand() % 37 - 18, allObjects[huge_plasma].position.y + rand() % 37 - 18, 0, 0, plasma_particle, 0, 0);
        //more clear and not fp rounding reliant value compared to 0.5f
        if (allObjects[huge_plasma].scale < 0.45f) {  //break walls around

            plasma_huge_destroy(huge_plasma, i, j);
        }
    }
}

void plasma_big_destroy(int big_plasma, int i, int j) {
    if (allObjects[big_plasma].alarm1 == 0) {
        float tmpdir = 0.0f;
        float tempSpdx = 0.0f;
        float tempSpdy = 0.0f;
        for (int w = -2; w < 3; w++) {      //plasma_huge collison, has a bigger area to cover, maybe choose closest if needed?
            for (int h = -2; h < 3; h++) {
                if (game_area[i + w][j + h].my_grid_type == wall && is_within_circle(sf::Vector2f((i + w) * 16 + 8, (j + h) * 16 + 8), allObjects[big_plasma].position, 36)) {
                    create_explo_tile(i + w, j + h);
                }
            }
        }
        //create 10 small plasmas
        tmpdir = random_360_radians();
        for (int i = 0; i < 10; i++) {
            tempSpdx = cos(tmpdir) * 6;
            tempSpdy = sin(tmpdir) * 6;
            create_object(allObjects[big_plasma].position.x, allObjects[big_plasma].position.y, tempSpdx, tempSpdy, plasma, tmpdir, 2);
            tmpdir += 36.0f / degreestoradians;
        }
        allObjects[big_plasma].alarm1 = 1;     //destroy next frame
    }
}

void plasma_big_collison(int big_plasma, int i, int j) {
    float tmpdir = 0.0f;
    float tempSpdx = 0.0f;
    float tempSpdy = 0.0f;
    if (allObjects[big_plasma].image_index > 1 && allObjects[big_plasma].alarm1 == 0) {
        for (int w = -2; w < 3; w++) {      //plasma_big collison, has a bigger area to cover, maybe choose closest bandit if needed?
            for (int h = -2; h < 3; h++) {
                for (int O : game_area[i + w][j + h].object_indexes) {
                    switch (allObjects[O].my_id) {
                    case bandit:
                        if (is_within_circle(allObjects[O].position, allObjects[big_plasma].position, (bandit_hitbox + allObjects[big_plasma].scale * plasma_hitbox))) {
                            allObjects[O].my_hp -= round(15 * allObjects[big_plasma].scale);
                            if (allObjects[O].my_hp > 0) {
                                bandit_hurt(O, big_plasma);
                            }
                            else {  //dead
                                bandit_die(O, big_plasma, 0);
                            }
                            //create on hit effect
                            create_object(allObjects[big_plasma].position.x, allObjects[big_plasma].position.y, 0, 0, player_bullet_destroy, 0, 0);
                            create_object(allObjects[O].position.x, allObjects[O].position.y, 0, 0, plasma_hit, 0, 0);

                            allObjects[big_plasma].scale -= 0.1f;
                            //allObjects[big_plasma].alarm1 = 1;      //dont move next frame
                            allObjects[big_plasma].position -= allObjects[big_plasma].speed;
                            goto exit_big_plasma;
                        }
                        break;
                    default:
                        break;
                    }
                }
                //collision with wall
                if (game_area[i + w][j + h].my_grid_type == wall && is_within_circle(sf::Vector2f(((i + w) * 16) + 8, ((j + h) * 16) + 8), allObjects[big_plasma].position, (wall_hitbox + allObjects[big_plasma].alarm2 + allObjects[big_plasma].scale * plasma_hitbox))) {
                    allObjects[big_plasma].scale -= 0.1f;
                    allObjects[big_plasma].position -= allObjects[big_plasma].speed;      //only move back if its going into wall
                    create_object(allObjects[big_plasma].position.x, allObjects[big_plasma].position.y, 0.5, 0.5, dust, 0, 0);    //dust
                    goto exit_big_plasma;
                }
            }
        }
        exit_big_plasma:
        //create plasma trails
        create_object(allObjects[big_plasma].position.x + rand() % 25 - 12, allObjects[big_plasma].position.y + rand() % 25 - 12, 0, 0, plasma_particle, 0, 0);
        //more clear and not fp rounding reliant value compared to 0.5f
        if (allObjects[big_plasma].scale < 0.45f) {  //break walls around
            plasma_big_destroy(big_plasma, i, j);
        }
    }
}

void plasma_collision(int plasma, int i, int j) {
    for (int w = -1; w < 2; w++) {      //plasma collison
        for (int h = -1; h < 2; h++) {
            for (int O : game_area[i + w][j + h].object_indexes) {
                switch (allObjects[O].my_id) {
                case bandit:
                    if (is_within_circle(allObjects[O].position, allObjects[plasma].position, (bandit_hitbox + allObjects[plasma].scale * plasma_hitbox))) {
                        allObjects[O].my_hp -= round(4 * allObjects[plasma].scale);
                        if (allObjects[O].my_hp > 0) {
                            bandit_hurt(O, plasma);
                        }
                        else {  //dead
                            bandit_die(O, plasma, 0);
                        }
                        //create on hit effect
                        create_object(allObjects[plasma].position.x, allObjects[plasma].position.y, 0, 0, player_bullet_destroy, 0, 0);
                        create_object(allObjects[O].position.x, allObjects[O].position.y, 0, 0, plasma_hit, 0, 0);

                        allObjects[plasma].scale -= 0.1f;
                        allObjects[plasma].alarm1 = 1;      //dont move next frame
                        goto exit_plasma;
                    }
                    break;
                default:
                    break;
                }
            }
            //collision with wall
            if (game_area[i + w][j + h].my_grid_type == wall && is_within_circle(sf::Vector2f(((i + w) * 16) + 8, ((j + h) * 16) + 8), allObjects[plasma].position, (wall_hitbox + allObjects[plasma].alarm2 + allObjects[plasma].scale * plasma_hitbox))) {
                allObjects[plasma].scale -= 0.1f;
                allObjects[plasma].alarm1 = 1;      //dont move next frame
                create_object(allObjects[plasma].position.x, allObjects[plasma].position.y, 0.5, 0.5, dust, 0, 0);    //dust
                goto exit_plasma;
            }
        }
    }
    exit_plasma:
    //create plasma trails
    create_object(allObjects[plasma].position.x + rand() % 17 - 9, allObjects[plasma].position.y + rand() % 17 - 9, 0, 0, plasma_particle, 0, 0);
    //more clear and not fp rounding reliant value compared to 0.5f
    if (allObjects[plasma].scale < 0.45f) {
        destroy_plasma(plasma, -1);
    }
}

//adding all the allObjects indexes to the 2dVector
void add_object_indexs_to_2Dvector(int start, int end) {
    for (int i = start; i < end; i++) {
        if (allObjects[i].my_id != nothing) {
            int xpos = allObjects[i].position.x / 16;
            int ypos = allObjects[i].position.y / 16;
            //game_area[xpos][ypos].object_indexes[game_area[xpos][ypos].current_object_index] = i;
            game_area[xpos][ypos].object_indexes.push_back(i);
            //game_area[xpos][ypos].current_object_index++;
        }
    }
}

void fire_weapom(int index, float direction) {
    float Xspd = 0.0f;
    float Yspd = 0.0f;
    float Xoff = 0.0f;
    float Yoff = 0.0f;
    switch (index) {
    case 0:     //ultra shovel
        if (LMB_pressed && wep_reload < 0.0f) {
            LMB_pressed = false;
            if (player_rads > 13) {
                wep_kick = -6;
                wep_angle *= -1;
                play_sounds_this_frame_count[snd_ultra_shovel_ID] = 1;
                player_rads -= 14;
                wep_reload = 21.0f;
                motion_add_dir(direction, 8, 0);

                Xspd = (3 + long_arms * 3.0f);
                Xoff = cos(direction) * (long_arms * 20.0f + 24.0f);    //24.0f is to account for the offset
                Yoff = sin(direction) * (long_arms * 20.0f + 24.0f);
                create_object(allObjects[0].position.x + Xoff, allObjects[0].position.y + Yoff, Xspd, 0, ultra_slash, direction, 0);

                Xspd -= 1;
                direction += 60.0f / degreestoradians;

                Xoff = cos(direction) * (long_arms * 15.0f + 24.0f);
                Yoff = sin(direction) * (long_arms * 15.0f + 24.0f);
                create_object(allObjects[0].position.x + Xoff, allObjects[0].position.y + Yoff, Xspd, 0, ultra_slash, direction, 0);

                direction -= 120.0f / degreestoradians;

                Xoff = cos(direction) * (long_arms * 15.0f + 24.0f);
                Yoff = sin(direction) * (long_arms * 15.0f + 24.0f);
                create_object(allObjects[0].position.x + Xoff, allObjects[0].position.y + Yoff, Xspd, 0, ultra_slash, direction, 0);
            }
            else {
                //not enough rads
            }
        }
        break;
    case 11:
        if (LMB_pressed && wep_reload < 0.0f) {
            LMB_pressed = false;
            wep_kick = 7;
            motion_add_dir(direction, -16, 0);
            play_sounds_this_frame_count[snd_plasma_huge_ID] = 1;
            wep_reload = 260.0f;
            Xspd = cos(direction) * 6.0f;
            Yspd = sin(direction) * 6.0f;
            create_object(allObjects[0].position.x + Xspd / 2, allObjects[0].position.y + Yspd / 2, Xspd, Yspd, plasma_huge, direction, 0);
        }
        break;
    default:
        break;
    }
}

void object_tunnel_corner(int currOBJ) {
    switch (allObjects[currOBJ].my_id) {
    case objectID::bullet1:
        destroy_bullet_1(currOBJ);
        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
        break;
    case objectID::bullet2:
        destroy_bullet_2(currOBJ);
        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
        break;
    case objectID::player_bullet:
        destroy_player_bullet(currOBJ);
        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
        break;
    case objectID::horror_bullet:
        destroy_horror_bullet(currOBJ);
        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
        break;
    case objectID::bandit_corpse:
        bounce_in_corner_wall(currOBJ);
        break;
    case objectID::idpd_nade:
        bounce_in_wall(currOBJ);
        allObjects[currOBJ].speeddir = allObjects[currOBJ].speeddir * 0.5;
        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
        play_sound_relative_to_player(snd_nade_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
        break;
    case objectID::debris:
        bounce_in_corner_wall(currOBJ);
        allObjects[currOBJ].speeddir = allObjects[currOBJ].speeddir / 2;
        break;
    case objectID::plasma_huge:
        allObjects[currOBJ].alarm2 = 99;     //tunneled
        break;
    case objectID::plasma_big:
        allObjects[currOBJ].alarm2 = 99;     //tunneled
        break;
    case objectID::plasma:
        allObjects[currOBJ].alarm2 = 99;     //tunneled
        break;
    default:
        break;
    }
}

void do_object_logic(int start, int end) {    //logic done on each obect every frame
    float tmpdir = 0.0f;
    float tempSpeedX = 0.0f;
    float tempSpeedY = 0.0f;
    float tempSpeed = 0.0f;
    float diffx = 0.0f;
    float diffy = 0.0f;
    std::random_device rd;
    // Initialize random number generator
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, RAND_MAX);
    for (int i = start; i < end; i++) {
        switch (allObjects[i].my_id) {
        case bullet1:
            allObjects[i].image_index++;
            allObjects[i].position += allObjects[i].speed;
            break;
        case bullet2:
            allObjects[i].position += allObjects[i].speed;
            break;
        case bullet1_destroy:
            allObjects[i].image_index++;
            if (allObjects[i].image_index > 9) {
                allObjects[i].my_id = nothing;
            }
            break;
        case bullet2_destroy:
            allObjects[i].image_index++;
            if (allObjects[i].image_index > 9) {
                allObjects[i].my_id = nothing;
            }
            break;
        case rad:
            allObjects[i].image_index--;
            //remove them after a certain amount of time lower with loop
            if (allObjects[i].image_index < 0) {
                allObjects[i].my_id = nothing;
            }

            if (allObjects[i].next_hurt > current_frame) {
                allObjects[i].speed.x *= 0.7f;
                allObjects[i].speed.y *= 0.7f;
                //allObjects[i].position += allObjects[i].speed;
            }
            if (allObjects[i].next_hurt == current_frame) {
                allObjects[i].speed.x = 0.0f;
                allObjects[i].speed.y = 0.0f;
            }

            diffx = allObjects[i].position.x - allObjects[0].position.x;
            diffy = allObjects[i].position.y - allObjects[0].position.y;
            if (allObjects[i].next_hurt < current_frame && sqrt(pow(diffx, 2) + pow(diffy, 2)) < plutonium_hunger) {
                tmpdir = atan2(diffy, diffx);
                allObjects[i].speed.x = cos(tmpdir) * -12;
                allObjects[i].speed.y = sin(tmpdir) * -12;
            }
            if (allObjects[i].team == 0) {
                allObjects[i].position += allObjects[i].speed;
            }

            allObjects[i].team = 0;
            break;
        case rad_destroy:
            allObjects[i].image_index++;
            //remove them after a certain amount of time
            if (allObjects[i].image_index > 6) {
                allObjects[i].my_id = nothing;
            }
            break;
        case ammo_pack:
            allObjects[i].image_index++;
            if (allObjects[i].image_index > 35 && rand() % 60 == 0) {
                allObjects[i].image_index = 0;
            }
            allObjects[i].alarm1--;
            if (allObjects[i].alarm1 < 0) {
                allObjects[i].my_id = nothing;
            }
            diffx = allObjects[i].position.x - allObjects[0].position.x;
            diffy = allObjects[i].position.y - allObjects[0].position.y;
            if (sqrt(pow(diffx, 2) + pow(diffy, 2)) < plutonium_hunger_ammo) {
                tmpdir = atan2(diffy, diffx);
                allObjects[i].speed.x = cos(tmpdir) * -6;
                allObjects[i].speed.y = sin(tmpdir) * -6;
            }
            else {
                allObjects[i].speed.x = 0;
                allObjects[i].speed.y = 0;
            }

            allObjects[i].position += allObjects[i].speed;
            break;
        case bandit:
            allObjects[i].speeddir -= allObjects[i].friction;

            if (allObjects[i].walk_frames > 0) {
                motion_add_dir(allObjects[i].direction, 0.8f, i);
            }

            if (allObjects[i].speeddir > 3.0f) {
                allObjects[i].speeddir = 3.0f;
            }
            else if (allObjects[i].speeddir < 0.0f) {
                allObjects[i].speeddir = 0;
            }

            allObjects[i].speed.x = cos(allObjects[i].direction) * allObjects[i].speeddir;
            allObjects[i].speed.y = sin(allObjects[i].direction) * allObjects[i].speeddir;

            allObjects[i].position += allObjects[i].speed;

            allObjects[i].image_index++;

            allObjects[i].alarm1--;
            allObjects[i].walk_frames--;

            break;
        case bandit_corpse:
            if (allObjects[i].speeddir > 0.0f) {
                allObjects[i].speeddir -= 0.2f;
                allObjects[i].speed.x = cos(allObjects[i].direction) * allObjects[i].speeddir;
                allObjects[i].speed.y = sin(allObjects[i].direction) * allObjects[i].speeddir;
                allObjects[i].position += allObjects[i].speed;
            }
            allObjects[i].image_index++;
            break;
        case idpd_freak:
            allObjects[i].speeddir -= allObjects[i].friction;

            if (allObjects[i].speeddir > 4.5f) {
                allObjects[i].speeddir = 4.5f;
            }
            else if (allObjects[i].speeddir < 0.0f) {
                allObjects[i].speeddir = 0;
            }

            allObjects[i].speed.x = cos(allObjects[i].direction) * allObjects[i].speeddir;
            allObjects[i].speed.y = sin(allObjects[i].direction) * allObjects[i].speeddir;

            allObjects[i].position += allObjects[i].speed;

            allObjects[i].image_index++;

            allObjects[i].alarm1--;
            allObjects[i].alarm2--;

            if (allObjects[i].walk_frames > 0)
            {
                allObjects[i].walk_frames--;
                if (allObjects[i].next_hurt < current_frame) {
                    motion_add_dir(allObjects[i].direction, 0.55f, i);
                }
                else {
                    motion_add_dir(allObjects[i].walk_direction, 1, i);
                }
            }

            //alarm1
            if (allObjects[i].alarm1 < 0) {
                allObjects[i].alarm1 = 15 + rand() % 5;
                if (has_line_of_sight(allObjects[i].position.x, allObjects[i].position.y)) {
                    allObjects[i].walk_frames = 20;
                    motion_add_dir(angle_to_player_radians(allObjects[i].position) + (random_180_radians() / 2) - (45 / degreestoradians), 5.0f, i);
                    if (is_within_circle(allObjects[i].position, allObjects[0].position, 160) && !is_within_circle(allObjects[i].position, allObjects[0].position, 64) && rand() % 3 != 0) {
                        allObjects[i].gun_angle = angle_to_player_radians(allObjects[i].position) + (random_180_radians() / 2) - (45 / degreestoradians);
                        allObjects[i].alarm1 += 30;
                        allObjects[i].alarm2 = 15 + 8;
                        allObjects[i].walk_frames = 6;
                    }
                }
                else {
                    if (rand() % 4 == 0) {
                        allObjects[i].walk_frames = 20;
                        motion_add_dir(random_360_radians(), 3.0f, i);
                    }
                }
            }
            if (allObjects[i].alarm2 >= 0 && allObjects[i].alarm2 < 8) {
                if (allObjects[i].alarm2 == 7) {
                    allObjects[i].gun_angle = angle_to_player_radians(allObjects[i].position) + (random_180_radians() / 2) - (45 / degreestoradians);
                }
                tmpdir = allObjects[i].gun_angle + (random(100.0f) - 50.0f) / degreestoradians;
                tempSpeed = random(3.0f) + 4.0f;
                tempSpeedX = cos(tmpdir);
                tempSpeedY = sin(tmpdir);
                create_object(allObjects[i].position.x, allObjects[i].position.y, tempSpeedX, tempSpeedY, idpd_bullet, tmpdir, 0);

                tmpdir = allObjects[i].gun_angle + (random(40.0f) - 20.0f) / degreestoradians;
                tempSpeed = random(3.0f) + 4.0f;
                tempSpeedX = cos(tmpdir);
                tempSpeedY = sin(tmpdir);
                create_object(allObjects[i].position.x, allObjects[i].position.y, tempSpeedX, tempSpeedY, idpd_bullet, tmpdir, 0);
            }

            break;
        case player_bullet:
            allObjects[i].position += allObjects[i].speed;
            allObjects[i].image_index++;
            break;
        case horror_bullet:
            allObjects[i].position += allObjects[i].speed;
            allObjects[i].image_index++;
            break;
        case plasma_huge:
            if (allObjects[i].image_index > 1) {
                allObjects[i].position += allObjects[i].speed;
            }
            //do this to delay a frame
            if (allObjects[i].alarm1 == 2) {
                allObjects[i].my_id = nothing;
                play_sound_relative_to_player(snd_plasma_split_ID, allObjects[i].position.x, allObjects[i].position.y);
            }
            if (allObjects[i].alarm1 == 1) {
                allObjects[i].alarm1 = 2;
            }
            allObjects[i].image_index++;
            break;
        case plasma_big:
            if (allObjects[i].image_index > 1) {
                allObjects[i].position += allObjects[i].speed;
            }
            //do this to delay a frame
            if (allObjects[i].alarm1 == 2) {
                allObjects[i].my_id = nothing;
                play_sound_relative_to_player(snd_plasma_split_ID, allObjects[i].position.x, allObjects[i].position.y);
            }
            if (allObjects[i].alarm1 == 1) {
                allObjects[i].alarm1 = 2;
            }
            allObjects[i].image_index++;
            break;
        case plasma:
            //alarm1 determines if the plasma hit something that keeps it from moving
            if (allObjects[i].image_index > 1 && allObjects[i].alarm1 == 0) {
                allObjects[i].position += allObjects[i].speed;
            }

            allObjects[i].alarm1 = 0;
            allObjects[i].image_index++;
            break;
        case plasma_particle:
            //alarm1 is the image speed / 10
            allObjects[i].image_index += allObjects[i].alarm1;
            if (allObjects[i].image_index > 29) {
                allObjects[i].my_id = nothing;
            }
            break;
        case plasma_impact:
            allObjects[i].image_index++;
            if (allObjects[i].image_index > 16) {
                allObjects[i].my_id = nothing;
            }
            break;
        case plasma_hit:
            allObjects[i].image_index++;
            if (allObjects[i].image_index > 9) {
                allObjects[i].my_id = nothing;
            }
            break;
        case ultra_slash:
            if (allObjects[i].alarm3 == 0) {
                allObjects[i].speeddir -= allObjects[i].friction;
                allObjects[i].speed.x = cos(allObjects[i].direction) * allObjects[i].speeddir;
                allObjects[i].speed.y = sin(allObjects[i].direction) * allObjects[i].speeddir;

                allObjects[i].position += allObjects[i].speed;
            }
            allObjects[i].image_index++;
            if (allObjects[i].image_index > 6) {
                allObjects[i].my_id = nothing;
            }
            break;
        case idpd_explosion:
            allObjects[i].image_index++;
            if (allObjects[i].image_index > 19) {
                allObjects[i].my_id = nothing;
            }
            break;
        case idpd_nade:
            allObjects[i].alarm1++;
            allObjects[i].alarm2++;
            if (allObjects[i].alarm1 > 90) {
                detonate_IDPD_nade(i, 0);
                //play extra sound
                play_sound_relative_to_player(snd_IDPD_explosion_ID, allObjects[i].position.x, allObjects[i].position.y);
            }
            if (allObjects[i].alarm1 == 69) {
                play_sound_relative_to_player(snd_IDPD_nade_almost_ID, allObjects[i].position.x, allObjects[i].position.y);
            }
            if (allObjects[i].alarm2 >= 10) {
                allObjects[i].friction = 0.5f;
                if (allObjects[i].alarm2 == 10) {
                    for (int b = 0; b < 4; b++) {
                        create_object(allObjects[i].position.x, allObjects[i].position.y, 2, 2, smoke, 0, 0);    //smoke
                        play_sound_relative_to_player(snd_IDPD_nade_load_ID, allObjects[i].position.x, allObjects[i].position.y);
                    }
                }
            }

            allObjects[i].speeddir -= allObjects[i].friction;
            if (allObjects[i].speeddir > 12.0f){
                allObjects[i].speeddir = 12.0f;
            }
            if (allObjects[i].speeddir <= 0.0f) {
                allObjects[i].speeddir = 0.0f;
                //create portal charges
                tempSpeedX = random(1) + 2;
                diffx = rand() % 96 - 48;
                diffy = rand() % 96 - 48;
                tmpdir = atan2f(diffy, diffx);
                create_object(allObjects[i].position.x + diffx, allObjects[i].position.y + diffy, cos(tmpdir) * -tempSpeedX, sin(tmpdir) * -tempSpeedX, idpd_portal_charge, (sqrt((diffx * diffx) + (diffy * diffy)) / tempSpeedX) + 1, rand() % 4);
            }

            allObjects[i].speed.x = cos(allObjects[i].direction) * allObjects[i].speeddir;
            allObjects[i].speed.y = sin(allObjects[i].direction) * allObjects[i].speeddir;

            allObjects[i].position += allObjects[i].speed;
            break;
        case idpd_portal_charge:
            allObjects[i].alarm1--;
            if (allObjects[i].alarm1 < 0) {
                allObjects[i].my_id = nothing;
            }
            else {
                allObjects[i].position += allObjects[i].speed;
            }

            break;
        case player_bullet_destroy:
            allObjects[i].image_index++;
            if (allObjects[i].image_index > 9) {
                allObjects[i].my_id = nothing;
            }
            break;
        case horror_bullet_destroy:
            allObjects[i].image_index++;
            if (allObjects[i].image_index > 9) {
                allObjects[i].my_id = nothing;
            }
            break;
        case idpd_nade_remove:
            allObjects[i].image_index++;
            if (allObjects[i].image_index > 12) {
                allObjects[i].my_id = nothing;
            }
            break;
        case debris:
            if (allObjects[i].speeddir > 0) {
                allObjects[i].alarm2--;
                allObjects[i].speeddir -= 0.2f;

                allObjects[i].speed.x = cos(allObjects[i].direction) * allObjects[i].speeddir;
                allObjects[i].speed.y = sin(allObjects[i].direction) * allObjects[i].speeddir;

                allObjects[i].position += allObjects[i].speed;
            }
            allObjects[i].alarm1--;
            
            break;
        case dust:
            allObjects[i].speed.x *= 0.93f;
            allObjects[i].speed.y *= 0.93f;
            allObjects[i].position.x += allObjects[i].speed.x;
            allObjects[i].position.y += allObjects[i].speed.y;
            allObjects[i].scale += allObjects[i].growspeed;
            allObjects[i].growspeed -= 0.02f;
            allObjects[i].direction += allObjects[i].rotation;
            if (allObjects[i].scale < 0.0f) {
                allObjects[i].my_id = nothing;
            }
            break;
        case smoke:
            allObjects[i].speed.x *= 0.93f;
            allObjects[i].speed.y *= 0.93f;
            allObjects[i].position.x += allObjects[i].speed.x;
            allObjects[i].position.y += allObjects[i].speed.y;
            allObjects[i].scale += allObjects[i].growspeed;
            allObjects[i].growspeed -= 0.001f;
            allObjects[i].direction += allObjects[i].rotation;
            if (allObjects[i].scale < 0.0f) {
                allObjects[i].my_id = nothing;
            }
            break;
        case deflect:
            allObjects[i].image_index++;
            if (allObjects[i].image_index > 12) {
                allObjects[i].my_id = nothing;
            }
            break;
        default:
            break;
        }
    }
}
void reset_rotateable_sprites(std::vector<sf::Sprite> &sprites, int largest_index) {
    for (int i = 0; i < largest_index; i++) {
        sprites[i].setColor({ 0,0,0,0 });
    }
}

void do_object_collision(int start, int end, int threadNUM) {       //create objects at different offsets depending on the thread so work is more evenly spread and overlap in object creation is basically impossible
    std::random_device rd;
    // Initialize random number generator
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, RAND_MAX);
    
    for (int i = start; i < end; i++) {
        for (int j = top_physics - extra_physics; j < bottom_physics + extra_physics; j++) {    //the physics bounds should start and end at the highest and lowest explotile
            float tmpdir = 0.0f;
            float diffx = 0.0f;
            float diffy = 0.0f;
            float tempSpdx = 0.0f;
            float tempSpdy = 0.0f;
            bool horizontalcontact = false;
            bool verticalcontact = false;
            float prevX = 0.0f;
            float prevY = 0.0f;
            bool bouncedH = false;
            bool bouncedV = false;
            int parsedObjects = 0; //maybe use this
            switch (game_area[i][j].my_grid_type) {
            case wall:
                for (int w = -1; w < 2; w++) {      //each wall checks around it for possible collisions with objects that are supposed to be bigger than a single point
                    for (int h = -1; h < 2; h++) {
                        for (int O : game_area[i + w][j + h].object_indexes) {      //walls collisions and bounce
                            switch (allObjects[O].my_id) {
                            case objectID::rad:
                                diffx = (allObjects[O].position.x + allObjects[O].speed.x) - ((i * 16) + 8);    //distance from the center of the wall
                                diffy = (allObjects[O].position.y + allObjects[O].speed.y) - ((j * 16) + 8);    //distance from the center of the wall
                                if (sqrt(pow(diffx, 2) + pow(diffy, 2)) < 16) {
                                    if (sqrt(pow(diffx, 2) + pow(diffy, 2)) < sqrt(pow(allObjects[O].position.x, 2) + pow(allObjects[O].position.y, 2))) {      //if moving closer to the wall
                                        allObjects[O].team = 1;     //doesnt move if team is 1
                                    }
                                }
                                break;
                            case objectID::player:
                                collide_wall(O, i, j, h, w, 5);
                                break;
                            case objectID::ammo_pack:
                                collide_wall(O, i, j, h, w, 7);
                                break;
                            case bandit:
                                horizontalcontact = false;
                                verticalcontact = false;
                                object_bounce_wall(O, h, w, 5, 5, i, j);
                                break;
                            default:
                                break;
                            }

                        }
                    }
                }
                for (int currOBJ : game_area[i][j].object_indexes) {    //inside of wall
                    switch (allObjects[currOBJ].my_id) {
                    case objectID::bullet1:
                        destroy_bullet_1(currOBJ);
                        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
                        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
                        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
                        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
                        break;       //bullet destroy particle
                    case objectID::bullet2:
                        destroy_bullet_2(currOBJ);
                        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
                        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
                        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
                        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
                        break;
                    case objectID::player_bullet:
                        destroy_player_bullet(currOBJ);
                        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
                        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
                        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
                        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
                        break;      //bullet destroy particle
                    case objectID::horror_bullet:
                        destroy_horror_bullet(currOBJ);
                        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
                        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
                        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
                        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
                        break;       //bullet destroy particle
                    case plasma_huge:       //same version but in wall
                        plasma_huge_collison(currOBJ, i, j);
                        allObjects[currOBJ].alarm2 = 99;
                        break;
                    case plasma_big:
                        plasma_big_collison(currOBJ, i, j);
                        allObjects[currOBJ].alarm2 = 99;
                        break;
                    case plasma:
                        plasma_collision(currOBJ, i, j);
                        allObjects[currOBJ].alarm2 = 99;
                        break;
                    case objectID::bandit_corpse:
                        bounce_in_wall(currOBJ);
                        break;
                    case objectID::idpd_nade:
                        bounce_in_wall(currOBJ);
                        allObjects[currOBJ].speeddir = allObjects[currOBJ].speeddir * 0.5;
                        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
                        play_sound_relative_to_player(snd_nade_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
                        break;
                    case objectID::idpd_explosion:
                        if (allObjects[currOBJ].image_index == 3 || allObjects[currOBJ].image_index == 4) {
                            for (int w = -6; w < 7; w++) {  
                                for (int h = -6; h < 7; h++) {
                                    //destroy wall
                                    if (game_area[i + w][j + h].my_grid_type == wall && is_within_circle(sf::Vector2f(((i + w) * 16) + 8, ((j + h) * 16) + 8), allObjects[currOBJ].position, (wall_hitbox + 48))) {
                                        create_explo_tile(i + w, j + h);
                                    }
                                    for (int O : game_area[i + w][j + h].object_indexes) {
                                        switch (allObjects[O].my_id) {
                                        case idpd_explosion:
                                            if ((allObjects[O].image_index == 3 || allObjects[O].image_index == 4) &&
                                                is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (48 + 48))) {

                                                tmpdir = atan2f(allObjects[currOBJ].position.y - allObjects[O].position.y, allObjects[currOBJ].position.x - allObjects[O].position.x);
                                                allObjects[currOBJ].position.x += cos(tmpdir) * 4;
                                                allObjects[currOBJ].position.y += sin(tmpdir) * 4;

                                                allObjects[O].position.x -= cos(tmpdir) * 4;
                                                allObjects[O].position.y -= sin(tmpdir) * 4;
                                                //moving both should have more predictable results
                                                //not broken like the official version
                                            }
                                            break;
                                        case idpd_nade:
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (2 + 48))) {
                                                detonate_IDPD_nade(O, -1);
                                            }
                                            break;
                                        case bandit:
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (bandit_hitbox + 48))) {
                                                allObjects[O].my_hp -= 8;
                                                tmpdir = atan2f(allObjects[currOBJ].position.y - allObjects[O].position.y, allObjects[currOBJ].position.x - allObjects[O].position.x);
                                                allObjects[currOBJ].speed.x = cos(tmpdir) * 12;
                                                allObjects[currOBJ].speed.y = sin(tmpdir) * 12; //this is so the bandit_hurt() function works
                                                if (allObjects[O].my_hp > 0) {
                                                    bandit_hurt(O, currOBJ);
                                                }
                                                else {  //dead
                                                    bandit_die(O, currOBJ, threadNUM);
                                                }

                                            }
                                            break;
                                        case plasma_huge:
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (allObjects[O].scale * plasma_hitbox + 48))) {
                                                plasma_huge_destroy(O, i + w, j + h);
                                            }
                                            break;
                                        case plasma_big:
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (allObjects[O].scale * plasma_hitbox + 48))) {
                                                plasma_big_destroy(O, i + w, j + h);
                                            }
                                            break;
                                        case plasma:
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (allObjects[O].scale * plasma_hitbox + 48))) {
                                                //turn into plasma explosion
                                                destroy_plasma(O, -1);
                                            }
                                            break;
                                        case bullet1:
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (3 + 48))) {
                                                destroy_bullet_1(O);
                                            }
                                            break;
                                        case bullet2:
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (3 + 48))) {
                                                destroy_bullet_2(O);
                                            }
                                            break;
                                        case horror_bullet:
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (3 + 48))) {
                                                destroy_horror_bullet(O);
                                            }
                                            break;
                                        default:
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case objectID::ultra_slash:
                        allObjects[currOBJ].alarm3 = 1;
                        if (allObjects[currOBJ].image_index < 5) {
                            for (int w = -4; w < 5; w++) {      
                                for (int h = -4; h < 5; h++) {
                                    for (int O : game_area[i + w][j + h].object_indexes) {
                                        switch (allObjects[O].my_id) {
                                        case bandit:
                                            if (allObjects[O].next_hurt < current_frame && is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position, bandit_hitbox, allObjects[currOBJ].direction)) {
                                                bandit_die(O, currOBJ, threadNUM);
                                            }
                                            break;
                                        case idpd_nade:
                                            if (is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position, 2, allObjects[currOBJ].direction)) {
                                                allObjects[O].direction = allObjects[currOBJ].direction;
                                                allObjects[O].speeddir = 12.0f;
                                                allObjects[O].alarm2 = 4;
                                                allObjects[O].friction = 0.0f;
                                                create_object(allObjects[O].position.x, allObjects[O].position.y, 0, 0, deflect, allObjects[currOBJ].direction * degreestoradians, 0);
                                            }
                                            
                                            break;
                                        case bullet1:
                                            if (allObjects[O].team != 1 && is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position, 3, allObjects[currOBJ].direction)) {
                                                allObjects[O].direction = allObjects[currOBJ].direction * degreestoradians + 180.0f;
                                                allObjects[O].speed.x = cos(allObjects[currOBJ].direction) * 4.0f;
                                                allObjects[O].speed.y = sin(allObjects[currOBJ].direction) * 4.0f;
                                                allObjects[O].team = 1;
                                                create_object(allObjects[O].position.x, allObjects[O].position.y, 0, 0, deflect, allObjects[currOBJ].direction * degreestoradians, 0);
                                            }
                                            break;
                                        case bullet2:
                                            if (is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position, 3, allObjects[currOBJ].direction)) {
                                                destroy_bullet_2(O);
                                            }
                                            break;
                                        default:
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case objectID::debris:
                        bounce_in_wall(currOBJ);
                        allObjects[currOBJ].speeddir = allObjects[currOBJ].speeddir / 2;
                        break;
                    default:
                        break;
                    }
                }
                //check for bullets tunneling through corners
                if (game_area[i + 1][j + 1].my_grid_type == wall && game_area[i + 1][j].my_grid_type != wall && game_area[i][j + 1].my_grid_type != wall) {      //up left diagonal
                    for (int currOBJ : game_area[i][j + 1].object_indexes) {
                        if (allObjects[currOBJ].position.y - allObjects[currOBJ].speed.y < (j + 1) * 16 + 0.01f) {
                            object_tunnel_corner(currOBJ);
                        }
                    }
                    for (int currOBJ : game_area[i + 1][j].object_indexes) {
                        if (allObjects[currOBJ].position.y - allObjects[currOBJ].speed.y > (j + 1) * 16 - 0.01f) {
                            object_tunnel_corner(currOBJ);
                        }
                    }
                }
                if (game_area[i - 1][j + 1].my_grid_type == wall && game_area[i - 1][j].my_grid_type != wall && game_area[i][j + 1].my_grid_type != wall) {      //up right diagonal
                    for (int currOBJ : game_area[i][j + 1].object_indexes) {
                        if (allObjects[currOBJ].position.y - allObjects[currOBJ].speed.y < (j + 1) * 16 + 0.01f) {
                            object_tunnel_corner(currOBJ);
                        }
                    }
                    for (int currOBJ : game_area[i - 1][j].object_indexes) {
                        if (allObjects[currOBJ].position.y - allObjects[currOBJ].speed.y > (j + 1) * 16 - 0.01f) {
                            object_tunnel_corner(currOBJ);
                        }
                    }
                }
                break;
            case floor_tile:
                goto floor_logic;       //these work the same as explo tiles just with a different texture
                break;
            case exlpo_tile:        //ignore bullets on these tiles ie do logic with enemy to bullet not the other way around
                floor_logic:
                for (int currOBJ : game_area[i][j].object_indexes) {
                    switch (allObjects[currOBJ].my_id) {
                    case objectID::player:
                        //do collisons with everything
                        for (int w = -1; w < 2; w++) {
                            for (int h = -1; h < 2; h++) {
                                for (int O : game_area[i + w][j + h].object_indexes) {
                                    switch (allObjects[O].my_id) {
                                    case objectID::rad:
                                        if (abs(allObjects[O].position.x - allObjects[0].position.x) < 8 && abs(allObjects[O].position.y - allObjects[0].position.y) < 8) {
                                            allObjects[O].my_id = rad_destroy;
                                            allObjects[O].image_index = -1;
                                            allObjects[O].position.x -= allObjects[O].speed.x / 2;
                                            allObjects[O].position.y -= allObjects[O].speed.y / 2;
                                            player_rads++;
                                            play_sounds_this_frame_count[snd_rad_pickup_ID]++;
                                        }
                                        break;
                                    case objectID::ammo_pack:
                                        if (abs(allObjects[O].position.x - allObjects[0].position.x) < 8 && abs(allObjects[O].position.y - allObjects[0].position.y) < 8) {
                                            allObjects[O].my_id = nothing;
                                            //player pick up ammo
                                        }
                                        break;
                                    case objectID::bandit:
                                        diffx = allObjects[O].position.x - allObjects[currOBJ].position.x;
                                        diffy = allObjects[O].position.y - allObjects[currOBJ].position.y;
                                        if (abs(diffx) < 7 && abs(diffy) < 7) {
                                            tmpdir = atan2f(diffy, diffx) + 180.0f / degreestoradians;

                                            motion_add_dir(tmpdir, 0.5f, currOBJ);  //the bigger the enemy the more it pushes: speed = size * 0.5
                                        }
                                        break;
                                    }

                                }
                            }
                        }
                        break;
                    case objectID::bandit:
                        //bandit ai
                        if (allObjects[currOBJ].alarm1 < 0) {
                            //choose what to do
                            allObjects[currOBJ].alarm1 = 20 + rand() % 10;
                            if (has_line_of_sight(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y)) {    //game_area[i][j].has_line_of_sight
                                if (!is_within_circle(allObjects[currOBJ].position, allObjects[0].position, 48)) {
                                    if (rand() % 4 == 0) {  //shoot
                                        tmpdir = angle_to_player_radians(allObjects[currOBJ].position);
                                        tmpdir += random_360_radians() / 18.0f - (10.0f / degreestoradians);
                                        tempSpdx = cos(tmpdir) * 4.0f;
                                        tempSpdy = sin(tmpdir) * 4.0f;
                                        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, tempSpdx, tempSpdy, bullet1, tmpdir, threadNUM);
                                        play_sound_relative_to_player(snd_shoot_1_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
                                        allObjects[currOBJ].direction = tmpdir;
                                        allObjects[currOBJ].alarm1 = 20 + rand() % 5;
                                    }
                                    else {  //walk towards player
                                        allObjects[currOBJ].speeddir += 0.4f;
                                        allObjects[currOBJ].direction = angle_to_player_radians(allObjects[currOBJ].position) + random_180_radians() - (90.0f / degreestoradians);
                                        allObjects[currOBJ].walk_frames = 10 + rand() % 10;
                                    }
                                }
                                else {      //run away
                                    tmpdir = angle_to_player_radians(allObjects[currOBJ].position);
                                    tmpdir += 170.0f / degreestoradians + random_360_radians() / 18.0f;
                                    
                                    allObjects[currOBJ].speeddir += 0.4f;
                                    allObjects[currOBJ].walk_frames = 40 + rand() % 10;
                                    allObjects[currOBJ].direction = tmpdir;     //used for gun angle
                                    motion_add_dir(allObjects[currOBJ].direction, 0.4, currOBJ);
                                }
                            }
                            else if (rand() % 4 == 0) {      //move in radom direction if no line of sight
                                allObjects[currOBJ].direction = random_360_radians();
                                motion_add_dir(allObjects[currOBJ].direction, 0.4, currOBJ);

                                allObjects[currOBJ].walk_frames = 20 + rand() % 10;
                                allObjects[currOBJ].alarm1 = allObjects[currOBJ].walk_frames + 10 + rand() % 30;
                            }
                            allObjects[currOBJ].facing_right = cos(allObjects[currOBJ].direction) > 0;
                        }
                        for (int w = -1; w < 2; w++) {      //bandit collison
                            for (int h = -1; h < 2; h++) {
                                for (int O : game_area[i + w][j + h].object_indexes) {
                                    if (allObjects[currOBJ].my_hp > 0 && O != currOBJ) {
                                        switch (allObjects[O].my_id) {
                                        case objectID::bandit:
                                            diffx = allObjects[O].position.x - allObjects[currOBJ].position.x;
                                            diffy = allObjects[O].position.y - allObjects[currOBJ].position.y;
                                            if (abs(diffx) < 7 && abs(diffy) < 7) {
                                                tmpdir = atan2f(diffy, diffx) + 180.0f / degreestoradians;

                                                motion_add_dir(tmpdir, 1.0f, currOBJ);
                                            }
                                            break;
                                        case objectID::bullet1:       //getting hurt
                                            if (allObjects[O].team != 2 && is_within_circle(allObjects[O].position, allObjects[currOBJ].position, 10)) {
                                                destroy_bullet_1(O);
                                                allObjects[currOBJ].my_hp -= 3;
                                                if (allObjects[currOBJ].my_hp > 0) {
                                                    bandit_hurt(currOBJ, O);
                                                }
                                                else {  //dead
                                                    bandit_die(currOBJ, O, threadNUM);
                                                }
                                            }
                                            break;
                                        case objectID::player_bullet:       //getting hurt
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, 10)) {
                                                destroy_player_bullet(O);
                                                allObjects[currOBJ].my_hp -= 3;
                                                if (allObjects[currOBJ].my_hp > 0) {
                                                    bandit_hurt(currOBJ, O);
                                                }
                                                else {  //dead
                                                    bandit_die(currOBJ, O, threadNUM);
                                                }
                                            }
                                            break;
                                        case objectID::horror_bullet:       //getting hurt
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, 10)) {
                                                destroy_horror_bullet(O);
                                                allObjects[currOBJ].my_hp -= 1;
                                                if (allObjects[currOBJ].my_hp > 0) {
                                                    bandit_hurt(currOBJ, O);
                                                    allObjects[currOBJ].rad_drop++;
                                                }
                                                else {  //dead
                                                    bandit_die(currOBJ, O, threadNUM);
                                                }
                                            }
                                            break;
                                        case objectID::bandit_corpse:
                                            if (allObjects[O].speeddir > 1.0f && allObjects[currOBJ].next_hurt < current_frame) {
                                                if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, 7)) {
                                                    allObjects[currOBJ].my_hp -= 1 + impact_wrists;
                                                    if (allObjects[currOBJ].my_hp > 0) {
                                                        bandit_hurt(currOBJ, O);
                                                    }
                                                    else {  //dead
                                                        bandit_die(currOBJ, O, threadNUM);
                                                    }
                                                    allObjects[O].speeddir *= 0.5f;
                                                }
                                            }
                                            break;
                                        case objectID::debris:
                                            if (allObjects[O].speeddir > 1.0f && allObjects[currOBJ].next_hurt < current_frame) {
                                                if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, 6)) {
                                                    allObjects[currOBJ].my_hp -= 1;
                                                    if (allObjects[currOBJ].my_hp > 0) {
                                                        bandit_hurt(currOBJ, O);
                                                    }
                                                    else {  //dead
                                                        bandit_die(currOBJ, O, threadNUM);
                                                    }
                                                    allObjects[O].speeddir *= 0.5f;
                                                }
                                            }
                                            break;
                                        default:
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case horror_bullet:
                        for (int w = -1; w < 2; w++) {      //horror_bullet collison
                            for (int h = -1; h < 2; h++) {
                                for (int O : game_area[i + w][j + h].object_indexes) {
                                    //destroy projectiles
                                    if (allObjects[currOBJ].my_id != horror_bullet) {
                                        break;
                                    }
                                    switch (allObjects[O].my_id) {
                                    case bullet1:
                                        if (allObjects[O].team != 1 && is_within_circle(allObjects[currOBJ].position, allObjects[O].position, 10)) {
                                            destroy_horror_bullet(currOBJ);
                                            destroy_bullet_1(O);
                                        }
                                        break;
                                    case bullet2:
                                        if (is_within_circle(allObjects[currOBJ].position, allObjects[O].position, 10)) {
                                            destroy_horror_bullet(currOBJ);
                                            destroy_bullet_2(O);
                                        }
                                        break;
                                    case idpd_nade:
                                        if (is_within_circle(allObjects[currOBJ].position, allObjects[O].position, 6)) {
                                            destroy_horror_bullet(currOBJ);
                                            detonate_IDPD_nade(O, -1);
                                        }
                                        break;
                                    default:
                                        break;
                                    }
                                }
                            }
                        }
                        break;
                    case plasma_huge:
                        plasma_huge_collison(currOBJ, i, j);
                        break;
                    case plasma_big:
                        plasma_big_collison(currOBJ, i, j);
                        break;
                    case plasma:
                        plasma_collision(currOBJ, i, j);
                        break;
                    case plasma_impact:
                        if (allObjects[currOBJ].image_index == 3 || allObjects[currOBJ].image_index == 4) {
                            for (int w = -3; w < 4; w++) {
                                for (int h = -3; h < 4; h++) {
                                    for (int O : game_area[i + w][j + h].object_indexes) {
                                        switch (allObjects[O].my_id) {
                                        case bandit:
                                            if (allObjects[O].next_hurt < current_frame && is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (bandit_hitbox + 32))) {
                                                allObjects[O].my_hp -= 10;
                                                tmpdir = atan2f(allObjects[currOBJ].position.y - allObjects[O].position.y, allObjects[currOBJ].position.x - allObjects[O].position.x);
                                                allObjects[currOBJ].speed.x = cos(tmpdir) * 8;
                                                allObjects[currOBJ].speed.y = sin(tmpdir) * 8; //this is so the bandit_hurt() function works with kb
                                                if (allObjects[O].my_hp > 0) {
                                                    bandit_hurt(O, currOBJ);
                                                }
                                                else {  //dead
                                                    bandit_die(O, currOBJ, threadNUM);
                                                }

                                            }
                                            break;
                                        default:
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case ultra_slash:
                        if (allObjects[currOBJ].image_index < 5) {
                            for (int w = -4; w < 5; w++) {
                                for (int h = -4; h < 5; h++) {
                                    if (game_area[i + w][j + h].my_grid_type == wall && is_within_circle(sf::Vector2f(((i + w) * 16) + 8, ((j + h) * 16) + 8), allObjects[currOBJ].position, (wall_hitbox + 24))) {
                                        allObjects[currOBJ].alarm3 = 1;
                                    }
                                    for (int O : game_area[i + w][j + h].object_indexes) {
                                        switch (allObjects[O].my_id) {
                                        case bandit:
                                            if (allObjects[O].next_hurt < current_frame && is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position, bandit_hitbox, allObjects[currOBJ].direction)) {
                                                allObjects[currOBJ].speed.x *= 2.0f;
                                                allObjects[currOBJ].speed.y *= 2.0f;
                                                bandit_die(O, currOBJ, threadNUM);
                                                allObjects[currOBJ].speed.x *= 0.5f;
                                                allObjects[currOBJ].speed.y *= 0.5f;
                                            }
                                            break;
                                        case idpd_nade:
                                            if (is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position, 2, allObjects[currOBJ].direction)) {
                                                allObjects[O].direction = allObjects[currOBJ].direction;
                                                allObjects[O].speeddir = 12.0f;
                                                allObjects[O].alarm2 = 4;
                                                allObjects[O].friction = 0.0f;
                                                create_object(allObjects[O].position.x, allObjects[O].position.y, 0, 0, deflect, allObjects[currOBJ].direction * degreestoradians, 0);
                                            }
                                            break;
                                        case bullet1:
                                            if (allObjects[O].team != 1 && is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position, 3, allObjects[currOBJ].direction)) {
                                                allObjects[O].direction = allObjects[currOBJ].direction * degreestoradians + 180.0f;
                                                allObjects[O].speed.x = cos(allObjects[currOBJ].direction) * 4.0f;
                                                allObjects[O].speed.y = sin(allObjects[currOBJ].direction) * 4.0f;
                                                allObjects[O].team = 1;
                                                create_object(allObjects[O].position.x, allObjects[O].position.y, 0, 0, deflect, allObjects[currOBJ].direction * degreestoradians, 0);
                                            }
                                            break;
                                        case bullet2:
                                            if (is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position, 3, allObjects[currOBJ].direction)) {
                                                destroy_bullet_2(O);
                                            }
                                            break;
                                        default:
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case idpd_explosion:
                        if (allObjects[currOBJ].image_index == 3 || allObjects[currOBJ].image_index == 4) {
                            for (int w = -6; w < 7; w++) {      
                                for (int h = -6; h < 7; h++) {
                                    //destroy wall
                                    if (game_area[i + w][j + h].my_grid_type == wall && is_within_circle(sf::Vector2f(((i + w) * 16) + 8, ((j + h) * 16) + 8), allObjects[currOBJ].position, (wall_hitbox + 48))) {
                                        create_explo_tile(i + w, j + h);
                                    }
                                    for (int O : game_area[i + w][j + h].object_indexes) {
                                        switch (allObjects[O].my_id) {
                                        case idpd_explosion:
                                            if ((allObjects[O].image_index == 3 || allObjects[O].image_index == 4) &&
                                                is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (48 + 48))) {

                                                tmpdir = atan2f(allObjects[currOBJ].position.y - allObjects[O].position.y, allObjects[currOBJ].position.x - allObjects[O].position.x);
                                                allObjects[currOBJ].position.x += cos(tmpdir) * 4;
                                                allObjects[currOBJ].position.y += sin(tmpdir) * 4;

                                                allObjects[O].position.x -= cos(tmpdir) * 4;
                                                allObjects[O].position.y -= sin(tmpdir) * 4;
                                                //moving both should have more predictable results
                                                //not broken like the official version
                                            }
                                            break;
                                        case idpd_nade:
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (2 + 48))) {
                                                detonate_IDPD_nade(O, -1);
                                            }
                                            break;
                                        case bandit:
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (bandit_hitbox + 48))) {
                                                allObjects[O].my_hp -= 8;
                                                tmpdir = atan2f(allObjects[currOBJ].position.y - allObjects[O].position.y, allObjects[currOBJ].position.x - allObjects[O].position.x);
                                                allObjects[currOBJ].speed.x = cos(tmpdir) * 12;
                                                allObjects[currOBJ].speed.y = sin(tmpdir) * 12; //this is so the bandit_hurt() function works
                                                if (allObjects[O].my_hp > 0) {
                                                    bandit_hurt(O, currOBJ);
                                                }
                                                else {  //dead
                                                    bandit_die(O, currOBJ, threadNUM);
                                                }
                                                
                                            }
                                            break;
                                        case plasma_huge:
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (allObjects[O].scale * plasma_hitbox + 48))) {
                                                plasma_huge_destroy(O, i + w, j + h);
                                            }
                                            break;
                                        case plasma_big:
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (allObjects[O].scale * plasma_hitbox + 48))) {
                                                plasma_big_destroy(O, i + w, j + h);
                                            }
                                            break;
                                        case plasma:
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (allObjects[O].scale * plasma_hitbox + 48))) {
                                                //turn into plasma explosion
                                                destroy_plasma(O, -1);
                                            }
                                            break;
                                        case bullet1:
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (3 + 48))) {
                                                destroy_bullet_1(O);
                                            }
                                            break;
                                        case bullet2:
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (3 + 48))) {
                                                destroy_bullet_2(O);
                                            }
                                            break;
                                        case horror_bullet:
                                            if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (3 + 48))) {
                                                destroy_horror_bullet(O);
                                            }
                                            break;
                                        default:
                                            break;
                                        }
                                    }
                                }
                            }
                        }
                        break;
                    case debris:
                        //do this here so random functions work
                        if (allObjects[currOBJ].alarm1 < 1) {
                            create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
                            allObjects[currOBJ].my_id = nothing;
                        }
                        if (allObjects[currOBJ].alarm2 < 1) {
                            create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
                            allObjects[currOBJ].alarm2 = round(((rand() % 20) / allObjects[currOBJ].speeddir) + 1);
                        }
                        break;
                    default:
                        break;
                    }
                }
                break;
            default:
                break;
            }
        }
    }
}

int generate_2x2_tile(int x, int y, int nub_chance, bool Btile) {  //x, y is the top left corner
    int removedwalls = 0;
    bool adjacent_nub = false;
    for (int i = -2; i <= 2; i += 2) {
        for (int j = -2; j <= 2; j += 2) {
            if (!(game_area[x + i][y + j].my_grid_type == floor_tile &&
                  game_area[x + i + 1][y + j + 1].my_grid_type == floor_tile &&
                  game_area[x + i + 1][y + j].my_grid_type == floor_tile &&
                  game_area[x + i][y + j + 1].my_grid_type == floor_tile)
                &&
                !(game_area[x + i][y + j].my_grid_type == wall &&
                  game_area[x + i + 1][y + j + 1].my_grid_type == wall &&
                  game_area[x + i + 1][y + j].my_grid_type == wall &&
                  game_area[x + i][y + j + 1].my_grid_type == wall)) {
                adjacent_nub = true;
            }
        }
    }
    if (adjacent_nub) {
        removedwalls += game_area[x][y].my_grid_type == wall;
        create_floor(x, y, Btile);

        removedwalls += game_area[x + 1][y + 1].my_grid_type == wall;
        create_floor(x + 1, y + 1, Btile);

        removedwalls += game_area[x + 1][y].my_grid_type == wall;
        create_floor(x + 1, y, Btile);

        removedwalls += game_area[x][y + 1].my_grid_type == wall;
        create_floor(x, y + 1, Btile);
    }
    else {
        int choice = rand() % 4;
        if (choice != 0) {
            removedwalls += game_area[x][y].my_grid_type == wall;
            create_floor(x, y, Btile);
        }
        if (choice != 1) {
            removedwalls += game_area[x + 1][y + 1].my_grid_type == wall;
            create_floor(x + 1, y + 1, Btile);
        }
        if (choice != 2) {
            removedwalls += game_area[x + 1][y].my_grid_type == wall;
            create_floor(x + 1, y, Btile);
        }
        if (choice != 3) {
            removedwalls += game_area[x][y + 1].my_grid_type == wall;
            create_floor(x, y + 1, Btile);
        }
    }

    if (removedwalls > 1) {
        allFloors[gen_curr_floor_index].setPosition(x * 16, y * 16);
        int choice = rand() % 9 + 1;
        if (choice > 2) {
            choice = 0;
        }
        if (rand() % 50 == 0 && removedwalls == 4) {
            choice = 3;
        }
        if (choice == 2 && Btile && removedwalls != 4) {
            choice = 1;
        }
        allFloors[gen_curr_floor_index].setOrigin(0, choice + 4 * Btile);
        gen_curr_floor_index++;
    }
    return removedwalls;
}

void generate_level() {
    //reset area
    for (int i = left_physics - 2; i <= right_physics + 2; i++) {
        for (int j = top_physics - 2; j <= bottom_physics + 2; j++) {
            game_area[i][j].my_grid_type = wall;
        }
    }
    //reset objects
    for (int i = 1; i < max_objects; i++) {
        allObjects[i].my_id = nothing;
    }
    //reset floors
    for (int i = 1; i < max_floors; i++) {
        allFloors[i].setPosition(0, 0);
    }
    vector2D_reset(top_physics, bottom_physics, left_physics, right_physics);

    level_generator level_generators[255];
    int generators_active = 0;

    gen_curr_floor_index = 0;

    //first floor tile
    allFloors[gen_curr_floor_index].setPosition(24000, 24000);
    gen_curr_floor_index++;


    allObjects[0].position = { 24016.0f, 24016.0f };
    int initial_goal = 480;
    int goal = initial_goal;
    int safe_dist = 0;
    top_physics = 1500;
    bottom_physics = 1501;
    left_physics = 1500;
    right_physics = 1501;
    game_area[1500][1500].my_grid_type = floor_tile;
    game_area[1500][1501].my_grid_type = floor_tile;
    game_area[1501][1500].my_grid_type = floor_tile;
    game_area[1501][1501].my_grid_type = floor_tile;
    goal -= 4;  //starting 4 tiles
    level_generators[0].x = 1500;
    level_generators[0].y = 1500;
    level_generators[0].spdx = 0;
    level_generators[0].spdy = 0;

    level_generators[0].active = true;
    generators_active++;

    int biasx = ((rand() % 2) * 2 - 1) * 2;
    int biasy = ((rand() % 2) * 2 - 1) * 2;
    int extra = 0;
    int turn = 0;
    level_generators[0].spdx = rand() % 2;
    if (level_generators[0].spdx == 1) {
        level_generators[0].spdx = (rand() % 2) * 2 - 1;
        level_generators[0].spdy = 0;
    }
    else {
        level_generators[0].spdy = (rand() % 2) * 2 - 1;
    }
    if (area == 1) {
        while (goal > 0) {
            for (int i = 0; i < 254; i++) {
                if (level_generators[i].active) {
                    if (goal < initial_goal - safe_dist) {
                        if (rand() % (19 + generators_active) > 20) {
                            level_generators[i].active = false;
                            generators_active--;
                        }
                        if (rand() % 8 == 0) {
                            for (int b = 0; b < 254; b++) {
                                if (level_generators[b].active == false) {
                                    level_generators[b].active = true;
                                    level_generators[b].Btile = rand() % 7 == 0;
                                    level_generators[b].x = level_generators[i].x;
                                    level_generators[b].y = level_generators[i].y;
                                    level_generators[b].spdx = rand() % 2;
                                    if (level_generators[b].spdx == 1) {
                                        level_generators[b].spdx = (rand() % 2) * 2 - 1;
                                        level_generators[b].spdy = 0;
                                    }
                                    else {
                                        level_generators[b].spdy = (rand() % 2) * 2 - 1;
                                    }
                                    generators_active++;
                                    break;
                                }
                            }
                        }
                        //turn = choose(0, 0, 0, 0, 0, 0, 0, 0, 0, 90, -90, 90, -90, 180);
                        int choice = rand() % 14;
                        if (choice < 9) {
                            //turn = 0;
                        }
                        else if (choice < 13) {
                            //turn = (rand() % 2) * 2 - 1;
                            //turn *= 90;
                            if (level_generators[i].spdx != 0) {
                                level_generators[i].spdx = 0;
                                level_generators[i].spdy = (rand() % 2) * 2 - 1;
                            }
                            else {
                                level_generators[i].spdy = 0;
                                level_generators[i].spdx = (rand() % 2) * 2 - 1;
                            }
                        }
                        else {
                            //turn = 180;
                            level_generators[i].spdx *= -1;
                            level_generators[i].spdy *= -1;
                        }
                    }

                    level_generators[i].x += level_generators[i].spdx * 2;
                    level_generators[i].y += level_generators[i].spdy * 2;
                    if (rand() % 2) {   //clear out bigger area
                        goal -= generate_2x2_tile(level_generators[i].x + biasx, level_generators[i].y + biasy, 1, level_generators[i].Btile);
                        goal -= generate_2x2_tile(level_generators[i].x + biasx, level_generators[i].y, 1, level_generators[i].Btile);
                        goal -= generate_2x2_tile(level_generators[i].x, level_generators[i].y + biasy, 1, level_generators[i].Btile);
                    }
                    goal -= generate_2x2_tile(level_generators[i].x, level_generators[i].y, 1, level_generators[i].Btile);
                }
            }
        }
        //generate enemies
        int tmp_num_of_enemies_to_spawn = 1;
        int enemy_choice = 0;
        if (sub_area == 1) {
            for (int i = left_physics; i <= right_physics; i++) {
                for (int j = top_physics; j <= bottom_physics; j++) {
                    if(game_area[i][j].my_grid_type == floor_tile && !is_within_circle(sf::Vector2f(24016, 24016), sf::Vector2f( i * 16 + 8 , j * 16 + 8 ), 100)) {
                        if (rand() % 4 == 0) {   //spawn enemy
                            if (rand() % 2) {   //cluster spawn
                                tmp_num_of_enemies_to_spawn = (90 / (1 + (200 * pow(e_constant, -0.3f * LOOPS))));    //logistic growth so the enemy count caps out at about l30, but keeps general growth in early loops
                            }
                            else {              //single spawn
                                tmp_num_of_enemies_to_spawn = 1;
                            }
                        }
                        else {
                            tmp_num_of_enemies_to_spawn = 0;
                        }
                        enemy_choice = rand() % 9;
                        for (int r = 0; r < tmp_num_of_enemies_to_spawn; r++) {
                            if (enemy_choice < 10) { //bandit
                                float rand_off_x = random_360_radians() - 3.14f;
                                float rand_off_y = random_360_radians() - 3.14f;
                                create_object(i * 16 + 8 + rand_off_x, j * 16 + 8 + rand_off_y, 0, 0, bandit, 0, 0);
                            }
                        }
                    }
                }
            }
        }
        if (sub_area == 2) {

        }
        if (sub_area == 3) {

        }
        //clear out area around player
        for (int i = 1499; i < 1503; i++) {
            for (int j = 1499; j < 1503; j++) {
                if (game_area[i][j].my_grid_type == wall) {
                    create_explo_tile(i, j);
                    //create debris too
                }
            }
        }
    }
}


//no debug window
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

sf::Image game_icon;

int main()
{
    //sounds
    play_sounds_this_frame_pos.reserve(255);
    play_sounds_this_frame_count.reserve(255);

    sf::Sound snd_shoot_1;
    sf::SoundBuffer snd_shoot_1_buff;

    sf::Sound snd_horror_portal;
    sf::SoundBuffer snd_horror_portal_buff;
    sf::Sound snd_horror_portal_pan;
    sf::SoundBuffer snd_horror_portal_pan_buff;

    sf::Sound snd_bandit_hurt;
    sf::SoundBuffer snd_bandit_hurt_buff;
    sf::Sound snd_bandit_die;
    sf::SoundBuffer snd_bandit_die_buff;

    sf::Sound snd_rad_pickup;
    sf::SoundBuffer snd_rad_pickup_buff;

    sf::Sound snd_horror_beam_start;
    sf::SoundBuffer snd_horror_beam_start_buff;
    sf::Sound snd_horror_beam_hold;
    sf::SoundBuffer snd_horror_beam_hold_buff;

    sf::Sound snd_hit_wall;
    sf::SoundBuffer snd_hit_wall_buff;

    sf::Sound snd_wall_break_rock;
    sf::SoundBuffer snd_wall_break_rock_buff;

    sf::Sound snd_IDPD_explosion;
    sf::SoundBuffer snd_IDPD_explosion_buff;

    sf::Sound snd_plasma_hit;
    sf::SoundBuffer snd_plasma_hit_buff;

    sf::Sound snd_ultra_shovel;
    sf::SoundBuffer snd_ultra_shovel_buff;

    sf::Sound snd_plasma_huge;
    sf::SoundBuffer snd_plasma_huge_buff;

    sf::Sound snd_plasma_huge_upgrade;
    sf::SoundBuffer snd_plasma_huge_upgrade_buff;

    sf::Sound snd_plasma_split;
    sf::SoundBuffer snd_plasma_split_buff;

    sf::Sound snd_plasma_split_upgrade;
    sf::SoundBuffer snd_plasma_split_upgrade_buff;

    sf::Sound snd_hammer_swap;
    sf::SoundBuffer snd_hammer_swap_buff;

    sf::Sound snd_energy_swap;
    sf::SoundBuffer snd_energy_swap_buff;

    sf::Sound snd_explosion;
    sf::SoundBuffer snd_explosion_buff;
    
    if (!snd_shoot_1_buff.loadFromFile("snd/shoot_1.wav")) {
        return -1;
    }
    snd_shoot_1.setBuffer(snd_shoot_1_buff);
    snd_shoot_1.setAttenuation(0.015f);
    snd_shoot_1.setVolume(100.0f);

    if (!snd_horror_portal_buff.loadFromFile("snd/horror_portal.wav")) {
        return -1;
    }
    snd_horror_portal.setBuffer(snd_horror_portal_buff);

    if (!snd_horror_portal_pan_buff.loadFromFile("snd/horror_portal_pan.wav")) {
        return -1;
    }
    snd_horror_portal_pan.setBuffer(snd_horror_portal_pan_buff);
    snd_horror_portal_pan.setAttenuation(0.005f);

    if (!snd_bandit_hurt_buff.loadFromFile("snd/bandit_hurt.wav")) {
        return -1;
    }
    snd_bandit_hurt.setBuffer(snd_bandit_hurt_buff);
    snd_bandit_hurt.setAttenuation(0.04f);
    snd_bandit_hurt.setVolume(100.0f);

    if (!snd_bandit_die_buff.loadFromFile("snd/bandit_die.wav")) {
        return -1;
    }
    snd_bandit_die.setBuffer(snd_bandit_die_buff);
    snd_bandit_die.setAttenuation(0.04f);
    snd_bandit_die.setVolume(100.0f);

    if (!snd_rad_pickup_buff.loadFromFile("snd/rad_pickup.wav")) {
        return -1;
    }
    snd_rad_pickup.setBuffer(snd_rad_pickup_buff);
    snd_rad_pickup.setVolume(70.0f);

    if (!snd_horror_beam_start_buff.loadFromFile("snd/horror_beam_start.wav")) {
        return -1;
    }
    snd_horror_beam_start.setBuffer(snd_horror_beam_start_buff);
    snd_horror_beam_start.setVolume(70.0f);

    if (!snd_horror_beam_hold_buff.loadFromFile("snd/horror_beam_hold.wav")) {
        return -1;
    }
    snd_horror_beam_hold.setBuffer(snd_horror_beam_hold_buff);

    //walls
    if (!snd_hit_wall_buff.loadFromFile("snd/hit_wall.wav")) {
        return -1;
    }
    snd_hit_wall.setBuffer(snd_hit_wall_buff);
    snd_hit_wall.setAttenuation(0.02f);
    snd_hit_wall.setVolume(100.0f);

    if (!snd_wall_break_rock_buff.loadFromFile("snd/wall_break_rock.wav")) {
        return -1;
    }
    snd_wall_break_rock.setBuffer(snd_wall_break_rock_buff);
    snd_wall_break_rock.setAttenuation(0.005f);
    snd_wall_break_rock.setVolume(100.0f);

    //explosions
    if (!snd_IDPD_explosion_buff.loadFromFile("snd/IDPD_explosion.wav")) {
        return -1;
    }
    snd_IDPD_explosion.setBuffer(snd_IDPD_explosion_buff);
    snd_IDPD_explosion.setAttenuation(0.01f);
    snd_IDPD_explosion.setVolume(100.0f);

    if (!snd_explosion_buff.loadFromFile("snd/explosion.wav")) {
        return -1;
    }
    snd_explosion.setBuffer(snd_explosion_buff);
    snd_explosion.setAttenuation(0.005f);
    snd_explosion.setVolume(100.0f);
    
    //plasma
    if (!snd_plasma_hit_buff.loadFromFile("snd/plasma_hit.wav")) {
        return -1;
    }
    snd_plasma_hit.setBuffer(snd_plasma_hit_buff);
    snd_plasma_hit.setAttenuation(0.02f);
    snd_plasma_hit.setVolume(100.0f);

    //ushov
    if (!snd_ultra_shovel_buff.loadFromFile("snd/ultra_shovel.wav")) {
        return -1;
    }
    snd_ultra_shovel.setBuffer(snd_ultra_shovel_buff);
    snd_ultra_shovel.setVolume(100.0f);

    if (!snd_plasma_huge_buff.loadFromFile("snd/plasma_huge.wav")) {
        return -1;
    }
    snd_plasma_huge.setBuffer(snd_plasma_huge_buff);
    snd_plasma_huge.setVolume(100.0f);

    if (!snd_plasma_huge_upgrade_buff.loadFromFile("snd/plasma_huge_upgrade.wav")) {
        return -1;
    }
    snd_plasma_huge_upgrade.setBuffer(snd_plasma_huge_upgrade_buff);
    snd_plasma_huge_upgrade.setVolume(100.0f);

    if (!snd_plasma_split_buff.loadFromFile("snd/plasma_split.wav")) {
        return -1;
    }
    snd_plasma_split.setBuffer(snd_plasma_split_buff);
    snd_plasma_split.setAttenuation(0.01f);
    snd_plasma_split.setVolume(100.0f);

    if (!snd_plasma_split_upgrade_buff.loadFromFile("snd/plasma_split_upgrade.wav")) {
        return -1;
    }
    snd_plasma_split_upgrade.setBuffer(snd_plasma_split_upgrade_buff);
    snd_plasma_split_upgrade.setAttenuation(0.01f);
    snd_plasma_split_upgrade.setVolume(100.0f);

    if (!snd_hammer_swap_buff.loadFromFile("snd/hammer_swap.wav")) {
        return -1;
    }
    snd_hammer_swap.setBuffer(snd_hammer_swap_buff);
    snd_hammer_swap.setVolume(100.0f);

    if (!snd_energy_swap_buff.loadFromFile("snd/energy_swap.wav")) {
        return -1;
    }
    snd_energy_swap.setBuffer(snd_energy_swap_buff);
    snd_energy_swap.setVolume(100.0f);

    sf::Sound snd_nade_hit_wall;
    sf::SoundBuffer snd_nade_hit_wall_buff;
    if (!snd_nade_hit_wall_buff.loadFromFile("snd/nade_hit_wall.wav")) {
        return -1;
    }
    snd_nade_hit_wall.setBuffer(snd_nade_hit_wall_buff);
    snd_nade_hit_wall.setAttenuation(0.01f);
    snd_nade_hit_wall.setVolume(100.0f);

    sf::Sound snd_IDPD_nade_load;
    sf::SoundBuffer snd_IDPD_nade_load_buff;
    if (!snd_IDPD_nade_load_buff.loadFromFile("snd/IDPD_nade_load.wav")) {
        return -1;
    }
    snd_IDPD_nade_load.setBuffer(snd_IDPD_nade_load_buff);
    snd_IDPD_nade_load.setAttenuation(0.01f);
    snd_IDPD_nade_load.setVolume(100.0f);

    sf::Sound snd_IDPD_nade_almost;
    sf::SoundBuffer snd_IDPD_nade_almost_buff;
    if (!snd_IDPD_nade_almost_buff.loadFromFile("snd/IDPD_nade_almost.wav")) {
        return -1;
    }
    snd_IDPD_nade_almost.setBuffer(snd_IDPD_nade_almost_buff);
    snd_IDPD_nade_almost.setAttenuation(0.01f);
    snd_IDPD_nade_almost.setVolume(100.0f);


    //music
    sf::Music mus1;
    mus1.openFromFile("mus/mus1.ogg");
    mus1.setVolume(50.0f);
    //mus1.play();
    mus1.setLoop(true);

    

    auto window = sf::RenderWindow({ (u_int)window_size_x, (u_int)window_size_y }, "Nuclear Throne Arranged", 4U);
    window.setFramerateLimit(MAXFPS);

    game_icon.loadFromFile("res/NT icon arranged.png");
    window.setIcon(32, 32, game_icon.getPixelsPtr());

    sf::View myView(sf::Vector2f(160, 120), sf::Vector2f(320, 240));
    window.setView(myView);

     //sprites drawn over shadows
    sf::RenderTexture buffer_under;
    buffer_under.create(320, 240);
    sf::Sprite buffer_underSprite(buffer_under.getTexture());

    //shadows
    sf::RenderTexture shadows;
    shadows.create(320, 240);
    sf::Sprite bufferShadows(shadows.getTexture());

    //sprites drawn under shadows
    sf::RenderTexture buffer_over;
    buffer_over.create(320, 240);
    sf::Sprite buffer_overSprite(buffer_over.getTexture());

    gameObject player;
    sf::Vector2f cameraPos = { 24000.0f, 24000.0f };
    int cameraBoundsTop = 0;
    int cameraBoundsBottom = 10;
    int cameraBoundsLeft = 0;
    int cameraBoundsRight = 10;
    //player.position = { gridSize * 8.0f + 50.0f, gridSize * 8.0f - 3.0f };
    //player.position = { gridSize * 16.0f, gridSize * 16.0f };
    player.position = { 24008.0f, 24008.0f };
    player.speed = { 0.0f, 0.0f };
    player.my_id = objectID::player;

    //fps
    sf::Clock clock;
    float fps = 0.0f;

    srand(std::time(NULL));
    //uncomment if you want set seed
    //srand(0);
    
    //player_sprite
    player_sprite.setOrigin(24,24);


    //load sprites
        sf::Texture allEnemySprites;
        allEnemySprites.loadFromFile("res/enemies/all_enemies.png");

        sf::Texture allSmallEffectSprites;
        allSmallEffectSprites.loadFromFile("res/allSmallEffects.png");
        sf::Texture allMediumEffectSprites;
        allMediumEffectSprites.loadFromFile("res/allMediumEffects.png");
        sf::Texture allBigEffectSprites;
        allBigEffectSprites.loadFromFile("res/allBigEffects.png");

        //middleWall1
        sf::Texture middleWall1;
        middleWall1.loadFromFile("res/sprWall1Top_1.png");
        sf::VertexArray draw_middlewall1s = create_vertex_array(middleWall1, 164);     //4 * 164, where 164 is the max amount of walls that can be drawn, could be lower since only 1/4 of the walls should be a specific sprite

        //middleWall2
        sf::Texture middleWall2;
        middleWall2.loadFromFile("res/sprWall1Top_2.png");
        sf::VertexArray draw_middlewall2s = create_vertex_array(middleWall2, 164);     //4 * 164, where 164 is the max amount of walls that can be drawn

        //middleWall3
        sf::Texture middleWall3;
        middleWall3.loadFromFile("res/sprWall1Top_3.png");
        sf::VertexArray draw_middlewall3s = create_vertex_array(middleWall3, 164);     //4 * 164, where 164 is the max amount of walls that can be drawn

        //middleWall4
        sf::Texture middleWall4;
        middleWall4.loadFromFile("res/sprWall1Top_4.png");
        sf::VertexArray draw_middlewall4s = create_vertex_array(middleWall4, 164);     //4 * 164, where 164 is the max amount of walls that can be drawn


        //botWall1
        sf::Texture botWall1;
        botWall1.loadFromFile("res/sprWall1Bot_1.png");
        sf::VertexArray draw_botwall1s = create_vertex_array(botWall1, 40);

        //botWall2
        sf::Texture botWall2;
        botWall2.loadFromFile("res/sprWall1Bot_2.png");
        sf::VertexArray draw_botwall2s = create_vertex_array(botWall2, 40);

        //botWall3
        sf::Texture botWall3;
        botWall3.loadFromFile("res/sprWall1Bot_3.png");
        sf::VertexArray draw_botwall3s = create_vertex_array(botWall3, 40);

        //botWall4
        sf::Texture botWall4;
        botWall4.loadFromFile("res/sprWall1Bot_4.png");
        sf::VertexArray draw_botwall4s = create_vertex_array(botWall4, 40);


        sf::Texture boarderWall;
        boarderWall.loadFromFile("res/sprWall1Boarder.png");
        sf::VertexArray draw_boarderWalls = create_vertex_array(boarderWall, 600);

        //wall1 shadow
        sf::Texture Wall1shadow;
        Wall1shadow.loadFromFile("res/sprWall1shadow.png");
        sf::VertexArray draw_Wall1shadows = create_vertex_array(Wall1shadow, 600);

        //floorTile1
        sf::Texture floorTile1;
        floorTile1.loadFromFile("res/sprFloor1_1.png");
        sf::VertexArray draw_floorTile1s = create_vertex_array(floorTile1, 200);

        //floorTile2
        sf::Texture floorTile2;
        floorTile2.loadFromFile("res/sprFloor1_2.png");
        sf::VertexArray draw_floorTile2s = create_vertex_array(floorTile2, 40);

        //floorTile3
        sf::Texture floorTile3;
        floorTile3.loadFromFile("res/sprFloor1_3.png");
        sf::VertexArray draw_floorTile3s = create_vertex_array(floorTile3, 40);

        //floorTile4
        sf::Texture floorTile4;
        floorTile4.loadFromFile("res/sprFloor1_4.png");
        sf::VertexArray draw_floorTile4s = create_vertex_array(floorTile4, 20);

        //floorTile1B
        sf::Texture floorTile1B;
        floorTile1B.loadFromFile("res/sprFloor1_1B.png");
        sf::VertexArray draw_floorTile1Bs = create_vertex_array(floorTile1B, 200);

        //floorTile2B
        sf::Texture floorTile2B;
        floorTile2B.loadFromFile("res/sprFloor1_2B.png");
        sf::VertexArray draw_floorTile2Bs = create_vertex_array(floorTile2B, 40);

        //floorTile3B
        sf::Texture floorTile3B;
        floorTile3B.loadFromFile("res/sprFloor1_3B.png");
        sf::VertexArray draw_floorTile3Bs = create_vertex_array(floorTile3B, 40);

        //floorTile4B
        sf::Texture floorTile4B;
        floorTile4B.loadFromFile("res/sprFloor1_4B.png");
        sf::VertexArray draw_floorTile4Bs = create_vertex_array(floorTile4B, 20);


        //exploTile1
        sf::Texture exploTile1;
        exploTile1.loadFromFile("res/sprExploTile1.png");
        sf::VertexArray draw_exploTile1s = create_vertex_array(exploTile1, 320);     

        //exploTile2
        sf::Texture exploTile2;
        exploTile2.loadFromFile("res/sprExploTile2.png");
        sf::VertexArray draw_exploTile2s = create_vertex_array(exploTile2, 320);     

        //exploTile3
        sf::Texture exploTile3;
        exploTile3.loadFromFile("res/sprExploTile3.png");
        sf::VertexArray draw_exploTile3s = create_vertex_array(exploTile3, 320);    

        //exploTile4
        sf::Texture exploTile4;
        exploTile4.loadFromFile("res/sprExploTile4.png");
        sf::VertexArray draw_exploTile4s = create_vertex_array(exploTile4, 320);     



        //floorTile1 under
        sf::Texture floorTile1_under;
        floorTile1_under.loadFromFile("res/sprFloor1_1_under.png");
        sf::VertexArray draw_floorTile1_unders = create_vertex_array(floorTile1_under, 210);
        //floorTile1B under
        sf::Texture floorTile1B_under;
        floorTile1B_under.loadFromFile("res/sprFloor1_1B_under.png");
        sf::VertexArray draw_floorTile1B_unders = create_vertex_array(floorTile1B_under, 210);
        //explotile under
        sf::Texture exploTile1_under;
        exploTile1_under.loadFromFile("res/sprExploTile1_under.png");
        sf::VertexArray draw_exploTile1_unders = create_vertex_array(exploTile1_under, 50);


        //bullet1_destroy1
        sf::Texture bullet1_destroy1tex;
        bullet1_destroy1tex.loadFromFile("res/enemy_bullets/sprEnemyBullet1_destroy1.png");

        //bullet1_destroy2
        sf::Texture bullet1_destroy2tex;
        bullet1_destroy2tex.loadFromFile("res/enemy_bullets/sprEnemyBullet1_destroy2.png");

        //bullet1_destroy3
        sf::Texture bullet1_destroy3tex;
        bullet1_destroy3tex.loadFromFile("res/enemy_bullets/sprEnemyBullet1_destroy3.png");

        //bullet1_destroy4
        sf::Texture bullet1_destroy4tex;
        bullet1_destroy4tex.loadFromFile("res/enemy_bullets/sprEnemyBullet1_destroy4.png");

        //bullet1_destroy1bloom
        sf::Texture bullet1_destroy1bloomtex;
        bullet1_destroy1bloomtex.loadFromFile("res/enemy_bullets/sprEnemyBullet1_destroy1bloom.png");

        //bullet1_destroy2bloom
        sf::Texture bullet1_destroy2bloomtex;
        bullet1_destroy2bloomtex.loadFromFile("res/enemy_bullets/sprEnemyBullet1_destroy2bloom.png");

        //bullet1_destroy3bloom
        sf::Texture bullet1_destroy3bloomtex;
        bullet1_destroy3bloomtex.loadFromFile("res/enemy_bullets/sprEnemyBullet1_destroy3bloom.png");

        //bullet1_1
        sf::Texture bullet1_1tex;
        bullet1_1tex.loadFromFile("res/enemy_bullets/sprEnemyBullet1_1.png");
        sf::VertexArray draw_bullet1_1s = create_vertex_array(bullet1_1tex, 350 * draw_mult);

        //bullet1_2
        sf::Texture bullet1_2tex;
        bullet1_2tex.loadFromFile("res/enemy_bullets/sprEnemyBullet1_2.png");
        std::vector<sf::Sprite> bullet_1_batchable;
        int bullet_1_batchable_max = 3000;
       
        //bullet1_2BIG
        sf::Texture bullet1_2BIGtex;
        bullet1_2BIGtex.loadFromFile("res/enemy_bullets/sprEnemyBullet1_2BIG.png");
        sf::VertexArray draw_bullet1_2BIGs = create_vertex_array(bullet1_2BIGtex, 3000);

        //bullet2_1BIG
        sf::Texture bullet2_1BIGtex;
        bullet2_1BIGtex.loadFromFile("res/enemy_bullets/sprEnemyBullet2_1BIG.png");
        /* OLD
        sf::VertexArray draw_bullet2_1BIGs = create_vertex_array(bullet2_1BIGtex, 20000);
        */

        //bullet2_1
        sf::Texture bullet2_1tex;
        bullet2_1tex.loadFromFile("res/enemy_bullets/sprEnemyBullet2_1.png");

        //enemy_bullet_destroy2_1
        sf::Texture enemy_bullet_destroy2_1;
        enemy_bullet_destroy2_1.loadFromFile("res/enemy_bullets/enemy_bullet_destroy2_1.png");

        //enemy_bullet_destroy2_2
        sf::Texture enemy_bullet_destroy2_2;
        enemy_bullet_destroy2_2.loadFromFile("res/enemy_bullets/enemy_bullet_destroy2_2.png");

        //enemy_bullet_destroy2_3
        sf::Texture enemy_bullet_destroy2_3;
        enemy_bullet_destroy2_3.loadFromFile("res/enemy_bullets/enemy_bullet_destroy2_3.png");

        //enemy_bullet_destroy2_1bloom
        sf::Texture enemy_bullet_destroy2_1bloom;
        enemy_bullet_destroy2_1bloom.loadFromFile("res/enemy_bullets/enemy_bullet_destroy2_1bloom.png");

        //enemy_bullet_destroy2_2bloom
        sf::Texture enemy_bullet_destroy2_2bloom;
        enemy_bullet_destroy2_2bloom.loadFromFile("res/enemy_bullets/enemy_bullet_destroy2_2bloom.png");

        //enemy_bullet_destroy2_3bloom
        sf::Texture enemy_bullet_destroy2_3bloom;
        enemy_bullet_destroy2_3bloom.loadFromFile("res/enemy_bullets/enemy_bullet_destroy2_3bloom.png");


        //shadow24
        sf::Texture shadow24tex;
        shadow24tex.loadFromFile("res/shadow24.png");
        sf::VertexArray draw_shadow24s = create_vertex_array(shadow24tex, 1500 * draw_mult);

        //banditgun
        sf::Texture bandit_guntex;
        bandit_guntex.loadFromFile("res/enemies/desert/bandit/sprBanditGun.png");

        //playerbullet1_1 (revolver bullets etc.)
        sf::Texture playerbullet1_1tex;
        playerbullet1_1tex.loadFromFile("res/player/projectiles/bullets/playerbullet1_1.png");
        //playerbullet1_2
        sf::Texture playerbullet1_2tex;
        playerbullet1_2tex.loadFromFile("res/player/projectiles/bullets/playerbullet1_2.png");
        //playerbullet1bloom
        sf::Texture playerbullet1bloomtex;
        playerbullet1bloomtex.loadFromFile("res/player/projectiles/bullets/playerbullet1bloom.png");

        //playerbullet1_1bloom
        sf::Texture playerbullet1_2bloomtex;
        playerbullet1_2bloomtex.loadFromFile("res/player/projectiles/bullets/playerbullet1_2bloom.png");

        //playerbulletdestroy1
        sf::Texture playerbulletdelete1;
        playerbulletdelete1.loadFromFile("res/player/projectiles/bullets/playerbulletdelete1.png");
        //playerbulletdestroy2
        sf::Texture playerbulletdelete2;
        playerbulletdelete2.loadFromFile("res/player/projectiles/bullets/playerbulletdelete2.png");
        //playerbulletdestroy3
        sf::Texture playerbulletdelete3;
        playerbulletdelete3.loadFromFile("res/player/projectiles/bullets/playerbulletdelete3.png");
        //4th is same as enemy bullet 1

        //playerbulletdestroy1bloom
        sf::Texture playerbulletdelete1bloom;
        playerbulletdelete1bloom.loadFromFile("res/player/projectiles/bullets/playerbulletdelete1bloom.png");
        //playerbulletdestroy2bloom
        sf::Texture playerbulletdelete2bloom;
        playerbulletdelete2bloom.loadFromFile("res/player/projectiles/bullets/playerbulletdelete2bloom.png");
        //playerbulletdestroy3bloom
        sf::Texture playerbulletdelete3bloom;
        playerbulletdelete3bloom.loadFromFile("res/player/projectiles/bullets/playerbulletdelete3bloom.png");

        //4th is same as enemy bullet 1 bloom

        //plasma_huge_1
        sf::Texture plasma_huge_1tex;
        plasma_huge_1tex.loadFromFile("res/player/projectiles/plasma/plasma_huge_1.png");
        //plasma_huge_2
        sf::Texture plasma_huge_2tex;
        plasma_huge_2tex.loadFromFile("res/player/projectiles/plasma/plasma_huge_2.png");

        //plasma_huge_1bloom
        sf::Texture plasma_huge_1_bloomtex;
        plasma_huge_1_bloomtex.loadFromFile("res/player/projectiles/plasma/plasma_huge_bloom_1.png");
        //plasma_huge_2bloom
        sf::Texture plasma_huge_2_bloomtex;
        plasma_huge_2_bloomtex.loadFromFile("res/player/projectiles/plasma/plasma_huge_bloom_2.png");

        //plasma_big_1
        sf::Texture plasma_big_1tex;
        plasma_big_1tex.loadFromFile("res/player/projectiles/plasma/plasma_big_1.png");
        //plasma_big_2
        sf::Texture plasma_big_2tex;
        plasma_big_2tex.loadFromFile("res/player/projectiles/plasma/plasma_big_2.png");

        //plasma_big_1bloom
        sf::Texture plasma_big_1_bloomtex;
        plasma_big_1_bloomtex.loadFromFile("res/player/projectiles/plasma/plasma_big_bloom_1.png");
        //plasma_big_2bloom
        sf::Texture plasma_big_2_bloomtex;
        plasma_big_2_bloomtex.loadFromFile("res/player/projectiles/plasma/plasma_big_bloom_2.png");

        //plasma_1
        sf::Texture plasma_1tex;
        plasma_1tex.loadFromFile("res/player/projectiles/plasma/plasma_1.png");
        //plasma_2
        sf::Texture plasma_2tex;
        plasma_2tex.loadFromFile("res/player/projectiles/plasma/plasma_2.png");

        //plasma_1bloom
        sf::Texture plasma_bloom_1tex;
        plasma_bloom_1tex.loadFromFile("res/player/projectiles/plasma/plasma_bloom_1.png");
        //plasma_2bloom
        sf::Texture plasma_bloom_2tex;
        plasma_bloom_2tex.loadFromFile("res/player/projectiles/plasma/plasma_bloom_2.png");


        //plasma_hit_1
        sf::Texture plasma_hit_1tex;
        plasma_hit_1tex.loadFromFile("res/player/projectiles/plasma/plasma_hit_1.png");
        //plasma_hit_2
        sf::Texture plasma_hit_2tex;
        plasma_hit_2tex.loadFromFile("res/player/projectiles/plasma/plasma_hit_2.png");
        //plasma_hit_3
        sf::Texture plasma_hit_3tex;
        plasma_hit_3tex.loadFromFile("res/player/projectiles/plasma/plasma_hit_3.png");
        //plasma_hit_4
        sf::Texture plasma_hit_4tex;
        plasma_hit_4tex.loadFromFile("res/player/projectiles/plasma/plasma_hit_4.png");

        //plasma_hit_1_bloom
        sf::Texture plasma_hit_1bloomtex;
        plasma_hit_1bloomtex.loadFromFile("res/player/projectiles/plasma/plasma_hit_1_bloom.png");
        //plasma_hit_2_bloom
        sf::Texture plasma_hit_2bloomtex;
        plasma_hit_2bloomtex.loadFromFile("res/player/projectiles/plasma/plasma_hit_2_bloom.png");
        //plasma_hit_3_bloom
        sf::Texture plasma_hit_3bloomtex;
        plasma_hit_3bloomtex.loadFromFile("res/player/projectiles/plasma/plasma_hit_3_bloom.png");
        //plasma_hit_4_bloom
        sf::Texture plasma_hit_4bloomtex;
        plasma_hit_4bloomtex.loadFromFile("res/player/projectiles/plasma/plasma_hit_4_bloom.png");


        //horror sprites
        //horror beam A and B skin
        //horror_beamA1
        sf::Texture horror_beamA1;
        horror_beamA1.loadFromFile("res/player/projectiles/horror/horror_beam_A1.png");
        //horror_beamA2
        sf::Texture horror_beamA2;
        horror_beamA2.loadFromFile("res/player/projectiles/horror/horror_beam_A2.png");
        //horror_beamA1bloom
        sf::Texture horror_beamA1bloom;
        horror_beamA1bloom.loadFromFile("res/player/projectiles/horror/horror_beam_A1bloom.png");
        //horror_beamA2bloom
        sf::Texture horror_beamA2bloom;
        horror_beamA2bloom.loadFromFile("res/player/projectiles/horror/horror_beam_A2bloom.png");

        //horror_beam_destroyA1
        sf::Texture horror_beam_destroyA1;
        horror_beam_destroyA1.loadFromFile("res/player/projectiles/horror/horror_beam_destroy_A1.png");
        //horror_beam_destroyA2
        sf::Texture horror_beam_destroyA2;
        horror_beam_destroyA2.loadFromFile("res/player/projectiles/horror/horror_beam_destroy_A2.png");
        //horror_beam_destroyA3
        sf::Texture horror_beam_destroyA3;
        horror_beam_destroyA3.loadFromFile("res/player/projectiles/horror/horror_beam_destroy_A3.png");
        //horror_beam_destroyA1bloom
        sf::Texture horror_beam_destroyA1bloom;
        horror_beam_destroyA1bloom.loadFromFile("res/player/projectiles/horror/horror_beam_destroy_A1bloom.png");
        //horror_beam_destroyA2bloom
        sf::Texture horror_beam_destroyA2bloom;
        horror_beam_destroyA2bloom.loadFromFile("res/player/projectiles/horror/horror_beam_destroy_A2bloom.png");
        //horror_beam_destroyA3bloom
        sf::Texture horror_beam_destroyA3bloom;
        horror_beam_destroyA3bloom.loadFromFile("res/player/projectiles/horror/horror_beam_destroy_A3bloom.png");

        //explosions
        sf::Texture idpd_explosion_tex;
        idpd_explosion_tex.loadFromFile("res/explosions/sprPopoExplo_strip.png");

        sf::Texture plasma_impact_tex;
        plasma_impact_tex.loadFromFile("res/player/projectiles/plasma/sprPlasmaImpact_strip.png");

        sf::Texture idpd_nade_tex;
        idpd_nade_tex.loadFromFile("res/explosions/IDPD_nade.png");

        sf::Texture idpd_nade_remove_1;
        idpd_nade_remove_1.loadFromFile("res/explosions/IDPD_explosion_remove_1.png");
        sf::Texture idpd_nade_remove_2;
        idpd_nade_remove_2.loadFromFile("res/explosions/IDPD_explosion_remove_2.png");
        sf::Texture idpd_nade_remove_3;
        idpd_nade_remove_3.loadFromFile("res/explosions/IDPD_explosion_remove_3.png");
        sf::Texture idpd_nade_remove_4;
        idpd_nade_remove_4.loadFromFile("res/explosions/IDPD_explosion_remove_4.png");
        sf::Texture idpd_nade_remove_5;
        idpd_nade_remove_5.loadFromFile("res/explosions/IDPD_explosion_remove_5.png");

        //melee
        sf::Texture ultra_slash_tex_1;
        ultra_slash_tex_1.loadFromFile("res/player/projectiles/melee/ultra_slash_1.png");
        sf::Texture ultra_slash_tex_2;
        ultra_slash_tex_2.loadFromFile("res/player/projectiles/melee/ultra_slash_2.png");
        sf::Texture ultra_slash_tex_3;
        ultra_slash_tex_3.loadFromFile("res/player/projectiles/melee/ultra_slash_3.png");

        //batcher_bullet1 for rotateable sprites
        SimpleSpriteBatcher batcher_bullet1;
        batcher_bullet1.texture = &bullet1_2tex;

        SimpleSpriteBatcher batcher_bullet2;
        batcher_bullet2.texture = &bullet2_1tex;

        //player
        sf::Texture horror_tex;
        horror_tex.loadFromFile("res/player/characters/horror.png");

        player_sprite.setTexture(horror_tex);

        sf::Texture crosshair_tex;
        crosshair_tex.loadFromFile("res/player/sprCrosshair.png");

        cursor_sprite.setTexture(crosshair_tex);
        cursor_sprite.setOrigin(8, 8);
        cursor_sprite.setTextureRect({ 0, 0, 16, 16 });

        sf::Image cursor_pixels_1_16;
        cursor_pixels_1_16.loadFromFile("res/player/sprCrosshair_1_16.png");

        sf::Image cursor_pixels_1_32;
        cursor_pixels_1_32.loadFromFile("res/player/sprCrosshair_1_32.png");

        sf::Image cursor_pixels_1_48;
        cursor_pixels_1_48.loadFromFile("res/player/sprCrosshair_1_48.png");

        sf::Image cursor_pixels_1_64;
        cursor_pixels_1_64.loadFromFile("res/player/sprCrosshair_1_64.png");

        naitive_cursor_sprite.loadFromPixels(cursor_pixels_1_32.getPixelsPtr(), sf::Vector2u(32, 32), sf::Vector2u(16, 16));

        window.setMouseCursor(naitive_cursor_sprite);

        sf::Texture weapons_tex;
        weapons_tex.loadFromFile("res/player/weapons.png");

        wep_sprite.setTexture(weapons_tex);
        bwep_sprite.setTexture(weapons_tex);

    //initialize the area, this should be reset every level to regenerate the next level
    for (int i = 0; i < gridSize; i++) {
        for (int j = 0; j < gridSize; j++) {
            if (i == 0 || j == 0 || i == gridSize-1 || j == gridSize-1) {
                game_area[i][j].my_grid_type = boarder;
            }
            else {
                game_area[i][j].my_grid_type = wall;
            }
        }
    }

    sf::Color BGColor = {0, 0, 0};

    //font
    sf::Font font;
    font.loadFromFile("C:/Users/svt16/Desktop/Nuclear Throne Arranged/cmake-sfml-project/src/PressStart2P-Regular.ttf");

    //reverve max object count
    allObjects.reserve(max_objects);
    //rotateable_sprites_bullets.reserve(rotateable_sprites_bullets_max);

    allObjects.push_back(player);

    allFloors.reserve(max_floors);

    for (int i = 0; i < bullet_1_batchable_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 12,12 });
        bullet_1_batchable.push_back(temp);
    }

    for (int i = 0; i < bullet_2_batchable_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 16,16 });
        bullet_2_batchable.push_back(temp);
    }

    for (int i = 0; i < all_enemy_sprites_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 16,16 });
        temp.setTexture(allEnemySprites);
        all_enemy_sprites.push_back(temp);
    }

    for (int i = 0; i < all_enemy_corpses_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 16,16 });
        temp.setTexture(allEnemySprites);
        all_enemy_corpses.push_back(temp);
    }

    for (int i = 0; i < rotateable_sprites_bullets_max; i++) {
        sf::Sprite temp;
        temp.setColor({0, 0, 0, 0});
        temp.setOrigin({ 12,12 });
        rotateable_sprites_bullets.push_back(temp);
    }

    for (int i = 0; i < rotateable_sprites_bullets_huge_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 24,24 });
        rotateable_sprites_bullets_huge.push_back(temp);
    }
    for (int i = 0; i < rotateable_sprites_bullets_huge_bloom_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 48,48 });
        rotateable_sprites_bullets_huge_bloom.push_back(temp);
    }

    for (int i = 0; i < rotateable_sprites_bullets_big_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 12,12 });
        rotateable_sprites_bullets_big.push_back(temp);
    }
    for (int i = 0; i < rotateable_sprites_bullets_big_bloom_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 24,24 });
        rotateable_sprites_bullets_big_bloom.push_back(temp);
    }
    
    for (int i = 0; i < idpd_explosions_sprites_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 48,48 });
        temp.setTexture(idpd_explosion_tex);
        idpd_explosions_sprites.push_back(temp);
    }

    for (int i = 0; i < plasma_impact_sprites_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 16,16 });
        temp.setTexture(plasma_impact_tex);
        plasma_impact_sprites.push_back(temp);
    }

    for (int i = 0; i < rotateable_sprites_guns_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        rotateable_sprites_guns.push_back(temp);
    }

    for (int i = 0; i < rotateable_effects_small_bloom_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 4,4 });
        temp.setTexture(allSmallEffectSprites);
        rotateable_effects_small_bloom.push_back(temp);
    }

    for (int i = 0; i < rotateable_effects_small_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 4,4 });
        temp.setTexture(allSmallEffectSprites);
        rotateable_effects_small.push_back(temp);
    }
    for (int i = 0; i < under_effects_small_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 4,4 });
        temp.setTexture(allSmallEffectSprites);
        under_effects_small.push_back(temp);
    }

    for (int i = 0; i < rotateable_effects_medium_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 8,8 });
        temp.setTexture(allMediumEffectSprites);
        rotateable_effects_medium.push_back(temp);
    }
    for (int i = 0; i < rotateable_effects_large_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 12,12 });
        temp.setTexture(allBigEffectSprites);
        rotateable_effects_large.push_back(temp);
    }

    window.setVerticalSyncEnabled(false);
    window.setMouseCursorGrabbed(true);

    //window.setMouseCursorVisible(false);

    allObjects[0].friction = 0.45f;

    while (window.isOpen()){
        for (auto event = sf::Event(); window.pollEvent(event);){
            if (window.hasFocus()) {
                if (event.type == sf::Event::Closed)
                {
                    //window.setMouseCursorGrabbed(false);
                    window.close();
                }
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::P && P_released) {
                        GAME_PAUSED = !GAME_PAUSED;
                        P_released = false;
                    }
                    if (event.key.code == sf::Keyboard::L && L_released) {
                        FRAME_ADVANCE = 2;
                        L_released = false;
                    }
                    if (event.key.code == sf::Keyboard::R && R_released) {
                        want_gen = true;
                        R_released = false;
                    }
                    if (event.key.code == sf::Keyboard::Space && SPACE_released) {
                        SPACE_pressed = true;
                        SPACE_released = false;
                    }
                    if (event.key.code == sf::Keyboard::F) {
                        clear_all_bullets();
                    }
                    if (event.key.code == sf::Keyboard::Escape) {
                        window.close();
                    }
                    if (event.key.code == sf::Keyboard::W) {
                        player_move_up = true;
                    }
                    if (event.key.code == sf::Keyboard::A) {
                        player_move_left = true;
                    }
                    if (event.key.code == sf::Keyboard::S) {
                        player_move_down = true;
                    }
                    if (event.key.code == sf::Keyboard::D) {
                        player_move_right = true;
                    }
                    if (event.key.code == sf::Keyboard::Add) {
                        if (window_scale < 4) {
                            window_scale++;
                            resize_window(1, window);
                        }
                    }
                    if (event.key.code == sf::Keyboard::Subtract) {
                        if (window_scale > 1) {
                            window_scale--;
                            resize_window(-1, window);
                        }
                    }

                    if (event.key.code == sf::Keyboard::LShift) {
                        SHIFT_held = true;
                    }
                }
                if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.key.code == sf::Mouse::Left && LMB_released) {
                        LMB_pressed = true;
                        LMB_released = false;
                    }
                    if (event.key.code == sf::Mouse::Right && RMB_released) {
                        RMB_pressed = true;
                        RMB_released = false;
                    }
                }
                if (event.type == sf::Event::KeyReleased) {
                    if (event.key.code == sf::Keyboard::P) {
                        P_released = true;
                    }
                    if (event.key.code == sf::Keyboard::L) {
                        L_released = true;
                    }
                    if (event.key.code == sf::Keyboard::R) {
                        R_released = true;
                    }
                    if (event.key.code == sf::Keyboard::Space) {
                        SPACE_released = true;
                    }

                    if (event.key.code == sf::Keyboard::W) {
                        player_move_up = false;
                    }
                    if (event.key.code == sf::Keyboard::A) {
                        player_move_left = false;
                    }
                    if (event.key.code == sf::Keyboard::S) {
                        player_move_down = false;
                    }
                    if (event.key.code == sf::Keyboard::D) {
                        player_move_right = false;
                    }
                    if (event.key.code == sf::Keyboard::LShift) {
                        SHIFT_held = false;
                    }
                }
                if (event.type == sf::Event::MouseButtonReleased) {
                    if (event.key.code == sf::Mouse::Left) {
                        LMB_released = true;
                    }
                    if (event.key.code == sf::Mouse::Right) {
                        RMB_released = true;
                    }
                }
                
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    player_held_LMB = true;
                }
                else {
                    player_held_LMB = false;
                }
                if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
                    player_held_RMB = true;
                }
                else {
                    player_held_RMB = false;
                }
            }
            if(event.type == sf::Event::LostFocus){
                player_move_up = false;
                player_move_left = false;
                player_move_down = false;
                player_move_right = false;
                SHIFT_held = false;
                //when clicking out of window stop inputs
            }
        }

        //find the direction from the player to the mouse on this frame
        mousepos.x = sf::Mouse::getPosition(window).x / window_scale;
        mousepos.y = sf::Mouse::getPosition(window).y / window_scale;

        //area background color
        switch (area) {
        case 1:
            BGColor = {175, 143, 106, 0};
            break;
        default:
            BGColor = { 0, 0, 0, 0 };
            break;
        }
        if (want_gen) {
            want_gen = false;
            LOOPS++;
            generate_level();
        }
        //debug to see where the background bleeds through
        //BGColor = { 255, 0, 0, 0};
        window.clear(BGColor);
        buffer_over.clear(sf::Color::Transparent);
        buffer_under.clear(sf::Color::Transparent);
        shadows.clear(sf::Color::Transparent);

        sf::CircleShape c{ 3.0f };
        sf::Text tx;
        sf::Text ty;
        sf::Text ts;
        tx.setString("x: " + std::to_string(allObjects[0].position.x));
        tx.setCharacterSize(8);
        tx.setFont(font);
        tx.setColor(sf::Color::Black);
        tx.setPosition({ 2, 12 });
        ty.setString("y: " + std::to_string(allObjects[0].position.y));
        ty.setCharacterSize(8);
        ty.setFont(font);
        ty.setColor(sf::Color::Black);
        ty.setPosition({2, 2});
        ts.setString("LOOPS: " + std::to_string(LOOPS));
        ts.setCharacterSize(8);
        ts.setFont(font);
        ts.setColor(sf::Color::Black);
        ts.setPosition({ 2, 22 });

        int curr_objcount_real = 0;
        //quite laggy so take that into account when using

        for (int i = 0; i < max_objects; i++) {
            if (allObjects[i].my_id != nothing) {
                curr_objcount_real++;
            }
        }

        sf::Text tO;
        tO.setString("objects: " + std::to_string(curr_objcount_real));
        tO.setCharacterSize(8);
        tO.setFont(font);
        tO.setColor(sf::Color::Black);
        tO.setPosition({ 2, 42 });

        int curr_tile_count = 0;
        //quite laggy so take that into account when using

        for (int i = left_physics - extra_physics; i < right_physics + extra_physics; i++) {
            for (int j = top_physics - extra_physics; j < bottom_physics + extra_physics; j++) {
                if (game_area[i][j].my_grid_type != wall) {
                    curr_tile_count++;
                }
            }
        }

        sf::Text tO0;
        tO0.setString("tiles: " + std::to_string(curr_tile_count));
        tO0.setCharacterSize(8);
        tO0.setFont(font);
        tO0.setColor(sf::Color::Black);
        tO0.setPosition({ 2, 62 });

        if (FRAME_ADVANCE == 2 && GAME_PAUSED) {
            GAME_PAUSED = false;
            FRAME_ADVANCE = 1;
        }
        else if (FRAME_ADVANCE == 1 && !GAME_PAUSED) {
            GAME_PAUSED = true;
            FRAME_ADVANCE = 0;
        }

        //start of things that shouldnt be done when paused
        if (!GAME_PAUSED) {
            //leveling up
            if (player_level < 10) {
                if (player_rads > player_level * 60) {
                    player_rads -= player_level * 60;
                    player_level++;
                }
            }
            else {
                if (player_rads > 600 * meltdown) {
                    player_rads = 600 * meltdown;
                }
            }

            //do player movement first
            int horizontal_player_move = player_move_right - player_move_left;
            int vertical_player_move = player_move_down - player_move_up;
            float player_acceleration = 2.5f;
            float dirto_add = 0.0f;
            if (horizontal_player_move || vertical_player_move) {

                if (!horizontal_player_move && vertical_player_move) {
                    dirto_add = 180.0f - (90.0f * vertical_player_move);
                }
                if (horizontal_player_move && !vertical_player_move) {
                    dirto_add = 90.0f - (90.0f * horizontal_player_move);
                }
                if (horizontal_player_move && vertical_player_move) {
                    if (horizontal_player_move == 1 && vertical_player_move == 1) {
                        dirto_add = 45.0f;
                    }
                    if (horizontal_player_move == 1 && vertical_player_move == -1) {
                        dirto_add = 315.0f;
                    }
                    if (horizontal_player_move == -1 && vertical_player_move == -1) {
                        dirto_add = 225.0f;
                    }
                    if (horizontal_player_move == -1 && vertical_player_move == 1) {
                        dirto_add = 135.0f;
                    }
                }

                float spd_add_x = cos(dirto_add / degreestoradians) * player_acceleration;
                float spd_add_y = sin(dirto_add / degreestoradians) * player_acceleration;

                float spd_curr_x = cos(allObjects[0].direction) * allObjects[0].speeddir;
                float spd_curr_y = sin(allObjects[0].direction) * allObjects[0].speeddir;

                spd_curr_x += spd_add_x;
                spd_curr_y += spd_add_y;

                float new_angle = atan2f(spd_curr_y, spd_curr_x);
                float new_speed = sqrt((spd_curr_y * spd_curr_y) + (spd_curr_x * spd_curr_x));

                allObjects[0].speeddir = new_speed;
                allObjects[0].direction = new_angle;
            }

            if (allObjects[0].speeddir > player_max_speed) {
                allObjects[0].speeddir = player_max_speed;
            }

            //allObjects[0].friction = 0.45f;
            float friction_player = 0.45f;
            if (SHIFT_held && allObjects[0].friction > 0.3f && allObjects[0].friction < 0.5f) {
                friction_player = 2.0f;
            }
            else {
                friction_player = allObjects[0].friction;
            }
            allObjects[0].speeddir -= friction_player;

            if (allObjects[0].speeddir < 0) {
                allObjects[0].speeddir = 0;
            }

            allObjects[0].position.x += cos(allObjects[0].direction) * allObjects[0].speeddir;
            allObjects[0].position.y += sin(allObjects[0].direction) * allObjects[0].speeddir;

            current_create_start = 1;   //reset each frame so that objects can be slotted into deleted objects places
            if (wep < 11) {
                weapon_camera_type = 2;
            }
            else {
                weapon_camera_type = 4;
            }

            mouse_offset_window_center_x = (mousepos.x - window_size_x / (window_scale * 2)) / (6 - weapon_camera_type);
            mouse_offset_window_center_y = (mousepos.y - window_size_y / (window_scale * 2)) / (6 - weapon_camera_type);

            camera_want_x = floor(allObjects[0].position.x + cameraOffset.x + mouse_offset_window_center_x);
            camera_want_y = floor(allObjects[0].position.y + cameraOffset.y + mouse_offset_window_center_y);

            cameraPos.x = floor((camera_want_x - cameraPos.x) / 3 + cameraPos.x);
            cameraPos.y = floor((camera_want_y - cameraPos.y) / 3 + cameraPos.y);

            //calualte direction to mouse
            direction_to_mouse = atan2f(allObjects[0].position.y - (mousepos.y + cameraPos.y), allObjects[0].position.x - (mousepos.x + cameraPos.x)) + 180.0f / degreestoradians;

            if (allObjects[0].image_index >= 14) {
                allObjects[0].image_index = -1;
            }
            allObjects[0].image_index++;

            if (player_prev_speed_greater_than_zero != allObjects[0].speeddir > 0.0f) {
                //allObjects[0].image_index = 0;
            }
            player_prev_speed_greater_than_zero = allObjects[0].speeddir > 0.0f;
            player_is_facing_right = (0 > allObjects[0].position.x - (mousepos.x + cameraPos.x)) * 2 - 1;

            float xspd = 0.0f;
            float yspd = 0.0f;

            float tmpdir = 0.0f;
            float tmpspd = 0.0f;
            float diffx = 0.0f;
            float diffy = 0.0f;

            for (int i = 0; i < 0; i++) {
                float dir = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (360.0f / degreestoradians)));
                xspd = cos(dir) * -2;
                yspd = sin(dir) * -2;
                create_object(24016,
                    24016,
                    xspd,
                    yspd, bullet2, dir, 0);
            }
            for (int i = 0; i < 0; i++) {
                float dir = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (360.0f / degreestoradians)));
                xspd = cos(dir) * -1;
                yspd = sin(dir) * -1;
                create_object(24000,
                    24000,
                    xspd,
                    yspd, bullet1, dir, 0);
            }
            swapmove = 0;
            if (SPACE_pressed) {
                SPACE_pressed = false;

                play_swap_sound(bwep);

                int tmpwep = wep;
                wep = bwep;
                bwep = tmpwep;

                //reload
                float tmpreload = wep_reload;
                wep_reload = bwep_reload;
                bwep_reload = tmpreload;

                wep_kick = 0;
                swapmove = 1;
            }

            wep_reload -= reload_speed;

            if (wep_kick > 0) {
                wep_kick--;
            }
            else if (wep_kick < 0) {
                wep_kick++;
            }

            if (player_held_LMB) {      //player shooting logic
                fire_weapom(wep, direction_to_mouse);
            }
            if (player_held_RMB) {    //player active logic
                switch (player_character) {
                case horror:        //unnerfed beam
                    xspd = cos(direction_to_mouse) * 12;
                    yspd = sin(direction_to_mouse) * 12;

                    for (int i = (int)horror_beam_strength; i > 0; i--) {
                        if (player_rads > 0) {
                            tmpdir = random_360_radians();
                            create_object(allObjects[0].position.x + (cos(tmpdir) * horror_beam_strength + 1), allObjects[0].position.y + (sin(tmpdir) * horror_beam_strength + 1), xspd, yspd, horror_bullet, direction_to_mouse, 0);
                            player_rads--;
                            play_sounds_this_frame_count[snd_horror_beam_hold_ID] = true;
                            if (horror_beam_strength == 1.0f) {
                                play_sounds_this_frame_count[snd_horror_beam_start_ID] = true;
                            }
                        }
                        else {
                            break;
                        }
                    }

                    horror_beam_strength += 0.1f;

                    if (horror_beam_strength > 7.0f) {
                        horror_beam_strength = 7.0f;
                    }
                    break;
                default:
                    break;
                }
            }
            else {
                switch (player_character) {
                case horror:
                    //horror beam
                    horror_beam_strength -= 1.0f;
                    if (horror_beam_strength < 1.0f) {
                        horror_beam_strength = 1.0f;
                    }
                    break;
                default:
                    break;
                }
            }
            switch (player_character) {
            case horror:
                if (!snd_horror_beam_hold.getLoop()) {
                    snd_horror_beam_hold.play();
                    snd_horror_beam_hold.setLoop(true);
                }
                if (ultra_picked == 2) {    //anomaly
                    int totalhp = 0;
                    for (int i = 1; i < max_objects; i++) {
                        switch (allObjects[i].my_id) {
                        case bandit:
                            totalhp += allObjects[i].my_hp;
                            break;
                        default:
                            break;
                        }
                    }
                    if (totalhp <= 140 && totalhp) {
                        clear_all_bullets();
                        for (int i = 1; i < max_objects; i++) {
                            switch (allObjects[i].my_id) {
                            case bandit:
                                bandit_die_anomaly(i);
                                break;
                            default:
                                break;
                            }
                        }
                        play_sounds_this_frame_count[snd_horror_portal_ID] = true;
                    }
                }
                break;
            default:
                break;
            }

            do_object_logic(0, max_objects);

            //do all movement logic before doing collison logic with the 2d vector do ai logic after to take into account line of sight
            add_object_indexs_to_2Dvector(0, max_objects);

            //now thread collision logic in two parts to avoid wierdness
            int left_physics_adjusted = left_physics - extra_physics;
            int right_physics_adjusted = right_physics + extra_physics;
            do_object_collision(left_physics_adjusted, right_physics_adjusted, 0);

            //play sounds
            float pitch_offset = 0.0f;
            for (int i = 0; i < 255; i++) {
                if (play_sounds_this_frame_count[i]) {
                    switch (i) {
                    case snd_shoot_1_ID:
                        //play_sound_random_pitch(snd_shoot_1, 0.1f, i);
                        pitch_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2f))) - 0.1f;
                        snd_shoot_1.setPitch(1 + pitch_offset);
                        snd_shoot_1.setPosition(play_sounds_this_frame_pos[i].x / play_sounds_this_frame_count[i], 0, play_sounds_this_frame_pos[i].y / play_sounds_this_frame_count[i]);
                        snd_shoot_1.play();
                        break;
                    case snd_horror_portal_ID:
                        pitch_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2f))) - 0.1f;
                        snd_horror_portal.setPitch(1 + pitch_offset);
                        snd_horror_portal.play();
                        snd_horror_portal_pan.setPitch(1 + pitch_offset);
                        snd_horror_portal_pan.setPosition(play_sounds_this_frame_pos[i].x / play_sounds_this_frame_count[i], 0, play_sounds_this_frame_pos[i].y / play_sounds_this_frame_count[i]);
                        snd_horror_portal_pan.play();
                        break;
                    case snd_bandit_hurt_ID:
                        pitch_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2f))) - 0.1f;
                        snd_bandit_hurt.setPitch(1 + pitch_offset);
                        snd_bandit_hurt.setPosition(play_sounds_this_frame_pos[i].x / play_sounds_this_frame_count[i], 0, play_sounds_this_frame_pos[i].y / play_sounds_this_frame_count[i]);
                        snd_bandit_hurt.play();
                        break;
                    case snd_bandit_die_ID:
                        pitch_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2f))) - 0.1f;
                        snd_bandit_die.setPitch(1 + pitch_offset);
                        snd_bandit_die.setPosition(play_sounds_this_frame_pos[i].x / play_sounds_this_frame_count[i], 0, play_sounds_this_frame_pos[i].y / play_sounds_this_frame_count[i]);
                        snd_bandit_die.play();
                        break;
                    case snd_rad_pickup_ID:
                        pitch_offset = (1.0f + ((float(player_rads) / float(player_level * 60)) / 4.0f));
                        snd_rad_pickup.setPitch(pitch_offset);
                        snd_rad_pickup.play();
                        break;
                    case snd_horror_beam_start_ID:
                        snd_horror_beam_start.play();
                        break;
                    case snd_horror_beam_hold_ID:
                        snd_horror_beam_hold.setVolume(70.0f);
                        break;
                    case snd_hit_wall_ID:
                        pitch_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2f))) - 0.1f;
                        snd_hit_wall.setPitch(1 + pitch_offset);
                        snd_hit_wall.setPosition(play_sounds_this_frame_pos[i].x / play_sounds_this_frame_count[i], 0, play_sounds_this_frame_pos[i].y / play_sounds_this_frame_count[i]);
                        snd_hit_wall.play();
                        break;
                    case snd_wall_break_rock_ID:
                        pitch_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2f))) - 0.1f;
                        snd_wall_break_rock.setPitch(1 + pitch_offset);
                        snd_wall_break_rock.setPosition(play_sounds_this_frame_pos[i].x / play_sounds_this_frame_count[i], 0, play_sounds_this_frame_pos[i].y / play_sounds_this_frame_count[i]);
                        snd_wall_break_rock.play();
                        break;
                    case snd_IDPD_explosion_ID:
                        pitch_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2f))) - 0.1f;
                        snd_IDPD_explosion.setPitch(1 + pitch_offset);
                        snd_IDPD_explosion.setPosition(play_sounds_this_frame_pos[i].x / play_sounds_this_frame_count[i], 0, play_sounds_this_frame_pos[i].y / play_sounds_this_frame_count[i]);
                        snd_IDPD_explosion.play();
                        break;
                    case snd_plasma_hit_ID:
                        pitch_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.3f))) - 0.15f;
                        snd_plasma_hit.setPosition(play_sounds_this_frame_pos[i].x / play_sounds_this_frame_count[i], 0, play_sounds_this_frame_pos[i].y / play_sounds_this_frame_count[i]);
                        snd_plasma_hit.play();
                        break;
                    case snd_ultra_shovel_ID:
                        pitch_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2f))) - 0.1f;
                        snd_ultra_shovel.setPitch(1 + pitch_offset);
                        snd_ultra_shovel.play();
                        break;
                    case snd_plasma_huge_ID:
                        pitch_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.3f))) - 0.15f;
                        if (laser_brain < 1.1f) {
                            snd_plasma_huge.setPitch(1 + pitch_offset);
                            snd_plasma_huge.play();
                        }
                        else {
                            snd_plasma_huge_upgrade.setPitch(1 + pitch_offset);
                            snd_plasma_huge_upgrade.play();
                        }
                        break;
                    case snd_plasma_split_ID:
                        pitch_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.3f))) - 0.15f;
                        if (laser_brain < 1.1f) {
                            snd_plasma_split.setPosition(play_sounds_this_frame_pos[i].x / play_sounds_this_frame_count[i], 0, play_sounds_this_frame_pos[i].y / play_sounds_this_frame_count[i]);
                            snd_plasma_split.setPitch(1 + pitch_offset);
                            snd_plasma_split.play();
                        }
                        else {
                            snd_plasma_split_upgrade.setPosition(play_sounds_this_frame_pos[i].x / play_sounds_this_frame_count[i], 0, play_sounds_this_frame_pos[i].y / play_sounds_this_frame_count[i]);
                            snd_plasma_split_upgrade.setPitch(1 + pitch_offset);
                            snd_plasma_split_upgrade.play();
                        }
                        break;
                    case snd_hammer_swap_ID:
                        snd_hammer_swap.play();
                        break;
                    case snd_energy_swap_ID:
                        snd_energy_swap.play();
                        break;
                    case snd_explosion_ID:
                        pitch_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2f))) - 0.1f;
                        snd_explosion.setPitch(1 + pitch_offset);
                        snd_explosion.setPosition(play_sounds_this_frame_pos[i].x / play_sounds_this_frame_count[i], 0, play_sounds_this_frame_pos[i].y / play_sounds_this_frame_count[i]);
                        snd_explosion.play();
                        break;
                    case snd_nade_hit_wall_ID:
                        pitch_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2f))) - 0.1f;
                        snd_nade_hit_wall.setPitch(1 + pitch_offset);
                        snd_nade_hit_wall.setPosition(play_sounds_this_frame_pos[i].x / play_sounds_this_frame_count[i], 0, play_sounds_this_frame_pos[i].y / play_sounds_this_frame_count[i]);
                        snd_nade_hit_wall.play();
                        break;
                    case snd_IDPD_nade_load_ID:
                        pitch_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2f))) - 0.1f;
                        snd_IDPD_nade_load.setPitch(1 + pitch_offset);
                        snd_IDPD_nade_load.setPosition(play_sounds_this_frame_pos[i].x / play_sounds_this_frame_count[i], 0, play_sounds_this_frame_pos[i].y / play_sounds_this_frame_count[i]);
                        snd_IDPD_nade_load.play();
                        break;
                    case snd_IDPD_nade_almost_ID:
                        pitch_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (0.2f))) - 0.1f;
                        snd_IDPD_nade_almost.setPitch(1 + pitch_offset);
                        snd_IDPD_nade_almost.setPosition(play_sounds_this_frame_pos[i].x / play_sounds_this_frame_count[i], 0, play_sounds_this_frame_pos[i].y / play_sounds_this_frame_count[i]);
                        snd_IDPD_nade_almost.play();
                        break;
                    default:
                        break;
                    }
                    play_sounds_this_frame_count[i] = 0;
                    play_sounds_this_frame_pos[i].x = 0;
                    play_sounds_this_frame_pos[i].y = 0;
                }
                else {
                    switch (i) {
                    case 6:
                        snd_horror_beam_hold.setVolume(0.0f);
                        break;
                    default:
                        break;
                    }
                }
            }

            c.setPosition(allObjects[0].position - cameraPos);
            c.setOrigin({ 3, 3 });
        }
        else {
            add_object_indexs_to_2Dvector(0, max_objects);
            //so they still get drawn
        }
        //end of everything that shouldnt happen when paused

        //get camera position to determine what cells to draw
        int extra_camera_draw_room = 0;
        int cameraBoundsTop = (cameraPos.y - cameraOffset.y)/16 - 9 - extra_camera_draw_room;
        int cameraBoundsBottom = (cameraPos.y - cameraOffset.y)/16 + 10 + extra_camera_draw_room;
        int cameraBoundsLeft = (cameraPos.x - cameraOffset.x)/16 - 12 - extra_camera_draw_room;
        int cameraBoundsRight = (cameraPos.x - cameraOffset.x)/16 + 13 + extra_camera_draw_room;

        if (cameraBoundsTop < 0) {
            cameraBoundsTop = 0;
        }
        if (cameraBoundsBottom > gridSize) {
            cameraBoundsBottom = gridSize;
        }
        if (cameraBoundsLeft < 0) {
            cameraBoundsLeft = 0;
        }
        if (cameraBoundsRight > gridSize) {
            cameraBoundsRight = gridSize;
        }

        //debug rectangle
        sf::RectangleShape bounding_defaul_res;
        bounding_defaul_res.setFillColor(sf::Color::Red);
        bounding_defaul_res.setSize(sf::Vector2f(320, 240));
        bounding_defaul_res.setPosition(sf::Vector2f(160, 120));
        //debug rectangle

        //draw everything in the area of the camera plus a little extra


        sf::RectangleShape wallrect;
        wallrect.setFillColor(sf::Color::Green);
        wallrect.setSize(sf::Vector2f(16, 16));

        sf::RectangleShape boarderrect;
        boarderrect.setFillColor(sf::Color::Red);
        boarderrect.setSize(sf::Vector2f(16, 16));

        sf::Vector2f currDrawPosition;

        int allEnemySpritesIndex = 0;
        int allEnemyCorpsesIndex = 0;

        int wall1ArrayIndex = 0;
        int wall2ArrayIndex = 0;
        int wall3ArrayIndex = 0;
        int wall4ArrayIndex = 0;

        int wall1BOTArrayIndex = 0;
        int wall2BOTArrayIndex = 0;
        int wall3BOTArrayIndex = 0;
        int wall4BOTArrayIndex = 0;

        int wallBoardeArrayIndex = 0;

        int wallShadowArrayIndex = 0;

        int floor1ArrayIndex = 0;
        int floor2ArrayIndex = 0;
        int floor3ArrayIndex = 0;
        int floor4ArrayIndex = 0;
        int floor5ArrayIndex = 0;
        int floor6ArrayIndex = 0;
        int floor7ArrayIndex = 0;
        int floor8ArrayIndex = 0;

        int floor1BArrayIndex = 0;
        int floor2BArrayIndex = 0;
        int floor3BArrayIndex = 0;
        int floor4BArrayIndex = 0;

        int exploTile1ArrayIndex = 0;
        int exploTile2ArrayIndex = 0;
        int exploTile3ArrayIndex = 0;
        int exploTile4ArrayIndex = 0;

        int floor1_under_ArrayIndex = 0;
        int floor1B_under_ArrayIndex = 0;
        int exploTile1_under_ArrayIndex = 0;

        int bullet1_destroy1ArrayIndex = 0;
        int bullet1_destroy2ArrayIndex = 0;
        int bullet1_destroy3ArrayIndex = 0;
        int bullet1_destroy4ArrayIndex = 0;

        int bullet1_destroy1bloomArrayIndex = 0;
        int bullet1_destroy2bloomArrayIndex = 0;
        int bullet1_destroy3bloomArrayIndex = 0;

        int enemy_bullet2_destroy1ArrayIndex = 0;
        int enemy_bullet2_destroy2ArrayIndex = 0;
        int enemy_bullet2_destroy3ArrayIndex = 0;

        int enemy_bullet2_destroy1bloomArrayIndex = 0;
        int enemy_bullet2_destroy2bloomArrayIndex = 0;
        int enemy_bullet2_destroy3bloomArrayIndex = 0;

        int bullet1_1ArrayIndex = 0;
        int bullet1_2BIGArrayIndex = 0;
        int bullet2_1BIGArrayIndex = 0;

        int shadow24_ArrayIndex = 0;

        int playerbullet1_bloomArrayIndex = 0;

        int horror_beam_destroyA1_ArrayIndex = 0;
        int horror_beam_destroyA2_ArrayIndex = 0;
        int horror_beam_destroyA3_ArrayIndex = 0;
        int horror_beam_destroyA1bloom_ArrayIndex = 0;
        int horror_beam_destroyA2bloom_ArrayIndex = 0;
        int horror_beam_destroyA3bloom_ArrayIndex = 0;

        int rotateableSpriteBulletIndex = 0;
        int rotateableSpriteBulletHugeIndex = 0;
        int rotateableSpriteBulletHugeBloomIndex = 0;

        int rotateableSpriteBulletBigIndex = 0;
        int rotateableSpriteBulletBigBloomIndex = 0;

        int plasmaImpactIDX = 0;

        int rotateableSpriteGunIndex = 0;
        int rotateableEffectsSmallIndex = 0;
        int rotateableEffectsMediumIndex = 0;
        int rotateableEffectsLargeIndex = 0;

        int underEffectsSmallIndex = 0;

        int rotateableEffectsSmallBloomIndex = 0;
        //int rotateableEffectsSmallNoRotBloomIndex = 0;

        int bullet_1_batchableIndex = 0;
        int bullet_2_batchableIndex = 0;

        int IDPD_explosionIndex = 0;

        for (int i = 0; i < max_floors; i++) {
            currDrawPosition = allFloors[i].getPosition() - cameraPos;
            //currDrawPosition = {100, 100};
            if (abs(currDrawPosition.x - 160) < 200 && abs(currDrawPosition.y - 120) < 160) {
                int choice = allFloors[i].getOrigin().y;
                switch (choice) {
                case 0:
                    add_sprite_32(floor1ArrayIndex, currDrawPosition, draw_floorTile1s);
                    floor1ArrayIndex++;
                    break;
                case 1:
                    add_sprite_32(floor2ArrayIndex, currDrawPosition, draw_floorTile2s);
                    floor2ArrayIndex++;
                    break;
                case 2:
                    add_sprite_32(floor3ArrayIndex, currDrawPosition, draw_floorTile3s);
                    floor3ArrayIndex++;
                    break;
                case 3:
                    add_sprite_32(floor4ArrayIndex, currDrawPosition, draw_floorTile4s);
                    floor4ArrayIndex++;
                    break;
                    //B tiles
                case 4:
                    add_sprite_36(floor1BArrayIndex, currDrawPosition - sf::Vector2f(2, 2), draw_floorTile1Bs);
                    floor1BArrayIndex++;
                    break;
                case 5:
                    add_sprite_36(floor2BArrayIndex, currDrawPosition - sf::Vector2f(2, 2), draw_floorTile2Bs);
                    floor2BArrayIndex++;
                    break;
                case 6:
                    add_sprite_36(floor3BArrayIndex, currDrawPosition - sf::Vector2f(2, 2), draw_floorTile3Bs);
                    floor3BArrayIndex++;
                    break;
                case 7:
                    add_sprite_36(floor4BArrayIndex, currDrawPosition - sf::Vector2f(2, 2), draw_floorTile4Bs);
                    floor4BArrayIndex++;
                    break;
                default:
                    add_sprite_32(floor1ArrayIndex, currDrawPosition, draw_floorTile1s);
                    floor1ArrayIndex++;
                    break;
                }
                if (choice > 3) {
                    add_sprite_32(floor1B_under_ArrayIndex, currDrawPosition - sf::Vector2f(0, 32), draw_floorTile1B_unders);
                    floor1B_under_ArrayIndex++;
                }
                else {
                    add_sprite_32(floor1_under_ArrayIndex, currDrawPosition - sf::Vector2f(0, 32), draw_floorTile1_unders);
                    floor1_under_ArrayIndex++;
                }
            }
        }

        for (int i = cameraBoundsLeft; i < cameraBoundsRight; i++) {
            for (int j = cameraBoundsTop; j < cameraBoundsBottom; j++) {
                if (game_area[i][j].my_grid_type == wall) {         //drawing walls, will have to make this draw different things based on the surrounding walls
                    currDrawPosition = { i * 16 - cameraPos.x, j * 16 - cameraPos.y };
                    int choice = (i + j) % 4;
                    //boarder of wall
                    add_sprite_24(wallBoardeArrayIndex, currDrawPosition - sf::Vector2f(4, 12), draw_boarderWalls);
                    wallBoardeArrayIndex++;

                    add_sprite_24(wallShadowArrayIndex, currDrawPosition - sf::Vector2f(4, -8), draw_Wall1shadows);
                    wallShadowArrayIndex++;

                    switch (choice) {
                    case 0:
                        add_sprite_16(wall1ArrayIndex, currDrawPosition - sf::Vector2f(0, 8), draw_middlewall1s);
                        wall1ArrayIndex++;
                        break;
                    case 1:
                        add_sprite_16(wall2ArrayIndex, currDrawPosition - sf::Vector2f(0, 8), draw_middlewall2s);
                        wall2ArrayIndex++;
                        break;
                    case 2:
                        add_sprite_16(wall3ArrayIndex, currDrawPosition - sf::Vector2f(0, 8), draw_middlewall3s);
                        wall3ArrayIndex++;
                        break;
                    case 3:
                        add_sprite_16(wall4ArrayIndex, currDrawPosition - sf::Vector2f(0, 8), draw_middlewall4s);
                        wall4ArrayIndex++;
                        break;
                    }
                    if (game_area[i][j + 1].my_grid_type != wall) {     //if there isnt a wall undernearth a bottom wall needs to be drawn
                        switch (choice) {
                        case 0:
                            add_sprite_16(wall1BOTArrayIndex, currDrawPosition, draw_botwall1s);
                            wall1BOTArrayIndex++;
                            break;
                        case 1:
                            add_sprite_16(wall2BOTArrayIndex, currDrawPosition, draw_botwall2s);
                            wall2BOTArrayIndex++;
                            break;
                        case 2:
                            add_sprite_16(wall3BOTArrayIndex, currDrawPosition, draw_botwall3s);
                            wall3BOTArrayIndex++;
                            break;
                        case 3:
                            add_sprite_16(wall4BOTArrayIndex, currDrawPosition, draw_botwall4s);
                            wall4BOTArrayIndex++;
                            break;
                        }
                        if (game_area[i][j + 1].my_grid_type == exlpo_tile) {
                            add_sprite_16(exploTile1_under_ArrayIndex, currDrawPosition, draw_exploTile1_unders);
                            exploTile1_under_ArrayIndex++;
                        }
                    }
                }
                else if (game_area[i][j].my_grid_type == boarder) {

                }
                else if (game_area[i][j].my_grid_type == exlpo_tile) {
                    currDrawPosition = { i * 16 - cameraPos.x, j * 16 - cameraPos.y };
                    int choice = (int(i * (2.3 * abs(j - i) + 1)) + int(j * (1.3 * abs(j - i) + 7))) % 4;
                    switch (choice) {
                    case 0:
                        add_sprite_18(exploTile1ArrayIndex, currDrawPosition - sf::Vector2f{ 1, 1 }, draw_exploTile1s);
                        exploTile1ArrayIndex++;
                        break;
                    case 1:
                        add_sprite_18(exploTile2ArrayIndex, currDrawPosition - sf::Vector2f{ 1, 1 }, draw_exploTile2s);
                        exploTile2ArrayIndex++;
                        break;
                    case 2:
                        add_sprite_18(exploTile3ArrayIndex, currDrawPosition - sf::Vector2f{ 1, 1 }, draw_exploTile3s);
                        exploTile3ArrayIndex++;
                        break;
                    case 3:
                        add_sprite_18(exploTile4ArrayIndex, currDrawPosition - sf::Vector2f{ 1, 1 }, draw_exploTile4s);
                        exploTile4ArrayIndex++;
                        break;
                    }
                }
                else if (game_area[i][j].my_grid_type == floor_tile ) {
                    //currDrawPosition = { i * 16 - cameraPos.x, j * 16 - cameraPos.y };
                    //add_sprite_32(floor1ArrayIndex, currDrawPosition, draw_floorTile1s);
                    //floor1ArrayIndex++;
                    //do nothing
                }
                //sprites
                
                for (int idx : game_area[i][j].object_indexes) {
                    objectID id = allObjects[idx].my_id;
                    int choice = 0;
                    int choice2 = 0;
                    float tmp_wep_angle = 0.0f;
                    switch (id) {
                    case objectID::player:
                        //crosshair
                        cursor_sprite.setPosition(sf::Vector2f(mousepos));

                        add_sprite_24(shadow24_ArrayIndex, allObjects[idx].position - cameraPos + offset24, draw_shadow24s);
                        shadow24_ArrayIndex++;      //shadow

                        choice2 = 0;
                        if (allObjects[0].speeddir > 0.0f) {
                            choice2 = 1;
                        }
                        if (allObjects[0].next_hurt > current_frame) {
                            choice2 = 2;
                        }
                        choice = int(allObjects[0].image_index * 0.4f);
                        player_sprite.setPosition(allObjects[idx].position - cameraPos);
                        player_sprite.setTextureRect(sf::IntRect{ 48 * choice, 48 * choice2, 48, 48 });
                        player_sprite.setScale(player_is_facing_right, 1);

                        tmp_wep_angle = direction_to_mouse;

                        if (wep < 11) {     //melee
                            tmp_wep_angle = direction_to_mouse + (wep_angle * (1 - (wep_kick / 20))) / degreestoradians;
                        }

                        wep_sprite.setPosition(allObjects[idx].position - cameraPos + sf::Vector2f(cos(tmp_wep_angle) * -wep_kick, sin(tmp_wep_angle) * -wep_kick));
                        wep_sprite.setTextureRect(sf::IntRect{ 36 * wep_shine_frame, 36 * wep, 36, 36 });
                        wep_sprite.setScale(1, player_is_facing_right);
                        wep_sprite.setRotation(tmp_wep_angle * degreestoradians);
                        wep_sprite.setOrigin(wep_get_origin(wep));

                        bwep_sprite.setPosition(allObjects[idx].position - cameraPos + sf::Vector2f(-2 * player_is_facing_right, swapmove));
                        bwep_sprite.setTextureRect(sf::IntRect{ 0, 36 * bwep, 36, 36 });
                        bwep_sprite.setScale(1, player_is_facing_right);
                        bwep_sprite.setRotation(-90 - 15 * player_is_facing_right);
                        bwep_sprite.setOrigin(wep_get_origin(bwep));
                        break;
                    case bullet1:       //bullets
                        if (allObjects[idx].image_index == 0) {
                            
                            add_sprite_16(bullet1_1ArrayIndex, allObjects[idx].position - cameraPos + offset16, draw_bullet1_1s);
                            bullet1_1ArrayIndex++;
                            add_sprite_32(bullet1_2BIGArrayIndex, allObjects[idx].position - cameraPos + offset32, draw_bullet1_2BIGs);
                            bullet1_2BIGArrayIndex++;
                        }
                        else {
                            bullet_1_batchable[bullet_1_batchableIndex].setTexture(bullet1_2tex);
                            bullet_1_batchable[bullet_1_batchableIndex].setColor({ 255, 255, 255, 255 });
                            bullet_1_batchable[bullet_1_batchableIndex].setPosition(allObjects[idx].position - cameraPos);
                            bullet_1_batchable[bullet_1_batchableIndex].setRotation(allObjects[idx].direction + 180.0f);
                            //add_rotateable_sprite(bullet_1_batchableIndex, allObjects[idx].position - cameraPos, allObjects[idx].direction + 180.0f, bullet_1_batchable, bullet1_2tex);
                            bullet_1_batchableIndex++;

                            add_sprite_32(bullet1_2BIGArrayIndex, allObjects[idx].position - cameraPos + offset32, draw_bullet1_2BIGs);
                            bullet1_2BIGArrayIndex++;
                        }

                        break;
                    case bullet2:
                        bullet_2_batchable[bullet_2_batchableIndex].setTexture(bullet2_1tex);
                        bullet_2_batchable[bullet_2_batchableIndex].setColor({ 255, 255, 255, 255 });
                        bullet_2_batchable[bullet_2_batchableIndex].setPosition(allObjects[idx].position - cameraPos);
                        bullet_2_batchable[bullet_2_batchableIndex].setRotation(allObjects[idx].direction);
                        bullet_2_batchableIndex++;
                        
                        //add_sprite_32(bullet2_1BIGArrayIndex, allObjects[idx].position - cameraPos + offset32, draw_bullet2_1BIGs);
                        //bullet2_1BIGArrayIndex++;
                        break;
                    case bullet1_destroy:       //bullets destroy animation
                        choice = int(allObjects[idx].image_index * 0.4f);
                        switch (choice) {
                        case 0:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(bullet1_destroy1tex);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                            break;
                        case 1:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(bullet1_destroy2tex);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                            break;
                        case 2:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(bullet1_destroy3tex);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                            break;
                        case 3:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(bullet1_destroy4tex);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                            break;
                        }
                        break;
                    case idpd_explosion:
                        choice = int(allObjects[idx].image_index * 0.4f);
                        idpd_explosions_sprites[IDPD_explosionIndex].setColor({ 255, 255, 255, 255 });
                        idpd_explosions_sprites[IDPD_explosionIndex].setPosition(allObjects[idx].position - cameraPos);
                        idpd_explosions_sprites[IDPD_explosionIndex].setTextureRect(sf::IntRect{ 96 * choice, 0, 96, 96 });
                        IDPD_explosionIndex++;
                        break;

                    case plasma_impact:
                        choice = int(allObjects[idx].image_index * 0.4f);
                        plasma_impact_sprites[plasmaImpactIDX].setColor({ 255, 255, 255, 255 });
                        plasma_impact_sprites[plasmaImpactIDX].setPosition(allObjects[idx].position - cameraPos);
                        plasma_impact_sprites[plasmaImpactIDX].setTextureRect(sf::IntRect{ 32 * choice, 0, 32, 32 });
                        plasmaImpactIDX++;
                        break;

                    case idpd_nade:
                        choice = (allObjects[idx].alarm1 > 69) * (int(allObjects[idx].alarm1 * 0.4f) % 2 + 1);
                        rotateable_effects_small[rotateableEffectsSmallIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_effects_small[rotateableEffectsSmallIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_effects_small[rotateableEffectsSmallIndex].setRotation(allObjects[idx].rotation);
                        rotateable_effects_small[rotateableEffectsSmallIndex].setTextureRect(sf::IntRect{choice * 8, 32, 8, 8 });
                        rotateableEffectsSmallIndex++;
                        break;
                    case idpd_nade_remove:
                        choice = int(allObjects[idx].image_index * 0.4f);
                        switch (choice) {
                        default:
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setTexture(idpd_nade_remove_1);
                            break;
                        case 1:
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setTexture(idpd_nade_remove_2);
                            break;
                        case 2:
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setTexture(idpd_nade_remove_3);
                            break;
                        case 3:
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setTexture(idpd_nade_remove_4);
                            break;
                        case 4:
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setTexture(idpd_nade_remove_5);
                            break;
                        }

                        rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setRotation(allObjects[idx].rotation);
                        rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setScale(1, 1);
                        rotateableSpriteBulletHugeIndex++;
                        break;
                    case idpd_portal_charge:

                        rotateable_effects_small[rotateableEffectsSmallIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_effects_small[rotateableEffectsSmallIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_effects_small[rotateableEffectsSmallIndex].setRotation(0.0f);
                        rotateable_effects_small[rotateableEffectsSmallIndex].setTextureRect(sf::IntRect{ allObjects[idx].image_index * 8, 40, 8, 8});
                        rotateableEffectsSmallIndex++;
                        break;
                    case ultra_slash:
                        choice = int(allObjects[idx].image_index * 0.4f);
                        if (choice == 0) {
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setTexture(ultra_slash_tex_1);
                        }
                        if (choice == 1) {
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setTexture(ultra_slash_tex_2);
                        }
                        if (choice == 2) {
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setTexture(ultra_slash_tex_3);
                        }

                        rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setRotation(allObjects[idx].direction* degreestoradians);
                        rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setScale(1, 1);
                        rotateableSpriteBulletHugeIndex++;

                        break;
                    case debris:
                        choice = allObjects[idx].image_index;
                        rotateable_effects_small[rotateableEffectsSmallIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_effects_small[rotateableEffectsSmallIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_effects_small[rotateableEffectsSmallIndex].setRotation(allObjects[idx].friction);
                        rotateable_effects_small[rotateableEffectsSmallIndex].setTextureRect(sf::IntRect{ 8 * choice, 0, 8, 8 });
                        rotateableEffectsSmallIndex++;
                        
                        break;
                    case dust:
                        choice = allObjects[idx].image_index;
                        rotateable_effects_medium[rotateableEffectsMediumIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_effects_medium[rotateableEffectsMediumIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_effects_medium[rotateableEffectsMediumIndex].setRotation(allObjects[idx].direction);
                        rotateable_effects_medium[rotateableEffectsMediumIndex].setScale(sf::Vector2f(allObjects[idx].scale, allObjects[idx].scale));
                        rotateable_effects_medium[rotateableEffectsMediumIndex].setTextureRect(sf::IntRect{ 16 * choice, 0, 16, 16 });
                        rotateableEffectsMediumIndex++;

                        break;
                    case smoke:
                        choice = allObjects[idx].image_index;
                        rotateable_effects_large[rotateableEffectsLargeIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_effects_large[rotateableEffectsLargeIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_effects_large[rotateableEffectsLargeIndex].setRotation(allObjects[idx].direction);
                        rotateable_effects_large[rotateableEffectsLargeIndex].setScale(sf::Vector2f(allObjects[idx].scale, allObjects[idx].scale));
                        rotateable_effects_large[rotateableEffectsLargeIndex].setTextureRect(sf::IntRect{ 24 * choice, 0, 24, 24 });
                        rotateableEffectsLargeIndex++;

                        break;
                    case deflect:
                        choice = int(allObjects[idx].image_index * 0.4f);
                        rotateable_effects_large[rotateableEffectsLargeIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_effects_large[rotateableEffectsLargeIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_effects_large[rotateableEffectsLargeIndex].setRotation(allObjects[idx].direction);
                        rotateable_effects_large[rotateableEffectsLargeIndex].setScale(sf::Vector2f(1, 1));
                        rotateable_effects_large[rotateableEffectsLargeIndex].setTextureRect(sf::IntRect{ 24 * choice, 24, 24, 24 });
                        rotateableEffectsLargeIndex++;

                        break;
                    case detail:
                        choice = allObjects[idx].image_index;
                        under_effects_small[underEffectsSmallIndex].setColor({ 255, 255, 255, 255 });
                        under_effects_small[underEffectsSmallIndex].setPosition(allObjects[idx].position - cameraPos);
                        under_effects_small[underEffectsSmallIndex].setRotation(0.0f);
                        under_effects_small[underEffectsSmallIndex].setScale(sf::Vector2f(allObjects[idx].scale, 1));
                        if (area != 5) {
                            under_effects_small[underEffectsSmallIndex].setTextureRect(sf::IntRect{ 8 * choice, 48 + area * 8, 8, 8 });
                        }
                        else {
                            under_effects_small[underEffectsSmallIndex].setTextureRect(sf::IntRect{ 12 * choice, 48 + area * 8, 12, 8 });
                        }
                        underEffectsSmallIndex++;

                        break;
                    case ammo_pack:
                        if (allObjects[idx].alarm1 > 60 || int(allObjects[idx].alarm1 / 2) % 2) {
                            choice = int(allObjects[idx].image_index * 0.4f);
                            rotateable_effects_medium[rotateableEffectsMediumIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_effects_medium[rotateableEffectsMediumIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_effects_medium[rotateableEffectsMediumIndex].setRotation(0);
                            rotateable_effects_medium[rotateableEffectsMediumIndex].setScale(1, 1);
                            rotateable_effects_medium[rotateableEffectsMediumIndex].setTextureRect(sf::IntRect{ 16 * choice, 48, 16, 16 });
                            rotateableEffectsMediumIndex++;
                        }
                        break;
                    case plasma_particle:
                        choice = int(allObjects[idx].image_index / 10.0f);
                        rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setRotation(0);
                        rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setScale(1, 1);
                        rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setTextureRect(sf::IntRect{ 8 * choice, 24, 8, 8 });
                        rotateableEffectsSmallBloomIndex++;

                        break;
                    
                    case rad:
                        if (allObjects[idx].image_index > 60 || int(allObjects[idx].image_index / 2) % 2) {
                            choice = 0;
                            rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setRotation(allObjects[idx].rotation);
                            rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setScale(1, 1);
                            rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setTextureRect(sf::IntRect{ 8 * choice, 8, 8, 8 });
                            rotateableEffectsSmallBloomIndex++;
                        }
                        break;
                    case rad_destroy:
                        choice = allObjects[idx].image_index;
                        rotateable_effects_small[rotateableEffectsSmallIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_effects_small[rotateableEffectsSmallIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_effects_small[rotateableEffectsSmallIndex].setRotation(0);
                        rotateable_effects_small[rotateableEffectsSmallIndex].setTextureRect(sf::IntRect{ 8 * choice, 16, 8, 8 });
                        rotateableEffectsSmallIndex++;
                        break;
                    case bandit:
                        add_sprite_24(shadow24_ArrayIndex, allObjects[idx].position - cameraPos + offset24, draw_shadow24s);
                        shadow24_ArrayIndex++;      //shadow
                        rotateable_sprites_guns[rotateableSpriteGunIndex].setTexture(bandit_guntex);
                        rotateable_sprites_guns[rotateableSpriteGunIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_sprites_guns[rotateableSpriteGunIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_sprites_guns[rotateableSpriteGunIndex].setOrigin({ 16,16 });
                        rotateable_sprites_guns[rotateableSpriteGunIndex].setRotation(allObjects[idx].direction * degreestoradians);
                        rotateableSpriteGunIndex++;    //gun

                        all_enemy_sprites[allEnemySpritesIndex].setColor({ 255, 255, 255, 255 });
                        all_enemy_sprites[allEnemySpritesIndex].setPosition(allObjects[idx].position - cameraPos);
                        all_enemy_sprites[allEnemySpritesIndex].setScale(allObjects[idx].facing_right * 2 - 1, 1);

                        if (allObjects[idx].image_index >= 0) {
                            if (abs(allObjects[idx].speed.x) < 0.01f && abs(allObjects[idx].speed.y) < 0.01f) {
                                choice = int((allObjects[idx].image_index % 8) * 0.4);
                                choice2 = 0;
                            }
                            else {
                                choice = int((allObjects[idx].image_index % 12) * 0.4);
                                choice2 = 1;
                            }
                        }
                        else {
                            if (allObjects[idx].image_index < -3) {
                                choice = 0;
                            }
                            else {
                                choice = 1;
                            }
                            choice2 = 2;
                        }

                        all_enemy_sprites[allEnemySpritesIndex].setTextureRect(sf::IntRect{ 32 * choice, 32 * choice2, 32, 32 });
                        allEnemySpritesIndex++;

                        break;
                    case bandit_corpse:
                        all_enemy_corpses[allEnemyCorpsesIndex].setColor({ 255, 255, 255, 255 });
                        all_enemy_corpses[allEnemyCorpsesIndex].setPosition(allObjects[idx].position - cameraPos);
                        all_enemy_corpses[allEnemyCorpsesIndex].setScale(allObjects[idx].facing_right * 2 - 1, 1);

                        choice = int(allObjects[idx].image_index * 0.4f);
                        if (choice > 5) {
                            choice = 5;
                        }

                        //choice2 = 2;

                        all_enemy_corpses[allEnemyCorpsesIndex].setTextureRect(sf::IntRect{ 32 * choice, 32 * 2, 32, 32 });
                        allEnemyCorpsesIndex++;

                        break;
                    case player_bullet:
                        if (allObjects[idx].image_index == 1) {
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(playerbullet1_1tex);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                        }
                        else {
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(playerbullet1_2tex);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                        }
                        break;
                    case plasma_huge:
                        if (allObjects[idx].image_index <= 1) {
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setTexture(plasma_huge_1tex);
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setRotation(allObjects[idx].direction);
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setScale(0.5f + allObjects[idx].scale / 2, 0.5f + allObjects[idx].scale / 2);
                            rotateableSpriteBulletHugeIndex++;

                            rotateable_sprites_bullets_huge_bloom[rotateableSpriteBulletHugeBloomIndex].setTexture(plasma_huge_1_bloomtex);
                            rotateable_sprites_bullets_huge_bloom[rotateableSpriteBulletHugeBloomIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets_huge_bloom[rotateableSpriteBulletHugeBloomIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets_huge_bloom[rotateableSpriteBulletHugeBloomIndex].setRotation(allObjects[idx].direction);
                            rotateable_sprites_bullets_huge_bloom[rotateableSpriteBulletHugeBloomIndex].setScale(0.5f + allObjects[idx].scale / 2, 0.5f + allObjects[idx].scale / 2);
                            rotateableSpriteBulletHugeBloomIndex++;
                        }
                        else {
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setTexture(plasma_huge_2tex);
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setRotation(allObjects[idx].direction);
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setScale(0.5f + allObjects[idx].scale / 2, 0.5f + allObjects[idx].scale / 2);
                            rotateableSpriteBulletHugeIndex++;

                            rotateable_sprites_bullets_huge_bloom[rotateableSpriteBulletHugeBloomIndex].setTexture(plasma_huge_2_bloomtex);
                            rotateable_sprites_bullets_huge_bloom[rotateableSpriteBulletHugeBloomIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets_huge_bloom[rotateableSpriteBulletHugeBloomIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets_huge_bloom[rotateableSpriteBulletHugeBloomIndex].setRotation(allObjects[idx].direction);
                            rotateable_sprites_bullets_huge_bloom[rotateableSpriteBulletHugeBloomIndex].setScale(0.5f + allObjects[idx].scale / 2, 0.5f + allObjects[idx].scale / 2);
                            rotateableSpriteBulletHugeBloomIndex++;
                        }
                        break;
                    case plasma_big:
                        if (allObjects[idx].image_index <= 1) {
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setTexture(plasma_big_1tex);
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setRotation(allObjects[idx].direction);
                            rotateable_sprites_bullets_huge[rotateableSpriteBulletHugeIndex].setScale(0.5f + allObjects[idx].scale / 2, 0.5f + allObjects[idx].scale / 2);
                            rotateableSpriteBulletHugeIndex++;

                            rotateable_sprites_bullets_huge_bloom[rotateableSpriteBulletHugeBloomIndex].setTexture(plasma_big_1_bloomtex);
                            rotateable_sprites_bullets_huge_bloom[rotateableSpriteBulletHugeBloomIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets_huge_bloom[rotateableSpriteBulletHugeBloomIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets_huge_bloom[rotateableSpriteBulletHugeBloomIndex].setRotation(allObjects[idx].direction);
                            rotateable_sprites_bullets_huge_bloom[rotateableSpriteBulletHugeBloomIndex].setScale(0.5f + allObjects[idx].scale / 2, 0.5f + allObjects[idx].scale / 2);
                            rotateableSpriteBulletHugeBloomIndex++;
                        }
                        else {
                            rotateable_sprites_bullets_big[rotateableSpriteBulletBigIndex].setTexture(plasma_big_2tex);
                            rotateable_sprites_bullets_big[rotateableSpriteBulletBigIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets_big[rotateableSpriteBulletBigIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets_big[rotateableSpriteBulletBigIndex].setRotation(allObjects[idx].direction);
                            rotateable_sprites_bullets_big[rotateableSpriteBulletBigIndex].setScale(0.5f + allObjects[idx].scale / 2, 0.5f + allObjects[idx].scale / 2);
                            rotateableSpriteBulletBigIndex++;

                            rotateable_sprites_bullets_big_bloom[rotateableSpriteBulletBigBloomIndex].setTexture(plasma_big_2_bloomtex);
                            rotateable_sprites_bullets_big_bloom[rotateableSpriteBulletBigBloomIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets_big_bloom[rotateableSpriteBulletBigBloomIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets_big_bloom[rotateableSpriteBulletBigBloomIndex].setRotation(allObjects[idx].direction);
                            rotateable_sprites_bullets_big_bloom[rotateableSpriteBulletBigBloomIndex].setScale(0.5f + allObjects[idx].scale / 2, 0.5f + allObjects[idx].scale / 2);
                            rotateableSpriteBulletBigBloomIndex++;
                        }
                        break;
                    case plasma:
                        if (allObjects[idx].image_index <= 1) {
                            rotateable_sprites_bullets_big[rotateableSpriteBulletBigIndex].setTexture(plasma_1tex);
                            rotateable_sprites_bullets_big[rotateableSpriteBulletBigIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets_big[rotateableSpriteBulletBigIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets_big[rotateableSpriteBulletBigIndex].setRotation(allObjects[idx].direction);
                            rotateable_sprites_bullets_big[rotateableSpriteBulletBigIndex].setScale(0.5f + allObjects[idx].scale / 2, 0.5f + allObjects[idx].scale / 2);
                            rotateableSpriteBulletBigIndex++;

                            rotateable_sprites_bullets_big_bloom[rotateableSpriteBulletBigBloomIndex].setTexture(plasma_bloom_1tex);
                            rotateable_sprites_bullets_big_bloom[rotateableSpriteBulletBigBloomIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets_big_bloom[rotateableSpriteBulletBigBloomIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets_big_bloom[rotateableSpriteBulletBigBloomIndex].setRotation(allObjects[idx].direction);
                            rotateable_sprites_bullets_big_bloom[rotateableSpriteBulletBigBloomIndex].setScale(0.5f + allObjects[idx].scale / 2, 0.5f + allObjects[idx].scale / 2);
                            rotateableSpriteBulletBigBloomIndex++;
                        }
                        else {
                            rotateable_sprites_bullets_big[rotateableSpriteBulletBigIndex].setTexture(plasma_2tex);
                            rotateable_sprites_bullets_big[rotateableSpriteBulletBigIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets_big[rotateableSpriteBulletBigIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets_big[rotateableSpriteBulletBigIndex].setRotation(allObjects[idx].direction);
                            rotateable_sprites_bullets_big[rotateableSpriteBulletBigIndex].setScale(0.5f + allObjects[idx].scale / 2, 0.5f + allObjects[idx].scale / 2);
                            rotateableSpriteBulletBigIndex++;

                            rotateable_sprites_bullets_big_bloom[rotateableSpriteBulletBigBloomIndex].setTexture(plasma_bloom_2tex);
                            rotateable_sprites_bullets_big_bloom[rotateableSpriteBulletBigBloomIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets_big_bloom[rotateableSpriteBulletBigBloomIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets_big_bloom[rotateableSpriteBulletBigBloomIndex].setRotation(allObjects[idx].direction);
                            rotateable_sprites_bullets_big_bloom[rotateableSpriteBulletBigBloomIndex].setScale(0.5f + allObjects[idx].scale / 2, 0.5f + allObjects[idx].scale / 2);
                            rotateableSpriteBulletBigBloomIndex++;
                        }
                        break;
                    case plasma_hit:
                        choice = int(allObjects[idx].image_index * 0.4f);
                        switch (choice) {
                        default:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(plasma_hit_1tex);
                            break;
                        case 1:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(plasma_hit_2tex);
                            break;
                        case 2:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(plasma_hit_3tex);
                            break;
                        case 3:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(plasma_hit_4tex);
                            break;
                        }

                        rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                        rotateableSpriteBulletIndex++;

                        break;
                    case player_bullet_destroy:
                        choice = int(allObjects[idx].image_index * 0.4f);
                        switch (choice) {
                        case 0:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(playerbulletdelete1);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                            break;
                        case 1:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(playerbulletdelete2);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                            break;
                        case 2:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(playerbulletdelete3);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                            break;
                        case 3:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(bullet1_destroy4tex);        //same as enemybullet1
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                            break;
                        }
                        break;
                    case horror_bullet:
                        if (allObjects[idx].image_index == 1) {
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(horror_beamA1);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                        }
                        else {
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(horror_beamA2);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                        }
                        break;
                    case horror_bullet_destroy:
                        choice = int(allObjects[idx].image_index * 0.4f);
                        switch (choice) {
                        case 0:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(horror_beam_destroyA1);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                            break;
                        case 1:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(horror_beam_destroyA2);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                            break;
                        case 2:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(horror_beam_destroyA3);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                            break;
                        }
                        break;
                    case bullet2_destroy:
                        choice = int(allObjects[idx].image_index * 0.4f);
                        switch (choice) {
                        case 0:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(enemy_bullet_destroy2_1);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                            break;
                        case 1:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(enemy_bullet_destroy2_2);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                            break;
                        case 2:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(enemy_bullet_destroy2_3);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                            rotateableSpriteBulletIndex++;
                            break;
                        }
                        break;
                    default:
                        break;
                    }
                }
            }
        }

        sf::Text tC;
        float currentTime = clock.restart().asSeconds();
        fps = 1.0f / currentTime;
        
        tC.setString("fps: " + std::to_string(fps));
        tC.setCharacterSize(8);
        tC.setColor(sf::Color::Black);
        tC.setFont(font);
        tC.setPosition({ 2, 32 });

        //onscreen sprites drawn
        sf::Text tspr;

        tspr.setString("rads: " + std::to_string(player_rads));
        tspr.setCharacterSize(8);
        tspr.setFont(font);
        tspr.setColor(sf::Color::Black);
        tspr.setPosition({ 2, 52 });

        sf::Text debug1;

        int tmpNUMoffloors = 0;
        for (int i = left_physics; i <= right_physics; i++) {
            for (int j = top_physics; j <= bottom_physics; j++) {
                if (game_area[i][j].my_grid_type == exlpo_tile) {
                    tmpNUMoffloors++;
                }
            }
        }
        debug1.setString("rotateableSpriteBulletIndex: " + std::to_string(rotateableSpriteBulletIndex));
        debug1.setCharacterSize(8);
        debug1.setFont(font);
        debug1.setColor(sf::Color::Black);
        debug1.setPosition({ 2, 72 });

        sf::Text debug2;

        debug2.setString("bwep_reload: " + std::to_string(bwep_reload));
        debug2.setCharacterSize(8);
        debug2.setFont(font);
        debug2.setColor(sf::Color::Black);
        debug2.setPosition({ 2, 92 });


        //area in which physics happen
        vector2D_reset(top_physics - 6, bottom_physics + 6, left_physics - 6, right_physics + 6);       //make sure these dont go out of bounds

        //before drawing clear the rest of the vertex arrays which could have extra sprites from the previos frame, each array only  needs to be cleared if the sprite appears in the current "area"

        sf::RenderStates Renderer;
        sf::RenderStates RendererBloom;
        RendererBloom.blendMode = sf::BlendAdd;

        if(area == 1){

            clear_extra_vertex_array(draw_bullet1_1s, bullet1_1ArrayIndex);
            clear_extra_vertex_array(draw_bullet1_2BIGs, bullet1_2BIGArrayIndex);

            clear_extra_vertex_array(draw_middlewall1s, wall1ArrayIndex);
            clear_extra_vertex_array(draw_middlewall2s, wall2ArrayIndex);
            clear_extra_vertex_array(draw_middlewall3s, wall3ArrayIndex);
            clear_extra_vertex_array(draw_middlewall4s, wall4ArrayIndex);

            clear_extra_vertex_array(draw_boarderWalls, wallBoardeArrayIndex);

            clear_extra_vertex_array(draw_Wall1shadows, wallShadowArrayIndex);

            clear_extra_vertex_array(draw_botwall1s, wall1BOTArrayIndex);
            clear_extra_vertex_array(draw_botwall2s, wall2BOTArrayIndex);
            clear_extra_vertex_array(draw_botwall3s, wall3BOTArrayIndex);
            clear_extra_vertex_array(draw_botwall4s, wall4BOTArrayIndex);

            clear_extra_vertex_array(draw_floorTile1s, floor1ArrayIndex);
            clear_extra_vertex_array(draw_floorTile2s, floor2ArrayIndex);
            clear_extra_vertex_array(draw_floorTile3s, floor3ArrayIndex);
            clear_extra_vertex_array(draw_floorTile4s, floor4ArrayIndex);

            clear_extra_vertex_array(draw_floorTile1Bs, floor1BArrayIndex);
            clear_extra_vertex_array(draw_floorTile2Bs, floor2BArrayIndex);
            clear_extra_vertex_array(draw_floorTile3Bs, floor3BArrayIndex);
            clear_extra_vertex_array(draw_floorTile4Bs, floor4BArrayIndex);

            clear_extra_vertex_array(draw_exploTile1s, exploTile1ArrayIndex);
            clear_extra_vertex_array(draw_exploTile2s, exploTile2ArrayIndex);
            clear_extra_vertex_array(draw_exploTile3s, exploTile3ArrayIndex);
            clear_extra_vertex_array(draw_exploTile4s, exploTile4ArrayIndex);

            clear_extra_vertex_array(draw_exploTile1_unders, exploTile1_under_ArrayIndex);
            clear_extra_vertex_array(draw_floorTile1B_unders, floor1B_under_ArrayIndex);
            clear_extra_vertex_array(draw_floorTile1_unders, floor1_under_ArrayIndex);

            clear_extra_vertex_array(draw_shadow24s, shadow24_ArrayIndex);

            Renderer.texture = &exploTile1_under;
            buffer_under.draw(draw_exploTile1_unders, Renderer);

            Renderer.texture = &floorTile1B_under;
            buffer_under.draw(draw_floorTile1B_unders, Renderer);

            Renderer.texture = &floorTile1_under;
            buffer_under.draw(draw_floorTile1_unders, Renderer);

            //floors, drawn underneath explo tiles
            Renderer.texture = &floorTile1;
            buffer_under.draw(draw_floorTile1s, Renderer);

            Renderer.texture = &floorTile2;
            buffer_under.draw(draw_floorTile2s, Renderer);

            Renderer.texture = &floorTile3;
            buffer_under.draw(draw_floorTile3s, Renderer);

            Renderer.texture = &floorTile4;
            buffer_under.draw(draw_floorTile4s, Renderer);

            Renderer.texture = &floorTile1B;
            buffer_under.draw(draw_floorTile1Bs, Renderer);

            Renderer.texture = &floorTile2B;
            buffer_under.draw(draw_floorTile2Bs, Renderer);

            Renderer.texture = &floorTile3B;
            buffer_under.draw(draw_floorTile3Bs, Renderer);

            Renderer.texture = &floorTile4B;
            buffer_under.draw(draw_floorTile4Bs, Renderer);


            //explo tiles
            Renderer.texture = &exploTile1;
            buffer_under.draw(draw_exploTile1s, Renderer);

            Renderer.texture = &exploTile2;
            buffer_under.draw(draw_exploTile2s, Renderer);

            Renderer.texture = &exploTile3;
            buffer_under.draw(draw_exploTile3s, Renderer);

            Renderer.texture = &exploTile4;
            buffer_under.draw(draw_exploTile4s, Renderer);

            //details
            //debris
            for (sf::Sprite spr : under_effects_small) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_under.draw(spr);
            }
            reset_rotateable_sprites(under_effects_small, underEffectsSmallIndex);

            //enemy corpses
            for (sf::Sprite spr : all_enemy_corpses) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_under.draw(spr);
            }

            reset_rotateable_sprites(all_enemy_corpses, allEnemyCorpsesIndex);


            buffer_under.display();

            sf::Sprite combinedunder(buffer_under.getTexture());
            //window.draw(combinedunder);
            buffer_over.draw(combinedunder);
            

            //shadows now drawn

            Renderer.texture = &Wall1shadow;
            shadows.draw(draw_Wall1shadows, Renderer);
            Renderer.texture = &shadow24tex;
            shadows.draw(draw_shadow24s, Renderer);

            shadows.display();

            sf::Sprite combinedshadows(shadows.getTexture());
            combinedshadows.setColor(sf::Color(255, 255, 255, 100));
            //window.draw(combinedshadows);
            buffer_over.draw(combinedshadows);

            //walls
            Renderer.texture = &botWall1;
            buffer_over.draw(draw_botwall1s, Renderer);

            Renderer.texture = &botWall2;
            buffer_over.draw(draw_botwall2s, Renderer);

            Renderer.texture = &botWall3;
            buffer_over.draw(draw_botwall3s, Renderer);

            Renderer.texture = &botWall4;
            buffer_over.draw(draw_botwall4s, Renderer);

            //dust
            for (sf::Sprite spr : rotateable_effects_medium) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr);
            }
            reset_rotateable_sprites(rotateable_effects_medium, rotateableEffectsMediumIndex);

            //smoke
            for (sf::Sprite spr : rotateable_effects_large) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr);
            }
            reset_rotateable_sprites(rotateable_effects_large, rotateableEffectsLargeIndex);

            //debris
            for (sf::Sprite spr : rotateable_effects_small) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr);
            }
            reset_rotateable_sprites(rotateable_effects_small, rotateableEffectsSmallIndex);


            ////enemies////
            //bandit
            //guns
            //rotateable guns
            for (sf::Sprite spr : rotateable_sprites_guns) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr);
            }
            reset_rotateable_sprites(rotateable_sprites_guns, rotateableSpriteGunIndex);

            for (sf::Sprite spr : all_enemy_sprites) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr);
            }

            reset_rotateable_sprites(all_enemy_sprites, allEnemySpritesIndex);

            //bloom small effects
            for (sf::Sprite spr : rotateable_effects_small_bloom) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr);
            }
            //wait for after drawing blooms
            //reset_rotateable_sprites(rotateable_effects_small_bloom, rotateableEffectsSmallBloomIndex);

            //bullets / bullet destroys
            Renderer.texture = &bullet1_1tex;
            buffer_over.draw(draw_bullet1_1s, Renderer);

            //rotateable bullets_huge
            for (sf::Sprite spr : rotateable_sprites_bullets_huge) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr);
            }
            reset_rotateable_sprites(rotateable_sprites_bullets_huge, rotateableSpriteBulletHugeIndex);

            //rotateable bullets_big
            for (sf::Sprite spr : rotateable_sprites_bullets_big) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr);
            }
            reset_rotateable_sprites(rotateable_sprites_bullets_big, rotateableSpriteBulletBigIndex);


            //rotateable bullets
            for (sf::Sprite spr : rotateable_sprites_bullets) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr);
            }

            //bullet2
            batcher_bullet2.texture = &bullet2_1tex;
            batcher_bullet2.batchSprites(bullet_2_batchable);
            buffer_over.draw(batcher_bullet2, Renderer);

            batcher_bullet1.batchSprites(bullet_1_batchable);
            buffer_over.draw(batcher_bullet1, Renderer);

            reset_rotateable_sprites(bullet_1_batchable, bullet_1_batchableIndex);
            

            if (mouse_offset_window_center_y <= 0) {
                buffer_over.draw(wep_sprite);
            }
            buffer_over.draw(bwep_sprite);
            //player
            buffer_over.draw(player_sprite);

            if (mouse_offset_window_center_y > 0) {
                buffer_over.draw(wep_sprite);
            }
            
            //plasma impact
            for (sf::Sprite spr : plasma_impact_sprites) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr);
            }

            //idpd explosions
            for (sf::Sprite spr : idpd_explosions_sprites) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr);
            }


            //  !!! BLOOM START !!!  //


            for (sf::Sprite spr : idpd_explosions_sprites) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                spr.setScale(2, 2);
                spr.setColor({ 255, 255, 255, 25 });
                buffer_over.draw(spr, RendererBloom);  //bloom
                spr.setScale(1, 1);
                //spr.setColor({ 255, 255, 255, 255 });
            }
            reset_rotateable_sprites(idpd_explosions_sprites, IDPD_explosionIndex);


            for (sf::Sprite spr : plasma_impact_sprites) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                spr.setScale(2, 2);
                spr.setColor({ 255, 255, 255, 25 });
                buffer_over.draw(spr, RendererBloom);  //bloom
                spr.setScale(1, 1);
                //spr.setColor({ 255, 255, 255, 255 });
            }
            reset_rotateable_sprites(plasma_impact_sprites, plasmaImpactIDX);

            //bullets bloom order  doesnt really matter since they have add blending
            //enemy
            RendererBloom.texture = &bullet1_2BIGtex;
            buffer_over.draw(draw_bullet1_2BIGs, RendererBloom);

            for (sf::Sprite spr : rotateable_effects_small_bloom) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                spr.setScale(2, 2);
                spr.setColor({ 255, 255, 255, 25 });
                buffer_over.draw(spr, RendererBloom);
            }
            reset_rotateable_sprites(rotateable_effects_small_bloom, rotateableEffectsSmallBloomIndex);

            //rotateable bullets bloom / destroy blooms
            for (sf::Sprite spr : rotateable_sprites_bullets) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                spr.scale(2, 2);
                spr.setColor({ 255, 255, 255, 25 });
                buffer_over.draw(spr, RendererBloom);
                spr.scale(1, 1);
                spr.setColor({ 255, 255, 255, 255 });
            }

            reset_rotateable_sprites(rotateable_sprites_bullets, rotateableSpriteBulletIndex);

            //rotateable bullets_huge
            for (sf::Sprite spr : rotateable_sprites_bullets_huge_bloom) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr, RendererBloom);
            }
            reset_rotateable_sprites(rotateable_sprites_bullets_huge_bloom, rotateableSpriteBulletHugeBloomIndex);

            //rotateable bullets_big
            for (sf::Sprite spr : rotateable_sprites_bullets_big_bloom) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr, RendererBloom);
            }
            reset_rotateable_sprites(rotateable_sprites_bullets_big_bloom, rotateableSpriteBulletBigBloomIndex);


            //bullet2 bloom
            batcher_bullet2.texture = &bullet2_1BIGtex;
            batcher_bullet2.batchSprites(bullet_2_batchable);
            buffer_over.draw(batcher_bullet2, RendererBloom);
            reset_rotateable_sprites(bullet_2_batchable, bullet_2_batchableIndex);

            //player
            //buffer_over.draw(c);

            //wall boarder under wall tops
            Renderer.texture = &boarderWall;
            buffer_over.draw(draw_boarderWalls, Renderer);

            Renderer.texture = &middleWall1;
            buffer_over.draw(draw_middlewall1s, Renderer);

            Renderer.texture = &middleWall2;
            buffer_over.draw(draw_middlewall2s, Renderer);

            Renderer.texture = &middleWall3;
            buffer_over.draw(draw_middlewall3s, Renderer);

            Renderer.texture = &middleWall4;
            buffer_over.draw(draw_middlewall4s, Renderer);

            buffer_over.display();
            //draw all sprites that are over shadows
            //window.draw(buffer_overSprite);

        }
        else if(area == 2){

        }

        //buffer_over.draw(c);
        bool debug_text_show = 1;
        if (debug_text_show) {
            buffer_over.draw(tx);
            buffer_over.draw(ty);
            buffer_over.draw(ts);
            buffer_over.draw(tC);
            buffer_over.draw(tO);
            buffer_over.draw(tO0);
            buffer_over.draw(tspr);
            buffer_over.draw(debug1);
            buffer_over.draw(debug2);
        }
        if (!naitive_cursor_active) {
            buffer_over.draw(cursor_sprite);
        }

        //window.draw(bounding_defaul_res);

        current_frame++;

        window.draw(buffer_overSprite);
        
        //window.draw(bufferShadows);
        

        window.display();

    }
    return 0;
}
