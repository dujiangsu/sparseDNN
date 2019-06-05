#include <iostream>
#include <chrono>
#include <string>
#include <iomanip>
#include <fstream>   
#include <vector>
#include <sstream>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace chrono;


int readW(int numofLayers, int numofNeuron,int *indics, double *values){
	//Read in using CSR format
	string s1 = "/home/dujiangsu/dataset/";
	string s2 = to_string(numofNeuron);
	//string s3 = to_string(numofNeuron);
	string tmpath = s1+s2+"/neuron"+s2+"/n"+s2+"-l";
	
	//numofLayers+
	for(int i = 0;i<101;i++)
	{
		int it = i+1;
		string filename = tmpath + to_string(it)+".tsv";
		ifstream fs;
		fs.open(filename,ios::in);
		string line,tmp;
		cout<<filename<<endl;
		//string []words;
		vector<string> words;
		int j = 0;
		if(!fs.eof()){
			while(getline(fs,line)){
							
				boost::algorithm::split(words,line,boost::is_any_of("\t"));
				indics[i*numofNeuron*32+j] = stoi(words[0]);
				values[i*numofNeuron*32+j] = atof(words[2].c_str());
				//cout<<values[0]<<endl;
				//while(std::getline(line,tmp,'\t'))   words.push_back(tmp);
				//cout<<words[0];
				j++;
			}
			//cout<<j<<endl;
		}				
		fs.close();
	}
	
	cout<<indics[100*32768]<<endl;
	cout<<values[100*32768]<<endl;
	
	cout<<indics[1*32768+1]<<endl;
	cout<<values[1*32768+1]<<endl;
	
}

double * readI(int numofNeuron,double *input){
	
}

int writeO(){
	
}


int main(int argc, char *argv[])
{
	int numofLayers = 0;
	int numofNeuron = 0;
	//Two arguments in need.
	if(argc == 3){
		numofLayers = atoi(argv[1]);
		numofNeuron = atoi(argv[2]);
		printf("%d Layers to be run in %d neurons' network.\n",numofLayers,numofNeuron);
	}
	else{
		printf("Wrong arguments numbers\n");
	}
	
	//Initialize Memory
	int *indices = (int *)malloc(32*(numofLayers-1)*numofNeuron*sizeof(int));
	double *values = (double *)malloc(32*(numofLayers-1)*numofNeuron*sizeof(double));
	double *input = (double *)malloc(numofNeuron*sizeof(double));
	
	//Read Neurons
	auto start = system_clock::now();
	readW(numofLayers,numofNeuron,indices,values);
	auto end   = system_clock::now();
	auto duration = duration_cast<microseconds>(end - start);
	//Read Input
	//readI(numofNeuron,input);
	//Processing
	
	//Write Output
	
	//Validate the result
	cout <<  "Time Consumed:" 
     << double(duration.count()) * microseconds::period::num / microseconds::period::den 
     << "s" << endl;
    return 0;
}

