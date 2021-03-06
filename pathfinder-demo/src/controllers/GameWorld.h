/**
 * @brief GameWorld
 *
 * GameWorld which controls the path finder demo
 *
 * @author Valtteri Pyyhtiä
 */

#ifndef GAME_WORLD_H
#define GAME_WORLD_H

#include "Updateable.h"

#include <random>
#include <cmath>
#include <iostream>

#include <Node.h>
#include <Point.h>
#include <BlockGraph.h>
#include <PathFinder.h>
#include <AStarPathFinder.h>
#include "DemoConfigurations.h"
#include "GameTimer.h"

using namespace pathfinder;

class GameWorld : public Updateable {

    public:
        /**
         * @brief Initializes GameWorld
         *
         * Initializes graph and sets A* as default path finder algorithm
         *
         * @param graphSize to be used in the GameWorld. Minimum width and
         * length of the graph is 1. If graphSize is lower than 1, then default
         * 35 is used as graph size.
         */
        GameWorld(int graphSize = 35);

        /**
         * @brief GameWorld destructor
         */
        ~GameWorld();

        /**
         * @brief Updates GameWorld
         */
        void update();

        /**
         * @brief Set A* algorithm to be used in path finding
         */
        void useAStarAlgorithm();

        /**
         * @brief Get width of the game world
         * @return width of the game world
         */
        int getWidth() const;

        /**
         * @brief Get height of the game world
         * @return height of the game world
         */
        int getHeight() const;

        /**
         * @brief Get BlockGraph
         * @return graph
         */
        BlockGraph* getBlockGraph();

        /**
         * @brief Create random walls
         */
        void createRandomWalls();

        /**
         * @brief Toggle moving on and off
         */
        void toggleMoving();

        /**
         * @brief Get start point position
         * @return start point position
         */
        const Point& getStartPoint() const;

        /**
         * @brief Get end point position
         * @return end point position
         */
        const Point& getEndPoint() const;

        /**
         * @brief Move start point to new location
         * @param point of the new location
         */
        void moveStartTo(const Point& point);

        /**
         * @brief Move end point to new location
         * @param point of the new location
         */
        void moveEndTo(const Point& point);

        /**
         * @brief Increase start point movement speed
         */
        void increaseMovementSpeed();

        /**
         * @brief Decrease start point movement speed
         */
        void decreaseMovementSpeed();

        /**
         * @brief Get currently the shortest path
         * @return shortest path
         */
        const Path& getPath() const;

    private:
        BlockGraph* graph;

        GameTimer gameTimer;

        int startMovingSpeed = START_MOVING_SPEED;

        int movingSpeed;

        int width;

        int height;

        PathFinder* pathFinder;

        Point start = Point(-1,-1);

        Point end = Point(-1,-1);

        Path* finalPath;

        bool movingEnabled;

        bool startAndEndNodesExistInGraph() const;

        void findAndCleanShortestPath();

        void findShortestPath(const Node& startNode, const Node& endNode);

        void moveAlongThePathIfNodeIsAccessible();

        void resetMovingSpeed();

        float getCostFactorFromStartPointsNode();
};

#endif
