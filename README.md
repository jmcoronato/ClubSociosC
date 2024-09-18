# ClubSociosC

ClubSociosC es un programa de consola implementado en C que gestiona una base de datos de socios de un club. Utiliza un archivo CSV como base de datos de entrada, genera un archivo binario para su procesamiento y un archivo .idx ordenado por la clave del registro, junto con su posicion en el archivo binario. Además, implementa un índice mediante un árbol binario de búsqueda (BST) para optimizar las búsquedas de socios en el archivo binario, levantando el archivo socios.idx.

## Características

- **Lectura de CSV**: El programa lee un archivo CSV que contiene la información de los socios.
- **Generación de archivo binario**: Convierte el CSV en un archivo binario para un acceso más eficiente.
- **Índice guardado en archivo idx y levantado en BST**: Utiliza un árbol binario de búsqueda para indexar y buscar rápidamente a los socios en el archivo binario.

## Requisitos

- Compilador de C (GCC recomendado)
- Sistema operativo compatible con herramientas de desarrollo en C (Linux, macOS, Windows)

## Compilación

- **SOLO LA PRIMERA EJECUCION** Para compilar el programa, primero abrir el ejecutable "GenerarIndice.exe" en la carpeta ClubSociosC\GenerarIndice\bin\Debug para que se genere el indice y se guarde en el archivo socios.idx.
- Luego, cada vez que se quiera ejecutar el programa, abrir el ejecutable de la ruta "ClubSociosC\ProgramaSocios\bin\Debug\ProgramaSocios.exe"
