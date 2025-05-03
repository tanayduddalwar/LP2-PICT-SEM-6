#include<iostream>
#include <vector>
#include <queue>
#include<unordered_set>
using namespace std;
int N=3;
vector<vector<int>>goal={{1,2,3},{4,5,6},{7,8,0}};
struct State{
    vector<vector<int>>board;
    int g;
    int h;
    string path;
    bool operator>(const State&Other) const{
        return g + h>Other.g+Other.h;
    } 
};
pair<int,int>locateblank(vector<vector<int>>&board){
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]==0){
                return {i,j};
            }
        }
    }
    return {-1,-1};
}
int calc_heuristic(vector<vector<int>>&board){
    int count=0;
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            if(board[i][j]!=0 && board[i][j]!=goal[i][j]){
                count++;
            }
        }
    }
    return count;
}
string str_path(vector<vector<int>>&board){
    string ans="";
    for(int i=0;i<3;i++){
        for(int j=0;j<3;j++){
            ans=ans+to_string(board[i][j]);
        }
    }
    return ans;
}
bool isgoal(vector<vector<int>>&board){
    if(board==goal){
        return true;
    }
    return false;
}
void solve(vector<vector<int>>&start){
    priority_queue<State,vector<State>,greater<State>>pq;
    int delrow[]={-1,0,1,0};
    int delcol[]={0,1,0,-1};
    char dir[]={'U','R','D','L'};
    pq.push({start,0,calc_heuristic(start),""});
    unordered_set<string>visited;
    visited.insert(str_path(start));
    while(!pq.empty()){
        State curr=pq.top();
        pq.pop();
        pair<int,int>blank=locateblank(curr.board);
        int x=blank.first;
        int y=blank.second;
        if(isgoal(curr.board)){
            cout<<"Solved in "<<curr.g<<"Steps"<<endl;
            cout<<"Path:"<<curr.path<<endl;
            return;

        }
        for(int i=0;i<4;i++){
            int x_loc=x + delrow[i];
            int y_loc=y + delcol[i];
            if(x_loc>=0 && x_loc<3 && y_loc>=0 && y_loc<3){
                auto newboard=curr.board;
                swap(newboard[x][y],newboard[x_loc][y_loc]);
                string p=str_path(newboard);
                if(!visited.count(p)){
                    visited.insert(p);
                    pq.push({newboard,curr.g+1,calc_heuristic(newboard),curr.path+dir[i]});
                }
                
            }

        }

    }
}
int main()
{
    vector<vector<int>>start={{7,8,3},{1,4,6},{5,2,0}};
    solve(start);
    /* code */
    return 0;
}
