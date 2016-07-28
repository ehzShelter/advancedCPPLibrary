#include "./StanfordCPPLib/basicgraph.h"
#include "./StanfordCPPLib/graph.h"
#include "./StanfordCPPLib/queue.h"
#include <iostream>
#include <limits>
#include <queue>

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

int main(void)
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
    // G.getEdgeSet();
    std::cout << std::endl;
    std::cout << "BFS " << std::endl;

    BFS(G, V1);
    std::cout << std::endl;
    levelPrint(V5);
    std::cout << std::endl;
    return 0;
}
