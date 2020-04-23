#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#define N 3


int minElement(double* array, size_t size){
  int min = array[0];
  int index = 0;
  for (size_t i = 1; i < size; ++i) {
    if (min > array[i]) {
      min = array[i];
      index = i;
    }
  }
  return index;
}

double fE(double input[N]){
  double output=0;
  output = (input[0] - 20) * (input[0] -20)+ (input[1] -5)*( input[1] -5) + (input[2]-2.6)*(input[2]-2.6);
  return output;
}


//void grad_descent(double init[N], double *answer){
void grad_descent(double M_org[N], double* M){
  double dEdM[N]={0};
  double err=100;
  double Msize[N];

  while(err>0.00000001){
    double E_pre  = fE(M_org);
    for(int i=0;i<N;i++){
      double tmp_M = M_org[i];
      double E_cand[3] = {0};
      double delta[3] = {0};
      for(int dm = -1; dm<2;dm++){
        M[i] = tmp_M + dm*0.001;
        E_cand[dm+1] = fE(M);
        delta[dm+1] = (E_cand[dm+1] - E_pre);
      }
      int index = minElement(delta,3);
      dEdM[i] = -delta[index];
      M[i]=tmp_M;
      std::cout<<"minindex and delta"<<index<<","<<delta[index]<<"\n";
    }
    err=0;
    for(int j=0;j<N;j++){
      M[j] = M_org[j]+dEdM[j];
      err+=(dEdM[j])*(dEdM[j])/2.0;
      std::cout<<"M,"<<M[j]<<",";
    }
    std::cout<<"err:"<<err<<std::endl;
    memcpy(M_org,M,sizeof(Msize));
  }
}

int main(void){
  double M_org[N] = {20,5,3};
  double M[N];
  memcpy(M,M_org,sizeof(M_org));

  grad_descent(M_org, M);
  
  for(int j=0;j<N;j++){
    std::cout<<"M,"<<M[j]<<",";
  }
  std::cout<<"\n";
}
