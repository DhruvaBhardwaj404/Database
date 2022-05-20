#include "Handler.h"

Handler::Handler(string name,unsigned int m)
{
    try{
        mode=m;
        if(m==0)
            chdir("./sql");
        else if(m==1)
            chdir("./nsql");

        fstream file("handler_info.dat",ios::in|ios::binary);
        if(file.is_open()){
            file.read((char*)this,sizeof(Handler));
            file.close();
        }
        name.resize(MAX_COL_NAME);

        if(strcmp(name.c_str(),"N-N")!=0){

            if(col_Name[hashFun(name)]==1){
               strcpy(sel_Col_Name,name.c_str());
            }
            else{
                cout<<"[!!!] No collection with specified name exist!\n";
            }
        }
    }
    catch(...){
        cout<<"[!!!] Error while creating sql object!";
        throw "";
    }

}

Handler::~Handler()
{
try{
    strcpy(sel_Col_Name,"N-N\0");
    fstream file("handler_info.dat",ios::out|ios::binary);
    if(file.is_open()){
        file.write((char*)this,sizeof(Handler));
        file.close();
    }
}
catch(...){
    cout<<"[!!!] Error while destructing Sql object!";
}
}


void Handler::use_Handler(){

 string command;
 string m=(mode==0?"sql":"nsql");

 while(true){
    vector<string> pcom;
    cout<<"Selected mode=>"<<m<<" : ";

    if(strcmp(sel_Col_Name,"N-N")!=0){
        goto_Col("N-N");
    }

    getline(cin,command);

    try{
        pcom=parse(command);
    }
    catch(...){
        cout<<"[!!!]Error while parsing!\n";
    }

    if(pcom.size()<1){
        cout<<"[!!!] Insufficient number of arguments!\n";
    }

    if(pcom.size()==1){

        if(pcom[0]=="display"){
            display_Collection();
        }
        else
            cout<<"[!!!] Too few arguments specified!\n";
    }

    if(pcom.size()>=2){

        if(pcom[0]=="use"){
            select_Collection(pcom);
        }

        else if(pcom[0]=="create"){
            create_Collection(pcom);
        }


        else if(pcom[0]=="delete"){
            delete_Collection(pcom);
        }

        else if(pcom[0]=="switch" && pcom[1]=="database")
           break;

        else
         cout<<endl<<"[!!!]Command not recognised!\n";
    }
  }
}



void  Handler::select_Collection(const vector<string> &pcom){
try{
    if(col_Name[hashFun(pcom[1])]==1){
        if(pcom.size()==3){
            strcpy(sel_Col_Name,pcom[1].c_str());
            goto_Col(pcom[2]);
        }
        else if(pcom.size()==2){
            strcpy(sel_Col_Name,pcom[1].c_str());
            goto_Col("N-N");

        }
    }
    else{
        cout<<"[!!!]No collection with the specified name exist!\n";
    }
}catch(...){
    cout<<"[!!!] Error in select_Collections!\n";
}
}


void  Handler::create_Collection(const vector<string> &pcom){

    if(col_Name[hashFun(pcom[1])]==1){
        cout<<"[!!!] Collection with given name exist!\n";
        return ;
    }
    else{
        col_Name[hashFun(pcom[1])]=1;
    }

    try{
        string command="mkdir "+pcom[1];
        system(command.c_str());
        strcpy(sel_Col_Name,pcom[1].c_str());
        goto_Col("New");
    }
    catch(...){
        cout<<"Error while creating the collection\n";
    }
}


void  Handler::delete_Collection(const vector<string> &pcom){
;
}

void  Handler::display_Collection(){
;
}

void Handler::goto_Col(string tab){
try{
    if(strcmp(sel_Col_Name,"N-N")!=0){
        chdir(("./"+string(sel_Col_Name)).c_str());

        if(strcmp(tab.c_str(),"New")==0){
            try{
                col=new Col_Handler(sel_Col_Name,mode);
            }
            catch(...){
                string command="rm -r "+tab;
                chdir("../");
                system(command.c_str());
                return;
            }
        }

        else if(strcmp(tab.c_str(),"N-N")==0)
            col=new Col_Handler("N-N");

        else
            col=new Col_Handler(tab);

        col->use_Col();
        delete col;
        strcpy(sel_Col_Name,"N-N\0");
        chdir("../");

    }

    else{
        cout<<"[!!!]No collection selected!\n";
    }
}
catch(...){
    cout<<"[!!!]Error in goto_Col!\n";
}
}




