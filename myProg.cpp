#include "./StanfordCPPLib/graph.h"
#include "./StanfordCPPLib/basicgraph.h"
#include <iostream>

int main(void)
{
    BasicGraph G;
    Vertex* V1 = G.addVertex("L");
    Vertex* V2 = G.addVertex("M");

    V1->setColor(1);
    std::cout << V1->getColor();
    std::cout << *V1;
    std::cout << std::endl;
    std::cout << *V2;
    return 0;
}
