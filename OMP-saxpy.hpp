#include <vector>

template <class T> void saxpy(const std::size_t N, const T alpha) {
  std::vector<T> x(N, 0), y(N, 0), z(N, 0);
#pragma omp parallel for
  for (int i = 0; i < N; i++) {
    z[i] = alpha * x[i] + y[i];
  }
}
