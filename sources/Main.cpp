
// -----------------------------------------------------------------------------

// Inicio de la aplicaci�n. Postfija_REX.
/// @author Menightmar
/// @date 02-03-2019
/// @brief Programa para traducir de notaci�n infija a postfija y evaluar expresiones matem�ticas.

// Anexaremos las siguientes cabeceras principales.

#include <stdio.h>
#include <stdlib.h>

// -----------------------------------------------------------------------------

// Tenemos la biblioteca de wxWidgets , incluiremos la cabecera general.

#include <wx/wx.h>

// Incluiremos ahora nuestros modulo de la pantalla principal.

#include <Pantalla_Principal.h>

// -----------------------------------------------------------------------------

// Lo primero ser� crear una clase que derive de wxApp para la aplicaci�n principal.

class Postfija_App : public wxApp {
	
	// La propiedad de nuestra aplicaci�n postfija sera la pantalla wxFrame de la aplicaci�n.

	private :
		
		// Pantalla principal.
		
		Postfija_Pantalla * Pantalla_Principal;
	
	// Tenemos los siguientes metodos publicos.
	
	public :
		
		// El metodo OnInit que es donde iniciar� nuestra aplicaci�n.
		
		bool OnInit () override {
			
			// Asignaremos la pantalla inicial creando una nueva instancia de la misma.
			
			Pantalla_Principal = new Postfija_Pantalla ();
			
			// Devolvemos true.
			
			return true;
			
		}
	
};

// Implementaci�n de la app y el Main por parte de wxWidgets.

IMPLEMENT_APP (Postfija_App)

// -----------------------------------------------------------------------------
