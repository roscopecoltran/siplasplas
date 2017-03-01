#ifndef SIPLASPLAS_JOBS_WORKER_HPP
#define SIPLASPLAS_JOBS_WORKER_HPP

#include "pool.hpp"
#include "job.hpp"
#include "jobqueue.hpp"
#include <thread>
#include <atomic>

namespace cpp
{

namespace jobs
{

class Engine;

class SIPLASPLAS_JOBS_EXPORT Worker
{
public:
    enum class Mode
    {
        Async,
        Sync
    };

    enum class State
    {
        Idle,
        Running,
        Stopping
    };

    Worker(Engine* engine, std::size_t poolSize, Mode mode = Mode::Async);
    ~Worker();

    std::thread::id threadId() const;
    bool running() const;
    void run();
    void stop();
    void submit(Job* job);
    void wait(Job* job);
    Pool& pool();
    void join();

    const std::atomic<State>& state() const;
    std::size_t totalJobsRun() const;
    std::size_t totalJobsDiscarded() const;
    std::size_t cyclesWithoutJobs() const;
    std::size_t maxCyclesWithoutJobs() const;

private:
    JobQueue _workQueue;
    Pool _pool;
    Engine* _engine;
    std::thread _workerThread;
    std::thread::id _workerThreadId;
    std::atomic_bool _running;
    Mode _mode;
    std::atomic<State> _state;
    std::size_t _totalJobsRun;
    std::size_t _totalJobsDiscarded;
    std::size_t _cyclesWithoutJobs;
    std::size_t _maxCyclesWithoutJobs;

    Job* getJob();
};

}

}

#endif // SIPLASPLAS_JOBS_WORKER_HPP
