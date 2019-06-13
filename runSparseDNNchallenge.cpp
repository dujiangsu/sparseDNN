#include <stdlib.h>
#include <stdio.h>
#include <string> 
#include <boost/algorithm/string.hpp>
#include "ActivationSolver.hpp"
#include "tiktoc.hpp"

using namespace std;



namespace READ{
	//由于特性，是固定的每隔32个

	
	int size ; 
	int inx[10] ;
	int head[60000];
	char* readFile(char * filename){
		//Read in using CSR format			
		FILE * pFile;
		char * buffer;
		size_t result;
		pFile = fopen(filename, "r");
		if (pFile==NULL) {fputs ("File error",stderr); exit (1);}
		fseek (pFile , 0 , SEEK_END);
		size = ftell (pFile);

		rewind (pFile);
		buffer = (char*) malloc (sizeof(char)*size);
		if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}
		result = fread (buffer,1,size,pFile);
		if (result != size) {fputs ("Reading error",stderr); exit (3);}
		//printf("%s\n",buffer);
		fclose(pFile); 
		return buffer;
	}
	
	void weightSwap( weightStruct * addr1 , weightStruct * addr2 ){
		weightStruct temp;
		temp.index_i = (*addr1).index_i;
		temp.index_j = (*addr1).index_j;
		temp.value = (*addr1).value;
		(*addr1).index_i = (*addr2).index_i;
		(*addr1).index_j = (*addr2).index_j;
		(*addr1).value = (*addr2).value;
		(*addr2).index_i = temp.index_i;
		(*addr2).index_j = temp.index_j;
		(*addr2).value = temp.value;		
	}
	
	void quick_sort(weightStruct * weight, int b, int e)
	{
		if (b < e - 1) {
			int lb = b, rb = e - 1;
			while (lb < rb) {
				while (weight[rb].index_i >= weight[b].index_i && lb < rb)
					rb--;
				while (weight[lb].index_i <= weight[b].index_i && lb < rb)
				lb++;				
				weightSwap(&weight[lb], &weight[rb]);				
			}
			weightSwap(&weight[b], &weight[lb]);
			quick_sort(weight, b, lb);
			quick_sort(weight, lb + 1, e);
		}
	}
	
	

	void rankWeight(int numofLayers, int layerNeuron, weightStruct * weight){
		for(int i = 0; i<numofLayers ; i++){
			quick_sort( weight, i*layerNeuron*32, (i+1)*layerNeuron*32-1);
			printf("%d th/ed/rd layer has been sorted\n", i+1);			
			/* for(int j = 0; j<1000 ; j++){
				printf("%d-------%d\n",weight[j].index_i,weight[j].index_j);
			} */			
		}
	}
	
	
	
	int readint( int &i, char * buffer){
			int ret = 0 ; 
			for( ; buffer[i]>'9' || buffer[i]<'0' ; i++ ) ; 
			for( ; buffer[i]<='9' && buffer[i]>='0' ; ++i ) ret *= 10 , ret += buffer[i]-'0' ; 
			return ret ; 
	}

	double readdouble( int &i, char * buffer ) {
			double ret = 0 ; 
			//int cnt = -10000 ; 
			//for( ; buffer[i]>'9' || buffer[i]<'0' ; i++ ) ; 
			//for( ; ( buffer[i] <='9' && buffer[i] >= '0' )||(buffer[i]=='.') ; i++ ) 
			//	if( buffer[i] =='.' ) cnt = 0 ; 
			//		else cnt ++ , ret = ret * 10 + buffer[i]-'0' ; 
			//if( cnt > 0 )ret /= inx[cnt] ;
			while(buffer[i]!='\n')i++;
			return ret ; 
					
	}
	
	
	void readWeight(int numofLayers, int layerNeuron, weightStruct * &weight){
		weight = new weightStruct[32*numofLayers*layerNeuron];
		weightStruct * write = weight;
		int filenum;
		char * buffer;
		
		for( int i = 0 ; i<numofLayers ; i++){
			filenum = i+1; 
			char filename[50];			
			sprintf(filename,"%s%d%s%d%s%d%s%d%s","/home/dujiangsu/dataset/",layerNeuron,"/neuron",layerNeuron,"/n",layerNeuron,"-l",filenum,".tsv");
			printf("%s\n",filename);			
			buffer = readFile(filename);
			
			int ps = 0;
			for( int j = 0; j<32*layerNeuron ; j++){
				(*write).index_i = readint( ps , buffer );
				//printf("%d\n",(*write).index_i);
				(*write).index_j = readint( ps , buffer );
				readdouble( ps , buffer );
				(*write).value = 0.0625;
				++write;
			}			
					
		}
		free(buffer);
		printf("WEIGHT READ COMPLETE.\n");
		
		rankWeight( numofLayers , layerNeuron , weight );
		
		printf("RANKING COMPLETE\n");
	}	
	
	double * dispatch( inputStruct * input, int layerNeuron , int picID ){
		double * sample = new double[layerNeuron];
		std::fill_n(sample, layerNeuron, 0);
		for(int i = head[picID]; i ; i = input[i].prev) sample[input[i].index] = 1;
		return sample;		
	}
	
	void readInput(int numofLayers, int layerNeuron, inputStruct * &input){
		char * buffer;
		char filename[50];
		sprintf(filename,"%s%d%s%d%s","/home/dujiangsu/dataset/",layerNeuron,"/sparse-images-",layerNeuron,".tsv");
		buffer = readFile(filename);
		
		int T = 0 ; 
		for( int i=0 ; i<size ; i++ ) if( buffer[i] == '\n' ) T ++ ;
		
		std::fill_n(head, 60000, 0);
		input = new inputStruct[T];
		inputStruct * write = input;
		
		int ps = 0;
		for( int i = 0; i<T ; i++){
			int r = readint( ps , buffer );
			int c = readint( ps , buffer );
			double w = readdouble( ps , buffer );	
			
			(*write).index = c;	
			(*write).prev = head[r];						
			head[r] = i;						
			(*write).value = w;	
			++write;
		}
		
		free(buffer);
		printf("Input READ COMPLETE.\n");		
	}

}



double neuralNetBias[4] = {-0.3,-0.35,-0.4,-0.45};
double biasValue;
int neuronType[4] = {1024, 4096, 16384, 65536};
int totalNeurons, totalEdges;
int numofLayers, layerNeuron;
	


int main(int argc, char *argv[])
{
	READ::inx[0] = 1;
	for( int i=1 ; i<=7 ; i++ ) READ::inx[i] = READ::inx[i-1]  *  10 ;
	if(argc == 3){
		numofLayers = atoi(argv[1]);
		layerNeuron = neuronType[atoi(argv[2])];
		printf("%d Layers to be run in %d neurons' network.\n",numofLayers,layerNeuron);
	}
	else{
		printf("Wrong arguments numbers\n");
	}
	
	totalNeurons = numofLayers * layerNeuron;
	totalEdges = 32 * totalNeurons;
	biasValue = neuralNetBias[atoi(argv[2])];
	
	READ::inputStruct * input;
	READ::weightStruct * weight;
	
	//double * bias = new double[totalNeurons];
	//std::fill_n(bias, totalNeurons, biasValue);
	
	//Reading
	tik();
	READ::readWeight( numofLayers , layerNeuron , weight );	
	READ::readInput( numofLayers , layerNeuron , input );
	printf("Reading Data Consumed:");
	toc();
	
	tik();
	for(int i = 0; i<10;i++){
		CAL::reluInference( numofLayers, layerNeuron , weight , dispatch( input, layerNeuron , i) , biasValue );
		printf("SAMPLE %d COMPLETE\n",i);
	}
	printf("Calculation Consumed:");
	toc();
	
	//Result Check
	
}

/* 	printf("%f\n",bias[totalNeurons-1]);
	printf("%d\n",indices[32*1024*100]);	
	printf("%d   %d\n", row[0], column[0]);	 */