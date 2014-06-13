Stefano De Colli	09-10203 	
Oskar González 		09-10351
Karen Troiano		09-10855
						 

Inteligencia Artificial I

Proyecto III - Sudoku

El  presente  proyecto  tiene  como  finalidad  resolver  instancias  de  Sudoku, utilizando  un solucionador SAT. El solucionador seleccionado fue minisat. 

Para  que  el  solucionador  pueda  comprender  las  clausulas del problema (ver informe) deben  estar en  texto  de formato  DIMACS,  dicho  texto  lo  generamos  utilizando  un  programa  (encoder.py)  escrito  en el lenguaje  Python3.4.1. Para cada instancia, minisat nos devuelve la solución, también  en formato DIMACS, la cual traducimos también con otro programa (decoder.py) escrito en Python3.4.1. 


Contenido:
 
* Informe.pdf : Contiene una pequeña explicación sobre el proyecto, cláusulas utilizadas y resultados obtenidos.
* encoder.py: Archivo que convierte las clausulas en un archivo en formato DIMACS.
* decoder.py: Archivo que convierte las un archivo en formato DIMACS en clausulas con la solución del problema.
* sudoku.py: Archivo maestro del proyecto. 
* minisat : Solucionador SAT utilizado.
* Resultados: Carpeta que contiene los resultados de corridas con las instancias en la página del curso.

How to:

* Para correr el proyecto tiene dos opciones:

	./sudoku.py [Instancias Entrada] [Archivo Salida]

	python3 sudoku.py [Instancias Entrada] [Archivo Salida]


		
