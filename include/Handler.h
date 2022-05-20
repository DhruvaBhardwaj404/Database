#ifndef HANDLER_H
#define HANDLER_H

#include "functionsDB.h"
#include "Col_Handler.h"
#include "functionsDB.h"
#include "paramDefinitions.h"

using namespace std;

class Handler
{
    public:
        Handler(string name,unsigned int mode);
        void use_Handler();
        void select_Collection(const vector<string> &pcom);
        void create_Collection(const vector<string> &pcom);
        void delete_Collection(const vector<string> &pcom);
        void display_Collection();
        void goto_Col(string name);
        virtual ~Handler();
    private:
        bitset<HASH_SIZE> col_Name;
        bool col_Selected=false;
        unsigned int mode;
        Col_Handler *col;
        char sel_Col_Name[MAX_COL_NAME]="N-N";
};

#endif // HANDLER_H
