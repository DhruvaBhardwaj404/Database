#include "Col_Handler.h"


using namespace std;

Col_Handler::Col_Handler(string tab_name)
{
    fstream file("col_info.dat",ios::in|ios::binary);
    if(file.is_open()){
        file.read((char*)this,sizeof(Col_Handler));
        file.close();
    }

    if(strcmp(tab_name.c_str(),"N-N")!=0){
        tab_name.resize(MAX_TAB_NAME);
        if(tab_Name[hashFun(tab_name)]==1){
            strcpy(sel_Tab,tab_name.c_str());
            sel=true;
        }
        else{
            cout<<"[!!!] Table with specified does not exist!";
        }
    }
}


Col_Handler::Col_Handler(string col_name,unsigned int m)
{
    col_name.resize(MAX_COL_NAME);
    strcpy(Name,col_name.c_str());
    mode=m;
    fstream file("col_info.dat",ios::out|ios::binary);
    if(file.is_open()){
        file.write((char*)this,sizeof(Col_Handler));
        file.close();
    }
}

Col_Handler::~Col_Handler()
{
try{
    strcpy(sel_Tab,"N-N\0");
    fstream file("col_info.dat",ios::out|ios::binary);
    if(file.is_open()){
        file.write((char*)this,sizeof(Col_Handler));
        file.close();
    }
}
catch(...){
    cout<<"Error while destructing Col_Handler object!\n";
}
}

void Col_Handler::use_Col(){
 string command;
 vector<string> pcom;

 while(true){
    vector<string> pcom;
    cout<<"In "<<Name<<" =>";

    if(strcmp(sel_Tab,"N-N")!=0){
        goto_Tab(sel_Tab);
    }

    getline(cin,command);
    pcom=parse(command);
    if(pcom.size()<1){
        cout<<"[!!!] Insufficient number of arguments!\n";
    }
    if(pcom.size()==1){
        if(pcom[0]=="display"){
        //    display_Table();
        }
        else
         cout<<endl<<"[!!!]Command not recognised!\n";
    }
    else if(pcom.size()==2){
        if(pcom[0]=="use"){
            select_Table(pcom[1]);
        }

        else if(pcom[0]=="delete"){
        //     delete_Table();
        }

        else if(pcom[0]=="switch" && pcom[1]=="database"){
            break;
        }
        if(pcom[0]=="create" && mode==1){
            create_Table({},pcom[1]);
        }
        else
         cout<<endl<<"[!!!]Command not recognised!\n";
    }

    else if(pcom.size()==3){
        if(pcom[0]=="create"){
            create_Table(command,pcom[1]);
        }
        else
         cout<<endl<<"[!!!]Command not recognised!\n";
    }
  }
}


void Col_Handler::select_Table(const string &name){
try{
    if(tab_Name[hashFun(name)]==1){
        string command="./"+name;
        chdir(command.c_str());
        if(mode==0){
            stab= new SQL_TabHandler();
            stab->use_tabHandler();
            delete stab;
        }
        else{
            ntab= new NSQL_TabHandler();
            ntab->use_tabHandler();
            delete ntab;
        }
          strcpy(sel_Tab,"N-N");
          chdir("../");
    }
    else{
        cout<<"[!!!] Table with specified Name doesn't exist!\n";
    }
}
catch(...){
    cout<<"[!!!] Error in Select Table\n!";
}
}

void Col_Handler::create_Table(const string &com,const string &name){
try{
    if(tab_Name[hashFun(name)]==0){
        string command = "mkdir ./";
        command+=name;
        system(command.c_str());
        command="./"+name;
        chdir(command.c_str());

        try{
            if(mode==0){
                auto dat=parseData(com);
                stab= new SQL_TabHandler(dat.second,name);
                delete stab;
            }
            else{
                ntab= new NSQL_TabHandler(name);
                delete ntab;
            }
        }
        catch(...){
                //cout<<"here in destruction!";
                command="rm -r "+name;
                chdir("../");
                system(command.c_str());
                return;
            }

            chdir("../");
            tab_Name[hashFun(name)]=1;
    }
    else{
        cout<<"[!!!] Table with the given name already exist!\n";
    }
}
catch(...){
    cout<<"[!!!] Error in create_Table!\n";
}
}

void Col_Handler::delete_Table(const string &name){
;
}

void Col_Handler::display_Table(const string &name){
;
}

void Col_Handler::goto_Tab(const string &name){
;
}
