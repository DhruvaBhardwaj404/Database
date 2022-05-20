#include "Exisiting_DB.h"


using namespace std;

Exisiting_DB::Exisiting_DB(){
try{
    fstream db("Database_Info.txt",ios::in|ios::binary);
    if(db.is_open()){
        db.read((char*)this,sizeof(Exisiting_DB));
        db.close();
    }
}
catch(...){
   cout<<"[!!!]error while constructing Exisiting_DB!";
}
}

Exisiting_DB::~Exisiting_DB(){
try{
    fstream db("Database_Info.txt",ios::out|ios::binary);
    if(db.is_open()){
        db.write((char*)this,sizeof(Exisiting_DB));
        db.close();
    }
}
catch(...){
    cout<<"[!!!] Error occurred while destroying ";
}
}

int Exisiting_DB::find(string name){
 int pos=hashFun(name);
 if(Names[pos]==0){
    return 1;
 }
 else{
    return 0;
 }
}


int Exisiting_DB::add(string name){
    int pos=hashFun(name);
    if(Names[pos]==0){
        Names[pos]=1;
        numDB++;
        return 0;
    }
    else{
        return -1;
    }

}




