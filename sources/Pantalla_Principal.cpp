
// -----------------------------------------------------------------------------

// Implementaremos los metodos de la pantalla principal.

#include <Pantalla_Principal.h>

// -----------------------------------------------------------------------------

// Constructor para nuestra pantalla de los valores a evaluar.

Postfija_Pantalla_Evaluar::Postfija_Pantalla_Evaluar (wxWindow * Parental , bool Usar_X , bool Usar_Y , bool Usar_Z) : wxDialog (Parental , wxID_ANY , wxString ("Valores para Evaluar")) {
	
	// Lo primero que vamos a hacer es crear nuestro contenedor principal.
	
	Contenedor = new wxPanel (this , wxID_ANY , wxPoint (0 , 0) , wxSize (300 , 220));
	
	// Asignaremos los valores para usar cada variable.
	
	Utilizar_X = Usar_X;
	Utilizar_Y = Usar_Y;
	Utilizar_Z = Usar_Z;
	
	// -----------------------------  Componentes  -----------------------------
	
	// Crearemos la Etiqueta del titulo.
	
	Etiqueta_Evaluar = new wxStaticText (Contenedor , wxID_ANY , wxString ("Escribe los valores.") , wxPoint (26 , 12) , wxSize (248 , 30));
	
	// Ahora vamos a crear las etiquetas para cada variable.
	
	Etiqueta_X = new wxStaticText (Contenedor , wxID_ANY , wxString ("X") , wxPoint (26 , 48) , wxSize (35 , 30));
	Etiqueta_Y = new wxStaticText (Contenedor , wxID_ANY , wxString ("Y") , wxPoint (26 , 88) , wxSize (35 , 30));
	Etiqueta_Z = new wxStaticText (Contenedor , wxID_ANY , wxString ("Z") , wxPoint (26 , 128) , wxSize (35 , 30));
	
	// Ahora con las cajas de valores.
	
	Texto_X = new wxTextCtrl (Contenedor , wxID_ANY , wxEmptyString , wxPoint (71 , 43) , wxSize (200 , 30));
	Texto_Y = new wxTextCtrl (Contenedor , wxID_ANY , wxEmptyString , wxPoint (71 , 83) , wxSize (200 , 30));
	Texto_Z = new wxTextCtrl (Contenedor , wxID_ANY , wxEmptyString , wxPoint (71 , 123) , wxSize (200 , 30));
	
	// Ahora vamos a validar si tenemos activos todos los elementos o solo algunos.
	
	Etiqueta_X->Enable (Utilizar_X) , Texto_X->Enable (Utilizar_X);
	Etiqueta_Y->Enable (Utilizar_Y) , Texto_Y->Enable (Utilizar_Y);
	Etiqueta_Z->Enable (Utilizar_Z) , Texto_Z->Enable (Utilizar_Z);
	
	// Finalmente crearemos los botones para aceptar y cancelar.
	
	Boton_Aceptar = new wxButton (Contenedor , ID::ID_Boton_Aceptar , wxString ("Aceptar") , wxPoint (21 , 178) , wxSize (115 , 30));
	Boton_Cancelar = new wxButton (Contenedor , ID::ID_Boton_Cancelar , wxString ("Cancelar") , wxPoint (163 , 178) , wxSize (115 , 30));
	
	// Establecemos el ID de escape en el boton de cancelar.
	
	SetEscapeId (ID::ID_Boton_Cancelar);
	
	// ----------------------------  Fuentes  ----------------------------------
	
	// Crearemos una nueva fuente para la etiqueta de nuestro titulo , etiquetas y números con estas caracteristicas : Pt : 14 , face "Times New Roman".
	
	wxFont Fuente_Evaluacion (wxFontInfo (14).FaceName ("Times New Roman"));
	
	// Asignaremos la fuente al titulo.
	
	Etiqueta_Evaluar->SetFont (Fuente_Evaluacion);
	
	// Ahora a las etiquetas de valores.
	
	Etiqueta_X->SetFont (Fuente_Evaluacion) , Etiqueta_Y->SetFont (Fuente_Evaluacion) , Etiqueta_Z->SetFont (Fuente_Evaluacion);
	
	// Y a las cajas de texto.
	
	Texto_X->SetFont (Fuente_Evaluacion) , Texto_Y->SetFont (Fuente_Evaluacion) , Texto_Z->SetFont (Fuente_Evaluacion);
	
	// -------------------------------------------------------------------------
	
	// Ajustamos el tamaño y centramos.
	
	Fit () , Center ();
	
}

// ---------------------- Definición de Acessores  -----------------------------

// Implementaremos el metodo para convertir la caja de valor X en double.

double Postfija_Pantalla_Evaluar::Get_X () {
	
	// El resultado inicial es 0.0.
	
	double Resultado = 0.0;
	
	// Validamos si tenemos habilitado la caja.
	
	if (Texto_X->IsEnabled ()) {
		
		// Entonces intentaremos convertir el valor que tiene en un número.
		
		try {
			
			// Asignamos el resultado de la conversión.
			
			Resultado = stod (Texto_X->GetValue ().ToStdString ());
			
		} catch (...) {
			
			// Mostraremos un error de conversión.
			
			wxMessageBox (wxString ("Error , escribe un número valido para X") , wxString ("Error de Número") , (wxOK | wxCENTRE | wxICON_ERROR) , this);
			
		}
		
	}
	
	// Devolvemos el resultado.
	
	return Resultado;
	
}

// Ahora para el valor de Y.

double Postfija_Pantalla_Evaluar::Get_Y () {
	
	// El resultado inicial es 0.0.
	
	double Resultado = 0.0;
	
	// Validamos si tenemos habilitado la caja.
	
	if (Texto_Y->IsEnabled ()) {
		
		// Entonces intentaremos convertir el valor que tiene en un número.
		
		try {
			
			// Asignamos el resultado de la conversión.
			
			Resultado = stod (Texto_Y->GetValue ().ToStdString ());
			
		} catch (...) {
			
			// Mostraremos un error de conversión.
			
			wxMessageBox (wxString ("Error , escribe un número valido para Y") , wxString ("Error de Número") , (wxOK | wxCENTRE | wxICON_ERROR) , this);
			
		}
		
	}
	
	// Devolvemos el resultado.
	
	return Resultado;
	
}

// Asi tambien para Z.

double Postfija_Pantalla_Evaluar::Get_Z () {
	
	// El resultado inicial es 0.0.
	
	double Resultado = 0.0;
	
	// Validamos si tenemos habilitado la caja.
	
	if (Texto_Z->IsEnabled ()) {
		
		// Entonces intentaremos convertir el valor que tiene en un número.
		
		try {
			
			// Asignamos el resultado de la conversión.
			
			Resultado = stod (Texto_Z->GetValue ().ToStdString ());
			
		} catch (...) {
			
			// Mostraremos un error de conversión.
			
			wxMessageBox (wxString ("Error , escribe un número valido para X") , wxString ("Error de Número") , (wxOK | wxCENTRE | wxICON_ERROR) , this);
			
		}
		
	}
	
	// Devolvemos el resultado.
	
	return Resultado;
	
}

// ----------------------  Definición de Eventos  ------------------------------

// Lo primero es declarar la tabla de eventos para este dialogo.

BEGIN_EVENT_TABLE (Postfija_Pantalla_Evaluar , wxDialog)
	
	// Declaramos el evento del botón aceptar.
	
	EVT_BUTTON (Postfija_Pantalla_Evaluar::ID::ID_Boton_Aceptar , Postfija_Pantalla_Evaluar::Evento_Aceptar)
	
END_EVENT_TABLE ()

// Ahora implementaremos el metodo para este evento que validará que las cadenas numericas sean validas.

void Postfija_Pantalla_Evaluar::Evento_Aceptar (wxCommandEvent & Argumentos) {
	
	// Ahora lo que vamos a hacer es validar que las cadenas dentro de los campos sean números validos.
	
	if (Utilizar_X) {
		
		// Tenemos que validar la cadena siguiente.
		
		std::string Cadena_X (Texto_X->GetValue ().ToStdString ());
		
		// Validamos que no esté vacia y que sea un número haciendo uso de la expresión regular para ello.
		
		if (Cadena_X.empty () || !std::regex_match (Cadena_X , Expresion_Numero)) {
			
			// Mostramos el mensaje siguiente.
			
			wxMessageBox (wxString ("Error , escribe un número valido para X") , wxString ("Error de Número") , (wxOK | wxCENTRE | wxICON_ERROR) , this);
			
			// Terminamos la función.
			
			return;
			
		}
		
	}
	
	// Lo mismo para Y.
	
	if (Utilizar_Y) {
		
		// Tenemos que validar la cadena siguiente.
		
		std::string Cadena_Y (Texto_Y->GetValue ().ToStdString ());
		
		// Validamos que no esté vacia y que sea un número haciendo uso de la expresión regular para ello.
		
		if (Cadena_Y.empty () || !std::regex_match (Cadena_Y , Expresion_Numero)) {
			
			// Mostramos el mensaje siguiente.
			
			wxMessageBox (wxString ("Error , escribe un número valido para Y") , wxString ("Error de Número") , (wxOK | wxCENTRE | wxICON_ERROR) , this);
			
			// Terminamos la función.
			
			return;
			
		}
		
	}
	
	// Y para Z.
	
	if (Utilizar_Z) {
		
		// Tenemos que validar la cadena siguiente.
		
		std::string Cadena_Z (Texto_Z->GetValue ().ToStdString ());
		
		// Validamos que no esté vacia y que sea un número haciendo uso de la expresión regular para ello.
		
		if (Cadena_Z.empty () || !std::regex_match (Cadena_Z , Expresion_Numero)) {
			
			// Mostramos el mensaje siguiente.
			
			wxMessageBox (wxString ("Error , escribe un número valido para Z") , wxString ("Error de Número") , (wxOK | wxCENTRE | wxICON_ERROR) , this);
			
			// Terminamos la función.
			
			return;
			
		}
		
	}
	
	// Finalmente si no hubo error alguno , terminamos el dialogo modal con codigo afirmativo.
	
	EndModal (ID::ID_Boton_Aceptar);
	
}

// -----------------------------------------------------------------------------

// Constructor de nuestra pantalla principal.

Postfija_Pantalla::Postfija_Pantalla () : wxFrame (nullptr , wxID_ANY , wxString ("Notación Postfija - REX") , wxDefaultPosition , wxDefaultSize , wxDEFAULT_FRAME_STYLE & ~(wxRESIZE_BORDER | wxMAXIMIZE_BOX)) {
	
	// Utilizando el siguiente metodo iniciaremos todos los componentes de esta pantalla.
	
	Init_Pantalla ();
	
	// Ajustamos el tamaño , centramos y presentamos.
	
	Fit () , Center () , Show (true);
	
}

// -----------------------------------------------------------------------------

// Ahora los metodos privados , comenzando por el inicializador de la pantalla.

void Postfija_Pantalla::Init_Pantalla () {
	
	// Crearemos como primer elemento el contenedor o panel para ir colocando sobre esté los demas componentes.
	
	Contenedor = new wxPanel (this , wxID_ANY , wxPoint (0 , 0) , wxSize (580 , 620));
	
	// -----------------------------  Componentes  -----------------------------
	
	// Crearemos ahora el componente de texto para la etiqueta.
	
	Etiqueta_Expresion = new wxStaticText (Contenedor , ID::ID_Etiqueta_Expresion , wxString ("Escribe la expresión matemática : ") , wxPoint (26 , 18) , wxSize (508 , 30));
	
	// La caja de texto donde el usuario escribira la expresión es la siguiente.
	
	Texto_Expresion = new wxTextCtrl (Contenedor , ID::ID_Texto_Expresion , wxEmptyString , wxPoint (26 , 48) , wxSize (528 , 30));
	
	// Colocaremos un hint en este elemento.
	
	Texto_Expresion->SetHint (wxString ("Ejemplo : 2 + 3 * 4"));
	
	// Ahora los dos botones para poder realizar la conversión de nuestra cadena de entrada.
	
	Boton_Convetir = new wxButton (Contenedor , ID::ID_Boton_Convertir , wxString ("Convertir a Postfija") , wxPoint (26 , 93) , wxSize (250 , 30));
	Boton_Evaluar = new wxButton (Contenedor , ID::ID_Boton_Evaluar , wxString ("Evaluar Expresión") , wxPoint (304 , 93) , wxSize (250 , 30));
	
	// Ahora finalmente crearemos la caja de texto donde iran las salidas del algoritmo.
	
	Texto_Algoritmo = new wxTextCtrl (Contenedor , ID::ID_Texto_Algoritmo , wxEmptyString , wxPoint (26 , 143) , wxSize (528 , 451) , (wxTE_MULTILINE | wxTE_LEFT | wxTE_RICH));
	
	// ----------------------------  Fuente  -----------------------------------
	
	// Crearemos una fuente para los textos y etiquetas. La fuente sera de esta forma : Pt : 14 , face "Times New Roman".
	
	wxFont Fuente_Expresion (wxFontInfo (14).FaceName ("Times New Roman"));
	
	// Asignaremos la fuente a los componentes de etiqueta.
	
	Etiqueta_Expresion->SetFont (Fuente_Expresion);
	
	// Asignaremos la fuente a la caja tambien.

	Texto_Expresion->SetFont (Fuente_Expresion);
	
	// -----------------------  Caja Algoritmo  --------------------------------
	
	// Ahora pasaremos a realizar una pequeña configuración a nuestra caja donde se colocará los datos de salida del programa conforme la expresión  y
	// los valores a evaluar.
	
	// En primer lugar lo haremos que solo sea de lectura.
	
	Texto_Algoritmo->SetEditable (false);
	
	// Estableceremos una fuente para esta caja con las siguietes propiedades : Face : "Times New Roman" , Size : 16pt , Color : Negro (variable).
	
	wxFont Fuente_Algoritmo (wxFontInfo (16).FaceName ("Times New Roman"));
	
	// Asignaremos la fuente a la caja de salida.
	
	Texto_Algoritmo->SetFont (Fuente_Algoritmo);
	
	// Imprimiremos un texto para indicar que esta caja es para las salidas.
	
	Texto_Algoritmo->AppendText (wxString (" >>>  Salida del Algoritmo  <<< \n"));
	
}

// -----------------------------------------------------------------------------

// -------------------------------  Eventos  -----------------------------------

// Ahora implementaremos los metodos respectivos para los eventos de cada botón , comenzamos primero declarando la tabla de eventos.

BEGIN_EVENT_TABLE (Postfija_Pantalla , wxFrame)

	// Eventos de los botones de acción.
	
	EVT_BUTTON (Postfija_Pantalla::ID::ID_Boton_Convertir , Postfija_Pantalla::Evento_Convertir)
	EVT_BUTTON (Postfija_Pantalla::ID::ID_Boton_Evaluar , Postfija_Pantalla::Evento_Evaluar)
	
END_EVENT_TABLE ()

// Ahora implementaremos el codigo para el metodo que atiende el botón de convertir , esté realizará la conversión de notación infija a postfija
// e ira imprimiendo el resultado en la caja de algoritmo.

void Postfija_Pantalla::Evento_Convertir (wxCommandEvent & Argumentos) {
	
	// Antes de continuar nos debemos asegurar que tenemos la cadena escrita en la caja respectiva.
	
	const wxString Cadena_Entrada (Texto_Expresion->GetValue ());
	
	// Validamos que no esté vacio.
	
	if (!Cadena_Entrada.IsEmpty ()) {
		
		// Ahora podemos simplemente llamar a la función que se encarga de convertir la cadena en postfija y asignar el resultado.
		
		Expresion_Postfija = std::move (Convertir_Postfija (std::string (Cadena_Entrada.c_str ())));
		
	}
	else {
		
		// Mostraremos el siguiente mensaje.
		
		wxMessageBox (wxString ("Escribe una Expresión Valida") , wxString ("Cadena Vacia") , (wxOK | wxCENTRE) , this);
		
	}
	
}

// Asi mismo implementaremos el codigo para nuestro metodo que determina el resultado despues de aplicar una evaluación con valores a nuestra
// expresión en notación postfija.

void Postfija_Pantalla::Evento_Evaluar (wxCommandEvent & Argumentos) {
	
	// Antes de continuar nos debemos asegurar que tenemos la cadena escrita en la caja respectiva.
	
	const wxString Cadena_Entrada (Texto_Expresion->GetValue ());
	
	// Validamos que no esté vacio.
	
	if (!Cadena_Entrada.IsEmpty ()) {
		
		// Primero tenemos que aplicar la conversión a notación postfija , si la cadena resultante no está vacia continuaremos.
		
		Expresion_Postfija = std::move (Convertir_Postfija (std::string (Cadena_Entrada.c_str ())));
		
		// Validamos que no esté vacia.
		
		if (!Expresion_Postfija.empty ()) {
			
			// Declaramos las cadenas para cada variable por defecto .
			
			std::string Cadenas_Variables [3] = { std::string ("DEFAULT") , std::string ("DEFAULT") , std::string ("DEFAULT") };
			
			// Declaramos los valores por defecto en 0 para cada variable.
			
			double Valores_Variables [3] = { 0.0 };
			
			// Ahora vamos a realizar la evaluación pero para ello necesitamos determinar cuantas variables utilizar , 1 , 2 o 3. Para esto
			// buscaremos las variables X , Y , Z en la expresión.
			
			bool Utilizar_X = ((Expresion_Postfija.find_first_of ('X') != std::string::npos) || (Expresion_Postfija.find_first_of ('x') != std::string::npos));
			bool Utilizar_Y = ((Expresion_Postfija.find_first_of ('Y') != std::string::npos) || (Expresion_Postfija.find_first_of ('y') != std::string::npos));
			bool Utilizar_Z = ((Expresion_Postfija.find_first_of ('Z') != std::string::npos) || (Expresion_Postfija.find_first_of ('z') != std::string::npos));
			
			// El número de argumentos utilizados.
			
			size_t Cantidad_Variables = 0u;
			
			// Ahora vamos a Realizar la petición de datos para la evaluación si al menos tenemos una variable utilizada.
			
			if (Utilizar_X || Utilizar_Y || Utilizar_Z) {
				
				// Ahora vamos a crear un pequeño dialogo para solicitar los valores a utilizar en la evaluación. Creamos la pantalla.
				
				Postfija_Pantalla_Evaluar Dialogo_Evaluar (this , Utilizar_X , Utilizar_Y , Utilizar_Z);
				
				// Mostramos el dialogo motal y continuamos si es correcto.
				
				if (Dialogo_Evaluar.ShowModal () == Postfija_Pantalla_Evaluar::ID::ID_Boton_Aceptar) {
					
					// Ahora vamos a asignar las cadenas que se utilizaran. Empezando por la X
					
					if (Utilizar_X) {
						
						// Asignamos el valor de X del dialogo.
						
						Valores_Variables [Cantidad_Variables] = Dialogo_Evaluar.Get_X ();
						
						// Asignamos la siguiente cadena.
						
						Cadenas_Variables [Cantidad_Variables ++] = std::string (1u , ((Expresion_Postfija.find_first_of ('X') != std::string::npos) ?
							Expresion_Postfija [Expresion_Postfija.find ('X')] :
							Expresion_Postfija [Expresion_Postfija.find ('x')]));
						
					}
					
					// Ahora la Y.
					
					if (Utilizar_Y) {
						
						// Asignamos el valor de Y del dialogo.
						
						Valores_Variables [Cantidad_Variables] = Dialogo_Evaluar.Get_Y ();
						
						// Asignamos la siguiente cadena.
						
						Cadenas_Variables [Cantidad_Variables ++] = std::string (1u , ((Expresion_Postfija.find_first_of ('Y') != std::string::npos) ?
							Expresion_Postfija [Expresion_Postfija.find ('Y')] :
							Expresion_Postfija [Expresion_Postfija.find ('y')]));
						
					}
					
					// Finalmente la Z.
					
					if (Utilizar_Z) {
						
						// Asignamos el valor de Z del dialogo.
						
						Valores_Variables [Cantidad_Variables] = Dialogo_Evaluar.Get_Z ();
						
						// Asignamos la siguiente cadena.
						
						Cadenas_Variables [Cantidad_Variables ++] = std::string (1u , ((Expresion_Postfija.find_first_of ('Z') != std::string::npos) ?
							Expresion_Postfija [Expresion_Postfija.find ('Z')] :
							Expresion_Postfija [Expresion_Postfija.find ('z')]));
						
					}
					
				}
				else {
					
					// En caso de cancelar el dialogo simplemente devolvemos la función.
					
					return;
					
				}
				
			}
			
			// Por ultimo solo queda evaluar la expresión postfija con esta información.
			
			Evaluar_Postfija (Expresion_Postfija , Cantidad_Variables , Cadenas_Variables , Valores_Variables);
			
		}
		
	}
	else {
		
		// Mostraremos el siguiente mensaje.
		
		wxMessageBox (wxString ("Escribe una Expresión Valida") , wxString ("Cadena Vacia") , (wxOK | wxCENTRE) , this);
		
	}
	
}

// -----------------------------------------------------------------------------

// -----------------------------  Auxiliares  ----------------------------------

// Implementamos ahora la función que se encarga del proceso de transformar la cadena de entrada de notacion infija a postfija , colocando los resultados
// en la caja de texto y asi mismo devuelve la cadena std postfija obtenida.

std::string Postfija_Pantalla::Convertir_Postfija (const std::string & Cadena_Entrada) {
	
	// Generaremos la cadena de salida en notación postfija a partir de la entrada.
	
	std::string Cadena_Salida;
	
	// Lo primero que vamos a hacer es crear un nuevo Objeto de dicha clase del algoritmo para poder realizar la conversión. Usaremos la cadena de entrada.
	
	Algoritmo_Postfija Parser (Cadena_Entrada);
	
	// Validamos si la cadena de entrada es valida y continuamos
	
	if (Parser.Is_Valid ()) {
		
		// Ahora simplemente dejamos que el algoritmo haga el resto y asignamos la cadena resultante.
		
		Cadena_Salida = std::move (Parser.Generate_Postfija ());
		
		// -----------------------  Presentación  ------------------------------
		
		// Si la cadena es valida entonces mostramos lo siguiente.
		
		if (!Cadena_Salida.empty ()) {
			
			// Ahora presentaremos la salida en nuestra caja de texto actual con un formato como el que sigue.
			
			const wxString Formato_Salida (" --------------------------- \n >> Cadena Postfija : %s\n --------------------------- \n");
			
			// Ahora vamos a realizar la asignación de un atributo de texto por defecto en verde para la salida de este valor en la caja de texto.
			
			Texto_Algoritmo->SetDefaultStyle (wxTextAttr (wxColour (21 , 148 , 28) , wxNullColour , Texto_Algoritmo->GetFont ()));
			
			// Ahora vamos a escribir el resultado en la caja.
			
			Texto_Algoritmo->AppendText (wxString::Format (Formato_Salida , Cadena_Salida.c_str ()));
			
		}
		else {
			
			// Ahora vamos a realizar la asignación de un atributo de texto por defecto en rojo para la salida de este valor en la caja de texto.
			
			Texto_Algoritmo->SetDefaultStyle (wxTextAttr ((*wxRED) , wxNullColour , Texto_Algoritmo->GetFont ()));
			
			// Ahora vamos a escribir el siguiente mensaje en la caja.
			
			Texto_Algoritmo->AppendText (wxString (" --------------------------- \n >> Cadena de entrada no Valida : <Postfija Nullo> %s\n --------------------------- \n"));
			
		}
		
	}
	else {
		
		// Mostraremos un mensaje en la pantalla.
		
		wxMessageBox (wxString ("La expresión infija contiene errores") , wxString ("Expresión No Valida") , (wxOK | wxCENTRE | wxICON_ERROR));
		
	}
	
	// -------------------------------------------------------------------------
	
	// Devolvemos la cadena de salida en notación postfija.
	
	return Cadena_Salida;
	
}

// Ahora lo que haremos será evaluar nuestra cadena usando está función , la cual recibe como argumento la cadena postfija y los argumentos opcionales
// que pasaremos a cada variable dentro de la misma expresión.

double Postfija_Pantalla::Evaluar_Postfija (const std::string & Cadena_Postfija , size_t Argumentos , std::string * Variables , double * Valores) {
	
	// Tenemos el siguiente valor de resultado.
	
	double Resultado = 0.0;
	
	// -------------------------  Evaluación  ----------------------------------
	
	// Lo primero que vamos a realizar es crear nuestro Evaluador , sin ninguna cadena por el momento.
	
	Algoritmo_Postfija Evaluador;
	
	// Ahora solamente vamos a invocar a su metodo para evaluar la cadena en postfija que tenemos y obtener el resultado. Pasamos los
	// valores para cada variable.
	
	Resultado = Evaluador.Evaluate_Postfija (Cadena_Postfija , Argumentos , Variables , Valores);
	
	// ------------------------  Presentación  ---------------------------------
	
	// Vamos a realizar la asignación de un atributo de texto por defecto en azul para la salida de esta evaluación.
	
	Texto_Algoritmo->SetDefaultStyle (wxTextAttr ((*wxBLUE) , wxNullColour , Texto_Algoritmo->GetFont ()));
	
	// Lo primero es presentar cada variable con su respectivo valor.
	
	Texto_Algoritmo->AppendText (wxString (" --------------------------- \n"));
	
	// Validamos cada elemento si tenemos alguno y lo iremos mostrando.
	
	for (size_t Indice_Argumento = 0u ; Indice_Argumento < Argumentos ; ++ Indice_Argumento) {
		
		// Presentamos el valor de la variable actual.
		
		Texto_Algoritmo->AppendText (wxString::Format (wxString (" >> Variable [%s] : %.2lf\n") , Variables [Indice_Argumento] , Valores [Indice_Argumento]));
		
	}
	
	// Ahora presentaremos la salida en nuestra caja de texto actual con un formato como el que sigue.
	
	const wxString Formato_Salida (" >> Cadena Evaluada: %.2lf\n --------------------------- \n");
	
	// Ahora vamos a escribir el resultado en la caja.
	
	Texto_Algoritmo->AppendText (wxString::Format (Formato_Salida , Resultado));
	
	// -------------------------------------------------------------------------
	
	// Devolvemos el resultado final.
	
	return Resultado;
	
}

// -----------------------------------------------------------------------------
