
// -----------------------------------------------------------------------------

// Tenemos este archivo de cabecera para poder colocar los elementos de la clase Postfija la cual realiza la conversión a
// notación postfija de una cadena de entrada en Infija.

#ifndef ALGORITMO_POSTFIJA
#define ALGORITMO_POSTFIJA

// -----------------------------------------------------------------------------

// Para este ocuparemos elementos de c++ , comenzando por las entradas y salidas estandar.

#include <stdio.h>
#include <stdlib.h>

// Ahora las cadenas string de c/c++.

#include <string.h>
#include <string>

// Funciones matematicas estandar.

#include <math.h>

// Asi como elementos de STL , ocuparemos los contenedores siguientes :

#include <deque>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <initializer_list>

// Y por ultimo las utilerias y expresiones regulares que nos ofrece c++ 11.

#include <utility>
#include <regex>

// -----------------------------------------------------------------------------

// -------------------------  Notación Postfija  -------------------------------

// Antes de comenzar daremos una breve explicación de lo que es la notación postfija tomando como base el siguiente texto y cito :
// Cuando usted escribe una expresión aritmética como B * C, la forma de la expresión le proporciona información para que pueda interpretarla correctamente.
// En este caso sabemos que la variable B está siendo multiplicada por la variable C, ya que el operador de multiplicación * aparece entre ellos en la expresión. Este tipo de notación se conoce como infija ya que el operador está entre los dos operandos sobre los que está actuando.
// 
// Considere otro ejemplo de notación infija, A + B * C. Los operadores + y * siguen apareciendo entre los operandos, pero hay un problema. 
// ¿Sobre qué operandos actúan? ¿Opera el + sobre A y B o el * opera sobre B y C? La expresión parece ambigua.
// 
// De hecho, usted ha estado leyendo y escribiendo estos tipos de expresiones durante mucho tiempo y no le causan ningún problema. 
// La razón de esto es que usted sabe algo sobre los operadores + y *. Cada operador tiene un nivel de precedencia. Los operadores de mayor precedencia se utilizan antes que los operadores de menor precedencia. Lo único que puede cambiar ese orden es la presencia de paréntesis. El orden de precedencia para los operadores aritméticos ubica la multiplicación y la división por encima de la suma y la resta. Si aparecen dos operadores de igual precedencia, se utiliza un ordenamiento o asociatividad de izquierda a derecha.
// 
// Interpretemos la expresión problemática A + B * C usando la precedencia de los operadores. B y C se multiplican primero y A se añade a ese resultado. (A + B) * C 
// forzaría la suma de A y B antes de la multiplicación. En la expresión A + B + C, por precedencia (vía asociatividad), el + que está más a la izquierda operaría primero.
// 
// Aunque todo esto puede ser obvio para usted, recuerde que las computadoras necesitan saber exactamente qué operadores deben ejecutarse y en qué orden. 
// Una forma de escribir una expresión que garantice que no habrá confusión con respecto al orden de las operaciones es crear lo que se denomina expresión completamente agrupada. Este tipo de expresión utiliza una pareja de paréntesis para cada operador. Los paréntesis dictan el orden de las operaciones; no hay ambigüedad. Tampoco es necesario recordar las reglas de precedencia.
// 	
// La expresión A + B * C + D se puede reescribir como ((A + (B * C)) + D) para mostrar que la multiplicación ocurre primero, seguida por la adición que está más a la izquierda.
// A + B + C + D se puede escribir como ((A + B) + C) + D) ya que las operaciones de adición se asocian de izquierda a derecha.
// 	
// Hay otros dos formatos de expresión muy importantes que, al principio, pueden no parecer obvios. Considere la expresión infija A + B. 
// ¿Qué pasaría si moviéramos el operador antes de los dos operandos? La expresión resultante sería + A B. Del mismo modo, podríamos mover el operador al final. Obtendríamos A B +. Estas expresiones se ven un poco extrañas.
// 	
// Estos cambios en la posición del operador con respecto a los operandos crean dos nuevos formatos de expresión, la notación prefija y la notación sufija (o postfija). 
// La notación prefija requiere que todos los operadores precedan a los dos operandos sobre los que actúan. La notación sufija, por otro lado, requiere que sus operadores aparezcan después de los operandos correspondientes. Algunos ejemplos más deberían ayudar a hacer esto un poco más claro (ver la Tabla 2).

// Fuente : http://interactivepython.org/runestone/static/pythoned/BasicDS/ExpresionesInfijasPrefijasYSufijas.html

// -----------------------------------------------------------------------------

// ---------------------------  Operadores  ------------------------------------

// La primera parte de este algoritmo consiste en declarar todos los Operadores Aritmeticos que tenemos disponibles y con esto nos referimos a lo siguientes simbolos convencionales :
// + : Suma
// - : Resta
// * : Multiplicacion
// / : División
// ^ : Potencia
// ( , ) : Operador parentesis para ordenar las operaciones por prioridades.
// -(Numero) : Negativo

// Declararemos un mapa o diccionario de operadores junto a su respectivo valor de prioridad de acuerdo a la regla de operaciones.

extern std::unordered_map <std::string , size_t> Conjunto_Operadores;

// -----------------------------------------------------------------------------

// ---------------------------  Variables  -------------------------------------

// Las variables son representaciones de valores que desconocemos en el momento de declarar la expresión pero que toman un valor (Numero) una vez que son evaluadas dichas expresiones.
// Podemos tratar a las variables como si fueran numeros , por lo que necesitamos tener un conjunto predefinido de las posibles variables y sus simbolos para evitar que se interpreten
// como operadores en la expresión.

// Las variables convencionales son : Xx , Yy , Zz , por lo tanto.

extern std::unordered_set <std::string> Conjunto_Variables;

// -----------------------------------------------------------------------------

// ---------------------------  Funciones  -------------------------------------

// De manera similar que con los operadores , contamos con palabras reservadas para cada función matematica definida en el programa , usamos los nombres convencionales de
// una calculadora cientifica , por lo tanto tenemos a :
// sen : seno
// cos : coseno
// tan : tangente
// asen : arco-seno
// acos : arco-coseno
// atan : arco-tangente
// sqrt : raiz cuadrada

// Para poder realizar la evaluación de una cadena en notación postfija necesitamos tener todo el conjunto de funciones antes mencionadas declaradas para luego implementarlas.
// Cada función tiene que cumplir con el siguiente prototipo.
// Siendo el primer argumento el número de valores a pasar a la función y el segundo el array con dichos valores.

typedef double (* Tipo_Funcion) (size_t , double *);

// Función : Sen.

double Funcion_Sen (size_t Argumentos , double * Valores);

// Función : Cos.

double Funcion_Cos (size_t Argumentos , double * Valores);

// Función : Tan.

double Funcion_Tan (size_t Argumentos , double * Valores);

// Función : Asen.

double Funcion_Asen (size_t Argumentos , double * Valores);

// Función : Acos.

double Funcion_Acos (size_t Argumentos , double * Valores);

// Función : Atan.

double Funcion_Atan (size_t Argumentos , double * Valores);

// Función : Sen.

double Funcion_Sqrt (size_t Argumentos , double * Valores);

// Para tener el mapa organizado con el nombre de la función , el número de argumentos y la respectiva dirección de memoria , requerimos un mapa que
// tenga como ID el nombre y como valor una paridad (Argumentos , Memoria). Siendo asi.

typedef std::pair <size_t , Tipo_Funcion> Funcion_Evaluacion;

// Declaramos un conjunto de las funciones disponibles.

extern std::unordered_map <std::string , Funcion_Evaluacion> Conjunto_Funciones;

// -----------------------------------------------------------------------------

// ---------------------------  Expresiones  -----------------------------------

// Como parte adicional de nuestro algoritmo , se realiza una serie de validaciones para asegurarse que en primer lugar la expresión es valida , si los digitos son
// correctos y la estructura de la expresión tambien es valida , por ejemplo :

// Expresiones Validas :
//		1 * 3 + 4
//		5 + 6 * 10 + 242
//		(5 + 7) * (45.0 - 74.58)
//		sen (4x + 5) - 78

// Expresiones No Validas :
//		1 + + 3
//		5 6 * 7
//		(5 + 7 * 8
//		sen )45 + 5 * 6

// Asi que para determinar que las expresiones establecidas sean correctas usaremos expresiones regulares de C++ 11 para comprobarlo.

// Tenemos en primer lugar una expresión regular que determina si una cadena de entrada es valida , cumpliendo con las reglas gramaticales y matematicas.

extern const std::regex Expresion_Matematica;

// Tenemos ahora una expresión que determina si el numero es valido.
// Un numero valido puede ser de la forma : 20 , 30.5 , -3.56
// Un numero no valido es : 20.

extern const std::regex Expresion_Numero;

// Tenemos ahora una expresión que determina si el simbolo es un operador valido.
// Operadores validos : Mapa_Operadores (+ , - , * , / , ^)
// Operadores no validos : ~ , _ , ...

extern const std::regex Expresion_Operador;

// -----------------------------------------------------------------------------

// ---------------------------  Algoritmo  -------------------------------------

// Ahora vamos a comenzar la declaración de la clase para el algoritmo y todos sus elementos y metodos auxiliares para realizar la conversión de una notación a otra.

class Algoritmo_Postfija {
	
	// --------------------------  Propiedades  --------------------------------
	
	private :
		
		// Como primera propiedad de nuestro algoritmo es precisamente la cadena de entrada en Notación Infija , esta sera la base para que el algoritmo
		// pueda realizar todos los calculos necesarios.
		
		std::string Cadena_Entrada;
		
		// Como siguiente elemento para que el algoritmo pueda establecere todos los numeros en orden como van interpretando dicha cadena , se necesita de una Pila
		// de valores , la cual contendra numeros o expresiones en el orden en el que deben ser procesadas o evaluadas , por lo tanto requerimos de esta pila
		// de elementos para acomodar los valores. Utilizaremos el contenedor deque para almacenar dicha pila.
		
		// Los datos seran de tipo string ya que pueden ser expresiones conformadas por numeros , operadores , funciones , etc.
		
		mutable std::deque <std::string> Pila_Numeros;
		
		// Como siguiente elemento tenemos otra pila , pero esta vez la de Operadores , la cual tendra exclusivamente strings del conjunto de operadores anteriormente
		// declarados.
		
		// La pila de igual forma contiene solamente strings y sera utilizada para acomodar los operadores despues de los operandos con los que trabajará.
		
		mutable std::deque <std::string> Pila_Operadores;
	
	// ---------------------------  Metodos  -----------------------------------
	
	public :
		
		
		// -----------------------  Constructores  -----------------------------
		
		// Tenemos ahora el primer metodo que es el constructor por defecto de nuestra clase de algoritmo el cual deja los elementos vacios.
		
		Algoritmo_Postfija () = default;
		
		// Ahora un constructor que inicializa los elementos de nuestra clase , vacia las pilas , etc.
		
		explicit Algoritmo_Postfija (const std::string & Entrada_Infija);
		
		// De igual forma otro constructor pero para una cadena en move constructor.
		
		explicit Algoritmo_Postfija (std::string && Entrada_Infija);
		
		// ------------------------  Validacion  -------------------------------
		
		// Antes que nada tenemos un metodo que determina si la expresión actualmente asignada es valida , para esto contamos con las regular expresions.
		
		bool Is_Valid () const;
		
		// ------------------------  Accesors  ---------------------------------
		
		// Metodo de acceso para la cadena de Entrada en infija.
		
		const std::string & Get_Entrada () const {
			
			// Devolvemos la referencia a la cadena infija en este algoritmo.
			
			return Cadena_Entrada;
			
		}
		
		// ------------------------  Setters  ----------------------------------
		
		// Metodo para cambiar la cadena de entrada al igual como si usaramos el constructor.
		
		void Set_Entrada (const std::string & Nueva_Entrada);
		
		// Metodo para cambiar la cadena de entrada mediante move constructor.
		
		void Set_Entrada (std::string && Nueva_Entrada);
		
		// -----------------------  Algoritmo  ---------------------------------
		
		// Ahora tenemos la función más importante , la cual se encarga de transformar la cadena de entrada actualmente establecida en una notación
		// postfija , devolviendo el resultado de la cadena.
		
		// Este algoritmo se divide por partes separadas en metodos auxiliares , por lo que este metodo es una forma de agrupar el resto de pasos por lo que 
		// pasa el algoritmo completo.
		
		std::string Generate_Postfija () const;
		
		// ----------------------  Evaluador  ----------------------------------
		
		// Lo que tenemos es ahora el algoritmo para la evaluación de una cadena en notación postfija , teniendo como datos el mapa de variables y sus
		// respectivos valores con los cuales sustituir en la expresión actual. Devolviendo de esta forma el resultado de dicha expresión.
		
		typedef std::map <std::string , double> Tipo_Mapa_Valores;
		
		// Definimos el tipo de dato del mapa.
		
		typedef typename Tipo_Mapa_Valores::value_type Variable_Valor;
		
		// Declaramos ahora la función par realizar la evaluación completa de nuestra expresión en notación postfija tomando en cuenta los valores pasados
		// en la entrada o ninguno si no hay necesidad de pasar valores para variables.
		
		double Evaluate_Postfija (const std::string & Cadena_Postfija , size_t Argumentos = 0u , std::string * Variables = nullptr , double * Valores = nullptr) const;
	
	// ----------------------  Metodos Auxiliares  -----------------------------
	
	private :
		
		// ------------------------  Cadena  -----------------------------------
		
		// Tenemos primero un metodo que permite limpiar la cadena de entrada , limpiar la cadena significa quitar los espacios en blanco.
		// dejar una cadena de la forma : 2 + 5x * (4+ 7) , en la forma : 2+5x*(4+7)  para que resulte un poco más facil interpretarla.
		
		std::string Cadena_Limpiar (const std::string & Cadena) const;
		
		// Tenemos ahora la función recursiva que permitira ir leyendo una expresión en la forma : 2+5x*(4+7) e ir llenando la pila de
		// numeros y operadores con las partes que la componen asi como de organizar la sub-expresión en caso de ser necesario , devolviendo
		// la cadena especificada en notación postfija. Recibe como entrada la cadena en notación infija.
		
		std::string Cadena_Parsear (const std::string & Cadena) const;
		
		// Tenemos por ultimo la función que interpreta lo que tenemos en ambas pilas como una expresión en notación postfija , para ello
		// utiliza unicamente el contenido de las pilas actuales y devuelve la cadena de la expresión resultante.
		
		std::string Cadena_Organizar () const;
		
		// -------------------------  Pila  ------------------------------------
		
		// Tenemos un par de funciones que nos permiten realizar Operaciones sobre las pilas de numeros y de operadores al momento de
		// realizar el parseo de la cadena.
		
		// Primero tenemos la función que realiza la apilación de nuestros valores , ya sean : números , variables o sub-expresiones.
		
		void Apilar_Numero (const std::string & Cadena) const;
		
		// Para apilar un número en move constructor tenemos esta función.
		
		void Apilar_Numero (std::string && Cadena) const;
		
		// Asi mismo tenemos la siguiente función que realiza la apilación de nuestros. De acuerdo a la jerarquia
		// de los operadores.
		
		void Apilar_Operador (const std::string & Cadena) const;
		
		// ----------------------  Validación  ---------------------------------
		
		// Tenemos como validación adicional la de un Numero o Variable (X , Y , Z) de una cadena determinada.
		
		bool Is_Number (const std::string & Cadena) const;
		
		// Tenemos como otra validación la de si la cadena es un Operador.
		
		bool Is_Operator (const std::string & Cadena) const;
		
		// Y la validación si es una función de entre la lista de funciones anteriormente mencionada.
		
		bool Is_Function (const std::string & Cadena) const;
		
		// ------------------------  Posicion  ---------------------------------
		
		// Tenemos una función especifica que nos ayuda a determinar la posición final de cierre de un parentesis '(' , tomando en
		// cuenta todas las jerarquias que pudiera tener dentro este parentesis.
		
		size_t Expresion_Terminador (const std::string & Cadena , size_t Posicion = 0u) const;
		
		// -----------------------  Auxiliares  --------------------------------
		
		// Ahora vamos a implementar los metodos que acompañan al algoritmo para poder realizar todo el proceso de manera organizada
		// y de esta forma evitar repetir partes de codigo en toda una función.
		
		// Tenemos en primer lugar el metodo que realiza la lectura de la siguiente cadena ya sea de tipo Numerico , Operador o Funcion.
		// Tomando como argumento la cadena en expresión infija a interpretar y la posición en la que vamos procesando.
		
		std::string Read_Next (const std::string & Cadena_Infija , size_t Posicion = 0u) const;
		
		// Ahora tenemos otro metodo que permite leer una cadena de tipo Numerico a partir de la posición indicada y devolver dicho resultado.
		
		std::string Read_Number (const std::string & Cadena_Infija , size_t Posicion = 0u) const;
		
		// Tenemos otro metodo que lee una función , las funciones estan compuestas de letras y posiblemente números de acuerdo a la tabla.
		
		std::string Read_Function (const std::string & Cadena_Infija , size_t Posicion = 0u) const;
		
		// -----------------------  Evaluación  --------------------------------
		
		// Finalmente tenemos un metodo el cual realiza una función simplé y es la de aplicar un operador y/o función a nuestra evaluación
		// actual al momento de evaluar la cadena , tomando en cuenta los operadores de la pila y los operandos. Devuelve el valor
		// resultante de aplicar dicha evaluación.
		
		double Evaluar_Funcion (const std::string & Operacion) const;
	
};

// -----------------------------------------------------------------------------

#endif // ALGORITMO_POSTFIJA

// -----------------------------------------------------------------------------
