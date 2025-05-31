#include "matrix_multiplication.hpp"
#include <cmath> // for std::min
#include <immintrin.h>

// Manual vectorization using intrinsics
void mm3(matrix_t const & A, matrix_t const & B, matrix_t & C, std::size_t N) noexcept {
	constexpr std::size_t L1 = 1 << 15;
	constexpr std::size_t n = std::sqrt(L1 / (3.0 * sizeof(double)));
	constexpr int v = 4;

	for (std::size_t j = 0; j < N; j += n) {
		for (std::size_t k = 0; k < N; k += n) {
			for (std::size_t i = 0; i < N; i += n) {
				// Macro-kernel
				for (std::size_t jj = j; jj < std::min(j + n, N); jj += v) {
					for (std::size_t kk = k; kk < std::min(k + n, N); kk += v) {
						for (std::size_t ii = i; ii < std::min(i + n, N); ii += v) {
							// Micro-kernel
							auto a = A.data() + ii + kk * N;
							auto b = B.data() + kk + jj * N;
							auto c = C.data() + ii + jj * N;

							auto a0_ = _mm256_loadu_pd(a + 0 * N);
							auto a1_ = _mm256_loadu_pd(a + 1 * N);
							auto a2_ = _mm256_loadu_pd(a + 2 * N);
							auto a3_ = _mm256_loadu_pd(a + 3 * N);

							for (int cc = 0; cc < 4; ++cc) {
								auto b00 = _mm256_broadcast_sd(b + 0 + cc * N);
								auto b01 = _mm256_broadcast_sd(b + 1 + cc * N);
								auto b02 = _mm256_broadcast_sd(b + 2 + cc * N);
								auto b03 = _mm256_broadcast_sd(b + 3 + cc * N);

								auto c0_ = _mm256_loadu_pd(c + cc * N);
								c0_ = _mm256_add_pd(c0_,
									_mm256_add_pd(
										_mm256_add_pd(
											_mm256_mul_pd(a0_, b00),
											_mm256_mul_pd(a1_, b01)
										),
										_mm256_add_pd(
											_mm256_mul_pd(a2_, b02),
											_mm256_mul_pd(a3_, b03)
										)
									)
								);

								_mm256_storeu_pd(c + cc * N, c0_);
							}
						}
					}
				}
			}
		}
	}
}
