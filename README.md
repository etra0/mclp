# Maximal Covering Location Problem
* Nombre: Sebastián Aedo
* Rol: 201573057-1

# Instrucciones:

Para compilar la versión release solo basta con ejecutar
```bash
make release
```

Y luego para ejecutar
```bash
./bin/mclp ./instances/SJC818.txt ./instances/demand-SJC818.dat 5 1200 1000
```

Para revisar los parámetros, se puede ejecutar
```bash
./bin/mclp -h
```

La versión por defecto no guardará ningún archivo más que la solución final
como `best_solution` (además de mostrar por pantalla cual es la mejor solución).

Se puede compilar una versión que guarda todas las soluciones (útil para
generar animaciones)
```bash
# Asegurarse de que el directorio build está vacío
make clean
CFLAGS="-DSAVE_SOLUTIONS" make release
```

Se implementaron 2 soluciones iniciales, una solución completamente aleatoria y
otra con solución inicial Greedy. La compilada por defecto es la que ocupa la
solución inicial Greedy. Para compilar la solución inicial aleatoria se hace lo
siguiente:

```bash
# Asegurarse de que el directorio build está vacío
make clean

# Si se quiere compilar la solucion inicial aleatoria
CFLAGS="-DRANDOM_SOL" make release

# Alternativamente, se puede especificar la seed a utilizar
CFLAGS="-DRANDOM_SOL -DSEED=2910" make release
```

# Estructura del proyecto

```
├── Makefile
├── README.md
├── bin # Where the binaries will be stored
│   └── (...)
├── instances
│   └── (...)
├── solutions
├── src
│   ├── argparse.cpp
│   ├── base_structure.cpp
│   ├── main.cpp # Minimal main para manejar la logica principal.
│   ├── solver.cpp
│   ├── utils.cpp
│   └── mclp # Carpeta con todos los headers (donde están la mayoría de los comentarios)
│       ├── argparse.hpp # Lógica de parseo de argumentos
│       ├── base_structure.hpp # Definición de estructuras básicas como dominio y nodos
│       ├── solver.hpp # Definición de la clase solver, encargada de manejar la lógica del cómputo de la solución
│       └── utils.hpp # Utilidades no estrictamente necesarias pero que ayudan al desarrollo
└── tools
    ├── generate_cases.py
    └── plot.py
```

La carpeta `src` es la que contiene el código fuente. En general, cada función
se documentó en los respectivos headers, pero en el caso de `solver.cpp` se
incluyeron comentarios adicionales de como se hicieron las funciones.
