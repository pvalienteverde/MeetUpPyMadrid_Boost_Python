/*
 * ejemplo6.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: Pedro Valiente Verde
 */

#include <iostream>

#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>
#include "multiplicacion.h"

namespace py = boost::python;


py::list wrapper_multiplicacion(const py::list& datos, double factor) {
	py::stl_input_iterator<double> begin(datos), end;
	std::vector<double> datos_transformar(begin, end);

	auto nuevos_datos = Multiplicacion(datos_transformar, factor);

	py::list resultado;
	for (auto const &i : nuevos_datos)
		resultado.append(i);

	return resultado;
}

BOOST_PYTHON_MODULE(ejemplo6)
{
	py::def("wrapper_multiplicacion", wrapper_multiplicacion,"wrapper de la funcion multiplicacion, a listas");
}

