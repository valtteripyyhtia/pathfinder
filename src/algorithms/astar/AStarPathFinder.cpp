#include "AStarPathFinder.h"

namespace pathfinder {

    AStarPathFinder::AStarPathFinder(Graph* graph) : PathFinder(graph),
        extendedGraph(graph) {
        // do nothing at the moment
    }

    ExtendedNodeGraph& AStarPathFinder::getAllExtendedNodes() {
        return extendedGraph;
    }

    Path AStarPathFinder::findAndGetShortestPath(Node startNode, Node endNode) {
        pathfinder::Path path;
        initializeStartAndEndNodes(startNode, endNode);
        OpenList openList;
        openList.add(*start);

        while(!openList.isEmpty()) {
            ExtendedNode& current = openList.getBestNode();
            openList.removeBestNode();
            addNodeToClosedList(current);

            path.addNode(current.getNode());

            if(extendedNodeIsGoal(current))
                break;

            std::vector<ExtendedNode*> neighbours =
                    extendedGraph.getAccessibleNeighboursOfExtendedNode(current);

            const Node& currentNode = current.getNode();
            for(ExtendedNode* neighbour : neighbours) {
                const Node& neighbourNode = neighbour->getNode();
                float cost = current.getCurrentCost() +
                        movementCalculator.getCostBetweenNodes(currentNode,
                                                               neighbourNode);

                if(openList.contains(*neighbour) && cost < neighbour->getCurrentCost()) {
                   neighbour->setCurrentCost(cost);
                   neighbour->setTotalCost(cost+heuristic.estimateDistance(
                                               neighbourNode, endNode));
                   openList.fixOpenList();
                }
                else if(!neighbour->isInClosedList()) {
                    neighbour->setCurrentCost(cost);
                    neighbour->setTotalCost(cost+heuristic.estimateDistance(
                                                neighbourNode, endNode));
                    openList.add(*neighbour);
                }
            }
        }

        cleanExtendedNodesFromOpenAndClosedList(openList);
        return path;
    }

    void AStarPathFinder::initializeStartAndEndNodes(const Node& start,
                                                     const Node& end) {
        initializeEndNode(end);
        initializeStartNode(start);
    }

    void AStarPathFinder::initializeEndNode(const Node &endNode) {
        int endX = endNode.getX();
        int endY = endNode.getY();
        end = &extendedGraph.getExtendedNodeInPosition(endX, endY);
    }

    void AStarPathFinder::initializeStartNode(const Node &startNode) {
        int startX = startNode.getX();
        int startY = startNode.getY();
        start = &extendedGraph.getExtendedNodeInPosition(startX, startY);
        start->setCurrentCost(0);
        start->setTotalCost(heuristic.estimateDistance(startNode,
                                                       end->getNode()));
    }

    void AStarPathFinder::addNodeToClosedList(ExtendedNode& extendedNode) {
        extendedNode.setNodeToClosedList();
        closedList.push_back(&extendedNode);
    }

    bool AStarPathFinder::extendedNodeIsGoal(const ExtendedNode& extendedNode) const {
        return extendedNode == *end;
    }

    void AStarPathFinder::cleanExtendedNodesFromOpenAndClosedList(
            OpenList& openList) {

        while(!openList.isEmpty()) {
            resetExtendedNodeCurrentCost(openList.getBestNode());
            openList.removeBestNode();
        }

        while(!closedList.empty()) {
            ExtendedNode* nodeToRemove = closedList.back();
            resetExtendedNodeCurrentCost(*nodeToRemove);
            nodeToRemove->setNodeRemovedFromClosedList();
            closedList.pop_back();
        }
    }

    void AStarPathFinder::resetExtendedNodeCurrentCost(ExtendedNode& nodeToReset) {
        nodeToReset.setCurrentCost(std::numeric_limits<float>::max());
    }


}
