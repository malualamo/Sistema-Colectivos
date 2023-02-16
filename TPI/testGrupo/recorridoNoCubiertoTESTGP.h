//
// Created by Jeremias on 9/6/2022.
//

#ifndef TPI_RECORRIDONOCUBIERTOTESTGP_H
#define TPI_RECORRIDONOCUBIERTOTESTGP_H

#endif //TPI_RECORRIDONOCUBIERTOTESTGP_H

#include "../ejercicios.h"
#include "../auxiliares.h"
#include "gtest/gtest.h"

template<typename T>
bool included(T elem, vector<T> container){
    for (int i = 0; i < container.size(); ++i) {
        if (container[i] == elem){return true;}
    }
    return false;
}

template<typename T>
void ASSERT_ELEMENTS(vector<T> container, vector<T> elems) {
    for(int i = 0; i < elems.size(); i++ ) {
        ASSERT_TRUE(included(elems[i], container));
    }

}