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
int rotateable_sprites_guns_max = 500 * draw_mult;

std::vector<sf::Sprite> rotateable_sprites_guns_top;
int rotateable_sprites_guns_top_max = 500 * draw_mult;

//small effects 8x8 unrotateable
std::vector<sf::Sprite> rotateable_effects_small_bloom;
int rotateable_effects_small_bloom_max = 5500;
//small effects 8x8
std::vector<sf::Sprite> rotateable_effects_small;
int rotateable_effects_small_max = 3000;
//small effects 8x8 underneath
std::vector<sf::Sprite> under_effects_small;
int under_effects_small_max = 500;

//medium effects 16x16
std::vector<sf::Sprite> rotateable_effects_medium;
int rotateable_effects_medium_max = 6000;

//large effects 24x24
std::vector<sf::Sprite> rotateable_effects_large;
int rotateable_effects_large_max = 4000;

sf::Sprite portal_sprite;

sf::Sprite T2_sprite;
int T2_object_index = 1;
bool t2_draw_in_front = true;

std::vector<sf::Sprite> variable_textures;
int variable_textures_max = 400;


std::vector<sf::Sprite> variable_textures_bloom;
int variable_textures_bloom_max = 4000;

int wall_textures_max = 600;
std::vector<sf::Sprite> wall_textures;

int wall_boarder_textures_max = 600;
std::vector<sf::Sprite> wall_boarder_textures;

int floor_textures_max = 130;
std::vector<sf::Sprite> floor_textures;

int floor_textures_B_max = 100;
std::vector<sf::Sprite> floor_textures_B;

int wall_textures_bot_max = 260;
std::vector<sf::Sprite> wall_textures_bot;

int explo_tiles_tex_max = 600;
std::vector<sf::Sprite> explo_tiles_tex;



int T2_explo_tiles_tex_max = 600;
std::vector<sf::Sprite> T2_explo_tiles_tex;

int T2_floor_tiles_tex_max = 100;
std::vector<sf::Sprite> T2_floor_tiles_tex;

sf::Vector2f cameraPos = { 24000.0f, 24000.0f };

//text ingame
std::vector<sf::Text> popup_texts;
int popup_texts_max = 100;
int popup_text_index = 0;

static float degreestoradians = 57.2957795f;

sf::Vector2f offset8 = { -4, -4 };
sf::Vector2f offset16 = {-8, -8};
sf::Vector2f offset18 = { -9, -9 };
sf::Vector2f offset24 = { -12, -12 };
sf::Vector2f offset32 = { -16, -16 };
sf::Vector2f offset48 = { -24, -24 };
sf::Vector2f offset64 = { -32, -32 };

const int gridSize = 3000;
static int max_objects = 262144 / 4;
int current_create_start = 1;
//int curr_objcount = 1;   this is now redundant as threads break it   //important to keep this equal to the amount of objects active so increase when "adding" object and decrease when "removing" an object (setting it to "nothing" type) starts at one for the player object
int current_frame = 0;      //used for stuff like i-frames, reset this each area
int LOOPS = 19;
//game logic stuff
int area = 0;
int sub_area = 1;

int idpd_spawn_count = 0;

int enemy_count = 0;
int enemy_count_start = 0;  //enemy count at start of level
int lowest_corpse_lifetime = 65535;
int lowest_corpse_lifetime_ID = 0;
bool created_portal = false;
bool create_portal = false;
int corpse_delay = 50;
sf::Vector2f portal_camera_offset = { 0, 0 };
sf::Vector2f create_portal_POS = { 24016, 24016 };

bool killed_throne_2 = false;
bool can_move_outside_T2_arena = false;

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

//std::vector<std::vector<gridTile>> game_area(gridSize, std::vector<gridTile>(gridSize));
gridTile game_area[gridSize][gridSize];

//player stuff
int player_level = 1;
int player_rads = 99999;

bool player_invincible = false;

int player_bullets = 255;
int player_bolts = 55;
int player_shells = 55;
int player_explosives = 55;
int player_energy = 55;

int player_bullets_max = 255;
int player_bolts_max = 55;
int player_shells_max = 55;
int player_explosives_max = 55;
int player_energy_max = 55;

float global_ammo_mult = 1.0f;  //ammo mult deteremined by the player ammo and weapons

float player_friction_mult = 1.0f;

int player_max_rads = 60;
int player_hp = 12;
int player_max_hp = 12;
float player_max_speed = 4.0f;      //max should be less than 5.0f or else walls can be cliped through
bool is_Bskin = false;

int portal_wait_time = 30;

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
bool reloaded = true;
bool breloaded = true;

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
int plutonium_hunger = 120;       //set to 120 when mutation got 80 when not    nerfed from 140
int plutonium_hunger_ammo = 60;  //set to 60 when mutation got 30 when not      nerfed from 70
int impact_wrists = 0;
float long_arms = 1.0f;         //0.0f if no long arms, 1.0f if long arms
float trigger_fingers = 0.6f;
float laser_brain = 1.2f;
int second_stomach = 0;
int stress = 1;

//ultras
int ultra_picked = 2;   //0 = no ultra

int meltdown = 1;       //set to 2 when meltdown is picked

character player_character = horror;

//sounds

//these two are for 2d sound
std::vector<sf::Vector3f> play_sounds_this_frame_pos;
std::vector<int> play_sounds_this_frame_count;



//portal spiral stuff

int all_portal_spirals_start = 0;   //determines which portal spiral is drawn first
int all_portal_spirals_count = 0;
const int all_portal_spirals_max = 1000;
portal_spiral all_portal_spirals[all_portal_spirals_max];

//center of screen
const float center_of_screen_X = 160.0f;
const float center_of_screen_Y = 120.0f;

float portal_spiral_X = center_of_screen_X;
float portal_spiral_Y = center_of_screen_Y;

float portal_spiral_player_X = 160.0f;
float portal_spiral_player_Y = 120.0f;

float portal_spiral_angle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (1000.0f)));

bool portal_spiral_active = 0;

int portal_spiral_type = 1;
int portal_spiral_time = 0;
int portal_spiral_wave = 0;

float random(float max_value) {    //dont use in multithreaded for more randomness
    return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max_value)));
}

void create_portal_spiral() {
    all_portal_spirals_start++;
    all_portal_spirals_count++;
    if (all_portal_spirals_start > all_portal_spirals_max - 1) {
        all_portal_spirals_start = 0;
    }
    all_portal_spirals[all_portal_spirals_start].grow = 0;
    all_portal_spirals[all_portal_spirals_start].langle = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (360.0f)));
    all_portal_spirals[all_portal_spirals_start].lanim = -static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (300.0f)));
    all_portal_spirals[all_portal_spirals_start].lsound = 0;
    all_portal_spirals[all_portal_spirals_start].image_scale = 0.0f;
    all_portal_spirals[all_portal_spirals_start].image_angle = portal_spiral_angle;
    all_portal_spirals[all_portal_spirals_start].active = true;

    all_portal_spirals[all_portal_spirals_start].position = {portal_spiral_X, portal_spiral_Y};
}

void portal_spiral_step() {
    for (int i = 0; i < all_portal_spirals_max; i++) {
        if (all_portal_spirals[i].active == true) {
            all_portal_spirals[i].grow += 0.0002;
            all_portal_spirals[i].image_scale += all_portal_spirals[i].grow;
            all_portal_spirals[i].grow = (all_portal_spirals[i].grow + 1) * (1 + 0.0005f * all_portal_spirals[i].image_scale) - 1;
            /*if (!instance_exists(SpiralCont))
            {
                grow *= 1.5
                    UberCont.lisWallsUpdate = 1
            }*/
            if (all_portal_spirals[i].image_scale > 2 && (all_portal_spirals[i].lanim < 0 || all_portal_spirals[i].lanim > 6)) {
                all_portal_spirals_count--;
                all_portal_spirals[i].active = false;
                all_portal_spirals[i].image_scale = 0;
                all_portal_spirals[i].grow = 0;
            }
            all_portal_spirals[i].lanim += (0.2 + random(0.3));
        }
    }
}

void spiral_cont_step() {
    portal_spiral_angle += (8 + (sin(portal_spiral_angle / 300)));
    portal_spiral_time++;

    portal_spiral_X = center_of_screen_X + (sin(portal_spiral_angle / 921)) * (sin(portal_spiral_angle / 500)) * 80;
    portal_spiral_Y = center_of_screen_Y + (cos(portal_spiral_angle / 583)) * (sin(portal_spiral_angle / 500)) * 50;

    portal_spiral_wave++;
    if (portal_spiral_wave == 1) {
        portal_spiral_wave = 0;

        create_portal_spiral();
    }
}


//generation
bool want_gen = true;

void draw_text_NT(sf::Text text, sf::RenderTexture &renderer) {
    text.setColor(sf::Color::Black);
    text.setPosition(text.getPosition() + sf::Vector2f{ 1, 0 });
    renderer.draw(text);
    text.setPosition(text.getPosition() + sf::Vector2f{ 0, 1 });
    renderer.draw(text);
    text.setPosition(text.getPosition() + sf::Vector2f{ -1, 0 });
    renderer.draw(text);

    text.setPosition(text.getPosition() + sf::Vector2f{ 0, -1 });
    text.setColor(sf::Color::White);
    renderer.draw(text);
}

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

float angle_to_player_radians(sf::Vector2f position) {
    return atan2f(allObjects[0].position.y - position.y, allObjects[0].position.x - position.x);
}

void play_sound_relative_to_player(sound sound_id, float x, float y) {
    play_sounds_this_frame_pos[sound_id].x += x - allObjects[0].position.x;
    play_sounds_this_frame_pos[sound_id].y += y - allObjects[0].position.y;
    play_sounds_this_frame_count[sound_id]++;
}

void play_sound_on_player(sound sound_id) {
    play_sounds_this_frame_pos[sound_id].x = 0;
    play_sounds_this_frame_pos[sound_id].y = 0;
    play_sounds_this_frame_count[sound_id]++;
}

void stop_looping_sound(sound sound_id) {
    play_sounds_this_frame_pos[sound_id].x = 0;
    play_sounds_this_frame_pos[sound_id].y = 0;
    play_sounds_this_frame_count[sound_id] = -1;
}

int add_new_sound(enum sound sound_id, std::string filename_path, sound_sound_buffer all_sounds[], float pitch_variance, float attenuation = 1.0f, float volume = 100.0f) {
    if (!all_sounds[sound_id].sound_buffer.loadFromFile(filename_path)) {
        return -1;
    }
    all_sounds[sound_id].sound.setBuffer(all_sounds[sound_id].sound_buffer);
    all_sounds[sound_id].sound.setAttenuation(attenuation);
    all_sounds[sound_id].sound.setVolume(volume);
    all_sounds[sound_id].pitch_variance = pitch_variance;
    return 1;
}

void play_sound_random_pitch(sf::Sound &_sound, float variance, int i) {
    float pitch_offset = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (2.0f*variance))) - variance;
    _sound.setPitch(1 + pitch_offset);
    _sound.setPosition(play_sounds_this_frame_pos[i].x / play_sounds_this_frame_count[i], 0, play_sounds_this_frame_pos[i].y / play_sounds_this_frame_count[i]);
    _sound.play();
}

void corpse_step(int i) {
    if (allObjects[i].speeddir > 12.0f) {
        allObjects[i].speeddir = 12.0f;
    }
    if (allObjects[i].speeddir > 0.0f) {
        allObjects[i].speeddir -= allObjects[i].friction;
        allObjects[i].speed.x = cos(allObjects[i].direction) * allObjects[i].speeddir;
        allObjects[i].speed.y = sin(allObjects[i].direction) * allObjects[i].speeddir;
        allObjects[i].position += allObjects[i].speed;
    }
    allObjects[i].image_index++;

    if (enemy_count + idpd_spawn_count == 0) {
        if (allObjects[i].image_index < lowest_corpse_lifetime) {
            lowest_corpse_lifetime = allObjects[i].image_index;
            lowest_corpse_lifetime_ID = i;
        }
        if (lowest_corpse_lifetime_ID == i && !created_portal && allObjects[i].speeddir <= 0) {
            allObjects[i].alarm3--;
        }
        else {
            allObjects[i].alarm3 = corpse_delay;
        }
    }
    else {
        allObjects[i].alarm3 = corpse_delay;
    }
    if (allObjects[i].alarm3 < 0) {
        create_portal = true;
        create_portal_POS = allObjects[i].position;
    }

    return;
}

void reset_popup_texts() {
    for (int i = 0; i < popup_texts_max; i++) {
        popup_texts[i].setString("");
    }
}

void create_popuptext(std::string string, sf::Vector2f pos) {
    if (popup_text_index >= popup_texts_max) {
        popup_text_index = 0;
    }
    popup_texts[popup_text_index].setPosition(round(pos.x) - string.length() * 4, round(pos.y));
    popup_texts[popup_text_index].setLineSpacing(50);     //alarm
    popup_texts[popup_text_index].setString(string);
    popup_text_index++;
}

void pickup_ammo() {
    play_sound_relative_to_player(snd_ammo_pickup_ID, allObjects[0].position.x, allObjects[0].position.y);
    int wep_choice = 0;
    if (rand() % 2) {
        wep_choice = wep;
    }
    else {
        wep_choice = bwep;
    }
    if (wep_choice < melee_weps) {     //melee

        int choice = rand() % 5;
        switch (choice) {
        default:    //case 0:
            player_bullets += 32;
            if (player_bullets > player_bullets_max) {
                player_bullets = player_bullets_max;
                create_popuptext("MAX BULLETS", allObjects[0].position + sf::Vector2f{ 0, -8 });
            }
            else {
                create_popuptext("+32 BULLETS", allObjects[0].position + sf::Vector2f{ 0, -8 });
            }
            break;
        case 1:
            player_energy += 10;
            if (player_energy > player_energy_max) {
                player_energy = player_energy_max;
                create_popuptext("MAX ENERGY", allObjects[0].position + sf::Vector2f{ 0, -8 });
            }
            else {
                create_popuptext("+10 ENERGY", allObjects[0].position + sf::Vector2f{ 0, -8 });
            }
            break;
        case 2:
            player_shells += 8;
            if (player_shells > player_shells_max) {
                player_shells = player_shells_max;
                create_popuptext("MAX SHELLS", allObjects[0].position + sf::Vector2f{ 0, -8 });
            }
            else {
                create_popuptext("+8 SHELLS", allObjects[0].position + sf::Vector2f{ 0, -8 });
            }
            break;
        case 3:
            player_bolts += 7;
            if (player_bolts > player_bolts_max) {
                player_bolts = player_bolts_max;
                create_popuptext("MAX BOLTS", allObjects[0].position + sf::Vector2f{ 0, -8 });
            }
            else {
                create_popuptext("+7 BOLTS", allObjects[0].position + sf::Vector2f{ 0, -8 });
            }
            break;
        case 4:
            player_explosives += 6;
            if (player_explosives > player_explosives_max) {
                player_explosives = player_explosives_max;
                create_popuptext("MAX EXPLOSIVES", allObjects[0].position + sf::Vector2f{ 0, -8 });
            }
            else {
                create_popuptext("+6 EXPLOSIVES", allObjects[0].position + sf::Vector2f{ 0, -8 });
            }
            break;
        }
    }
    else if (wep < energy_weps) {    //energy weapons
        player_energy += 10;
        if (player_energy > player_energy_max) {
            player_energy = player_energy_max;
            create_popuptext("MAX ENERGY", allObjects[0].position + sf::Vector2f{ 0, -8 });
        }
        else {
            create_popuptext("+10 ENERGY", allObjects[0].position + sf::Vector2f{ 0, -8 });
        }
    }
}

void calculate_ammo_drop_mult() {
    global_ammo_mult = 0.0f;
    //wep
    if (wep < melee_weps) { //melee
        global_ammo_mult += 0.15f;
    }
    else if (wep < energy_weps) {
        if (player_energy < player_energy_max * 0.2f) {
            global_ammo_mult += 0.8f;
        }
        else if (player_energy < player_energy_max * 0.6f) {
            global_ammo_mult += 0.5f;
        }
        else {
            global_ammo_mult += 0.15f;
        }
    }

    //bwep
    if (bwep < melee_weps) { //melee
        global_ammo_mult += 0.15f;
    }
    else if (bwep < energy_weps) {
        if (player_energy < player_energy_max * 0.2f) {
            global_ammo_mult += 0.8f;
        }
        else if (player_energy < player_energy_max * 0.6f) {
            global_ammo_mult += 0.5f;
        }
        else {
            global_ammo_mult += 0.15f;
        }
    }
    //rabit paw
}

bool inline is_within_circle(sf::Vector2f pos1, sf::Vector2f pos2, float distance) {
    return (distance * distance) > ((pos1.x - pos2.x) * (pos1.x - pos2.x)) + ((pos1.y - pos2.y) * (pos1.y - pos2.y));
}

void make_T2_arena() {
    top_physics -= 100;
    bottom_physics += 100;
    left_physics -= 100;
    right_physics += 100;

    for (int i = left_physics-1; i < right_physics+1; i++) {
        for (int j = top_physics-1; j < bottom_physics+1; j++) {
            if (game_area[i][j].my_grid_type == wall && (i == left_physics || i == right_physics) || (j == bottom_physics || j == top_physics)) {
                game_area[i][j].my_grid_type = T2_boarder;
            }
            else if (game_area[i][j].my_grid_type == wall) {
                game_area[i][j].my_grid_type = void_tile;
            }
        }
    }
}

//returns object index
int create_object(float x, float y, float xspd, float yspd, objectID obj_id, float direction, int image_index) {
    int _i = int(x / 16);
    int _j = int(y / 16);
    int I = current_create_start;
    float tmpdir = 0.0f;
    for (int i = I; i < max_objects; i++) {
        if (allObjects[i].my_id == nothing) {
            switch (obj_id) {
            case throne_2:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = no_hitbox;

                allObjects[i].position = { x, y };
                allObjects[i].image_index = 0;
                allObjects[i].my_hp = 600 * round(1 + LOOPS / 3);

                allObjects[i].rad_drop = 70;

                allObjects[i].team = 1;     //what attack
                allObjects[i].size = 0;     //how many shots
                allObjects[i].walk_frames = (rand() % 2) * 2 - 1;

                allObjects[i].facing_right = rand() % 2;

                allObjects[i].gun_angle = random_360_radians();

                T2_object_index = i;

                allObjects[i].walk_direction = 0.0f;

                allObjects[i].alarm1 = 67;
                allObjects[i].alarm2 = 0;
                allObjects[i].alarm3 = 0;

                allObjects[i].hurt_ID = snd_throne_2_hurt_ID;
                allObjects[i].die_ID = snd_throne_2_die_ID;

                enemy_count++;
                t2_draw_in_front = true;
                break;
            case portal:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = portal_hitbox;

                allObjects[i].position = { x, y };
                allObjects[i].image_index = 0;
                allObjects[i].alarm1 = 0;
                allObjects[i].alarm2 = 0;
                if (area != 0) {
                    allObjects[i].alarm3 = 30;
                }
                else {
                    allObjects[i].alarm3 = 15;
                }
                play_sound_on_player(snd_portal_open_ID);
                play_sound_on_player(snd_portal_loop_ID);
                break;
            case portal_lightning:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = no_hitbox;

                allObjects[i].position = { x, y };
                allObjects[i].image_index = 0;
                allObjects[i].alarm1 = rand() % 5;
                allObjects[i].speed = { xspd, yspd };
                break;
            case portal_clear:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = portal_clear_hitbox;

                allObjects[i].position = { x, y };
                break;
            case bullet1:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = enemy_bullet_hitbox;
                allObjects[i].damage = 3;

                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].direction = direction * degreestoradians + 180.0f;
                allObjects[i].image_index = 0;
                allObjects[i].team = 2;     //enemy team
                break;
            case guardian_bullet:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = guardian_bullet_hitbox;
                allObjects[i].damage = 5;

                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].direction = direction;
                allObjects[i].image_index = 0;
                allObjects[i].team = 2;     //enemy team
                break;
            case large_guardian_bullet:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = guardian_bullet_hitbox;
                allObjects[i].damage = 12;

                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].direction = direction;

                allObjects[i].speeddir = sqrt((xspd * xspd) + (yspd * yspd));
                allObjects[i].image_index = 0;
                allObjects[i].team = 2;     //enemy team
                break;
            case T2_bullet:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = guardian_bullet_hitbox;
                allObjects[i].damage = 12;

                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].direction = direction;

                allObjects[i].speeddir = sqrt((xspd * xspd) + (yspd * yspd));
                allObjects[i].image_index = 0;
                allObjects[i].alarm1 = 15;
                allObjects[i].team = 2;     //enemy team
                break;
            case idpd_bullet:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = enemy_bullet_hitbox;
                allObjects[i].damage = 3;

                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].direction = direction * degreestoradians + 180.0f;
                allObjects[i].image_index = 0;
                allObjects[i].team = 2;     //enemy team
                break;
            case bullet2:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = enemy_bullet_hitbox;
                allObjects[i].damage = 2;

                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].direction = direction * degreestoradians + 180.0f;
                allObjects[i].image_index = 0;
                allObjects[i].team = 2;     //enemy team
                break;
            case rad:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = enemy_bullet_hitbox;

                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].image_index = 60 + ((150 + rand() % 30) / ((4 + LOOPS) / 4));   //60 is when the rad starts to blink
                allObjects[i].alarm1 = rand() % 12;
                allObjects[i].next_hurt = current_frame + 7 + rand() % 7;       //how much time to not be attracted to the player
                allObjects[i].rotation = random_360_degrees();
                break;
            case rad_destroy:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = no_hitbox;

                allObjects[i].position = { x, y };
                allObjects[i].image_index = 0;
                break;
            case ammo_pack:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = ammo_hitbox;

                allObjects[i].position = { x, y };
                allObjects[i].speed = { 0, 0 };
                allObjects[i].image_index = 0;
                allObjects[i].size = 1;
                allObjects[i].alarm1 = 60 + ((200 + rand() % 30) / ((5 + LOOPS) / 5));
                break;
            case health_pack:
                allObjects[i].my_id = ammo_pack;
                allObjects[i].my_hitbox = ammo_hitbox;

                allObjects[i].position = { x, y };
                allObjects[i].speed = { 0, 0 };
                allObjects[i].image_index = 0;
                allObjects[i].size = 2; //is health pack
                allObjects[i].alarm1 = 60 + ((200 + rand() % 30) / ((5 + LOOPS) / 5));
                break;
            case bandit:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = bandit_hitbox;

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

                allObjects[i].size = 1;

                allObjects[i].hurt_ID = snd_bandit_hurt_ID;
                allObjects[i].die_ID = snd_bandit_die_ID;

                allObjects[i].my_hitbox = bandit_hitbox;

                enemy_count++;

                break;
            case scorpion:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = no_hitbox;

                allObjects[i].position = { x, y };
                allObjects[i].speed = { 0, 0 };

                allObjects[i].speeddir = 0.0f;
                allObjects[i].direction = random_360_radians();
                allObjects[i].friction = 0.2f;

                allObjects[i].alarm1 = 30 + rand() % 90;

                allObjects[i].walk_frames = 0;

                allObjects[i].next_hurt = 0;
                allObjects[i].my_hp = round(15 * (1 + (LOOPS * 0.05f)));

                allObjects[i].size = 2;

                enemy_count++;
                break;
            case idpd_freak:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = idpd_freak_hitbox;

                allObjects[i].position = { x, y };
                allObjects[i].speed = { 0, 0 };

                allObjects[i].speeddir = 0.0f;
                allObjects[i].walk_direction = random_360_radians();
                allObjects[i].gun_angle = random_360_radians();
                allObjects[i].friction = 0.2f;

                allObjects[i].alarm1 = 20 + rand() % 10;
                allObjects[i].alarm2 = 0;
                allObjects[i].alarm3 = 0;

                allObjects[i].next_hurt = 0;
                allObjects[i].my_hp = round(30 * (1 + (LOOPS * 0.05f)));
                allObjects[i].image_index = rand() % 17;
                allObjects[i].team = 2;     //enemy team
                allObjects[i].rad_drop = 25;

                allObjects[i].size = 2;

                allObjects[i].hurt_ID = snd_idpd_freak_hurt_ID;
                allObjects[i].die_ID = snd_idpd_freak_die_ID;

                allObjects[i].my_hitbox = idpd_freak_hitbox;

                play_sound_relative_to_player(snd_idpd_freak_enter_ID, x, y);
                //clear nearby walls

                create_object(x, y, 0, 0, portal_clear, 0, 0);

                enemy_count++;

                break;
            case idpd_spawn:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = no_hitbox;

                allObjects[i].position = { x, y };
                allObjects[i].alarm1 = 40 + idpd_spawn_count * 3;
                allObjects[i].alarm2 = 52 + idpd_spawn_count * 3;
                allObjects[i].alarm3 = 5;
                allObjects[i].image_index = 0;
                idpd_spawn_count++;
                break;
            case player_bullet:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = enemy_bullet_hitbox;

                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].direction = direction * degreestoradians;
                allObjects[i].image_index = 0;
                allObjects[i].team = 1;     //player team
                break;
            case player_bullet_destroy:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = no_hitbox;

                allObjects[i].position = { x, y };
                allObjects[i].image_index = 0;
                allObjects[i].rotation = random_360_degrees();
                break;
            case horror_bullet:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = enemy_bullet_hitbox;
                allObjects[i].damage = 1;

                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].direction = direction * degreestoradians;
                allObjects[i].image_index = 0;
                allObjects[i].team = 1;     //player team
                break;
            case plasma_huge:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = plasma_hitbox;
                allObjects[i].damage = 25;

                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].scale = laser_brain; //bigger if laser brain
                allObjects[i].direction = direction * degreestoradians;
                allObjects[i].image_index = 0;
                allObjects[i].team = 1;     //player team
                allObjects[i].alarm1 = 0;
                allObjects[i].alarm2 = 0;   //tunneled
                allObjects[i].alarm3 = 0;   //whether the plasma has hit something
                break;
            case plasma_big:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = plasma_hitbox;
                allObjects[i].damage = 15;

                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].scale = 1.0f; //bigger if laser brain
                allObjects[i].direction = direction * degreestoradians;
                allObjects[i].image_index = image_index;
                allObjects[i].team = 1;     //player team
                allObjects[i].alarm1 = 0;
                allObjects[i].alarm2 = 0;   //tunneled
                allObjects[i].alarm3 = 0;   //whether the plasma has hit something
                break;
            case plasma:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = plasma_hitbox;
                allObjects[i].damage = 4;

                allObjects[i].position = { x, y };
                allObjects[i].speed = { xspd, yspd };
                allObjects[i].scale = 1.0f; //bigger if laser brain
                allObjects[i].direction = direction * degreestoradians;
                allObjects[i].image_index = image_index;
                allObjects[i].team = 1;     //player team
                allObjects[i].alarm1 = 0;
                allObjects[i].alarm2 = 0;   //tunneled
                allObjects[i].alarm3 = 0;   //whether the plasma has hit something
                break;
            case plasma_particle:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = no_hitbox;

                allObjects[i].position = { x, y };
                allObjects[i].image_index = 0;
                allObjects[i].alarm1 = 3 + (rand() % 2);    //3 or 4
                break;
            case plasma_impact:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = plasma_impact_hitbox;
                allObjects[i].damage = 10;

                allObjects[i].position = { x, y };
                allObjects[i].image_index = 0;
                allObjects[i].team = 2;     //enemy team
                play_sound_relative_to_player(snd_plasma_hit_ID, x, y);
                break;
            case plasma_hit:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = no_hitbox;

                allObjects[i].position = { x, y };
                allObjects[i].image_index = 0;
                allObjects[i].rotation = random_360_degrees();
                break;
            case ultra_slash:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = no_hitbox;
                allObjects[i].damage = 30;

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
                allObjects[i].my_hitbox = idpd_explosion_hitbox;
                allObjects[i].damage = 8;

                allObjects[i].position = { x, y };
                allObjects[i].image_index = 0;
                allObjects[i].team = 2;     //enemy team
                play_sound_relative_to_player(snd_explosion_ID, x, y);
                break;
            case idpd_nade:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = idpd_nade_hitbox;

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
                allObjects[i].my_hitbox = no_hitbox;

                allObjects[i].position = { x, y };
                allObjects[i].speed.x = xspd;
                allObjects[i].speed.y = yspd;
                allObjects[i].image_index = image_index;
                allObjects[i].alarm1 = int(direction); //how long til it disappears
                break;
            case debris:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = enemy_bullet_hitbox;
                allObjects[i].damage = 1;

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
                allObjects[i].my_hitbox = no_hitbox;

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
                allObjects[i].my_hitbox = no_hitbox;

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
                allObjects[i].my_hitbox = no_hitbox;

                allObjects[i].position = { x, y };
                allObjects[i].direction = direction;
                allObjects[i].image_index = 0;
                break;
            case detail:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = no_hitbox;

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
            case heal_FX:
                allObjects[i].my_id = obj_id;
                allObjects[i].my_hitbox = no_hitbox;

                allObjects[i].position = { x, y };
                allObjects[i].image_index = 0;
                break;
            default:
                break;
            }
            current_create_start = i + 1;       //helps alot with high object counts
            return i;
        }
    }
}

void pickup_health() {
    play_sound_relative_to_player(snd_hp_pickup_ID, allObjects[0].position.x, allObjects[0].position.y);
    player_hp += 2 + second_stomach;
    if (player_hp >= player_max_hp) {
        player_hp = player_max_hp;
        create_popuptext("MAX HP", allObjects[0].position + sf::Vector2f{ 0, -8 });
        if (second_stomach == 2) {

        }
        else {
            create_object(allObjects[0].position.x, allObjects[0].position.y, 0, 0, heal_FX, 0, 0);
        }
    }
    else if (second_stomach == 2) {
        create_popuptext("+4 HP", allObjects[0].position + sf::Vector2f{ 0, -8 });
    }
    else {
        create_popuptext("+2 HP", allObjects[0].position + sf::Vector2f{ 0, -8 });
        create_object(allObjects[0].position.x, allObjects[0].position.y, 0, 0, heal_FX, 0, 0);
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

void get_wep_reload_sound(int wep) {
    switch (wep) {
    case 11: //SPC
        if (laser_brain < 1.1f) {
            play_sound_on_player(snd_plasma_reload_ID);
        }
        else {
            play_sound_on_player(snd_plasma_reload_upgrade_ID);
        }
        break;
    default:
        break;
    }
}

sf::Vector2f wep_get_origin(int wep_id){
    switch (wep_id) {
    case 0: //ushov
        return sf::Vector2f( 5, 7 );
        break;
    case 11:    //SPC
        return sf::Vector2f( 3, 6 );
        break;
    default:
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
    default:
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

void destroy_projectile(int object_index) {
    float tmpdir;
    float tmpspd;
    float tmpspdX;
    float tmpspdY;
    switch (allObjects[object_index].my_id) {
    case horror_bullet:
        allObjects[object_index].my_id = horror_bullet_destroy;    //turn into a on hit effect
        allObjects[object_index].image_index = 0;
        allObjects[object_index].direction = random_360_degrees();
        break;
    case player_bullet:
        allObjects[object_index].my_id = player_bullet_destroy;    //turn into a on hit effect
        allObjects[object_index].image_index = 0;
        allObjects[object_index].direction = random_360_degrees();
        break;
    case bullet1:
        allObjects[object_index].my_id = bullet1_destroy;    //turn into a on hit effect
        allObjects[object_index].image_index = 0;
        allObjects[object_index].direction = random_360_degrees();
        break;
    case idpd_bullet:
        allObjects[object_index].my_id = idpd_bullet_destroy;    //turn into a on hit effect
        allObjects[object_index].image_index = 0;
        allObjects[object_index].direction = random_360_degrees();
        break;
    case bullet2:
        allObjects[object_index].my_id = bullet2_destroy;    //turn into a on hit effect
        allObjects[object_index].image_index = 0;
        allObjects[object_index].direction = random_360_degrees();
        break;
    case T2_bullet:
        allObjects[object_index].my_id = nothing;
        if (random(100) < 100 * global_ammo_mult) {
            if (random(player_max_hp) > player_hp && rand() % 3 != 0) {
                create_object(allObjects[object_index].position.x, allObjects[object_index].position.y, 0, 0, health_pack, 0, 0);
            }
            else {
                create_object(allObjects[object_index].position.x, allObjects[object_index].position.y, 0, 0, ammo_pack, 0, 0);
            }
        }
        break;
    case guardian_bullet:
        allObjects[object_index].my_id = guardian_bullet_destroy;    //turn into a on hit effect
        //allObjects[object_index].image_index = 0;
        allObjects[object_index].rotation = 0.0f;   //image_index
        allObjects[object_index].speed = { 0, 0 };
        allObjects[object_index].speeddir = 2.0f;
        allObjects[object_index].direction = random_360_degrees();
        motion_add_dir(random_360_radians(), 1, object_index);
        allObjects[object_index].friction = 0.3f + random(0.4f);
        break;
    case large_guardian_bullet:
        allObjects[object_index].my_id = guardian_bullet_destroy;    //turn into a on hit effect
        //allObjects[object_index].image_index = 0;
        allObjects[object_index].rotation = 0.0f;   //image_index
        allObjects[object_index].speed = { 0, 0 };
        allObjects[object_index].speeddir = 2.0f;
        allObjects[object_index].direction = random_360_degrees();
        allObjects[object_index].friction = 0.3f + random(0.4f);
        tmpdir = random_360_radians();
        tmpspd = 2.0f;
        for (int b = 0; b < 4; b++) {
            for (int i = 0; i < 7 + LOOPS; i++) {
                tmpspdX = cos(tmpdir) * tmpspd;
                tmpspdY = sin(tmpdir) * tmpspd;
                create_object(allObjects[object_index].position.x, allObjects[object_index].position.y, tmpspdX, tmpspdY, guardian_bullet, tmpdir, 0);
                tmpdir += (360.0f / float(7 + LOOPS)) / degreestoradians;
            }
            tmpspd += 0.5f;
        }

        if (random(100) < 100 * global_ammo_mult) {
            if (random(player_max_hp) > player_hp && rand() % 3 != 0) {
                create_object(allObjects[object_index].position.x, allObjects[object_index].position.y, 0, 0, health_pack, 0, 0);
            }
            else {
                create_object(allObjects[object_index].position.x, allObjects[object_index].position.y, 0, 0, ammo_pack, 0, 0);
            }
        }
        break;
    case idpd_nade:
        allObjects[object_index].my_id = idpd_explosion;
        allObjects[object_index].image_index = 0;  //make sure the first 3 frames are non-damaging

        tmpspd = 0.0f;
        for (int i = 0; i < 8; i++) {
            tmpspd = 1.0f + random(2.0f);
            create_object(allObjects[object_index].position.x, allObjects[object_index].position.y, tmpspd, tmpspd, smoke, 0, 0);    //smoke
        }
        for (int i = 0; i < 17; i++) {
            tmpspd = 5.0f + random(1.0f);
            create_object(allObjects[object_index].position.x, allObjects[object_index].position.y, tmpspd, tmpspd, dust, 0, 0);    //dust
        }
        play_sound_relative_to_player(snd_explosion_ID, allObjects[object_index].position.x, allObjects[object_index].position.y);
        break;
    case plasma:
        allObjects[object_index].my_id = plasma_impact;
        allObjects[object_index].image_index = -1;

        for (int i = 0; i < 3; i++) {
            create_object(allObjects[object_index].position.x, allObjects[object_index].position.y, 2, 2, smoke, 0, 0);    //smoke
        }

        play_sound_relative_to_player(snd_plasma_hit_ID, allObjects[object_index].position.x, allObjects[object_index].position.y);
        break;
    default:
        break;
    }
}

void clear_idpd_nade(int object_index) {
    allObjects[object_index].my_id = idpd_nade_remove;
    allObjects[object_index].image_index = rand() % 3;
    allObjects[object_index].scale = rand() % 2 * 2 - 1;
    allObjects[object_index].rotation = random_360_degrees();
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

bool is_within_throne_2(sf::Vector2f T2_pos, sf::Vector2f otherpos, int other_size) {
    //2 circles the should make up an acurate recreation of the original hitbox
    T2_pos += {0, 8};
    if (is_within_circle(T2_pos, otherpos, (other_size + 40))) {
        return true;
    }
    T2_pos += {0, 23};
    if (is_within_circle(T2_pos, otherpos, (other_size + 40))) {
        return true;
    }
    return false;
}

void clear_all_bullets() {      //clear all enemy bullets
    objectID curr_id = nothing;
    for (int i = 1; i < max_objects; i++) {
        if (allObjects[i].my_id == idpd_nade) {
            clear_idpd_nade(i);
        }
        else if(allObjects[i].my_id == bullet1 || allObjects[i].my_id == bullet2 || allObjects[i].my_id == guardian_bullet || allObjects[i].my_id == horror_bullet || 
            allObjects[i].my_id == player_bullet || allObjects[i].my_id == idpd_bullet || allObjects[i].my_id == T2_bullet || allObjects[i].my_id == large_guardian_bullet) {
            destroy_projectile(i);
        }
    }
}

void enemy_hurt(int ENEMY, int PROJ) {
    allObjects[ENEMY].next_hurt = current_frame + 6;
    allObjects[ENEMY].image_index = -6;
    motion_add_XY_speed(allObjects[PROJ].speed.x, allObjects[PROJ].speed.y, ENEMY);   //knockback
    play_sound_relative_to_player(allObjects[ENEMY].hurt_ID, allObjects[ENEMY].position.x, allObjects[ENEMY].position.y);
}

void enemy_die(int ENEMY, int PROJ) {
    if (PROJ > 0) {     //is killed by and object (not anomaly)
        allObjects[ENEMY].speed = allObjects[PROJ].speed;
        motion_add_XY_speed(allObjects[PROJ].speed.x, allObjects[PROJ].speed.y, ENEMY);   //knockback
    }
    else {
        motion_add_dir(random_360_radians(), random(4.0f), ENEMY);
    }
    allObjects[ENEMY].image_index = 0;
    allObjects[ENEMY].friction = 0.4f;

    int current_object = 0;

    //create rads
    float tempSpdx = 0.0f;
    float tempSpdy = 0.0f;

    if (allObjects[ENEMY].my_id != throne_2) {
        for (int i = allObjects[ENEMY].rad_drop; i > 0; i--) {
            tempSpdx = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 6.0f)) - 3.0f;
            tempSpdy = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 6.0f)) - 3.0f;
            create_object(allObjects[ENEMY].position.x, allObjects[ENEMY].position.y, tempSpdx, tempSpdy, rad, 0.0f, 0);
        }
    }

    if (abs(allObjects[ENEMY].speed.x) < 1.0f && abs(allObjects[ENEMY].speed.y) < 1.0f) {
        allObjects[ENEMY].direction = random_360_radians();
    }

    //specific enemy stuff
    float tmpdir = 0.0f;
    float tmpSpd = 0.0f;
    switch (allObjects[ENEMY].my_id) {
    case throne_2:
        motion_add_dir(random_360_radians(), 4.5f, ENEMY);
        allObjects[ENEMY].speeddir = 1.0f;
        clear_all_bullets();
        allObjects[ENEMY].my_id = throne_2_death;
        allObjects[ENEMY].alarm1 = 80;
        killed_throne_2 = true;
        break;
    case bandit:
        //convert into corpse
        allObjects[ENEMY].my_id = bandit_corpse;

        //ammo drop
        if (random(100) < 16 * global_ammo_mult) {
            if (random(player_max_hp) > player_hp && rand() % 3 != 0) {
                create_object(allObjects[ENEMY].position.x, allObjects[ENEMY].position.y, 0, 0, health_pack, 0, 0);
            }
            else {
                create_object(allObjects[ENEMY].position.x, allObjects[ENEMY].position.y, 0, 0, ammo_pack, 0, 0);
            }
        }

        //debug start
        for (int i = 0; i < 10; i++) {
            tmpdir = random_360_radians();
            tmpSpd = random(2.0f) + 3.0f;
            tempSpdx = cos(tmpdir) * tmpSpd;
            tempSpdy = sin(tmpdir) * tmpSpd;
            create_object(allObjects[ENEMY].position.x,
                allObjects[ENEMY].position.y,
                tempSpdx,
                tempSpdy, bullet2, tmpdir + 180.0f / degreestoradians, 0);
        }
        //debug end
        break;
    case idpd_freak:

        //ammo drop
        if (random(100) < 60 * global_ammo_mult) {
            if (random(player_max_hp) > player_hp && rand() % 3 != 0) {
                create_object(allObjects[ENEMY].position.x, allObjects[ENEMY].position.y, 0, 0, health_pack, 0, 0);
            }
            else {
                create_object(allObjects[ENEMY].position.x, allObjects[ENEMY].position.y, 0, 0, ammo_pack, 0, 0);
            }
        }

        if (rand() % 4 == 0) {
            for (int i = 0; i < 3; i++) {
                tmpdir = allObjects[ENEMY].direction;
                current_object = create_object(allObjects[ENEMY].position.x, allObjects[ENEMY].position.y, 4, 0, idpd_nade, tmpdir, 0);
                motion_add_dir(random_360_radians(), 4, current_object);
            }
        }

        //convert into corpse
        allObjects[ENEMY].my_id = idpd_freak_corpse;
        allObjects[ENEMY].alarm1 = 800; //revive time
        break;
    default:
        break;
    }

    //reload
    wep_reload *= trigger_fingers;
    bwep_reload *= trigger_fingers;

    enemy_count--;
    allObjects[ENEMY].alarm3 = corpse_delay;  //delay when killin last enemy

    play_sound_relative_to_player(allObjects[ENEMY].die_ID, allObjects[ENEMY].position.x, allObjects[ENEMY].position.y);
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

void enemy_push(int currOBJ, int O) {
    if (allObjects[O].size >= allObjects[currOBJ].size
        && is_within_circle(allObjects[O].position, allObjects[currOBJ].position, allObjects[currOBJ].my_hitbox + allObjects[O].my_hitbox)) {
        float diffx = 0.0f;
        float diffy = 0.0f;
        float tmpdir = 0.0f;
        diffx = allObjects[O].position.x - allObjects[currOBJ].position.x;
        diffy = allObjects[O].position.y - allObjects[currOBJ].position.y;

        tmpdir = atan2f(diffy, diffx) + 180.0f / degreestoradians;
        motion_add_dir(tmpdir, 1.0f, currOBJ);
    }
}

void corpse_hit(int O, int currOBJ) {
    if (allObjects[O].speeddir > 1.0f && allObjects[currOBJ].next_hurt < current_frame) {
        if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, allObjects[O].my_hitbox + allObjects[currOBJ].my_hitbox)) {
            allObjects[currOBJ].my_hp -= 1 + impact_wrists;
            if (allObjects[currOBJ].my_hp > 0) {
                enemy_hurt(currOBJ, O);
            }
            else {  //dead
                enemy_die(currOBJ, O);
            }
            allObjects[O].speeddir *= 0.5f;
        }
    }
}

void horror_bullet_collision(int currOBJ, int i, int j) {
    for (int w = -1; w < 2; w++) {      //horror_bullet collison
        for (int h = -1; h < 2; h++) {
            for (int O : game_area[i + w][j + h].object_indexes) {
                //destroy projectiles
                if (allObjects[currOBJ].my_id != horror_bullet) {
                    break;
                }
                if (allObjects[O].team != player_team && is_within_circle(allObjects[currOBJ].position, allObjects[O].position, allObjects[O].my_hitbox + allObjects[currOBJ].my_hitbox)) {
                    switch (allObjects[O].my_id) {
                    case bullet1:
                        destroy_projectile(currOBJ);
                        destroy_projectile(O);
                        break;
                    case idpd_bullet:
                        destroy_projectile(currOBJ);
                        destroy_projectile(O);
                        break;
                    case guardian_bullet:
                        destroy_projectile(currOBJ);
                        destroy_projectile(O);
                        break;
                    case large_guardian_bullet:
                        destroy_projectile(currOBJ);
                        destroy_projectile(O);
                        break;
                    case T2_bullet:
                        destroy_projectile(currOBJ);
                        destroy_projectile(O);
                        break;
                    case bullet2:
                        destroy_projectile(currOBJ);
                        destroy_projectile(O);
                        break;
                    case idpd_nade:
                        destroy_projectile(currOBJ);
                        destroy_projectile(O);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }
}

void bullet_collide_player(int O, int currOBJ) {
    if (allObjects[O].team != allObjects[currOBJ].team && is_within_circle(allObjects[currOBJ].position, allObjects[O].position, allObjects[O].my_hitbox + player_hitbox)) {
        if (allObjects[currOBJ].next_hurt < current_frame && !player_invincible) {
            motion_add_XY_speed(allObjects[O].speed.x, allObjects[O].speed.y, currOBJ);
        }
        destroy_projectile(O);
        if (allObjects[currOBJ].next_hurt < current_frame && !player_invincible) {
            play_sound_relative_to_player(snd_player_hurt_ID, allObjects[0].position.x, allObjects[0].position.y);
            player_hp -= allObjects[O].damage;
            allObjects[currOBJ].next_hurt = current_frame + 6;
            allObjects[currOBJ].image_index = 0;

        }
    }
}

void player_collision(int i, int j, int currOBJ) {
    float diffx = 0.0f;
    float diffy = 0.0f;
    float tmpdir = 0.0f;
    for (int w = -5; w < 6; w++) {
        for (int h = -5; h < 6; h++) {
            for (int O : game_area[i + w][j + h].object_indexes) {
                    switch (allObjects[O].my_id) {
                    case bullet2:
                        bullet_collide_player(O, currOBJ);
                        break;
                    case bullet1:
                        bullet_collide_player(O, currOBJ);
                        break;
                    case idpd_bullet:
                        bullet_collide_player(O, currOBJ);
                        break;
                    case guardian_bullet:
                        bullet_collide_player(O, currOBJ);
                        break;
                    case large_guardian_bullet:
                        bullet_collide_player(O, currOBJ);
                        break;
                    case T2_bullet:
                        bullet_collide_player(O, currOBJ);
                        break;
                    case objectID::portal:
                        if (allObjects[O].alarm1 == 0 && is_within_circle(allObjects[currOBJ].position, allObjects[O].position, portal_hitbox + player_hitbox)) {
                            allObjects[O].alarm1 = 1;
                            allObjects[O].alarm2 = portal_wait_time;
                            play_sound_on_player(snd_portal_close_ID);
                        }
                        break;
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
                            if (allObjects[O].size == 1) {
                                pickup_ammo();
                                allObjects[O].my_id = ammo_pack_destroy;     //disappear sprite vs. picked up sprite is 2
                                allObjects[O].size = 2;
                                allObjects[O].image_index = 0;
                                //player pick up ammo
                            }
                            else {
                                pickup_health();
                                allObjects[O].my_id = ammo_pack_destroy;     //disappear sprite vs. picked up sprite is 2
                                allObjects[O].size = 2;
                                allObjects[O].image_index = 0;
                            }

                        }
                        break;
                    case objectID::bandit:
                        diffx = allObjects[O].position.x - allObjects[currOBJ].position.x;
                        diffy = allObjects[O].position.y - allObjects[currOBJ].position.y;
                        if (is_within_circle(allObjects[currOBJ].position, allObjects[O].position, bandit_hitbox + player_hitbox)) {
                            tmpdir = atan2f(diffy, diffx) + 180.0f / degreestoradians;

                            motion_add_dir(tmpdir, 0.5f, currOBJ);  //the bigger the enemy the more it pushes: speed = size * 0.5
                        }
                        break;
                    case objectID::idpd_freak:
                        diffx = allObjects[O].position.x - allObjects[currOBJ].position.x;
                        diffy = allObjects[O].position.y - allObjects[currOBJ].position.y;
                        if (is_within_circle(allObjects[currOBJ].position, allObjects[O].position, idpd_freak_hitbox + player_hitbox)) {
                            tmpdir = atan2f(diffy, diffx) + 180.0f / degreestoradians;

                            motion_add_dir(tmpdir, 1.0f, currOBJ);  //the bigger the enemy the more it pushes: speed = size * 0.5
                            if (allObjects[O].alarm3 < 0 && allObjects[currOBJ].next_hurt < current_frame) { //melee cooldown
                                play_sound_relative_to_player(snd_player_hurt_ID, allObjects[0].position.x, allObjects[0].position.y);
                                allObjects[O].alarm3 = 25;
                                player_hp -= 5;
                                allObjects[currOBJ].next_hurt = current_frame + 6;
                                allObjects[currOBJ].image_index = 0;
                                motion_add_dir(tmpdir, 4.0f, currOBJ);
                            }
                        }
                        break;
                    case objectID::idpd_explosion:
                        if (!player_invincible && (allObjects[O].image_index == 3 || allObjects[O].image_index == 4) && is_within_circle(allObjects[currOBJ].position, allObjects[O].position, 48 + player_hitbox)) {
                            play_sound_relative_to_player(snd_player_hurt_ID, allObjects[0].position.x, allObjects[0].position.y);
                            player_hp -= 8;
                            allObjects[currOBJ].next_hurt = current_frame + 6;
                            allObjects[currOBJ].image_index = 0;
                            tmpdir = atan2f(allObjects[currOBJ].position.y - allObjects[O].position.y, allObjects[currOBJ].position.x - allObjects[O].position.x);
                            allObjects[O].speed.x = cos(tmpdir) * 12;
                            allObjects[O].speed.y = sin(tmpdir) * 12; //this is so the enemy_hurt() function works
                            motion_add_XY_speed(allObjects[O].speed.x, allObjects[O].speed.y, currOBJ);
                        }
                        break;
                    default:
                        break;
                    }

            }
        }
    }
}

// collision logic
void basic_enemy_collision(int currOBJ, int i, int j) {
    float diffx = 0.0f;
    float diffy = 0.0f;
    float tmpdir = 0.0f;
    for (int w = -1; w < 2; w++) {
        for (int h = -1; h < 2; h++) {
            for (int O : game_area[i + w][j + h].object_indexes) {
                if (allObjects[currOBJ].my_hp > 0 && O != currOBJ) {
                    if (allObjects[i].my_id == bullet1 || allObjects[i].my_id == bullet2 || allObjects[i].my_id == guardian_bullet || allObjects[i].my_id == horror_bullet ||
                        allObjects[i].my_id == player_bullet || allObjects[i].my_id == idpd_bullet || allObjects[i].my_id == T2_bullet || allObjects[i].my_id == large_guardian_bullet) {
                        if (allObjects[O].team != enemy_team && is_within_circle(allObjects[currOBJ].position, allObjects[O].position, allObjects[currOBJ].my_hitbox + allObjects[O].my_hitbox)) {
                            destroy_projectile(O);
                            play_sound_relative_to_player(allObjects[currOBJ].hurt_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
                            allObjects[currOBJ].my_hp -= allObjects[O].damage;
                            allObjects[currOBJ].next_hurt = current_frame + 6;
                            allObjects[currOBJ].image_index = 0;
                            motion_add_XY_speed(allObjects[O].speed.x, allObjects[O].speed.y, currOBJ);
                        }
                    }
                    else {
                        switch (allObjects[O].my_id) {
                        case objectID::bandit:
                            enemy_push(currOBJ, O);
                            break;
                        case objectID::idpd_freak:
                            enemy_push(currOBJ, O);
                            break;
                        case objectID::bandit_corpse:
                            corpse_hit(O, currOBJ);
                            break;
                        case objectID::idpd_freak_corpse:
                            corpse_hit(O, currOBJ);
                            break;
                        case objectID::debris:
                            if (allObjects[O].speeddir > 1.0f && allObjects[currOBJ].next_hurt < current_frame) {
                                if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, 6)) {
                                    allObjects[currOBJ].my_hp -= 1;
                                    if (allObjects[currOBJ].my_hp > 0) {
                                        enemy_hurt(currOBJ, O);
                                    }
                                    else {  //dead
                                        enemy_die(currOBJ, O);
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
    }
}

void plasma_impact_collision_2(int currOBJ, int O) {
    float tmpdir = 0.0f;
    allObjects[O].my_hp -= 10;
    tmpdir = atan2f(allObjects[currOBJ].position.y - allObjects[O].position.y, allObjects[currOBJ].position.x - allObjects[O].position.x);
    allObjects[currOBJ].speed.x = cos(tmpdir) * 8;
    allObjects[currOBJ].speed.y = sin(tmpdir) * 8; //this is so the enemy_hurt() function works with kb
    if (allObjects[O].my_hp > 0) {
        enemy_hurt(O, currOBJ);
    }
    else {  //dead
        enemy_die(O, currOBJ);
    }
}
void plasma_impact_collision(int currOBJ, int i, int j) {
    for (int w = -3; w < 4; w++) {
        for (int h = -3; h < 4; h++) {
            for (int O : game_area[i + w][j + h].object_indexes) {
                switch (allObjects[O].my_id) {
                case bandit:
                    if (allObjects[O].next_hurt < current_frame && is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (bandit_hitbox + 32))) {
                        plasma_impact_collision_2(currOBJ, O);
                    }
                    break;
                case idpd_freak:
                    if (allObjects[O].next_hurt < current_frame && is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (idpd_freak_hitbox + 32))) {
                        plasma_impact_collision_2(currOBJ, O);
                    }
                    break;
                default:
                    break;
                }
            }
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

void plasma_hurt(int plasma, int other, int damage) {
    if (allObjects[plasma].alarm3 == 0) {
        allObjects[plasma].alarm3 = 1;  //cant do damage again this frame
        allObjects[other].my_hp -= round(damage * allObjects[plasma].scale);
        if (allObjects[other].my_hp > 0) {
            enemy_hurt(other, plasma);
        }
        else {  //dead
            enemy_die(other, plasma);
        }
        //create on hit effect
        create_object(allObjects[plasma].position.x, allObjects[plasma].position.y, 0, 0, player_bullet_destroy, 0, 0);
        create_object(allObjects[other].position.x, allObjects[other].position.y, 0, 0, plasma_hit, 0, 0);

        allObjects[plasma].scale -= 0.1f;
        allObjects[plasma].position -= allObjects[plasma].speed;
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
                            plasma_hurt(huge_plasma, O, 25);
                            goto exit_huge_plasma;
                        }
                        break;
                    case idpd_freak:
                        if (is_within_circle(allObjects[O].position, allObjects[huge_plasma].position, (idpd_freak_hitbox + allObjects[huge_plasma].scale * plasma_hitbox))) {
                            plasma_hurt(huge_plasma, O, 25);
                            goto exit_huge_plasma;
                        }
                        break;
                    case throne_2:
                        if (allObjects[O].alarm1 < 0 && is_within_throne_2(allObjects[O].position, allObjects[huge_plasma].position, allObjects[huge_plasma].scale * plasma_hitbox)) {
                            plasma_hurt(huge_plasma, O, 25);
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
                            plasma_hurt(big_plasma, O, 15);
                            goto exit_big_plasma;
                        }
                        break;
                    case idpd_freak:
                        if (is_within_circle(allObjects[O].position, allObjects[big_plasma].position, (idpd_freak_hitbox + allObjects[big_plasma].scale * plasma_hitbox))) {
                            plasma_hurt(big_plasma, O, 15);
                            goto exit_big_plasma;
                        }
                        break;
                    case throne_2:
                        if (allObjects[O].alarm1 < 0 && is_within_throne_2(allObjects[O].position, allObjects[big_plasma].position, allObjects[big_plasma].scale * plasma_hitbox)) {
                            plasma_hurt(big_plasma, O, 15);
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
                        plasma_hurt(plasma, O, 4);
                        goto exit_plasma;
                    }
                    break;
                case idpd_freak:
                    if (is_within_circle(allObjects[O].position, allObjects[plasma].position, (bandit_hitbox + allObjects[plasma].scale * plasma_hitbox))) {
                        plasma_hurt(plasma, O, 4);
                        goto exit_plasma;
                    }
                    break;
                case throne_2:
                    if (allObjects[O].alarm1 < 0 && is_within_throne_2(allObjects[O].position, allObjects[plasma].position, allObjects[plasma].scale * plasma_hitbox)) {
                        plasma_hurt(plasma, O, 4);
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
                allObjects[plasma].position -= allObjects[plasma].speed;
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
        destroy_projectile(plasma);
    }
}

void ultra_slash_collision(int currOBJ, int i, int j) {
    for (int w = -7; w < 8; w++) {
        for (int h = -7; h < 8; h++) {
            for (int O : game_area[i + w][j + h].object_indexes) {
                if (allObjects[currOBJ].alarm3 == 0 && game_area[i + w][j + h].my_grid_type == wall && is_within_circle(sf::Vector2f(((i + w) * 16) + 8, ((j + h) * 16) + 8), allObjects[currOBJ].position, (wall_hitbox + 24))) {
                    allObjects[currOBJ].position -= allObjects[currOBJ].speed;
                    allObjects[currOBJ].alarm3 = 1;
                }
                switch (allObjects[O].my_id) {
                case throne_2:
                    if (allObjects[O].alarm1 < 0 && allObjects[O].next_hurt < current_frame &&
                        (is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position + sf::Vector2f{ 0, 8 }, 40, allObjects[currOBJ].direction)
                      || is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position + sf::Vector2f{ 0, 31 }, 40, allObjects[currOBJ].direction))) {
                        allObjects[O].my_hp -= 30;
                        if (allObjects[O].my_hp > 0) {
                            enemy_hurt(O, currOBJ);
                        }
                        else {  //dead
                            enemy_die(O, currOBJ);
                        }
                    }
                    break;
                case bandit:
                    if (allObjects[O].next_hurt < current_frame && is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position, bandit_hitbox, allObjects[currOBJ].direction)) {
                        allObjects[O].my_hp -= 30;
                        if (allObjects[O].my_hp > 0) {
                            enemy_hurt(O, currOBJ);
                        }
                        else {  //dead
                            enemy_die(O, currOBJ);
                        }
                    }
                    break;
                case idpd_freak:
                    if (allObjects[O].next_hurt < current_frame && is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position, bandit_hitbox, allObjects[currOBJ].direction)) {
                        allObjects[O].my_hp -= 30;
                        if (allObjects[O].my_hp > 0) {
                            enemy_hurt(O, currOBJ);
                        }
                        else {  //dead
                            enemy_die(O, currOBJ);
                        }
                    }
                    break;
                case idpd_nade:
                    if (is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position, idpd_nade_hitbox, allObjects[currOBJ].direction)) {
                        allObjects[O].direction = allObjects[currOBJ].direction;
                        allObjects[O].speeddir = 12.0f;
                        allObjects[O].alarm2 = 4;
                        allObjects[O].friction = 0.0f;
                        allObjects[O].team = -1;    //reflected
                        create_object(allObjects[O].position.x, allObjects[O].position.y, 0, 0, deflect, allObjects[currOBJ].direction * degreestoradians, 0);
                    }

                    break;
                case bullet1:
                    if (allObjects[O].team != 1 && is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position, enemy_bullet_hitbox, allObjects[currOBJ].direction)) {
                        allObjects[O].direction = allObjects[currOBJ].direction * degreestoradians + 180.0f;
                        allObjects[O].speed.x = cos(allObjects[currOBJ].direction) * 4.0f;
                        allObjects[O].speed.y = sin(allObjects[currOBJ].direction) * 4.0f;
                        allObjects[O].team = 1;
                        create_object(allObjects[O].position.x, allObjects[O].position.y, 0, 0, deflect, allObjects[currOBJ].direction * degreestoradians, 0);
                    }
                    break;
                case idpd_bullet:
                    if (allObjects[O].team != 1 && is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position, enemy_bullet_hitbox, allObjects[currOBJ].direction)) {
                        allObjects[O].direction = allObjects[currOBJ].direction * degreestoradians + 180.0f;
                        allObjects[O].speed.x = cos(allObjects[currOBJ].direction) * 4.0f;
                        allObjects[O].speed.y = sin(allObjects[currOBJ].direction) * 4.0f;
                        allObjects[O].team = 1;
                        create_object(allObjects[O].position.x, allObjects[O].position.y, 0, 0, deflect, allObjects[currOBJ].direction * degreestoradians, 0);
                    }
                    break;
                case bullet2:
                    if (is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position, enemy_bullet_hitbox, allObjects[currOBJ].direction)) {
                        destroy_projectile(O);
                    }
                    break;
                case guardian_bullet:
                    if (is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position, guardian_bullet_hitbox, allObjects[currOBJ].direction)) {
                        destroy_projectile(O);
                    }
                    break;
                case large_guardian_bullet:
                    if (is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position, guardian_bullet_hitbox, allObjects[currOBJ].direction)) {
                        destroy_projectile(O);
                    }
                    break;
                case T2_bullet:
                    if (is_within_melee_slash(allObjects[currOBJ].position, allObjects[O].position, enemy_bullet_hitbox, allObjects[currOBJ].direction)) {
                        destroy_projectile(O);
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void idpd_explosion_collision(int currOBJ, int i, int j) {
    float tmpdir = 0.0f;
    for (int w = -7; w < 8; w++) {
        for (int h = -7; h < 8; h++) {
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
                case throne_2:
                    if (allObjects[O].alarm1 < 0 && allObjects[O].team != 2 && is_within_throne_2(allObjects[O].position, allObjects[currOBJ].position, idpd_explosion_hitbox)){
                        allObjects[O].my_hp -= 8;
                        if (allObjects[O].my_hp > 0) {
                            enemy_hurt(O, currOBJ);
                        }
                        else {  //dead
                            enemy_die(O, currOBJ);
                        }
                    }
                    break;
                case idpd_nade:
                    if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (2 + idpd_explosion_hitbox))) {
                        destroy_projectile(O);
                    }
                    break;
                case bandit:
                    if ((allObjects[currOBJ].team != allObjects[O].team) && is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (bandit_hitbox + idpd_explosion_hitbox))) {
                        allObjects[O].my_hp -= 8;
                        tmpdir = atan2f(allObjects[currOBJ].position.y - allObjects[O].position.y, allObjects[currOBJ].position.x - allObjects[O].position.x);
                        allObjects[currOBJ].speed.x = cos(tmpdir) * 12;
                        allObjects[currOBJ].speed.y = sin(tmpdir) * 12; //this is so the enemy_hurt() function works
                        if (allObjects[O].my_hp > 0) {
                            enemy_hurt(O, currOBJ);
                        }
                        else {  //dead
                            enemy_die(O, currOBJ);
                        }

                    }
                    break;
                case idpd_freak:
                    if ((allObjects[currOBJ].team != allObjects[O].team) && is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (idpd_freak_hitbox + idpd_explosion_hitbox))) {
                        allObjects[O].my_hp -= 8;
                        tmpdir = atan2f(allObjects[currOBJ].position.y - allObjects[O].position.y, allObjects[currOBJ].position.x - allObjects[O].position.x);
                        allObjects[currOBJ].speed.x = cos(tmpdir) * 12;
                        allObjects[currOBJ].speed.y = sin(tmpdir) * 12; //this is so the enemy_hurt() function works
                        if (allObjects[O].my_hp > 0) {
                            enemy_hurt(O, currOBJ);
                        }
                        else {  //dead
                            enemy_die(O, currOBJ);
                        }

                    }
                    break;
                case plasma_huge:
                    if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (allObjects[O].scale * plasma_hitbox + idpd_explosion_hitbox))) {
                        plasma_huge_destroy(O, i + w, j + h);
                    }
                    break;
                case plasma_big:
                    if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (allObjects[O].scale * plasma_hitbox + idpd_explosion_hitbox))) {
                        plasma_big_destroy(O, i + w, j + h);
                    }
                    break;
                case plasma:
                    if (is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (allObjects[O].scale * plasma_hitbox + idpd_explosion_hitbox))) {
                        //turn into plasma explosion
                        destroy_projectile(O);
                    }
                    break;
                case bullet1:
                    if (allObjects[O].team != allObjects[O].team && is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (enemy_bullet_hitbox + idpd_explosion_hitbox))) {
                        destroy_projectile(O);
                    }
                    break;
                case idpd_bullet:
                    if (allObjects[O].team != allObjects[O].team && is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (enemy_bullet_hitbox + idpd_explosion_hitbox))) {
                        destroy_projectile(O);
                    }
                    break;
                case guardian_bullet:
                    if (allObjects[O].team != allObjects[O].team && is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (guardian_bullet_hitbox + idpd_explosion_hitbox))) {
                        destroy_projectile(O);
                    }
                    break;
                case large_guardian_bullet:
                    if (allObjects[O].team != allObjects[O].team && is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (guardian_bullet_hitbox + idpd_explosion_hitbox))) {
                        destroy_projectile(O);
                    }
                    break;
                case T2_bullet:
                    if (allObjects[O].team != allObjects[O].team && is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (enemy_bullet_hitbox + idpd_explosion_hitbox))) {
                        destroy_projectile(O);
                    }
                    break;
                case bullet2:
                    if (allObjects[O].team != allObjects[O].team && is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (enemy_bullet_hitbox + idpd_explosion_hitbox))) {
                        destroy_projectile(O);
                    }
                    break;
                case horror_bullet:
                    if (allObjects[O].team != allObjects[O].team && is_within_circle(allObjects[O].position, allObjects[currOBJ].position, (enemy_bullet_hitbox + idpd_explosion_hitbox))) {
                        destroy_projectile(O);
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
}

void throne_2_collision(int O, int i, int j) {
    for (int w = -10; w < 11; w++) {
        for (int h = -10; h < 11; h++) {
            for (int O : game_area[i + w][j + h].object_indexes) {      //walls collisions and bounce
                switch (allObjects[O].my_id) {
                case plasma_huge:
                    plasma_huge_collison(O, i, j);
                    break;
                case plasma_big:
                    plasma_big_collison(O, i, j);
                    break;
                case plasma:
                    plasma_collision(O, i, j);
                    break;
                case horror_bullet:
                    //!!!
                    break;
                default:
                    break;
                }
            }
        }
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

void fire_weapon(int index, float direction) {
    float Xspd = 0.0f;
    float Yspd = 0.0f;
    float Xoff = 0.0f;
    float Yoff = 0.0f;
    switch (index) {
    case 0:     //ultra shovel
        if (LMB_pressed && wep_reload < 0.0f) {
            LMB_pressed = false;
            if (player_rads > 13) {
                reloaded = false;

                wep_kick = -6;
                wep_angle *= -1;
                play_sounds_this_frame_count[snd_ultra_shovel_ID] = 1;
                player_rads -= 14;
                wep_reload = 15.0f;
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
        if (LMB_pressed && wep_reload < 0.0f && player_energy - 24 >= 0) {
            reloaded = false;

            player_energy -= 24;
            LMB_pressed = false;
            wep_kick = 7;
            motion_add_dir(direction, -16, 0);
            play_sounds_this_frame_count[snd_plasma_huge_ID] = 1;
            wep_reload = 260.0f;
            Xspd = cos(direction) * 6.0f;
            Yspd = sin(direction) * 6.0f;
            create_object(allObjects[0].position.x + Xspd / 2, allObjects[0].position.y + Yspd / 2, Xspd, Yspd, plasma_huge, direction, 0);
        }
        if (LMB_pressed && wep_reload < 0.0f && player_energy - 24 < 0) {
            play_sound_on_player(snd_empty_ID);
            create_popuptext("NOT ENOUGH ENERGY", allObjects[0].position);
            LMB_pressed = false;
            wep_kick = 3;
        }
        break;
    default:
        break;
    }
}

void object_tunnel_corner(int currOBJ) {
    switch (allObjects[currOBJ].my_id) {
    case objectID::bullet1:
        destroy_projectile(currOBJ);
        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
        break;
    case objectID::idpd_bullet:
        destroy_projectile(currOBJ);
        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
        break;
    case objectID::guardian_bullet:
        destroy_projectile(currOBJ);
        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
        break;       //bullet destroy particle
    case objectID::large_guardian_bullet:
        destroy_projectile(currOBJ);
        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
        break;       //bullet destroy particle
    case objectID::bullet2:
        destroy_projectile(currOBJ);
        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
        break;
    case objectID::player_bullet:
        destroy_projectile(currOBJ);
        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
        break;
    case objectID::horror_bullet:
        destroy_projectile(currOBJ);
        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
        break;
    case objectID::bandit_corpse:
        bounce_in_corner_wall(currOBJ);
        break;
    case objectID::idpd_freak_corpse:
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

float direction_to_player(int OBJ) {
    return atan2f(allObjects[0].position.y - allObjects[OBJ].position.y, allObjects[0].position.x - allObjects[OBJ].position.x);
}

void do_object_logic(int start, int end) {    //logic done on each obect every frame
    float tmpdir = 0.0f;
    float tempSpeedX = 0.0f;
    float tempSpeedY = 0.0f;
    float tempSpeed = 0.0f;
    float diffx = 0.0f;
    float diffy = 0.0f;

    int choice = 0;
     
    lowest_corpse_lifetime = 65535;

    int _i = 0;
    int _j = 0;
    std::random_device rd;
    // Initialize random number generator
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, RAND_MAX);
    for (int i = start; i < end; i++) {
        switch (allObjects[i].my_id) {
        case throne_2_death:
            allObjects[i].image_index++;
            allObjects[i].alarm1--;

            allObjects[i].speed.x = cos(allObjects[i].direction) * allObjects[i].speeddir;
            allObjects[i].speed.y = sin(allObjects[i].direction) * allObjects[i].speeddir;

            allObjects[i].position += allObjects[i].speed;

            if (allObjects[i].alarm1 < 0) {
                //explode into portal
                allObjects[i].my_id = nothing;
                create_object(allObjects[i].position.x, allObjects[i].position.y, 0, 0, portal, 0, 0);
                created_portal = true;
                can_move_outside_T2_arena = true;

                //create rads
                for (int b = allObjects[i].rad_drop; b > 0; b--) {
                    tempSpeed = random(15.0f);
                    tmpdir = random_360_radians();
                    tempSpeedX = cos(tmpdir) * tempSpeed;
                    tempSpeedY = sin(tmpdir) * tempSpeed;
                    create_object(allObjects[i].position.x, allObjects[i].position.y, tempSpeedX, tempSpeedY, rad, 0.0f, 0);
                }
            }

            T2_sprite.setColor({ 255, 255, 255, 255 });
            T2_sprite.setPosition(allObjects[i].position - cameraPos);
            T2_sprite.setRotation(0);
            //T2_sprite.setTextureRect(sf::IntRect{ 250 * choice, 0, 250, 250 });
            T2_sprite.setOrigin(125, 125);
            T2_sprite.setScale(1, 1);
            break;
        case throne_2:
            allObjects[i].image_index++;
            allObjects[i].alarm1--;
            allObjects[i].alarm2--;
            allObjects[i].alarm3--;
            if (allObjects[i].alarm1 == 0) {
                allObjects[i].image_index = 0;
                //make all walls invisibe and not collide with bullets
                make_T2_arena();
            }

            //draw always
            if (allObjects[i].alarm1 > 0) {
                t2_draw_in_front = true;
                //T2_sprite.setTexture(throne2Appear);
            }
            else {
                //T2_sprite.setTexture(throne2Idle);
                t2_draw_in_front = false;

                //attack logic
                if (allObjects[i].alarm3 < 0) {
                   
                    if (allObjects[i].team == 1) {  //attack 1
                        allObjects[i].alarm3 = 10;
                        allObjects[i].size++; //number of shots
                        tmpdir = direction_to_player(i) + (((30 + random(10)) / degreestoradians) * allObjects[i].walk_frames);  //what side that swaps every shot
                        tempSpeed = 5 + random(1);
                        tempSpeedX = cos(tmpdir) * tempSpeed; 
                        tempSpeedY = sin(tmpdir) * tempSpeed;

                        allObjects[i].walk_frames = -allObjects[i].walk_frames;

                        create_object(allObjects[i].position.x, allObjects[i].position.y, tempSpeedX, tempSpeedY, large_guardian_bullet, tmpdir, 0);

                        if (allObjects[i].size > LOOPS + 2) {
                            allObjects[i].size = 0;
                            allObjects[i].alarm3 = 100;
                            allObjects[i].team = (rand() % 3) + 1;
                        }
                        else {
                            allObjects[i].alarm3 /= (2 - allObjects[i].my_hp / (600 * round(1 + LOOPS / 3)));
                        }
                    }
                    if (allObjects[i].team == 2 && allObjects[i].alarm3 <= 0) {  //attack 2
                        allObjects[i].size++; //number of shots
                        choice = 10 + LOOPS;
                        for (int b = 0; b < choice; b++) {
                            tmpdir = allObjects[i].gun_angle;
                            tempSpeed = 8;
                            tempSpeedX = cos(tmpdir) * tempSpeed;
                            tempSpeedY = sin(tmpdir) * tempSpeed;

                            create_object(allObjects[i].position.x, allObjects[i].position.y, tempSpeedX, tempSpeedY, guardian_bullet, tmpdir, 0);
                            allObjects[i].gun_angle += (360 / float(choice)) / degreestoradians;
                        }
                        allObjects[i].alarm3 = 0;
                        if (allObjects[i].size > LOOPS * 5 + 15) {
                            allObjects[i].alarm3 += 40;
                            allObjects[i].size = 0;
                            allObjects[i].gun_angle = random_360_radians();
                            allObjects[i].team = ((rand() % 2) * 2) + 1;
                        }
                    }
                    if (allObjects[i].team == 3 && allObjects[i].alarm3 < 0) {  //attack 3
                        tmpdir = random_360_radians();
                        for (int b = 0; b < 4 + LOOPS; b++) {
                            tempSpeed = 4 + random(6);
                            tempSpeedX = cos(tmpdir) * tempSpeed;
                            tempSpeedY = sin(tmpdir) * tempSpeed;

                            create_object(allObjects[i].position.x, allObjects[i].position.y, tempSpeedX, tempSpeedY, T2_bullet, tmpdir + 180 / degreestoradians, 0);

                            tmpdir += (360 / float(4 + LOOPS)) / degreestoradians;
                        }
                        allObjects[i].alarm3 = 100;
                        allObjects[i].team = (rand() % 3) + 1;
                        
                        allObjects[i].walk_frames = -allObjects[i].walk_frames;
                    }
                }

                //do movement logic
                if (allObjects[i].alarm2 < 0) {
                    allObjects[i].alarm2 = 30;

                    allObjects[i].walk_direction = direction_to_player(i) + ((50.0f + random(20.0f)) * (allObjects[i].facing_right * 2 - 1)) / degreestoradians;
                    if (rand() % 10 == 0) {
                        allObjects[i].facing_right = !allObjects[i].facing_right;
                    }
                }
                allObjects[i].speeddir = 1.5;
                if (allObjects[i].team == 2 && allObjects[i].alarm3 == 0) {
                    allObjects[i].speeddir = 2.0f;
                    allObjects[i].direction = direction_to_player(i);
                }
                else {
                    motion_add_dir(allObjects[i].walk_direction, 4.5f, i);
                }
                allObjects[i].speed.x = cos(allObjects[i].direction) * allObjects[i].speeddir;
                allObjects[i].speed.y = sin(allObjects[i].direction) * allObjects[i].speeddir;

                allObjects[i].position += allObjects[i].speed;

            }

            T2_sprite.setColor({ 255, 255, 255, 255 });
            T2_sprite.setPosition(allObjects[i].position - cameraPos);
            T2_sprite.setRotation(0);
            //T2_sprite.setTextureRect(sf::IntRect{ 250 * choice, 0, 250, 250 });
            T2_sprite.setOrigin(125, 125);
            T2_sprite.setScale(1, 1);
            //
            break;
        case portal:
            portal_camera_offset =  {(allObjects[i].position.x - allObjects[0].position.x) / 16, (allObjects[i].position.y - allObjects[0].position.y) / 16 };
            allObjects[i].image_index++;
            allObjects[i].alarm3--;
            if (allObjects[i].alarm1 == 0 && allObjects[i].image_index < 5 && area != 0) {
                clear_all_bullets();
            }
            if (allObjects[i].alarm1 == 1) {
                allObjects[i].alarm2--;
            }
            if (allObjects[i].alarm1 == 1 && allObjects[i].alarm2 < 0) {
                allObjects[0].scale = 0;   //make player invisible
                player_friction_mult = 10.0f;
                allObjects[i].image_index = 0;
                allObjects[i].alarm1 = 2;
            }
            if (allObjects[i].alarm1 == 2 && allObjects[i].image_index > 29) {
                //go to next level
                want_gen = true;
                stop_looping_sound(snd_portal_loop_ID);
            }
            if (allObjects[i].alarm3 < 0) {
                if (has_line_of_sight(allObjects[i].position.x, allObjects[i].position.y) || is_within_circle(allObjects[i].position, allObjects[0].position, 16) || area == 0) {
                    if (is_within_circle(allObjects[i].position, allObjects[0].position, 32) || area == 0) {
                        player_invincible = true;
                    }
                    if (is_within_circle(allObjects[i].position, allObjects[0].position, 48) || (allObjects[i].alarm1 != 0) || area == 0) {
                        tmpdir = atan2f(allObjects[i].position.y - allObjects[0].position.y, allObjects[i].position.x - allObjects[0].position.x);
                        motion_add_dir(tmpdir, 3, 0);
                        if (allObjects[i].alarm1 != 2) {
                            allObjects[0].position.x += cos(tmpdir) * 3;
                            allObjects[0].position.y += sin(tmpdir) * 3;
                        }

                        allObjects[0].image_index = 3;
                        allObjects[0].gun_angle += 30;

                        if (allObjects[0].alarm1 == 0) {
                            allObjects[0].alarm1 = 1;   //cant move
                        }

                        player_invincible = true;
                        allObjects[0].next_hurt = current_frame + 6;
                    }
                    else {
                    allObjects[0].gun_angle = 0;
                    }
                    if (is_within_circle(allObjects[i].position, allObjects[0].position, 96) || area == 0) {
                        tmpdir = atan2f(allObjects[i].position.y - allObjects[0].position.y, allObjects[i].position.x - allObjects[0].position.x);
                        motion_add_dir(tmpdir, 2, 0);
                    }
                }
            }
            if (rand() % 20 == 0 && area != 0) {
                tmpdir = random_360_radians();
                tempSpeedX = cos(tmpdir) * 2;
                tempSpeedY = sin(tmpdir) * 2;
                create_object(allObjects[i].position.x, allObjects[i].position.y, tempSpeedX, tempSpeedY, portal_lightning, 0, 0);
            }
            break;
        case portal_lightning:
            allObjects[i].image_index++;
            if (allObjects[i].image_index > 12) {
                allObjects[i].my_id = nothing;
            }
            allObjects[i].position += allObjects[i].speed;
            break;
        case portal_clear:
            _i = int(allObjects[i].position.x / 16);
            _j = int(allObjects[i].position.y / 16);
            for (int w = -2; w < 3; w++) {
                for (int h = -2; h < 3; h++) {
                    //destroy wall
                    if (game_area[_i + w][_j + h].my_grid_type == wall && is_within_circle(sf::Vector2f(((_i + w) * 16) + 8, ((_j + h) * 16) + 8), allObjects[i].position, (wall_hitbox + 32))) {
                        create_explo_tile(_i + w, _j + h);
                    }
                }
            }
            allObjects[i].my_id = nothing;
            break;
        case bullet1:
            allObjects[i].image_index++;
            allObjects[i].position += allObjects[i].speed;
            break;
        case guardian_bullet:
            allObjects[i].image_index++;
            allObjects[i].position += allObjects[i].speed;
            break;
        case guardian_bullet_destroy:
            allObjects[i].rotation += allObjects[i].friction;
            if (allObjects[i].rotation >= 4.99f) {
                allObjects[i].my_id = nothing;
            }
            allObjects[i].speeddir -= 0.4f;
            if (allObjects[i].speeddir < 0.0f) {
                allObjects[i].speeddir = 0.0f;
            }
            allObjects[i].speed.x = cos(allObjects[i].direction) * allObjects[i].speeddir;
            allObjects[i].speed.y = sin(allObjects[i].direction) * allObjects[i].speeddir;

            allObjects[i].position += allObjects[i].speed;
            break;
        case large_guardian_bullet:
            allObjects[i].image_index++;
            if (allObjects[i].image_index > 14) {
                allObjects[i].speeddir -= 0.1f;

                allObjects[i].speed.x = cos(allObjects[i].direction) * allObjects[i].speeddir;
                allObjects[i].speed.y = sin(allObjects[i].direction) * allObjects[i].speeddir;
                if (allObjects[i].speeddir < 0) {
                    destroy_projectile(i);
                }

                allObjects[i].position += allObjects[i].speed;
            }
            break;
        case T2_bullet:
            allObjects[i].image_index++;
            
            allObjects[i].speeddir -= 0.25f;

            if (allObjects[i].speeddir > 0.0f) {

                allObjects[i].speed.x = cos(allObjects[i].direction) * allObjects[i].speeddir;
                allObjects[i].speed.y = sin(allObjects[i].direction) * allObjects[i].speeddir;

                allObjects[i].position += allObjects[i].speed;
            }
            else {
                allObjects[i].alarm1--;
                if (allObjects[i].alarm1 == 0) {
                    allObjects[i].direction = direction_to_player(i) + (random(60) - 30) / degreestoradians;
                }
                if (allObjects[i].alarm1 < 0) {
                    allObjects[i].image_index = 0;
                    tempSpeedX = cos(allObjects[i].direction) * 10;
                    tempSpeedY = sin(allObjects[i].direction) * 10;
                    create_object(allObjects[i].position.x, allObjects[i].position.y, tempSpeedX, tempSpeedY, bullet2, allObjects[i].direction + 180 / degreestoradians, 0);
                }
                if(allObjects[i].alarm1 < -40 - LOOPS * 10){
                    destroy_projectile(i);
                }
            }
            break;
        case idpd_bullet:
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
        case idpd_bullet_destroy:
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
                allObjects[i].speed.x *= 0.85f;
                allObjects[i].speed.y *= 0.85f;
                //allObjects[i].position += allObjects[i].speed;
            }
            if (allObjects[i].next_hurt == current_frame) {
                allObjects[i].speed.x = 0.0f;
                allObjects[i].speed.y = 0.0f;
            }

            diffx = allObjects[i].position.x - allObjects[0].position.x;
            diffy = allObjects[i].position.y - allObjects[0].position.y;
            if (allObjects[i].next_hurt < current_frame && (sqrt(pow(diffx, 2) + pow(diffy, 2)) < plutonium_hunger || created_portal)) {
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
                play_sound_relative_to_player(snd_pickup_disappear_ID, allObjects[i].position.x, allObjects[i].position.y);
                allObjects[i].my_id = ammo_pack_destroy;
                allObjects[i].size = 1;     //disappear sprite vs. picked up sprite is 2
                allObjects[i].image_index = 0;
                break;
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
        case ammo_pack_destroy:
            allObjects[i].image_index++;
            if (allObjects[i].image_index > 12) {
                allObjects[i].my_id = nothing;
            }
            break;
        case heal_FX:
            allObjects[i].image_index++;
            allObjects[i].position.y -= 2;
            if (allObjects[i].image_index == 8) {   //make up for sprite modification
                allObjects[i].position.y -= 2;
            }
            if (allObjects[i].image_index > 17) {
                allObjects[i].my_id = nothing;
            }
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

            //bandit ai
            if (allObjects[i].alarm1 < 0) {
                //choose what to do
                allObjects[i].alarm1 = 20 + rand() % 10;
                if (has_line_of_sight(allObjects[i].position.x, allObjects[i].position.y)) {    //game_area[i][j].has_line_of_sight
                    if (!is_within_circle(allObjects[i].position, allObjects[0].position, 48)) {
                        if (rand() % 4 == 0) {  //shoot
                            tmpdir = angle_to_player_radians(allObjects[i].position);
                            tmpdir += random_360_radians() / 18.0f - (10.0f / degreestoradians);
                            tempSpeedX = cos(tmpdir) * 4.0f;
                            tempSpeedY = sin(tmpdir) * 4.0f;
                            create_object(allObjects[i].position.x, allObjects[i].position.y, tempSpeedX, tempSpeedY, bullet1, tmpdir, 0);
                            play_sound_relative_to_player(snd_shoot_1_ID, allObjects[i].position.x, allObjects[i].position.y);
                            allObjects[i].direction = tmpdir;
                            allObjects[i].alarm1 = 20 + rand() % 5;
                        }
                        else {  //walk towards player
                            allObjects[i].speeddir += 0.4f;
                            allObjects[i].direction = angle_to_player_radians(allObjects[i].position) + random_180_radians() - (90.0f / degreestoradians);
                            allObjects[i].walk_frames = 10 + rand() % 10;
                        }
                    }
                    else {      //run away
                        tmpdir = angle_to_player_radians(allObjects[i].position);
                        tmpdir += 170.0f / degreestoradians + random_360_radians() / 18.0f;

                        allObjects[i].speeddir += 0.4f;
                        allObjects[i].walk_frames = 40 + rand() % 10;
                        allObjects[i].direction = tmpdir;     //used for gun angle
                        motion_add_dir(allObjects[i].direction, 0.4, i);
                    }
                }
                else if (rand() % 4 == 0) {      //move in radom direction if no line of sight
                    allObjects[i].direction = random_360_radians();
                    motion_add_dir(allObjects[i].direction, 0.4, i);

                    allObjects[i].walk_frames = 20 + rand() % 10;
                    allObjects[i].alarm1 = allObjects[i].walk_frames + 10 + rand() % 30;
                }
                allObjects[i].facing_right = cos(allObjects[i].direction) > 0;
            }
            //bandit ai

            break;
        case bandit_corpse:
            corpse_step(i);
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
            allObjects[i].alarm3--;
            
            allObjects[i].facing_right = allObjects[i].speed.x > 0;

            if (allObjects[i].walk_frames > 0)
            {
                allObjects[i].walk_frames--;
                if (allObjects[i].next_hurt > current_frame) {  //in iframes
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
                allObjects[i].walk_direction = allObjects[i].direction;
            }
            //shoot
            if (allObjects[i].alarm2 >= 0 && allObjects[i].alarm2 < 8) {
                play_sound_relative_to_player(snd_grunt_fire_ID, allObjects[i].position.x, allObjects[i].position.y);
                if (allObjects[i].alarm2 == 7) {
                    allObjects[i].gun_angle = angle_to_player_radians(allObjects[i].position) + (random_180_radians() / 2) - (45 / degreestoradians);
                }
                tmpdir = allObjects[i].gun_angle + (random(100.0f) - 50.0f) / degreestoradians;
                tempSpeed = random(3.0f) + 4.0f;
                tempSpeedX = cos(tmpdir) * tempSpeed;
                tempSpeedY = sin(tmpdir) * tempSpeed;
                create_object(allObjects[i].position.x, allObjects[i].position.y, tempSpeedX, tempSpeedY, idpd_bullet, tmpdir, 0);

                tmpdir = allObjects[i].gun_angle + (random(40.0f) - 20.0f) / degreestoradians;
                tempSpeed = random(3.0f) + 4.0f;
                tempSpeedX = cos(tmpdir) * tempSpeed;
                tempSpeedY = sin(tmpdir) * tempSpeed;
                create_object(allObjects[i].position.x, allObjects[i].position.y, tempSpeedX, tempSpeedY, idpd_bullet, tmpdir, 0);
            }

            break;
        case idpd_freak_corpse:
            if (!created_portal || allObjects[i].alarm1 < 16) {
                allObjects[i].alarm1--;
            }

            if (allObjects[i].alarm1 < 0) {
                create_object(allObjects[i].position.x, allObjects[i].position.y, 0, 0, idpd_freak, random_360_radians(), 0);
                allObjects[i].my_id = idpd_freak_revive;
                play_sound_relative_to_player(snd_idpd_freak_revive_ID, allObjects[i].position.x, allObjects[i].position.y);
                allObjects[i].image_index = 0;
            }
            if (allObjects[i].alarm1 == 15) {
                play_sound_relative_to_player(snd_idpd_freak_revive_area_ID, allObjects[i].position.x, allObjects[i].position.y);
            }
            corpse_step(i);
            break;
        case idpd_freak_revive:
            allObjects[i].image_index++;
            if (allObjects[i].image_index > 29) {
                allObjects[i].my_id = nothing;
            }
            break;
        case idpd_spawn:
            allObjects[i].alarm1--;
            allObjects[i].alarm2--;
            allObjects[i].alarm3--;
            allObjects[i].image_index++;
            if (allObjects[i].alarm2 == 12) {
                allObjects[i].image_index = 0;
            }
            if (allObjects[i].alarm2 == 0) {
                create_object(allObjects[i].position.x, allObjects[i].position.y, 0, 0, idpd_freak, random_360_radians(), 0);
            }
            if (allObjects[i].alarm1 < -34) {
                allObjects[i].my_id = nothing;
                idpd_spawn_count--;
            }
            //create portal charges
            tempSpeedX = random(1) + 2;
            diffx = rand() % 96 - 48;
            diffy = rand() % 96 - 48;
            tmpdir = atan2f(diffy, diffx);
            create_object(allObjects[i].position.x + diffx, allObjects[i].position.y + diffy, cos(tmpdir) * -tempSpeedX, sin(tmpdir) * -tempSpeedX, idpd_portal_charge, (sqrt((diffx * diffx) + (diffy * diffy)) / tempSpeedX) + 1, rand() % 4);

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
            allObjects[i].alarm3 = 0;   //whether the plasma has hit something
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
            allObjects[i].alarm3 = 0;   //whether the plasma has hit something
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
            allObjects[i].alarm3 = 0;   //whether the plasma has hit something
            //alarm1 determines if the plasma hit something that keeps it from moving
            if (allObjects[i].image_index > 1) {
                allObjects[i].position += allObjects[i].speed;
            }

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
            allObjects[i].speeddir -= allObjects[i].friction;
            allObjects[i].speed.x = cos(allObjects[i].direction) * allObjects[i].speeddir;
            allObjects[i].speed.y = sin(allObjects[i].direction) * allObjects[i].speeddir;

            allObjects[i].position += allObjects[i].speed;
            allObjects[i].alarm3 = 0;

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
                destroy_projectile(i);
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
        case popup_text:
            allObjects[i].alarm1--;
            if (allObjects[i].alarm1 > 10) {
                allObjects[i].position.y -= 2;
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

void reset_popup_texts(std::vector<sf::Text>& texts, int largest_index) {
    for (int i = 0; i < largest_index; i++) {
        texts[i].setString("");
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
            case T2_boarder:
                //simply remove any object that gets this far out
                for (int O : game_area[i][j].object_indexes) {
                    allObjects[O].my_id = nothing;
                }
                break;
            case void_tile:
                //only need to do collisions with freaks and player
                for (int w = -1; w < 2; w++) {      //each wall checks around it for possible collisions with objects that are supposed to be bigger than a single point
                    for (int h = -1; h < 2; h++) {
                        for (int O : game_area[i + w][j + h].object_indexes) {      //walls collisions and bounce
                            switch (allObjects[O].my_id) {
                            case objectID::player:
                                player_collision(i, j, O);
                                if (!can_move_outside_T2_arena) {
                                    collide_wall(O, i, j, h, w, 5);
                                }
                                break;
                            case idpd_freak:
                                if (!can_move_outside_T2_arena) {
                                    object_bounce_wall(O, h, w, idpd_freak_hitbox, idpd_freak_hitbox, i, j);
                                }
                                break;
                            case objectID::idpd_freak_corpse:
                                if (!can_move_outside_T2_arena) {
                                    object_bounce_wall(O, h, w, idpd_freak_hitbox + 1, idpd_freak_hitbox + 1, i, j);
                                }
                                break;
                            case throne_2:
                                if (w == 0 && h == 0) {
                                    throne_2_collision(O, i, j);
                                }
                                break;
                            case ultra_slash:
                                if (allObjects[O].image_index < 5) {
                                    ultra_slash_collision(O, i, j);
                                }
                                break;
                            case idpd_explosion:
                                if (allObjects[O].image_index == 3 || allObjects[O].image_index == 4) {
                                    idpd_explosion_collision(O, i, j);
                                }
                                break;
                            default:
                                break;
                            }

                        }
                    }
                }
                break;
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
                                object_bounce_wall(O, h, w, bandit_hitbox, bandit_hitbox, i, j);
                                break;
                            case idpd_freak:
                                object_bounce_wall(O, h, w, idpd_freak_hitbox + 1, idpd_freak_hitbox + 1, i, j);
                                break;
                            case objectID::idpd_freak_corpse:
                                object_bounce_wall(O, h, w, idpd_freak_hitbox + 1, idpd_freak_hitbox + 1, i, j);
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
                        destroy_projectile(currOBJ);
                        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
                        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
                        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
                        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
                        break;       //bullet destroy particle
                    case objectID::idpd_bullet:
                        destroy_projectile(currOBJ);
                        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
                        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
                        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
                        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
                        break;       //bullet destroy particle
                    case objectID::guardian_bullet:
                        destroy_projectile(currOBJ);
                        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
                        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
                        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
                        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
                        break;       //bullet destroy particle
                    case objectID::large_guardian_bullet:
                        destroy_projectile(currOBJ);
                        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
                        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
                        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
                        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
                        break;       //bullet destroy particle
                    case objectID::bullet2:
                        destroy_projectile(currOBJ);
                        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
                        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
                        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
                        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
                        break;
                    case objectID::player_bullet:
                        destroy_projectile(currOBJ);
                        allObjects[currOBJ].position.x -= allObjects[currOBJ].speed.x / 1.5f;
                        allObjects[currOBJ].position.y -= allObjects[currOBJ].speed.y / 1.5f;
                        play_sound_relative_to_player(snd_hit_wall_ID, allObjects[currOBJ].position.x, allObjects[currOBJ].position.y);
                        create_object(allObjects[currOBJ].position.x, allObjects[currOBJ].position.y, 0.5, 0.5, dust, 0, 0);    //dust
                        break;      //bullet destroy particle
                    case objectID::horror_bullet:
                        destroy_projectile(currOBJ);
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
                            idpd_explosion_collision(currOBJ, i, j);
                        }
                        break;
                    case objectID::ultra_slash:
                        if (allObjects[currOBJ].image_index < 5) {
                            ultra_slash_collision(currOBJ,i, j);
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
                    case throne_2:
                        throne_2_collision(currOBJ, i, j);
                        break;
                    case objectID::player:
                        //do collisons with everything
                        player_collision(i, j, currOBJ);
                        
                        break;
                    case objectID::bandit:
                        basic_enemy_collision(currOBJ, i, j);
                        break;
                    case objectID::idpd_freak:
                        basic_enemy_collision(currOBJ, i, j);
                        break;
                    case horror_bullet:
                        horror_bullet_collision(currOBJ, i, j);
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
                            plasma_impact_collision(currOBJ, i, j);
                        }
                        break;
                    case ultra_slash:
                        if (allObjects[currOBJ].image_index < 5) {
                            ultra_slash_collision(currOBJ, i, j);
                        }
                        break;
                    case idpd_explosion:
                        if (allObjects[currOBJ].image_index == 3 || allObjects[currOBJ].image_index == 4) {
                            idpd_explosion_collision(currOBJ, i, j);
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
    if (adjacent_nub || nub_chance == 0) {
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

    reset_popup_texts();

    level_generator level_generators[255];
    int generators_active = 0;

    gen_curr_floor_index = 0;

    //first floor tile
    allFloors[gen_curr_floor_index].setPosition(24000, 24000);
    gen_curr_floor_index++;

    enemy_count = 0;
    created_portal = false; //can create portal again
    create_portal = false;
    lowest_corpse_lifetime_ID = 0;
    allObjects[0].scale = 1;
    player_friction_mult = 1.0f;
    allObjects[0].alarm1 = 0;
    player_invincible = false;

    killed_throne_2 = false;
    can_move_outside_T2_arena = false;

    idpd_spawn_count = 0;

    portal_sprite.setPosition(-1000, -1000);
    T2_sprite.setPosition(-1000, -1000);

    allObjects[0].position = { 24016.0f, 24016.0f };
    int initial_goal = 0;
    int goal = 0;
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
    if (area == 0) {    //throne 2

        initial_goal = 240;
        goal = initial_goal;
        while (goal > 0) {
            for (int i = 0; i < 254; i++) {
                if (level_generators[i].active) {
                    if (goal < initial_goal - safe_dist) {
                        if (rand() % (19 + generators_active) > 22) {
                            level_generators[i].active = false;
                            generators_active--;
                        }
                        if (rand() % 4 == 0) {
                            for (int b = 0; b < 254; b++) {
                                if (level_generators[b].active == false) {
                                    level_generators[b].active = true;
                                    level_generators[b].Btile = 0;  //never b-tile
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
                        int choice = rand() % 6;
                        if (choice < 1) {
                            //turn = 0;
                        }
                        else if (choice < 5) {
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
                    //only generate 1 tile at a time
                    goal -= generate_2x2_tile(level_generators[i].x, level_generators[i].y, 0, level_generators[i].Btile);
                }
            }
        }
        //check if any details are on b-tiles
        for (int i = 0; i < 500; i++) {
            if (allObjects[i].my_id == detail) {
                for (int j = 0; j < max_floors; j++) {                                                                                                                                         //is b-tile
                    if (abs(allObjects[i].position.x - allFloors[j].getPosition().x - 16) < 19 && abs(allObjects[i].position.y - allFloors[j].getPosition().y - 16) < 19 && allFloors[j].getOrigin().y > 3) {
                        allObjects[i].my_id = nothing;
                    }
                }
            }
        }

        //generate enemies
        int tmp_num_of_enemies_to_spawn = LOOPS * 3;
        int enemies_spawned = 0;
        if (sub_area == 1) {
            while (tmp_num_of_enemies_to_spawn > enemies_spawned) {
                for (int i = left_physics; i <= right_physics; i++) {
                    for (int j = top_physics; j <= bottom_physics; j++) {
                        if (game_area[i][j].my_grid_type == floor_tile && !is_within_circle(sf::Vector2f(24016, 24016), sf::Vector2f(i * 16 + 8, j * 16 + 8), 80) && is_within_circle(sf::Vector2f(24016, 24016), sf::Vector2f(i * 16 + 8, j * 16 + 8), 120)) {
                            if (tmp_num_of_enemies_to_spawn > enemies_spawned && rand() % 4 == 0) {
                                enemies_spawned++;
                                float rand_off_x = 0;
                                float rand_off_y = 0;
                                create_object(i * 16 + 8 + rand_off_x, j * 16 + 8 + rand_off_y, 0, 0, idpd_spawn, 0, 0);
                            }
                        }
                    }
                }
            }
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
    if (area == 1) {
        initial_goal = 480;
        goal = initial_goal;
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
        //check if any details are on b-tiles
        for (int i = 0; i < 500; i++) {
            if (allObjects[i].my_id == detail) {
                for (int j = 0; j < max_floors; j++) {                                                                                                                                         //is b-tile
                    if (abs(allObjects[i].position.x - allFloors[j].getPosition().x - 16) < 19 && abs(allObjects[i].position.y - allFloors[j].getPosition().y - 16) < 19 && allFloors[j].getOrigin().y > 3) {
                        allObjects[i].my_id = nothing;
                    }
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
                        if (tmp_num_of_enemies_to_spawn > 1) {  //cluster spawn destroys nearby walls
                            for (int b = -1; b < 2; b++) {
                                for (int c = -1; c < 2; c++) {
                                    if (game_area[i + b][j + c].my_grid_type == wall) {
                                        create_explo_tile(i + b, j + c);
                                        //create debris too
                                    }
                                }
                            }
                        }
                        for (int r = 0; r < tmp_num_of_enemies_to_spawn; r++) {
                            if (enemy_choice < 1) { //bandit
                                float rand_off_x = random_360_radians() - 3.14f;
                                float rand_off_y = random_360_radians() - 3.14f;
                                create_object(i * 16 + 8 + rand_off_x, j * 16 + 8 + rand_off_y, 0, 0, idpd_freak, 0, 0);
                            }
                            else {
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
    enemy_count_start = enemy_count;

    return;
}


//no debug window
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

sf::Image game_icon;

int main()
{

    //font
    sf::Font font;
    font.loadFromFile("C:/Users/svt16/Desktop/Nuclear Throne Arranged/cmake-sfml-project/src/PressStart2P-Regular.ttf");

    //sounds
    play_sounds_this_frame_pos.reserve(255);
    play_sounds_this_frame_count.reserve(255);

    //SOUND_START
    const int all_sounds_max = 1000;
    sound_sound_buffer all_sounds[all_sounds_max];

    add_new_sound(snd_shoot_1_ID, "snd/shoot_1.wav", all_sounds, 0.1f, 0.015f);

    add_new_sound(snd_horror_portal_ID, "snd/horror_portal.wav", all_sounds, 0.1f);

    add_new_sound(snd_horror_portal_pan_ID, "snd/horror_portal_pan.wav", all_sounds, 0.1f, 0.005f);

    add_new_sound(snd_bandit_hurt_ID, "snd/bandit_hurt.wav", all_sounds, 0.1f, 0.04f);

    add_new_sound(snd_bandit_die_ID, "snd/bandit_die.wav", all_sounds, 0.1f, 0.04f);

    add_new_sound(snd_rad_pickup_ID, "snd/rad_pickup.wav", all_sounds, 0.02f, 0.00f, 70.0f);

    add_new_sound(snd_horror_beam_start_ID, "snd/horror_beam_start.wav", all_sounds, 0.02f, 0.0f, 70.0f);

    add_new_sound(snd_horror_beam_hold_ID, "snd/horror_beam_hold.wav", all_sounds, 0.00f, 0.0f, 70.0f);

    add_new_sound(snd_hit_wall_ID, "snd/hit_wall.wav", all_sounds, 0.1f, 0.02f);

    add_new_sound(snd_wall_break_rock_ID, "snd/wall_break_rock.wav", all_sounds, 0.1f, 0.005f);

    add_new_sound(snd_IDPD_explosion_ID, "snd/IDPD_explosion.wav", all_sounds, 0.1f, 0.01f);

    add_new_sound(snd_explosion_ID, "snd/explosion.wav", all_sounds, 0.1f, 0.005f);

    add_new_sound(snd_plasma_hit_ID, "snd/plasma_hit.wav", all_sounds, 0.15f, 0.02f);

    add_new_sound(snd_ultra_shovel_ID, "snd/ultra_shovel.wav", all_sounds, 0.1f, 0.0f);

    add_new_sound(snd_plasma_huge_ID, "snd/plasma_huge.wav", all_sounds, 0.15f, 0.0f);

    add_new_sound(snd_plasma_huge_upgrade_ID, "snd/plasma_huge_upgrade.wav", all_sounds, 0.15f, 0.0f);

    add_new_sound(snd_plasma_split_ID, "snd/plasma_split.wav", all_sounds, 0.15f, 0.01f);

    add_new_sound(snd_plasma_split_upgrade_ID, "snd/plasma_split_upgrade.wav", all_sounds, 0.15f, 0.01f);

    add_new_sound(snd_hammer_swap_ID, "snd/hammer_swap.wav", all_sounds, 0.005f, 0.0f);

    add_new_sound(snd_energy_swap_ID, "snd/energy_swap.wav", all_sounds, 0.005f, 0.0f);

    add_new_sound(snd_nade_hit_wall_ID, "snd/nade_hit_wall.wav", all_sounds, 0.1f, 0.01f);

    add_new_sound(snd_IDPD_nade_load_ID, "snd/IDPD_nade_load.wav", all_sounds, 0.1f, 0.01f);

    add_new_sound(snd_IDPD_nade_almost_ID, "snd/IDPD_nade_almost.wav", all_sounds, 0.1f, 0.01f);

    add_new_sound(snd_idpd_freak_hurt_ID, "snd/IDPD_freak_hurt.wav", all_sounds, 0.1f, 0.01f);

    add_new_sound(snd_idpd_freak_die_ID, "snd/IDPD_freak_die.wav", all_sounds, 0.1f, 0.01f);

    add_new_sound(snd_grunt_fire_ID, "snd/grunt_fire.wav", all_sounds, 0.1f, 0.01f);

    add_new_sound(snd_horror_hurt_ID, "snd/horror_hurt.wav", all_sounds, 0.07f, 0.00f);

    add_new_sound(snd_pickup_disappear_ID, "snd/pickup_disappear.wav", all_sounds, 0.1f, 0.01f);

    add_new_sound(snd_ammo_pickup_ID, "snd/ammo_pickup.wav", all_sounds, 0.07f, 0.01f);

    add_new_sound(snd_hp_pickup_ID, "snd/hp_pickup.wav", all_sounds, 0.07f, 0.01f);

    add_new_sound(snd_empty_ID, "snd/empty.wav", all_sounds, 0.02f, 0.00f, 90.0f);

    add_new_sound(snd_music_ID, "mus/mus1.ogg", all_sounds, 0.0f, 0.0f, 0.0f);

    add_new_sound(snd_melee_flip_ID, "snd/melee_flip.wav", all_sounds, 0.07f, 0.0f, 50.0f);

    add_new_sound(snd_plasma_reload_ID, "snd/plasma_reload.wav", all_sounds, 0.07f, 0.0f, 90.0f);

    add_new_sound(snd_plasma_reload_upgrade_ID, "snd/plasma_reload_upgrade.wav", all_sounds, 0.07f, 0.0f, 90.0f);

    add_new_sound(snd_idpd_freak_enter_ID, "snd/idpd_freak_enter.wav", all_sounds, 0.15f, 0.01f);

    add_new_sound(snd_idpd_freak_revive_ID, "snd/idpd_freak_revive.wav", all_sounds, 0.05f, 0.01f);

    add_new_sound(snd_idpd_freak_revive_area_ID, "snd/idpd_freak_revive_area.wav", all_sounds, 0.05f, 0.01f);

    add_new_sound(snd_portal_open_ID, "snd/portal_open.wav", all_sounds, 0.01f, 0.01f);

    add_new_sound(snd_portal_close_ID, "snd/portal_close.wav", all_sounds, 0.01f, 0.01f);

    add_new_sound(snd_portal_loop_ID, "snd/portal_loop.wav", all_sounds, 0.0f, 0.0f, 0.0f);
    all_sounds[snd_portal_loop_ID].sound.play();
    all_sounds[snd_portal_loop_ID].sound.setLoop(true);

    //music
    //all_sounds[snd_music_ID].sound.play();
    all_sounds[snd_music_ID].sound.setLoop(true);
    

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

        //bosses
        sf::Texture throne2Appear;
        throne2Appear.loadFromFile("res/T2/sprNothing2Appear.png");

        sf::Texture throne2Idle;
        throne2Idle.loadFromFile("res/T2/sprNothing2Idle.png");


        sf::Texture throne2Hurt;
        throne2Hurt.loadFromFile("res/T2/sprNothing2Hurt.png");

        sf::Texture throne2Dead;
        throne2Dead.loadFromFile("res/T2/sprNothing2Death.png");

        sf::Sprite hp_bar_spr;
        sf::Sprite health_bar_spr;

        sf::Texture hp_bar;
        hp_bar.loadFromFile("res/player/hp_bar.png");
        sf::Texture health_bar;
        health_bar.loadFromFile("res/player/health_bar.png");

        hp_bar_spr.setTexture(hp_bar);
        hp_bar_spr.setOrigin(0, 0);
        hp_bar_spr.setPosition(20, 4);

        health_bar_spr.setTexture(health_bar);
        health_bar_spr.setOrigin(0, 0);
        health_bar_spr.setPosition(22, 7);
        health_bar_spr.setScale(84, 1);

        sf::Text hp_text;
        hp_text.setCharacterSize(8);
        hp_text.setFont(font);
        hp_text.setPosition(40, 7);

        sf::Texture portalDisappearTex;
        portalDisappearTex.loadFromFile("res/sprPortalDisappear.png");
        sf::Texture portalIdleTex;
        portalIdleTex.loadFromFile("res/sprPortal.png");

        sf::Texture portalBigDisappearTex;
        portalBigDisappearTex.loadFromFile("res/T2/sprBigPortalDisappear.png");
        sf::Texture portalBigIdleTex;
        portalBigIdleTex.loadFromFile("res/T2/sprBigPortal.png");
        sf::Texture portalBigAppearTex;
        portalBigAppearTex.loadFromFile("res/T2/sprBigPortalSpawn.png");
        
        sf::Texture portalLightning;
        portalLightning.loadFromFile("res/sprPortalLightning.png");

        sf::Texture allSmallEffectSprites;
        allSmallEffectSprites.loadFromFile("res/allSmallEffects.png");
        sf::Texture allMediumEffectSprites;
        allMediumEffectSprites.loadFromFile("res/allMediumEffects.png");
        sf::Texture allBigEffectSprites;
        allBigEffectSprites.loadFromFile("res/allBigEffects.png");

        sf::Texture allWallTops;
        allWallTops.loadFromFile("res/allWallTops.png");

        sf::Texture allWallBots;
        allWallBots.loadFromFile("res/allWallBots.png");

        sf::Texture allWallBoarders;
        allWallBoarders.loadFromFile("res/allWallBoarders.png");

        sf::Texture allFloors_tex;
        allFloors_tex.loadFromFile("res/allFloors.png");

        sf::Texture allFloorsBs_tex;
        allFloorsBs_tex.loadFromFile("res/allFloorsBs.png");
        
        sf::Texture allExploTiles;
        allExploTiles.loadFromFile("res/allExploTiles.png");


        sf::Texture Floor_T2_Tiles;
        Floor_T2_Tiles.loadFromFile("res/T2/T2_floor_unders.png");

        sf::Texture Explo_T2_Tiles;
        Explo_T2_Tiles.loadFromFile("res/T2/T2_explo_unders.png");

        /*sf::Texture boarderWall;
        boarderWall.loadFromFile("res/sprWall1Boarder.png");
        sf::VertexArray draw_boarderWalls = create_vertex_array(boarderWall, 600);*/

        sf::Texture idpdPortalClose;
        idpdPortalClose.loadFromFile("res/sprIDPDPortalClose.png");


        sf::Texture portal_spiral_tex;
        portal_spiral_tex.loadFromFile("res/portal_spiral.png");

        sf::Sprite portal_spiral_spr;
        portal_spiral_spr.setTexture(portal_spiral_tex);
        portal_spiral_spr.setOrigin(320, 320);

        //wall1 shadow
        sf::Texture Wall1shadow;
        Wall1shadow.loadFromFile("res/sprWall1shadow.png");
        sf::VertexArray draw_Wall1shadows = create_vertex_array(Wall1shadow, 600);


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
        sf::VertexArray draw_exploTile1_unders = create_vertex_array(exploTile1_under, 600);

        sf::Texture exploTile0_under;
        exploTile0_under.loadFromFile("res/sprExploTile0_under.png");
        sf::VertexArray draw_exploTile0_unders = create_vertex_array(exploTile0_under, 600);
        //floorTile0 under
        sf::Texture floorTile0_under;
        floorTile0_under.loadFromFile("res/sprFloor0_1_under.png");
        sf::VertexArray draw_floorTile0_unders = create_vertex_array(floorTile0_under, 100);


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

        //large
        sf::Texture largeGuardianBullet;
        largeGuardianBullet.loadFromFile("res/T2/sprBigGuardianBullet.png");
        sf::Texture largeGuardianBulletSpawn;
        largeGuardianBulletSpawn.loadFromFile("res/T2/sprBigGuardianBulletSpawn.png");

        sf::Texture GuardianBulletSpawn;
        GuardianBulletSpawn.loadFromFile("res/enemy_bullets/sprGuardianBulletSpawn.png");

        sf::Texture T2Bullet;
        T2Bullet.loadFromFile("res/T2/sprThrone2Bullet;.png");

        //guardian bullet
        sf::Texture guardian_bullet_1tex;
        guardian_bullet_1tex.loadFromFile("res/enemy_bullets/guardian_bullet_1.png");

        sf::Texture guardian_bullet_2tex;
        guardian_bullet_2tex.loadFromFile("res/enemy_bullets/guardian_bullet_2.png");

        sf::Texture guardian_bullet_3tex;
        guardian_bullet_3tex.loadFromFile("res/enemy_bullets/guardian_bullet_3.png");

        sf::Texture guardian_bullet_4tex;
        guardian_bullet_4tex.loadFromFile("res/enemy_bullets/guardian_bullet_4.png");

        //destroy
        sf::Texture guardian_bullet_destroy_1tex;
        guardian_bullet_destroy_1tex.loadFromFile("res/enemy_bullets/guardian_bullet_destroy_1.png");

        sf::Texture guardian_bullet_destroy_2tex;
        guardian_bullet_destroy_2tex.loadFromFile("res/enemy_bullets/guardian_bullet_destroy_2.png");

        sf::Texture guardian_bullet_destroy_3tex;
        guardian_bullet_destroy_3tex.loadFromFile("res/enemy_bullets/guardian_bullet_destroy_3.png");

        sf::Texture guardian_bullet_destroy_4tex;
        guardian_bullet_destroy_4tex.loadFromFile("res/enemy_bullets/guardian_bullet_destroy_4.png");

        sf::Texture guardian_bullet_destroy_5tex;
        guardian_bullet_destroy_5tex.loadFromFile("res/enemy_bullets/guardian_bullet_destroy_5.png");

        sf::Texture guardian_bullet_destroy_6tex;
        guardian_bullet_destroy_6tex.loadFromFile("res/enemy_bullets/guardian_bullet_destroy_6.png");


        //idpd_bullet
        sf::Texture idpd_bullettex;
        idpd_bullettex.loadFromFile("res/enemy_bullets/sprIDPD_bullet.png");
        //idpd_bullet_2
        sf::Texture idpd_bullet_2tex;
        idpd_bullet_2tex.loadFromFile("res/enemy_bullets/sprIDPD_bullet_2.png");

            //idpd_bullet_destroy1
            sf::Texture idpd_bullet_destroy1tex;
            idpd_bullet_destroy1tex.loadFromFile("res/enemy_bullets/sprIDPD_bullet_destroy1.png");

            //idpd_bullet_destroy2
            sf::Texture idpd_bullet_destroy2tex;
            idpd_bullet_destroy2tex.loadFromFile("res/enemy_bullets/sprIDPD_bullet_destroy2.png");

            //idpd_bullet_destroy3
            sf::Texture idpd_bullet_destroy3tex;
            idpd_bullet_destroy3tex.loadFromFile("res/enemy_bullets/sprIDPD_bullet_destroy3.png");

            //idpd_bullet_destroy4
            sf::Texture idpd_bullet_destroy4tex;
            idpd_bullet_destroy4tex.loadFromFile("res/enemy_bullets/sprIDPD_bullet_destroy4.png");


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


        //shadow24
        sf::Texture shadow24tex;
        shadow24tex.loadFromFile("res/shadow24.png");
        sf::VertexArray draw_shadow24s = create_vertex_array(shadow24tex, 1500 * draw_mult);

        //shadow24
        sf::Texture shadow48tex;
        shadow48tex.loadFromFile("res/shadow48.png");
        sf::VertexArray draw_shadow48s = create_vertex_array(shadow48tex, 1500 * draw_mult);

        //banditgun
        sf::Texture bandit_guntex;
        bandit_guntex.loadFromFile("res/enemies/desert/bandit/sprBanditGun.png");
        //banditgun
        sf::Texture idpd_freak_guntex;
        idpd_freak_guntex.loadFromFile("res/enemies/sprIDPDFreakGun.png");

        //playerbullet1_1 (revolver bullets etc.)
        sf::Texture playerbullet1_1tex;
        playerbullet1_1tex.loadFromFile("res/player/projectiles/bullets/playerbullet1_1.png");
        //playerbullet1_2
        sf::Texture playerbullet1_2tex;
        playerbullet1_2tex.loadFromFile("res/player/projectiles/bullets/playerbullet1_2.png");

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

        //horror_beam_destroyA1
        sf::Texture horror_beam_destroyA1;
        horror_beam_destroyA1.loadFromFile("res/player/projectiles/horror/horror_beam_destroy_A1.png");
        //horror_beam_destroyA2
        sf::Texture horror_beam_destroyA2;
        horror_beam_destroyA2.loadFromFile("res/player/projectiles/horror/horror_beam_destroy_A2.png");
        //horror_beam_destroyA3
        sf::Texture horror_beam_destroyA3;
        horror_beam_destroyA3.loadFromFile("res/player/projectiles/horror/horror_beam_destroy_A3.png");

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

        sf::Texture idpd_freak_revive_area_tex;
        idpd_freak_revive_area_tex.loadFromFile("res/enemies/sprPopoReviveArea.png");

        sf::Texture idpd_freak_revive_tex;
        idpd_freak_revive_tex.loadFromFile("res/enemies/sprPopoRevive.png");

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
        temp.setOrigin({ 20,20 });
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
        temp.setOrigin({ 16,16 });
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

    for (int i = 0; i < rotateable_sprites_guns_top_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        rotateable_sprites_guns_top.push_back(temp);
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
    for (int i = 0; i < variable_textures_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        variable_textures.push_back(temp);
    }
    for (int i = 0; i < variable_textures_bloom_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        variable_textures_bloom.push_back(temp);
    }
    //walls
    for (int i = 0; i < wall_textures_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 0,0 });
        temp.setTexture(allWallTops);
        wall_textures.push_back(temp);
    }
    for (int i = 0; i < wall_textures_bot_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 0,0 });
        temp.setTexture(allWallBots);
        wall_textures_bot.push_back(temp);
    }
    for (int i = 0; i < wall_boarder_textures_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 4,4 });
        temp.setTexture(allWallBoarders);
        wall_boarder_textures.push_back(temp);
    }
    for (int i = 0; i < floor_textures_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 0,0 });
        temp.setTexture(allFloors_tex);
        floor_textures.push_back(temp);
    }
    for (int i = 0; i < floor_textures_B_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setTexture(allFloors_tex);
        floor_textures_B.push_back(temp);
    }
    for (int i = 0; i < explo_tiles_tex_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 0,0 });
        temp.setTexture(allExploTiles);
        explo_tiles_tex.push_back(temp);
    }
    //throne 2
    for (int i = 0; i < T2_explo_tiles_tex_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 0,0 });
        temp.setTexture(Explo_T2_Tiles);
        T2_explo_tiles_tex.push_back(temp);
    }
    for (int i = 0; i < T2_floor_tiles_tex_max; i++) {
        sf::Sprite temp;
        temp.setColor({ 0, 0, 0, 0 });
        temp.setOrigin({ 0,0 });
        temp.setTexture(Floor_T2_Tiles);
        T2_floor_tiles_tex.push_back(temp);
    }
    for (int i = 0; i < popup_texts_max; i++) {
        sf::Text temp;
        temp.setString("");
        temp.setFont(font);
        temp.setCharacterSize(8);
        popup_texts.push_back(temp);
    }

    portal_sprite.setOrigin(16, 16);

    window.setVerticalSyncEnabled(false);
    window.setMouseCursorGrabbed(true);

    //window.setMouseCursorVisible(false);

    allObjects[0].friction = 0.45f;

    seed = rand();

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

            //change sprites
            bullet2_1tex.loadFromFile("res/enemy_bullets/sprEnemyBullet2_1_throne.png");
            bullet2_1BIGtex.loadFromFile("res/enemy_bullets/sprEnemyBullet2_1BIG_throne.png");

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
        tx.setColor(sf::Color::White);
        tx.setPosition({ 2, 12 });
        ty.setString("y: " + std::to_string(allObjects[0].position.y));
        ty.setCharacterSize(8);
        ty.setFont(font);
        ty.setColor(sf::Color::White);
        ty.setPosition({2, 2});
        ts.setString("LOOPS: " + std::to_string(LOOPS));
        ts.setCharacterSize(8);
        ts.setFont(font);
        ts.setColor(sf::Color::White);
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
        tO.setColor(sf::Color::White);
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
        tO0.setColor(sf::Color::White);
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
            allObjects[0].team = player_team;
            //do player movement first
            int horizontal_player_move = player_move_right - player_move_left;
            int vertical_player_move = player_move_down - player_move_up;
            float player_acceleration = 2.5f;
            if (allObjects[0].alarm1 > 0) {
                player_acceleration = 0;
            }
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
            allObjects[0].speeddir -= friction_player * player_friction_mult;

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

            camera_want_x = floor(allObjects[0].position.x + cameraOffset.x + mouse_offset_window_center_x + portal_camera_offset.x);
            camera_want_y = floor(allObjects[0].position.y + cameraOffset.y + mouse_offset_window_center_y + portal_camera_offset.y);
            portal_camera_offset = {0, 0};

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

                int tmpreloaded = reloaded;
                reloaded = breloaded;
                breloaded = tmpreloaded;
            }

            wep_reload -= reload_speed * (1 + stress * (1 - player_hp / player_max_hp));

            if (wep_reload < 0.0f && !reloaded) {
                reloaded = true;
                if (wep < 11) {
                    play_sound_on_player(snd_melee_flip_ID);
                }
                else {
                    get_wep_reload_sound(wep);
                }
            }

            if (wep_kick > 0) {
                wep_kick--;
            }
            else if (wep_kick < 0) {
                wep_kick++;
            }

            if (player_held_LMB) {      //player shooting logic
                fire_weapon(wep, direction_to_mouse);
            }
            calculate_ammo_drop_mult(); //calculate ammo mult after firing

            play_sounds_this_frame_count[snd_horror_beam_hold_ID] = -1;
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
                            play_sounds_this_frame_count[snd_horror_beam_hold_ID] = 1;
                            if (horror_beam_strength == 1.0f) {
                                play_sounds_this_frame_count[snd_horror_beam_start_ID] = 1;
                            }
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
                if (!all_sounds[snd_horror_beam_hold_ID].sound.getLoop()) {
                    all_sounds[snd_horror_beam_hold_ID].sound.play();
                    all_sounds[snd_horror_beam_hold_ID].sound.setLoop(true);
                    all_sounds[snd_horror_beam_hold_ID].sound.setVolume(0.0f);
                }
                if (ultra_picked == 2) {    //anomaly
                    int totalhp = 0;
                    for (int i = 1; i < max_objects; i++) {
                        switch (allObjects[i].my_id) {
                        case bandit:
                            totalhp += allObjects[i].my_hp;
                            break;
                        case idpd_freak:
                            totalhp += allObjects[i].my_hp;
                            break;
                        case throne_2:
                            totalhp += allObjects[i].my_hp;
                            break;
                        default:
                            break;
                        }
                    }
                    if (totalhp <= 140 && totalhp) {
                        //clear_all_bullets();
                        for (int i = 1; i < max_objects; i++) {
                            switch (allObjects[i].my_id) {
                            case bandit:
                                enemy_die(i, -1);
                                play_sound_relative_to_player(snd_horror_portal_ID, allObjects[i].position.x, allObjects[i].position.y);
                                break;
                            case idpd_freak:
                                enemy_die(i, -1);
                                play_sound_relative_to_player(snd_horror_portal_ID, allObjects[i].position.x, allObjects[i].position.y);
                                break;
                            default:
                                break;
                            }
                        }
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
            //portal
            if (create_portal && !created_portal) {
                create_portal = false;
                if (area != 0) {
                    create_object(create_portal_POS.x, create_portal_POS.y, 0, 0, portal, 0, 0);
                    create_object(create_portal_POS.x, create_portal_POS.y, 0, 0, portal_clear, 0, 0);
                    created_portal = true;
                }
                else {
                    if (!killed_throne_2) {
                        create_object(create_portal_POS.x, create_portal_POS.y, 0, 0, throne_2, 0, 0);
                    }
                }
            }

            //play sounds
            float pitch_offset = 0.0f;
            for (int i = 0; i < 255; i++) {
                if (play_sounds_this_frame_count[i] > 0) {
                    switch (i) {
                    default:
                        play_sound_random_pitch(all_sounds[i].sound, all_sounds[i].pitch_variance, i);
                        break;
                    case snd_rad_pickup_ID:
                        pitch_offset = (1.0f + ((float(player_rads) / float(player_level * 60)) / 4.0f));
                        all_sounds[i].sound.setPitch(pitch_offset);
                        all_sounds[i].sound.play();
                        break;
                    case snd_horror_beam_hold_ID:
                        all_sounds[snd_horror_beam_hold_ID].sound.setVolume(70.0f);
                        break;
                    case snd_portal_loop_ID:
                        
                        all_sounds[snd_portal_loop_ID].sound.setPlayingOffset(sf::milliseconds(0));
                        all_sounds[snd_portal_loop_ID].sound.setVolume(80.0f);
                        break;
                    case snd_plasma_huge_ID:
                        if (laser_brain < 1.1f) {
                            play_sound_random_pitch(all_sounds[i].sound, all_sounds[i].pitch_variance, i);
                        }
                        else {
                            play_sound_random_pitch(all_sounds[snd_plasma_huge_upgrade_ID].sound, all_sounds[snd_plasma_huge_upgrade_ID].pitch_variance, snd_plasma_huge_upgrade_ID);
                        }
                        break;
                    case snd_plasma_split_ID:
                        if (laser_brain < 1.1f) {
                            play_sound_random_pitch(all_sounds[i].sound, all_sounds[i].pitch_variance, i);
                        }
                        else {
                            play_sound_random_pitch(all_sounds[snd_plasma_split_upgrade_ID].sound, all_sounds[snd_plasma_split_upgrade_ID].pitch_variance, snd_plasma_split_upgrade_ID);
                        }
                        break;
                    case snd_player_hurt_ID:
                        switch(player_character){
                        case horror:
                            play_sound_random_pitch(all_sounds[snd_horror_hurt_ID].sound, all_sounds[snd_horror_hurt_ID].pitch_variance, snd_horror_hurt_ID);
                            break;
                        }
                        break;
                    }
                    play_sounds_this_frame_count[i] = 0;
                    play_sounds_this_frame_pos[i].x = 0;
                    play_sounds_this_frame_pos[i].y = 0;
                }
                else if (play_sounds_this_frame_count[i] < 0) {
                    switch (i) {
                    case snd_horror_beam_hold_ID:
                        all_sounds[snd_horror_beam_hold_ID].sound.setVolume(0.0f);
                        break;
                    case snd_portal_loop_ID:
                        all_sounds[snd_portal_loop_ID].sound.setVolume(0.0f);
                        break;
                    default:
                        break;
                    }
                    play_sounds_this_frame_count[i] = 0;
                    play_sounds_this_frame_pos[i].x = 0;
                    play_sounds_this_frame_pos[i].y = 0;
                }
            }

            for (int b = 0; b < popup_texts_max; b++) {
                if (popup_texts[b].getLineSpacing() > 20) {
                    popup_texts[b].setPosition(popup_texts[b].getPosition() + sf::Vector2f{ 0, -2 });
                }
                if (popup_texts[b].getLineSpacing() < 0) {
                    popup_texts[b].setString("");
                }
                popup_texts[b].setLineSpacing(popup_texts[b].getLineSpacing() - 1);
            }

            //set hp bar
            int player_health_bar_scale = 84.0f * (float(player_hp) / float(player_max_hp));
            if (player_health_bar_scale < 0) {
                player_health_bar_scale = 0;
            }
            health_bar_spr.setScale(player_health_bar_scale, 1);
            if (player_hp < 0) {
                player_hp = 0;
            }
            hp_text.setString(std::to_string(player_hp) + "/" + std::to_string(player_max_hp));
            std::string tmpstr1 = hp_text.getString();
            int tmp_dist = (tmpstr1.length()) * 8;
            tmp_dist = 84 / 2 - tmp_dist / 2;

            hp_text.setPosition(tmp_dist + 22, 7);

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

        //t2 stuff throne_2
        int choice = int(allObjects[T2_object_index].image_index * 0.4f);
        if (t2_draw_in_front == true) {
            T2_sprite.setTexture(throne2Appear);
        }
        else {
            if (allObjects[T2_object_index].my_id == throne_2) {
                if (allObjects[T2_object_index].next_hurt < current_frame) {
                    T2_sprite.setTexture(throne2Idle);
                    choice = int(allObjects[T2_object_index].image_index * 0.4f) % 8;
                }
                else {
                    T2_sprite.setTexture(throne2Hurt);
                    choice = int(-(allObjects[T2_object_index].next_hurt - current_frame - 6) * 0.4f);
                }
            }
            else {
                T2_sprite.setTexture(throne2Dead);
                choice = int(allObjects[T2_object_index].image_index * 0.4f) % 3;
            }
        }
        if (can_move_outside_T2_arena) {
            T2_sprite.setScale(0, 0);
        }
        T2_sprite.setTextureRect(sf::IntRect{ 250 * choice, 0, 250, 250 });

        int allEnemySpritesIndex = 0;
        int allEnemyCorpsesIndex = 0;

        int wallBoardeArrayIndex = 0;

        int wallShadowArrayIndex = 0;

        int floor1_under_ArrayIndex = 0;
        int floor1B_under_ArrayIndex = 0;
        int exploTile1_under_ArrayIndex = 0;
        int exploTile0_under_ArrayIndex = 0;
        int floor0_under_ArrayIndex = 0;

        int bullet1_1ArrayIndex = 0;
        int bullet1_2BIGArrayIndex = 0;
        int bullet2_1BIGArrayIndex = 0;

        int shadow24_ArrayIndex = 0;
        int shadow48_ArrayIndex = 0;

        int playerbullet1_bloomArrayIndex = 0;

        int rotateableSpriteBulletIndex = 0;
        int rotateableSpriteBulletHugeIndex = 0;
        int rotateableSpriteBulletHugeBloomIndex = 0;

        int rotateableSpriteBulletBigIndex = 0;
        int rotateableSpriteBulletBigBloomIndex = 0;

        int plasmaImpactIDX = 0;

        int rotateableSpriteGunIndex = 0;
        int rotateableSpriteGunTopIndex = 0;

        int rotateableEffectsSmallIndex = 0;
        int rotateableEffectsMediumIndex = 0;
        int rotateableEffectsLargeIndex = 0;

        int underEffectsSmallIndex = 0;

        int rotateableEffectsSmallBloomIndex = 0;

        int variableTexturesIndex = 0;

        int variableTexturesBloomIndex = 0;
        //int rotateableEffectsSmallNoRotBloomIndex = 0;

        int bullet_1_batchableIndex = 0;
        int bullet_2_batchableIndex = 0;

        int IDPD_explosionIndex = 0;

        int wall_texturesArrayIndex = 0;
        int wall_textures_botArrayIndex = 0;

        int floor_texturesArrayIndex = 0;
        int floor_textures_BArrayIndex = 0;

        int explo_tiles_texArrayIndex = 0;

        int T2_explo_tiles_texArrayIndex = 0;
        int T2_floor_tiles_texArrayIndex = 0;

        for (int i = 0; i < max_floors; i++) {
            currDrawPosition = allFloors[i].getPosition() - cameraPos;
            //currDrawPosition = {100, 100};
            if (abs(currDrawPosition.x - 160) < 200 && abs(currDrawPosition.y - 120) < 360) {
                int choice = allFloors[i].getOrigin().y;

                if (area == 1) {
                    if (choice > 3) {
                        add_sprite_32(floor1B_under_ArrayIndex, currDrawPosition - sf::Vector2f(0, 32), draw_floorTile1B_unders);
                        floor1B_under_ArrayIndex++;

                        floor_textures_B[floor_textures_BArrayIndex].setColor({ 255, 255, 255, 255 });
                        floor_textures_B[floor_textures_BArrayIndex].setPosition(currDrawPosition);
                        floor_textures_B[floor_textures_BArrayIndex].setTextureRect(sf::IntRect{ 36 * choice, 0, 36, 36 });
                        floor_textures_BArrayIndex++;
                    }
                    else {
                        add_sprite_32(floor1_under_ArrayIndex, currDrawPosition - sf::Vector2f(0, 32), draw_floorTile1_unders);
                        floor1_under_ArrayIndex++;

                        floor_textures[floor_texturesArrayIndex].setColor({ 255, 255, 255, 255 });
                        floor_textures[floor_texturesArrayIndex].setPosition(currDrawPosition);
                        floor_textures[floor_texturesArrayIndex].setTextureRect(sf::IntRect{ 32 * choice, 32 * area, 32, 32 });
                        floor_texturesArrayIndex++;
                    }
                }
                if (area == 0) {
                    add_sprite_32(floor0_under_ArrayIndex, currDrawPosition - sf::Vector2f(0, 32), draw_floorTile0_unders);
                    floor0_under_ArrayIndex++;

                    floor_textures[floor_texturesArrayIndex].setColor({ 255, 255, 255, 255 });
                    floor_textures[floor_texturesArrayIndex].setPosition(currDrawPosition);
                    floor_textures[floor_texturesArrayIndex].setTextureRect(sf::IntRect{ 32 * choice, 32 * area, 32, 32 });
                    floor_texturesArrayIndex++;

                    T2_floor_tiles_tex[T2_floor_tiles_texArrayIndex].setColor({ 255, 255, 255, 255 });
                    T2_floor_tiles_tex[T2_floor_tiles_texArrayIndex].setPosition(currDrawPosition - sf::Vector2f{ 16 , 16 });
                    T2_floor_tiles_tex[T2_floor_tiles_texArrayIndex].setTextureRect(sf::IntRect{ 64 * choice, 0, 64, 96 });
                    T2_floor_tiles_texArrayIndex++;
                }
            }
        }
        
        for (int i = cameraBoundsLeft; i < cameraBoundsRight; i++) {
            for (int j = cameraBoundsTop; j < cameraBoundsBottom; j++) {
                if (game_area[i][j].my_grid_type == wall) {         //drawing walls, will have to make this draw different things based on the surrounding walls
                    currDrawPosition = { i * 16 - cameraPos.x, j * 16 - cameraPos.y };
                    //int choice = (int(i * (2.3 * abs(j - i) + 1)) + int(j * (1.3 * abs(j - i) + 7)));
                    uint32_t rand_choice = i * 3000 + j + seed;
                    rand_choice ^= (rand_choice << 13);
                    rand_choice ^= (rand_choice >> 17);
                    rand_choice ^= (rand_choice << 5);
                    rand_choice ^= (rand_choice << 11);
                    rand_choice ^= (rand_choice >> 7);
                    rand_choice ^= (rand_choice << 9);
                    int choice = int(rand_choice % 100);
                    if (choice > 75) {
                        choice = 0;
                    }
                    if (choice > 70) {
                        choice = 1;
                    }
                    if (choice > 60) {
                        choice = 2;
                    }
                    if (choice > 24) {
                        choice = 4;
                    }
                    if (choice > 16) {
                        choice = 5;
                    }
                    if (choice > 7) {
                        choice = 6;
                    }
                    //boarder of wall
                   
                    wall_boarder_textures[wallBoardeArrayIndex].setColor({ 255, 255, 255, 255 });
                    wall_boarder_textures[wallBoardeArrayIndex].setPosition(currDrawPosition - sf::Vector2f{ 0, 8 });
                    wall_boarder_textures[wallBoardeArrayIndex].setTextureRect(sf::IntRect{ 24 * area, 24 * 0, 24, 24 });
                    wallBoardeArrayIndex++;


                    add_sprite_24(wallShadowArrayIndex, currDrawPosition - sf::Vector2f(4, -8), draw_Wall1shadows);
                    wallShadowArrayIndex++;

                    wall_textures[wall_texturesArrayIndex].setColor({ 255, 255, 255, 255 });
                    wall_textures[wall_texturesArrayIndex].setPosition(currDrawPosition - sf::Vector2f{0, 8});
                    wall_textures[wall_texturesArrayIndex].setTextureRect(sf::IntRect{ 16 * choice, 16 * area, 16, 16 });
                    wall_texturesArrayIndex++;

                    if (game_area[i][j + 1].my_grid_type != wall) {     //if there isnt a wall undernearth a bottom wall needs to be drawn
                        int choice = (i + j) % 4;
                        wall_textures_bot[wall_textures_botArrayIndex].setColor({ 255, 255, 255, 255 });
                        wall_textures_bot[wall_textures_botArrayIndex].setPosition(currDrawPosition);
                        wall_textures_bot[wall_textures_botArrayIndex].setTextureRect(sf::IntRect{ 16 * choice, 16 * area, 16, 16 });
                        wall_textures_botArrayIndex++;
                    }
                }
                else if (game_area[i][j].my_grid_type == boarder) {

                }
                else if (game_area[i][j].my_grid_type == exlpo_tile) {
                    currDrawPosition = { i * 16 - cameraPos.x, j * 16 - cameraPos.y };
                    int choice = (int(i * (2.3 * abs(j - i) + 1)) + int(j * (1.3 * abs(j - i) + 7))) % 4;
                    
                    explo_tiles_tex[explo_tiles_texArrayIndex].setColor({ 255, 255, 255, 255 });
                    explo_tiles_tex[explo_tiles_texArrayIndex].setPosition(currDrawPosition - sf::Vector2f{1, 1});
                    explo_tiles_tex[explo_tiles_texArrayIndex].setTextureRect(sf::IntRect{ 18 * choice, 18 * area, 18, 18 });
                    explo_tiles_texArrayIndex++;
                    if (area == 0) {
                        T2_explo_tiles_tex[T2_explo_tiles_texArrayIndex].setColor({ 255, 255, 255, 255 });
                        T2_explo_tiles_tex[T2_explo_tiles_texArrayIndex].setPosition(currDrawPosition - sf::Vector2f{ 1 + 7 , 1 + 7 });
                        T2_explo_tiles_tex[T2_explo_tiles_texArrayIndex].setTextureRect(sf::IntRect{ 32 * choice, 0, 32, 48 });
                        T2_explo_tiles_texArrayIndex++;
                    }
                    
                    if (area == 1) {
                        add_sprite_16(exploTile1_under_ArrayIndex, currDrawPosition - sf::Vector2f(0, 16), draw_exploTile1_unders);
                        exploTile1_under_ArrayIndex++;
                    }
                    if (area == 0) {
                        add_sprite_16(exploTile0_under_ArrayIndex, currDrawPosition - sf::Vector2f(0, 16), draw_exploTile0_unders);
                        exploTile0_under_ArrayIndex++;
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

                        if (allObjects[0].scale > 0.1f) {
                            add_sprite_24(shadow24_ArrayIndex, allObjects[idx].position - cameraPos + offset24, draw_shadow24s);
                            shadow24_ArrayIndex++;      //shadow
                        }

                        choice2 = 0;
                        if (allObjects[0].speeddir > 0.0f) {
                            choice2 = 1;
                        }
                        if (allObjects[0].next_hurt >= current_frame) {
                            choice2 = 2;
                        }
                        if (allObjects[idx].gun_angle > 360) {
                            allObjects[idx].gun_angle -= 360;
                        }
                        if (allObjects[idx].gun_angle < 360) {
                            allObjects[idx].gun_angle += 360;
                        }

                        if (allObjects[0].alarm1 == 0) {
                            allObjects[idx].gun_angle = 0;
                        }

                        choice = int(allObjects[0].image_index * 0.4f);
                        player_sprite.setPosition(allObjects[idx].position - cameraPos);
                        player_sprite.setRotation(allObjects[idx].gun_angle);   //rotation
                        player_sprite.setTextureRect(sf::IntRect{ 48 * choice, 48 * choice2, 48, 48 });
                        player_sprite.setScale(player_is_facing_right * allObjects[0].scale, 1 * allObjects[0].scale);

                        allObjects[0].alarm1 = 0;

                        tmp_wep_angle = direction_to_mouse;

                        if (wep < 11) {     //melee
                            tmp_wep_angle = direction_to_mouse + (wep_angle * (1 - (wep_kick / 20))) / degreestoradians;
                        }

                        wep_sprite.setPosition(allObjects[idx].position - cameraPos + sf::Vector2f(cos(tmp_wep_angle) * -wep_kick, sin(tmp_wep_angle) * -wep_kick));
                        wep_sprite.setTextureRect(sf::IntRect{ 36 * wep_shine_frame, 36 * wep, 36, 36 });
                        if (wep < 11) {
                            wep_sprite.setScale(1 * allObjects[0].scale, (player_is_facing_right * (reloaded * 2 - 1)) * allObjects[0].scale);
                        }
                        else {
                            wep_sprite.setScale(1 * allObjects[0].scale, player_is_facing_right * allObjects[0].scale);
                        }
                        wep_sprite.setRotation(tmp_wep_angle * degreestoradians);
                        wep_sprite.setOrigin(wep_get_origin(wep));

                        bwep_sprite.setPosition(allObjects[idx].position - cameraPos + sf::Vector2f(-2 * player_is_facing_right, swapmove));
                        bwep_sprite.setTextureRect(sf::IntRect{ 0, 36 * bwep, 36, 36 });
                        bwep_sprite.setScale(1 * allObjects[0].scale, player_is_facing_right * allObjects[0].scale);
                        bwep_sprite.setRotation(-90 - 15 * player_is_facing_right);
                        bwep_sprite.setOrigin(wep_get_origin(bwep));
                        break;
                    case throne_2:
                        /*choice = int(allObjects[idx].image_index * 0.4f);
                        if (allObjects[idx].alarm1 > 0) {
                            T2_sprite.setTexture(throne2Appear);
                        }
                        else {
                            T2_sprite.setTexture(throne2Idle);
                            choice = int(allObjects[idx].image_index * 0.4f) % 8;
                            t2_draw_in_front = false;
                        }
                        T2_sprite.setColor({ 255, 255, 255, 255 });
                        T2_sprite.setPosition(allObjects[idx].position - cameraPos);
                        T2_sprite.setRotation(0);
                        T2_sprite.setTextureRect(sf::IntRect{ 250 * choice, 0, 250, 250 });
                        T2_sprite.setOrigin(125, 125);
                        T2_sprite.setScale(1, 1);*/
                        break;
                    case portal:
                        choice = int(allObjects[idx].image_index * 0.4f) % 4;
                        if (allObjects[idx].alarm1 == 2) {
                            portal_sprite.setTexture(portalDisappearTex);
                            choice = int(allObjects[idx].image_index * 0.4f) % 12;
                        }
                        else {
                            portal_sprite.setTexture(portalIdleTex);
                            choice = int(allObjects[idx].image_index * 0.4f) % 4;
                        }
                        if (area == 0 || (area == 7 && sub_area == 3)) {
                            if (allObjects[idx].alarm3 <= 0) {
                                if (allObjects[idx].alarm1 == 2) {
                                    portal_sprite.setTexture(portalBigDisappearTex);
                                    choice = int(allObjects[idx].image_index * 0.4f) % 12;
                                }
                                else {
                                    portal_sprite.setTexture(portalBigIdleTex);
                                    choice = int(allObjects[idx].image_index * 0.4f) % 4;
                                }
                            }
                            else {
                                portal_sprite.setTexture(portalBigAppearTex);
                                choice = int(allObjects[idx].image_index * 0.4f) % 12;
                            }
                            portal_sprite.setPosition(allObjects[idx].position - cameraPos);
                            portal_sprite.setTextureRect({ choice * 96, 0, 96, 96 });
                            portal_sprite.setOrigin(48, 48);
                        }
                        else {
                            portal_sprite.setPosition(allObjects[idx].position - cameraPos);
                            portal_sprite.setTextureRect({ choice * 32, 0, 32, 32 });
                            portal_sprite.setOrigin(16, 16);
                        }
                        break;
                    case portal_lightning:
                        choice = int(allObjects[idx].image_index * 0.4f);
                        choice2 = allObjects[idx].alarm1;
                        variable_textures[variableTexturesIndex].setTexture(portalLightning);
                        variable_textures[variableTexturesIndex].setColor({ 255, 255, 255, 255 });
                        variable_textures[variableTexturesIndex].setPosition(allObjects[idx].position - cameraPos);
                        variable_textures[variableTexturesIndex].setRotation(0);
                        variable_textures[variableTexturesIndex].setTextureRect(sf::IntRect{ 32 * choice, 32 * choice2, 32, 32 });
                        variable_textures[variableTexturesIndex].setOrigin(16, 16);
                        variable_textures[variableTexturesIndex].setScale(1, 1);
                        variableTexturesIndex++;
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
                    case idpd_bullet:       //bullets destroy animation
                        if (allObjects[idx].image_index == 1) {
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(idpd_bullettex);
                        }
                        else {
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(idpd_bullet_2tex);
                        }

                        rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                        rotateableSpriteBulletIndex++;
                        break;
                    case guardian_bullet:
                        if (allObjects[idx].image_index < 18) {
                            choice = int(allObjects[idx].image_index * 0.4f) % 7;
                            variable_textures_bloom[variableTexturesBloomIndex].setTexture(GuardianBulletSpawn);
                            variable_textures_bloom[variableTexturesBloomIndex].setColor({ 255, 255, 255, 255 });
                            variable_textures_bloom[variableTexturesBloomIndex].setPosition(allObjects[idx].position - cameraPos);
                            variable_textures_bloom[variableTexturesBloomIndex].setRotation(0);
                            variable_textures_bloom[variableTexturesBloomIndex].setTextureRect(sf::IntRect{ 52 * choice, 0, 52, 52 });
                            variable_textures_bloom[variableTexturesBloomIndex].setOrigin(26, 26);
                            variable_textures_bloom[variableTexturesBloomIndex].setScale((allObjects[idx].speed.x > 0) * 2 - 1, 1);
                            variableTexturesBloomIndex++;
                        }
                        else {
                            choice = int(allObjects[idx].image_index * 0.4f) % 4;
                            switch (choice) {
                            default:
                                rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(guardian_bullet_1tex);
                                break;
                            case 1:
                                rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(guardian_bullet_2tex);
                                break;
                            case 2:
                                rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(guardian_bullet_3tex);
                                break;
                            case 3:
                                rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(guardian_bullet_4tex);
                                break;
                            }

                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(0);
                            rotateableSpriteBulletIndex++;
                        }
               
                        break;
                    case large_guardian_bullet:
                        if (allObjects[idx].image_index > 14) {
                            choice = int(allObjects[idx].image_index * 0.4f) % 4;
                            variable_textures_bloom[variableTexturesBloomIndex].setTexture(largeGuardianBullet);
                        }
                        else {
                            choice = int(allObjects[idx].image_index * 0.4f);
                            variable_textures_bloom[variableTexturesBloomIndex].setTexture(largeGuardianBulletSpawn);
                        }
                        variable_textures_bloom[variableTexturesBloomIndex].setColor({ 255, 255, 255, 255 });
                        variable_textures_bloom[variableTexturesBloomIndex].setPosition(allObjects[idx].position - cameraPos);
                        variable_textures_bloom[variableTexturesBloomIndex].setRotation(0);
                        variable_textures_bloom[variableTexturesBloomIndex].setTextureRect(sf::IntRect{ 32 * choice, 0, 32, 32 });
                        variable_textures_bloom[variableTexturesBloomIndex].setOrigin(16, 16);
                        variable_textures_bloom[variableTexturesBloomIndex].setScale(1, 1);
                        variableTexturesBloomIndex++;

                        break;
                    case T2_bullet:
                        choice = int(allObjects[idx].image_index * 0.4f) % 6;
                        variable_textures_bloom[variableTexturesBloomIndex].setTexture(T2Bullet);
                        variable_textures_bloom[variableTexturesBloomIndex].setColor({ 255, 255, 255, 255 });
                        variable_textures_bloom[variableTexturesBloomIndex].setPosition(allObjects[idx].position - cameraPos);
                        variable_textures_bloom[variableTexturesBloomIndex].setRotation(0);
                        variable_textures_bloom[variableTexturesBloomIndex].setTextureRect(sf::IntRect{ 32 * choice, 0, 32, 32 });
                        variable_textures_bloom[variableTexturesBloomIndex].setOrigin(16, 16);
                        variable_textures_bloom[variableTexturesBloomIndex].setScale(1, 1);
                        variableTexturesBloomIndex++;
                        break;
                    case guardian_bullet_destroy:
                        choice = int(allObjects[idx].rotation);
                        switch (choice) {
                        default:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(guardian_bullet_destroy_1tex);
                            break;
                        case 1:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(guardian_bullet_destroy_2tex);
                            break;
                        case 2:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(guardian_bullet_destroy_3tex);
                            break;
                        case 3:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(guardian_bullet_destroy_4tex);
                            break;
                        case 4:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(guardian_bullet_destroy_5tex);
                            break;
                        }

                        rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(0);
                        rotateableSpriteBulletIndex++;
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
                            break;
                        case 1:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(bullet1_destroy2tex);
                            break;
                        case 2:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(bullet1_destroy3tex);
                            break;
                        case 3:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(bullet1_destroy4tex);
                            break;
                        }
                        rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                        rotateableSpriteBulletIndex++;
                        break;
                    case idpd_bullet_destroy:       //bullets destroy animation
                        choice = int(allObjects[idx].image_index * 0.4f);
                        switch (choice) {
                        case 0:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(idpd_bullet_destroy1tex);
                            break;
                        case 1:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(idpd_bullet_destroy2tex);
                            break;
                        case 2:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(idpd_bullet_destroy3tex);
                            break;
                        case 3:
                            rotateable_sprites_bullets[rotateableSpriteBulletIndex].setTexture(idpd_bullet_destroy4tex);
                            break;
                        }
                        rotateable_sprites_bullets[rotateableSpriteBulletIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_sprites_bullets[rotateableSpriteBulletIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_sprites_bullets[rotateableSpriteBulletIndex].setRotation(allObjects[idx].direction);
                        rotateableSpriteBulletIndex++;
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
                        choice = int(allObjects[idx].image_index * 0.4f);
                        rotateable_effects_small[rotateableEffectsSmallIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_effects_small[rotateableEffectsSmallIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_effects_small[rotateableEffectsSmallIndex].setRotation(0.0f);
                        rotateable_effects_small[rotateableEffectsSmallIndex].setTextureRect(sf::IntRect{ allObjects[idx].image_index * 8, 40, 8, 8});
                        rotateableEffectsSmallIndex++;
                        break;
                    case idpd_spawn:

                        if (allObjects[idx].alarm3 > 0) {  //portal start
                            choice = int(allObjects[idx].image_index * 0.4f);
                            rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setRotation(0.0f);
                            rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setTextureRect(sf::IntRect{ choice * 8, 104, 8, 8 });
                            rotateableEffectsSmallBloomIndex++;
                        }
                        else if (allObjects[idx].alarm2 >= 13) {
                            choice = int(allObjects[idx].image_index * 0.4f) % 4;
                            rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setRotation(0.0f);
                            rotateable_effects_small_bloom[rotateableEffectsSmallBloomIndex].setTextureRect(sf::IntRect{ choice * 8, 40, 8, 8 });
                            rotateableEffectsSmallBloomIndex++;
                        }

                        else {
                            choice = int(allObjects[idx].image_index * 0.4f);
                            variable_textures_bloom[variableTexturesBloomIndex].setTexture(idpdPortalClose);
                            variable_textures_bloom[variableTexturesBloomIndex].setColor({ 255, 255, 255, 255 });
                            variable_textures_bloom[variableTexturesBloomIndex].setPosition(allObjects[idx].position - cameraPos);
                            variable_textures_bloom[variableTexturesBloomIndex].setRotation(0);
                            variable_textures_bloom[variableTexturesBloomIndex].setTextureRect(sf::IntRect{ 32 * choice, 0, 32, 32 });
                            variable_textures_bloom[variableTexturesBloomIndex].setOrigin(16, 16);
                            variable_textures_bloom[variableTexturesBloomIndex].setScale(1, 1);
                            variableTexturesBloomIndex++;
                        }


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
                            if (choice > 6) {
                                choice = 0;
                            }
                            rotateable_effects_medium[rotateableEffectsMediumIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_effects_medium[rotateableEffectsMediumIndex].setPosition(allObjects[idx].position - cameraPos);
                            rotateable_effects_medium[rotateableEffectsMediumIndex].setRotation(0);
                            rotateable_effects_medium[rotateableEffectsMediumIndex].setScale(1, 1);
                            rotateable_effects_medium[rotateableEffectsMediumIndex].setTextureRect(sf::IntRect{ 16 * choice, 32 + allObjects[idx].size * 16, 16, 16});
                            rotateableEffectsMediumIndex++;
                        }
                        break;
                    case ammo_pack_destroy:
                        choice = int(allObjects[idx].image_index * 0.4f);

                        rotateable_effects_medium[rotateableEffectsMediumIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_effects_medium[rotateableEffectsMediumIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_effects_medium[rotateableEffectsMediumIndex].setRotation(0);
                        rotateable_effects_medium[rotateableEffectsMediumIndex].setScale(1, 1);
                        rotateable_effects_medium[rotateableEffectsMediumIndex].setTextureRect(sf::IntRect{ 16 * choice, allObjects[idx].size * 16, 16, 16});
                        rotateableEffectsMediumIndex++;
                        break;
                    case heal_FX:
                        choice = int(allObjects[idx].image_index * 0.4f);

                        rotateable_effects_medium[rotateableEffectsMediumIndex].setColor({ 255, 255, 255, 255 });
                        rotateable_effects_medium[rotateableEffectsMediumIndex].setPosition(allObjects[idx].position - cameraPos);
                        rotateable_effects_medium[rotateableEffectsMediumIndex].setRotation(0);
                        rotateable_effects_medium[rotateableEffectsMediumIndex].setScale(1, 1);
                        rotateable_effects_medium[rotateableEffectsMediumIndex].setTextureRect(sf::IntRect{ 16 * choice, 5 * 16, 16, 16 });
                        rotateableEffectsMediumIndex++;
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
                        rotateable_sprites_guns[rotateableSpriteGunIndex].setScale(1, 1);
                        rotateable_sprites_guns[rotateableSpriteGunIndex].setRotation(allObjects[idx].direction * degreestoradians);
                        rotateableSpriteGunIndex++;    //gun

                        all_enemy_sprites[allEnemySpritesIndex].setColor({ 255, 255, 255, 255 });
                        all_enemy_sprites[allEnemySpritesIndex].setPosition(allObjects[idx].position - cameraPos);
                        all_enemy_sprites[allEnemySpritesIndex].setScale(allObjects[idx].facing_right * 2 - 1, 1);

                        if (allObjects[idx].image_index >= 0) {
                            if (abs(allObjects[idx].speed.x) < 0.01f && abs(allObjects[idx].speed.y) < 0.01f) {
                                choice = (int(allObjects[idx].image_index * 0.4f) % 4);
                                choice2 = 0;
                            }
                            else {
                                choice = (int(allObjects[idx].image_index * 0.4f) % 6);
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
                    case idpd_freak:
                        add_sprite_48(shadow48_ArrayIndex, allObjects[idx].position - cameraPos + offset48, draw_shadow48s);
                        shadow48_ArrayIndex++;      //shadow
                        if (allObjects[idx].gun_angle > 180.0f / degreestoradians) {
                            allObjects[idx].gun_angle -= 180.0f / degreestoradians;
                        }
                        if (allObjects[idx].gun_angle < -180.0f / degreestoradians) {
                            allObjects[idx].gun_angle += 180.0f / degreestoradians;
                        }
                        
                        if (allObjects[idx].gun_angle <= 0) {
                            sf::Vector2f gun_offset = { cos(allObjects[idx].gun_angle) * 3, sin(allObjects[idx].gun_angle) * 3 };
                            rotateable_sprites_guns[rotateableSpriteGunIndex].setTexture(idpd_freak_guntex);
                            rotateable_sprites_guns[rotateableSpriteGunIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_guns[rotateableSpriteGunIndex].setPosition(allObjects[idx].position + gun_offset - cameraPos);
                            rotateable_sprites_guns[rotateableSpriteGunIndex].setOrigin({ 16,16 });
                            rotateable_sprites_guns[rotateableSpriteGunIndex].setRotation(allObjects[idx].gun_angle * degreestoradians);
                            if (abs(allObjects[idx].gun_angle) > 90.0f / degreestoradians) {
                                rotateable_sprites_guns[rotateableSpriteGunIndex].setScale(1, -1);
                            }
                            else {
                                rotateable_sprites_guns[rotateableSpriteGunIndex].setScale(1, 1);
                            }
                            rotateableSpriteGunIndex++;    //gun
                        }
                        else {
                            rotateable_sprites_guns_top[rotateableSpriteGunTopIndex].setTexture(idpd_freak_guntex);
                            sf::Vector2f gun_offset = { cos(allObjects[idx].gun_angle) * 3, sin(allObjects[idx].gun_angle) * 3 };
                            rotateable_sprites_guns_top[rotateableSpriteGunTopIndex].setColor({ 255, 255, 255, 255 });
                            rotateable_sprites_guns_top[rotateableSpriteGunTopIndex].setPosition(allObjects[idx].position + gun_offset - cameraPos);
                            rotateable_sprites_guns_top[rotateableSpriteGunTopIndex].setOrigin({ 16,16 });
                            rotateable_sprites_guns_top[rotateableSpriteGunTopIndex].setRotation(allObjects[idx].gun_angle* degreestoradians);
                            if (abs(allObjects[idx].gun_angle) > 90.0f / degreestoradians) {
                                rotateable_sprites_guns_top[rotateableSpriteGunTopIndex].setScale(1, -1);
                            }
                            else {
                                rotateable_sprites_guns_top[rotateableSpriteGunTopIndex].setScale(1, 1);
                            }
                            rotateableSpriteGunTopIndex++;    //gun
                        }

                        all_enemy_sprites[allEnemySpritesIndex].setColor({ 255, 255, 255, 255 });
                        all_enemy_sprites[allEnemySpritesIndex].setPosition(allObjects[idx].position - cameraPos);
                        all_enemy_sprites[allEnemySpritesIndex].setScale(allObjects[idx].facing_right * 2 - 1, 1);

                        if (allObjects[idx].next_hurt > current_frame) {
                            choice2 = 2;
                            choice = int(-(allObjects[idx].next_hurt - current_frame - 6) * 0.4f);
                        }
                        else {
                            if (abs(allObjects[idx].speed.x) < 0.01f && abs(allObjects[idx].speed.y) < 0.01f) {
                                choice = (int(allObjects[idx].image_index * 0.4f) % 10);
                                choice2 = 0;
                            }
                            else {
                                choice = (int(allObjects[idx].image_index * 0.4f) % 6);
                                choice2 = 1;
                            }
                        }

                        choice2 += 3;

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

                        choice2 = 2;

                        all_enemy_corpses[allEnemyCorpsesIndex].setTextureRect(sf::IntRect{ 32 * choice, 32 * choice2, 32, 32 });
                        allEnemyCorpsesIndex++;

                        break;
                    case idpd_freak_corpse:
                        all_enemy_corpses[allEnemyCorpsesIndex].setColor({ 255, 255, 255, 255 });
                        all_enemy_corpses[allEnemyCorpsesIndex].setPosition(allObjects[idx].position - cameraPos);
                        all_enemy_corpses[allEnemyCorpsesIndex].setScale(allObjects[idx].facing_right * 2 - 1, 1);

                        choice = int(allObjects[idx].image_index * 0.4f);
                        if (choice > 5) {
                            choice = 5;
                        }

                        choice2 = 2 + 3;

                        all_enemy_corpses[allEnemyCorpsesIndex].setTextureRect(sf::IntRect{ 32 * choice, 32 * choice2, 32, 32 });
                        allEnemyCorpsesIndex++;
                        
                        if (allObjects[idx].alarm1 < 15) {
                            choice = int((14 - allObjects[idx].alarm1) * 0.4f);
                            variable_textures[variableTexturesIndex].setTexture(idpd_freak_revive_area_tex);
                            variable_textures[variableTexturesIndex].setColor({ 255, 255, 255, 255 });
                            variable_textures[variableTexturesIndex].setPosition(allObjects[idx].position - cameraPos);
                            variable_textures[variableTexturesIndex].setRotation(0);
                            variable_textures[variableTexturesIndex].setTextureRect(sf::IntRect{ 35 * choice, 0, 35, 40 });
                            variable_textures[variableTexturesIndex].setOrigin(18, 20);
                            variable_textures[variableTexturesIndex].setScale(1, 1);
                            variableTexturesIndex++;
                        }

                        break;
                    case idpd_freak_revive:
                        choice = int(allObjects[idx].image_index * 0.4f);
                        variable_textures[variableTexturesIndex].setTexture(idpd_freak_revive_tex);
                        variable_textures[variableTexturesIndex].setColor({ 255, 255, 255, 255 });
                        variable_textures[variableTexturesIndex].setPosition(allObjects[idx].position - cameraPos);
                        variable_textures[variableTexturesIndex].setRotation(0);
                        variable_textures[variableTexturesIndex].setTextureRect(sf::IntRect{ 48 * choice, 0, 48, 48 });
                        variable_textures[variableTexturesIndex].setOrigin(24, 40);
                        variable_textures[variableTexturesIndex].setScale(1, 1);
                        variableTexturesIndex++;
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
        tC.setColor(sf::Color::White);
        tC.setFont(font);
        tC.setPosition({ 2, 32 });

        //onscreen sprites drawn
        sf::Text tspr;

        tspr.setString("rads: " + std::to_string(player_rads));
        tspr.setCharacterSize(8);
        tspr.setFont(font);
        tspr.setColor(sf::Color::White);
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
        debug1.setString("allObjects[T2_object_index].alarm3: " + std::to_string(allObjects[T2_object_index].alarm3));
        debug1.setCharacterSize(8);
        debug1.setFont(font);
        debug1.setColor(sf::Color::White);
        debug1.setPosition({ 2, 72 });

        sf::Text debug2;

        debug2.setString("allObjects[T2_object_index].size: " + std::to_string(allObjects[T2_object_index].size));
        debug2.setCharacterSize(8);
        debug2.setFont(font);
        debug2.setColor(sf::Color::White);
        debug2.setPosition({ 2, 92 });


        //area in which physics happen
        vector2D_reset(top_physics - 6, bottom_physics + 6, left_physics - 6, right_physics + 6);       //make sure these dont go out of bounds

        //before drawing clear the rest of the vertex arrays which could have extra sprites from the previos frame, each array only  needs to be cleared if the sprite appears in the current "area"

        sf::RenderStates Renderer;
        sf::RenderStates RendererBloom;
        RendererBloom.blendMode = sf::BlendAdd;

        if (area >= 0) {

            clear_extra_vertex_array(draw_bullet1_1s, bullet1_1ArrayIndex);
            clear_extra_vertex_array(draw_bullet1_2BIGs, bullet1_2BIGArrayIndex);

            clear_extra_vertex_array(draw_Wall1shadows, wallShadowArrayIndex);

            clear_extra_vertex_array(draw_exploTile1_unders, exploTile1_under_ArrayIndex);
            clear_extra_vertex_array(draw_exploTile0_unders, exploTile0_under_ArrayIndex);

            clear_extra_vertex_array(draw_floorTile0_unders, floor0_under_ArrayIndex);

            clear_extra_vertex_array(draw_floorTile1B_unders, floor1B_under_ArrayIndex);
            clear_extra_vertex_array(draw_floorTile1_unders, floor1_under_ArrayIndex);

            clear_extra_vertex_array(draw_shadow24s, shadow24_ArrayIndex);
            clear_extra_vertex_array(draw_shadow48s, shadow48_ArrayIndex);

            //portal spirals in background

            spiral_cont_step();
            portal_spiral_step();

            int portals_amount_left = all_portal_spirals_count;
            int portals_sprital_position = all_portal_spirals_start;

            while (portals_amount_left > 0) {
                portal_spiral_spr.setPosition(all_portal_spirals[portals_sprital_position].position);
                portal_spiral_spr.setRotation(all_portal_spirals[portals_sprital_position].image_angle + 45);
                portal_spiral_spr.setScale(all_portal_spirals[portals_sprital_position].image_scale, all_portal_spirals[portals_sprital_position].image_scale);
                int darkness = 255 * (all_portal_spirals[portals_sprital_position].image_scale + 0.2f);
                if (darkness > 255) {
                    darkness = 255;
                }
                sf::Uint8 color_darkness = darkness;
                portal_spiral_spr.setColor({ color_darkness, color_darkness, color_darkness });
                buffer_under.draw(portal_spiral_spr);
                portals_amount_left--;
                portals_sprital_position--;
                if (portals_sprital_position < 0) {
                    portals_sprital_position = 999;
                }
            }

            //throne 2 floors underneath floors

            //explo tiles
            for (sf::Sprite spr : T2_explo_tiles_tex) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_under.draw(spr);
            }
            reset_rotateable_sprites(T2_explo_tiles_tex, T2_explo_tiles_texArrayIndex);
            //floor tiles
            for (sf::Sprite spr : T2_floor_tiles_tex) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_under.draw(spr);
            }
            reset_rotateable_sprites(T2_floor_tiles_tex, T2_floor_tiles_texArrayIndex);

            Renderer.texture = &exploTile1_under;
            buffer_under.draw(draw_exploTile1_unders, Renderer);
            Renderer.texture = &exploTile0_under;
            buffer_under.draw(draw_exploTile0_unders, Renderer);

            Renderer.texture = &floorTile1B_under;
            buffer_under.draw(draw_floorTile1B_unders, Renderer);

            Renderer.texture = &floorTile1_under;
            buffer_under.draw(draw_floorTile1_unders, Renderer);
            Renderer.texture = &floorTile0_under;
            buffer_under.draw(draw_floorTile0_unders, Renderer);

           

            //floors, drawn underneath explo tiles
            for (sf::Sprite spr : floor_textures) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_under.draw(spr);
            }
            reset_rotateable_sprites(floor_textures, floor_texturesArrayIndex);

            for (sf::Sprite spr : floor_textures_B) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_under.draw(spr);
            }
            reset_rotateable_sprites(floor_textures_B, floor_textures_BArrayIndex);

            //explo tiles
            for (sf::Sprite spr : explo_tiles_tex) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_under.draw(spr);
            }
            reset_rotateable_sprites(explo_tiles_tex, explo_tiles_texArrayIndex);

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
            Renderer.texture = &shadow48tex;
            shadows.draw(draw_shadow48s, Renderer);

            shadows.display();

            sf::Sprite combinedshadows(shadows.getTexture());
            combinedshadows.setColor(sf::Color(255, 255, 255, 100));
            //window.draw(combinedshadows);
            buffer_over.draw(combinedshadows);

            //walls
            for (sf::Sprite spr : wall_textures_bot) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr);
            }
            reset_rotateable_sprites(wall_textures_bot, wall_textures_botArrayIndex);

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

            for (sf::Sprite spr : variable_textures_bloom) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr);
            }

            for (sf::Sprite spr : variable_textures) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr);
            }
            reset_rotateable_sprites(variable_textures, variableTexturesIndex);

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

            for (sf::Sprite spr : rotateable_sprites_guns_top) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr);
            }
            reset_rotateable_sprites(rotateable_sprites_guns_top, rotateableSpriteGunTopIndex);


            if (!t2_draw_in_front) {
                buffer_over.draw(T2_sprite);
            }

            //portal
            buffer_over.draw(portal_sprite);


            buffer_over.draw(bwep_sprite);

            if (direction_to_mouse - (180 / degreestoradians) > 0) {
                buffer_over.draw(wep_sprite);
            }

            //player
            buffer_over.draw(player_sprite);

            if (direction_to_mouse - (180 / degreestoradians) <= 0) {
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


            for (sf::Sprite spr : variable_textures_bloom) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                spr.setScale(2, 2);
                spr.setColor({ 255, 255, 255, 25 });
                buffer_over.draw(spr, RendererBloom);
                spr.setScale(1, 1);
            }
            reset_rotateable_sprites(variable_textures_bloom, variableTexturesBloomIndex);


            portal_sprite.setScale(2, 2);
            portal_sprite.setColor({ 255, 255, 255, 25 });
            buffer_over.draw(portal_sprite, RendererBloom);
            portal_sprite.setScale(1, 1);
            portal_sprite.setColor({ 255, 255, 255, 255 });

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
            for (sf::Sprite spr : wall_boarder_textures) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr);
            }
            reset_rotateable_sprites(wall_boarder_textures, wallBoardeArrayIndex);

            for (sf::Sprite spr : wall_textures) {
                if (spr.getColor() == sf::Color{ 0, 0, 0, 0 }) {
                    break;
                }
                buffer_over.draw(spr);
            }
            reset_rotateable_sprites(wall_textures, wall_texturesArrayIndex);

            if (t2_draw_in_front) {
                buffer_over.draw(T2_sprite);
            }

            for (sf::Text tex : popup_texts) {
                if (tex.getLineSpacing() > 20 || int(tex.getLineSpacing()) % 4 < 2) {
                    tex.setPosition(tex.getPosition() - cameraPos);
                    draw_text_NT(tex, buffer_over);
                    tex.setPosition(tex.getPosition() + cameraPos);
                }
            }

            buffer_over.draw(hp_bar_spr);
            buffer_over.draw(health_bar_spr);
            draw_text_NT(hp_text, buffer_over);

            buffer_over.display();
            //draw all sprites that are over shadows
            //window.draw(buffer_overSprite);

        }
        if(area == 2){

        }

        draw_text_NT(hp_text, buffer_over);
        //buffer_over.draw(c);
        bool debug_text_show = 0;

        if (debug_text_show) {
            draw_text_NT(tx, buffer_over);
            draw_text_NT(ty, buffer_over);
            draw_text_NT(ts, buffer_over);
            draw_text_NT(tC, buffer_over);
            draw_text_NT(tO, buffer_over);
            draw_text_NT(tO0, buffer_over);
            draw_text_NT(tspr, buffer_over);
            draw_text_NT(debug1, buffer_over);
            draw_text_NT(debug2, buffer_over);
        }

        if (!naitive_cursor_active) {
            buffer_over.draw(cursor_sprite);
        }

        //window.draw(bounding_defaul_res);
        if (!GAME_PAUSED) {
            current_frame++;
        }

        window.draw(buffer_overSprite);
        
        //window.draw(bufferShadows);
        

        window.display();

    }
    return 0;
}
