/*
################################################################################################################
#                                        Computational Electromagnetics                                        #
#  Implementation of Finite Difference Time Domain (FDTD) to solve Electrodynamic Wave Propagation Problem     #
################################################################################################################
*/

#include<iostream>
#include<fstream>
#include<vector>

const double L = 1;     // Length of space (m)
const int T = 1;        // Time Duration (s)
const double vp = 3e8;  //Phase Velocity
const double freq = 1e9;// Source Frequency (Hz)
const double lamb = 0.3;// Source Wavelength (m)
const double eps0 = 0;  //Vacume Permitivity
const double mu0 = 0;   // Vacume Permeability


class Field {
    public:
        // Set number of nodes
        int setN(int i, const char *str)
        {
            if (str == "intNode")
            {
                N=i;
            }
            else
            {
                N=i-1;
            }
            nodeType = str;
            initField();
            return 0;            
        }

        // View whole field
        int view()
        {
             for (const double& i : F) {
                std::cout << i << "\t";
             }
            std::cout<< std::endl;
            return 0;
        }

        // Update Field
        int updateSpace(Field D)
        {
            if (nodeType == "intNode")
            { 
                for (int i = 1; i < N-1; i++) // Update internal fields
                {
                    F.at(i) = F.at(i) + dFact*(D.at(i-1)-D.at(i));
                }
            }
            else // fracNode
            {
                for (int i = 0; i < N-1; i++) // Update internal fields
                {
                    F.at(i) = F.at(i) + dFact*(D.at(i)-D.at(i+1));
                }
            }

            return 0;
        }

                // Set Source
        int setupSource(int loc, int time, const char *node) // Field Values at time=0
        {
            if (node == "intNode")
            {
                F.at(loc) = sin(2*3.141519*freq * (time*delT));
                F.at(loc) = exp(-.5*(time/8)*(time/8));
                //F.at(loc) = 1;
            }
            else
            {
                std::cout << "Excitation for fractional nodes not available!";
            }
            
            return 0;
        }

        // Pull values of the field
        double at(int i)
        {
            return F.at(i);
        }
        int len()
        {
            return F.size();
        }

        // Set Boundary Conditions
        int setBoundary(const char *material)
        {
            if (material == "PEC")
            {
                F.at(0)    = 0; // First Node
                F.at(N-1)  = 0; // Last Node
            }
            else std::cout << "Only PEC available!";
            return 0;
        }

    private:
        int N;          // Number of nodes
        double delX;    // Space Grid Size
        double delT;    // For no Disparsion, delT/delX = c
        double dFact;   //Disparsion Factor
        const char *nodeType; //Integer/Fraction type node
        std::vector<double> F;

        // Initialize Field Vector with 0;
        int initField()
        {
            delX = L/N;
            delT = vp/delX;
            dFact = 0.5;
            
            for (int i = 0; i < N; i++)
            {
                F.push_back((double)0.0);
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
    
    int N = 100;             // Total Nodes
    const int t_max = 300;    // Maximum Cycles of Time Evaluation

    // Instances of Field Vectors
    Field E;
    Field H;

    Data fieldE("fieldE.txt"); 
    Data fieldH("fieldH.txt");
    
    // Initilizing Field Vectors
    E.setN(N,"intNode");
    H.setN(N,"fracNode");

    // Time evolution
    for (int t = 0; t < t_max; t++)
    {
        E.setBoundary("PEC"); // Update the boundary values
        E.setupSource(N/2,t,"intNode");
        H.updateSpace(E);
        E.updateSpace(H);

        fieldE.write(E);
        fieldH.write(H);
    }
    
    return 0;
    }
