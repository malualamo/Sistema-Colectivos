#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"
#include "recorridoNoCubiertoTESTGP.h"

using namespace std;

const gps P = puntoGps(-31.465027, -64.212973);
const recorrido R = {P,
                     desviarPunto(P, 1000, 0),
                     desviarPunto(P, 2000, 0),
                     desviarPunto(P, 3000, 0),
                     desviarPunto(P, 4000, 0),
                     desviarPunto(P, 5000, 0),
                     desviarPunto(P, 6000, 0),
                     desviarPunto(P, 7000, 0),
                     desviarPunto(P, 8000, 0),
                     desviarPunto(P, 9000, 0),
};

TEST(recorridoNoCubiertoTEST, viajeCompletamenteImperfecto){
    viaje v = {};
    vector<int> desvios(R.size(), 0);
    desvios[0] = 390;
    desvios[1] = 30;
    desvios[2] = -190;
    desvios[3] = -390;
    desvios[4] = 390;
    desvios[5] = 30;
    desvios[6] = -190;
    desvios[7] = -390;
    desvios[8] = -190;

    for(int i = 0; i < R.size(); i++){
        v.push_back(medicion(i, desviarPunto(R[i], 0, desvios[i])));
    }

    vector<gps> res = recorridoNoCubierto(v, R, 0.1);
    EXPECT_EQ(res.size(), 7);
    ASSERT_ELEMENTS(res, {R[3], R[0], R[2]});

}