#include "OpenListTest.h"

SCENARIO("OpenList can be empty", "[openlist][extendednode]") {

    GIVEN("An empty OpenList") {

        pathfinder::OpenList openList;

        WHEN("Nothing is done") {

            THEN("OpenList is empty") {
                REQUIRE(openList.isEmpty());
            }

        }
    }
}

SCENARIO("ExtendedNodes can be added/removed to/from OpenList",
         "[openlist][extendednode]") {

    GIVEN("An empty OpenList") {

        pathfinder::OpenList openList;

        WHEN("Adding two ExtendedNodes with total costs 3 and 2 to open list") {

            pathfinder::Node node(1,0);
            pathfinder::ExtendedNode extNode1(&node);
            pathfinder::ExtendedNode extNode2(&node);

            extNode1.setTotalCost(3);
            extNode2.setTotalCost(2);

            openList.add(extNode1);
            openList.add(extNode2);

            THEN("Best node in the open list has total cost 2") {

                pathfinder::ExtendedNode bestNode = openList.getBestNode();

                Approx approximation((double)
                                     bestNode.getTotalCost());

                REQUIRE(approximation == 2);

            }

            AND_WHEN("Adding ExtendedNode with total cost 5") {

                pathfinder::ExtendedNode extNode3(&node);
                extNode3.setTotalCost(5);
                openList.add(extNode3);

                THEN("Best node in the open list has total cost 2") {

                    pathfinder::ExtendedNode bestNode = openList.getBestNode();

                    Approx approximation((double)
                                         bestNode.getTotalCost());

                    REQUIRE(approximation == 2);

                }

                AND_WHEN("Removing best node from the open list") {

                    openList.removeBestNode();

                    THEN("Best node in the open list has total cost 3") {

                        pathfinder::ExtendedNode bestNode = openList.getBestNode();

                        Approx approximation((double)
                                             bestNode.getTotalCost());

                        REQUIRE(approximation == 3);

                    }

                    AND_WHEN("Adding ExtendedNode with total cost 1") {

                        pathfinder::ExtendedNode extNode4(&node);
                        extNode4.setTotalCost(1);
                        openList.add(extNode4);

                        THEN("Best node in the open list has total cost 1") {

                            pathfinder::ExtendedNode bestNode = openList.getBestNode();

                            Approx approximation((double)
                                                 bestNode.getTotalCost());

                            REQUIRE(approximation == 1);

                        }
                    }

                }
            }
        }
    }
}

SCENARIO("ExtendedNodes can be checked if they are in the OpenList",
         "[openlist][extendednode]") {

    GIVEN("OpenList with two ExtendedNodes in positions (2,1) and (2,2)") {

        pathfinder::Node node1(2, 1);
        pathfinder::Node node2(2, 2);

        pathfinder::ExtendedNode extNode1(&node1);
        pathfinder::ExtendedNode extNode2(&node2);

        pathfinder::OpenList openList;
        openList.add(extNode1);
        openList.add(extNode2);

        WHEN("Checking if there is ExtendedNode (2,1) in the open list") {

            bool isInOpenList = openList.contains(extNode1);

            THEN("Open list contains ExtendedNode (2, 1)") {
                REQUIRE(isInOpenList);
            }

        }

        WHEN("Checking if there is ExtendedNode (2, 2) in the open list") {

            bool isInOpenList = openList.contains(extNode2);

            THEN("Open list contains ExtendedNode (2, 2)") {
                REQUIRE(isInOpenList);
            }

        }

        WHEN("Checking if there is ExtendedNode (1, 0) in the open list") {

            pathfinder::Node node3(1, 0);
            pathfinder::ExtendedNode extNode3(&node3);

            bool isInOpenList = openList.contains(extNode3);

            THEN("Open list does not contain ExtendedNode (1, 0)") {
                REQUIRE_FALSE(isInOpenList);
            }

            openList.add(extNode3);
            AND_WHEN("Adding ExtendedNode (1,0) to the open list") {

                openList.add(extNode3);

                THEN("ExtendedNode (1,0) is in the open list") {
                    REQUIRE(openList.contains(extNode3));
                }
            }
        }

        WHEN("Removing two nodes from the open list") {

            openList.removeBestNode();
            openList.removeBestNode();

            THEN("ExtendedNodes (2, 1) and (2, 2) are not in the open list") {

                bool bothNodesAreRemoved =
                        (!openList.contains(extNode1) &&
                         !openList.contains(extNode2))
                        ? true : false;

                REQUIRE(bothNodesAreRemoved);

            }

        }
    }
}

SCENARIO("OpenList can be updated if ExtendedNodes are changed",
         "[openlist][extendednode]") {

    GIVEN("OpenList with two ExtendedNodes in positions (2,1) and (2,2)"
          "with total costs 10.0f and 20.0f") {

        pathfinder::OpenList openList;

        pathfinder::Node node1(2,1);
        pathfinder::Node node2(2,2);

        pathfinder::ExtendedNode extNode1(&node1);
        pathfinder::ExtendedNode extNode2(&node2);

        extNode1.setTotalCost(10.0f);
        extNode2.setTotalCost(20.0f);

        openList.add(extNode1);
        openList.add(extNode2);

        WHEN("Checking best node from OpenList") {

            const pathfinder::Node bestNode = openList.getBestNode().getNode();

            THEN("Best node is the first node") {
                REQUIRE(bestNode == node1);
            }

        }

        WHEN("Changing second ExtendedNode's total cost to 5.0f and fixing"
             "open list") {

            extNode2.setTotalCost(5.0f);
            openList.fixOpenList();

            THEN("Best node from open list is the second node") {

                const pathfinder::Node bestNode = openList.getBestNode().getNode();
                REQUIRE(bestNode == node2);
            }
        }
    }

}
