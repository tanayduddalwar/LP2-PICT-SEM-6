#include<iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;
int main()
{
    
    float fn,gn,hn=INT_MAX;
    float finalfn=INT_MAX;
    float finalret,finalx,finaly=0;
    float totaltime=0;
    float x,y;
    int members;
    int ret;
    cout<<"Enter the number of students"<<endl;
    cin>>members;
    vector<float>left(members);
    vector<float>right;
    cout<<"Enter time for each member to come out"<<endl;
    for(int i=0;i<members;i++){
        cout<<"Enter time for "<<i<<"th member"<<endl;
        cin>>left[i];
    }
    while(left.size()>2){
        for(int i=0;i<left.size()-1;i++){
            for(int j=i+1;j<left.size();j++){
                x=left[i];
                y=left[j];
                ret=min(x,y);
                for(int k=0;k<right.size();k++){
                    if(right[i]<ret){
                        ret=right[i];
                    }
                }
                hn=ret-x-y;
                for(int z=0;z<left.size();z++){
                    hn=hn+left[z];
                }
                
                gn=max(x,y)+ret;
                fn=gn+hn;
                if(fn<finalfn){
                    finalfn=fn;
                    finalx=x;
                    finaly=y;
                    finalret=ret;
                }
                cout<<"fn="<<gn<<"+"<<hn<<"="<<fn<<endl;

            }
        }
        cout<<"Choose"<<finalx<<"and"<<finaly<<"went"<<endl;
        cout<<"fn="<<finalfn<<endl;
        totaltime=totaltime+max(finalx,finaly);
        left.erase(find(left.begin(),left.end(),finalx));
        left.erase(find(left.begin(),left.end(),finaly));
        cout<<finalret<<"returned"<<endl;
        left.push_back(finalret);

        totaltime=totaltime+finalret;
        right.push_back(finalx);
        right.push_back(finaly);
        right.erase(find(right.begin(),right.end(),finalret));
        cout<<"Total Time taken"<<totaltime<<endl;
    }
    totaltime=totaltime+max(left[0],left[1]);
    cout<<"Total Time taken"<<totaltime<<endl;
    return 0;
}
