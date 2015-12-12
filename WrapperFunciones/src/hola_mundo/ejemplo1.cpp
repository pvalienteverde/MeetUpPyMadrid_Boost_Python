/*
 * ejemplo1.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: Pedro Valiente Verde
 */

#include <iostream>
#include <string>

#include <boost/python.hpp>

void HolaMundo() {
	std::cout << "Hola Mundo" << std::endl;
}

BOOST_PYTHON_MODULE(ejemplo1)
{
	boost::python::def("hola_mundo", HolaMundo,
			"Funcion que muestra nuestro primer saludo");
}

