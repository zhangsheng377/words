#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <stdio.h>
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

void MakeNearNodes(NODE* node,int index);
//void StartDFS(string startWord,string targetWord);
//bool DFS(string word,string targetWord,vector<string> path);
//void ShowPath(vector<string> path);

int main()
{
    ifstream fin("words");
    ofstream fout("wordsdata1");
    string tmpWord;
    vector<string> tmpWords;
    while(getline(fin,tmpWord))
    {
        int tmpWord_length=tmpWord.length();
        bool isWord=true;
        for(int i=0; i<tmpWord_length; i++)
        {
            if(tmpWord[i]>='A' && tmpWord[i]<='Z') tmpWord[i]+=32;
            if(tmpWord[i]<'a' || tmpWord[i]>'z')
            {
                isWord=false;
                break;
            }
        }
        if(isWord==true) tmpWords.push_back(tmpWord);
    }
    sort(tmpWords.begin(),tmpWords.end());
    //cout<<"sort ok"<<endl;
    unique_copy(tmpWords.begin(),tmpWords.end(),back_inserter(words));
    //cout<<"unique ok"<<endl;
    int words_size=words.size();
    cout<<"words size = "<<words_size<<endl<<"Building the words' topo, please wait..."<<endl;
    for(int i=0; i<words_size; i++)
    {
        cout<<i<<endl;
        NODE* node=new NODE;
        node->word=words[i];
        node->NO=i;
        int word_size=node->word.length();
        node->nearNodes.resize(word_size);
        for(int j=0; j<word_size; j++)
        {
            MakeNearNodes(node,j);
        }
        nodes.push_back(*node);
    }
    cout<<endl<<nodes.size()<<endl;
    int nodes_size=nodes.size();
    /*fout<<nodes_size<<endl;
    for(int i=0;i<nodes_size;i++){
        fout<<nodes[i].word<<endl;
        int word_length=nodes[i].word.length();
        for(int j=0;j<word_length;j++){
            int nearNodes_size=nodes[i].nearNodes[j].size();
            fout<<nearNodes_size<<endl;
            for(int s_i=0;s_i<nearNodes_size;s_i++){
                fout<<nodes[i].nearNodes[j][s_i]->NO<<endl;
            }
        }
    }*/

    //FILE *fp=fopen("wordsdata","w");
   // if(fwrite(&nodes_size,sizeof(nodes_size),1,fp)==-1) cout<<"nodes_size false"<<endl;
    fout<<nodes_size<<endl;
    for(int i=0; i<nodes_size; i++)
    {
       // if(fwrite(&nodes[i].NO,sizeof(nodes[i].NO),1,fp)==-1) cout<<"node_NO false"<<endl;
        fout<<nodes[i].NO<<endl;
       // if(fwrite(&nodes[i].word,sizeof(nodes[i].word),1,fp)==-1) cout<<"node_word false"<<endl;
        fout<<nodes[i].word<<endl;
        int nearNodes_size=nodes[i].nearNodes.size();
       // if(fwrite(&nearNodes_size,sizeof(nearNodes_size),1,fp)==-1) cout<<"nearNodes_size false"<<endl;
        fout<<nearNodes_size<<endl;
        for(int j=0; j<nearNodes_size; j++)
        {
            int s_size=nodes[i].nearNodes[j].size();
           // if(fwrite(&s_size,sizeof(s_size),1,fp)==-1) cout<<"s_size false"<<endl;
            fout<<s_size<<endl;
            for(int s_i=0; s_i<s_size; s_i++)
            {
               // if(fwrite(&nodes[i].nearNodes[j][s_i],sizeof(nodes[i].nearNodes[j][s_i]),1,fp)==-1) cout<<"nearNodes false"<<endl;
                fout<<nodes[i].nearNodes[j][s_i]<<endl;
            }
        }
    }
    //fclose(fp);
    //fout.close();

    /*
        char c;
        do
        {
            bestpath.clear();
            string startWord;
            cout<<"Please input startWord:\n";
            cin>>startWord;

                vector<string> strs=FindNearWords(startWord,1);
                for(int i=0; i<strs.size(); i++)
                {
                    cout<<strs[i]<<endl;
                }

            string targetWord;
            cout<<"Please input targetWord:\n";
            cin>>targetWord;

            //StartDFS(startWord,targetWord);

            cout<<endl<<"If you want to continue, please input y"<<endl;
            cin>>c;
        }
        while(c=='y');
    */
    return 0;
}

void MakeNearNodes(NODE* node,int index)
{
    int nodes_size=nodes.size();
    int word_length=node->word.length();
    string firstSubstr=node->word.substr(0,index);
    string afterSubstr;
    if(index+1<word_length) afterSubstr=node->word.substr(index+1,word_length-index);
    else afterSubstr="";
    for(int i=0; i<nodes_size; i++)
    {
        if(nodes[i].word!=node->word)
        {
            if(nodes[i].word.length()==(unsigned int)word_length)
            {
                string tmpFirstSubstr=nodes[i].word.substr(0,index);
                string tmpAfterSubstr;
                if(index+1<word_length) tmpAfterSubstr=nodes[i].word.substr(index+1,word_length-index);
                else tmpAfterSubstr="";
                if(tmpFirstSubstr==firstSubstr && tmpAfterSubstr==afterSubstr)
                {
                    nodes[i].nearNodes[index].push_back(node->NO);
                    node->nearNodes[index].push_back(nodes[i].NO);
                }
            }
        }
    }
}
/*
void StartDFS(string startWord,string targetWord)
{
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
                vector<string> strs=FindNearWords(startWord,i);
                int strs_size=strs.size();
                for(int j=0; j<strs_size; j++)
                {
                    if(DFS(strs[j],targetWord,path)==true) isFind=true;
                }
            }
        }
        if(isFind==false) cout<<"Can't find."<<endl;
    }
}

bool DFS(string word,string targetWord,vector<string> path)
{
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
                    vector<string> strs=FindNearWords(word,i);
                    int strs_size=strs.size();
                    for(int j=0; j<strs_size; j++)
                    {
                        if(binary_search(tmpPath.begin(),tmpPath.end(),strs[j])==false)//去环
                        {
                            if(DFS(strs[j],targetWord,path)==true) isFind=true;
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
    int path_size=path.size();
    for(int i=0; i<path_size-1; i++)
    {
        cout<<path[i]<<"-->";
    }
    cout<<path[path_size-1]<<endl;
}
*/
