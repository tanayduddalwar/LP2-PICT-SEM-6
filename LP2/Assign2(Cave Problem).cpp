#include<iostream>
#include<bits/stdc++.h>
using namespace std;

int main()
{
    cout<<"************The Bridge of Death************"<<endl<<endl;
    cout<<"There are n friends stuck on an island.\nThey want to cross the bridge as soon as possible because the bridge can fall down at any moment due to storm.\nAt a time, only 2 people can walk on the bridge.\nAlso they one torch and they couldn't see without the torch.\nSo, every time 2 people go on the other side, someone will have to come back to return the torch.\nYou have to calculate the minimum time in which all of them can cross the bridge.";
    cout<<endl<<endl;
    float estimate;
    float total_time = 0;
    int person;
    cout<<"Enter the number of persons: ";
    cin>>person;
    vector<float>left(person);
    for(int i=0;i<person;i++)
    {
        cout<<"Enter the time for "<<i+1<<"th person:";
        cin>>left[i];
    }
    cout<<"How much minimum time will the "<<person<<" friends take to cross the bridge?"<<endl;
    cin>>estimate;
    vector<float>right;
    float x,y,ret,finalx,finaly,finalret;
    float finalfn=INT_MAX;
    float fn=INT_MAX;
    float gn=INT_MAX;
    float hn=INT_MAX;
    while(left.size()>2)
    {
        for(int i=0;i<left.size()-1;i++)
        {
            for(int j=i+1;j<left.size();j++)
            {
                cout<<"("<<left[i]<<","<<left[j]<<")"<<endl;
                x=left[i];
                y=left[j];
                ret=x;
                if(ret>y)
                    ret=y;
                for(int k=0;k<right.size();k++)
                {
                    if(ret>right[k])
                        ret=right[k];
                }
                gn=max(x,y)+ret;
                hn=ret-x-y;
                for(int a=0;a<left.size();a++)
                {
                    hn+=left[a];
                }
                fn=gn+hn;
                if(fn<finalfn)
                {
                    finalfn=fn;
                    finalx=x;
                    finaly=y;
                    finalret=ret;
                }
                cout<<"f(n)="<<gn<<"+"<<hn<<"="<<fn<<endl;
                cout<<endl;
            }
        }
        cout<<"Chose "<<finalx<<" and "<<finaly<<endl;
        cout<<"f(n)="<<finalfn<<endl;
        cout<<endl;
        cout<<finalx<<" and "<<finaly<<" went"<<endl;
        total_time+=max(finalx,finaly);
        left.erase(find(left.begin(),left.end(),finalx));
        cout<<finalret<<" returned"<<endl;
        total_time+=finalret;
        left.erase(find(left.begin(),left.end(),finaly));
        left.push_back(finalret);
        right.push_back(finalx);
        right.push_back(finaly);
        right.erase(find(right.begin(),right.end(),finalret));

        cout<<"Time:"<<total_time<<endl;
        cout<<endl;
    }
    cout<<"f(n)="<<max(left[0],left[1])<<"+0="<<max(left[0],left[1])<<endl;
    cout<<left[0]<<" and "<<left[1]<<" went"<<endl;
    total_time+=max(left[0],left[1]);
    cout<<"Total time taken: "<<total_time<<endl;
    cout<<endl;
    if(estimate==total_time)
    {
        cout<<"Congratulations! Your estimate was correct."<<endl;
    }
    else if(estimate>total_time)
    {
        cout<<"Your estimate was a little high."<<endl;
    }
    else
    {
        cout<<"Your estimate was a little low."<<endl;
    }
    return 0;
}