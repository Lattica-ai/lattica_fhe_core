#pragma once

#include <ATen/Parallel.h>
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
void execute_with_pool(std::vector<T>& tasks, Func f, int64_t grain_size = 1) {
    at::parallel_for(0, tasks.size(), grain_size, [&](int64_t start, int64_t stop) {
        for (int64_t i = start; i < stop; ++i) {
            f(tasks[i]);
        }
    });
}