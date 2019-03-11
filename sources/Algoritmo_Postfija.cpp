
// Definici�n del algoritmo de conversi�n a notaci�n P�stfija.

#include <Algoritmo_Postfija.h>

// -----------------------------------------------------------------------------

// ----------------------  Operadores Definici�n  ------------------------------

// Comenzaremos por declarar el mapa de operadores que tenemos disponibles para nuestra aplicaci�n los cuales son :

std::unordered_map <std::string , size_t> Conjunto_Operadores = {
	
	// Operadores Aritmeticos.
	
	std::pair <std::string , size_t> ("+" , 0u) ,
	std::pair <std::string , size_t> ("-" , 1u) ,
	std::pair <std::string , size_t> ("*" , 2u) ,
	std::pair <std::string , size_t> ("/" , 3u) ,
	std::pair <std::string , size_t> ("^" , 4u) ,
	
	// Operadores de Parentesis.
	
	std::pair <std::string , size_t> ("(" , 5u) ,
	std::pair <std::string , size_t> (")" , 6u)
	
};

// -----------------------------------------------------------------------------

// ----------------------  Variables Definici�n  -------------------------------

// Definiremos la lista de las posibles variables o incognitas en las expresiones.

std::unordered_set <std::string> Conjunto_Variables = {
	
	// Variables tradicionales.
	
	std::string ("X") , std::string ("x") ,
	std::string ("Y") , std::string ("y") ,
	std::string ("Z") , std::string ("z")
	
};

// -----------------------------------------------------------------------------

// ----------------------  Funciones Definici�n  -------------------------------

// Ahora vamos a implementar la funci�n sen y lo mismo para el resto.

double Funcion_Sen (size_t Argumentos , double * Valores) {
	
	// Devolvemos el resultado de aplicar la funci�n matematica sobre nuestro primer argumento.
	
	return sin (Valores [0]);
	
}

// Implementaremos la funci�n cos.

double Funcion_Cos (size_t Argumentos , double * Valores) {
	
	// Devolvemos el resultado de aplicar la funci�n matematica sobre nuestro primer argumento.
	
	return cos (Valores [0]);
	
}

// Implementaremos la funci�n tan.

double Funcion_Tan (size_t Argumentos , double * Valores) {
	
	// Devolvemos el resultado de aplicar la funci�n matematica sobre nuestro primer argumento.
	
	return tan (Valores [0]);
	
}

// Implementaremos la funci�n Asen.

double Funcion_Asen (size_t Argumentos , double * Valores) {
	
	// Devolvemos el resultado de aplicar la funci�n matematica sobre nuestro primer argumento.
	
	return asin (Valores [0]);
	
}

// Implementaremos la funci�n Acos.

double Funcion_Acos (size_t Argumentos , double * Valores) {
	
	// Devolvemos el resultado de aplicar la funci�n matematica sobre nuestro primer argumento.
	
	return cos (Valores [0]);
	
}

// Implementaremos la funci�n Atan.

double Funcion_Atan (size_t Argumentos , double * Valores) {
	
	// Devolvemos el resultado de aplicar la funci�n matematica sobre nuestro primer argumento.
	
	return cos (Valores [0]);
	
}

// Implementaremos la funci�n Sqrt.

double Funcion_Sqrt (size_t Argumentos , double * Valores) {
	
	// Devolvemos el resultado de aplicar la funci�n matematica sobre nuestro primer argumento.
	
	return sqrt (Valores [0]);
	
}

// Asignaremos la lista de todas las funciones disponibles para el algoritmo.

std::unordered_map <std::string , Funcion_Evaluacion> Conjunto_Funciones = {
	
	// Funciones trigonometricas.
	
	std::pair <std::string , Funcion_Evaluacion> (std::string ("sen") , Funcion_Evaluacion (1u , &Funcion_Sen)) ,
	std::pair <std::string , Funcion_Evaluacion> (std::string ("cos") , Funcion_Evaluacion (1u , &Funcion_Cos)) ,
	std::pair <std::string , Funcion_Evaluacion> (std::string ("tan") , Funcion_Evaluacion (1u , &Funcion_Tan)) ,
	std::pair <std::string , Funcion_Evaluacion> (std::string ("asen") , Funcion_Evaluacion (1u , &Funcion_Asen)) ,
	std::pair <std::string , Funcion_Evaluacion> (std::string ("acos") , Funcion_Evaluacion (1u , &Funcion_Acos)) ,
	std::pair <std::string , Funcion_Evaluacion> (std::string ("atan") , Funcion_Evaluacion (1u , &Funcion_Atan)) ,
	
	// Funciones de raiz.
	
	std::pair <std::string , Funcion_Evaluacion> (std::string ("sqrt") , Funcion_Evaluacion (1u , &Funcion_Sqrt))
	
};

// -----------------------------------------------------------------------------

// --------------------  Definici�n de Expresiones  ----------------------------

// Asignaremos la expresi�n regular ECMAScript para la estructura de una expresi�n matematica correcta.

const std::regex Expresion_Matematica = std::regex (std::string ("([^\\(\\)]|((\\()(.)*(\\))))*"));

// Definiremos la expresi�n regular ECMAScript para la estructura de un numero correcto.

const std::regex Expresion_Numero = std::regex (std::string ("([0-9])+((.)([0-9])+)?"));

// Definiremos la expresi�n regular ECMAScript para la estructura de un operador correcto.

const std::regex Expresion_Operador = std::regex (std::string ("(\\+|\\-|\\*|\\/|\\^|\\(|\\))"));

// -----------------------------------------------------------------------------

// ---------------------------  Algoritmo  -------------------------------------

// -----------------------------------------------------------------------------

// -------------------------  Constructores  -----------------------------------

// Comenzaremos primero definiendo el constructor de nuestra clase Algoritmo con el argumento de cadena.

Algoritmo_Postfija::Algoritmo_Postfija (const std::string & Entrada_Infija) {
	
	// Asignaremos la cadena actual.
	
	Cadena_Entrada = Entrada_Infija;
	
}

// Ahora el constructor de nuestra clase Algoritmo con el argumento en move constructor.

Algoritmo_Postfija::Algoritmo_Postfija (std::string && Entrada_Infija) {
	
	// Asignaremos la cadena actual (move constructor).
	
	Cadena_Entrada = std::move (Entrada_Infija);
	
}

// -----------------------------------------------------------------------------

// --------------------------  Metodos Setters  --------------------------------

// Metodo para cambiar la cadena de entrada actualmente en el algoritmo.

void Algoritmo_Postfija::Set_Entrada (const std::string & Nueva_Entrada) {
	
	// Asignaremos la cadena actual.
	
	Cadena_Entrada = Nueva_Entrada;
	
}

// Metodo para cambiar la cadena de entrada actualmente en el algoritmo (move-constructor).

void Algoritmo_Postfija::Set_Entrada (std::string && Nueva_Entrada) {
	
	// Asignaremos la cadena actual (move constructor).
	
	Cadena_Entrada = std::move (Nueva_Entrada);
	
}

// -----------------------------------------------------------------------------

// ------------------------  Metodos de Cadenas  -------------------------------

// Implementaremos primero la funci�n que elimina todos los espacios de la cadena de entrada.

std::string Algoritmo_Postfija::Cadena_Limpiar (const std::string & Cadena) const {
	
	// Tenemos la siguiente cadena resultado.
	
	std::string Resultado;
	
	// Validaremos si tenemos una cadena no vacia.
	
	if (!Cadena.empty ()) {
		
		// Iteramos por cada simbolo en la cadena e iremos anexandolos a nuestra cadena resultado a excepci�n de los espacios.
		
		for (char Simbolo : Cadena) {
			
			// Si es diferente a un espacio , salto de linea o retorno de carro lo anexamos.
			
			if ((Simbolo != '\0') && (Simbolo != ' ') && (Simbolo != '\n') && (Simbolo != '\r') && (Simbolo != '\t')) {
				
				// Anexamos el simbolo a la cadena resultante.
				
				Resultado.append (1u , Simbolo);
				
			}
			
		}
		
	}
	
	// Devolveremos la cadena restante sin espacios o caracteres de salto de linea.
	
	return Resultado;
	
}

// Implementaremos el algoritmo de postfija recursivo en este metodo , el cual recive a la entrada la cadena en notaci�n infija y devuelve
// su respectiva representaci�n en notaci�n postfija.

std::string Algoritmo_Postfija::Cadena_Parsear (const std::string & Cadena) const {
	
	// Comenzaremos por declarar la cadena de salida en notaci�n postfija.
	
	std::string Cadena_Resultado;
	
	printf (" >> Cad parse : %s\n" , Cadena.c_str ());
	
	// -------------------------------------------------------------------------
	
	// ---------------------------  Interpretando  -----------------------------
	
	// Tenemos que empezar a recorrer la cadena desde la posici�n 0 hasta el final de la misma para ir leyendo sus partes que la componen.
	
	size_t Posicion = 0u;
	
	// Ahora tenemos que interpretar la cadena completa parte por parte , para esto nos ayudaremos de las funciones auxiliares. Asi que iteramos
	// por toda la cadena de entrada desde la posici�n 0 hasta el final de la misma.
	
	while (Posicion < Cadena.size ()) {
		
		// Lo primero que haremos sera leer e interpretar la cadena desde la posici�n actual. Leeremos el siguiente elemento y luego
		// lo asignaremos a la pila que corresponda.
		
		const std::string Cadena_Leida (std::move (Read_Next (Cadena , Posicion)));
		
		printf (" >> Cadena leida : %s " , Cadena_Leida.c_str ());
		
		// Ahora lo que sigue es darle una interpretaci�n a lo que leimos si no est� vacio.
		
		if (!Cadena_Leida.empty ()) {
			
			// ---------------------  Asignaci�n  ------------------------------
			
			// Ahora toca validar si la cadena actual es un n�mero � variable, si lo �s entonces pasaremos a realizar la apilaci�n del valor.
			
			if (Is_Number (Cadena_Leida)) {
				
				printf (" Numero \n");
				
				// -----------------------  N�mero  ----------------------------
				
				// Realizamos la apilaci�n del valor de manera normal.
				
				Apilar_Numero (Cadena_Leida);
				
			}
			else if (Is_Function (Cadena_Leida) || (Cadena_Leida == "(")) {
				
				printf (" Funci�n � Expresion \n");
				
				// -----------------  Funci�n � Expresi�n  ---------------------
				
				// En el caso de ser una funci�n o una expresi�n iniciado por un Parentesis , requerimos realizar el mismo procedimiento
				// recursivamente , es decir , mandaremos a llamar a esta funci�n para lo que est� dentro del parentesis de la funci�n o
				// del parentesis.
				
				// Lo siguiente que tenemos que hacer es obtener el valor de posici�n de Origen (donde empieza la "(" + 1u).
				
				const size_t Posicion_Origen = (Cadena.find_first_of ('(' , Posicion) + 1u);
				
				// Tendremos la posici�n de termino determinada por nuestra funci�n de busqueda.
				
				size_t Posicion_Termino = Expresion_Terminador (Cadena , Posicion_Origen);
				
				// Si ambas son diferentes a npos , entonces continuaremos.
				
				if ((Posicion_Origen != std::string::npos) && (Posicion_Termino != std::string::npos)) {
					
					// Antes de continuar con el parseo recursivo necesitamos respaldar nuestra pila de numeros.
					
					std::deque <std::string> Respaldo_Numeros = std::move (Pila_Numeros);
					
					// Asi como tambien la pila de operadores.
					
					std::deque <std::string> Respaldo_Operadores = std::move (Pila_Operadores);
					
					// ------------------  Parseo Recursivo  -------------------
					
					// Crearemos la sub-cadena de la expresi�n que vamos a interpretar recursivamente , para esto tenemos a.
					
					const std::string Subcadena_Infija (std::move (Cadena.substr (Posicion_Origen , (Posicion_Termino - Posicion_Origen))));
					
					// Ahora vamos a realizar el parseo de esta cadena llamando a esta misma funci�n recursivamente.
					
					std::string Subcadena_Postfija (Cadena_Parsear (Subcadena_Infija));
					
					// Si la cadena leida es de tipo funci�n , entonces , anexamos dicha funci�n a la expresi�n n�merica.
					
					if (Is_Function (Cadena_Leida)) {
						
						// Anexamos un espacio y la funci�n.
						
						Subcadena_Postfija.append (1u , ' ').append (Cadena_Leida);
						
					}
					
					// ---------------------------------------------------------
					
					// Restauramos el estado de la pila de numeros.
					
					Pila_Numeros = std::move (Respaldo_Numeros);
					
					// Y el de la pila de operadores.
					
					Pila_Operadores = std::move (Respaldo_Operadores);
					
					// Apilaremos este como si fuera un n�mero en la pila de numeros.
					
					Apilar_Numero (std::move (Subcadena_Postfija));
					
					// Finalmente asignaremos la posici�n actual en el valor de nuestra posici�n termino + 1.
					
					Posicion = (Posicion_Termino + 1u);
					
					// Continuamos el bucle.
					
					continue;
					
				}
				
			}
			else if (Is_Operator (Cadena_Leida)) {
				
				printf (" Operador \n");
				
				// ----------------------  Operador  ---------------------------
				
				// Asi que es un operador , de esta forma ahora entonces realizaremos la apilaci�n del mismo en el orden que se establezca usando nuestro metodo.
				
				Apilar_Operador (Cadena_Leida);
				
			}
			else {
				
				printf (" Ninguno \n");
				
				// No coincide ninguna de las expresiones , entonces hay un error.
				
				return std::string ();
				
			}
			
			// Finalmente sumaremos la cantidad de letras leidas en la cadena a la posici�n actual.
			
			Posicion += Cadena_Leida.size ();
			
		}
		else {
			
			// Terminamos la lectura.
			
			break;
			
		}
		
	}
	
	// -------------------------------------------------------------------------
	
	// Asignaremos la organizaci�n de nuestra expresi�n a partir de las pilas que tenemos y est� sera nuestra expresi�n final.
	
	Cadena_Resultado = std::move (Cadena_Organizar ());
	
	printf ("\n >>> Sub Resultado : %s \n\n" , Cadena_Resultado.c_str ());
	
	// Devolvemos finalmente nuestro resultado.
	
	return Cadena_Resultado;
	
}

// A continuaci�n definiremos la funci�n que tiene como finalidad la de interpretar la expresi�n en postfija que tenemos con base
// a los valores actuales en la pila de n�meros y en la de operadores.

std::string Algoritmo_Postfija::Cadena_Organizar () const {
	
	// Tenemos la cadena resultante en esta localidad.
	
	std::string Cadena_Resultado;
	
	// -------------------------------------------------------------------------
	
	// ---------------------  Acomodar Expresi�n  ------------------------------
	
	// Lo que vamos a hacer en primer lugar es crear una nueva Pila con todos los elementos de ambas pilas que tenemos , primero
	// colocaremos todos los elementos de la pila de n�meros en ese mismo orden.
	
	std::deque <std::string> Pila_Expresion (std::move (Pila_Numeros));
	
	// Ahora vamos a insertar al final de la Pila los operadores comenzando por el ultimo (cima de la pila) hasta el primero.
	// Por lo que insertaremos el rango comenzando por el inicio invertido de la pila de operadores.
	
	Pila_Expresion.insert (Pila_Expresion.end () , Pila_Operadores.rbegin () , Pila_Operadores.rend ());
	
	// Finalmente vamos a iterar por cada uno de estos elementos e iremos separando cada expresi�n u operador con un espacio
	// que iremos anexando a la cadena resultante.
	
	for (std::deque <std::string>::iterator Expresion_Actual = Pila_Expresion.begin () ; Expresion_Actual != Pila_Expresion.end () ; ++ Expresion_Actual) {
		
		// Insertaremos la expresi�n actual en la cadena resultante.
		
		Cadena_Resultado.append (*Expresion_Actual);
		
		// Anexamos un espacio si no es el final de la pila.
		
		if ((Expresion_Actual + 1u) != Pila_Expresion.end ()) {
			
			// Ponemos un espacio para separar la expresi�n de la siguiente.
			
			Cadena_Resultado.append (1u , ' ');
			
		}
		
	}
	
	// Dejaremos limpias todas las pilas antes de terminar.
	
	Pila_Expresion.clear () , Pila_Numeros.clear () , Pila_Operadores.clear ();
	
	// -------------------------------------------------------------------------
	
	// Finalmente devolvemos la expresi�n en notaci�n postfija.
	
	return Cadena_Resultado;
	
}

// -----------------------------------------------------------------------------

// -------------------------  Metodos de Pilas  --------------------------------

// Tenemos primero la funci�n que realiza el apilamiento de una nueva expresi�n o valor en la pila de numeros.

void Algoritmo_Postfija::Apilar_Numero (const std::string & Cadena) const {
	
	// Simplemente tenemos que realizar el apilamiento al final de la misma con la cadena de parametro.
	
	Pila_Numeros.push_back (Cadena);
	
}

// Asi mismo para cuando la cadena de entrada es de tipo r-value.

void Algoritmo_Postfija::Apilar_Numero (std::string && Cadena) const {
	
	// Simplemente tenemos que realizar el apilamiento al final de la misma con la cadena de parametro en move constructor.
	
	Pila_Numeros.push_back (std::move (Cadena));
	
}

// Ahora tenemos la funci�n que realiza el apilamiento de un operador en la pila de operadores siguiendo la prioridad que
// se define en el mapa de operadores.

void Algoritmo_Postfija::Apilar_Operador (const std::string & Cadena) const {
	
	// ---------------------------  Prioridad  ---------------------------------
	
	// Lo primero que debemos de hacer es comprobar si el ultimo operador colocado tiene prioridad menor al que tenemos
	// actualmente , si no es asi entonces hay que acomodar la expresi�n.
	
	if (!Pila_Operadores.empty ()) {
		
		// Tomaremos el ultimo operador de la pila y obtendremos su prioridad desde el mapa.
		
		const size_t Prioridad_Pila = Conjunto_Operadores [Pila_Operadores.back ()];
		
		// Ahora tomaremos el valor de prioridad para el operador que tenemos que apilar.
		
		const size_t Prioridad_Actual = Conjunto_Operadores [Cadena];
		
		// Validamos , si el operador de la pila tiene mayor prioridad que el actual , entonces organizamos.
		
		if (Prioridad_Pila > Prioridad_Actual) {
			
			// Ahora vamos a organizar , para esto tenemos que interpretar lo que llevamos hasta el momento en la pila
			// de n�meros y de operadores como una sola expresi�n que apilaremos nuevamente en los n�meros.
			
			// Utilizamos nuestro interprete y organizador , colocamos el resultado en la pila de n�meros.
			
			Apilar_Numero (std::move (Cadena_Organizar ()));
			
		}
		
	}
	
	// -------------------------------------------------------------------------
	
	// Finalmente apilaremos el operador en nuestra pila de operadores hasta el final.
	
	Pila_Operadores.push_back (Cadena);
	
}

// -----------------------------------------------------------------------------

// ----------------------  Metodos de Validaci�n  ------------------------------

// Definiremos para empezar los metodos auxiliares de validaci�n en nuestra clase del algoritmo.

// Comenzaremos por la validaci�n de toda la expresi�n de entrada.

bool Algoritmo_Postfija::Is_Valid () const {
	
	// Devolvemos true si la expresi�n regular respectiva lanza un valor true tambien sobre la cadena actual.
	
	return ((!Cadena_Entrada.empty ()) ? std::regex_match (Cadena_Entrada , Expresion_Matematica) : false);
	
}

// Ahora pasaremos al metodo que valida que una cadena determinada sea un numero o las variables [X , Y , Z].

bool Algoritmo_Postfija::Is_Number (const std::string & Cadena) const {
	
	// Para esto de igual forma que con la expresi�n completa , usaremos una regular-expresi�n para validarlo.
	
	return ((!Cadena.empty ()) ? (std::regex_match (Cadena , Expresion_Numero) || (Conjunto_Variables.count (Cadena) > 0u)) : false);
	
}

// Ahora pasaremos al metodo para validar que una cadena sea un Operador valido dentro de nuestra lista de operadores.

bool Algoritmo_Postfija::Is_Operator (const std::string & Cadena) const {
	
	// Utilizaremos tanto la expresi�n regular como el mapa de operadores para determinar que sea un operador valido.
	
	return ((!Cadena.empty ()) && std::regex_match (Cadena , Expresion_Operador) && (Conjunto_Operadores.count (Cadena) > 0u));
	
}

// De igual forma para cuando se trata de una funci�n tenemos que validarlo con la lista de funciones permitidas.

bool Algoritmo_Postfija::Is_Function (const std::string & Cadena) const {
	
	// Utilizaremos tanto la expresi�n regular como el mapa de operadores para determinar que sea un operador valido.
	
	return ((!Cadena.empty ()) && (Conjunto_Funciones.count (Cadena) > 0u));
	
}

// -----------------------------------------------------------------------------

// --------------------  Definici�n de Posici�n  -------------------------------

// Definiremos la funci�n que determina la posici�n del ')' a partir de la posici�n de la apertura del mismo.

size_t Algoritmo_Postfija::Expresion_Terminador (const std::string & Cadena , size_t Posicion) const {
	
	// Tenemos la posici�n resultado en npos inicialmente.
	
	size_t Posicion_Termino = std::string::npos;
	
	// Ahora para encontrar el valor de posici�n final necesitamos considerar los niveles que tenemos de jerarquia dentro de la
	// misma expresi�n , tendremos un contador de niveles para saber que el nivel que ocupamos sea el correcto comenzando desde 0.
	
	char Contador_Nivel = 0;
	
	// Con base a esta posici�n origen buscaremos la posici�n final (donde est� la ")") iterando por cada letra y sumando
	// y validando los niveles.
	
	for (size_t Posicion_Actual = Posicion ; Posicion_Actual < Cadena.size () ; ++ Posicion_Actual) {
		
		// Tomaremos el simbolo actual.
		
		const char Simbolo_Actual = Cadena [Posicion_Actual];
		
		// Si el simbolo actual es igual a ")" y el nivel es 0 , entonces encontramos el termino de la sub-expresi�n.
		
		if (Simbolo_Actual == ')') {
			
			// Si el nivel es igual a 0 , entonces encontramos el operador.
			
			if (Contador_Nivel == 0) {
				
				// Asignamos la posici�n actual.
				
				Posicion_Termino = Posicion_Actual;
				
				// Terminamos el bucle.
				
				break;
				
			}
			
			// Restamos 1 a nuestro contador de nivel.
			
			-- Contador_Nivel;
			
		}
		else if (Simbolo_Actual == '(') {
			
			// Si es otro operador de expresi�n , sumaremos 1 al nivel.
			
			++ Contador_Nivel;
			
		}
		
	}
	
	// Finalmente devolvemos la posici�n termino.
	
	return Posicion_Termino;
	
}

// -----------------------------------------------------------------------------

// --------------------  Definici�n del Aloritmo  ------------------------------

// Ahora viene la parte de implementar todas las funciones que tenemos en nuestra clase del Algoritmo parte por parte para ir componiendo
// todo el flujo de trabajo en orden.

// 1.- Tenemos entonces la primer funci�n que es la principal contenedora de todos los pasos del algoritmo , llamar a esta funci�n
// devolvera el resultado de la cadena en notaci�n postfija.

std::string Algoritmo_Postfija::Generate_Postfija () const {
	
	// Crearemos la cadena resultante en la siguiente variable.
	
	std::string Cadena_Salida;
	
	// -------------------------------------------------------------------------
	
	// Lo primero que debemos de hacer es validar que la cadena sea valida , si no entonces devolvemos una cadena vacia.
	
	if (Is_Valid ()) {
		
		printf (" >> Valida \n");
		
		// Paso 1 : Limpiar la Cadena.
		// Lo primero es dejar la cadena de entrada actual sin espacios y sin caracteres especiales no imprimibles.
		
		const std::string Cadena_Infija (std::move (Cadena_Limpiar (Cadena_Entrada)));
		
		// Paso 2 : Limpiar pilas.
		// Limpiaremos ambas pilas de numeros y operadores.
		
		printf (" >> Entrada : %s \n" , Cadena_Infija.c_str ());
		
		Pila_Numeros.clear () , Pila_Operadores.clear ();
		
		// Paso 3 : Parsear Cadena.
		// Ahora lo siguiente es aplicar el algoritmo en si , para esto llamaremos a nuestra funci�n recursiva que va interpretando
		// parte por parte de la cadena ayudandose de las pilas. Devolviendo el resultado de la expresi�n actual en notaci�n postfija.
		
		Cadena_Salida = std::move (Cadena_Parsear (Cadena_Infija));
		
	}
	
	printf (" >> Salida \n");
	
	// -------------------------------------------------------------------------
	
	// Devolvemos la cadena de salida.
	
	return Cadena_Salida;
	
}

// 2.- Tenemos otra funci�n la cual realiza la lectura de un token o cadena para interpretar como numero , simbolo , operador , etc.

std::string Algoritmo_Postfija::Read_Next (const std::string & Cadena_Infija , size_t Posicion) const {
	
	// Tendremos la cadena resultante en esta localidad.
	
	std::string Cadena_Resultado;
	
	// --------------------------  Interpretando  ------------------------------
	
	// Tenemos tres posibles resultados :
	// 1 : Cadena Numerica.
	// 2 : Operador matematico o una variable.
	// 3 : Funci�n (palabra reservada).
	
	// Nuestro algoritmo leera los caracteres necesarios de la cadena entrada y a partir de Posicion , hasta completar la cadena
	// del tipo que se trate , para esto lo primero que debemos de realizar es tomar como base el primer caracter.
	
	const char Simbolo_Inicio = Cadena_Infija [Posicion];
	
	// Validaremos que tipo de cadena es. Si es un n�mero entonces deberia tratarse de un digito (0-9) , tenemos una funci�n que
	// nos permite determinar esto.
	
	if (isdigit (static_cast <int> (Simbolo_Inicio))) {
		
		// ----------------------  Caso 1 : N�mero  ----------------------------
		
		// Entonces se trata de un n�mero por lo que leeremos dicho valor y asignaremos nuestro resultado.
		
		Cadena_Resultado = std::move (Read_Number (Cadena_Infija , Posicion));
		
	}
	else {
		
		// Tenemos la representaci�n en cadena de dicho simbolo.
		
		std::string Simbolo_Cadena (1u , Simbolo_Inicio);
		
		// Validaremos ahora que cumpla con ser un operador o una variable
		
		if (Is_Operator (Simbolo_Cadena) || (Conjunto_Variables.count (Simbolo_Cadena) > 0)) {
			
			// -------------------  Caso 2 : Operador  -------------------------
			
			// Entonces se trata de un operador matematico o una variable , por lo que lo anexamos tal cual.
			
			Cadena_Resultado = std::move (Simbolo_Cadena);
			
		}
		else {
			
			// -------------------  Caso 3 : Funci�n  -------------------------
			
			// Entonces se trata de una funci�n , al igual que con el n�mero tenemos la funci�n que lo lee.
			
			Cadena_Resultado = std::move (Read_Function (Cadena_Infija , Posicion));
			
		}
		
	}
	
	// -------------------------------------------------------------------------
	
	// Finalmente devolvemos nuestra cadena resultante.
	
	return Cadena_Resultado;
	
}

// 3.- Si la cadena se trata de un N�mero entonces tenemos la siguiente funci�n que lee dicho n�mero.

std::string Algoritmo_Postfija::Read_Number (const std::string & Cadena_Infija , size_t Posicion) const {
	
	// Tenemos la cadena resultante.
	
	std::string Cadena_Resultado;
	
	// Realizamos la lectura de nuestro valor para ello vamos a tomar caracter por caracter de la cadena hasta llegar al final o hasta llegar a un
	// valor que no coincida con :
	//		[0-9] : Digito.
	//		'.' : Punto Decimal.
	
	for (std::string::const_iterator Posicion_Actual = (Cadena_Infija.cbegin () + Posicion) ; Posicion_Actual != Cadena_Infija.cend () ; ++ Posicion_Actual) {
		
		// Leeremos el siguiente caracter.
		
		const char Simbolo = *(Posicion_Actual);
		
		// Validamos el simbolo para saber que cumpla con ser un digito o punto decimal.
		
		if (!(isdigit (static_cast <int> (Simbolo))) && (Simbolo != '.')) {
			
			// Terminamos el bucle.
			
			break;
			
		}
		
		// Anexamos el caracter a la cadena resultado.
		
		Cadena_Resultado.append (1u , Simbolo);
		
	}
	
	// Devolvemos la cadena resultado.
	
	return Cadena_Resultado;
	
}

// 4.- Ahora si la cadena es una funci�n , leeremos toda la palabra de la funci�n hasta encontrarnos con un parentesis o un espacio vacio.

std::string Algoritmo_Postfija::Read_Function (const std::string & Cadena_Infija , size_t Posicion) const {
	
	// Tenemos la cadena resultante.
	
	std::string Cadena_Resultado;
	
	// Ahora vamos a leer toda la cadena de igual forma que con el n�mero e iremos validando que cumpla con :
	//		[A-Za-z] : Letra.
	
	for (std::string::const_iterator Posicion_Actual = (Cadena_Infija.cbegin () + Posicion) ; Posicion_Actual != Cadena_Infija.cend () ; ++ Posicion_Actual) {
		
		// Leeremos el siguiente caracter.
		
		const char Simbolo = *(Posicion_Actual);
		
		// Validamos el simbolo para saber que cumpla con ser una letra. Si es un digito , parentesis � espacio entonces terminamos el bucle.
	
		if (isdigit (static_cast <int> (Simbolo)) || (Simbolo == '(') || (Simbolo == ' ')) {
			
			// Terminamos el bucle.
			
			break;
			
		}
		
		// Anexamos el caracter a la cadena resultado.
		
		Cadena_Resultado.append (1u , Simbolo);
		
	}
	
	// Finalmente devolvemos el resultado.
	
	return Cadena_Resultado;
	
}

// -----------------------------------------------------------------------------

// --------------------  Definici�n del Aloritmo  ------------------------------

// Ahora viene la parte de implementar la funci�n evaluadora de cadenas postfijas , la cual arroja un resultado numerico a partir de la cadena indicada y opcionalmente
// un mapa de valores para cada variable utilizada en la cadena de entrada.

double Algoritmo_Postfija::Evaluate_Postfija (const std::string & Cadena_Postfija , size_t Argumentos , std::string * Variables , double * Valores) const {
	
	// El resultado final iniciado en 0.0.
	
	double Resultado = 0.0;
	
	// -------------------------------------------------------------------------
	
	// Lo primero que necesitamos tomar en cuenta es el conjunto de valores para cada variable si es que contamos con alguno.
	
	Tipo_Mapa_Valores Mapa_Valores;
	
	// Validamos si tenemos alg�n valor dentro de la lista.
	
	if (Argumentos > 0u) {
		
		// Iteramos por cada valor y lo vamos colocando en el mapa de valores.
		
		for (size_t Posicion_Argumento = 0u ; Posicion_Argumento < Argumentos ; ++ Posicion_Argumento) {
			
			// Insertamos este nuevo valor en el mapa.
			
			Mapa_Valores.insert (Variable_Valor (Variables [Posicion_Argumento] , Valores [Posicion_Argumento]));
			
		}
		
	}
	
	// -------------------------------------------------------------------------
	
	// --------------------------  Evaluaci�n  ---------------------------------
	
	// La evaluaci�n es un proceso mediante el cual vamos a realizar el seguimiento de la notaci�n postfija de nuestra expresi�n y vamos a ir aplicando
	// las operaciones sobre los operandos en el orden en el que vayan apareciendo , dando como resultado el valor que hubiera dado al aplicar la expresi�n
	// de manera natural.
	
	// Para conseguirlo ocuparemos la pila de n�meros nuevamente la cual servira para poder apilar los resultados conforme vayan siendo procesados y asu ves
	// estos iran siendo los operandos para las operaciones que vayan apareciendo , dejando al final la pila con un solo elemento que ser� nuestro resultado final.
	
	Pila_Numeros.clear ();
	
	// Ahora lo que necesitamos es recorrer nuevamente nuestra cadena de notaci�n postfija como lo hicimos para pasar de infija a postfija , con la posici�n
	// origen en 0.
	
	size_t Posicion = 0u;
	
	// Ahora lo que sigue es la iteraci�n mientras esta posici�n no sea mayor que el n�mero de caracteres en la cadena.
	
	while (Posicion < Cadena_Postfija.size ()) {
		
		// Buscaremos la posici�n del siguiente espacio o el terminador de la cadena.
		
		// size_t Posicion_Termino = Posicion;
		
		// Cadena leida la cual termina hasta encontrar un espacio o un terminador de cadena.
		
		std::string Cadena_Leida;
		
		// Iteramos en un bucle hasta encontrar el espacio o el final de cadena.
		
		while ((Posicion < Cadena_Postfija.size ()) && (Cadena_Postfija [Posicion % Cadena_Postfija.size ()] != ' ')) {
			
			// Anexamos este caracter a la cadena.
			
			Cadena_Leida.append (1u , Cadena_Postfija [Posicion]);
			
			// Incrementaremos la posici�n en 1.
			
			++ Posicion;
			
		}
		
		// Creamos la sub-cadena desde la posici�n origen hasta el termino.
		
		// std::string Cadena_Leida ((Cadena_Postfija.begin () + Posicion) , (Cadena_Postfija.begin () + ((Posicion_Termino < Cadena_Postfija.size ()) ? (Posicion_Termino - 1u) : Posicion_Termino));
		
		// Validamos si la cadena no est� vacia.
		
		if (!Cadena_Leida.empty ()) {
			
			// Entonces validamos que tipo de cadena es.
			
			if (Is_Number (Cadena_Leida)) {
				
				// Si es una variable, entonces tenemos que reemplazar la cadena por el valor que corresponda.
				
				if (Conjunto_Variables.count (Cadena_Leida) > 0u) {
					
					// Imprimiremos la cadena del valor en un buffer.
					
					char Buffer_Valor [100] = { '\0' };
					
					// Imprimiremos el valor respectivo si lo tenemos en el mapa de variables , si no asignamos un 0.
					
					sprintf (Buffer_Valor , "%.2lf" , ((Mapa_Valores.count (Cadena_Leida) > 0u) ? Mapa_Valores [Cadena_Leida] : 0.0));
					
					// Asignamos el valor a la cadena.
					
					Cadena_Leida = std::move (std::string (Buffer_Valor));
					
				}
				
				printf (" >> Numero Apilar : %s \n" , Cadena_Leida.c_str ());
				
				// Entonces simplemente apilamos la cadena en la pila de n�meros.
				
				Pila_Numeros.push_back (std::move (Cadena_Leida));
				
			}
			else if (Is_Operator (Cadena_Leida) || Is_Function (Cadena_Leida)) {
				
				// Si es un operador o una funci�n entonces tenemos que aplicar dicha evaluaci�n a nuestros operandos en la pila y el resultado
				// volverlo a apilar como si fuese otro numero m�s.
				
				const double Sub_Resultado = Evaluar_Funcion (Cadena_Leida);
				
				// Ahora vamos a convertir el valor a cadena
				
				char Buffer_Valor [100] = { '\0' };
				
				// Imprimiremos el valor respectivo si lo tenemos en el mapa de variables , si no asignamos un 0.
				
				sprintf (Buffer_Valor , "%.2lf" , Sub_Resultado);
				
				printf (" >> Resultado Apilar : %s \n" , Buffer_Valor);
				
				// Y apilaremos el resultado.
				
				Pila_Numeros.push_back (std::move (std::string (Buffer_Valor)));
				
			}
			
		}
		
		// Incrementamos nuevamente la posicion..
		
		++ Posicion;
		
	}
	
	// Validamos si la pila no est� vacia.
	
	if (!Pila_Numeros.empty ()) {
		
		// El ultimo paso es convertir el valor de cadena de la pila de n�meros resultante que quedo , como un valor double para asignar al resultado.
		
		try {
			
			// Convertimos el valor de cima de la pila en un double.
			
			Resultado = std::stod (Pila_Numeros.back ());
			
			// Limpiamos la pila.
			
			Pila_Numeros.clear ();
			
		} catch (...) {
			
			// En caso de que no se pueda convertir el resultado entonces devolvemos 0.0.
			
			return 0.0;
			
		}
		
	}
	
	// -------------------------------------------------------------------------
	
	// Finalmente devolvemos el valor resultante.
	
	return Resultado;
	
}

// -----------------------  Definici�n de Evaluaci�n  --------------------------

// Finalmente definiremos la funci�n que se encarga de realizar la operaci�n especificada mediante el operador o la funci�n indicada sobre los operandos
// que tenemos en la pila de n�meros actualmente.

double Algoritmo_Postfija::Evaluar_Funcion (const std::string & Operacion) const {
	
	// Tenemos el resultado en 0.0.
	
	double Resultado = 0.0;
	
	// -------------------------------------------------------------------------
	
	// Ahora vamos a realizar la operaci�n o funci�n determinada por la cadena de operaci�n.
	
	if (Is_Operator (Operacion)) {
		
		// ---------------------  Aplicar Operador  ----------------------------
		
		// Tenemos un operador , por lo que debemos comprobar que tengamos 2 operadores en la pila de n�meros actualmente y sacarlos.
		
		if (Pila_Numeros.size () > 1u) {
			
			// Obtenemos los dos operandos en el orden en el que esta , primero el Operando B (operando derecho) y luego el A (operando izquierdo).
			
			const std::string Cadena_B (Pila_Numeros.back ());
			
			// Sacamos este elemento de la pila.
			
			Pila_Numeros.pop_back ();
			
			// Ahora el Operando A.
			
			const std::string Cadena_A (Pila_Numeros.back ());
			
			// Sacamos este elemento de la pila.
			
			Pila_Numeros.pop_back ();
			
			// Ahora lo que haremos sera convertir dichos valores a double para posteriormente operar.
			
			try {
				
				// Convertimos el valor en double para ambos operandos.
				
				double Operando_A = std::stod (Cadena_A) , Operando_B = std::stod (Cadena_B);
				
				// Ahora realizamos la operaci�n respectiva de acuerdo al operando.
				
				Resultado = ((Operacion == "+") ? (Operando_A + Operando_B) :
					((Operacion == "-") ? (Operando_A - Operando_B) :
					((Operacion == "*") ? (Operando_A * Operando_B) :
					((Operacion == "/") ? (Operando_A / Operando_B) :
					((Operacion == "^") ? pow (Operando_A , Operando_B) : 0.0)))));
				
			} catch (...) {
				
				// devolvemos el resultado.
				
				return Resultado;
				
			}
			
		}
		
	}
	else if (Is_Function (Operacion)) {
		
		// ---------------------  Aplicar Funci�n  -----------------------------
		
		// Obtendremos la respectiva funci�n del mapa de funciones con el nombre de la misma.
		
		Funcion_Evaluacion Funcion_Aplicar = Conjunto_Funciones [Operacion];
		
		// Validaremos que la pila de n�meros tenga al menos el n�mero de argumentos necesario.
		
		if (Pila_Numeros.size () >= Funcion_Aplicar.first) {
			
			// Ahora lo que haremos sera tomar el n�mero de argumentos que tiene la funci�n en cuesti�n y con este valor obtendremos un array nuevo.
			
			double * Operandos = new double [Funcion_Aplicar.first];
			
			// Obtendremos los operandos de la pila de n�meros.
			
			for (size_t Operando_Posicion = 0u ; Operando_Posicion < Funcion_Aplicar.first ; ++ Operando_Posicion) {
				
				// Obtendremos la cadena del valor.
				
				const std::string Operando (Pila_Numeros.back ());
				
				// Sacamos este elemento de la pila.
				
				Pila_Numeros.pop_back ();
				
				// Intentaremos convertir el valor.
				
				try {
					
					// Convertimos el valor en double y lo asignamos.
					
					Operandos [Operando_Posicion] = std::stod (Operando);
					
				} catch (...) {
					
					// Destruimos el array de elementos.
					
					delete [] (Operandos);
					
					// Devolvemos el resultado.
					
					return Resultado;
					
				}
				
			}
			
			// Ahora vamos a realizar la aplicaci�n de la funci�n respectiva con los operandos indicados , asignando el resultado.
			
			Resultado = (Funcion_Aplicar.second) (Funcion_Aplicar.first , Operandos);
			
			// Destruimos el array de elementos.
			
			delete [] (Operandos);
			
		}
		
	}
	
	// -------------------------------------------------------------------------
	
	// Finalmente devolvemos el resultado.
	
	return Resultado;
	
}

// -----------------------------------------------------------------------------
