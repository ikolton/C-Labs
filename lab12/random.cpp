#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <cctype>
#include <ctime>
#include <thread>
#include <utility>
#include <thread>
#include <chrono>
#include <mutex>
using namespace std;

/* Exercise 1.  Threads and mutex.
 Program random.cpp fills an array with random values then replaces each element x with f(x).
Finally it computes sum of elements in the array.
 When generateArray is called in parallel by two threads the output changes. The order of elements
can change but the sum should remain the same. Correct the algorithm to avoid data races.
Make the number of threads used a parameter of the algorithm.
 Change computeSum function so that it could be run in parallel by several threads.
 */


template <int N>
struct Array{
    int a[N];
    int i  = 0;
    int value = 1;
    long long sum = 0;
    std::mutex mtx; // Mutex to protect critical sections

    int f(int x){
        int y = x%11;
        return (y*y+1);
    }

    void generateArray(){
        while(i<N){
            std::lock_guard<std::mutex> lock(mtx); // Lock the mutex before accessing shared data
            a[i++] = rand();
        }
        i = 0;
        while(i<N){
            std::lock_guard<std::mutex> lock(mtx); // Lock the mutex before accessing shared data
            a[i] = f(a[i]);
            i++;
        }
    }

    void computeSumRange(int start, int end, long long &partialSum){
        partialSum = 0;
        for(int j = start; j < end; j++){
            partialSum += a[j];
        }
    }

    long long computeSum(int numThreads = 1){
        sum = 0;
        std::vector<std::thread> threads;
        std::vector<long long> partialSums(numThreads, 0);
        int chunkSize = N / numThreads;

        for(int t = 0; t < numThreads; t++){
            int start = t * chunkSize;
            int end = (t == numThreads - 1) ? N : start + chunkSize;
            threads.emplace_back(&Array::computeSumRange, this, start, end, std::ref(partialSums[t]));
        }

        for(auto &t : threads){
            t.join();
        }

        sum = std::accumulate(partialSums.begin(), partialSums.end(), 0LL);
        return sum;
    }
};

int main() {
    srand(2019);
    using A = Array<1000>;
    A array;
    std::thread t1(&A::generateArray, &array);
//  What happens if you uncomment this line?
//  std::thread t2(&A::generateArray, &array);
//  t2.join();
    t1.join();
    for (int i = 0; i < 40; i++) {
        cout << array.a[0 + i] << "  ";
    }
    long long sum = array.computeSum(4); // Use 4 threads to compute the sum
    cout << "\n sum = " << sum << endl;
}
