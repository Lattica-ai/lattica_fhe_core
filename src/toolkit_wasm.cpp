#include "interface_binding_wasm.h"
#include "ATen/Parallel.h"

auto a = at_lattica_nspace::register_c10_thread_pool();
