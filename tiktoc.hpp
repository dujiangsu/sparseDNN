#include<ctime>
#include <stdlib.h>
#include <stdio.h>
#ifndef WATCH_H
#define WATCH_H

clock_t st , en ; 
void tik() {
	st = clock() ;

}
void toc() {
	en = clock() ; 
	printf("%.3lf s\n",double(en-st)/1000000) ; 
}
#endif
