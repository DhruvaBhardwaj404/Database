#include <iostream>
#include<string>
#include<cstdlib>
#include<new>
#include<fstream>
#include<unistd.h>
#include"functionsDB.h"
#include"Exisiting_DB.h"
#include"Database.h"
#include<syscall.h>

using namespace std;
using namespace functionsDB;

int main()
{
try{
 string command;
 chdir("../data");
 Exisiting_DB DB_info;   // Contains Info about existing databases
 vector<string> pcom;

 Database *DB;


 //==========display banner=============================================

 char banner[6][50]={{"|==============================================|"},
                     {"|                 DBMS 1.0                     |"},
                     {"|                   KOSH                       |"},
                     {"|                created by-                   |"},
                     {"|                  Dhruva                      |"},
                     {"|==============================================|"}};
  for(int a=0;a<6;a++){
    cout<<"\t\t\t"<<banner[a]<<endl;
  }
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  fstream db;

  do{

   cout.flush();
   cout<<endl<<"=> ";
   getline(cin,command);
   pcom=parse(command);

   if(pcom[0]=="exit"){
        break;
     }

   if(pcom.size()<2){
        cout<<"[!!!]Insufficient arguments!";
        continue;
   }

   if(pcom.size()==3){
      if(pcom[0]=="create" && pcom[1]=="database"){

          if(DB_info.find(pcom[2])==0){
            cout<<endl<<"[!!!] Database with the same name exist!!"<<endl;
          }

          else{
                DB_info.add(pcom[2]);
                DB=new Database(pcom[2]);
                DB->use_DB();
                delete DB;
                chdir("../");
            }
        }
    }
    else if(pcom.size()==2){
      if(pcom[0]=="use"){
          if(DB_info.find(pcom[1])==0){
            string loc="./"+pcom[1];
            chdir(loc.c_str());
            DB=new Database();
            DB->use_DB();
            chdir("../");

          }
          else{
            cout<<"[!!!] No database with specified name exist!";
          }
      }
    }
     else if(pcom[0]!="exit"){
        cout<<endl<<"[!!!]Command not recognised!"<<endl;
     }

    db.open("Database_Info.txt",ios::out|ios::binary);
    if(db.is_open()){
        db.write((char*)&DB_info,sizeof(DB_info));
        db.close();
    }
    else{
        cout<<"[!!!]Couldn't update Database_Info.txt!";
        exit(0);
    }

  }
   while(command!="exit");
    db.close();
}
catch(...){
    cout<<"[!!!]error occurred in main()!";
}
}
