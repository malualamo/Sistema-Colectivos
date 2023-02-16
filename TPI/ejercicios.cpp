#include "ejercicios.h"
#include "auxiliares.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <iomanip>

using namespace std;

/******++++**************************** EJERCICIO tiempoTotal ***********+++***********************/
tiempo tMax(viaje v){
    tiempo max= obtenerTiempo(v[0]);
    for(int i=0; i < v.size(); i++){
        if(obtenerTiempo(v[i]) > max){
            max = obtenerTiempo(v[i]);
        }
    }
    return max;
}

tiempo tMin(viaje v){
    tiempo min= obtenerTiempo(v[0]);
    for(int i=0; i < v.size(); i++){
        if(obtenerTiempo(v[i]) < min){
            min = obtenerTiempo(v[i]);
        }
    }
    return min;
}

tiempo tiempoTotal(viaje v) {
    tiempo t;
    t=tMax(v)-tMin(v);

    return t;
}

/* En la función tiempoTotal la cantidad de operaciones en el peor caso en tMax(v) es de 7n, y en tMin(v)
 * también 7n. Con las operaciones elementales de la linea 33, la función tiempoTotal hace
 * en el peor caso 14n+2 operaciones, es decir que pertenece a O(n).*/

/************++*********************** EJERCICIO distanciaTotal ************++*********************/

void ordenarViaje(viaje &v){
    for(int i=0; i<v.size(); i++){
        for(int j=i; j<v.size(); j++){
            if(obtenerTiempo(v[i])> obtenerTiempo(v[j])){
                swap(v[i],v[j]);
            }
        }
    }
}


distancia distanciaTotal(viaje v) {
    distancia d=0;
    ordenarViaje(v);
    for(int i=0; i<v.size()-1; i++){
        d = d + distEnKM(obtenerPosicion(v[i]), obtenerPosicion(v[i+1]));
    }

    return d;
}

/* En la función distanciaTotal la cantidad de operaciones en el peor caso para ordenarViaje(v) pertenece a O(n**2).
 * Ademas, para el peor caso el for de la linea 58 pertenece a O(n). Por lo tanto, si la funcion pertenece a O(n)+O(n**2),
 * entonces pertenece a O(n**2).*/

/*****************************+***** EJERCICIO excesoDeVelocidad **********************************/

float velocidad(tuple<tiempo, gps> p1, tuple<tiempo, gps> p2){
    float velocidad;
    velocidad=(distEnKM(obtenerPosicion(p2), obtenerPosicion(p1)))/((obtenerTiempo(p2)- obtenerTiempo(p1))/3600);
    return velocidad;
}

bool excesoDeVelocidad(viaje v) {
    bool resp = false;
    ordenarViaje(v);
    for(int i=1; i<v.size(); i++){
        if (velocidad(v[i-1],v[i])>80){
            resp=true;
            return resp;
        }
    }

    return resp;
}

/************************************ EJERCICIO recorridoCubierto *******************************/

vector<gps> recorridoNoCubierto(viaje v, recorrido r, distancia u) {
    vector<gps> resp={};
    for(int i=0; i<r.size(); i++){ // |r|
        int contador=0;
        for(int j=0; j<v.size(); j++){ // |v|
            if(distEnKM(r[i], obtenerPosicion(v[j]))>=u){
                contador=contador+1;
            }
        }
        if(contador==v.size()){
            resp.push_back(r[i]);
        }
    }

    return resp;
}

/*Tomamos n=|v| y m=|r|, longitudes del viaje y el recorrido respectivamente, y analizamos que el peor caso
sucede cuando todos los puntos del recorrido estan fuera del umbral. En este caso, para cada punto del recorrido, se
realizan 10*|v|+3 operaciones elementales. Esto nos da una complejidad de 4*|m|*(10*|n|+3) que pertenece a O(n*m)*/

/***************************************** EJERCICIO flota ***************************************/

bool estuvoEnfranja(viaje v, tiempo t0, tiempo tf){
    ordenarViaje(v);
    if(tMax(v)<t0 || tMin(v)>tf ){
        return false;
    }
    return true;
}

int flota(vector<viaje> f, tiempo t0, tiempo tf) {
    int resp=0;
    for (int i=0; i<f.size(); i++){
        if(estuvoEnfranja(f[i],t0,tf)){
            resp=resp + 1;
        }
    }

    return resp;
}

/************************************** EJERCICIO construirGrilla *******************************/

double anchoCelda(gps esq1, gps esq2, int m){
    return (obtenerLongitud(esq2)- obtenerLongitud(esq1))/m;
}

double altoCelda(gps esq1, gps esq2, int n){
    return (obtenerLatitud(esq1)- obtenerLatitud(esq2))/n;
}

grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    grilla resp = {};
    double ancho= anchoCelda(esq1, esq2, m);
    double alto= altoCelda(esq1, esq2, n);
    for (int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            resp.push_back(celda (gps (obtenerLatitud(esq1)-(i-1)*alto, obtenerLongitud(esq1)+(j-1)*ancho), gps(
                    obtenerLatitud(esq2) + (n-i)*alto, obtenerLongitud(esq2)-(m-j)*ancho), nombre (i,j)));
        }
    }

    return resp;
}

/*La complejidad del algoritmo es de O(nxm), ya que en el peor caso el for de la linea 142 itera 4n veces, y a su vez
 * cada una de las iteraciones iteran 15m veces, lo que da una complejidad de O(n*m) */


/************************************* EJERCICIO cantidadDeSaltos ******************************/

int Nombre0(nombre n) {
    return get<0>(n);
}

int Nombre1(nombre n) {
    return get<1>(n);
}

gps obtenerEsq1(celda c){
    return get <0>(c);
}

gps obtenerEsq2(celda c){
    return get <1>(c);
}

nombre obtenerNombre(celda c){
    return get<2>(c);
}

int distanciaEntreCeldas(nombre n1, nombre n2){
    int res= sqrt(pow((Nombre0(n1)- Nombre0(n2)),2)+ pow((Nombre1(n1)- Nombre1(n2)),2));
    return res;
}

bool estaEnCelda(celda c, gps g){
    if(obtenerLatitud(obtenerEsq1(c)) >= obtenerLatitud(g) && obtenerLongitud(obtenerEsq1(c))<= obtenerLongitud(g)){
        if(obtenerLatitud(obtenerEsq2(c))< obtenerLatitud(g) && obtenerLongitud(obtenerEsq2(c))> obtenerLongitud(g)){
            return true;
        }
    }
    return false;
}

nombre nombreDe(tuple<tiempo, gps> t, grilla g){
    for(int i=0; i<g.size(); i++){
        if(estaEnCelda(g[i], obtenerPosicion(t))){
            return obtenerNombre(g[i]);
        }
    }
}

vector<nombre> secuenciaDeNombres(grilla g, viaje v){
    vector<nombre> n={};
    for(int i=0; i<v.size(); i++){
        n.push_back(nombreDe(v[i],g));
    }
    return n;
}

int cantidadDeSaltos(grilla g, viaje v) {
    int resp=0;
    ordenarViaje(v);
    vector<nombre> N=secuenciaDeNombres(g,v);
    for(int i=1; i<N.size(); i++){
        if(distanciaEntreCeldas(N[i-1], N[i])>1){
            resp=resp+1;
        }
    }
    return resp;
}


/************************************* EJERCICIO corregirViaje ******************************/

bool estaEnErrores(viaje v, int i, vector<tiempo> errores){
    for(int j=0; j<errores.size(); j++){
        if(obtenerTiempo(v[i])==errores[j]){
            return true;
        }
    }
    return false;
}

tuple<tiempo, gps> tuplaDeTiempoMaximo(viaje v){
    ordenarViaje(v);
    return v[v.size()-1];
}


vector< tuple<tiempo, gps> > tiemposMasCercanos(viaje v, int i, vector<tiempo> errores){
    tuple<tiempo, gps> masCercano1= tuplaDeTiempoMaximo(v); //tomamos el tiempo maximo ya que todas las diferencias de tiempos van a ser menores
    tuple<tiempo, gps> masCercano2= tuplaDeTiempoMaximo(v);
    vector<tuple<tiempo, gps>> vectorTiempos={};
    double menorDiferencia= obtenerTiempo(tuplaDeTiempoMaximo(v));
    int j=0;
    int k=0;
    int indiceMasCercano;
    while(j<v.size()){
        if(abs(obtenerTiempo(v[i])- obtenerTiempo(v[j])) < menorDiferencia && j!=i && not estaEnErrores(v,j,errores)){
            masCercano1 = v[j];
            menorDiferencia= abs(obtenerTiempo(v[i])- obtenerTiempo(v[j]));
            indiceMasCercano = j;
        }
        j++;
    }
    menorDiferencia= obtenerTiempo(v[v.size()-1]);
    while(k<v.size()) {
        if (abs(obtenerTiempo(v[i]) - obtenerTiempo(v[k])) < menorDiferencia && k!=i && k!=indiceMasCercano && not estaEnErrores(v,k,errores)) {
            masCercano2 = v[k];
            menorDiferencia= abs(obtenerTiempo(v[i])- obtenerTiempo(v[k]));
        }
        k++;
    }
    vectorTiempos.push_back(masCercano1);
    vectorTiempos.push_back(masCercano2);
    return vectorTiempos;

}

gps diferenciaPosiciones(tuple<tiempo, gps> m, tuple<tiempo, gps> n){ //Esto debido a que no podemos restar tuplas en c++
    gps diferencia;
    get<0>(diferencia)=(obtenerLatitud(obtenerPosicion(m))-obtenerLatitud(obtenerPosicion(n)));
    get<1>(diferencia)=(obtenerLongitud(obtenerPosicion(m))-obtenerLongitud(obtenerPosicion(n)));
    return diferencia;

}

double latitudDeCorregido(viaje v, int i, tuple<tiempo, gps> masCercano1, tuple<tiempo, gps> masCercano2){
    double res=obtenerLatitud(obtenerPosicion(masCercano2))+ ((obtenerTiempo(v[i])- obtenerTiempo(masCercano2))*obtenerLatitud(diferenciaPosiciones(masCercano1,masCercano2)))/(obtenerTiempo(masCercano1)- obtenerTiempo(masCercano2));
    return res;

}

double longitudDeCorregido(viaje v, int i, tuple<tiempo, gps> masCercano1, tuple<tiempo, gps> masCercano2){
    double res = obtenerLongitud(obtenerPosicion(masCercano2))+ ((obtenerTiempo(v[i])- obtenerTiempo(masCercano2))*obtenerLongitud(diferenciaPosiciones(masCercano1,masCercano2)))/(obtenerTiempo(masCercano1)- obtenerTiempo(masCercano2));
    return res;
}

tuple<tiempo, gps> gpsCorregido(viaje v, int i, vector<tiempo> errores){
    tuple<tiempo, gps> masCercano1=tiemposMasCercanos(v, i, errores)[0];
    tuple<tiempo, gps> masCercano2=tiemposMasCercanos(v, i, errores)[1];
    if(obtenerTiempo(masCercano1)> obtenerTiempo(masCercano2)){ //swapeo asi me quedan el menor y el mayor respectivamente
        tuple<tiempo, gps> aux;
        aux=masCercano1;
        masCercano1=masCercano2;
        masCercano2=aux;
    }
    tuple<tiempo, gps> corregido;
    get<0>(get<1>(corregido))=latitudDeCorregido(v, i, masCercano1, masCercano2);
    get<1>(get<1>(corregido))=longitudDeCorregido(v, i, masCercano1, masCercano2);
    get<0>(corregido)= obtenerTiempo(v[i]);
    return corregido;
}

void corregirViaje(viaje& v, vector<tiempo> errores){
    for(int i=0; i<v.size(); i++){
        if(estaEnErrores(v, i, errores)){
            v[i]= gpsCorregido(v, i, errores);
        }
    }

    return;
}