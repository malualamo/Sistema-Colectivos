#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(distanciaTotalTEST, viajeDesordenado){
    gps p1 = puntoGps(-33, -34);
    gps p2 = desviarPunto(p1, 2000, 0);
    gps p3 = desviarPunto(p2, 2000, 0);

    viaje v = {medicion(1.6, p2),
               medicion(1.5, p1),
               medicion(1.7, p3)};

    EXPECT_NEAR(distanciaTotal(v), 4.0, 0.01);
}

TEST(distanciaTotalTEST, viajeParado){
    gps p1 = puntoGps(-33, -34);

    viaje v = {medicion(1.1, p1),
               medicion(1.5, p1),
               medicion(1.2, p1),
               medicion(1.9, p1)};
    EXPECT_DOUBLE_EQ(distanciaTotal(v),0.0);
}

TEST(distanciaTotalTEST, viajeLargo){
    gps p1 = puntoGps(-33, -34);
    gps p2 = desviarPunto(p1, 2000, 0);
    gps p3 = desviarPunto(p2, 0, 2000);
    gps p4 = desviarPunto(p3, 3000,4000);
    gps p5 = desviarPunto(p4, 3000,4000);
    gps p6 = desviarPunto(p5, 4000,3000);
    gps p7 = desviarPunto(p6, 3000,4000);


    viaje v = {medicion(1, p1),
               medicion(3, p3),
               medicion(7, p7),
               medicion(2, p2),
               medicion(6, p6),
               medicion(5, p5),
               medicion(4, p4)};
    EXPECT_NEAR(distanciaTotal(v), 24.0, 0.01);
}