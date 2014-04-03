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

void converter(vector<vector<pair<int, string> > > &automato, set<int> estados_iniciais, set<int> estados_finais);

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

		estados.push_back(atoi(input.c_str()));
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

		estados_iniciais.insert(atoi(input.c_str()));
	}

	// Leitura dos estados finais
	while(true)
	{
		cin >> input;
		if(input == ";") break;

		estados_finais.insert(atoi(input.c_str()));
	}
	
	// Leitura das palavras a serem veriicadas
	while(true)
	{
		cin >> input;
		if(input == ";") break;

		palavras.push_back(input);
	}

	// Converte o AFNE para um AFN
	converter(automato, estados_iniciais, estados_finais);
	
	return 0;
}

void converter(vector<vector<pair<int, string> > > &automato, set<int> estados_iniciais, set<int> estados_finais)
{
	vector<bool> visited(automato.size(), false);
	queue<int> nodes;
	int atual;

	for(set<int>::iterator it = estados_iniciais.begin(); it != estados_iniciais.end(); it++)
		nodes.push(*it);
	
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

}

