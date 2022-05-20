#include "tableInfo.h"

void  tableInfo::map_DataTypes(char col_Names[100][20],unsigned int  col_Type[],unsigned int  var_Col_size[],unsigned int &NC){
    columns.clear();
    for(int i=0,j=0;i<NC;i++){
        if(col_Type[i]<=4){
           columns.insert(make_pair(string(col_Names[i]),make_pair(col_Type[i],0U)));
        }

        else{
            columns.insert({string(col_Names[i]),{col_Type[i],var_Col_size[j]}});
            j++;
        }

    }

}

void tableInfo::print_columns(char col_Names[100][20],unsigned int NC){
    cout<<endl;
    for(unsigned int i=0;i<NC;i++){
        cout<<col_Names[i]<<" "<<columns[col_Names[i]].first<<" "<<columns[col_Names[i]].second<<"\n";
    }
}
