
// -----------------------------------------------------------------------------

// Cabecera para la declaraci�n de la pantalla principal de la aplicaci�n grafica.

#ifndef PANTALLA_PRINCIPAL
#define PANTALLA_PRINCIPAL

// -----------------------------------------------------------------------------

// ---------------------------  wxWidgets  -------------------------------------

// Incluiremos las cabeceras de wxWidgets para poder trabajar con los wxFrame y los componentes que ocuparemos.

#include <wx/wx.h>


// -----------------------------------------------------------------------------

// ---------------------------  Algoritmo  -------------------------------------

// Ahora vamos a incluir nuestro modulo m�s importante , en el cual esta escrito el algoritmo para poder convertir cadenas a notaci�n
// postfija y evaluarlas.

#include <Algoritmo_Postfija.h>


// -----------------------------------------------------------------------------

// -----------------------  Pantalla Evaluar  ----------------------------------

// Implementaremos primero la pantalla de evaluaci�n la cual simplemente va a mostrar tres cajas de texto para que el usuario escriba
// los valores que quieren que tengan las posibles variables X , Y � Z , de esta forma podra realizar el programa el reemplazo necesario
// al momento de evaluar una expresi�n postfija.

class Postfija_Pantalla_Evaluar : public wxDialog {
	
	// Elementos privados de nuestro dialogo.
	
	private :
		
		// ----------------------  Componentes de GUI  -------------------------
		
		// Comenzaremos por colocar el contenedor de todos los elementos en este dialogo.
		
		wxPanel * Contenedor;
		
		// Ahora requerimos una etiqueta para el titulo de nuestra pantalla y las indicaciones.
		
		wxStaticText * Etiqueta_Evaluar;
		
		// Ahora necesitamos otras tres etiquetas para cada variable disponible (x , y , z).
		
		wxStaticText * Etiqueta_X;
		wxStaticText * Etiqueta_Y;
		wxStaticText * Etiqueta_Z;
		
		// De igual forma necesitamos las tres cajas de texto para que el usuario coloque el valor para cada variable.
		
		wxTextCtrl * Texto_X;
		wxTextCtrl * Texto_Y;
		wxTextCtrl * Texto_Z;
		
		// Necesitamos tambien tener almacenado un valor que nos permita determinar cuales variables utilizar [x , y , z].
		
		bool Utilizar_X , Utilizar_Y , Utilizar_Z;
		
		// Ahora finalmente tenemos los botones cl�sicos de cualquier dialogo , los de aceptar y cancelar.
		
		wxButton * Boton_Aceptar;
		wxButton * Boton_Cancelar;
	
	// Ahora los metodos publicos.
	
	public :
		
		// Enumeramos todos los ID de elementos.
		
		enum ID {
			
			// Botones de acci�n.
			
			ID_Boton_Aceptar = 0 ,
			ID_Boton_Cancelar
			
		};
		
		// -------------------------  Constructor  -----------------------------
		
		// Declaramos nuestro constructor el cual realiza la construcci�n de los elementos en la pantalla y asi mismo
		// habilita y desabilita los que no se requieran a partir de los parametros indicados.
		
		Postfija_Pantalla_Evaluar (wxWindow * Parental , bool Usar_X = true , bool Usar_Y = true , bool Usar_Z = true);
		
		// -------------------------  Accesores  -------------------------------
		
		// Para recuperar el valor en double de cada caja de datos , tenemos un metodo para cada caja.
		
		// Para recuperar el valor X del dialogo actual.
		
		double Get_X ();
		
		// Para recuperar el valor Y del dialogo actual.
		
		double Get_Y ();
		
		// Para recuperar el valor Z del dialogo actual.
		
		double Get_Z ();
		
		// -------------------------  Eventos  ---------------------------------
		
		// Finalmente tenemos el evento para el bot�n aceptar , el cual validara que todas las cadenas esten correctas o de lo contrario
		// mostrara un mensaje de error.
		
		void Evento_Aceptar (wxCommandEvent & Argumentos);
		
		// Declaramos aqui tambien la tabla de eventos.
		
		DECLARE_EVENT_TABLE ()
	
};

// -----------------------------------------------------------------------------

// -------------------- -  Pantalla Principal  ---------------------------------

// Ahora vamos a implementar una clase derivada de un wxFrame donde tendremos nuestros componentes para la aplicaci�n.

class Postfija_Pantalla : public wxFrame {
	
	// Eleentos privados de la pantalla.
	
	private : 
		
		// ----------------------  Componentes de GUI  -------------------------
		
		// Los componentes , botones , contenedor , etc.
		
		// Contenedor principal.
		
		wxPanel * Contenedor;
		
		// Tenemos la etiqueta para indicar donde escribir la expresi�n :
		
		wxStaticText * Etiqueta_Expresion;
		
		// Ahora la caja de texto donde el usuario escribira su expresi�n de entrada que quiere evaluar o convertir a postfija.
		
		wxTextCtrl * Texto_Expresion;
		
		// Botones que se utilizar�n.
		
		wxButton * Boton_Convetir;
		wxButton * Boton_Evaluar;
		
		// Ahora vamos a declarar un peque�o cuadro de texto donde se podra ir colocando los resultados de las conversiones.
		
		wxTextCtrl * Texto_Algoritmo;
		
		// ----------------------  Expresiones  --------------------------------
		
		// Asi mismo almacenaremos lo que es la cadena de entrada en notaci�n infija que el usuario escriba.
		
		std::string Expresion_Infija;
		
		// Y la cadena resultante en notaci�n postfija que corresponda.
		
		std::string Expresion_Postfija;
	
	// Ahora los metodos publicos de la pantalla.
	
	public :
		
		// Enumeramos todos los componentes de esta pantalla para que tengan un ID unico.
		
		enum ID {
			
			// Controles de etiqueta.
			
			ID_Etiqueta_Expresion = 0 ,
			
			// Botones de acci�n.
			
			ID_Boton_Convertir ,
			ID_Boton_Evaluar ,
			
			// Cajas de Texto.
			
			ID_Texto_Expresion ,
			ID_Texto_Algoritmo
			
		};
		
		// El constructor de nuestra pantalla que inicializa todos los componentes asi como rellena con valores por defectos.
		
		Postfija_Pantalla ();
	
	// Metodos privados para los eventos e inicializadores.
	
	private :
		
		// Inicializador de la pantalla y todos sus componentes.
		
		void Init_Pantalla ();
		
		// ----------------------------  Eventos  ------------------------------
		
		// Funci�n para el evento de parsear cadena de entrada a notaci�n postfija.
		
		void Evento_Convertir (wxCommandEvent & Argumento);
		
		// Funci�n para el evento de evaluar una cadena en notaci�n postfija , dandole valores a sus respectivas variables.
		
		void Evento_Evaluar (wxCommandEvent & Argumento);
		
		// Declaramos la tabla de eventos para esta pantalla.
		
		DECLARE_EVENT_TABLE ()
		
		// ------------------------  Auxiliares  -------------------------------
		
		// Asi mismo contamos con algunos metodos que ayudan a mejorar la modularidad de nuestro programa al separar en partes los
		// diferentes procesos por los cuales tenemos que pasar , desde convertir una cadena de infija a postfija , hasta la
		// evaluaci�n tomando en cuenta los valores escritos por el usuario.
		
		// Empezaremos por la funci�n que transforma la cadena de entrada indicada , a una en notaci�n postfija y la escribe en
		// la respectiva caja de resultados , devolviendo el dicho valor de la cadena.
		
		std::string Convertir_Postfija (const std::string & Cadena_Entrada);
		
		// Ahora la funci�n que se encarga de evaluar una cadena en notaci�n postfija con una serie de valores que se pasen como argumento
		// a est� funci�n mediante un array. Devolviendo el resultado n�merico que se genera.
		
		double Evaluar_Postfija (const std::string & Cadena_Postfija , size_t Argumentos = 0u , std::string * Variables = nullptr , double * Valores = nullptr);
	
};

// -----------------------------------------------------------------------------

#endif

// -----------------------------------------------------------------------------
