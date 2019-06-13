#ifndef ActivationSolver_H
#define ActivationSolver_H
#include <stdio.h>
#include "runSparseDNNchallenge.h"

namespace CAL{
	double bias;
	
	double * layerCalWritebased(READ::weightStruct * weight, int b, int layerNeuron , double * input){
		
		double * newInput = new double[layerNeuron];
		
		for( int j = 0; j<layerNeuron ; j++){
			int base_j = j*32;
			for( int k = 0; k<32 ; k++){
				newInput[j] += input[weight[b+base_j+k].index_i] * 0.0625;				
			}
			
			newInput[j] += bias;
			if(newInput[j]<0) newInput[j]=0;		
		}
		return newInput;
	}
	
	double * layerCalReadbased(READ::weightStruct * weight, int b, int layerNeuron , double * input){
		
		double * newInput = new double[layerNeuron];
		
		for( int j = 0; j<layerNeuron ; j++){
			int base_j = j*32;
			for( int k = 0; k<32 ; k++){
				newInput[weight[base_j+k].index_j] += input[j] * 0.0625;				
			}
			
			newInput[j] += bias;
			if(newInput[j]<0) newInput[j]=0;		
		}
		return newInput;
	}
	
	
	
	void reluInference( int numofLayers, int layerNeuron, READ::weightStruct * weight , double * sample , double biasValue ){
		bias = biasValue;	
		
		for( int i = 0 ; i< numofLayers ; i++){
			int b = i*layerNeuron*32;	
			//sample = layerCalWritebased(weight , b , layerNeuron , sample );
			//要记得对权重按index_i进行排序
			sample = layerCalReadbased(weight , b , layerNeuron , sample );		
		}	
	}
}
#endif