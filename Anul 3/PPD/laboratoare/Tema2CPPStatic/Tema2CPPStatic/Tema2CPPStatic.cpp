
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <fstream>
#include <string>
#include <sstream>
#include "Barrier.cpp"
using namespace std;

//int p = 4; //numarul de thread-uri
const int N = 10000, M = 10, n = 5, m = 5; //dimensiuni matrice F nebordata si V + dimensiuni matrice W

int F_static[M][N];
float W_static[m][n];
float F_static_bordat[M + 4][N + 4];
my_barrier* barrier(0);

//calculare noua valoare din matrice, folosind matricea de filtrare
float calculateNewValue(float W[m][n], float F[M + 4][N + 4], int i, int j) {
    float newValue = 0;
    int poz = n / 2;
    for (int ii = 0; ii < m; ii++) {
        for (int jj = 0; jj < n; jj++) {
            newValue += W[ii][jj] * F[i - poz + ii][j - poz + jj];       
        }
    }

    return newValue;
}


//citire matrice initiala din fisier
void readMatrixStatic(float matrix[M + 4][N + 4]) {
    ifstream inputMatrix("inputMatrix.txt");
    if (!inputMatrix.is_open())
        cout << "Error opening file";
    int value;

    for (int row = 2; row < M + 2; row++)
        for (int column = 2; column < N + 2; column++)
            inputMatrix >> matrix[row][column];

}
//functie de calcul pentru un thread
void calculateThread(int id, int p, float W[m][n], float F[M + 4][N + 4], int M, int N) {
    
    vector<float> auxiliarArray = {};
    for (int i = id + 2; i < M + 2; i += p) {
        for (int j = 2; j < N + 2; j++) {
            float value = calculateNewValue(ref(W), ref(F), i, j);
            auxiliarArray.push_back(value);
        }
    }

    (*barrier).wait();
    int index = 0;

    for (int i = id + 2; i < M + 2; i += p) {
        for (int j = 2; j < N + 2; j++) {
            F[i][j] = auxiliarArray.at(index);
            index++;
        }
    }
}

//functie pentru verificarea egalitatii fisierelor -> calcul secvential si calcul paralel
bool checkEquality() {
    ifstream outputSeq("outputMatrixSequencial.txt");
    ifstream outputPar("outputMatrixParallel.txt");
    float value1, value2;

    for (int row = 2; row < M + 2; row++)
        for (int column = 2; column < N + 2; column++) {
            outputSeq >> value1;
            outputPar >> value2;
            if (value1 != value2)
                return false;
        }

    return true;
}

int main(int argc, char* argv[])
{
    int p = atoi(argv[1]);
    float wVal = (float)1 / 9;

    srand(time(NULL));
    //initializarea matricii W
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) {
            W_static[i][j] = wVal;
        }

    //citire matrice F din fisier
    readMatrixStatic(ref(F_static_bordat));

    //bordarea matricii
    F_static_bordat[0][0] = F_static_bordat[0][1] = F_static_bordat[1][0] = F_static_bordat[1][1] = F_static_bordat[2][2];
    F_static_bordat[M + 3][1] = F_static_bordat[M + 2][1] = F_static_bordat[M + 3][0] = F_static_bordat[M + 2][0] = F_static_bordat[M + 1][2];
    F_static_bordat[0][N + 3] = F_static_bordat[0][N + 2] = F_static_bordat[1][N + 3] = F_static_bordat[1][N + 2] = F_static_bordat[2][N + 1];
    F_static_bordat[M + 3][N + 3] = F_static_bordat[M + 3][N + 2] = F_static_bordat[M + 2][N + 3] = F_static_bordat[M + 2][N + 2] = F_static_bordat[M + 1][N + 1];

    for (int i = 2; i < M + 2; i++) {
        F_static_bordat[i][0] = F_static_bordat[i][1] = F_static_bordat[i][2];
        F_static_bordat[i][N + 2] = F_static_bordat[i][N + 3] = F_static_bordat[i][N + 1];
    }
    for (int j = 2; j < N + 2; j++) {
        F_static_bordat[0][j] = F_static_bordat[1][j] = F_static_bordat[2][j];
        F_static_bordat[M + 2][j] = F_static_bordat[M + 3][j] = F_static_bordat[M + 1][j];
    }

    char* type = argv[2];
   /* string type;
    cout << "seq / par ?\n";
    cin >> type;*/
    if (strcmp(type, "seq") == 0) {
        ofstream outputSeq("outputMatrixSequencial.txt");
        auto startTime = chrono::high_resolution_clock::now();

        //secvential
        for (int i = 2; i < M + 2; i++) {
            for (int j = 2; j < N + 2; j++) {
                float value = calculateNewValue(ref(W_static), ref(F_static_bordat), i, j);
                outputSeq << value << " ";
            }
            outputSeq << "\n";
        }

        auto endTime = chrono::high_resolution_clock::now();
        cout << (double)chrono::duration<double, milli>(endTime - startTime).count() << "\n";
    }
    else {
        auto startTimeParalel = chrono::high_resolution_clock::now();
        ofstream outputPar("outputMatrixParallel.txt");
        barrier = new my_barrier(p);

        // paralel
        vector<thread> threads(p);
        for (int i = 0; i < p; i++) {
            threads[i] = thread(calculateThread, i, p, ref(W_static), ref(F_static_bordat), M, N);
        }

        for (int i = 0; i < p; i++) {
            threads[i].join();
        }

        for (int i = 2; i < M+2; i++) {
            for (int j = 2; j < N+2; j++) {
                outputPar << F_static_bordat[i][j] << " ";
            }
            outputPar << "\n";
        }

        auto endTimeParalel = chrono::high_resolution_clock::now();
        cout << (double)chrono::duration<double, milli>(endTimeParalel - startTimeParalel).count() << "\n";
    }

    if (strcmp(type, "par") == 0) {
        if (!checkEquality())
            cout << "Rezultate diferite";
        else
            cout << "Rezultate identice";
    }

    return 0;
}
