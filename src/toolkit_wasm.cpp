#include "interface_binding_wasm.h"
#include <ATen/Parallel.h>

auto a = at::register_c10_thread_pool();
