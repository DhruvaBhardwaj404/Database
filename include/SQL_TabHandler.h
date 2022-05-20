#ifndef SQL_TABHANDLER_H
#define SQL_TABHANDLER_H

#include"tableInfo.h"
#include"functionsDB.h"
#include"paramDefinitions.h"
#define vps vector<pair<string,string> >
#define vs vector<string>

using namespace std;
using namespace functionsDB;

class SQL_TabHandler
{
    public:
        SQL_TabHandler();
        SQL_TabHandler(vps columns,string name);
        void use_tabHandler();
        void select_Column(string name);
        void create_Column(vector<string> name);
        void insert_Data(const string &pcom);
        void find_in_Table();
        void display_Table();
        void delete_Table();
        void load_Tab_Data();
        void col_Info();

        vector<vector<string> >  validate_Data(vector< vector<pair<string,string> > > d);
        bool write_To_File(vector<string> data,fstream &f,unsigned int file_pos,unsigned int s,unsigned int e,unsigned int size);
        void read_From_File(fstream &f,unsigned int file_pos,unsigned int page,unsigned int col,unsigned int size);

        template<typename T>
            void read_From_File(fstream &f,unsigned int file_pos,unsigned int page,unsigned int col);
        template<typename T>
            bool write_To_File(vector<T> data,fstream &f,unsigned int file_pos,unsigned int s,unsigned int e);

        template <typename T>
            vector<T> write_Type_Con(vector<string> values,unsigned int type);

        vector<string> write_Type_Con(vector<string> values,unsigned int type);
        virtual ~SQL_TabHandler();
    private:
        tableInfo *Table;
        unsigned int RPP=MAX_RPP,  NP=0,  NR=0,  NC=0 ,PK=0;    //records per page, number of pages,number of records,number of cols,page size
        char Name[MAX_SIZE_NAME],col_Names[MAX_COL][MAX_COL_NAME_SIZE],var_Col[MAX_COL][MAX_COL_NAME_SIZE];
        unsigned int col_Type[MAX_COL],var_Col_Size[MAX_COL];
};

#endif // SQL_TABHANDLER_H
