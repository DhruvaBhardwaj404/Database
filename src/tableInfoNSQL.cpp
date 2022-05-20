#include "tableInfoNSQL.h"

void tableInfoNSQL::make_Attr_List(fstream &afile,fstream &kfile,int NA){
    if(NA==0){
        return;
    }
    int temp;
    char name[SIZE_ATTR_NAME],t;
    kfile.seekg(0);
    afile.seekg(0);

    for(int i=0;i<NA;i++){
        kfile.read((char*)&temp,SIZE_KEY);
        keys.push_back(temp);
        afile.read((char*)&name,SIZE_ATTR_NAME);
        afile.read((char*)&t,SIZE_ATTR_INFO);
        attr_List.push_back({name,int(t)});

    }


}


int tableInfoNSQL::search_Key(int value){

    int s=0,e=keys.size(),mid;

    if(e==0)
        return -1;

    while(s<=e){
        cout<<s<<" "<<e<<"\n";
        mid=(e+s)/2;
        //cout<<keys[mid];
        if(keys[mid]==value){
            return mid;
        }
        else if(keys[mid]<value){
            s=mid+1;
            continue;
        }
        else {
            e=mid-1;
            continue;
        }

    }
    return -1;
}


void tableInfoNSQL::sort_key(int size){
    int div=keys.size()-size,i=0,j=div,temp;
    vector<pair<string,int>> tattr;
    vector<int> tkey;
    //cout<<"\n in sort key | div "<<div<<" i "<<i <<" j "<<j<<endl;



    while(true)
    {
        if(i<div && j<keys.size()){
            temp=keys[i]<keys[j]?i++:j++;
            tkey.push_back(keys[temp]);
            tattr.push_back(attr_List[temp]);
        }
        else if(i==div && j<keys.size()){
             tkey.push_back(keys[j]);
             tattr.push_back(attr_List[j]);
             j++;
        }
        else if(i<div && j==keys.size()){
             tkey.push_back(keys[i]);
             tattr.push_back(attr_List[i]);
             i++;
        }
        else{
            break;
        }
    }
    keys.clear();
    attr_List.clear();
    keys=tkey;
    attr_List=tattr;
}

void tableInfoNSQL::print_info(NSQL_Cinfo *info){
    cout<<endl<<" filepos "<<info->file_pos
              <<" |start "<<info->start
              <<" |s "<<info->s
              <<" |e"<<info->e
              <<"\n last "<<info->last
              <<"  |mode "<<info->mode
              <<" |r_rec "<<info->r_rec
              <<" |w_rec "<<info->w_rec
              <<" |lfile "<<info->lfile_pos<<endl;
}


void tableInfoNSQL::print_attr_list(){
    cout<<"\nAttribute list"<<endl;
    for(auto x:attr_List){
        cout<<x.first<<" "<<x.second<<endl;
    }
    for(auto x:keys){
        cout<<x<<endl;
    }
}


void tableInfoNSQL::get_data(fstream &fchunk){
    headChunk head;
    nextChunk tail;
    string data,fname,tdata;
    data.resize(SIZE_FCHUNCKS);
    fstream chunk;
    int file_pos,chunk_size;

    while(!fchunk.eof()){
        //cout<<fchunk.tellg()<<endl;
        fchunk.read((char*)data.c_str(),SIZE_FCHUNCKS);
        fchunk.read((char*)&tail,SIZE_TAIL);
        //cout<<data<<" data "<<tail.ctype<<" "<<tail.cnum<<" "<<tail.pos<<" \n";
        while(tail.ctype!=0){
            if(tail.ctype==1){
                fname="sc-"+to_string(tail.cnum)+".dat";
                file_pos=(SIZE_HEAD+SIZE_SMALL_CHUNKS+SIZE_TAIL)*int(tail.pos);
                chunk_size=SIZE_SMALL_CHUNKS;
            }

            else if(tail.ctype==2){
                fname="bc-"+to_string(tail.cnum)+".dat";
                file_pos=(SIZE_HEAD+SIZE_BIG_CHUNKS+SIZE_TAIL)*int(tail.pos);
                chunk_size=(SIZE_BIG_CHUNKS);
            }

            tdata.clear();
            tdata.resize(chunk_size);
            chunk.open(fname,ios::in|ios::out);
            chunk.seekg(file_pos);
            chunk.read((char*)&head,SIZE_HEAD);
            chunk.read((char*)tdata.c_str(),chunk_size);
            chunk.read((char*)&tail,SIZE_TAIL);
            chunk.close();
            //cout<<tdata<<" data "<<tail.ctype<<" "<<tail.cnum<<" "<<tail.pos<<" \n";
            data+=tdata;
        }
      format_data(data);
      data.clear();
    }
}

void tableInfoNSQL::format_data(string data){
    string attr,value;
    bool flag=0;
    int index=record_Data.size();
    record_Data.push_back({});

    for(auto x:data){
        if(x==':'){
            flag=1;
        }

        else if(x==';'){
            flag=0;
            //cout<<index<<" index "<<attr<<" attr "<<value<<" value \n";
            record_Data[index].push_back({attr,data});

            if( Data.find(attr) != Data.end() ){
                Data.at("attr").push_back(data);
            }
            else{
                Data.insert({attr,{data}});
            }

            attr.clear();
            value.clear();
            continue;
        }

        else if(flag==0){
            attr+=x;
        }

        else{
            value+=x;
        }
    }

}
