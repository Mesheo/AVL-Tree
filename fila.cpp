#include <iostream>
#include <queue>
using namespace std;
  
// Print the queue
void mostrarFila(queue<int> fila)
{
    queue<int> g = fila;
    while (!g.empty()) {
        cout << '\t' << g.front();
        g.pop();
    }
    cout << '\n';
}
  
// Driver Code
int main()
{
    queue<int> fila;
    fila.push(10);
    fila.push(20);
    fila.push(30);
  
    cout << "The queue gquiz is : ";
    mostrarFila(fila);
  
    cout << "\nfila.size() : " << fila.size();
    cout << "\nfila.front() : " << fila.front();
    cout << "\nfila.back() : " << fila.back();
  
    cout << "\nfila.pop() : ";
    fila.pop();
    mostrarFila(fila);
  
    return 0;
}