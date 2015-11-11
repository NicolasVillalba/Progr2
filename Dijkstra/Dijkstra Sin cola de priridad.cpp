#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <sstream>
#define mp make_pair
#define max LLONG_MAX
using namespace std;

//Método de salida rápido
inline void escribirEntero (int n)
{
  int N = n, rev, count = 0;
  rev = N;
  if (N == 0) { putchar('0'); putchar('\n'); return ;}
  while ((rev % 10) == 0) { count++; rev /= 10;}
  rev = 0;
  while (N != 0) { rev = (rev<<3) + (rev<<1) + N % 10; N /= 10;}
  while (rev != 0) { putchar(rev % 10 + '0'); rev /= 10;}
  while (count--) putchar('0');
  putchar(' ');
}

//Método de entrada rápida usando el buffer
inline int EntradaRapida(){
	char ch;
	long long valor=0;
	ch=getchar();
	while(ch == '\n' || ch == ' '){
		ch=getchar();
	}
	valor=0;
	while(ch >= '0' && ch <= '9'){
		valor=(valor*10)+(ch-'0');
		ch=getchar();
  }
  return valor;
}


int main(){
	long long nodos,aristas;
	nodos=EntradaRapida();
	aristas = EntradaRapida();
	//Lista de adyacencia(nodo, peso)
	vector<pair<long long ,long long> > mapa[nodos+1];
	//carga lista de adyacencia
	for(int i = 0; i < aristas; i++){
		long long a,b,c;
		a= EntradaRapida();
		b= EntradaRapida();
		c= EntradaRapida();
		mapa[a].push_back(mp(b,c));
		mapa[b].push_back(mp(a,c));
	}
	deque <long long> cola;
	//Arreglo donde se guardan (nodo anterior, peso para llegar al nodo),cada posición del arreglo representa a un nodo. El
	//arreglo se utiliza, tanto para calcular las distancias de manera dinámica, como para luego, gracias a su indicador de nodo 
	//anterior, poder reconstruir el grafo.
	pair <long long, long long> pesos[nodos+5];
	//Inicialización del arreglo de pesos en infinito
	for(int i = 0; i <= nodos;i++){
		pesos[i]= mp(0,max);
	}
	//Comienzo del algoritmo Dijkstra sin utilización de cola de priridad, el método utiliza más memoria, ya que en la cola se pueden
	// agregar nodos ya visitados, siempre y cuando se cumpla la condición de que de este modo el camino sea más corto. A su vez el algoritmo
	// presenta una ventaja en velocidad, ya que no debe realizar una busqueda binaria en la cola para agregar nodos, debido a que esta no 
	// tiene ningún criterio de prioridad
	pesos[1]=mp(0,0);
	bool visitados[nodos+5];
	memset(visitados,0,sizeof(visitados));
	cola.push_back(1);
	long long aux;
	while(!cola.empty()){
		aux = cola.front();
		visitados[aux] = true;
		cola.pop_front();		
		for(size_t i = 0; i < mapa[aux].size();i++){
			long long nodo = mapa[aux].at(i).first;
			long long peso = mapa[aux].at(i).second;
			if(pesos[aux].second + peso < pesos[nodo].second){				
				pesos[nodo] = mp(aux, peso + pesos[aux].second);
				if(!visitados[nodo]){
					cola.push_front(nodo);				
				}else{
					cola.push_back(nodo);
				}
				visitados[nodo] = true;
			}
		}
	}
	//Luego solo queda verificar si el último nodo fué alcanzado por el recorrido del grafo, en caso de serlo
	// se comenzará a recorrer el arreglo de pesos desde el último nodo hasta el primero para así reconstruir el camino mínimo
	if(pesos[nodos].second != LLONG_MAX){
		vector <long long int> res;
		res.push_back(nodos);
		long long int aux = pesos[nodos].first;
		while(aux != 0){
			res.push_back(aux);
			aux = pesos[aux].first;
		}
		for(int i = res.size()-1; i >= 0 ; i-- ){
			escribirEntero(res[i]);
		}
		cout<<endl;
	}else{
		cout<<-1<<endl;
	}
	return 0;
	
}
