#include "SQL_TabHandler.h"

SQL_TabHandler::SQL_TabHandler()
{
    fstream file("table_info.dat",ios::in|ios::binary);
    if(file.is_open()){
        file.read((char*)this,sizeof(SQL_TabHandler));
        file.close();
    }
    Table=new tableInfo();
    Table->map_DataTypes(col_Names,col_Type,var_Col_Size,NC);
    Table->tableData.clear();
}


SQL_TabHandler::SQL_TabHandler(vps columns,string name){
    try{
        string log=validate_Types(columns);
        if(log.size()>2)
        {
            cout<<log;
            throw "Error in Constructor";
        }
    }
    catch(...){
        cout<<"[!!!]Error in validating\n";
        throw " ";
    }
    name.resize(MAX_SIZE_NAME);
    strcpy(Name,name.c_str());
    unsigned int i=0,j=0;
    if(columns.size()<=MAX_COL){
        NC=columns.size();

        for(auto col:columns){

            col.first.resize(20);
            strcpy(col_Names[i],col.first.c_str());
            col_Type[i]=int(col.second[0])-48;

            if(col.second.size()>1){
                if(col.second[1]=='s'){
                    strcpy(var_Col[j],col.first.c_str());
                    var_Col_Size[j]=stoi(string(col.second.begin()+2,col.second.end()));
                    j++;
                }
                else if(col.second[1]=='o'){
                //not done
                }
            }

            i++;

        }
    }

    fstream file("table_info.dat",ios::out|ios::binary);
    if(file.is_open()){
        file.write((char*)this,sizeof(SQL_TabHandler));
        file.close();
    }
        Table=new tableInfo();
        Table->map_DataTypes(col_Names,col_Type,var_Col_Size,NC);
        Table->tableData.clear();
        //Table->print_columns(col_Names,NC);

}


SQL_TabHandler::~SQL_TabHandler(){
    fstream file("table_info.dat",ios::out|ios::binary);
    delete Table;
    if(file.is_open()){
        file.write((char*)this,sizeof(SQL_TabHandler));
        file.close();
    }

}


void SQL_TabHandler::use_tabHandler(){
 string command;

 while(true){
    vector<string> pcom;
    cout<<"In "<<Name<<"=> ";
    getline(cin,command);
    pcom=parse(command);

    if(pcom.size()>=1){
        if(pcom[0]=="use"){
            //select_Column("");
        }

        else if(pcom[0]=="create"){
            //create_Column(pcom);
        }
        else if(pcom[0]=="insert"){
            insert_Data(command);
        }

        else if(pcom[0]=="display"){
            display_Table();
        }

        else if(pcom[0]=="delete"){
            //delete_Table();
        }
        else if(pcom[0]=="info"){
            col_Info();
        }

        else if(pcom[0]=="found"){

        }

        else if(pcom.size()==2)
            if(pcom[0]=="switch" && pcom[1]=="database")
                break;
        else
            cout<<endl<<"[!!!]Command not recognised!\n"<<endl;
    }
    else
        cout<<endl<<"[!!!]Command not recognised!\n"<<endl;


 }


}

void SQL_TabHandler::col_Info(){
    cout<<endl<<"Name of Table :"<<Name<<"\nNumber of Pages=>"<<NP<<"\nNumber of Columns=>"<<NC<<"\nNumber of Records=>"<<NR<<endl;
    cout<<"Col names\n";
    for(int i=0;i<NC;i++){
        cout<<col_Names[i]<<" | ";
    }
    cout<<endl;
}


void SQL_TabHandler::insert_Data(const string &pcom){
try{

 vector<vector<pair<string,string> > > data=parseInsert(pcom);
 vector<vector<string> > vData=validate_Data(data);

    int file_pos=0,r_cols=vData[0].size(),w_cols=0,s,e,s_cols=0,col_bSize,tempNR=NR;
    string fname;
    fstream file;

    while(r_cols>0){

        s=w_cols==0?0:w_cols;
       if(tempNR%MAX_RPP==0 || tempNR==0){
         NP++;
         if(file.is_open())
            file.close();

         if(r_cols<=MAX_RPP){
            e=s+r_cols;
         }
         else{
            e=s+MAX_RPP;
         }
       }

       else {
        if(((tempNR%MAX_RPP)+r_cols)<=MAX_RPP){
            e=s+r_cols;
        }
        else{
            e=s+(MAX_RPP-(tempNR%MAX_RPP));
        }
       }



        //cout<<"\n file_pos= "<<file_pos<<" r_cols="<<r_cols<<"  w_cols="<<w_cols<<" s= "<<s<<"  e= "<<e<<endl;

        if(!file.is_open()){
            fname="td-"+to_string(NP)+".dat";
            file.open(fname,ios::in | ios::out);
        }

        if(!file.is_open()){
            file.open(fname,ios::out);
        }
        s_cols=0;


        for(unsigned int i=0;i<NC;i++){
          if(col_Type[i]<=4)
            col_bSize=Table->fsize[col_Type[i]];
          else{
            col_bSize=Table->columns[col_Names[i]].second;
            //cout<<"here1";
        }

          if((tempNR)%MAX_RPP!=0)
            file_pos=s_cols+col_bSize*((tempNR)%MAX_RPP);
          else
            file_pos=0+s_cols;

          //cout<<"\n filepos= "<<file_pos<<" col BSIZE= "<<col_bSize<<" col-type"<<col_Type[i]<<endl;

            switch(col_Type[i]){
                case 0: write_To_File<int >(write_Type_Con<int>(vData[i],col_Type[i]),file,file_pos,s,e);
                    break;
                case 1: write_To_File<long long>(write_Type_Con<long long>(vData[i],col_Type[i]),file,file_pos,s,e);
                    break;
                case 2: write_To_File<double>(write_Type_Con<double>(vData[i],col_Type[i]),file,file_pos,s,e);
                    break;
                case 3: write_To_File<float>(write_Type_Con<float>(vData[i],col_Type[i]),file,file_pos,s,e);
                    break;
                case 4: write_To_File<char>(write_Type_Con<char>(vData[i],col_Type[i]),file,file_pos,s,e);
                    break;
                case 5: write_To_File(write_Type_Con(vData[i],col_Type[i]),file,file_pos,s,e,col_bSize);
                    break;
            }
          s_cols+=col_bSize*MAX_RPP;
        }

       w_cols=e;
       r_cols=vData[0].size() - w_cols;
       tempNR=NR+w_cols;

       //cout<<"\n file_pos= "<<file_pos<<" r_cols="<<r_cols<<"  w_cols="<<w_cols<<" s= "<<s<<"  e= "<<e<<endl;
    }
    NR=tempNR;
    file.close();

}
catch(...){
    cout<<"[!!!]Unable to complete insert operation!\n";
    }
}

void SQL_TabHandler::select_Column(string name){
;
}

void SQL_TabHandler::create_Column(vector<string> pcom){
;
}

void SQL_TabHandler::find_in_Table(){
;
}

void SQL_TabHandler::display_Table(){
try{
    start:
    if(Table->tableData.size()!=0){
      for(auto x: Table->tableData){
        for(auto y: x){
            cout<<y<<" ";
        }
        cout<<endl;
      }
    }
    else{
        load_Tab_Data();
        goto start;
       // cout<<"\nSize=>"<<Table->tableData.size()<<endl;
     }
    }
catch(...){
    cout<<"error while loading\n";
}
}

void SQL_TabHandler::delete_Table(){
;
}


void SQL_TabHandler::load_Tab_Data(){
    fstream file;

    for(unsigned int j=1;j<=NP;j++){

        string fname="td-"+to_string(j)+".dat";
        file.open(fname,ios::in| ios::out);
        unsigned file_pos=0;
        //cout<<"\n"<<fname<<"\n";

        for(unsigned int i=0;i<NC;i++){
            //cout<<"\nfile_pos"<<file_pos<<" i="<<i<<" j="<<j<<endl;

            switch(col_Type[i]){
                case 0: read_From_File<int>(file,file_pos,j,i); break;
                case 1: read_From_File<long long>(file,file_pos,j,i); break;
                case 2: read_From_File<float>(file,file_pos,j,i); break;
                case 3: read_From_File<double>(file,file_pos,j,i); break;
                case 4: read_From_File<char>(file,file_pos,j,i); break ;
                case 5: read_From_File(file,file_pos,j,i,Table->columns[col_Names[i]].second); break ;
            }

        if(col_Type[i]<=4)
            file_pos+=Table->fsize[col_Type[i]]*MAX_RPP;
        else{
            file_pos+=(Table->columns[col_Names[i]].second)*MAX_RPP;
            }
        }
    file.close();
    }
}


template<typename T>
void SQL_TabHandler::read_From_File(fstream &f,unsigned int file_pos,unsigned int page,unsigned int col){

    //cout<<endl<<"file_pos: "<<file_pos<<" page:"<<page<<" col:"<<col<<endl;
    vector<T> data;
    unsigned int s;
    if(page==NP)
        s=NR%MAX_RPP;
    else
        s=MAX_RPP;

    T d;
    f.seekg(file_pos);
    //cout<<"\n s="<<s<<" "<<f.tellg()<<" tellg\n";

    for(unsigned int i=0;i<s;i++){
        f.read((char*)&d,sizeof(d));
        data.push_back(d);
        //cout<<d<<" ";
    }

   Table->tableData.push_back({});
   if(col_Type[col]==4)
        for(const char x:data){
            //cout<<x<<" "<<to_string(x);
            Table->tableData[col].push_back(string(&x,1));
        }

    else
        for(auto x:data){
            //cout<<"pushing data in col "<<col<<" "<<to_string(x)<<" ";
            Table->tableData[col].push_back(to_string(x));
        }
  // cout<<"col size "<<Table->tableData[col].size()<<endl;

}



vector<vector<string> > SQL_TabHandler::validate_Data(vector<vector<pair<string,string> > > d){
    vector<vector<string> > vdata;
    map<string,vector<string> > data;

    for(int i=0;i<NC;i++){
        data.insert({col_Names[i],{}});
    }

    bool tres;
    for(auto elm : d){
        for(auto field : elm){
            try{
              //cout<<endl<<field.second<<" in validate types "<<Table->columns[field.first]<<endl;
              tres=type_Checker(field.second,Table->columns[field.first]);

              if(tres==true){
                data.at(field.first).push_back(field.second);
              }
              else{
                return {};
              }
            }
            catch(...){
                cout<<"[!!!] Statement "<<field.first<<" : "<<field.second<<" is not of the correct format!\n";
                throw ;
            }
        }
    }

    for(unsigned int i=0;i<NC;i++){
        vdata.push_back(data[col_Names[i]]);
    }

    return vdata;
}


template<typename T>
bool SQL_TabHandler::write_To_File(vector<T> data,fstream &f,unsigned int file_pos,unsigned int s,unsigned int e){
    //cout<<"in write to file generic\n";
    f.seekp(file_pos);
    if(e>data.size())
        throw "error";
    //cout<<"\nsize- "<<data.size()<<" file_pos= "<<file_pos<<" s="<<s<<" e="<<e<<"\n";
    while(s<e){
        //cout<<data[s]<<" - ";
        //cout<<"\n tellp in write to file"<<f.tellp()<<"\n";
        f.write((char*)&data[s],sizeof(T));
        s++;
    }
}

template <typename T>
vector<T> SQL_TabHandler::write_Type_Con(vector<string> values,unsigned int type){
    function<T(string)> func;

    switch(type){
        case 0:func=[](string a){ return stoi(a);    }; break;
        case 1:func=[](string a){ return stoll(a);   }; break;
        case 2:func=[](string a){ return stof(a);    }; break;
        case 3:func=[](string a){ return stod(a);    }; break;
        case 4:func=[](string a){ return char(a[0]); }; break;
    }

    vector<T> data;
   for(auto x:values){
        data.push_back(func(x));
    }
    return data;

}


bool SQL_TabHandler::write_To_File(vector<string> data,fstream &f,unsigned int file_pos,unsigned int s,unsigned int e,unsigned int size){
    //cout<<"in write to file \n";
    //cout<<"\nsize- "<<data.size()<<" file_pos= "<<file_pos<<" s="<<s<<" e="<<e<<"\n";

    f.seekp(file_pos);

    if(e>data.size())
        throw "error";


    char d[size];
    while(s<e){
        cout<<data[s]<<endl;
        strcpy(d,data[s].c_str());
        cout<<d<<endl;
        f.write((char*)&d,size);
        s++;
    }
}

vector<string> SQL_TabHandler::write_Type_Con(vector<string> values,unsigned int type){
    vector<string> data;
   for(auto x:values){
        data.push_back(x);
        //cout<<" x "<<x<<"\n";
    }
    return data;
}


void SQL_TabHandler::read_From_File(fstream &f,unsigned int file_pos,unsigned int page,unsigned int col,unsigned int size){

    //cout<<endl<<"file_pos: "<<file_pos<<" page:"<<page<<" col:"<<col<<endl;
    vector<string> data;
    unsigned int s;

    if(page==NP)
        s=NR%MAX_RPP;
    else
        s=MAX_RPP;


    char d[size];
    f.seekg(file_pos);

    //cout<<"\n s="<<s<<" | "<<f.tellg()<<" tellg\n";

    for(unsigned int i=0;i<s;i++){
        f.read((char*)&d,size);
        data.push_back(d);
        cout<<d<<" ";
    }

   Table->tableData.push_back({});


    for(auto x:data){
        //cout<<"pushing data in col "<<col<<" "<<x<<" ";
        Table->tableData[col].push_back(x);
    }

   //cout<<"col size "<<Table->tableData[col].size()<<endl;

}
