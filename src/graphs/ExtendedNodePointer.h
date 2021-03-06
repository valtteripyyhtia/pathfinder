/**
 * @brief ExtendedNodePointer class.
 *
 * ExtendedNodePointer wraps ExtendedNode inside.
 *
 * @author Valtteri Pyyhtiä
 */

#ifndef EXTENDED_NODE_POINTER_H
#define EXTENDED_NODE_POINTER_H

#include "ExtendedNode.h"

namespace pathfinder {

    class ExtendedNodePointer {

        public:
            /**
             * @brief ExtendedNodePointer
             *
             * Binds an ExtendedNode to this wrapper
             *
             * @param ExtendedNode to be binded
             */
            ExtendedNodePointer(ExtendedNode* extendedNode);

            /**
             * @brief Get a reference to binded ExtendedNode
             * @return reference to binded ExtendedNode
             */
            ExtendedNode& getExtendedNode() const;

            /**
             * @brief Compare two ExtendedNodePointers
             *
             * Uses the less than operator in ExtendedNode class.
             *
             * @param extendedNodePointer to be compared
             * @return true if this object is less than ExtendedNodePointer
             */
            bool operator<(const ExtendedNodePointer& extendedNodePointer) const;

        private:
            ExtendedNode* extendedNode; /*< binded ExtendedNode */
    };

}

#endif
