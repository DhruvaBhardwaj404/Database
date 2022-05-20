#include "Database.h"




Database::Database(string n)
{
    n.resize(20);
    string command,check;
    strcpy(name,n.c_str());
    command="mkdir ";
    command+=name;
       try{
         system(command.c_str());
         command="./";
         command+=name;
         chdir(command.c_str());
         system("mkdir nsql sql");
         fstream file("db_info.dat", ios::out | ios::binary);
         file.write((char*)this,sizeof(Database));
         file.close();
       }
       catch(...){
         cout<<"Error occurred while constructing Database object\n";
       }
}

Database::Database(){
    try{
        fstream file("db_info.dat",ios::in| ios::binary);
        if(file.is_open()){
            file.read((char*)this,sizeof(Database));
            file.close();
        }
        else{
            cout<<"Error occurred while creating Database object!\n";
            throw;
        }
    }
    catch(...){
        cout<<"[!!!] Error in constructing Database object\n";
    }
}

Database::~Database(){
    try{
        fstream file("db_info.dat",ios::out| ios::binary );
        file.write((char*)this,sizeof(Database));
        file.close();
        //system("pwd");
    }
    catch(...){
        cout<<"[!!!] Error in constructing Database object\n";
    }
}


void Database::use_DB(){
 string command;
 cout<<"Selected Database=>"<<name<<endl;

 while(true){
    vector<string> pcom;
    cout<<"DB:"<<Database::name<<": ";
    getline(cin,command);
    try{
        pcom=parse(command);
    }
    catch(...){
        cout<<"Error while parsing\n";
        continue;
    }

    if(pcom.size()<1){
        cout<<"[!!!] Insufficient arguments!\n";
        continue;
    }

     if(pcom[0]=="use"){

        if(pcom.size()==3 && (pcom[1]=="nsql" || pcom[1]=="sql" )){

                goto_Handler(pcom[1],pcom[2]);
        }
        else if(pcom.size()==2 && (pcom[1]=="nsql" || pcom[1]=="sql") ){

                goto_Handler(pcom[1],"N-N");
        }
        else{
            cout<<"[!!!] Command not recognized!\n";
        }
    }

    if(pcom.size()==2){
        if(pcom[0]=="switch" && pcom[1]=="database")
            break;
    }

    else
     cout<<endl<<"[!!!] Command not recognised!\n";

 }
}


void Database::goto_Handler(const string &mode,string name){
try{
    if(mode=="sql")
        col= new Handler(name,0);

    else
        col= new Handler(name,1);

    col->use_Handler();
    delete col;
    chdir("../");
}
catch(...){
    cout<<"[!!!] Error in database::createSQL\n";
}
}

/*
bool Database::find(string name,int mode){
try{
    int pos=hashFun(name);
    if(mode==0){
        if(SQLColSchema[pos]==0)
            return -1;
        else
            return 0;
    }
    else{
        if(NSQLColSchema[pos]==0)
            return -1;
        else
            return 0;
    }
}
catch(...){
    cout<<"error in database::find";
}
return 0;
}
*/
