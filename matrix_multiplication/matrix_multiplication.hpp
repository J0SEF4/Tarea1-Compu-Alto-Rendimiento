#pragma once
#include <cstdint>
#include <vector>

using value_t    = double;
using matrix_t   = std::vector<value_t>;
using function_t = void (*)(matrix_t const &, matrix_t const &, matrix_t &, std::size_t N);

void mm0(     matrix_t const & A, matrix_t const & B, matrix_t & C, std::size_t N) noexcept;
void mm1(     matrix_t const & A, matrix_t const & B, matrix_t & C, std::size_t N) noexcept;
void mm2(     matrix_t const & A, matrix_t const & B, matrix_t & C, std::size_t N) noexcept;
void mm3(     matrix_t const & A, matrix_t const & B, matrix_t & C, std::size_t N) noexcept;
