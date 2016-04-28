#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cstring>
#include <queue>
//#include "boost/regex.hpp"

using namespace std;

vector<string> words;
vector<string> bestpath;
class NODE
{
public:
    string word;
    vector< vector<int> > nearNodes;
    int NO;
};
vector<NODE> nodes;

//vector< vector<int> >  D;
//vector< vector<int> >  PATHD;
//const int INF=999999;

int SearchID(string word);
void StartDFS(int startID,int targetID);
bool DFS(int wordID,int targetID,vector<string> path);
void ShowPath(vector<string> path);

class ANT
{
public:
    vector<string> path;
    int wordID;
};
queue<ANT> ants;
bool isReach=false;
bool move(int targetID,int wordID,vector<string> path);

int main()
{
    cout<<"reading wordsdata1, please wait..."<<endl;
    ifstream fin("wordsdata1");
    int nodes_size;
    fin>>nodes_size;
    nodes.resize(nodes_size);
    //D.resize(nodes_size);
    //PATHD.resize(nodes_size);
    //cout<<nodes_size<<endl;
    for(int i=0; i<nodes_size; i++)
    {
        /*D[i].resize(nodes_size);
        cout<<"resize  D[i] ok"<<endl;
        for(int D_i=0; D_i<nodes_size; D_i++)
        {
            D[i][D_i]=INF;
            if(i==D_i) D[i][D_i]=0;
        }
        cout<<"init D[i] ok"<<endl;
        PATHD[i].resize(nodes_size);
        cout<<"resize  PATHD[i] ok"<<endl;
        for(int P_i=0; P_i<nodes_size; P_i++)
        {
            PATHD[i][P_i]=-1;
        }
        cout<<"init  PATHD[i] ok"<<endl;*/
        //fread(&nodes[i].NO,sizeof(nodes[i].NO),1,fp);
        fin>>nodes[i].NO;
        //cout<<"nodes[i].NO="<<nodes[i].NO<<endl;
        //fread(&nodes[i].word,sizeof(nodes[i].word),1,fp);
        fin>>nodes[i].word;
        //cout<<"nodes[i].word="<<nodes[i].word<<endl;
        int nearNodes_size;
        //fread(&nearNodes_size,sizeof(nearNodes_size),1,fp);
        fin>>nearNodes_size;
        //cout<<"nearNodes_size="<<nearNodes_size<<endl;
        nodes[i].nearNodes.resize(nearNodes_size);
        for(int j=0; j<nearNodes_size; j++)
        {
            int s_size;
            //fread(&s_size,sizeof(s_size),1,fp);
            fin>>s_size;
            //cout<<"s_size="<<s_size<<endl;
            nodes[i].nearNodes[j].resize(s_size);
            for(int s_i=0; s_i<s_size; s_i++)
            {
                //fread(&nodes[i].nearNodes[j][s_i],sizeof(nodes[i].nearNodes[j][s_i]),1,fp);
                fin>>nodes[i].nearNodes[j][s_i];
                //D[i][nodes[i].nearNodes[j][s_i]]=1;
                //D[nodes[i].nearNodes[j][s_i]][i]=1;
                //PATHD[i][nodes[i].nearNodes[j][s_i]]=i;
                //PATHD[nodes[i].nearNodes[j][s_i]][i]=nodes[i].nearNodes[j][s_i];
                //cout<<"nodes[i].nearNodes[j][s_i]="<<nodes[i].nearNodes[j][s_i]<<endl;
            }
        }
    }
    cout<<"words' size="<<nodes.size()<<endl;




    //fout.close();
    //cout<<nodes[0].word<<endl;

    //char c='y';
    //do
    {
        bestpath.clear();
        string startWord;
        cout<<"Please input startWord:\n";
        cin>>startWord;
        int startId=SearchID(startWord);
        if(startId==-1)
        {
            cout<<"Can't find this word."<<endl;
            //continue;
        }
        /*
                    vector<string> strs=FindNearWords(startWord,1);
                    for(int i=0; i<strs.size(); i++)
                    {
                        cout<<strs[i]<<endl;
                    }
        */
        string targetWord;
        cout<<"Please input targetWord:\n";
        cin>>targetWord;
        int targetId=SearchID(targetWord);
        if(targetId==-1)
        {
            cout<<"Can't find this word."<<endl;
            //continue;
        }

        //StartDFS(startId,targetId);
        //ants.clear();
        ANT ant;
        ant.wordID=startId;
        vector<string> path;
        path.clear();
        ant.path=path;
        ants.push(ant);
        while(ants.size())
        {
            ANT tmp=ants.front();
            ants.pop();
            move(targetId,tmp.wordID,tmp.path);
            //cout<<"ants   moved"<<endl;
            if(isReach==true) break;

        }
        if(isReach==false) cout<<"Can't find path."<<endl;
        //cout<<endl<<"If you want to continue, please input y"<<endl;
        //docin>>c;
    }
    //while(c=='y');

    return 0;
}


bool move(int targetID,int wordID,vector<string> path)
{
    //cout<<"ant moving"<<endl;
    string word=nodes[wordID].word;
    string targetWord=nodes[targetID].word;
    path.push_back(word);
    int bestpath_size=bestpath.size();
    int path_size=path.size();
    if(word==targetWord)
    {
        if(bestpath_size==0 || path_size<bestpath_size)
        {
            bestpath=path;
            isReach=true;
            ShowPath(bestpath);//怕程序执行得太久，所以每次输出更好一些的结果，而不是到最后再输出最优解
            return true;
        }
    }
    else
    {
        if(bestpath_size>0 && path_size>=bestpath_size) return false;
        else
        {
            //bool isFind=false;
            int word_length=word.length();
            vector<string> tmpPath=path;
            sort(tmpPath.begin(),tmpPath.end());
            for(int i=0; i<word_length; i++)
            {
                //if(word[i]!=targetWord[i])
                {
                    //cout<<"ids"<<endl;
                    vector<int> ids=nodes[wordID].nearNodes[i];
                    int ids_size=ids.size();
                    //cout<<"ids_size="<<ids_size<<endl;
                    for(int j=0; j<ids_size; j++)
                    {
                        if(binary_search(tmpPath.begin(),tmpPath.end(),nodes[ids[j]].word)==false)//去环
                        {
                            //if(DFS(ids[j],targetID,path)==true) isFind=true;
                            //cout<<"ant start"<<endl;
                            ANT ant;
                            //cout<<"ant start 1     j="<<j<<endl;
                            ant.wordID=ids[j];
                            //cout<<"ant start 2     j="<<j<<endl;
                            ant.path=path;
                            //ant->path.resize(path.size());
                            //memcpy(&ant->path[0],&path[0],path.size()*sizeof(string));
                            //cout<<"ant start 3     j="<<j<<endl;
                            ants.push(ant);
                            //cout<<"ant end"<<endl;
                        }
                    }
                }
            }
            //return isFind;
        }
    }
    // ~ANT();
    return false;
}

int SearchID(string word)
{
    int nodes_size=nodes.size();
    for(int i=0; i<nodes_size; i++)
    {
        if(nodes[i].word==word) return i;
    }
    return -1;
}

void StartDFS(int startID,int targetID)
{
    string startWord=nodes[startID].word;
    string targetWord=nodes[targetID].word;
    int startWord_length=startWord.length();
    int targetWord_length=targetWord.length();
    if(startWord_length!=targetWord_length) cout<<"Can't find."<<endl;
    else
    {
        vector<string> path;
        path.push_back(startWord);
        bool isFind=false;
        for(int i=0; i<startWord_length; i++)
        {
            //担心在某些情况下可能要变更已经相同的字母，所以设置为全部搜索//放弃，太慢
            if(startWord[i]!=targetWord[i])
            {
                vector<int> ids=nodes[startID].nearNodes[i];
                int ids_size=ids.size();
                for(int j=0; j<ids_size; j++)
                {
                    if(DFS(ids[j],targetID,path)==true) isFind=true;
                }
            }
        }
        if(isFind==false) cout<<"Can't find."<<endl;
    }
}

bool DFS(int wordID,int targetID,vector<string> path)
{
    string word=nodes[wordID].word;
    string targetWord=nodes[targetID].word;
    path.push_back(word);
    int bestpath_size=bestpath.size();
    int path_size=path.size();
    if(word==targetWord)
    {
        if(bestpath_size==0 || path_size<bestpath_size)
        {
            bestpath=path;
            ShowPath(bestpath);//怕程序执行得太久，所以每次输出更好一些的结果，而不是到最后再输出最优解
            return true;
        }
    }
    else
    {
        if(bestpath_size>0 && path_size>=bestpath_size) return false;
        else
        {
            bool isFind=false;
            int word_length=word.length();
            vector<string> tmpPath=path;
            sort(tmpPath.begin(),tmpPath.end());
            for(int i=0; i<word_length; i++)
            {
                if(word[i]!=targetWord[i])
                {
                    vector<int> ids=nodes[wordID].nearNodes[i];
                    int ids_size=ids.size();
                    for(int j=0; j<ids_size; j++)
                    {
                        if(binary_search(tmpPath.begin(),tmpPath.end(),nodes[ids[j]].word)==false)//去环
                        {
                            if(DFS(ids[j],targetID,path)==true) isFind=true;
                        }
                    }
                }
            }
            return isFind;
        }
    }
    return false;
}

void ShowPath(vector<string> path)
{
    cout<<endl;
    int path_size=path.size();
    for(int i=0; i<path_size-1; i++)
    {
        cout<<path[i]<<"-->";
    }
    cout<<path[path_size-1]<<endl;
}

