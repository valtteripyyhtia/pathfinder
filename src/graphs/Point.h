/**
 * @brief Point class.
 *
 * Point has x and y coordinates.
 *
 * @author Valtteri Pyyhtiä
 */

#ifndef POINT_H
#define POINT_H

namespace pathfinder {

    class Point {

        public:
            /**
             * @brief Point
             *
             * Initializes Point's x and y coordinates
             *
             * @param x coordinate
             * @param y coordinate
             */
            Point(int x, int y);

            /**
             * @brief Get x coordinate
             * @return x coordinate
             */
            int getX() const;

            /**
             * @brief Get y coordinate
             * @return y coordinate
             */
            int getY() const;

        private:
            int x;
            int y;

    };

}

#endif
