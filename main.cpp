#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
using namespace std;
ifstream fin("date.in");
ofstream fout("date.out");
#define nmax 1001
int nr_stari,m,stare_initiala,cnt,x,tranz,a,b,contor,valoare;
bool stare_finala[nmax];
vector< pair<int, char> > adiacenta[nmax];
string sir;
char stari[nmax],caracter;
void Citire()
{
    fin>>nr_stari>>m;
    fin.get();
    fin.get(stari,nmax);
    fin>>stare_initiala>>cnt;
    for(int i=1; i<=cnt; ++i)
    {
        fin>>x;
        stare_finala[x]=true;
    }
    fin>>tranz;
    for(int i=1; i<=tranz; ++i) ///$
    {
        fin>>a>>caracter>>b;
        adiacenta[a].push_back(make_pair(b,caracter));
    }
}
void NFA(int nod,vector < int > &lambda)
{
    for(vector< pair<int, char> > ::iterator it=adiacenta[nod].begin(); it!=adiacenta[nod].end(); it++)
        if((*it).second == '$')
        {
            lambda.push_back((*it).first);
            NFA((*it).first,lambda);
        }
}
bool Validare(string &cuvant)
{
    vector<int> stare_curenta;
    stare_curenta.push_back(stare_initiala);
    vector<int>lambda;
    vector<int>v;
    NFA(stare_initiala, lambda);
    for(int i = 0; i < lambda.size(); ++i)
        stare_curenta.push_back(lambda[i]);
    for(int k = 0; k < cuvant.size(); ++k)
    {
        for(int i = 0; i < stare_curenta.size(); ++i)
        {
            for(int j = 0; j < adiacenta[stare_curenta[i]].size(); ++j)
                if(cuvant[k] == adiacenta[stare_curenta[i]][j].second)
                    v.push_back(adiacenta[stare_curenta[i]][j].first);
        }
        for(int i = 0; i < v.size(); ++i)
            NFA(v[i], lambda);
        for(int i = 0; i < lambda.size(); ++i)
            v.push_back(lambda[i]);
        stare_curenta = v;
        lambda.clear();
        v.clear();
    }
    for(int i = 0; i < stare_curenta.size() ; ++i)
        if(stare_finala[stare_curenta[i]])
            return true;
    return false;
}
int main()
{
    Citire();
    while(fin>>sir)
    {
        cout<<sir<<"-";
        if(Validare(sir))
            cout<<"True";
        else
            cout<<"False";
        cout<<'\n';
    }
    return 0;
}
