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

/************++*********************** EJERCICIO distanciaTotal ************++*********************/
void swap(int a, int b){
    a=a+b;
    b=a-b;
    a=b-a;
}

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
    distancia d;
    ordenarViaje(v);
    for(int i=0; i<v.size()-1; i++){
        d = d + distEnKM(obtenerPosicion(v[i]), obtenerPosicion(v[i+1]));
    }

    return d;
}

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
    for(int i=0; i<r.size(); i++){
        int contador=0;
        for(int j=0; j<v.size(); j++){
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
float anchoCelda(gps esq1, gps esq2, int m){
    return (obtenerLongitud(esq2)- obtenerLongitud(esq1))/m;
}

float altoCelda(gps esq1, gps esq2, int n){
    return (obtenerLatitud(esq1)- obtenerLatitud(esq2))/n;
}

grilla construirGrilla(gps esq1, gps esq2, int n, int m) {
    grilla resp = {};
    float ancho= anchoCelda(esq1, esq2, m);
    float alto= altoCelda(esq1, esq2, n);
    for (int i=1; i<=n; i++){
        for(int j=1; j<=m; j++){
            resp.push_back(celda (gps (obtenerLatitud(esq1)-(i-1)*alto, obtenerLongitud(esq1)+(j-1)*ancho), gps(
                    obtenerLatitud(esq2) + (n-i)*alto, obtenerLongitud(esq2)-(m-j)*ancho), nombre (i,j)));
        }
    }

    return resp;
}

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
void corregirViaje(viaje& v, vector<tiempo> errores){


    return;
}
