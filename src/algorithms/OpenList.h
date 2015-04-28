/**
 * @brief OpenList class.
 *
 * OpenList holds ExtendedNodes
 *
 * @author Valtteri Pyyhtiä
 */

#ifndef OPENLIST_H
#define OPENLIST_H

#include "PriorityQueue.h"
#include "ExtendedNodePointer.h"
#include "ExtendedNode.h"

namespace pathfinder {

    class OpenList {

        public:
            /**
             * @brief initializes OpenList
             */
            OpenList();

            /**
             * @brief Add ExtendedNode into the open list
             * @param node to be added
             */
            void add(const ExtendedNode& node);

            /**
             * @brief Remove best node from the open list
             */
            void removeBestNode();

            /**
             * @brief Get best node from open list
             * @return reference to the best ExtendedNode
             */
            const ExtendedNode& getBestNode() const;

            /**
             * @brief Check if open list is empty
             * @return true if there's zero nodes in the open list
             */
            bool isEmpty() const;

        private:
            PriorityQueue<ExtendedNodePointer> openList;

    };

}

#endif