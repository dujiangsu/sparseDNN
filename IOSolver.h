#ifndef IOSolver_H
#define IOSolver_H
namespace READ{ 
	struct weightStruct{
		int index_i;
		int index_j;
		double value;
	};	
	struct inputStruct{
		int index, prev;
		double value;
	};	
	int readint( int &i );
	double readdouble( int &i );
	char * readFile(char * filename);
	void rankWeight(int numofLayers, int layerNeuron, weightStruct * weight);
	void quick_sort(weightStruct * weight, int b, int e);
	void weightSwap( weightStruct * addr1 , weightStruct * addr2 );
	void readWeight(int numofLayers, int layerNeuron, weightStruct * &weight);
	void readInput(int numofLayers, int layerNeuron, inputStruct * &input);
}
#endif