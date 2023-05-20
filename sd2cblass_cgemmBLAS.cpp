#include <iostream>
#include <random>
#include <chrono>
#include <complex>
#include <cblas.h>
using namespace std;




const int SIZE = 4096;

void genM(complex<float>* matrix)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(-1.0, 1.0);

    for (int i = 0; i < SIZE * SIZE; ++i) {
        matrix[i] = complex<float>(dis(gen), dis(gen));
    }
}

void peremnojenieMatrix1(const complex<float>* matrixA, const complex<float>* matrixB, complex<float>* result)
{
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            complex<float> sum(0.0f, 0.0f);
            for (int k = 0; k < SIZE; ++k) {
                sum += matrixA[i * SIZE + k] * matrixB[k * SIZE + j];
            }
            result[i * SIZE + j] = sum;
        }
    }
}

void peremnojenieMatrix3(const complex<float>* matrixA, const complex<float>* matrixB, complex<float>* result)
{
    const int blockSize = 64;

    for (int i = 0; i < SIZE; i += blockSize)
    {
        for (int j = 0; j < SIZE; j += blockSize)
        {
            for (int k = 0; k < SIZE; k += blockSize)
            {
                for (int ii = i; ii < min(i + blockSize, SIZE); ++ii)
                {
                    for (int jj = j; jj < min(j + blockSize, SIZE); ++jj)
                    {
                        std::complex<float> sum(0.0f, 0.0f);
                        for (int kk = k; kk < min(k + blockSize, SIZE); ++kk)
                        {
                            sum += matrixA[ii * SIZE + kk] * matrixB[kk * SIZE + jj];
                        }
                        result[ii * SIZE + jj] += sum;
                    }
                }
            }
        }
    }
}

int main()
{
    complex<float>* matrixA = new complex<float>[SIZE * SIZE];
    complex<float>* matrixB = new complex<float>[SIZE * SIZE];
    complex<float>* result = new complex<float>[SIZE * SIZE];

    genM(matrixA);
    genM(matrixB);

    // 1
    auto start = chrono::steady_clock::now();
    peremnojenieMatrix1(matrixA, matrixB, result);
    auto end = chrono::steady_clock::now();
    chrono::duration<double> seconds_counted = end - start;
    double time1 = seconds_counted.count();




    complex<float> alpha(1.0f, 0.0f); // alpha i beta dlya cblas
    complex<float> beta(0.0f, 0.0f);

    // 2
    start = chrono::steady_clock::now();
    cblas_cgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, SIZE, SIZE, SIZE, &alpha, matrixA, SIZE, matrixB, SIZE, &beta, result, SIZE);
    end = chrono::steady_clock::now();
    seconds_counted = end - start;
    double time2 = seconds_counted.count();

    // 3
    start = chrono::steady_clock::now();
    peremnojenieMatrix3(matrixA, matrixB, result);
    end = chrono::steady_clock::now();
    seconds_counted = end - start;
    double time3 = seconds_counted.count();

    // Оценка1
    int n = SIZE;
    double difficulty_1 = 2 * n * n * n;

    // Оценка2
    double p1 = difficulty_1 / (time1 * 1e-6);
    double p2 = difficulty_1 / (time2 * 1e-6);
    double p3 = difficulty_1 / (time3 * 1e-6);


    cout << "Время выполнения варианта 1: " << time1 << " сек" << endl;
    cout << "Время выполнения варианта 2: " << time2 << " сек" << endl;
    cout << "Время выполнения варианта 3: " << time3 << " сек" << endl;
    cout << "Производительность варианта 1: " << p1 << " MFlops" << endl;
    cout << "Производительность варианта 2: " << p2 << " MFlops" << endl;
    cout << "Производительность варианта 3: " << p3 << " MFlops" << endl;
    cout << "Оценка сложности алгоритма: " << difficulty_1 << endl;



    delete[] matrixA;
    delete[] matrixB;
    delete[] result;

    return 0;
}
