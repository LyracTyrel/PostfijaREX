
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <string>

#include <unordered_map>
#include <unordered_set>
#include <deque>
#include <queue>
#include <stack>

#include <utility>
#include <regex>

// -----------------------------------------------------------------------------

// Prioridad de los operadores aritmeticos.

static std::unordered_map <std::string , unsigned char> Mapa_Prioridades = {
	
	std::pair <std::string , unsigned char> ("+" , (unsigned char)0) ,
	std::pair <std::string , unsigned char> ("-" , (unsigned char)1) ,
	std::pair <std::string , unsigned char> ("*" , (unsigned char)2) ,
	std::pair <std::string , unsigned char> ("/" , (unsigned char)3) ,
	std::pair <std::string , unsigned char> ("^" , (unsigned char)4) ,
	std::pair <std::string , unsigned char> ("(" , (unsigned char)10)
	
};

// Conjunto de funciones disponibles.

static std::unordered_set <std::string> Mapa_Funciones = {
	
	std::string ("sen") , std::string ("cos")
	
};

// -----------------------------------------------------------------------------

// Función eliminadora de espacios. Ejem : 3 + 2 * 4 => 3+2*4

static std::string Cadena_Limpiar (const std::string & Cadena) {
	
	// Quitaremos todos los espacios en esta cadena y la reasignaremos , por lo que tenemos la siguiente cadena resultante.
	
	std::string Resultado;
	
	// Iteramos por cada simbolo en la cadena e iremos anexandolos a nuestra cadena resultado a excepción de los espacios.
	
	for (char Simbolo : Cadena) {
		
		// Si es diferente a un espacio , salto de linea o retorno de carro lo anexamos.
		
		if ((Simbolo != '\0') && (Simbolo != ' ') && (Simbolo != '\n') && (Simbolo != '\r')) {
			
			Resultado.append (1u , Simbolo);
			
		}
		
	}
	
	// Devolvemos la cadena limpia.
	
	return Resultado;
	
}

// -----------------------------------------------------------------------------

// Expresiones regulares para determinar si una cadena cumple con lo siguiente.
//		Numero : ([0-9])+((.)([0-9])+)? , Por ejemplo : 2.4 , 300 , 12 , 4 , -5 , etc.
//		Simbolo : (\+|\-|\*|\/|\^)

static const std::regex Expresion_Numero 	(std::string ("([0-9])+((.)([0-9])+)?"));
static const std::regex Expresion_Operador 	(std::string ("(\\+|\\-|\\*|\\/|\\^)"));

// Cadena Numerica.

static inline bool Is_Number (const std::string & Cadena) {
	
	// Validaremos usando la expresión regular de numeros.
	
	return std::regex_match (Cadena , Expresion_Numero);
	
}

// Cadena Operador.

static inline bool Is_Operator (const std::string & Cadena) {
	
	// Validaremos de igual forma.
	
	return std::regex_match (Cadena , Expresion_Operador);
	
}

// Comprobamos si es función valida.

static inline bool Is_Function (const std::string & Cadena) {
	
	// Si esta dentro del conjunto es valida.
	
	return (Mapa_Funciones.count (Cadena) > 0);
	
}

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

// Sustitución de elementos.

static std::string Sustituir (std::deque <std::string> & Pila_Numeros , std::stack <std::string> & Pila_Operadores) {
	
	// Cadena postfija.
	
	std::string Cadena_Postfija;
	
	// Ahora solo resta organizar la expresión en notación postfija usando las pilas , para ello vamos primero a poner los elementos de la pila de
	// numeros en el orden inverso al que se van a ir obteniendo , primero el primero en ser apilado.
	
	std::deque <std::string> Lista_Caracteres;
	
	// Colocaremos todos los que tenemos en la pila.
	
	while (!Pila_Numeros.empty ()) {
		
		// Sacamos el ultimo de la pila y lo ponemos al principio de la lista.
		
		Lista_Caracteres.push_front (Pila_Numeros.back ());
		
		// Lo sacamos de la pila.
		
		Pila_Numeros.pop_back ();
		
	}
	
	// Ahora que ya tenemos los numeros , anexaremos los operadores al final de la lista en el orden en el que van saliendo de la pila.
	
	while (!Pila_Operadores.empty ()) {
		
		// Sacamos el operador siguiente y lo alistamos al final.
		
		Lista_Caracteres.push_back (Pila_Operadores.top ());
		
		// Lo quitamos de la pila.
		
		Pila_Operadores.pop ();
		
	}
	
	// Finalmente solo queda formar la cadena resultante en postfija , para ello vamos a iterar por cada elemento en la lista.
	
	for (size_t Indice = 0u ; Indice < Lista_Caracteres.size () ; ++ Indice) {
		
		// Obtenemos el elemento siguiente y lo anexamos a la cadena de postfija.
		
		Cadena_Postfija.append (Lista_Caracteres [Indice]);
		
		// Si el siguiente no es el ultimo valor entonces anexamos un espacio de separador.
		
		if ((Indice + 1u) < Lista_Caracteres.size ()) {
			
			// Ponemos el espacio.
			
			Cadena_Postfija.append (1 , ' ');
			
		}
		
	}
	
	//  Devolvemos el resultado
	
	return Cadena_Postfija;
	
}

// -----------------------------------------------------------------------------

// Procesador de una cadena de entrada a postfija. Esta función basicamente tiene la tarea de interpretar un texto en la forma :
//		2 + 4 * 5 , etc , para poder generar con esto la respectiva notación postfja de la forna : 2 4 5 * +

// Para lograrlo ocuparemos dos pilas , una de numeros y otra de simbolos u operadores , ambas seran contenedores de strings.

typedef std::stack <std::string> TPila;

// Tenemos la función que nos permite realizar esta conversión a postfija para una serie de operaciones determinada.

static std::string Parse_Postfija (const std::string & Cadena_Infija) {
	
	// Esta función se encargará de traducir la cadena infija de entrada a notación postfija y devolver el resultado siguiente.
	
	std::string Cadena_Postfija;
	
	// Lo primero que tenemos que hacer es ir leyendo la cadena de entrada , e ir tomando los caracteres hasta encontrarnos con un operador.
	// Los elementos seran asignados a la siguiente cadena.
	
	std::string Cadena_Numero;
	
	// Para ir colocando los elementos en el orden postfijo necesitamos como ya deciamos dos pilas , una para los numeros y otra para los operadores.
	
	TPila Pila_Operadores;
	
	// Deque de numeros.
	
	std::deque <std::string> Pila_Numeros;
	
	// El contador de caracteres procesados empieza en 0.
	
	size_t Posicion = 0u;
	
	// Comenzamos la traducción caracter por caracter.
	
	for (Posicion ; Posicion < Cadena_Infija.size () ; ++ Posicion) {
		
		// Cadena actual.
		
		const std::string Cadena_Actual (1 , Cadena_Infija [Posicion]);
		
		printf (" >> Cadena Actual : %s - " , Cadena_Actual.c_str ());
		
		// Si no es un operador entonces es un numero (digito) o '.'.
		
		if (Is_Operator (Cadena_Actual)) {
			
			printf (" Operador \n");
			
			// Si tenemos una cadena de numero no vacia entonces la apilamos.
			
			if (!Cadena_Numero.empty ()) {
				
				// Colocaremos el numero en la deque de numeros.
				
				Pila_Numeros.push_back (std::move (Cadena_Numero));
				
				// Asignaremos la cadena numero vacia.
				
				Cadena_Numero = std::string ();
				
			}
			
			// Si la pila de operadores no está vacia entonces.
			
			if (!Pila_Operadores.empty ()) {
				
				// Operador de la cima.
				
				const std::string Operador_Cima = Pila_Operadores.top (); 
				
				// Comprobamos si el operador actual es de mayor prioridad que el que tenemos en la cima de la pila , si no es asi entonces continuamos.
				
				unsigned char Prioridad_Cima = Mapa_Prioridades [Operador_Cima];
				unsigned char Prioridad_Actual = Mapa_Prioridades [std::string (1 , Cadena_Infija [Posicion])];
				
				// Comparamos.
				
				if (Prioridad_Cima > Prioridad_Actual) {
					
					printf (" >> Prioridad << \n");
					
					// Tenemos que procesar esto de la siguiente forma :
					// Tenemos que sacar los ultimos dos elementos de la pila de numeros conforme el operador actual en la cima.
					
					std::string Operando_B (Pila_Numeros.back ());
					
					Pila_Numeros.pop_back ();
					
					std::string Operando_A (Pila_Numeros.back ());
					
					Pila_Numeros.pop_back ();
					
					// Sacamos el operador de la pila.
					
					Pila_Operadores.pop ();
					
					// Concatenamos los operandos y el operador de esta forma : Operando_A Operando_B Operador. Y lo apilamos como un numero.
					
					Pila_Numeros.push_back (std::move (std::string (Operando_A + " " + Operando_B + " " + Operador_Cima)));
					
				}
				
			}
			
			// Apilamos el operador en la pila de operadores.
			
			Pila_Operadores.push (Cadena_Actual);
			
		}
		else {
			
			printf (" Numero \n");
			
			// Anexamos el caracter a la cadena.
			
			Cadena_Numero.append (Cadena_Actual);
			
		}
		
	}
	
	// Evaluamos si lo que sobro que tenemos es un numero.
	
	if (Is_Number (Cadena_Numero)) {
		
		// Colocaremos el numero en la pila de numeros.
		
		Pila_Numeros.push_back (std::move (Cadena_Numero));
		
	}
	
	// Ahora solo resta organizar la expresión en notación postfija usando las pilas , para ello vamos primero a poner los elementos de la pila de
	// numeros en el orden inverso al que se van a ir obteniendo , primero el primero en ser apilado.
	
	std::deque <std::string> Lista_Caracteres;
	
	// Colocaremos todos los que tenemos en la pila.
	
	while (!Pila_Numeros.empty ()) {
		
		// Sacamos el ultimo de la pila y lo ponemos al principio de la lista.
		
		Lista_Caracteres.push_front (Pila_Numeros.back ());
		
		// Lo sacamos de la pila.
		
		Pila_Numeros.pop_back ();
		
	}
	
	// Ahora que ya tenemos los numeros , anexaremos los operadores al final de la lista en el orden en el que van saliendo de la pila.
	
	while (!Pila_Operadores.empty ()) {
		
		// Sacamos el operador siguiente y lo alistamos al final.
		
		Lista_Caracteres.push_back (Pila_Operadores.top ());
		
		// Lo quitamos de la pila.
		
		Pila_Operadores.pop ();
		
	}
	
	// Finalmente solo queda formar la cadena resultante en postfija , para ello vamos a iterar por cada elemento en la lista.
	
	for (size_t Indice = 0u ; Indice < Lista_Caracteres.size () ; ++ Indice) {
		
		// Obtenemos el elemento siguiente y lo anexamos a la cadena de postfija.
		
		Cadena_Postfija.append (Lista_Caracteres [Indice]);
		
		// Si el siguiente no es el ultimo valor entonces anexamos un espacio de separador.
		
		if ((Indice + 1u) < Lista_Caracteres.size ()) {
			
			// Ponemos el espacio.
			
			Cadena_Postfija.append (1 , ' ');
			
		}
		
	}
	
	// Finalmente devolvemos la cadena.
	
	return Cadena_Postfija;
	
}

// -----------------------------------------------------------------------------

// ----------------------  Notación Postfija  ----------------------------------

// El algoritmo de notación postfija consiste en transformar la expresión de tipo : 2 + 3 * 4 a una más simple de procesar
// y evaluar de la forma : 2 3 4 * + , siendo primero los numeros y luego los operadores en orden de prioridad.

// Función para leer la siguiente cadena de entrada.

static std::string Read_Token (const std::string & Cadena , size_t & Posicion) {
	
	// Leeremos una cadena numerica y operador (funciones) para poder conformar el progreso del parseador.
	
	std::string Token_Leido;
	
	// Tomaremos el simbolo actual.
	
	char Simbolo = Cadena [Posicion ++];
	
	// Validaremos si es un digito entonces pasaremos a continuar.
	
	if (isdigit (static_cast <int> (Simbolo))) {
		
		// Anexaremos el simbolo.
		
		Token_Leido.append (1 , Simbolo);
		
		// Entonces leeremos todo el numero hasta que encontremos un operador o el final de la cadena.
		
		while (Posicion < Cadena.size ()) {
			
			// Simbolo actual
			
			Simbolo = Cadena [Posicion];
			
			// Anexamos el siguiente simbolo si sigue siendo un digito o un ..
			
			if (isdigit (static_cast <int> (Simbolo)) || (Simbolo == '.')) {
				
				// Anexamos el siguiente digito.
				
				Token_Leido.append (1 , Simbolo);
				
				// Incrementamos la posicion.
				
				++ Posicion;
				
			}
			else {
				
				// Tompemos el ciclo.
				
				break;
				
			}
			
		}
		
	}
	else {
		
		// Buscaremos si está en la lista de Operadores el simbolo leido.
		
		if (Mapa_Prioridades.count (std::string (1 , Simbolo)) > 0) {
			
			// Anexamos el operador a la cadena.
			
			Token_Leido.append (1 , Simbolo);
			
		}
		else {
			
			// Entonces puede ser una función , si es asi la buscaremos en el mapa de funciones , pero antes hay que leer todo el nombre de la función.
			
			Token_Leido.append (1 , Simbolo);
			
			// Entonces leeremos todo el numero hasta que encontremos un operador o el final de la cadena.
			
			while (Posicion < Cadena.size ()) {
				
				// Simbolo actual
				
				Simbolo = Cadena [Posicion];
				
				// Anexamos el siguiente simbolo si es diferente a un digito y apertura "(" de función.
				
				if (!isdigit (static_cast <int> (Simbolo)) && (Simbolo != '(')) {
					
					// Anexamos el siguiente digito.
					
					Token_Leido.append (1 , Simbolo);
					
					// Incrementamos la posicion.
					
					++ Posicion;
					
				}
				else {
					
					// Tompemos el ciclo.
					
					break;
					
				}
				
			}
			
		}
		
	}
	
	// Restamos la posicion en 1.
	
	-- Posicion;
	
	// Devolvemos la cadena.
	
	return Token_Leido;
	
}

// Utilizaremos una función recursiva que se encargue de procesar la expresión postfija a partir de una cadena en infija dada y devuelva
// el resultado de dicha expresión , está será el elemento fundamental para el procesamiento de la cadena.

static std::string Postfija (const std::string & Cadena_Infija) {
	
	// Esta función basicamente se encargara de formar toda la expresión en notación postfija.
	
	std::string Cadena_Postfija;
	
	// Lo primero que tenemos que hacer es ir leyendo la cadena de entrada , e ir tomando los caracteres hasta encontrarnos con un operador.
	// Los elementos seran asignados a la siguiente cadena.
	
	std::string Cadena_Numero;
	
	// Para ir colocando los elementos en el orden postfijo necesitamos como ya deciamos dos pilas , una para los numeros y otra para los operadores.
	
	TPila Pila_Operadores;
	
	// Deque de numeros.
	
	std::deque <std::string> Pila_Numeros;
	
	// El contador de caracteres procesados empieza en 0.
	
	size_t Posicion = 0u;
	
	// Primero comenzamos por procesar todas las sub-expresiones que esten dentro de parentesis "( ... )" en un ciclo.
	
	for (Posicion ; Posicion < Cadena_Infija.size () ; ++ Posicion) {
		
		// Cadena actual.
		
		const std::string Cadena_Actual (std::move (Read_Token (Cadena_Infija , Posicion)));
		
		// Si la cadena está vacia terminamos.
		
		if (Cadena_Actual.empty ()) {
			
			// Terminamos el bucle.
			
			break;
			
		}
		
		// Si no es un operador entonces es un numero (digito) o '.'.
		
		if (Is_Operator (Cadena_Actual)) {
			
			printf (" Operador \n");
			
			// Si tenemos una cadena de numero no vacia entonces la apilamos.
			/*
			if (!Cadena_Numero.empty ()) {
				
				
				
				// Asignaremos la cadena numero vacia.
				
				Cadena_Numero = std::string ();
				
			}
			*/
			// Si la pila de operadores no está vacia entonces.
			
			if (!Pila_Operadores.empty ()) {
				
				// Operador de la cima.
				
				const std::string Operador_Cima = Pila_Operadores.top (); 
				
				// Comprobamos si el operador actual es de mayor prioridad que el que tenemos en la cima de la pila , si no es asi entonces continuamos.
				
				unsigned char Prioridad_Cima = Mapa_Prioridades [Operador_Cima];
				unsigned char Prioridad_Actual = Mapa_Prioridades [std::string (1 , Cadena_Infija [Posicion])];
				
				// Comparamos.
				
				if (Prioridad_Cima > Prioridad_Actual) {
					
					// Apilaremos la sustitución hasta el momento.
					
					Pila_Numeros.push_back (std::move (Sustituir (Pila_Numeros , Pila_Operadores)));
					
					printf (" >> Sustitucion : %s \n" , Pila_Numeros.back ().c_str ());
					
				}
				
			}
			
			// Apilamos el operador en la pila de operadores.
			
			Pila_Operadores.push (Cadena_Actual);
			
		}
		else if (Is_Function (Cadena_Actual)) {
			
			// Procesaremos la función como si fuera un operador (.
			
			printf (" Funcion \n");
			
			// Buscaremos la primer coincidencia de "(" en esta cadena.
			
			size_t Posicion_Inicio = Cadena_Infija.find_first_of ("(" , Posicion);
			
			// Si el valor es diferente a npos continuamos.
			
			if (Posicion_Inicio != std::string::npos) {
				
				// Ahora buscamos la posición de terminación a partir de esta.
				
				size_t Posicion_Termino = Cadena_Infija.find_first_of (")" , Posicion_Inicio);
				
				// Si la encontramos entonces.
				
				if (Posicion_Termino != std::string::npos) {
					
					// Procesaremos recursivamente este tramo de la cadena para buscar nuevos sub-operaciones dentro
					
					std::string Parcial_Postfija (std::move (Postfija (std::string ((Cadena_Infija.cbegin () + Posicion_Inicio + 1u) , (Cadena_Infija.cbegin () + Posicion_Termino)))));
					
					// Crearemos la cadena de la forma Argumento Funcion.
					
					std::string Funcion_Postfija (Parcial_Postfija + " " + Cadena_Actual);
					
					// Anexamos esta cadena a la deque de numeros actual.
					
					Pila_Numeros.push_back (std::move (Funcion_Postfija));
					
				}
				
				// Asignaremos la posición actual en la posición de terminación.
				
				Posicion = Posicion_Termino;
				
			}
			
		}
		else if (Cadena_Actual == "(") {
			
			// Buscaremos la primer coincidencia de "(" en esta cadena.
			
			size_t Posicion_Inicio = Posicion;
			
			// Si el valor es diferente a npos continuamos.
			
			if (Posicion_Inicio != std::string::npos) {
				
				// Ahora buscamos la posición de terminación a partir de esta.
				
				size_t Posicion_Termino = Cadena_Infija.find_first_of (")" , Posicion_Inicio);
				
				// Si la encontramos entonces.
				
				if (Posicion_Termino != std::string::npos) {
					
					// Procesaremos recursivamente este tramo de la cadena para buscar nuevos sub-operaciones dentro
					
					std::string Parcial_Postfija (std::move (Postfija (std::string ((Cadena_Infija.cbegin () + Posicion + 1u) , (Cadena_Infija.cbegin () + Posicion_Termino)))));
					
					// Anexamos esta cadena a la deque de numeros actual.
					
					Pila_Numeros.push_back (std::move (Parcial_Postfija));
					
				}
				
				// Asignaremos la posición actual en la posición de terminación.
				
				Posicion = Posicion_Termino;
				
			}
			
		}
		else {
			
			printf (" Numero \n");
			
			// Colocaremos el numero en la deque de numeros.
			
			Pila_Numeros.push_back (std::move (Cadena_Actual));
			
		}
		
	}
	
	// Evaluamos si lo que sobro que tenemos es un numero.
	
	if (Is_Number (Cadena_Numero)) {
		
		// Colocaremos el numero en la pila de numeros.
		
		Pila_Numeros.push_back (std::move (Cadena_Numero));
		
	}
	
	/*
	
	// Ahora lo siguiente es organizar la cadena por pasos , tomaremos un operador de la pila y los dos operandos de la pila de numeros.
	
	while (!Pila_Operadores.empty ()) {
		
		// Obtenemos el operador actual.
		
		const std::string Operador_Cima (Pila_Operadores.top ());
		
		// Lo sacamos de la pila.
		
		Pila_Operadores.pop ();
		
		// Tenemos los operandos en esta lista.
		
		std::deque <std::string> Operandos_Cima;
		
	}
	
	// Ahora solo resta organizar la expresión en notación postfija usando las pilas , para ello vamos primero a poner los elementos de la pila de
	// numeros en el orden inverso al que se van a ir obteniendo , primero el primero en ser apilado.
	
	std::deque <std::string> Lista_Caracteres;
	
	// Colocaremos todos los que tenemos en la pila.
	
	while (!Pila_Numeros.empty ()) {
		
		// Sacamos el ultimo de la pila y lo ponemos al principio de la lista.
		
		Lista_Caracteres.push_front (Pila_Numeros.back ());
		
		// Lo sacamos de la pila.
		
		Pila_Numeros.pop_back ();
		
	}
	
	// Ahora que ya tenemos los numeros , anexaremos los operadores al final de la lista en el orden en el que van saliendo de la pila.
	
	while (!Pila_Operadores.empty ()) {
		
		// Sacamos el operador siguiente y lo alistamos al final.
		
		Lista_Caracteres.push_back (Pila_Operadores.top ());
		
		// Lo quitamos de la pila.
		
		Pila_Operadores.pop ();
		
	}
	
	// Finalmente solo queda formar la cadena resultante en postfija , para ello vamos a iterar por cada elemento en la lista.
	
	for (size_t Indice = 0u ; Indice < Lista_Caracteres.size () ; ++ Indice) {
		
		// Obtenemos el elemento siguiente y lo anexamos a la cadena de postfija.
		
		Cadena_Postfija.append (Lista_Caracteres [Indice]);
		
		// Si el siguiente no es el ultimo valor entonces anexamos un espacio de separador.
		
		if ((Indice + 1u) < Lista_Caracteres.size ()) {
			
			// Ponemos el espacio.
			
			Cadena_Postfija.append (1 , ' ');
			
		}
		
	}
	
	*/
	
	// Asignaremos la sustitución.
	
	Cadena_Postfija = std::move (Sustituir (Pila_Numeros , Pila_Operadores));
	
	// Finalmente devolvemos la cadena.
	
	return Cadena_Postfija;
	
	/*
	
	// Una vez Comenzamos la traducción caracter por caracter.
	
	for (Posicion ; Posicion < Cadena_Infija.size () ; ++ Posicion) {
		
		
		
	}
	
	// Entonces tenemos que obtener la sub-cadena infija que esta dentro del parentesis y procesarla por aparte con
	// esta misma función recursiva.
	
	printf (" Parentesis \n");
	
	// Buscamos el simbolo ')' para obtener la subcadena.
	
	size_t Posicion_Terminador = Cadena_Infija.find_first_of (")" , Posicion);
	
	// Si lo encontramos entonces hacemos el procesamiento.
	
	if (Posicion_Terminador != std::string::npos) {
		
		// Procesamos la subcadena dentro del parentesis y la concatenamos directo sobre el resultado.
		
		// Cadena_Postfija.append (Parse_Postfija (std::string ((Cadena_Infija.begin () + Posicion + 1u) , (Cadena_Infija.begin () + Posicion_Terminador))));
		
		Pila_Numeros.push_front (std::move (Parse_Postfija (std::string ((Cadena_Infija.begin () + Posicion + 1u) , (Cadena_Infija.begin () + Posicion_Terminador)))));
		
		// Asignaremos la posición actual.
		
		Posicion = Posicion_Terminador;
		
		printf (" Parentesis fin \n");
		
	}
	else {
		
		// Devolvemos el resultado final.
		
		return Cadena_Postfija;
		
	}
	*/
	
}

// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------

int main () {
	
	printf (" >> Algoritmo para notación infija - postfija << \n");
	
	// Leeremos una cadena en notación infija y la almacenamos en el siguiente buffer.
	
	char Buffer_Entrada [400];
	
	printf (" >> Inserte una expresión en notación infija : ");
	fflush (stdin) , gets (Buffer_Entrada);
	
	// Crearemos una cadena limpia sin espacios , usamos la función siguiente.
	
	const std::string Cadena_Entrada (std::move (Cadena_Limpiar (std::string (Buffer_Entrada))));
	
	// -----------------------------------------------------------------------------
	
	// La cadena es :
	
	printf (" >> ----------------------------------------------- \n\n");
	printf (" >> Infija : [%s] \n" , Cadena_Entrada.c_str ());
	
	// -----------------------------------------------------------------------------
	
	// La cadena en postfija es :
	
	std::string Cadena_Salida (std::move (Postfija (Cadena_Entrada)));
	
	printf (" >> ----------------------------------------------- \n\n");
	printf (" >> Postfija : [%s] \n" , Cadena_Salida.c_str ());
	
	// -----------------------------------------------------------------------------
	
	
	
	// -----------------------------------------------------------------------------
	
	system ("pause");
	return EXIT_SUCCESS;
	
}

// -----------------------------------------------------------------------------
