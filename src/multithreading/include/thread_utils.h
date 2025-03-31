#pragma once

#include <thread>
#include "tensor_engine.h"
#include "mod_ops.h"

// Struct for parameter 'tasks' in the 'execute_with_pool' function
struct packPtArgs {
    TTensor pt;
    TTensor col;
    TTensor result;
    int64_t start;
    int64_t end;
};

// Struct for parameter 'tasks' in the 'execute_with_pool' function
struct NttArgs {
    int n;
    TTensor result;
    TTensor q_list;
    TTensor active_psi_arr;
    int64_t start;
    int64_t end;
};

template <typename T, typename Func>
void execute_with_pool(std::vector<T>& tasks, Func f) {

    struct {
        std::atomic_flag err_flag = ATOMIC_FLAG_INIT;
        std::exception_ptr eptr;
        std::atomic_size_t remaining{0};
        std::mutex mutex;
        std::condition_variable cv;
    } state;

    auto task = [f, &state, &tasks](int /* unused */, size_t task_id) {
        if (task_id < tasks.size()) {
            try {
                f(tasks[task_id]); // Execute the task
            } catch (...) {
                if (!state.err_flag.test_and_set()) {
                    state.eptr = std::current_exception();
                }
            }
        }
        {
            std::unique_lock<std::mutex> lk(state.mutex);
            if (--state.remaining == 0) {
                state.cv.notify_one();
            }
        }
    };

    state.remaining = tasks.size();
    at_lattica_nspace::_run_with_pool(std::move(task), tasks.size()); // Execute tasks in the thread pool

    // Wait for all tasks to finish
    {
        std::unique_lock<std::mutex> lk(state.mutex);
        if (state.remaining != 0) {
            state.cv.wait(lk);
        }
    }

    if (state.eptr) {
        std::rethrow_exception(state.eptr); // Rethrow if any task raised an exception
    }
}