/*
################################################################################################################
#                                        Computational Electromagnetics                                        #
#  Implementation of Finite Difference Time Domain (FDTD) to solve Electrodynamic Wave Propagation Problem     #
################################################################################################################
*/

#include<iostream>
#include<fstream>
#include<vector>

const double L = 1;      // Length of space (m)
const int T = 1;      // Time Duration (s)
const int t_max = 5;  // Maximum Cycles of Time Evaluation
const double vp = 3e8;        //Phase Velocity
const double freq = 1e9;      // Source Frequency (Hz)
const double lamb = 0.3;       // Source Wavelength (m)
const double eps0 = 1;        //Vacume Permitivity
const double mu0 = 1;         // Vacume Permeability


class Field {
    public:
        // Set number of nodes
        int setN(int i)
        {
            N = i;
            initField();
            std::cout<< "E001\t" << F.at(2) <<std::endl;
            return 0;            
        }

        // View whole field
        int view()
        {
            //std::cout<< "[";
             for (const int& i : F) {
                std::cout << i << "\t\t";
             }
            //std::cout<< "]";
            std::cout<< std::endl;
            return 0;
        }

        // Update Field
        int updateSpace(Field pastE1, Field E2)
        {
            setBoundary(); // Update the boundary values
            for (int i = 1; i < (N-1)-1; i++) // Update internal fields
            {
                F.at(i) = pastE1.at(i) + dFact*(E2.at(i)-E2.at(i-1));
            }
            return 0;
        }

        // Pull values of the field
        int at(int i)
        {
            return F.at(i);
        }
        int len()
        {
            return F.size();
        }

        // Set Boundary Conditions
        int setBoundary()
        {
            F.at(0)    = 0; // First Node
            F.at(N-1)  = 0; // Last Node
            return 0;
        }

        // Set Source
        int setupSource(int loc, const char *node)
        {
            if (node == "intNode")
            {
                F.at(loc) = 6.652;
                std::cout << (int)(lamb/delX) << "setUpsource\n";
                for (int i = 1; i < (int)(lamb/delX); i++)
                {
                    F.at(loc+i) = F.at(loc-i) = sin(2*3.141519/lamb * i*delX);
                    std::cout<< sin(2*3.141519/lamb * i*delX) << "\n\n";
                }
                
            }
            else
            {

            }
            
            return 0;
        }

    private:
        int N;  // Number of nodes
        double delX;     // Space Grid Size
        double delT;     // For no Disparsion, delT/delX = c

        std::vector<double> F;

        double dFact = 1; //Disparsion Factor

        // Initialize Field Vector with 0;
        int initField()
        {
            delX = L/N;
            delT = vp/delX;
            for (int i = 0; i < N; i++)
            {
                F.push_back((double)-01.05655);
            }
            return 0;
        }     

        // Pull values of the field
        double &setAt(int i)
        {
            return F.at(i);
        }
};


class Data {
    public:
        Data(const char *str)
        {
            filename = str;
            file.open(filename);
        }
        ~Data()
        {
            file.close();
        }
        void write(Field F)
        {
            for (int i = 0; i < F.len(); i++)
            {
                file << F.at(i) << "\t";
            }
            file << std::endl;
        }
    private:
        const char *filename;
        std::ofstream file;

};



int main(int argc, char *argv[]){
    std::system("cls"); //console>cls
    
    int N = 3;             // Total Nodes

    // Instances of Field Vectors
    Field pastE; Field E;
    Field pastH; Field H;

    Data fieldE("fieldE.txt"); 
    Data fieldH("fieldH.txt");
    
    // Initilizing Field Vectors
    pastE.setN(N); E.setN(N);
    pastH.setN(N); H.setN(N);

    std::cout<< "E000\t" << pastE.at(2) <<std::endl;

    // Setup Source
    pastE.setupSource(N/2,"intNode");
    //pastH.setupSource(N/2,"frcNode");

    //
    fieldE.write(pastE);
    fieldH.write(pastH);
    std::cout<< "E0\t";         pastE.view();
    std::cout<< "H0\t\t";       pastH.view();

    // Time evolution
    for (int t = 0; t < t_max; t++)
    {
        E.updateSpace(pastE,pastH);
        pastE = E;
        H.updateSpace(pastH,pastE);
        pastH = H;

        fieldE.write(E);
        fieldH.write(H);
        std::cout<< "E"<< t+1 <<"\t";      E.view();
        std::cout<< "H"<< t+1 <<"\t\t";    H.view();
    }
    
    return 0;
    }
