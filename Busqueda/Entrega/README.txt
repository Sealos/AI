
Stefano De Colli	09-10203 	
Oskar González 		09-10351
Karen Troiano		09-10855
						 

Inteligencia Artificial I


Proyecto I - 15/24 Puzzle - Shortest Solution

Contenido:
 
* Informe.pdf
* Directorios:
	* 24-puzzle: Contiene todos los archivos .cpp y .h necesarios para 
		los casos de 24-puzzle.
	* a_star: Contiene todos los archivos .cpp y .h necesarios para 
		el algoritmo de A*.
	* ida_star: Contiene todos los archivos .cpp y .h necesarios para 
		el algoritmo de IDA*.
	* pdb_gen: Contiene todos los archivos .bin necesarios para 
		los casos con heurística pdb.
	* resultados: Contiene todos los archivos .txt con los resultados 
		de las intancias resueltas por los algoritmos.


How to:

* Para compilar el proyecto,seleccionee la carpeta a evaluar (a_star, ida_star, 24-puzzle)
y escriba:
make

* Para correr el proyecto, compilar y luego invocar con:
./main <input>

* Para correr el proyecto y probar la heurística de pdb debe asegurarse que 
 las datas se encuentran cargadas en el directorio actual.
  Las datas son archivos .bin que se encuentran en el directorio pdb_gen


* Si requiere usar la heurística PDB, las mismas están en
/pdb_gen/ y luego /15/ o /24/, copiar, descomprimir, editar el main.cpp (l: 58/37),
compilar y ejecutar.
		