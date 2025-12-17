// KÜTÜPHANELER
#include <iostream>  //Ekrana yazı yazmak (cout) ve klavyeden veri almak için kullanılır.
#include <vector>  //Dinamik diziler (vector) kullanabilmek için eklenir.
#include <cstdlib>  //rand() ve atoi() gibi C standart fonksiyonlarını kullanmak için gerekir.
#include <omp.h>  //OpenMP fonksiyonlarını ve #pragma omp direktiflerini kullanabilmek için zorunludur.
#include <chrono>  //Programın çalışma süresini ölçmek için kullanılan zaman kütüphanesidir.

using namespace std;  //Kısa şekilde cout, vector yazmamızı sağlar.
using namespace chrono;  //Uzun isimleri kısaltır.

//MAIN FONKSİYONU
int main(int argc, char* argv[]) {  //Programın başlangıç noktasıdır. argc: Komut satırından girilen argüman sayısı. argv: Girilen argümanların kendisi

    if (argc < 4) {
    cout << "Kullanim: ./openmp_multiplication M K THREAD\n";
    return 1;
}  //Kullanıcıdan 3 parametre bekleniyor. Eğer eksik girilirse program kullanıcıyı uyarır. Hatalı çalışmayı önlemek için durur. 

    int M = atoi(argv[1]);  //Matrisin satır sayısını alır.
    int K = atoi(argv[2]);  //Matrisin sütun sayısını alır.
    int thread_count = atoi(argv[3]);  //OpenMP’de kullanılacak thread sayısını alır.

    //THREAD SAYISININ AYARLANMASI
    omp_set_num_threads(thread_count);  //OpenMP’ye kaç thread kullanacağını söyler.

    //VERİ YAPILARININ TANIMLANMASI
    vector<vector<int>> A(M, vector<int>(K));  //M x K boyutunda matris A oluşturur.
    vector<int> x(K);  //K boyutunda vektör x oluşturur.
    vector<long long> y_serial(M);  //Seri hesaplama sonucu oluşacak y vektörünü tutar.
    vector<long long> y_parallel(M);  //Paralel hesaplama sonucu oluşacak y vektörünü tutar.

    //MATRİSİN RASTGELE DOLDURULMASI
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < K; j++) {
            A[i][j] = rand() % 10;
        }
    }  //Matrisin tüm elemanlarını 0–9 arasında rastgele değerlerle doldurur.

    //VEKTÖRÜN RASTGELE DOLDURULMASI
    for (int i = 0; i < K; i++) {
        x[i] = rand() % 10;
    }  //x vektörünü 0–9 arası rastgele değerlerle doldurur.

    //SERİ HESAPLAMA
    auto start_serial = high_resolution_clock::now();  //Seri hesaplamanın başlangıç zamanını kaydeder.

    for (int i = 0; i < M; i++) {
        y_serial[i] = 0;
        for (int j = 0; j < K; j++) {
            y_serial[i] += A[i][j] * x[j];
        }
    }  //Seri olarak matris–vektör çarpımı yapılır.
    //Her satır için y[i], A matrisinin i. satırı ile x vektörünün çarpımlarının toplamıdır.
    //İşlem tek iş parçacığında (seri) gerçekleştirilir.

    auto end_serial = high_resolution_clock::now();  //Seri hesaplamanın bitiş zamanını alır.
    double serial_time = duration<double>(end_serial - start_serial).count();  //Seri çalışma süresini saniye cinsinden hesaplar.

    //PARALEL HESAPLAMA
    auto start_parallel = high_resolution_clock::now();  //Paralel hesaplamanın başlangıç zamanını alır.
    
    #pragma omp parallel for  //Dış döngüyü OpenMP ile paralelleştirir. İş yükü thread’lere dinamik olarak dağıtılır.

    for (int i = 0; i < M; i++) {
        y_parallel[i] = 0;
        for (int j = 0; j < K; j++) {
            y_parallel[i] += A[i][j] * x[j];
        }
    }  //Aynı hesaplama bu sefer paralel yapılır.

    auto end_parallel = high_resolution_clock::now();  //Paralel hesaplamanın bitiş zamanını alır.
    double parallel_time = duration<double>(end_parallel - start_parallel).count();  //Paralel çalışma süresini saniye cinsinden hesaplar.

    //SONUÇLAR
    cout << "Matris Boyutu: " << M << " x " << K << endl;  //Kullanılan matris boyutlarını ekrana yazdırır.
    cout << "Thread Sayisi: " << thread_count << endl;  //Kaç thread kullanıldığını gösterir.

    cout << "Seri Zaman: " << serial_time << " saniye\n";  //Seri çalışma süresini yazdırır.
    cout << "Paralel Zaman: " << parallel_time << " saniye\n";  //Paralel çalışma süresini yazdırır.
    cout << "Speedup: " << serial_time / parallel_time << endl;  //Speedup = Seri Zaman / Paralel Zaman hesaplar.

    return 0;
}
