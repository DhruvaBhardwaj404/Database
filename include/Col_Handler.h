#ifndef COL_HANDLER_H
#define COL_HANDLER_H

#include"functionsDB.h"
#include"SQL_TabHandler.h"
#include"NSQL_TabHandler.h"

using namespace std;
using namespace functionsDB;

class Col_Handler
{
    public:
        Col_Handler(string tab_name);
        Col_Handler(string col_Name,unsigned int m);
        void use_Col();
        void select_Table(const string &name);
        void create_Table(const string &pcom,const string &name);
        void delete_Table(const string &name);
        void display_Table(const string &name);
        void goto_Tab(const string &name);
        ~Col_Handler();

    private:
        char Name[MAX_COL_NAME];
        bitset<HASH_SIZE> tab_Name;
        bool sel=false;
        unsigned int mode;
        NSQL_TabHandler *ntab;
        SQL_TabHandler *stab;
        char sel_Tab[MAX_TAB_NAME]="N-N";
};

#endif // COL_HANDLER_H
