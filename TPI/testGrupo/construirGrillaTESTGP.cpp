#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;//

const float epsilon = 0.000001;

bool isClose(double x, double y) {
    return abs(x - y) < epsilon;
}

bool sonGPS1Iguales(celda c1, celda c2) {
    if (isClose(get<0>(get<0>(c1)),get<0>(get<0>(c2)))) {
        if (isClose(get<1>(get<0>(c1)),get<1>(get<0>(c2)))) {
            return true;
        }
    }
    return false;
}

bool sonGPS2Iguales(celda c1, celda c2) {
    if (isClose(get<0>(get<0>(c1)),get<0>(get<0>(c2)))) {
        if (isClose(get<1>(get<0>(c1)),get<1>(get<0>(c2)))) {
            return true;
        }
    }
    return false;
}


bool sonNombresIguales(celda c1, celda c2){
    if(get<0>(get<2>(c1))==get<0>(get<2>(c2))){
        if(get<1>(get<2>(c1))==get<1>(get<2>(c2))){
            return true;
        }
    }
    return false;
}

bool sonGrillasIguales(grilla g1, grilla g2){
    int c=0;
    if(g1.size()==g2.size()){
        for(int i=0; i<g1.size(); i++){
            for(int j=0; j<g2.size(); j++){
                if(sonGPS1Iguales(g1[i],g2[j]) && sonGPS2Iguales(g1[i],g2[j]) && sonNombresIguales(g1[i],g2[j])){
                    c=c+1;
                }
            }
        }
    }
    return c==g1.size();
}

TEST(construirGrillaTESTGP, grillasIguales){

    int n = 4;
    int m = 2;

    gps esq1 = puntoGps(0,0);
    gps esq2 = puntoGps(-52,52);

    grilla gres = {make_tuple(puntoGps(0,26), puntoGps(-13,52), make_tuple(1,2)), //estan desordenadas solo para ver si funcionaba
                   make_tuple(puntoGps(-13,0), puntoGps(-26,26), make_tuple(2,1)),
                   make_tuple(puntoGps(-39,0), puntoGps(-52,26), make_tuple(4,1)),
                   make_tuple(puntoGps(-13,26), puntoGps(-26,52), make_tuple(2,2)),
                   make_tuple(puntoGps(-26,0), puntoGps(-39,26), make_tuple(3,1)),
                   make_tuple(puntoGps(-26,26), puntoGps(-39,52), make_tuple(3,2)),
                   make_tuple(puntoGps(-39,26), puntoGps(-52,52), make_tuple(4,2)),
                   make_tuple(puntoGps(0,0), puntoGps(-13,26), make_tuple(1,1))
    };


    grilla g = construirGrilla(esq1,esq2,n,m);

    EXPECT_TRUE(sonGrillasIguales(gres, g));
}

TEST(construirGrillaTESTGP, grillasDistintas){
    int n = 4;
    int m = 2;

    gps esq1 = puntoGps(0,0);
    gps esq2 = puntoGps(-52,52);

    grilla gres = construirGrilla(esq1, esq2, 5, 10);


    grilla g = construirGrilla(esq1,esq2,n,m);

    EXPECT_FALSE(sonGrillasIguales(gres, g));

}