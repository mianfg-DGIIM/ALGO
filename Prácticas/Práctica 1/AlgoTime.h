class AlgoTime {
public:
    double ejecutarFuncion(funcion, int inicio, int fin, int paso=1) {
        for ( int i = inicio; i <= fin; i += paso ) {
            funcion(i);
        }
    }
    
}