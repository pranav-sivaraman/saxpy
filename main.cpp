#include <chrono>
#include <cstdint>
#include <fmt/format.h>

#if (USE_OPENMP) || defined(USE_SERIAL)
#include "OMP-saxpy.hpp"
#ifdef USE_SERIAL
#define IMPL "Serial"
#else
#define IMPL "OpenMP"
#endif
#elif defined(USE_KOKKOS)
#define IMPL "Kokkos"
#include "Kokkos-saxpy.hpp"
#elif defined(USE_RAJA)
#include "RAJA-saxpy.hpp"
#define IMPL "RAJA"
#endif

int main(int argc, char *argv[]) {
  std::size_t N = UINT32_MAX;
  float alpha = 0.5;

  fmt::println("# of Elements: {}", N);
  const auto start{std::chrono::steady_clock::now()};
  saxpy<float>(N, alpha);
  const auto end{std::chrono::steady_clock::now()};
  const std::chrono::duration<double> elapsed_seconds{end - start};

  fmt::println("Finished {} SAXPY in {} seconds!", IMPL,
               elapsed_seconds.count());

  return 0;
}
