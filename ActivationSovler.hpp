#ifndef ActivationSolver_H
#define ActivationSolver_H
#include "IOSolver.h"
#include <stdio.h>

namespace CAL{
	double * featuremap = new double[layerNeuron*32*60000];
	double * newInput = new double[layerNeuron*60000];
	int inputSize;
	
	void * layerCal()(int * weight, int b, int e, int * input){
		for( int j = 0; j<layerNeuron ; j++){
				int base_j = j*32;
				for( int k = 0; k<32 ; k++){
					for( int s = 0 ; s<60000 ; s++){
						featuremap[] = weight[base_i+base_j+k]*input[inputSize-];
					}					
				}
		}
	}
	
	
	
	
	
	
	void * reluInference( int numofLayers, int layerNeuron, int numweightStruct * weight , inputStruct * input , double * bias ){
		inputSize = sizeof(input)-1;
		
		for( int i = 0 ; i< numofLayers ; i++){
			int b = i*layerNeuron*32;
			int e = (i+1)*layerNeuron*32-1;
			
			input = layerCal(weight, input, b , e );			
		}		
	}
}
#endif