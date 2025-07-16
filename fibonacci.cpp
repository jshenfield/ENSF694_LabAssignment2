/*
 *  lab2exe_D.cpp
 *  ENSF 694 Lab 2 Exercise D
 *  Completed by: Jack Shenfield
 *  Development Date: July 16th, 2025
 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
using namespace std;
#define N 2


void myPlot(int* x, double *y1, double *y2, int size){ // created with some help from chatgpt. This is my first time using GNUplot.
    // This funcitn must be completed by the students
    // iterative plot
    FILE* gp1 = popen("gnuplot -persistent", "w"); // open gnuplot
    if (gp1 == nullptr) {
        perror("Could not open pipe to Gnuplot (iterative)");
        exit(1);
    }
    // labels
    fprintf(gp1, "set title 'Iterative Fibonacci Timing'\n");
    fprintf(gp1, "set xlabel 'Input Size (n)'\n");
    fprintf(gp1, "set ylabel 'Time (seconds)'\n");
    fprintf(gp1, "plot '-' with lines title 'Iterative'\n");

    for (int i = 0; i < size; ++i) // data points
        fprintf(gp1, "%d %f\n", x[i], y1[i]);
    fprintf(gp1, "e\n");

    pclose(gp1);

    // recursive plot
    FILE* gp2 = popen("gnuplot -persistent", "w");
    if (gp2 == nullptr) {
        perror("Could not open pipe to Gnuplot (recursive)");
        exit(1);
    }
    // labels
    fprintf(gp2, "set title 'Recursive Matrix Fibonacci Timing'\n");
    fprintf(gp2, "set xlabel 'Input Size (n)'\n");
    fprintf(gp2, "set ylabel 'Time (seconds)'\n");
    fprintf(gp2, "plot '-' with lines title 'Recursive Matrix'\n");

    for (int i = 0; i < size; ++i) // print data points
        fprintf(gp2, "%d %f\n", x[i], y2[i]);
    fprintf(gp2, "e\n");

    pclose(gp2);
}




// Function to multiply two matrices of size N x N
void multiplyMatrix(int a[N][N], int b[N][N], int result[N][N]) {
    // This funcitn must be completed by the studnets
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            result[i][j] = 0; // set before doing += operation later, may result in garbage values
            for(int z = 0; z < N; z++){
                result[i][j] += a[i][z] * b[z][j];
            }
        }
    }
}

// Recursive funciont
void powerMatrix(int base[N][N], int exp, int result[N][N]) {
    // This funcitn must be completed by the students

    if(exp == 0){ // create identity matrix if exponent = 0
        for(int i = 0; i < N; i++){
            for(int j = 0; j < N; j++){
                if(i == j){
                    result[i][j] = 1; // 1s across the diagonal
                }
                else{
                    result[i][j] = 0; // all other indices filled by 0s
                }
            }
        }
        return;
    }

    else if(exp % 2 == 0){ // If exponent is even, square two of the matrices with half the exponent
        int temp[N][N];
        powerMatrix(base, exp/2, temp); // recursively call the same function
        multiplyMatrix(temp, temp, result);

    }
    
    else{ // If exponent is odd, square two of the matrices with half the exponent and multiply by matrix ^ 1
        int temp2[N][N];
        int tempSq[N][N];
        powerMatrix(base, exp/2, temp2);
        multiplyMatrix(temp2, temp2, tempSq);
        multiplyMatrix(tempSq, base, result);


    }
}

// Function to calculate the nth Fibonacci number using recursive matrix exponentiation
int fibonacciRecursive(int n) {
    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    int base[N][N] = {{1, 1}, {1, 0}};
    int result[N][N];
    powerMatrix(base, n - 1, result);
    return result[0][0];
}

// Function to calculate the nth Fibonacci number iteratively
int fibonacciIterative(int n) {
    // This funcitn must be completed by the students and if necessary its return value to be corrected.
    if(n == 1){ // have to set if/elseif statements for first two numbers, as they cannot be created from previous two values.
        return 0;
    }
    else if(n == 2){
        return 1;
    }
    
    int last = 0, curr = 1; // initialize first two values of sequence
    for (int i = 2; i <= n; i++) { // start at i = 2
        int next = last + curr;
        last = curr;
        curr = next;
    }
    return curr;
}

// Function to measure the time taken by a function to calculate the nth Fibonacci number
// This function is using a pointer to a funciton called fibonacciFunc
double measureTime(int (*fibonacciFunc)(int), int n) {
    // This funcitn must be completed by the students and if necessary its return value to be corrected.

    auto start = std::chrono::high_resolution_clock::now(); // start the clock

    volatile int result = fibonacciFunc(n);  // Call fib func

    auto end = std::chrono::high_resolution_clock::now(); // end clock

    std::chrono::duration<double> duration = end - start; // calculate the duration and store in double
    return duration.count(); // return the double
}

int main(void) {
    const int maxN = 400000000; // Adjust maxN based on the range you want to test
    double recursive_result[50];
    double iterative_result[50];
    int N_value[50];

    cout << "Recursive Matrix Exponentiation Method\n";
    cout << setw(12) << "N" << setw(12) << "Time\n";
    for (int n = 20000000, i=0; n <= maxN; n+=20000000, i++) {
        double time = measureTime(fibonacciRecursive, n);
        recursive_result[i] = time;
        cout << setw(12) << n << setw(12) << recursive_result[i] << endl;
    }

    cout << "\nIterative Method\n";
    cout << setw(12) << "N" << setw(12) << "Time\n";
    for (int n = 20000000, i=0; n <= maxN; n+=20000000, i++) {
        double time = measureTime(fibonacciIterative, n);
        iterative_result[i] = time;
        cout << setw(12) << n << setw(12) << iterative_result[i] << endl;
        N_value[i] = n;
    }
    
    myPlot(N_value, iterative_result,  recursive_result, 30 );

    return 0;
}


