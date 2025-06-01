# Tarea1-Compu-Alto-Rendimiento

# Pregunta 1
Como simples cambios alteran la performance de un codigo debido al uso de memoria caché.
Uso de matrix_multiplication hay varios archivos para la compilación y ejecución de un programa que permite calcular productos de matrices con diferentes metodos. 
- mm0: multiplicación de matrices usual.
- mm1: invertir orden de los loops.
- mm2: implementación de Blocking.
- mm3: Uso de AVX

**(a) [10pts] Compile y ejecute el programa para comparar los tiempos que requiere cada función para realizar el producto de matrices. Reporte los resultados en un gráfico y comente las diferencias. Explique en base al uso de memoria caché.**
1. Para compilar:
- Voy a donde está CMakeLists.txt
- Creo la carpeta de compilación y compilo, esto nos genera un ejecutable llamado main:
```bash
mkdir build
cd build
cmake ..
 en vez de make = cmake --build .
```
2. Ejecutar el benchmark (ejecutable generado al compilar el código):
- ejecutamos programa y redirige la salida a un archivo llamado output.csv:
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
3. Para graficar los resultados, voy a directorio donde está el archivo output.csv y ejecuto el siguiente comando:
```bash
python3 plot.py output.csv grafico.png
```
4. Comentar las diferencias. Explicando en base al uso de memoria caché. Comparar los tiempos que requiere cada función para realizar el producto de matrices.
Comparación de tiempos y caché:




(b) [10pts] Investigue el concepto de Blocking para multiplicación de matrices y explique su funcionamiento. ¿Observa alguna ventaja al comparar con los otros métodos?

Blocking para multiplicación de matrices es.... y su funcionamento es...
La ventaja al comparar con los otros métodos es....

(c) [10pts] Consulte la documentación de AVX-256 para entender el funcionamiento de mm3. Explique de manera detallada lo que ocurre en cada paso.

mm3 funciona de manera que...
