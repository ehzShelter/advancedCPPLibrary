#include "./StanfordCPPLib/basicgraph.h"
#include "./StanfordCPPLib/graph.h"
#include "./StanfordCPPLib/queue.h"
#include <iostream>
#include <limits>
#include <queue>
#include <string>

enum {
    INFINITY = std::numeric_limits<int>::max()
};

enum colorValue {
    WHITE,
    GRAY,
    BLACK
};

enum DISCOVER {
    UNDISCOVERED,
    DISCOVERED,
    FINISHED
};

void levelPrint(Vertex* v)
{
    std::cout << v->name << " " << v->getLevel();
}

void BFS(BasicGraph& G, Vertex* s)
{
    for (Vertex* u : G.getNeighbors(s)) {
        u->setColor(WHITE);
        u->setLevel(INFINITY);
        u->parent = nullptr;
    }

    s->setColor(GRAY);
    s->setLevel(0);
    s->parent = nullptr;

    std::queue<Vertex*> Q;

    Q.push(s);

    while (!Q.empty()) {
        Vertex* node = Q.front();
        Q.pop();
        std::cout << node->name << "-- ";

        for (Vertex* v : G.getNeighbors(node)) {
            if (v->getColor() == WHITE) {
                v->setColor(GRAY);
                v->setLevel(node->getLevel() + 1);
                v->parent = node;
                Q.push(v);
            }
        }
        std::cout << node->getLevel() << " ";
        std::cout << std::endl;
    }
}

void testingBFS(void)
{
    BasicGraph G;
    Vertex* V1 = G.addVertex("L");
    Vertex* V2 = G.addVertex("M");
    Vertex* V3 = G.addVertex("V");
    Vertex* V4 = G.addVertex("G");
    Vertex* V5 = G.addVertex("O");
    Vertex* V6 = G.addVertex("T");

    G.addEdge(V1, V3);
    G.addEdge(V1, V2);
    G.addEdge(V2, V3);
    G.addEdge(V3, V4);
    G.addEdge(V4, V5);
    G.addEdge(V5, V6);

    std::string str = G.toString();

    std::cout << str;
    G.getEdgeSet();
    std::cout << std::endl;
    std::cout << "BFS " << std::endl;

    BFS(G, V1);
    std::cout << std::endl;
    levelPrint(V5);
    std::cout << std::endl;
}

void DFSVisit(BasicGraph& G, Vertex* u)
{
    std::cout << u->name << " ";
    // white vertex u just have been discovered
    G.timestamp = G.timestamp + 1;

    u->discoveredTimestamp = G.timestamp;
    u->setColor(GRAY);

    // explore edge(u, v)
    for (Vertex* v : G.getNeighbors(u)) {
        if (v->getColor() == WHITE) {
            v->parent = u;
            DFSVisit(G, v);
        }
    }
    // blacken u, it is FINISHED
    u->setColor(BLACK);
    G.timestamp = G.timestamp + 1;
    u->finishedTimestamp = G.timestamp;
}

void DFSVisitEdgeClassify(BasicGraph& G, Vertex* u)
{
    // remember G must be a directed Graph
    // white vertex u just have been discovered
    G.timestamp = G.timestamp + 1;

    u->discoveredTimestamp = G.timestamp;
    u->setColor(GRAY);

    // explore edge(u, v)
    for (Vertex* v : G.getNeighbors(u)) {
        if (v->getColor() == BLACK) {

            if (u->discoveredTimestamp < v->discoveredTimestamp) {
                std::cout << "forwardEdge : ";
                std::cout << u->name << " " << v->name;
                std::cout << std::endl;
            } else {

                std::cout << "crossEdge : ";
                std::cout << u->name << " " << v->name;
                std::cout << std::endl;
            }
        }

        else if (v->getColor() == GRAY) {

            std::cout << "backEdge : ";
            std::cout << u->name << " " << v->name;
            std::cout << std::endl;
        }

        else {
            v->parent = u;
            std::cout << "treeEdge : ";
            std::cout << u->name << " " << v->name;
            std::cout << std::endl;
            DFSVisitEdgeClassify(G, v);
        }
    }

    // blacken u, it is FINISHED
    u->setColor(BLACK);
    G.timestamp = G.timestamp + 1;
    u->finishedTimestamp = G.timestamp;
}

void DFS(BasicGraph& G)
{
    // iterate through the whole graph for each and every vertices
    for (Vertex* u : G.getVertexSet()) {
        u->setColor(WHITE);
        u->parent = nullptr;
    }

    G.timestamp = 0;

    for (Vertex* u : G.getVertexSet()) {
        if (u->getColor() == WHITE) {
            DFSVisit(G, u);
        }
    }
}

void dfsTraverseForClassify(BasicGraph& G)
{
    // iterate through the whole graph for each and every vertices
    for (Vertex* u : G.getVertexSet()) {
        u->setColor(WHITE);
        u->parent = nullptr;
    }

    G.timestamp = 0;

    for (Vertex* u : G.getVertexSet()) {
        if (u->getColor() == WHITE) {
            // Edge Classification
            DFSVisitEdgeClassify(G, u);
        }
    }
}

void testingDFS(BasicGraph& G)
{
    G.addVertex("u");
    G.addVertex("v");
    G.addVertex("w");
    G.addVertex("x");
    G.addVertex("y");
    G.addVertex("z");
    G.addVertex("q");
    G.addVertex("r");
    G.addVertex("s");
    G.addVertex("t");

    G.addEdge("s", "v");
    G.addEdge("v", "w");
    G.addEdge("w", "s");
    G.addEdge("q", "s");
    G.addEdge("q", "w");
    G.addEdge("q", "t");
    G.addEdge("t", "x");
    G.addEdge("x", "z");
    G.addEdge("z", "x");
    G.addEdge("t", "y");
    G.addEdge("y", "q");
    G.addEdge("r", "u");
    G.addEdge("u", "y");
    G.addEdge("r", "y");

    std::string str = G.toString();

    std::cout << str;
    std::cout << std::endl;

    std::cout << "DFS ";

    DFS(G);
    std::cout << std::endl;
    std::cout << "DFS traversal for edge Classification: " << std::endl;
    dfsTraverseForClassify(G);

    std::cout << std::endl;
}

int main(void)
{
    // DFS
    BasicGraph G;
    testingDFS(G);

    std::cout << std::endl;
    return 0;
}
