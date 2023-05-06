#include<iostream>
#include "Fastor/Fastor.h"

int main(){
    std::system("cls"); // Clear Previous Output Screen
    std::cout<<"MoM"<<std::endl;
    
    const int N = 5;        //No of elements
    float L = 2;         //Length of wire
    float delX = L/N;  //Grid length

    float eps0 = 8.8541878128e-12; //Vacume permitivity
    float eps = 1;                  //Relative Permitivity of the Material
    float r = 0.0001;               //Radius of the wire

    Fastor::Tensor<float,N,1> B;   //Defining Solution matrix "B" of AX=B
    B.fill(4*3.14*eps0*eps);        //fill all the elements with 2.5

    Fastor::Tensor<float,N,N> A;   //Defining Solution matrix "A" of AX=B
    A.ones();                       // fill all the elements with 2.5
    int i,j;
    i=j=0;
    for(i=0; i<N; i++)
    {
        for (j=0; j<N; j++)
        {
            int m=i+1; //CPP index -> Matrix index
            int n=j+1; //CPP index -> Matrix index
            float x_i = (m-0.5)*delX; //locations of Testing Function (In this case, middle of every node)
            A(i,j) = std::log(std::abs((n*delX - x_i + std::sqrt(std::pow((n*delX - x_i),2)+r*r))/((n-1)*delX - x_i + std::sqrt(std::pow(((n-1)*delX - x_i),2)+r*r))));
        }    
    }

    Fastor::Tensor<float,N> X = Fastor::solve(A,B);    //Solving for "X" in AX+B
    Fastor::print(X);

    return 0;
}