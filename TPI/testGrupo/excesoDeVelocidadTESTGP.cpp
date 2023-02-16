#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

using namespace std;

const gps P = puntoGps(-33.5, -58.89996);
const double unaHora = 3600;

TEST(excesoDeVelocidadTEST, noSuperaLaVelocidadGP){
    viaje v = {medicion(0.0, P),
               medicion(unaHora, desviarPunto(P, 500, 0)),
               medicion(unaHora*2, desviarPunto(P, 1700, 0))}; // 1 KM por hora.

    EXPECT_FALSE(excesoDeVelocidad(v));
}