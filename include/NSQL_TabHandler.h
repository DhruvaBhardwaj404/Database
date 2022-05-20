#ifndef NSQL_TABHANDLER_H
#define NSQL_TABHANDLER_H

#include"tableInfoNSQL.h"
#include"functionsDB.h"
#include"paramDefinitions.h"
#define vps vector<pair<string,string> >
#define vs vector<string>

using namespace std;
using namespace functionsDB;

class NSQL_TabHandler
{
   public:

        NSQL_TabHandler();
        NSQL_TabHandler(string name);
        void use_tabHandler();
        void select_Column(string name);
        void create_Column(vector<string> name);
        void insert_Data(const string &pcom);
        void find_in_Table();
        void display_Table();
        void delete_Table();
        void load_Tab_Data();
        void col_Info();
        void attr_Updater(vector<pair<pair<string,int>,int> > &);
        void validate_Data(vector< vector<pair<string,string> > > &d);
        void get_File_pos(NSQL_Cinfo *info,int &numRec,int &numChunks,int chunkSize);
        bool write_To_File(const vector<vector<pair<string,string> > > &data,fstream &f,NSQL_Cinfo *info);
        void read_From_File(fstream &f,unsigned int file_pos,unsigned int page,unsigned int col,unsigned int size);
        void write_To_Chunks(string &temp, NSQL_Cinfo *info,int chunk_size,int chunkNum,int m);
        string write_Type_Con(const vector<pair<string,string> > &values);
        string con_To_String(const string &dat,int type);

       // template<typename T>
        //    void read_From_File(fstream &f,unsigned int file_pos,unsigned int page,unsigned int col);
       // template<typename T>
        //    bool write_To_File(vector<T> data,fstream &f,unsigned int file_pos,unsigned int s,unsigned int e);




        virtual ~NSQL_TabHandler();
    private:
        tableInfoNSQL *Table;
        unsigned int MFC=MAX_CHUNCKS,  NPP=0,NR=0,NRS=0,NRB=0,NA=0,PK=0, //storage block size, number of pages of pointers,number of records,number of attributes,page size
                     NFC=0,NSC=0,NBC=0, //number of first chunks, small chunks, large chunks
                     SFC=SIZE_FCHUNCKS, SSC=SIZE_SMALL_CHUNKS, SBC=SIZE_BIG_CHUNKS;

        char Name[MAX_SIZE_NAME];//col_Attr[MAX_ATTR][MAX_COL_NAME_SIZE];
        //unsigned int attr_Type[MAX_ATTR];

};

#endif // NSQL_TABHANDLER_H
