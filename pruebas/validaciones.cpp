
#include <stdio.h>
#include <stdlib.h>

#include <ctype.h>
#include <string>

bool Five_Chars (const std::string & Cadena) {
	
	printf (" >> Validacion A << \n");
	
	return (Cadena.size () == 5u);
	
}

bool Is_Number (const std::string & Cadena) {
	
	printf (" >> Validacion B << \n");
	
	for (std::string::const_iterator Inicio = Cadena.cbegin () ; Inicio != Cadena.cend () ; ++ Inicio) {
		
		const char Simbolo = (*Inicio);
		
		if (!isdigit (static_cast <int> (Simbolo)) && (Simbolo != '.')) {
			
			return false;
			
		}
		
	}
	
	return true;
	
}

int main () {
	
	const std::string Texto_A ("45.341");
	
	if (Five_Chars (Texto_A) || Is_Number (Texto_A)) {
		
		printf (" >> Cadena Numero de 5 Caracteres : %s \n" , Texto_A.c_str ());
		
	}
	else {
		
		printf (" >> Cadena Texto : %s \n" , Texto_A.c_str ());
		
	}
	
}
