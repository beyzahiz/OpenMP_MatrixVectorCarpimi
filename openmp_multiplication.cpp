#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>
#include <chrono>

using namespace std;
using namespace chrono;

int main(int argc, char* argv[]) {

    if (argc < 4) {
    cout << "Kullanim: ./openmp_multiplication M K THREAD\n";
    return 1;
}

    int M = atoi(argv[1]);
    int K = atoi(argv[2]);
    int thread_count = atoi(argv[3]);

    omp_set_num_threads(thread_count);


    vector<vector<int>> A(M, vector<int>(K));
    vector<int> x(K);
    vector<long long> y_serial(M);
    vector<long long> y_parallel(M);

    // Rastgele degerler
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            A[i][j] = rand() % 10;
        }
    }

    for (int i = 0; i < K; i++) {
        x[i] = rand() % 10;
    }

    // ================== SERI ==================
    auto start_serial = high_resolution_clock::now();

    for (int i = 0; i < M; i++) {
        y_serial[i] = 0;
        for (int j = 0; j < K; j++) {
            y_serial[i] += A[i][j] * x[j];
        }
    }

    auto end_serial = high_resolution_clock::now();
    double serial_time = duration<double>(end_serial - start_serial).count();

    // ================== PARALEL ==================
    auto start_parallel = high_resolution_clock::now();

    #pragma omp parallel for schedule(guided)

    for (int i = 0; i < M; i++) {
        y_parallel[i] = 0;
        for (int j = 0; j < K; j++) {
            y_parallel[i] += A[i][j] * x[j];
        }
    }

    auto end_parallel = high_resolution_clock::now();
    double parallel_time = duration<double>(end_parallel - start_parallel).count();

    // ================== SONUCLAR ==================
    cout << "Matris Boyutu: " << M << " x " << K << endl;
    cout << "Thread Sayisi: " << thread_count << endl;

    cout << "Seri Zaman: " << serial_time << " saniye\n";
    cout << "Paralel Zaman: " << parallel_time << " saniye\n";
    cout << "Speedup: " << serial_time / parallel_time << endl;

    return 0;
}
