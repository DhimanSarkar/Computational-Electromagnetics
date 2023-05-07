/*
#############################################################################################
#                            Computational Electromagnetics                                 #
#  Implementation of Method of Moment (MoM) to solve Electrostatic Lince Charge Problem     #
#############################################################################################
*/

#include<iostream>
#include "Eigen/Eigen"

int main(){
    std::system("cls"); //console>cls
  
    const int N = 100;       //No of elements
    float L = 2;            //Length of wire
    float delX = L/N;       //Grid length

    float eps0 = 8.8541878128e-12;  //Vacume permitivity
    float eps = 1;                  //Relative Permitivity of the Material
    float r = 0.0001;               //Radius of the wire

    Eigen::Matrix<double,N,1> B;    //Defining Solution matrix "B" of AX=B
    B.setConstant(4*3.14*eps0*eps); //fill all the elements with 4*pi*Epsilon

    Eigen::Matrix<double,N,N> A;    //Defining Solution matrix "A" of AX=B
A.setOnes();                        //Init
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            int m=i+1; //CPP index -> Matrix index
            int n=j+1; //CPP index -> Matrix index
            float x_i = (m-0.5)*delX; //locations of Testing Function (In this case, middle of every node)
            A(i,j) = std::log(std::abs((n*delX - x_i + std::sqrt(std::pow((n*delX - x_i),2)+r*r))/((n-1)*delX - x_i + std::sqrt(std::pow(((n-1)*delX - x_i),2)+r*r))));
        }
    }
    
    Eigen::Matrix<double,N,N> A_inv;
    A_inv = A.inverse();

    Eigen::Matrix<double,N,1> X;    //Defining Solution matrix "X" of AX=B
    X = A_inv * B;                  //Solving for "X" in AX+B

    std::cout<<X<<std::endl;

    return 0;
    }