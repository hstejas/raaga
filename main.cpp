#include "Raaga.h"


int main(int argc, char** argv)
{
    Raaga raaga(argc, &argv);
    if(raaga.loadList())
        raaga.run();
}