#include <Kokkos_Core.hpp>
#include <cstddef>

template <class T> void saxpy(std::size_t N, T alpha) {
  Kokkos::initialize();

  {
    Kokkos::View<T *> x("x", N), y("y", N), z("z", N);
    Kokkos::parallel_for(
        N, KOKKOS_LAMBDA(std::size_t i) { z[i] = alpha * x[i] + y[i]; });
  }

  Kokkos::finalize();
}
