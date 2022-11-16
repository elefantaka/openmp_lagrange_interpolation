//Lagrange interpolation with OpenMP parallelization

#include <bits/stdc++.h>
#include <omp.h>
#include <iostream>
#include <time.h>
#include <random>

using namespace std;

int MAX_THREADS = 1;
int DATA_SIZE = 1150;

struct DataPoint
{
    int x; 
    int y;
};

DataPoint *generateDataSet(int size, int maxInt)
{
    ++maxInt;
    DataPoint *set = new DataPoint[size];
    for (int i = 0; i < size; i++)
    {
        set[i] = {i, rand() % maxInt};
    }
    return set;
}

double interpolateLagrange(DataPoint *f, int givenX, int n)
{
    double result = 0;
// to split process into 4 threads
#pragma omp parallel num_threads(MAX_THREADS)
    {
// to split the code into 4 for basic loops
#pragma omp for
        for (int i = 0; i < n; i++)
        {

            double polynomial = f[i].y;

            for (int j = 0; j < n; j++)
            {
                if (j != i)
                {
// to write to the particular memory location, in this case "polynomial" variable, it's more efficient
#pragma omp atomic write
                    polynomial = polynomial * (givenX - f[j].x) / double(f[i].x - f[j].x);
                }
            }

            result += polynomial;
        }
    }

    return result;
}

int main()
{
    clock_t start = clock();
    srand(420);

    if (const char *env = getenv("MAX_THREADS"))
    {
        MAX_THREADS = (stoi((string)(env)));
    }

    if (const char *env = getenv("DATA_SIZE"))
    {
        DATA_SIZE = (stoi((string)(env)));
    }

    cout << MAX_THREADS << endl;
    cout << DATA_SIZE << endl;

    DataPoint *f = generateDataSet(DATA_SIZE, 100);

    cout << "Value of f(10) is : " << interpolateLagrange(f, 10, DATA_SIZE);

    clock_t stop = clock();
    double elapsed = (double)(stop - start) / CLOCKS_PER_SEC;

    printf("\nTime elapsed: %.5f\n", elapsed);

    return 0;
}

// useful commands:
// gcc main.cpp -lstdc++ -o main.o && ./main.o
// htop

// to print the generated points:
//  for (int i = 0; i < size; i++)
// {
//   cout << "idx;\t" << i << "\tx:\t" << f[i].x << "\ty:\t" << f[i].y << endl;
// }