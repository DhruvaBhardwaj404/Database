#include "functionsDB.h"


using namespace std;


string functionsDB::padding_Remover( string data){
    string s;
    auto it=data.begin();
    for(auto &x:data){
        if(x!=' '){
            s=string(it,data.end());
            break;
        }
        it++;
    }

    int y=0;
    for(auto x=data.rbegin();x!=data.rend();x++){
        if(*x!=' '){
            s.resize(s.size()-y);
            break;
        }
        y++;
    }

    return s;
}


vs functionsDB::parse(const string &command){

	vs parsed;
	string word;
	int length=command.size();

	for(int a=0;a<length+1;a++){
		if(command[a]==' ' || a==length){
			parsed.push_back(word);
		    word.clear();
		}
		else{
			word.push_back(command[a]);
		}

	}
	 return parsed;

}


vps functionsDB::parse(auto start,auto end){
    vps parsed;
    string command(start,end),col,dat;
    int size=command.size();
   // auto it=command.begin();
    string temp;

    for(int i=1;i<size;i++){
       if(command[i]!='{' && command[i]!=',' && command[i]!='}' && command[i]!=':'){
            temp+=command[i];
        }
        else if(command[i]==':'){
           col=padding_Remover(temp);
           temp.clear();


        }
        else if(command[i]==',' || command[i]=='}'){

            dat = padding_Remover(temp);
            temp.clear();

            if(col.size()>0 && dat.size()>0){
                parsed.push_back({col,dat});
                col.clear();
                dat.clear();
            }

            if(command[i]=='}'){
                break;
            }
        }

    }

 return parsed;
}



pair<vs,vps > functionsDB::parseData(const string &command){
try{
    pair<vs,vps > parsed;
    auto s=command.begin(),e=command.end();

    for(auto x:command){
        if(x=='{'){
            parsed.first= parse(string(command.begin(),s));
            parsed.second= parse(s,e);
        }
        s++;
    }

      //  for( auto y:parsed.second){
    //        cout<<y.first<<" "<<y.second<<" \n";
  //  }

    return parsed;
}
catch(...){
    cout<<"[!!!]error while parsing Data!\n";
}
return {};
}

vector<vector<pair<string,string> > > functionsDB::parseInsert(const string &command){
    vector<vector<pair<string,string> > > pdata;
    unsigned int i=0;
    for(auto c:command){
        if(c=='{')
            break;
        i++;
    }


    int j=0;
    bool flag=false;

    for(unsigned int s=i+1;i<command.size();i++){
        if(command[s]!=' '){
            if(command[s]=='{'){
                flag=true;
                j=s;
            }
            break;
        }
    }


    if(flag==false){ //for single insert
        pdata.push_back(parse(command.begin()+i,command.end()));
    }

    else{ // for multiple insert
        int s=j,e=j,count=0;
        for(unsigned int a=j;a<command.size();a++){
            if(command[a]=='}' && count==1){
                e=a+1;
                //cout<<string(command.begin()+s,command.begin()+e);
                pdata.push_back(parse(command.begin()+s,command.begin()+e));
                count--;
            }
            else if(command[a]=='{' && count==0){
                s=a;
                count++;
            }
          //  else if((command[a]=='}' && count==0) || (command[a]=='{' && count==1)){
           //     cout<<"[!!!]error while parsing,check the format!\n";
           //     throw "";
           // }
         }

    }
    return pdata;

}

string functionsDB::validate_Types (vps &cols,bool mode)  {
    try{
        string t1,t2;
        //cout<<"In validate types\n";
        bool flag=0;
        for(auto &x:cols){

            for(unsigned int i=0;i<TYPE_SIZE;i++){

                if(i<=4){
                    if(strcasecmp(type_name[i],x.second.c_str())==0){
                        //cout<<type_name[i]<<" "<<x.second<<" "<<int(char(i))<<"\n";
                        x.second=to_string(i);
                        flag=1;
                        break;
                    }
                }
                else if(i==5){
                    t1=string(x.second.begin(),x.second.begin()+6);
                    t2=mode==false?string(x.second.begin()+6,x.second.end()):"";
                    //cout<<"\n"<<x.first<<" "<<x.second<<endl;
                    //cout<<"\n t1 "<<t1<<" t2 "<<t2<<endl;

                    if(strcasecmp(t1.c_str(),type_name[i])==0){
                        if(mode == true){
                            flag=1;

                        }
                        else
                            if(t2.size()>0 && t2.size()<=3){
                                for(auto x:t2){
                                    if(isdigit(x)==false){
                                        throw ;
                                    }
                                }

                                int t3 = stoi(t2);
                                // cout<<"\n t3"<<t3<<endl;
                                if(t3>0 && t3<=100){
                                    x.second=to_string(5)+"s"+t2;
                                    //cout<<" x.second "<<x.second[0]<<endl;
                                    flag=1;
                                }
                            }
                    }
                }
            }
            if(flag==0){
                return ("[!!!]"+x.first+"=> specified type is not recognised!");
            }
        flag=0;
        }
        return "OK";
    }
    catch(string a){
        cout<<a;
    }
    catch(...){
        cout<<"[!!!] Error occurred in validate Types\n";
        throw;
    }

}

bool functionsDB::type_Checker(string value,pair<unsigned int,unsigned int>  type,bool mode){
try{
   // cout<<endl<<value<<" "<<type.first<<" "<<type.second<<" in type checker\n";
    if(type.first<=5){

        switch(type.first){
            case 0:{ int temp=stoi(value);}
                    break;
            case 1:{ long long temp=stoll(value);}
                    break;
            case 2: {float temp=stof(value);}
                    break;
            case 3: {double temp=stod(value);}
                    break;
            case 4: if(value.size()>1){
                        throw "Not a char";
                    }
                    break;
            case 5: if(value.size()>type.second && mode==false){
                        throw "string is longer than required\n";
                    }
                    break;
        }
    }
    else{
        ;
    }
    return true;
}
catch(...){
    cout<<"[!!!] "<<value<<" is not of expected type!\n";
    return false;
}
}

int functionsDB::type_Eval(string value){
    if(value[0]=='\"' && value[value.size()-1]=='\"'){
        return 5;
    }
    else {
        return 1;
    }

    //else if(strcmp(value,"true")==0 || strcmp(value,"false")==0 ){
   //     return
    //}
}

int functionsDB::hashFun(string name){

    int Num=0;
    for(int i=0;i<name.size();i++){
        Num+=((int(name[i]))%64)*(i+1);
    }
   // cout<<"\nhash =>"<<Num<<endl;
  return Num;

}




