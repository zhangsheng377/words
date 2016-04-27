#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
//#include "boost/regex.hpp"

using namespace std;

vector<string> words;
vector<string> bestpath;

vector<string> FindNearWords(string word,int index);
void StartDFS(string startWord,string targetWord);
bool DFS(string word,string targetWord,vector<string> path);
void ShowPath(vector<string> path);

int main()
{
    ifstream fin("words");
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
    cout<<"effective words' size = "<<words.size()<<endl;

    char c;
    do
    {
        bestpath.clear();
        string startWord;
        cout<<"\nPlease input startWord:\n";
        cin>>startWord;
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

        StartDFS(startWord,targetWord);

        cout<<endl<<"If you want to continue, please input y"<<endl;
        cin>>c;
    }
    while(c=='y');

    return 0;
}

vector<string> FindNearWords(string word,int index)
{
    int words_size=words.size();
    int word_length=word.length();
    vector<string> nearWords;
    string firstSubstr=word.substr(0,index);
    //cout<<"firstSubstr="<<firstSubstr<<endl;
    string afterSubstr;
    if(index+1<word_length) afterSubstr=word.substr(index+1,word_length-index);
    else afterSubstr="";
    //cout<<"afterSubstr="<<afterSubstr<<endl;
    for(int i=0; i<words_size; i++)
    {
        if(words[i]!=word)
        {
            if(words[i].length()==(unsigned int)word_length)
            {
                string tmpFirstSubstr=words[i].substr(0,index);
                string tmpAfterSubstr;
                if(index+1<word_length) tmpAfterSubstr=words[i].substr(index+1,word_length-index);
                else tmpAfterSubstr="";
                //cout<<"tmpFirstSubstr="<<tmpFirstSubstr<<endl;
                //cout<<"tmpAfterSubstr="<<tmpAfterSubstr<<endl;
                if(tmpFirstSubstr==firstSubstr && tmpAfterSubstr==afterSubstr)
                {
                    nearWords.push_back(words[i]);
                    //cout<<word<<" ==  "<<words[i]<<endl;
                }
            }
        }
    }
    return nearWords;
}

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
                //担心在某些情况下可能要变更已经相同的字母，所以设置为全部搜索//放弃，太慢
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
    cout<<endl;
    for(int i=0; i<path_size-1; i++)
    {
        cout<<path[i]<<"-->";
    }
    cout<<path[path_size-1]<<endl;
}
