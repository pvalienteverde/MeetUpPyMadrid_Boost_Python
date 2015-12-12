/*
 * ejemplo7.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: Pedro Valiente Verde
 */

#include <iostream>

#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>
#include <boost/python/numeric.hpp>
#include <boost/assign/std/vector.hpp>

#include "multiplicacion.h"

namespace py = boost::python;

py::numeric::array wrapper_multiplicacion(const py::numeric::array& datos, double factor = 1) {
	py::stl_input_iterator<double> begin(datos), end;
	std::vector<double> datos_transformar(begin, end);

	auto nuevos_datos = Multiplicacion(datos_transformar, factor);

	py::list resultado;
	for (auto const &i : nuevos_datos)
		resultado.append(i);

	return py::numeric::array(resultado);
}

BOOST_PYTHON_FUNCTION_OVERLOADS(args_por_defecto_multiplicacion, wrapper_multiplicacion, 1, 2);
BOOST_PYTHON_MODULE(ejemplo7)
{
	py::numeric::array::set_module_and_type("numpy", "ndarray");
	py::def("wrapper_multiplicacion", wrapper_multiplicacion,args_por_defecto_multiplicacion());
}

