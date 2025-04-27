#include <vector>
#include <cmath>
#include <limits>
#include <sodium.h>
#include <sodium/randombytes.h>
#include "csprng_poly.h"

static bool sodium_initialized = false;

void init_sodium() {
    if (!sodium_initialized) {
        if (sodium_init() < 0) {
            throw std::runtime_error("Failed to initialize Libsodium!");
        }
        sodium_initialized = true;
    }
}

void generate_random_int64_tensor(TTensor& tensor, int64_t q) {
    init_sodium();
    auto total_elems = tensor.numel();
    auto flattened_tensor = tensor.view(-1);
    auto accessor = flattened_tensor.packed_accessor32<int64_t, 1, at::DefaultPtrTraits>();

    double expansion_factor = 1.1; // 10% expansion
    auto collected = 0;
    std::vector<uint64_t> buffer(round(expansion_factor * total_elems));

    // Rejection sampling: max_multiple = biggest multiple of q that fits in 64 bits
    constexpr uint64_t max_random = static_cast<uint64_t>(0xFFFFFFFFFFFFFFFFULL);
    auto max_multiple = max_random - (max_random % q) - 1;

    while (collected < total_elems) {

        auto remaining = total_elems - collected;
        auto buffer_size = round(expansion_factor * remaining);

        randombytes_buf(buffer.data(), buffer_size * sizeof(uint64_t));

        uint64_t uq = static_cast<uint64_t>(q);
        for (auto i = 0; i < buffer_size && collected < total_elems; i++) {
            uint64_t val = buffer[i];
            if (val < uq) {
                accessor[collected++] = static_cast<int64_t>(val);
            } else if (val < max_multiple) {
                accessor[collected++] = static_cast<int64_t>(val % uq);
            }
        }
    }
}

void generate_random_int32_tensor(TTensor& tensor, int32_t low, int32_t high) {
    init_sodium();
    auto num_elements = tensor.numel();
    auto flattened_tensor = tensor.view(-1);
    auto accessor = flattened_tensor.packed_accessor32<int64_t, 1, at::DefaultPtrTraits>();

    uint32_t upper_bound = static_cast<uint32_t>(high - low);

    for (int64_t i = 0; i < num_elements; ++i) {
        uint32_t random_value = randombytes_uniform(upper_bound);
        accessor[i] = static_cast<int64_t>(low + static_cast<int32_t>(random_value));
    }
}

std::pair<float, float> boxMullerTransform(uint32_t r1, uint32_t r2) {
    constexpr float divisor = static_cast<float>(std::numeric_limits<uint32_t>::max()) + 1.0f; // 2^32
    constexpr float two_pi = 2.0f * static_cast<float>(M_PI); // 2 * pi

    // Convert the random integers to floats in (0, 1)
    float u1 = (static_cast<float>(r1) + 0.5f) / divisor;
    float u2 = (static_cast<float>(r2) + 0.5f) / divisor;

    // Apply the Box–Muller transform
    float magnitude = std::sqrt(-2.0f * std::log(u1));
    float z0 = magnitude * std::cos(two_pi * u2);
    float z1 = magnitude * std::sin(two_pi * u2);

    return std::make_pair(z0, z1);
}

void generate_random_normal_tensor(TTensor& tensor, float mean, float std) {
    init_sodium();
    int64_t total_elems = tensor.numel();
    auto flattened_tensor = tensor.view(-1);
    auto accessor = flattened_tensor.packed_accessor32<float, 1, at::DefaultPtrTraits>();

    // Each iteration of Box–Muller produces two normally distributed numbers.
    int64_t pairs = (total_elems + 1) / 2;

    // Buffer to hold random values
    std::vector<uint32_t> buffer(2 * pairs);
    randombytes_buf(buffer.data(), buffer.size() * sizeof(uint32_t));
    for (int64_t i = 0; i < pairs; ++i) {
        auto [z0, z1] = boxMullerTransform(buffer[2 * i], buffer[2 * i + 1]);

        accessor[2 * i] = mean + std * z0;
        if (2 * i + 1 < total_elems) {
            accessor[2 * i + 1] = mean + std * z1;
        }
    }
}
