#include <SFML/Graphics.hpp>
#pragma once

void loadALLsprites() {
    sf::Texture middleWall1;
    middleWall1.loadFromFile("res/sprWall1Top_1.png");
    middleWall1.generateMipmap();
    sf::Vector2f const middleWall1size_f = static_cast<sf::Vector2f>(middleWall1.getSize());

    sf::VertexArray draw_middlewall1s{ sf::PrimitiveType::Quads, 4 * 725 };     //4 * 725, where 725 is the max amount of walls that can be drawn

    for (int i = 0; i < 725; i++) {
        int const idx = i * 4;
        draw_middlewall1s[idx + 0].texCoords = { 0.0f, 0.0f };
        draw_middlewall1s[idx + 1].texCoords = { middleWall1size_f.x, 0.0f };
        draw_middlewall1s[idx + 2].texCoords = { middleWall1size_f.x, middleWall1size_f.y };
        draw_middlewall1s[idx + 3].texCoords = { 0.0f, middleWall1size_f.y };

    }
}