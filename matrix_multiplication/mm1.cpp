#include "matrix_multiplication.hpp"

// Invert loop order for locality
// Lift B out of innermost loop
void mm1(matrix_t const & A, matrix_t const & B, matrix_t & C, std::size_t N) noexcept {
	for (std::size_t j = 0; j < N; ++j) {
		for (std::size_t k = 0; k < N; ++k) {
			auto b = B[k + j * N];
			for (std::size_t i = 0; i < N; ++i) {
				C[i + j * N] += A[i + k * N] * b;
			}
		}
	}
}
