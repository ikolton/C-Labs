
// Compilation:
//   g++ ex_11_2_Mandelbrot.cpp EasyBMP.cpp -O2 -std=c++14 -o mandelbrot

/*
 * Exercise 2. Mandelbrot set
 Program mandelbrot.cpp generates bitmap file with part of Mandelbrot set contained in the
rectangle [x1, x2]x[y1, y2] on the complex plane. Each pixel corresponds to some complex number  c.
 It defines complex function f(z) = z2+c . We generate sequence zn+1 = f(zn) starting from z0=0. If
sequence is bounded than c belongs to Mandelbrot set.
In practice we iterate f(z). if |zn|> M (where M >2)  then sequence is unbounded and c is not in
Mandelbrot set. We use first such n to choose color for corresponding point.
 If we reach maximal number of iterations N and |zn| <= M for all n<=N  then we assume that c is in
the Mandelbrot set.
 Each point can be checked independently and it can be done in parallel.
 Change the part of the program that generates bitmap from sequential to asynchronous to get
maximal speed up. Find optimal number of threads for your processor.
 */

#include "EasyBMP.h"
#include <complex>
#include <chrono>
#include <thread>
#include <vector>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>


using namespace std;

class ThreadPool {
public:
    ThreadPool(size_t threads) : stop(false) {
        for(size_t i = 0; i<threads; ++i)
            workers.emplace_back([this] {
                for(;;) {
                    std::function<void()> task;
                    {
                        std::unique_lock<std::mutex> lock(this->queue_mutex);
                        this->condition.wait(lock, [this]{ return this->stop || !this->tasks.empty(); });
                        if(this->stop && this->tasks.empty())
                            return;
                        task = std::move(this->tasks.front());
                        this->tasks.pop();
                    }
                    task();
                }
            });
    }

    template<class F>
    void enqueue(F&& f) {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            if(stop)
                throw std::runtime_error("enqueue on stopped ThreadPool");
            tasks.emplace(std::forward<F>(f));
        }
        condition.notify_one();
    }

    ~ThreadPool() {
        {
            std::unique_lock<std::mutex> lock(queue_mutex);
            stop = true;
        }
        condition.notify_all();
        for(std::thread &worker: workers)
            worker.join();
    }

private:
    std::vector<std::thread> workers;
    std::queue<std::function<void()>> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop;
};

typedef complex<double> Complex;
/**
 * Returns functional object that converts pixel position to point in the complex plane.
 * @param imageWidth   image width
 * @param imageHeight  image hight
 * @param x1           minimal x
 * @param y1           minimal y
 * @param x2           maximal x
 * @param y2           maximal y
 * @return             functional object
 */
auto scaleFromPixelToComplex(int imageWidth, int imageHeight,
                             double x1, double y1, double x2, double y2){
    double sx = (x2-x1)/imageWidth;
    double sy = (y2-y1)/imageHeight;
    return [=](int x, int y){
        return Complex(x1 + sx * x, y2 - sy * y);
    };
}

/**
 * Checks if given complex number c is in not the Mandelbrot set.
 * @param c complex number
 * @param maxNumberOfIterations  maximal number of iterations
 * @param escapeThreshold
 * @return number of iterations after which image of 0 has module greather
 *         than escapeTreshold or 0 is maxNumberOfIteration was reached.
 */
static auto MandelbrotSetIterations( Complex c,
        size_t maxNumberOfIterations,
        double escapeThreshold = 4.0
){
    Complex x = 0;
    for(int i=0; i<maxNumberOfIterations; i++){
        x = x*x+c;
        if(abs(x)>escapeThreshold)
            return i+1;
    }
    return 0;
}


int main( int argc, char* argv[] )
{

    const int imageWidth = 1000;                // bitmap width
    const int imageHeight = 1000;               // bitmap height
    const char * fileName = "mandelbrot.bmp";     // file name to output bitmap

    double x1=-2, x2=1,   // Rectangle in the complex plane [x1, x2]x[y1,,y2]
    y1=-1, y2=1;          // that will plotted on bitmap.

    size_t maxNumberOfIteration = 2000;
//    size_t maxNumberOfIteration = 5000;
    double escapeThreshold = 4;

    BMP Output;                                // We create bitmap
    Output.SetSize(imageWidth, imageHeight );  // We set bitmap sizes
    Output.SetBitDepth( 24 );        // We set color depth
    // Each pixel has 24 bits (8 bits for each RGB component)

    auto pixelToComplex = scaleFromPixelToComplex(imageWidth, imageHeight, x1, y1, x2, y2);

    auto iterationsToPixel = [](size_t numerOfIterations){
        RGBApixel pixel;
        pixel.Blue = 0;
        pixel.Green = (ebmpBYTE) 0;
        pixel.Red = (ebmpBYTE) 0;
        if(numerOfIterations>0){
            pixel.Green = (ebmpBYTE) 255 - 10*(numerOfIterations % 20);
            pixel.Red = (ebmpBYTE) 255 - 10*(numerOfIterations % 10);
        }
        pixel.Alpha = 0;
        return pixel;
    };

//    auto start = std::chrono::steady_clock::now();

//    for(unsigned y=0; y<imageHeight; y++){
//        for(unsigned x=0; x<imageWidth; x++){
//
//            Complex c = pixelToComplex(x, y);
//
//            auto numberOfIteration = MandelbrotSetIterations(c, maxNumberOfIteration, escapeThreshold);
//            auto pixel = iterationsToPixel(numberOfIteration);
//            Output.SetPixel(x,y,pixel) ;
//        }
//    }

    unsigned int nThreads = std::thread::hardware_concurrency();
    ThreadPool pool(nThreads);

    auto start = std::chrono::steady_clock::now();

    std::mutex mtx;
    std::condition_variable cv;
    bool finished = false;

    for(unsigned y=0; y<imageHeight; y++){
        for(unsigned x=0; x<imageWidth; x++){
            pool.enqueue([&, x, y](){
                Complex c = pixelToComplex(x, y);

                auto numberOfIteration = MandelbrotSetIterations(c, maxNumberOfIteration, escapeThreshold);
                auto pixel = iterationsToPixel(numberOfIteration);
                Output.SetPixel(x,y,pixel);

                // Notify the main thread when the last task is done
                std::unique_lock<std::mutex> lock(mtx);
                if(x == imageWidth - 1 && y == imageHeight - 1) {
                    finished = true;
                    cv.notify_one();
                }
            });
        }
    }

// Wait for all tasks to finish
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [&](){ return finished; });

    auto stop = std::chrono::steady_clock::now();
    cout << "Time used : " << std::chrono::duration_cast<std::chrono::milliseconds>(stop-start).count() << " ms."<< endl;
    cout << "Bitmap written to " << fileName << "." << endl;
    Output.WriteToFile( fileName );
    return 0;
}
