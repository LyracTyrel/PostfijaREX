
# Archivo cmake para programa : Evaluador de Notación Postfija.

# Primero daremos la versión de nuestro cmake a utilizar como minimo.

cmake_minimum_required (VERSION 3.2.3)

# Crearemos el proyecto.

project (POSTFIJA_REX)

# El nombre del programa sera : 

set (APP_NAME		"Postfija_REX")

# Ahora pondremos los directorios para los elementos del programa.

set (DIR_SOURCES 	"${CMAKE_SOURCE_DIR}/sources")
set (DIR_INCLUDES 	"${CMAKE_SOURCE_DIR}/include")
set (DIR_GRAPHICS	"${CMAKE_SOURCE_DIR}/graphics")

# ------------------------------------------------------------------------------

# -------------------------  Proyecto Fuentes  ---------------------------------

# Lista de todos los archivos fuente en orden de dependencia.

set (PROGRAM_SOURCES
	"${DIR_SOURCES}/Main.cpp"
	"${DIR_SOURCES}/Pantalla_Principal.cpp"
	"${DIR_SOURCES}/Algoritmo_Postfija.cpp"
	"${DIR_GRAPHICS}/Resources.rc"
)

# ------------------------------ wxWidgets  ------------------------------------

# Incluiremos los elementos de wxWidgets para utilizar los graficos y componentes GUI (core , base).

find_package (wxWidgets REQUIRED COMPONENTS core base)

# Una vez encontrado el paquete procedemos a anexarlo al proyecto.

if (wxWidgets_FOUND)

	# Anexamos los directorios include a utilizar para esta biblioteca.
	
	include_directories ("${wxWidgets_INCLUDE_DIRS}")
	
	# Anexaremos la lista de dependencias a enlazar para la salida de la aplicación.
	
	link_libraries (${wxWidgets_LIBRARIES})

endif ()

# -------------------------------  Base  ---------------------------------------

# Anexaremos la lista de directorios para includes de la aplicación.

include_directories ("${DIR_INCLUDES}")

# Anexaremos las bibliotecas de dependencia base por defecto para el programa.

link_libraries (
	-lkernel32 -luser32 -lgdi32 -lcomdlg32 -lwinspool -lcomctl32 -lwinmm -lshell32 -lshlwapi -lsetupapi -lole32
	-liconv -lWs2_32 -lSecur32 -lws2_32 -loleaut32 -luuid -loleacc -lrpcrt4 -ladvapi32 -lversion -luxtheme
)

# ------------------------------------------------------------------------------

# --------------------------  Proyecto Output  ---------------------------------

# El ejecutable de salida será el siguiente.

add_executable ("${APP_NAME}" ${PROGRAM_SOURCES})

# Colocaremos la flag mwindows en el enlazador.

set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS}")

# ------------------------------------------------------------------------------

# Configuraciones adicionales de cmake para el compilador.

if (NOT DEFINED POSTFIJA_MAKE_PROGRAM)
	
	# Configuraciones predeterminadas para el compilador.
	
	set (CMAKE_CXX_FLAGS "-std=c++11 -m64 -O2 -w -static-libgcc -static-libstdc++")
	
endif ()

# Ponemos el señalador de que ya fue procesado.

set (POSTFIJA_MAKE_PROGRAM TRUE CACHE INTERNAL "Procesado" FORCE)

# ------------------------------------------------------------------------------
