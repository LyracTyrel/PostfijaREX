
// -----------------------------------------------------------------------------

// Inicio de la aplicación. Postfija_REX.
/// @author Menightmar
/// @date 02-03-2019
/// @brief Programa para traducir de notación infija a postfija y evaluar expresiones matemáticas.

// Anexaremos las siguientes cabeceras principales.

#include <stdio.h>
#include <stdlib.h>

// -----------------------------------------------------------------------------

// Tenemos la biblioteca de wxWidgets , incluiremos la cabecera general.

#include <wx/wx.h>

// Incluiremos ahora nuestros modulo de la pantalla principal.

#include <Pantalla_Principal.h>

// -----------------------------------------------------------------------------

// Lo primero será crear una clase que derive de wxApp para la aplicación principal.

class Postfija_App : public wxApp {
	
	// La propiedad de nuestra aplicación postfija sera la pantalla wxFrame de la aplicación.

	private :
		
		// Pantalla principal.
		
		Postfija_Pantalla * Pantalla_Principal;
	
	// Tenemos los siguientes metodos publicos.
	
	public :
		
		// El metodo OnInit que es donde iniciará nuestra aplicación.
		
		bool OnInit () override {
			
			// Asignaremos la pantalla inicial creando una nueva instancia de la misma.
			
			Pantalla_Principal = new Postfija_Pantalla ();
			
			// Devolvemos true.
			
			return true;
			
		}
	
};

// Implementación de la app y el Main por parte de wxWidgets.

IMPLEMENT_APP (Postfija_App)

// -----------------------------------------------------------------------------
