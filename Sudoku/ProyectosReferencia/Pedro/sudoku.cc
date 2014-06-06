/**
 * Proyecto 3: Sudoku
 * 
 * Inteligencia Artificial (CI5437)
 * 
 * 
 * 
 * 
 * 
 * Ultima modificacion: 19/11/2012
 * 
 * \autor	Andreina Garcia			08-10406
 * 			Jose Antonio Rodriguez	08-10971
 * 			Pedro Romero			08-10992
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

// Representacion del tablero en celdas, filas, columnas y subtableros
const int celdas[82] = {
	  1,  10,  19,  28,  37,  46,  55,  64,  73, 
	 82,  91, 100, 109, 118, 127, 136, 145, 154, 
	163, 172, 181, 190, 199, 208, 217, 226, 235,
	244, 253, 262, 271, 280, 289, 298, 307, 316,
	325, 334, 343, 352, 361, 370, 379, 388, 397,
	406, 415, 424, 433, 442, 451, 460, 469, 478,
	487, 496, 505, 514, 523, 532, 541, 550, 559,
	568, 577, 586, 595, 604, 613, 622, 631, 640,
	649, 658, 667, 676, 685, 694, 703, 712, 721, 730
};
const int filas[10] = {1, 82, 163, 244, 325, 406, 487, 568, 649, 730};
const int columnas[9] = {1, 10, 19, 28, 37, 46, 55, 64, 73};
const int subt[9] = {1, 28, 55, 244, 271, 298, 487, 514, 541};

string buffer;	// Especificacion en CNF de las clausulas iniciales
int num_clausulas; // Cantidad de clausulas generadas


/**
 * agregar_clausula
 * 
 */
void agregar_clausula(int vars[], int n) {
	char c[4];
	string clausula;
	sprintf(c, "%d ", vars[0]);
	clausula.append(c);
	for (int i = 1; i < n; ++i) {
		sprintf(c, "%d ", vars[i]);
		clausula.append(c);
	}
	clausula.append("0\n");
	//cout << "CLAU " << clausula << endl;
	buffer.append(clausula);
	++num_clausulas;
}

/**
 * agregar_subt 
 * 
 */
void agregar_subt(int sub) {
	int dif[4];
	int dos[2];
	int cont;
	for (int k = 0; k < 9; ++k) { // Valores
		for (int i = 0; i < 3; ++i) { // Fila
			for (int j = 0; j < 3; ++j) { // Columna
				cont = 0;
				for (int ii = 0; ii < 3; ++ii) {
					if (ii != i) {
						for (int jj = 0; jj < 3; ++jj) {
							if (jj != j) {
								dif[cont] = -(k + ii*81 + 1 + jj*9 + 27*(sub%3) + floor(sub / 3)*243);
								++cont;
							}
						}
					}
				}
				dos[0] = dif[0];
				dos[1] = dif[1];
				agregar_clausula(dos, 2);
				dos[0] = dif[0];
				dos[1] = dif[2];
				agregar_clausula(dos, 2);
				dos[0] = dif[0];
				dos[1] = dif[3];
				agregar_clausula(dos, 2);
				dos[0] = dif[1];
				dos[1] = dif[2];
				agregar_clausula(dos, 2);
				dos[0] = dif[1];
				dos[1] = dif[3];
				agregar_clausula(dos, 2);
				dos[0] = dif[2];
				dos[1] = dif[3];
				agregar_clausula(dos, 2);
			}
		}
	}
}


/**
 * Programa principal
 * \param argc numero de argumentos ingresados
 * \param argv lista de argumentos ingresados (archivo del sudoku)
 * \return 0 en caso de exito, -1 en caso de error
 */
int main (int argc, char* argv[]) {
	num_clausulas = 0;
	// Creacion de clausulas que representan las reglas del juego
	int vals[9];
	int doble[2];
	// Cada celda posee un unico valor
	for (int k = 0; k < 81; ++k) {
		int ini = celdas[k];
		for (int i = 0; i < 9; ++i) {
			vals[i] = ini;
			++ini;
		}
		agregar_clausula(vals, 9);
	}
	for (int r = 0; r < 9; ++r) {
		for (int c = 0; c < 9; ++c) {
			for (int vi = 1; vi < 9; ++vi) {
				for (int vj = vi + 1; vj <= 9; ++vj) {
					doble[0] = -(vi + r*81 + c*9);
					doble[1] = -(vj + r*81 + c*9);
					agregar_clausula(doble, 2);
				}
			}
		}
	}
	// Filas con todos los numeros y sin numeros repetidos
	for (int r = 0; r < 9; ++r) {
		for (int v = 0; v < 9; ++v) {
			for (int c = 0; c < 9; ++c)
				vals[c] = filas[c] + r * 9 + v;
			agregar_clausula(vals, 9);
		}
	}
	for (int r = 0; r < 9; ++r) {
		for (int v = 1; v <= 9; ++v) {
			for (int ci = 0; ci < 8; ++ci) {
				for (int cj = ci + 1; cj < 9; ++cj) {
					doble[0] = -(v + r*81 + ci*9);
					doble[1] = -(v + r*81 + cj*9);
					agregar_clausula(doble, 2);
				}
			}
		}
	}
	// Columnas con todos los numeros y sin numeros repetidos
	for (int c = 0; c < 9; ++c) {
		for (int v = 0; v < 9; ++v) {
			for (int r = 0; r < 9; ++r)
				vals[r] = columnas[r] + c * 81 + v;
			agregar_clausula(vals, 9);
		}
	}
	for (int c = 0; c < 9; ++c) {
		for (int v = 1; v <= 9; ++v) {
			for (int ri = 0; ri < 8; ++ri) {
				for (int rj = ri + 1; rj < 9; ++rj) {
					doble[0] = -(v + ri*81 + c*9);
					doble[1] = -(v + rj*81 + c*9);
					agregar_clausula(doble, 2);
				}
			}
		}
	}
	// Subtableros sin numeros repetidos, sin tomar en cuenta fila y columnas
	/*for (int ro = 0; ro < 3; ++ro) {
		for (int co = 0; co < 3; ++co) {
			for (int v = 1; v <= 9; ++v) {
				for (int r = 0; r < 8; ++r) {
					for (int c = r + 1; c < 9; ++c) {
						doble[0] = -(v + (ro * 3 + (r % 3))*81 + (co * 3 + (r % 3))*9);
						doble[1] = -(v + (ro * 3 + (c % 3))*81 + (co * 3 + (c % 3))*9);
						if (doble[0] != doble[1])
							agregar_clausula(doble, 2);
					}
				}
			}
		}
	}*/
	int cont;
	for (int ro = 0; ro < 3; ++ro) {
		for (int co = 0; co < 3; ++co) {
			for (int v = 1; v <= 9; ++v) {
				cont = 0;
				for (int r = 0; r < 3; ++r) {
					for (int c = 0; c < 3; ++c) {
						vals[cont] = v + (ro * 3 + r) * 81 + (co * 3 + c) * 9;
						++cont;
					}
				}
				agregar_clausula(vals, 9);
			}
		}
	}
	for (int i = 0; i < 9; ++i)
		agregar_subt(i);
	//cout << "Numero de clausulas generadas: " << num_clausulas << endl;
	// Se leen del archivo las clausulas instanciadas
	char linea[85];
	char l[1];
	int pos;
	int numero;
	string cl_inst;
	int num_cl_inst;
	if (argc == 2) {
		FILE *archivo = fopen(argv[1], "r");
		if (archivo == NULL) {
			cout << "Error leyendo archivo " << argv[1] << endl;
			return(-1);
		}
		ofstream sudoku_resp;
		sudoku_resp.open("soluciones_sudoku.txt");
		while (!feof(archivo)) {
			pos = 0;
			cl_inst.clear();
			num_cl_inst = 0;
			if (fgets(linea, 85, archivo) != NULL) {
				for (int i = 0; i < 81; ++i) {
					if (linea[i] != '.') {
						l[0] = linea[i];
						l[1] = '\0';
						numero = atoi(l);
						int cl = pos * 9 + numero;
						char c[4];
						sprintf(c, "%d ", cl);
						cl_inst.append(c);
						cl_inst.append("0\n");
						++num_cl_inst;
					}
					++pos;
				}
			}
			// Se genera el archivo temporal con el CNF que recibira el minisat
			if (num_cl_inst > 0) {
				int total = num_clausulas+num_cl_inst;
				ofstream archivo_cnf;
				archivo_cnf.open("clausulas_cnf");
				archivo_cnf << "p cnf 729 ";
				archivo_cnf << total;
				archivo_cnf << "\n";
				archivo_cnf << buffer;
				archivo_cnf << cl_inst;
				archivo_cnf.close();
				// Se ejecuta el minisat con el archivo de clausulas en CNF
				// y el archivo temporal de salida sat_resp
				int resp = system("./mainsat clausulas_cnf sat_resp");
				// Se decodifica el resultado en sat_resp
				ifstream resp_sat ("sat_resp");
				if (resp_sat.is_open()) {
					string sat;
					resp_sat >> sat;
					if (sat.compare("SAT") == 0) {
						while (resp_sat.good()) {
							resp_sat >> resp;
							if (resp > 0) {		// Clausulas en TRUE
								resp = resp % 9;
								if (resp == 0)
									resp = 9;
								sudoku_resp << resp;
							}
						}
						resp_sat.close();
						sudoku_resp << "\n";
					} else if (sat.compare("UNSAT") == 0) 
						sudoku_resp << "INSATISFACIBLE\n";
					else 
						sudoku_resp << "INDETERMINADO\n";
				} else {
					cout << "Error leyendo archivo sat_resp" << endl;
					return(-1);
				}
			}
		}
		fclose(archivo);
		sudoku_resp.close();
		// Se eliminan los archivos temporales
		remove("clausulas_cnf");
		remove("sat_resp");
	} else {
		cout << "No se indico archivo con sudokus iniciales." << endl;
		return(-1);
	}
	return 0;
}