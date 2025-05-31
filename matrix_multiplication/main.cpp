#include <iostream>
#include <chrono>
#include <cstdlib>
#include <random>

#include "matrix_multiplication.hpp"

double benchmark(function_t f, matrix_t const & A, matrix_t const & B, matrix_t & C, std::size_t N) noexcept {
	for (std::size_t i = 0; i < N * N; ++i) {
		C[i] = 0;
	}

	auto start = std::chrono::high_resolution_clock::now();
	f(A, B, C, N);
	auto end = std::chrono::high_resolution_clock::now();

	return std::chrono::duration<double>(end - start).count();
}

int main() {
	std::mt19937 gen;
	std::uniform_real_distribution<double> dis(0, 1);


	constexpr int runs = 2;

	#define BENCHMARK(f) do { \
		for (int i = 0; i < runs; ++i) { \
			auto time = benchmark(f, A, B, C, N); \
			std::cout << #f << ',' << N << ',' << time << std::endl; \
		} \
	} while (false)

	std::cout << "function,size,time" << std::endl;

	for (int N = 4; N <= 2*1024; N *= 2) {
		matrix_t A(N * N);
		matrix_t B(N * N);
		matrix_t C(N * N);

		for (std::size_t i = 0; i < N * N; ++i) {
			A[i] = dis(gen);
			B[i] = dis(gen);
		}

		BENCHMARK(mm0);
		BENCHMARK(mm1);
		BENCHMARK(mm2);
		BENCHMARK(mm3);
	}

	#undef BENCHMARK
}
