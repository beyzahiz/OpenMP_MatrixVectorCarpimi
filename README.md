# 🚀 OpenMP ile Paralel Matris-Vektör Çarpımı

![C++](https://img.shields.io/badge/Language-C++-blue.svg)
![OpenMP](https://img.shields.io/badge/Library-OpenMP-green.svg)
![License](https://img.shields.io/badge/License-MIT-orange.svg)

## 📖 Proje Hakkında
Bu proje, **C++** programlama dili ve **OpenMP** kütüphanesi kullanılarak yüksek performanslı **Matris-Vektör Çarpımı** ($Ax = y$) işlemini gerçekleştirir.

Projenin temel amacı, paylaşımlı bellek (shared memory) mimarilerinde **paralel programlamanın** hesaplama süresi üzerindeki etkisini göstermek ve seri işlem ile paralel işlem arasındaki performans farkını (Speedup) analiz etmektir.

Program şunları yapar:
1.  **Seri Hesaplama:** Tek işlem parçacığı (Single-thread) ile çarpma işlemi.
2.  **Paralel Hesaplama:** OpenMP kullanılarak çoklu işlem parçacığı (Multi-thread) ile çarpma işlemi.
3.  **Performans Analizi:** İki yöntem arasındaki hızlanma oranını (Speedup) otomatik hesaplar.

---

## 🧮 Matematiksel Model
Problem, $M \times N$ boyutunda bir $\mathbf{A}$ matrisi ile $N$ boyutunda bir $\mathbf{x}$ vektörünün çarpılarak $M$ boyutunda bir $\mathbf{y}$ vektörünün elde edilmesidir:

$$\mathbf{y} = \mathbf{A} \times \mathbf{x}$$

İşlemin eleman bazlı gösterimi şu şekildedir:

$$y_i = \sum_{j=0}^{N-1} A_{ij} \cdot x_j \quad , \quad 0 \le i < M$$

Bu işlem $O(M \times N)$ zaman karmaşıklığına sahiptir ve büyük boyutlu matrislerde paralelleştirme için ideal bir adaydır.

---

## ⚙️ Özellikler
* **Dinamik Boyutlandırma:** Matris ($M$) ve Vektör ($N$) boyutları çalışma zamanında kullanıcı tarafından belirlenir.
* **Thread Kontrolü:** Kullanılacak thread sayısı komut satırından parametre olarak girilebilir.
* **Hassas Ölçüm:** `std::chrono` kütüphanesi ile yüksek hassasiyetli süre ölçümü yapılır.
* **Speedup Hesabı:** $T_{seri} / T_{paralel}$ formülü ile hızlanma oranı anlık olarak raporlanır.
* **Rastgele Veri Üretimi:** Matris ve vektör elemanları test amaçlı rastgele sayılarla doldurulur.

---

## 🛠️ Kurulum ve Derleme

### Gereksinimler
* C++ Derleyicisi (GCC/G++)
* OpenMP Kütüphanesi (GCC ile standart gelir)

### Derleme Komutu
Projeyi derlemek için `-fopenmp` bayrağını kullanmanız gerekmektedir:

g++ -o openmp_multiplication main.cpp -fopenmp

---

## 🚀 Kullanım

Derlenen programı çalıştırmak için aşağıdaki argümanları sırasıyla giriniz:
`./openmp_multiplication <SATIR_M> <SUTUN_K> <THREAD_SAYISI>`

* **SATIR_M**: Matrisin satır sayısı.
* **SUTUN_K**: Matrisin sütun sayısı (ve vektörün boyutu).
* **THREAD_SAYISI**: Paralel işlemde kullanılacak iş parçacığı sayısı.

### Örnek Çalıştırma
**3000 x 3000** boyutunda bir matris ve **8 thread** kullanımı için:

./openmp_multiplication 3000 3000 8 

---

## Örnek Çıktı

Matris Boyutu: 3000 x 3000
Thread Sayisi: 8
Seri Zaman: 0.0354913 saniye
Paralel Zaman: 0.0090934 saniye
Speedup: 3.9029


