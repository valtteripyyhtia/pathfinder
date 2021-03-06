#ifndef GRAPHICS_CONTROLLER_H
#define GRAPHICS_CONTROLLER_H

#include "DemoConfigurations.h"
#include "GameWorld.h"
#include <SFML/Graphics.hpp>

class GraphicsController {

    public:
        GraphicsController(GameWorld* gameWorld,
                           sf::RenderWindow* window);

        void draw();

    private:
        GameWorld* gameWorld;

        sf::RenderWindow* window;

        void drawMainWindow();

        void drawTerrainBlock(const TerrainBlock* terrainBlock);

        void draw(int x, int y, sf::Color color);

        void drawPath();

        void drawCircle(int x, int y, sf::Color color);

        sf::Color wallColor = sf::Color(150, 150, 150);

        sf::Color grassColor = sf::Color(0, 200, 0);

        sf::Color waterColor = sf::Color(0, 191, 255);
};

#endif
