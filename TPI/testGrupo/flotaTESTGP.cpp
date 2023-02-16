#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

vector<viaje> F1 = {{
                           medicion(5.5,puntoGps(2.5, 2.89996)),
                           medicion(6.7,puntoGps(2.5, 2.89997)),
                           medicion(4.9,puntoGps(2.5, 2.89998))},
                   {
                           medicion(5.3,puntoGps(2.5, 2.89996)),
                           medicion(7.6,puntoGps(2.5, 2.89997)),
                           medicion(4.7,puntoGps(2.5, 2.89998))},
                   {
                           medicion(5.7,puntoGps(2.5, 2.89996)),
                           medicion(6.6,puntoGps(2.5, 2.89997)),
                           medicion(4.6,puntoGps(2.5, 2.89998))},

                   {
                           medicion(6.5,puntoGps(2.5, 2.89996)),
                           medicion(8.6,puntoGps(2.5, 2.89997)),
                           medicion(4.7,puntoGps(2.5, 2.89998))},
};

TEST(flotaTotalTEST, todosDespuesDeFranja){
EXPECT_EQ(flota(F1,3.0,4.5),0);
}

TEST(flotaTotalTEST, todosDentro){
EXPECT_EQ(flota(F1,5.0,8.5),4);
}
