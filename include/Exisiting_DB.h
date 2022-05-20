#ifndef EXISITING_DB_H
#define EXISITING_DB_H

#include"functionsDB.h"
#include"paramDefinitions.h"

using namespace std;
using namespace functionsDB;

class Exisiting_DB
{
    public:
        Exisiting_DB();
        ~Exisiting_DB();
        int numDB=0;
        bitset<HASH_SIZE> Names;
        int find(string name);
        int add(string name);

};

#endif // EXISITING_DB_H
