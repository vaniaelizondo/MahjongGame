//
//  main.cpp
//  ProyectoFinalMahjong
//
//  Created by Vania Elizondo on 7/11/15.
//  Copyright © 2015 Vania Elizondo. All rights reserved.
//

#include <iostream>
#include <iomanip>
using namespace std;

// diseño: juego Mahjong
//          • El objetivo del juego es eliminar todas las fichas del tablero.
//          • Se pueden eliminar fichas del tablero seleccionando 2 fichas iguales que estén libres.
//          • Una ficha está libre cuando no tiene fichas a su lado derecho o a su lado izquierdo.
//          • El jugador gana si elimina todas las fichas del tablero.

// algoritmo:   - mostrar tablero aleatorio de 40 fichas 5 renglones y 8 columnas. En cada casilla se muestra numero y caracter
//				  correspondiente
//              - mostrar el numero de fichas que quedan en el tablero
//              - pedir que el usuario elija dos casillas
//              - leerlos y verificar lo siguiente:
//					- condiciones:  • No se pueda seleccionar la misma casilla como casilla 1 y casilla 2.
//									• No se pueda seleccionar una casilla que no tiene ficha.
//									• No se pueda seleccionar una casilla que no esté libre.
//              - eliminar fichas si las 2 casillas son iguales y cumple con lo anterior
//              - preguntar si desea seguir jugando (validar letra)
//              - repetir hasta que el usuario indique lo contrario o mostrar mensaje que ganó cuando todas las fichas hayan sido
//				  eliminadas

// casos de prueba: al escoger dos casillas con el mismo caracter que esten bloqueadas no se eliminen


char cMatTablero[5][8];
char cArrFiguras[10] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

// funcion que genera caracteres aleatorios
void llenaTablero()
{
    int iR, iC, iContFicha, iValorFicha;
    
    // primero inicializa el arreglo con espacios en blanco
    for (iR = 0; iR < 5; iR++)
        for (iC = 0; iC < 8; iC++)
            cMatTablero[iR][iC] = ' ';
    
    srand((int)time(0));
    for (iValorFicha = 0, iContFicha = 0; iValorFicha < 10;
         iContFicha = 0, iValorFicha++)
    {
        do
        {
            iR = rand() % (5);
            iC = rand() % (8);
            if (cMatTablero[iR][iC] == ' ')
            {
                cMatTablero[iR][iC] = cArrFiguras[iValorFicha];
                iContFicha++;
            }
        } while (iContFicha != 4); // debo poner 4 Fichas de cada numero
    }
}

// funcion que muestra el formato del tablero como (nn) y caracter
void muestraTablero()
{
    int iN = 1;
    
    for (int iR = 0; iR < 5; iR++){
        for (int iC = 0; iC < 8; iC++, iN++){
            cout << '(' << setfill(' ') << setw(2) << iN << ')';
			cout << cMatTablero[iR][iC] << ' ';
        }
        cout << endl;
    }
}

// funcion que guarda qué caracter tiene la ficha seleccionada
void localizaFicha(int iF, char &cLugar)
{
	int iCont = 1;
	
	for (int iR = 0; iR < 5; iR++){
		for (int iC = 0; iC < 8; iC++, iCont++){
			if (iF == iCont)
			{
				cLugar = cMatTablero[iR][iC];
			}
		}
	}
}

// funcion que determina si la ficha seleccionada esta libre, si no hay una ficha con caracter antes o despues
void fichaLibre(int iF, bool &bFree)
{
	int iCont = 1;
	
	for (int iR = 0; iR < 5; iR++) {
		for (int iC = 0; iC < 8; iC++, iCont++) {
			if (iF == iCont) {
				if (iC == 0 || iC == 7 || cMatTablero[iR][iC-1] == ' ' || cMatTablero[iR][iC+1] == ' ')
					bFree = true;
				
				else
					bFree = false;
			}
		}
	}
}

// funcion que elimina un caracter de una ficha
void elimina(int iF)
{
	int iCont = 1;
	
	for (int iR = 0; iR < 5; iR++){
		for (int iC = 0; iC < 8; iC++, iCont++){
			if (iF == iCont)
			{
				cMatTablero[iR][iC] = ' ';
			}
		}
	}
}

int main() {
    int iCas1, iCas2, iNumFichas = 40;
	char cContinuar, cFigura1, cFigura2;
	bool bLibre1, bLibre2;
	
	// solo se generan los caracteres aleatorios una vez
	llenaTablero();
	
	// se muestra el tablero con los carecteres aleatorios
	muestraTablero();
	
    do {
		
		// muestra el numero de las fichas restantes
        cout << "Quedan " << iNumFichas << " fichas" << endl;
		
		// pide y valida casilla 1
		do {
			cout << "Casilla 1 -> ";
			cin >> iCas1;
			
			localizaFicha(iCas1, cFigura1);
			
			fichaLibre(iCas1, bLibre1);
			
		} while (iCas1 < 1 || iCas1 > 40 || cFigura1 == ' ' || bLibre1 == false);
		
		
		// pide y valida casilla 2
		do {
			cout << "Casilla 2 -> ";
			cin >> iCas2;
			
			localizaFicha(iCas2, cFigura2);
			
			fichaLibre(iCas2, bLibre2);
			
		} while (iCas2 < 1 || iCas2 > 40 || cFigura2 == ' ' || bLibre2 == false || iCas2 == iCas1);
		
		
		// comparar si las 2 fichas tienen caracteres iguales y eliminarlos
		if (cFigura1 == cFigura2)
		{
			elimina(iCas1);
			elimina(iCas2);
			iNumFichas -= 2;
		}
		
		// muestra el tablero actualizado
		muestraTablero();
		
		
		// al terminar el juego
		if (iNumFichas == 0)
		{
			cout << "Has ganado" << endl;
			return 0;
		}
		
		
		// preguntar si desea seguir jugando y validarlo
        do {
            cout << "Seguir (s/n) -> ";
            cin >> cContinuar;
			
			cContinuar = toupper(cContinuar);
			
        } while (cContinuar != 'S' && cContinuar != 'N');
		
		
    } while (cContinuar == 'S');
    
    return 0;
}
