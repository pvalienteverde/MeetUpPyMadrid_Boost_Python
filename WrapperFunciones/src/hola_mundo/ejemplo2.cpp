/*
 * ejemplo2.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: Pedro Valiente Verde
 */

#include <iostream>
#include <string>

#include <boost/python.hpp>

void hola_mundo(const std::string &texto = "Hola python madrid") {
	std::cout << texto << std::endl;
}

BOOST_PYTHON_MODULE(ejemplo2)
{
	boost::python::def("hola_mundo", hola_mundo,
			"Muestra por la pantalla el texto introducido\nArgumentos: \n\t texto: texto a mostrar");
}

