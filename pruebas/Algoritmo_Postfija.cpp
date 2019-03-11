
#include <stdio.h>
#include <stdlib.h>

#include <algorithm>
#include <iostream>
#include <deque>
#include <stack>
#include <queue>

#include <ctype.h>
#include <string.h>
#include <string>

#include <utility>
#include <initializer_list>

// -----------------------------------------------------------------------------

// Conjunto de operacioes y operadores , tuplas y demás elementos para realizar el procesamiento númerico.

template <typename T>
using Binary_OP = T (*) (T , T);

template <typename T>
using Unary_OP = T (*) (T);

// -----------------------------------------------------------------------------

// Operaciones

static double Suma (double Num_1 , double Num_2) {
	
	return (Num_1 + Num_2);
	
}

static double Resta (double Num_1 , double Num_2) {
	
	return (Num_1 - Num_2);
	
}

static double Multiplicacion (double Num_1 , double Num_2) {
	
	return (Num_1 * Num_2);
	
}

static double Division (double Num_1 , double Num_2) {
	
	return (Num_1 / Num_2);
	
}

static double Potencia (double Num_1 , double Num_2) {
	
	signed long int Potencia = static_cast <signed long int> (Num_2);
	
	double Resultado = 1.0;
	
	while ((Potencia --) > 0) {
		
		Resultado *= Num_1;
		
	}
	
	return Resultado;
	
}

// Declaración de las operaciones.

static const Binary_OP <double> OP_Suma = 				&Suma;
static const Binary_OP <double> OP_Resta = 				&Resta;
static const Binary_OP <double> OP_Multiplicacion = 	&Multiplicacion;
static const Binary_OP <double> OP_Division = 			&Division;
static const Binary_OP <double> OP_Potencia = 			&Potencia;

// -----------------------------------------------------------------------------

// Operadores y sus niveles de prioridad.
//		Suma : 0
//		Resta : 1
//		Multi : 2
//		Divi : 3
//		Potencia : 4

// Declaramos el tipo de paridad.

typedef std::pair <std::string , char> T_Operador; // Paridad : Simbolo , Nivel de prioridad.

// Declaramos todos los operadores que tenemos con su nivel de prioridad.

static const T_Operador Operador_Suma = 		T_Operador (std::string ("+") , 0);
static const T_Operador Operador_Resta = 		T_Operador (std::string ("-") , 1);
static const T_Operador Operador_Multi = 		T_Operador (std::string ("*") , 2);
static const T_Operador Operador_Divi = 		T_Operador (std::string ("/") , 3);
static const T_Operador Operador_Potencia = 	T_Operador (std::string ("^") , 4);

// -----------------------------------------------------------------------------

// Tokenizer para separar una cadena en tokens por su separador ' '.

static std::deque <std::string> Get_Tokens (const std::string & Entrada , const char Separador = ' ') {
	
	// Tenemos una cola vacia de elementos.
	
	std::deque <std::string> Tokens;
	
	// Tenemos la cadena actualmente procesando.
	
	std::string Cadena_Actual;
	
	// Iremos insertando token por token que tenga la cadena de entrada.
	
	for (char Elemento : Entrada) {
		
		// Si el elemento es diferente al separador entones la concatenamos con la cadena.
		
		if (Elemento !=  Separador) {
			
			// Anexamos este caracter a la cadena actual.
			
			Cadena_Actual.append (1 , Elemento);
			
		}
		else {
			
			// Aqui termina la cadena actual por lo que  pasamos al siguiente token y metemos el actual en la cola.
			
			Tokens.push_back (std::move (Cadena_Actual));
			
			// Asignamos una cadena vacia.
			
			Cadena_Actual = std::string ();
			
		}
		
	}
	
	// Si el ultimo elemento no está vacio entonces lo anexamos tambien.
	
	if (!Cadena_Actual.empty ()) {
		
		// Anexamos este ultimo token a la deque.
		
		Tokens.push_back (std::move (Cadena_Actual));
		
	}
	
	// Terminamos y devolvemos los tokens.
	
	return Tokens;
	
}

// Para determinar si una cadena es un numero.

static bool Is_Number (const std::string & Cadena) {
	
	// Devolvemos true si es un numero.
	
	try {
		
		double Numero = std::stod (Cadena);
		
	}
	catch (...) {
		
		// Devolvemos falso.
		
		return false;
		
	}
	
	// Devolvemos true.
	
	return true;
	
}

// Para determinar si es un operador de los antes declarados.

static bool Is_Op (const std::string & Cadena) {
	
	// Devolvemos true si cuadra con alguno de nuestros operadores.
	
	if (Cadena == Operador_Suma.first) {
		
		return true;
		
	}
	else if (Cadena == Operador_Resta.first) {
		
		return true;
		
	}
	else if (Cadena == Operador_Multi.first) {
		
		return true;
		
	}
	else if (Cadena == Operador_Divi.first) {
		
		return true;
		
	}
	else if (Cadena == Operador_Potencia.first) {
		
		return true;
		
	}
	
	// Devolvemos falso.
	
	return false;
	
}

// Para obtener el T_Operador con base a una cadena tenemos este metodo.

static T_Operador Get_Op (const std::string & Cadena) {
	
	// Devolvemos la operacion si cuadra con alguno de nuestros operadores.
	
	if (Cadena == Operador_Suma.first) {
		
		return Operador_Suma;
		
	}
	else if (Cadena == Operador_Resta.first) {
		
		return Operador_Resta;
		
	}
	else if (Cadena == Operador_Multi.first) {
		
		return Operador_Multi;
		
	}
	else if (Cadena == Operador_Divi.first) {
		
		return Operador_Divi;
		
	}
	else {
		
		return Operador_Potencia;
		
	}
	
}

// Algoritmo para la conversión de notación infija a postfija.

static std::string Conversion_Postfija (const std::string & Infija) {
	
	// Primero leeremos de izquierda a derecha para poder ir determinando los operadores y los numeros conforme van apareciendo y los iremos colocando en una
	// pila para cada caso , la pila de operadores y la de numeros implementadas con deque.
	
	std::stack <std::string> Numeros;
	std::stack <T_Operador> Operadores;
	
	// Obtendremos todos los tokens de la cadena de entrada.
	
	std::deque <std::string> Tokens (std::move (Get_Tokens (Infija)));
	
	// Ahora iremos recorriendo la expresión de izquierda a derecha , token por token.
	
	int N = 0;
	
	for (const std::string & Token_Actual : Tokens) {
		
		printf (" >> Token %i : [%s] \n" , (++ N) , Token_Actual.c_str ());
		
		if (Is_Number (Token_Actual)) {
			
			// Anexamos el elemento a la pila de numeros en ese orden.
			
			Numeros.push (Token_Actual);
			
		}
		else if (Is_Op (Token_Actual)) {
			
			// Obtenemos el operador actual.
			
			const T_Operador Op_Actual (Get_Op (Token_Actual));
			
			// Validamos si el operador actualmente en la pila es de menor prioridad , si no es asi entonces hacemos lo siguiente.
			
			if (!Operadores.empty () && (Op_Actual.second < Operadores.top ().second)) {
				
				// Desapilamos los dos valores de la pila de numeros.
				
				const std::string Val_B (Numeros.top ());
				
				Numeros.pop ();
				
				const std::string Val_A (Numeros.top ());
				
				Numeros.pop ();
				
				// Sacamos el operador de mayor peso de la pila.
				
				const T_Operador Operador_C (Operadores.top ());
				
				// Lo quitamos de la pila.
				
				Operadores.pop ();
				
				// Ahora hacemos una nueva cadena conformada por los operandos A B y el Operador sacado de la pila. Dicha cadena la
				// colocaremos en la pila de numeros para sustituir asi lo que teniamos.
				
				std::string Numero_C (Val_A + " " + Val_B + " " + Operador_C.first);
				
				// Apilamos la cadena invertida
				
				Numeros.push (std::move (std::string (Numero_C.crbegin () , Numero_C.crend ())));
				
			}
			
			// Anexamos el elemento a la pila de operadores.
			
			Operadores.push (Op_Actual);
			
		}
		else {
			
			// Terminamos el bucle.
			
			break;
			
		}
		
	}
	
	// Crearemos la cadena de postfija inversa.
	
	std::string Postfija_Inversa;
	
	// Sacamos los numeros en el orden inverso al que fueron colocados en la cadena de postfija.
	
	while (!Numeros.empty ()) {
		
		// Sacamos el ultimo elemento y lo ponemos en la cadena de postfija inversa.
		
		Postfija_Inversa.append (Numeros.top ());
		
		// Quitamos el ultimo elemento.
		
		Numeros.pop ();
		
	}
	
	// Crearemos la cadena postfija con esta cadena invertida.
	
	std::string Postfija (Postfija_Inversa.crbegin () , Postfija_Inversa.crend ());
	
	// Por ultimo tenemos que ir quitando y pre-anexando a la cadena de postfija los operadores  en el orden en el que van saliendo de la pila y luego los numeros igual.
	
	while (!Operadores.empty ()) {
		
		// Sacamos el ultimo elemento y lo ponemos en la cadena de postfija inversa.
		
		Postfija.append (Operadores.top ().first);
		
		// Quitamos el ultimo elemento.
		
		Operadores.pop ();
		
	}
	
	// Finalmente devolvemos el resultado invertido.
	
	return Postfija;
	
}

// -----------------------------------------------------------------------------

// Notación Infija :
//		3 + 2 * 4
// Notación Postfija :
//		3 2 4 * +

int main () {
	
	printf ("\n >> Programa que convierte Notación infija a postfija << \n");
	printf (" >> --------------------------------------------------------- << \n");
	
	char Entrada [200];
	
	printf (" >> Escribe la expresión en notación infija : ");
	fflush (stdin);
	gets (Entrada);
	
	printf (" >> --------------------------------------------------------- << \n");
	printf (" >> Expresión Infija : %s \n" , Entrada);
	
	std::string Salida (std::move (Conversion_Postfija (std::string (Entrada))));
	
	printf (" >> Expresión Postfija : %s \n" , Salida.c_str ());
	
	system ("pause");
	return EXIT_SUCCESS;
	
}
