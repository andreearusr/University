
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <algorithm>
#include<mpi.h>
#include<vector>

using namespace std;

void stringToArrayNumbers(const string& stringValue, int arrayValue[]) {
    for (int i = 0; i < stringValue.size(); i++) 
        arrayValue[i] = stringValue[i] - '0';
}

void addZerosToNumber(const string& stringValue, int arrayValue[], int arraySize) {
    for (int i = (int)stringValue.size(); i < arraySize; i++)
        arrayValue[i] = 0;
}

void writeInFile(int* result, int size, string file_name)
{
    ofstream outfile(file_name);

    bool rez = false;
    for (int i = size; i >= 0; i--) {
        if (result[i] == 0 && rez == false) {
            continue;
        }
        else {
            rez = true;
            outfile << result[i];
        }
    }
}

bool checkEquality() {
    ifstream file1("Numar3_seq.txt");
    ifstream file2("Numar3_par.txt");

    if (file1.is_open() && file2.is_open())
    {
        vector<string> arr1, arr2;
        string element;

        while (file1 >> element)
        {
            arr1.push_back(element);
        }
        file1.close();

        while (file2 >> element)
        {
            arr2.push_back(element);
        }
        file2.close();

        sort(arr1.begin(), arr1.end());
        sort(arr2.begin(), arr2.end());
        return arr1 == arr2;
    }
    else {
        cout << "Unable to open file";
        return false;
    }
}

void generateFile(string file_name, int numberSize)
{
    ofstream outFile(file_name);
    int digit;

    outFile << numberSize;
    outFile << "\n";

    for (int i = 0; i < numberSize; i++) {
        if (i == 0) 
            digit = rand() % 9 + 1;
        else
            digit = rand() % 10;

        outFile << digit;
    }
    
    outFile.close();
}

void secvential() {
    string line;
    string firstNumberStr, secondNumberStr;
    srand(time(NULL));

    ifstream fin("Numar1.txt");
    getline(fin, line);
    int firstNumberSize = stoi(line);
    getline(fin, firstNumberStr);
    fin.close();

    fin = ifstream("Numar2.txt");
    getline(fin, line);
    int secondNumberSize = stoi(line);
    getline(fin, secondNumberStr);
    fin.close();

    if (firstNumberSize < secondNumberSize) {
        swap(firstNumberStr, secondNumberStr);
        swap(firstNumberSize, secondNumberSize);
    }
    int N = firstNumberSize;
    reverse(firstNumberStr.begin(), firstNumberStr.end());
    reverse(secondNumberStr.begin(), secondNumberStr.end());

    int* firstNumber = new int[N];
    int* secondNumber = new int[N];
    int* result = new int[N + 1];
    stringToArrayNumbers(firstNumberStr, firstNumber);
    stringToArrayNumbers(secondNumberStr, secondNumber);
    addZerosToNumber(secondNumberStr, secondNumber, N);
    
    //auto startTime = chrono::high_resolution_clock::now();

    int carry = 0;
    for (int i = 0; i < N; ++i) {
        int currentSum = (firstNumber[i] + secondNumber[i] + carry);
        carry = currentSum / 10;
        result[i] = currentSum % 10;
    }
    result[N] = carry;

   // auto endTime = chrono::high_resolution_clock::now();
   // cout << (double)chrono::duration<double, milli>(endTime - startTime).count() << "\n";
    
    writeInFile(result, N, "Numar3_seq.txt");
}

void metoda1_paralel(int argc, char* argv[]) {
    string line;
    string firstNumberStr, secondNumberStr;

    ifstream fin("Numar1.txt");
    getline(fin, line);
    int firstNumberSize = stoi(line);
    getline(fin, firstNumberStr);
    fin.close();

    fin = ifstream("Numar2.txt");
    getline(fin, line);
    int secondNumberSize = stoi(line);
    getline(fin, secondNumberStr);
    fin.close();

    if (firstNumberSize < secondNumberSize) {
        swap(firstNumberStr, secondNumberStr);
        swap(firstNumberSize, secondNumberSize);
    }
    int N = firstNumberSize;

    int* firstNumber = new int[N];
    int* secondNumber = new int[N];
    int* result = new int[N + 1];

    int p, rank;
    int start, end, carry;
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    if (rank == 0) {
        reverse(firstNumberStr.begin(), firstNumberStr.end());
        reverse(secondNumberStr.begin(), secondNumberStr.end());

        stringToArrayNumbers(firstNumberStr, firstNumber);
        stringToArrayNumbers(secondNumberStr, secondNumber);
        addZerosToNumber(secondNumberStr, secondNumber, N);

        int cat = N / (p - 1);
        int start = 0, end = cat;
        int rest = N % (p - 1);
        
        //auto startTime = chrono::high_resolution_clock::now();

        for (int i = 1; i < p; ++i) {
            if (rest > 0) {
                rest--;
                end++;
            }

            MPI_Send(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD);

            MPI_Send(firstNumber + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(secondNumber + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD);

            start = end;
            end += cat;
        }
        for (int i = 1; i < p; ++i) {
            MPI_Recv(&start, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(&end, 1, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
            MPI_Recv(result + start, end - start, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
        }

       // auto endTime = chrono::high_resolution_clock::now();
        //cout << (double)chrono::duration<double, milli>(endTime - startTime).count() << "\n";

        writeInFile(result, N, "Numar3_par.txt");
    }
    else {
        int start = 0, end = 0;

        MPI_Recv(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        MPI_Recv(firstNumber + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(secondNumber + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);

        //calcularea sumei
        carry = 0;
        for (int i = start; i < end; ++i) {
            int currentSum = (firstNumber[i] + secondNumber[i] + carry);
            carry = currentSum / 10;
            result[i] = currentSum % 10;
        }

        if (rank != 1) {
            //primire carry
            int recv_carry;
            MPI_Recv(&recv_carry, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);

            // recalcularea sumei
            for (int i = start; i < end; ++i) {
                int currentSum = result[i] + recv_carry;
                recv_carry = currentSum / 10;
                result[i] = currentSum % 10;
            }
            carry += recv_carry;
        }

        //trimitere carry
        if (rank != p - 1) {
            MPI_Send(&carry, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
        }

        if (rank == p - 1) {
            result[N] = carry;
            end++;
        }

        MPI_Send(&start, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(&end, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
        MPI_Send(result + start, end - start, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
}

void metoda2_paralel(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);

    string line;
    string firstNumberStr, secondNumberStr;

    ifstream fin("Numar1.txt");
    getline(fin, line);
    int firstNumberSize = stoi(line);
    getline(fin, firstNumberStr);
    fin.close();

    fin = ifstream("Numar2.txt");
    getline(fin, line);
    int secondNumberSize = stoi(line);
    getline(fin, secondNumberStr);
    fin.close();

    if (firstNumberSize < secondNumberSize) {
        swap(firstNumberStr, secondNumberStr);
        swap(firstNumberSize, secondNumberSize);
    }

    int p, rank;
    int carry = 0;
    MPI_Status status;

    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int N = firstNumberSize;
    if (firstNumberSize % p != 0)
        N +=  p;

    int* firstNumber = new int[N];
    int* secondNumber = new int[N];
    int* result = new int[N + 1];
    
    int cat = N / p;

    int* auxF = new int[cat];
    int* auxS = new int[cat];
    int* auxR = new int[cat];

   // auto startTime = chrono::high_resolution_clock::now();

    if (rank == 0) {
        reverse(firstNumberStr.begin(), firstNumberStr.end());
        reverse(secondNumberStr.begin(), secondNumberStr.end());
        stringToArrayNumbers(firstNumberStr, firstNumber);
        stringToArrayNumbers(secondNumberStr, secondNumber);
        addZerosToNumber(firstNumberStr, firstNumber, N);
        addZerosToNumber(secondNumberStr, secondNumber, N);
    }

    MPI_Scatter(firstNumber, cat, MPI_INT, auxF, cat, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Scatter(secondNumber, cat, MPI_INT, auxS, cat, MPI_INT, 0, MPI_COMM_WORLD);

    //calcularea sumei
    for (int i = 0; i < cat; ++i) {
        int currentSum = (auxF[i] + auxS[i] + carry);
        carry = currentSum / 10;
        auxR[i] = currentSum % 10;
    }

    if (rank != 0) {
        //primire carry
        int rcarry;
        MPI_Recv(&rcarry, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, &status);

        //recalcularea sumei
        for (int i = 0; i < cat; ++i) {
            int currentSum = auxR[i] + rcarry;
            rcarry = currentSum / 10;
            auxR[i] = currentSum % 10;
        }
        carry += rcarry;
    }

    //trimitere carry
    if (rank == p - 1) {
        MPI_Send(&carry, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }
    else {
        MPI_Send(&carry, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

    MPI_Gather(auxR, cat, MPI_INT, result, cat, MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0) {
        MPI_Recv(&carry, 1, MPI_INT, p - 1, 0, MPI_COMM_WORLD, &status);
        result[N] = carry;

       // auto endTime = chrono::high_resolution_clock::now();
        //cout << (double)chrono::duration<double, milli>(endTime - startTime).count() << "\n";

        writeInFile(result, N, "Numar3_par.txt");
    }

    MPI_Finalize();
    delete[] auxF;
    delete[] auxS;
    delete[] auxR;
}

int main(int argc, char* argv[])
{

    /*generateFile("Numar1.txt",100);
    generateFile("Numar2.txt", 100000);*/
    //secvential();
    //metoda1_paralel(argc, argv);
    metoda2_paralel(argc, argv);

   if (!checkEquality())
        cout << "Rezultate diferite";
    else
        cout << "Rezultate identice";
}
