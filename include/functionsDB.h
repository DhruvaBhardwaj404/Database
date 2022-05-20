#ifndef FUNCTIONSDB_H
#define FUNCTIONSDB_H

#include<paramDefinitions.h>

#define vs vector<string>
#define vps vector<pair<string,string> >


using namespace std;

namespace functionsDB{
    static char type_name[TYPE_SIZE][20]={"INT","LONG LONG","FLOAT","DOUBLE","CHAR","STRING","OBJECT"};
    static unsigned int type_size[TYPE_SIZE]={2,8,4,8,1,0,0};

    struct nextChunk{
        unsigned int ctype:2;
        unsigned int cnum:7;
        unsigned int pos:7;
    };

    struct headChunk{
        unsigned int chunkNum:8;
    };

    struct NSQL_Cinfo{
        int file_pos=0,start=0,s=0,e=0,
            last=-1,lmode=0,mode=-1,
            r_rec=0,w_rec=0,lfile_pos=-1;

        fstream *sfile,*bfile;
    };

    vs parse(const string &command);
    vps parse(string::iterator start,string::iterator end);
    pair<vs,vps > parseData(const string &command);
    vector<vector<pair<string,string> > > parseInsert(const string &command);
    string padding_Remover(string data);
    string validate_Types(vps &cols,bool mode=false) ;
    bool type_Checker(string value,pair<unsigned int,unsigned int>  type,bool mode=0);
    int type_Eval(string value);
    int hashFun(string name);
}

#endif // FUNCTIONSDB_H
