#include <iostream>
#include <fstream>
#include <complex>

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

int main() {
    int width = 1600;
    int height = 1200;
    int max_iter = 1000;

    write_ppm("mandelbrot_color.ppm", width, height, max_iter);
    std::cout << "Imagen generada: mandelbrot_color.ppm" << std::endl;

    return 0;
}

