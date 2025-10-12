#include <random>
#include <SFML/Graphics.hpp>

static float degreestoradians = 57.2957795f;

inline float random_float(float max_value) {    //dont use in multithreaded for more randomness
	return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (max_value)));
}

inline float random_360_radians() {    //dont use in multithreaded for more randomness
    return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (360.0f / degreestoradians)));
}
inline float random_360_degrees() {    //dont use in multithreaded for more randomness
    return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (360.0f)));
}

inline float random_180_radians() {    //dont use in multithreaded for more randomness
    return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (180.0f / degreestoradians)));
}
inline float random_180_degrees() {    //dont use in multithreaded for more randomness
    return static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (180.0f)));
}


bool inline is_within_circle(sf::Vector2f pos1, sf::Vector2f pos2, float distance) {
	return (distance * distance) > ((pos1.x - pos2.x) * (pos1.x - pos2.x)) + ((pos1.y - pos2.y) * (pos1.y - pos2.y));
}