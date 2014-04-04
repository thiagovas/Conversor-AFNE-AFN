#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <utility>
#include <functional>
#include <locale>
#include <queue>
#include <stack>
#include <deque>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <cstdio>
using namespace std;

/* Union-Find */
vector<int> p; 

void initUnionFind(int n) 
{
	p.clear();
	p.resize(n);
	for(int i = 0; i < n; i++) 
		p[i] = i;
}

int Find(int a) { return p[a] == a ? a : p[a] = Find(p[a]); }

void Union(int a, int b) { p[Find(a)] = Find(b); }

void converter(vector<vector<pair<int, string> > > &automato, set<int> &estados_iniciais, set<int> &estados_finais);

int main()
{
	ios::sync_with_stdio(false);
	vector<vector<pair<int, string> > > automato;
	set<int> estados_iniciais, estados_finais;
	vector<int> alfabeto, estados;
	vector<string> palavras;
	string input,pv;
	int e1, e2;

	// Leitura dos estados do AFNE
	while(true)
	{
		cin >> input;
		if(input == ";") break;

		estados.push_back(atoi(input.c_str())-1);
	}

	// Leitura do alfabeto
	while(true)
	{
		cin >> input;
		if(input == ";") break;

		alfabeto.push_back(atoi(input.c_str()));
	}

	automato.clear();
	automato.resize(estados.size());

	// Leitura das transicoes
	while(true)
	{
		cin >> input;
		if(input == ";") break;
		e1 = atoi(input.c_str());

		cin >> e2 >> input >> pv;
		e1--; e2--;
		automato[e1].push_back(make_pair(e2, input));
	}
	
	// Leitura dos estados iniciais
	while(true)
	{
		cin >> input;
		if(input == ";") break;

		estados_iniciais.insert(atoi(input.c_str())-1);
	}

	// Leitura dos estados finais
	while(true)
	{
		cin >> input;
		if(input == ";") break;

		estados_finais.insert(atoi(input.c_str())-1);
	}
	
	// Leitura das palavras a serem verificadas
	while(true)
	{
		cin >> input;
		if(input == ";") break;

		palavras.push_back(input);
	}

	// Converte o AFNE para um AFN
	converter(automato, estados_iniciais, estados_finais);
	
	
	/*
	for(vector<vector<pair<int, string> > >::iterator it = automato.begin(); it != automato.end(); it++)
	{
		for(vector<pair<int, string> >::iterator jt = it->begin(); jt != it->end(); jt++)
		{
			cout << it-automato.begin() << " " << jt->first << " " << jt->second << endl;
		}
	}
	
	cout << "\nEstados iniciais:\n";
	for(set<int>::iterator it = estados_iniciais.begin(); it != estados_iniciais.end(); it++)
		cout << *it << endl;
	
	cout << "\nEstados finais:\n";
	for(set<int>::iterator it = estados_finais.begin(); it != estados_finais.end(); it++)
		cout << *it << endl;
	*/

	return 0;
}

void converter(vector<vector<pair<int, string> > > &automato, set<int> &estados_iniciais, set<int> &estados_finais)
{
	vector<bool> visited(automato.size(), false);
	vector<vector<pair<int, string> > > newAutomato;
	set<int> counter, newEstIniciais, newEstFinais;
	map<int, int> mVertex;
	queue<int> nodes;
	int atual;

	for(set<int>::iterator it = estados_iniciais.begin(); it != estados_iniciais.end(); it++)
		nodes.push(*it);
	
	initUnionFind(automato.size());

	while(!nodes.empty())
	{
		atual = nodes.front();
		nodes.pop();
		if(visited[atual]) continue;

		visited[atual] = true;
		for(vector<pair<int, string> >::iterator it = automato[atual].begin(); it != automato[atual].end(); it++)
		{
			if(it->second == "v")
			{
				if(estados_iniciais.find(atual) != estados_iniciais.end())
					estados_iniciais.insert(it->first);
				
				if(estados_finais.find(atual) != estados_finais.end())
					estados_finais.insert(it->first);

				if(estados_finais.find(it->first) != estados_finais.end())
					estados_finais.insert(atual);
				
				Union(atual, it->first);
				
				nodes.push(it->first);
			}
		}
	}

	for(int i = 0; i < automato.size(); i++)
		counter.insert(Find(i));
	atual = 0;
	for(set<int>::iterator it = counter.begin(); it != counter.end(); it++)
	{
		mVertex.insert(make_pair(*it, atual++));
		if(estados_iniciais.find(*it) != estados_iniciais.end())
			newEstIniciais.insert(mVertex[*it]);
		if(estados_finais.find(*it) != estados_finais.end())
			newEstFinais.insert(mVertex[*it]);
	}
	newAutomato.resize(mVertex.size());

	for(int i = 0; i < automato.size(); i++)
		if(p[i] == i)
		{
			for(int j = 0; j < automato.size(); j++) if(Find(j) == i)
			{
				for(int k = 0; k < automato[j].size(); k++)
					if(automato[j][k].second != "v")
						newAutomato[mVertex[i]].push_back(make_pair(mVertex[Find(automato[j][k].first)], automato[j][k].second));
			}
		}
	
	automato = newAutomato;
	estados_iniciais = newEstIniciais;
	estados_finais = newEstFinais;	
}

