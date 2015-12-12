/*
 * ejemplo3.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: Pedro Valiente Verde
 */

#include <string>

#include <boost/python.hpp>
#include <boost/algorithm/string.hpp>

std::string HolaMundo(const std::string &texto = "Hola python madrid") {
	std::string texto_upper = boost::to_upper_copy<std::string>(texto);
	return texto_upper;
}

// Sin la macro, no detecta los argumentos por defecto
BOOST_PYTHON_FUNCTION_OVERLOADS(sobre_carga_modificar_texto, HolaMundo, 0,
		1);

BOOST_PYTHON_MODULE(ejemplo4)
{
	boost::python::def("hola_mundo", HolaMundo,
			sobre_carga_modificar_texto(
					"Retorna el texto en mayusculas\nArgumentos: \n\t texto: texto a mostrar"));
}

