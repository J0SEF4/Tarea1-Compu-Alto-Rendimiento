# Tarea1-Compu-Alto-Rendimiento

# Pregunta 1

1. Para compilar:
- En Ubuntu WSL
- Voy a donde está CMakeLists.txt
- Creo la carpeta de compilación y compilo, esto nos genera un ejecutable llamado main:
```bash
mkdir build
cd build
cmake ..
cmake --build .
```

2. Ejecutar el benchmark (ejecutable generado al compilar el código):
- ejecuto programa y redirige la salida a un archivo llamado output.csv:
```bash
./main > output.csv
```
Teniendo el fromato de:
```csv
function,size,time
mm0,4,0.000123
mm1,4,0.000100
mm2,4,0.000080
...
```

3. Para graficar los resultados, voy a directorio donde está plot.py y ejecuto el siguiente comando:
```bash
python3 plot.py build/output.csv grafico1.png
```
