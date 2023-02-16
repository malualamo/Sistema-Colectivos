#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

TEST(distanciaTotalTESTGP, viajeDesordenado){
    gps p1 = puntoGps(-33, -34);
    gps p2 = desviarPunto(p1, 500, 2000);
    gps p3 = desviarPunto(p2, 350, 2000);
    gps p4 = desviarPunto(p3, 1500, 185);
    gps p5 = desviarPunto(p4, 270, 1500);

    viaje v = {medicion(1.6, p2),
               medicion(1.5, p1),
               medicion(1.7, p3),
               medicion(1.9, p4),
               medicion(1.2, p5)};

    EXPECT_NEAR(distanciaTotal(v), 11.86, 0.01);
}
