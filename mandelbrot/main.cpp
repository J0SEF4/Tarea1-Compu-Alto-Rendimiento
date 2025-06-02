#include <iostream>
#include <fstream>
#include <complex>
#include <vector>       
#include <chrono>       
#include <string>       
#include <fstream>      


int mandelbrot(std::complex<double> c, int max_iter, double tol = 1e-6) {
    std::complex<double> z = 0;
    int iter = 0;
    std::complex<double> prev_z;

    while (std::abs(z) <= 2.0 && iter < max_iter) {
        prev_z = z;
        z = z * z + c;
        ++iter;

        if (std::abs(z - prev_z)/std::abs(z) < tol)
            break;  // convergencia detectada
    }

    return iter;
}


// Mapea iteración a color RGB (gradiente colorido)
void iteration_to_color(int iter, int max_iter, unsigned char& r, unsigned char& g, unsigned char& b) {
    if (iter == max_iter) {
        r = g = b = 0;
        return;
    }

    double t = static_cast<double>(iter) / max_iter;
    r = static_cast<unsigned char>(9 * (1 - t) * t * t * t * 255);
    g = static_cast<unsigned char>(15 * (1 - t) * (1 - t) * t * t * 255);
    b = static_cast<unsigned char>(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
}

void write_ppm(const std::string& filename, int width, int height, int max_iter) {
    std::ofstream ofs(filename, std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";

    for (int j = 0; j < height; ++j) {
        double y = (double(j) / height) * 2.0 - 1.0;
        for (int i = 0; i < width; ++i) {
            double x = (double(i) / width) * 3.5 - 2.5;
            std::complex<double> c(x, y);
            int iter = mandelbrot(c, max_iter);

            unsigned char r, g, b;
            iteration_to_color(iter, max_iter, r, g, b);
            ofs << r << g << b;
        }
    }

    ofs.close();
}

void write_ppm_parallel(const std::string& filename, int width, int height, int max_iter, const std::string& schedule_type, int chunk_size = 1) {
    std::vector<unsigned char> image(width * height * 3);

    auto start = std::chrono::high_resolution_clock::now();

    #pragma omp parallel for collapse(2) schedule(static)
    for (int j = 0; j < height; ++j) {
        for (int i = 0; i < width; ++i) {
            double x = (double(i) / width) * 3.5 - 2.5;
            double y = (double(j) / height) * 2.0 - 1.0;
            std::complex<double> c(x, y);
            int iter = mandelbrot(c, max_iter);

            unsigned char r, g, b;
            iteration_to_color(iter, max_iter, r, g, b);

            int idx = (j * width + i) * 3;
            image[idx] = r;
            image[idx + 1] = g;
            image[idx + 2] = b;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "Tiempo (" << schedule_type << "): " << elapsed.count() << " segundos" << std::endl;

    std::ofstream ofs(filename, std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    ofs.write(reinterpret_cast<char*>(image.data()), image.size());
    ofs.close();
}

int main() {
    int width = 1600;
    int height = 1200;
    int max_iter = 1000;

    std::vector<unsigned char> image(width * height * 3);



    // --- (i) omp for con schedule ---
    
    std::cout << "\n--- (i) omp for con schedule ---" << std::endl;
    for (auto schedule_type : {"static", "dynamic", "guided"}) {
        for (int chunkSize : {10, 50, 100}) {
            auto start = std::chrono::high_resolution_clock::now();

            #pragma omp parallel
            {
                if (std::string(schedule_type) == "static") {
                    #pragma omp for schedule(static, chunkSize) nowait
                    for (int j = 0; j < height; ++j) {
                        for (int i = 0; i < width; ++i) {
                            double x = (double(i) / width) * 3.5 - 2.5;
                            double y = (double(j) / height) * 2.0 - 1.0;
                            std::complex<double> c(x, y);
                            int iter = mandelbrot(c, max_iter);

                            unsigned char r, g, b;
                            iteration_to_color(iter, max_iter, r, g, b);

                            int idx = (j * width + i) * 3;
                            image[idx] = r;
                            image[idx + 1] = g;
                            image[idx + 2] = b;
                        }
                    }
                } else if (std::string(schedule_type) == "dynamic") {
                    #pragma omp for schedule(dynamic, chunkSize) nowait
                    for (int j = 0; j < height; ++j) {
                        for (int i = 0; i < width; ++i) {
                            double x = (double(i) / width) * 3.5 - 2.5;
                            double y = (double(j) / height) * 2.0 - 1.0;
                            std::complex<double> c(x, y);
                            int iter = mandelbrot(c, max_iter);

                            unsigned char r, g, b;
                            iteration_to_color(iter, max_iter, r, g, b);

                            int idx = (j * width + i) * 3;
                            image[idx] = r;
                            image[idx + 1] = g;
                            image[idx + 2] = b;
                        }
                    }
                } else if (std::string(schedule_type) == "guided") {
                    #pragma omp for schedule(guided, chunkSize) nowait
                    for (int j = 0; j < height; ++j) {
                        for (int i = 0; i < width; ++i) {
                            double x = (double(i) / width) * 3.5 - 2.5;
                            double y = (double(j) / height) * 2.0 - 1.0;
                            std::complex<double> c(x, y);
                            int iter = mandelbrot(c, max_iter);

                            unsigned char r, g, b;
                            iteration_to_color(iter, max_iter, r, g, b);

                            int idx = (j * width + i) * 3;
                            image[idx] = r;
                            image[idx + 1] = g;
                            image[idx + 2] = b;
                        }
                    }
                }
            }

            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Tiempo (" << schedule_type << ", chunkSize=" << chunkSize << "): "
                      << std::chrono::duration<double>(end - start).count() << " segundos\n";
        }
    }
    
    // --- (ii) omp for con collapse ---
    std::cout << "\n--- (ii) omp for con collapse ---" << std::endl;
    for (auto schedule_type : {"static", "dynamic", "guided"}) {
        for (int chunkSize : {10, 50, 100}) {
            auto start = std::chrono::high_resolution_clock::now();

            #pragma omp parallel
            {
                if (std::string(schedule_type) == "static") {
                    #pragma omp for schedule(static, chunkSize) collapse(2) nowait
                    for (int j = 0; j < height; ++j) {
                        for (int i = 0; i < width; ++i) {
                            double x = (double(i) / width) * 3.5 - 2.5;
                            double y = (double(j) / height) * 2.0 - 1.0;
                            std::complex<double> c(x, y);
                            int iter = mandelbrot(c, max_iter);

                            unsigned char r, g, b;
                            iteration_to_color(iter, max_iter, r, g, b);

                            int idx = (j * width + i) * 3;
                            image[idx] = r;
                            image[idx + 1] = g;
                            image[idx + 2] = b;
                        }
                    }
                } else if (std::string(schedule_type) == "dynamic") {
                    #pragma omp for schedule(dynamic, chunkSize) collapse(2) nowait
                    for (int j = 0; j < height; ++j) {
                        for (int i = 0; i < width; ++i) {
                            double x = (double(i) / width) * 3.5 - 2.5;
                            double y = (double(j) / height) * 2.0 - 1.0;
                            std::complex<double> c(x, y);
                            int iter = mandelbrot(c, max_iter);

                            unsigned char r, g, b;
                            iteration_to_color(iter, max_iter, r, g, b);

                            int idx = (j * width + i) * 3;
                            image[idx] = r;
                            image[idx + 1] = g;
                            image[idx + 2] = b;
                        }
                    }
                } else if (std::string(schedule_type) == "guided") {
                    #pragma omp for schedule(guided, chunkSize) collapse(2) nowait
                    for (int j = 0; j < height; ++j) {
                        for (int i = 0; i < width; ++i) {
                            double x = (double(i) / width) * 3.5 - 2.5;
                            double y = (double(j) / height) * 2.0 - 1.0;
                            std::complex<double> c(x, y);
                            int iter = mandelbrot(c, max_iter);

                            unsigned char r, g, b;
                            iteration_to_color(iter, max_iter, r, g, b);

                            int idx = (j * width + i) * 3;
                            image[idx] = r;
                            image[idx + 1] = g;
                            image[idx + 2] = b;
                        }
                    }
                }
            }

            auto end = std::chrono::high_resolution_clock::now();
            std::cout << "Tiempo (collapse, " << schedule_type << ", chunkSize=" << chunkSize << "): "
                    << std::chrono::duration<double>(end - start).count() << " segundos\n";
        }
    }

    // --- (iii) Usando tasks ---
    std::cout << "\n--- (iii) Usando tasks ---" << std::endl;
    for (auto schedule_type : {"static", "dynamic", "guided"}) { 
    for (int chunkSize : {10, 50, 100}) {
        auto start = std::chrono::high_resolution_clock::now();

        #pragma omp parallel
        {
            #pragma omp single
            {
                for (int start_row = 0; start_row < height; start_row += chunkSize) {
                    int end_row = std::min(start_row + chunkSize, height);

                    #pragma omp task firstprivate(start_row, end_row)
                    {
                        for (int j = start_row; j < end_row; ++j) {
                            for (int i = 0; i < width; ++i) {
                                double x = (double(i) / width) * 3.5 - 2.5;
                                double y = (double(j) / height) * 2.0 - 1.0;
                                std::complex<double> c(x, y);
                                int iter = mandelbrot(c, max_iter);

                                unsigned char r, g, b;
                                iteration_to_color(iter, max_iter, r, g, b);

                                int idx = (j * width + i) * 3;
                                image[idx] = r;
                                image[idx + 1] = g;
                                image[idx + 2] = b;
                            }
                        }
                    }
                } 

                #pragma omp taskwait
            }
        }
    
        auto end = std::chrono::high_resolution_clock::now();
        std::cout << "Tiempo (tasks, chunkSize=" << chunkSize << "): "
                  << std::chrono::duration<double>(end - start).count() << " segundos\n";
        }
    }

    // Guardar imagen final generada
    std::ofstream ofs("mandelbrot_final.ppm", std::ios::binary);
    ofs << "P6\n" << width << " " << height << "\n255\n";
    ofs.write(reinterpret_cast<char*>(image.data()), image.size());
    ofs.close();

    return 0;
}

