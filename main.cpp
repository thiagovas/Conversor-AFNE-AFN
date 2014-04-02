#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <utility>
#include <functional>
#include <locale>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cmath>
#include <cctype>
#include <cstdio>
using namespace std;

int main()
{
	ios::sync_with_stdio(false);
	vector<vector<pair<int, string> > > automato;
	set<int> estados_iniciais, estados_finais;
	vector<int> alfabeto, estados;
	vector<string> palavras;
	string input,final;
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

		cin >> e2 >> input >> final;
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


	
	return 0;
}
