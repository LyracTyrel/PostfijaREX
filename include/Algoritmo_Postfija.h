
// -----------------------------------------------------------------------------

// Tenemos este archivo de cabecera para poder colocar los elementos de la clase Postfija la cual realiza la conversi�n a
// notaci�n postfija de una cadena de entrada en Infija.

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

// -------------------------  Notaci�n Postfija  -------------------------------

// Antes de comenzar daremos una breve explicaci�n de lo que es la notaci�n postfija tomando como base el siguiente texto y cito :
// Cuando usted escribe una expresi�n aritm�tica como B * C, la forma de la expresi�n le proporciona informaci�n para que pueda interpretarla correctamente.
// En este caso sabemos que la variable B est� siendo multiplicada por la variable C, ya que el operador de multiplicaci�n * aparece entre ellos en la expresi�n. Este tipo de notaci�n se conoce como infija ya que el operador est� entre los dos operandos sobre los que est� actuando.
// 
// Considere otro ejemplo de notaci�n infija, A + B * C. Los operadores + y * siguen apareciendo entre los operandos, pero hay un problema. 
// �Sobre qu� operandos act�an? �Opera el + sobre A y B o el * opera sobre B y C? La expresi�n parece ambigua.
// 
// De hecho, usted ha estado leyendo y escribiendo estos tipos de expresiones durante mucho tiempo y no le causan ning�n problema. 
// La raz�n de esto es que usted sabe algo sobre los operadores + y *. Cada operador tiene un nivel de precedencia. Los operadores de mayor precedencia se utilizan antes que los operadores de menor precedencia. Lo �nico que puede cambiar ese orden es la presencia de par�ntesis. El orden de precedencia para los operadores aritm�ticos ubica la multiplicaci�n y la divisi�n por encima de la suma y la resta. Si aparecen dos operadores de igual precedencia, se utiliza un ordenamiento o asociatividad de izquierda a derecha.
// 
// Interpretemos la expresi�n problem�tica A + B * C usando la precedencia de los operadores. B y C se multiplican primero y A se a�ade a ese resultado. (A + B) * C 
// forzar�a la suma de A y B antes de la multiplicaci�n. En la expresi�n A + B + C, por precedencia (v�a asociatividad), el + que est� m�s a la izquierda operar�a primero.
// 
// Aunque todo esto puede ser obvio para usted, recuerde que las computadoras necesitan saber exactamente qu� operadores deben ejecutarse y en qu� orden. 
// Una forma de escribir una expresi�n que garantice que no habr� confusi�n con respecto al orden de las operaciones es crear lo que se denomina expresi�n completamente agrupada. Este tipo de expresi�n utiliza una pareja de par�ntesis para cada operador. Los par�ntesis dictan el orden de las operaciones; no hay ambig�edad. Tampoco es necesario recordar las reglas de precedencia.
// 	
// La expresi�n A + B * C + D se puede reescribir como ((A + (B * C)) + D) para mostrar que la multiplicaci�n ocurre primero, seguida por la adici�n que est� m�s a la izquierda.
// A + B + C + D se puede escribir como ((A + B) + C) + D) ya que las operaciones de adici�n se asocian de izquierda a derecha.
// 	
// Hay otros dos formatos de expresi�n muy importantes que, al principio, pueden no parecer obvios. Considere la expresi�n infija A + B. 
// �Qu� pasar�a si movi�ramos el operador antes de los dos operandos? La expresi�n resultante ser�a + A B. Del mismo modo, podr�amos mover el operador al final. Obtendr�amos A B +. Estas expresiones se ven un poco extra�as.
// 	
// Estos cambios en la posici�n del operador con respecto a los operandos crean dos nuevos formatos de expresi�n, la notaci�n prefija y la notaci�n sufija (o postfija). 
// La notaci�n prefija requiere que todos los operadores precedan a los dos operandos sobre los que act�an. La notaci�n sufija, por otro lado, requiere que sus operadores aparezcan despu�s de los operandos correspondientes. Algunos ejemplos m�s deber�an ayudar a hacer esto un poco m�s claro (ver la Tabla 2).

// Fuente : http://interactivepython.org/runestone/static/pythoned/BasicDS/ExpresionesInfijasPrefijasYSufijas.html

// -----------------------------------------------------------------------------

// ---------------------------  Operadores  ------------------------------------

// La primera parte de este algoritmo consiste en declarar todos los Operadores Aritmeticos que tenemos disponibles y con esto nos referimos a lo siguientes simbolos convencionales :
// + : Suma
// - : Resta
// * : Multiplicacion
// / : Divisi�n
// ^ : Potencia
// ( , ) : Operador parentesis para ordenar las operaciones por prioridades.
// -(Numero) : Negativo

// Declararemos un mapa o diccionario de operadores junto a su respectivo valor de prioridad de acuerdo a la regla de operaciones.

extern std::unordered_map <std::string , size_t> Conjunto_Operadores;

// -----------------------------------------------------------------------------

// ---------------------------  Variables  -------------------------------------

// Las variables son representaciones de valores que desconocemos en el momento de declarar la expresi�n pero que toman un valor (Numero) una vez que son evaluadas dichas expresiones.
// Podemos tratar a las variables como si fueran numeros , por lo que necesitamos tener un conjunto predefinido de las posibles variables y sus simbolos para evitar que se interpreten
// como operadores en la expresi�n.

// Las variables convencionales son : Xx , Yy , Zz , por lo tanto.

extern std::unordered_set <std::string> Conjunto_Variables;

// -----------------------------------------------------------------------------

// ---------------------------  Funciones  -------------------------------------

// De manera similar que con los operadores , contamos con palabras reservadas para cada funci�n matematica definida en el programa , usamos los nombres convencionales de
// una calculadora cientifica , por lo tanto tenemos a :
// sen : seno
// cos : coseno
// tan : tangente
// asen : arco-seno
// acos : arco-coseno
// atan : arco-tangente
// sqrt : raiz cuadrada

// Para poder realizar la evaluaci�n de una cadena en notaci�n postfija necesitamos tener todo el conjunto de funciones antes mencionadas declaradas para luego implementarlas.
// Cada funci�n tiene que cumplir con el siguiente prototipo.
// Siendo el primer argumento el n�mero de valores a pasar a la funci�n y el segundo el array con dichos valores.

typedef double (* Tipo_Funcion) (size_t , double *);

// Funci�n : Sen.

double Funcion_Sen (size_t Argumentos , double * Valores);

// Funci�n : Cos.

double Funcion_Cos (size_t Argumentos , double * Valores);

// Funci�n : Tan.

double Funcion_Tan (size_t Argumentos , double * Valores);

// Funci�n : Asen.

double Funcion_Asen (size_t Argumentos , double * Valores);

// Funci�n : Acos.

double Funcion_Acos (size_t Argumentos , double * Valores);

// Funci�n : Atan.

double Funcion_Atan (size_t Argumentos , double * Valores);

// Funci�n : Sen.

double Funcion_Sqrt (size_t Argumentos , double * Valores);

// Para tener el mapa organizado con el nombre de la funci�n , el n�mero de argumentos y la respectiva direcci�n de memoria , requerimos un mapa que
// tenga como ID el nombre y como valor una paridad (Argumentos , Memoria). Siendo asi.

typedef std::pair <size_t , Tipo_Funcion> Funcion_Evaluacion;

// Declaramos un conjunto de las funciones disponibles.

extern std::unordered_map <std::string , Funcion_Evaluacion> Conjunto_Funciones;

// -----------------------------------------------------------------------------

// ---------------------------  Expresiones  -----------------------------------

// Como parte adicional de nuestro algoritmo , se realiza una serie de validaciones para asegurarse que en primer lugar la expresi�n es valida , si los digitos son
// correctos y la estructura de la expresi�n tambien es valida , por ejemplo :

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

// Tenemos en primer lugar una expresi�n regular que determina si una cadena de entrada es valida , cumpliendo con las reglas gramaticales y matematicas.

extern const std::regex Expresion_Matematica;

// Tenemos ahora una expresi�n que determina si el numero es valido.
// Un numero valido puede ser de la forma : 20 , 30.5 , -3.56
// Un numero no valido es : 20.

extern const std::regex Expresion_Numero;

// Tenemos ahora una expresi�n que determina si el simbolo es un operador valido.
// Operadores validos : Mapa_Operadores (+ , - , * , / , ^)
// Operadores no validos : ~ , _ , ...

extern const std::regex Expresion_Operador;

// -----------------------------------------------------------------------------

// ---------------------------  Algoritmo  -------------------------------------

// Ahora vamos a comenzar la declaraci�n de la clase para el algoritmo y todos sus elementos y metodos auxiliares para realizar la conversi�n de una notaci�n a otra.

class Algoritmo_Postfija {
	
	// --------------------------  Propiedades  --------------------------------
	
	private :
		
		// Como primera propiedad de nuestro algoritmo es precisamente la cadena de entrada en Notaci�n Infija , esta sera la base para que el algoritmo
		// pueda realizar todos los calculos necesarios.
		
		std::string Cadena_Entrada;
		
		// Como siguiente elemento para que el algoritmo pueda establecere todos los numeros en orden como van interpretando dicha cadena , se necesita de una Pila
		// de valores , la cual contendra numeros o expresiones en el orden en el que deben ser procesadas o evaluadas , por lo tanto requerimos de esta pila
		// de elementos para acomodar los valores. Utilizaremos el contenedor deque para almacenar dicha pila.
		
		// Los datos seran de tipo string ya que pueden ser expresiones conformadas por numeros , operadores , funciones , etc.
		
		mutable std::deque <std::string> Pila_Numeros;
		
		// Como siguiente elemento tenemos otra pila , pero esta vez la de Operadores , la cual tendra exclusivamente strings del conjunto de operadores anteriormente
		// declarados.
		
		// La pila de igual forma contiene solamente strings y sera utilizada para acomodar los operadores despues de los operandos con los que trabajar�.
		
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
		
		// Antes que nada tenemos un metodo que determina si la expresi�n actualmente asignada es valida , para esto contamos con las regular expresions.
		
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
		
		// Ahora tenemos la funci�n m�s importante , la cual se encarga de transformar la cadena de entrada actualmente establecida en una notaci�n
		// postfija , devolviendo el resultado de la cadena.
		
		// Este algoritmo se divide por partes separadas en metodos auxiliares , por lo que este metodo es una forma de agrupar el resto de pasos por lo que 
		// pasa el algoritmo completo.
		
		std::string Generate_Postfija () const;
		
		// ----------------------  Evaluador  ----------------------------------
		
		// Lo que tenemos es ahora el algoritmo para la evaluaci�n de una cadena en notaci�n postfija , teniendo como datos el mapa de variables y sus
		// respectivos valores con los cuales sustituir en la expresi�n actual. Devolviendo de esta forma el resultado de dicha expresi�n.
		
		typedef std::map <std::string , double> Tipo_Mapa_Valores;
		
		// Definimos el tipo de dato del mapa.
		
		typedef typename Tipo_Mapa_Valores::value_type Variable_Valor;
		
		// Declaramos ahora la funci�n par realizar la evaluaci�n completa de nuestra expresi�n en notaci�n postfija tomando en cuenta los valores pasados
		// en la entrada o ninguno si no hay necesidad de pasar valores para variables.
		
		double Evaluate_Postfija (const std::string & Cadena_Postfija , size_t Argumentos = 0u , std::string * Variables = nullptr , double * Valores = nullptr) const;
	
	// ----------------------  Metodos Auxiliares  -----------------------------
	
	private :
		
		// ------------------------  Cadena  -----------------------------------
		
		// Tenemos primero un metodo que permite limpiar la cadena de entrada , limpiar la cadena significa quitar los espacios en blanco.
		// dejar una cadena de la forma : 2 + 5x * (4+ 7) , en la forma : 2+5x*(4+7)  para que resulte un poco m�s facil interpretarla.
		
		std::string Cadena_Limpiar (const std::string & Cadena) const;
		
		// Tenemos ahora la funci�n recursiva que permitira ir leyendo una expresi�n en la forma : 2+5x*(4+7) e ir llenando la pila de
		// numeros y operadores con las partes que la componen asi como de organizar la sub-expresi�n en caso de ser necesario , devolviendo
		// la cadena especificada en notaci�n postfija. Recibe como entrada la cadena en notaci�n infija.
		
		std::string Cadena_Parsear (const std::string & Cadena) const;
		
		// Tenemos por ultimo la funci�n que interpreta lo que tenemos en ambas pilas como una expresi�n en notaci�n postfija , para ello
		// utiliza unicamente el contenido de las pilas actuales y devuelve la cadena de la expresi�n resultante.
		
		std::string Cadena_Organizar () const;
		
		// -------------------------  Pila  ------------------------------------
		
		// Tenemos un par de funciones que nos permiten realizar Operaciones sobre las pilas de numeros y de operadores al momento de
		// realizar el parseo de la cadena.
		
		// Primero tenemos la funci�n que realiza la apilaci�n de nuestros valores , ya sean : n�meros , variables o sub-expresiones.
		
		void Apilar_Numero (const std::string & Cadena) const;
		
		// Para apilar un n�mero en move constructor tenemos esta funci�n.
		
		void Apilar_Numero (std::string && Cadena) const;
		
		// Asi mismo tenemos la siguiente funci�n que realiza la apilaci�n de nuestros. De acuerdo a la jerarquia
		// de los operadores.
		
		void Apilar_Operador (const std::string & Cadena) const;
		
		// ----------------------  Validaci�n  ---------------------------------
		
		// Tenemos como validaci�n adicional la de un Numero o Variable (X , Y , Z) de una cadena determinada.
		
		bool Is_Number (const std::string & Cadena) const;
		
		// Tenemos como otra validaci�n la de si la cadena es un Operador.
		
		bool Is_Operator (const std::string & Cadena) const;
		
		// Y la validaci�n si es una funci�n de entre la lista de funciones anteriormente mencionada.
		
		bool Is_Function (const std::string & Cadena) const;
		
		// ------------------------  Posicion  ---------------------------------
		
		// Tenemos una funci�n especifica que nos ayuda a determinar la posici�n final de cierre de un parentesis '(' , tomando en
		// cuenta todas las jerarquias que pudiera tener dentro este parentesis.
		
		size_t Expresion_Terminador (const std::string & Cadena , size_t Posicion = 0u) const;
		
		// -----------------------  Auxiliares  --------------------------------
		
		// Ahora vamos a implementar los metodos que acompa�an al algoritmo para poder realizar todo el proceso de manera organizada
		// y de esta forma evitar repetir partes de codigo en toda una funci�n.
		
		// Tenemos en primer lugar el metodo que realiza la lectura de la siguiente cadena ya sea de tipo Numerico , Operador o Funcion.
		// Tomando como argumento la cadena en expresi�n infija a interpretar y la posici�n en la que vamos procesando.
		
		std::string Read_Next (const std::string & Cadena_Infija , size_t Posicion = 0u) const;
		
		// Ahora tenemos otro metodo que permite leer una cadena de tipo Numerico a partir de la posici�n indicada y devolver dicho resultado.
		
		std::string Read_Number (const std::string & Cadena_Infija , size_t Posicion = 0u) const;
		
		// Tenemos otro metodo que lee una funci�n , las funciones estan compuestas de letras y posiblemente n�meros de acuerdo a la tabla.
		
		std::string Read_Function (const std::string & Cadena_Infija , size_t Posicion = 0u) const;
		
		// -----------------------  Evaluaci�n  --------------------------------
		
		// Finalmente tenemos un metodo el cual realiza una funci�n simpl� y es la de aplicar un operador y/o funci�n a nuestra evaluaci�n
		// actual al momento de evaluar la cadena , tomando en cuenta los operadores de la pila y los operandos. Devuelve el valor
		// resultante de aplicar dicha evaluaci�n.
		
		double Evaluar_Funcion (const std::string & Operacion) const;
	
};

// -----------------------------------------------------------------------------

#endif // ALGORITMO_POSTFIJA

// -----------------------------------------------------------------------------
