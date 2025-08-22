
//Implementacion de las funciones del header "funciones.h" 

#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>

int printFunction(void){
    printf("**********************************\n");
    printf("*  Calculadora de Masa Corporal  *\n");
    printf("**********************************\n");
    return 0;
}

float imcFunction(float masa, float altura){
    float IMC;
    IMC = masa / (altura * altura);
    return IMC;
}

void impMatrix(float mA, int N){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            printf(" %f ", mA);
        }
        printf("\n");
    }
}

float matrixMult(int N, float mA, float mB){
    float mC;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            for(int k = 0; k < N; k++){
                mC += mA * mB;
		}
	}
}
    return mC;
}

void llenarMatriz(int N, float mA, float mB){
	for(int i = 0; i<N; i++){
		for(int j;j<N;j++){
			mA = rand()%100*0.121;
			mB = rand()%100;
		}
	}
}