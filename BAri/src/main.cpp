#include <TTL.hpp>
#include "Main/Main.hpp"
#include "Main/MANE.hpp"

//#include <cmath>
//std::size_t fib(std::size_t in)
//{
//    return static_cast<std::size_t>(1./sqrt(5.) * std::pow((1. + sqrt(5.))/2., static_cast<double>(in)) + -1./sqrt(5.) * std::pow((1. - sqrt(5.))/2., static_cast<double>(in)));
//}


int main()
{
//    std::size_t input;
//    std::cout << "What fib num do you wanna find, beeyatch? : " << std::flush;
//    std::cin >> input;
//    ttl::Ips time;
//    time.limit();
//    std::size_t out = fib(input);
//    time.limit();
//    std::cout << "Computation took: " << time.getDelay().count() << " us" << std::endl;
//    std::cout << "The number is: " << out << std::endl;
//    return 0;
    std::unique_ptr<ttl::Runnable> arg(new MANE);
    ttl::Runnable::cycle<true>(std::move(arg));
}



////////////////////////////////////////////////////////////
//
//    char *start, *finish;
//
//    void iterate(const int from, const int to)
//    {
//        std::mt19937 en(std::time(nullptr));
//        std::memcpy(&finish[from], &start[from], to - from);
//        for (int i = from; i < to; ++i)
//            start[i] = en();
//    }
//
//    void doNothing()
//    {}
//
//    void creatingThreads(int threads)
//    {
//        std::vector<ttl::JoinThread *> join_threads;
//        for (int i = 0; i < threads; ++i)
//            join_threads.emplace_back(new ttl::JoinThread(&Main::doNothing, this));
//        for (auto x : join_threads)
//            delete x;
//    }
//    static constexpr const std::size_t range = 1000000000;
//    void performXThreads(const int threads)
//    {
//
//        std::vector<ttl::JoinThread *> join_threads;
//        for (int i = 0; i < threads; ++i)
//                join_threads.emplace_back(new ttl::JoinThread(&Main::iterate, this, i * (range/threads), (i + 1) * (range/threads)));
//        for (auto x : join_threads)
//            delete x;
//    }
//
//    std::size_t computeOptimalThreadCount(const std::size_t maximum_thread_count = std::thread::hardware_concurrency())
//    {
//        ttl::Benchmark benchmark("", 1);
//        ttl::Benchmark overhead("", 10);
//
//        std::size_t least_threads;
//        float shortest_time;
//
//        for (std::size_t threads = 1; threads < maximum_thread_count; ++threads)
//        {
//            benchmark.resetAverageRunTime();
//            overhead.resetAverageRunTime();
//            benchmark.run(&Main::performXThreads, this, threads);
//            overhead.run(&Main::creatingThreads, this, threads);
//            if (threads == 1)
//            {
//                shortest_time = benchmark.getAverageRunTime() - overhead.getAverageRunTime();
//            }
//            else
//            {
//                float tmp = benchmark.getAverageRunTime() - overhead.getAverageRunTime();
//                if (tmp < shortest_time && tmp > 0.f)
//                {
//                    least_threads = threads;
//                    shortest_time = tmp;
//                }
//
//            }
//
//            std::cout << "Threads: " << threads << ": " << shortest_time << " microseconds" << std::endl;
//        }
//        return least_threads;
//    }
//
////////////////////////////////////////////////////////////
