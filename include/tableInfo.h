#ifndef TABLEINFO_H
#define TABLEINFO_H

#include "paramDefinitions.h"

using namespace std;

class tableInfo
{
    public:
         //string name;
         unsigned int fsize[5]={4,8,4,8,1};
         unsigned int NRT=0; // number of records read in tableData
         map<string,pair<unsigned int,unsigned int> > columns;
         void map_DataTypes(char col_Names[100][20],unsigned int col_Type[],unsigned int var_Col_size[],unsigned int &NC);
         vector<vector<string> > tableData;
         void print_columns(char col_Names[100][20],unsigned int NC);
};

#endif // TABLEINFO_H
