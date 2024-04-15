#include <RAJA/RAJA.hpp>
#include <umpire/Umpire.hpp>

using exec_policy = RAJA::omp_parallel_for_exec;

template <class T> void saxpy(std::size_t N, T alpha) {
  auto &rm = umpire::ResourceManager::getInstance();
  umpire::Allocator alloc = rm.getAllocator("HOST");

  T *x = static_cast<T *>(alloc.allocate(sizeof(T) * N));
  T *y = static_cast<T *>(alloc.allocate(sizeof(T) * N));
  T *z = static_cast<T *>(alloc.allocate(sizeof(T) * N));

  RAJA::forall<exec_policy>(RAJA::TypedRangeSegment<std::size_t>(0, N),
                            [=](std::size_t i) { z[i] = alpha * x[i] + y[i]; });

  alloc.deallocate(x);
  alloc.deallocate(y);
  alloc.deallocate(z);
}
