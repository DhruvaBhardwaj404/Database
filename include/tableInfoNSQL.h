#ifndef TABLEINFONSQL_H
#define TABLEINFONSQL_H

#include"functionsDB.h"
#include"paramDefinitions.h"

using namespace std;
using functionsDB::NSQL_Cinfo;
using functionsDB::headChunk;
using functionsDB::nextChunk;

class tableInfoNSQL
{
    public:
        vector<pair<string,int> > attr_List,new_Attr;
        map<string,vector<string> > Data;
        vector<vector<pair<string,string> > > record_Data;
        vector<int> keys,new_Keys;
        void make_Attr_List(fstream &afile,fstream &kfile,int NA);
        int search_Key(int value);
        void sort_key(int size);
        void print_info(NSQL_Cinfo *info);
        void print_attr_list();
        void get_data(fstream &fchunk);
        void format_data(string data);

};

#endif // TABLEINFONSQL_H
