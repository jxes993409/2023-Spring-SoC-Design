#ifndef __FIR_H__
#define __FIR_H__

#define N 11
#define SIZE 10

int taps[N] = {0,-10,-9,23,56,63,56,23,-9,-10,0};
int inputbuffer[N];
int inputsignal[SIZE];
int outputsignal[SIZE];
#endif
