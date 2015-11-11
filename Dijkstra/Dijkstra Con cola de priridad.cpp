#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <cstring>
#include <cmath>
#include <cstdio>

#define mp make_pair
#define max LLONG_MAX
using namespace std;

//Esta estructura es creada con el fin de usar su método "operator" como criterio de comparación (en este caso de menor a mayor) entré pares de
//enteros largos(el primer numero representa al nodo y el segundo al peso para llegar hasta el desde el nodo uno). Es tomado el segundo valor como
// criterio de comparación ya que este representa el peso del camino. Este operador será utilizado más adelante para agregar elementos a una cola de 
// prioridad.
struct Order{
    bool operator()(pair< long long,long long> const& a, pair< long long, long long> const& b) const
    {
        return a.second > b.second;
    }
};
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
	//Constructor de cola de prioridad estableciendo criterio de ordenamiento para la inserción de elementos
	priority_queue< pair<long long, long long> ,vector<pair<long long, long long> >,Order> cola;
	//Arreglo donde se guardan (nodo anterior, peso para llegar al nodo),cada posición del arreglo representa a un nodo. El
	//arreglo se utiliza, tanto para calcular las distancias de manera dinámica, como para luego, gracias a su indicador de nodo 
	//anterior, poder reconstruir el grafo.
	pair <long long, long long> pesos[nodos+5];
	//Inicialización del arreglo de pesos en infinito
	for(int i = 0; i <= nodos;i++){
		pesos[i]= mp(0,max);
	}
	//Comienzo del algorítmo Dijkstra con cola de priridad: los elementos serán agregados a la cola de acuerdo al peso del camino que va
	//desde el nodo 1 hasta el nodo que se está agregando, de esta manera, cada vez que se visita un nodo se obtiene la solución óptima para
	// llegar desde la raíz hasta este.
	pesos[1]=mp(0,0);
	bool visitados[nodos+5];
	memset(visitados,0,sizeof(visitados));
	cola.push(mp(1,0));
	long long aux;

	while(!cola.empty() && aux != nodos){
		aux = cola.top().first;
		visitados[aux] = true;
		cola.pop();		
		for(size_t i = 0; i < mapa[aux].size();i++){
			long long nodo = mapa[aux].at(i).first;
			long long peso = mapa[aux].at(i).second;
			if(!visitados[nodo] && pesos[aux].second + peso < pesos[nodo].second){
				pesos[nodo] = mp(aux, peso + pesos[aux].second);
				cola.push(mp(nodo,pesos[nodo].second));					
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
