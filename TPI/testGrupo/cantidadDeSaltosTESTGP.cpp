#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;


TEST(cantidadDeSaltosTESTGP, saltoEnGrilla){
    grilla g = construirGrilla(puntoGps(0.0,0.0), puntoGps(-52,52), 4, 2);

    gps p1 = puntoGps(-7, 10);
    gps p2 = puntoGps(-8, 12);
    gps p3 = puntoGps(-30, 40);
    gps p4 = puntoGps(-45, 25);
    gps p5 = puntoGps(-20, 18);

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3),
               medicion(1.8, p4),
               medicion(1.9, p5)};

    EXPECT_EQ(cantidadDeSaltos(g,v),2);
}

TEST(cantidadDeSaltosTESTGP, todosSaltosOrdenadosAMano){
    grilla g = construirGrilla(puntoGps(0.0,0.0),puntoGps(-3000,3000), 6, 6);

    gps p1 = puntoGps(0, 0);
    gps p2 = puntoGps(-2000,2000);
    gps p3 = puntoGps(-100,100);

    viaje v = {medicion(1.5, p1),
               medicion(1.6, p2),
               medicion(1.7, p3)};

    int val = cantidadDeSaltos(g,v);
    EXPECT_EQ(val,2);
}
