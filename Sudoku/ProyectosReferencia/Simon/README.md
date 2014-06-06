* Sudoku Solver

** Que debería haber en esta carpeta

- encoder.hs
- decoder.hs
- Makefile
- glucose_2.1
- sudoku_*.txt 
- sudoku_solver*.sh
- sudoku_file*.sh
- common

** Requisitos

Para poder compilar el proyecto hay dos maneras, la fácil y la
difícil. El proyecto requiere instalar una serie de dependencias que
podrían no estar disponibles en la distribución/sistema operativo que
se utilice. Nosotros proveeremos instrucciones para obtener estas
dependencias en Ubuntu 12.04 funcionando en 64bits.

El camino difícil consiste en instalar las dependencias y compilar. El
camino fácil consiste en conectarse por ssh a una cuenta que hemos
preparado que ya tiene el proyecto y las dependencias compiladas.

*** Camino Fácil

El password para el usuario es bl41b0n3t$ci5437

$ ssh ci5437@seriola.cbm.usb.ve

Esta cuenta estara disponible siempre y cuando todas las catastrofes
de la universidad no se junten, esto es: haya luz, haya internet y muy
posiblemente no llueva.

*** Camino Difícil

El encoder y el decoder están escritos en Haskell. Por lo tanto, para
poder compilar se requiere la plataforma Haskell que provee GHC
(http://www.haskell.org/ghc/download). Para instalar en Debian/Ubuntu:

$ sudo apt-get install ghc 

El SAT solver que seleccionamos es Glucose
(http://www.lri.fr/~simon/?page=glucose). Este SAT solver fue diseñado
para correr únicamente en máquinas 32 bits, por lo que para compilarlo
en 64 bits se necesitan las librerías multilib en Debian/Ubuntu: 

$ sudo apt-get install build-essential zlib1g-dev gcc-multilib g++-multilib

Con esto debería ser suficiente.

** Compilar

Para compilar el SAT solver:

$ cd glucose-2.1
$ ./build.sh

Para compilar el encoder y el decoder:

$ make

Por si acaso, asegurarse que los permisos estén correctos:

$ chmod +x sudoku_file*.sh
$ chmod +x sudoku_solver*.sh

** Corriendo el sudoku solver

Antes de correr, debe editar el archivo sudoku_solver.sh y cambiar las
variables definidas de ser necesario. En particular, $ENCODER,
$DECODER y $SAT_SOLVER.

Una vez hecho esto puede correr una instancia en particular utilizando

$ ./sudoku_solver.sh [instancia]

O puede correr un archivo con instancias utilizando

$ ./sudoku_file.sh [archivo]

Si se desea imprimir los sudokus 'human-readable' (en una cuadricula
9x9), agregar un parametro a sudoku_solver.sh, i.e.:

$ ./sudoku_solver.sh [instancia] humano

Hay una versión que utiliza reglas estáticas (para acelerar la
generación). Los comandos son identicos excepto que se utiliza
_static. Es decir:

$ ./sudoku_solver_static.sh [instancia]

$ ./sudoku_file_static.sh [archivo]

Con esta versión se corrieron las pruebas.
