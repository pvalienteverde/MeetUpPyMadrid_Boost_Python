/*
 * ejemplo8.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: Pedro Valiente Verde
 */

#include <iostream>
#include <boost/python.hpp>
#include "multiplicacion.h"
#include "../../../WrapperClases/convertidores/include/envoltorio_objetos_iterables.h"

namespace py = boost::python;

BOOST_PYTHON_FUNCTION_OVERLOADS(args_por_defecto_multiplicacion, multiplicacion, 1, 2);
BOOST_PYTHON_MODULE(ejemplo8){
	convertidores::RegistrarObjetosIterables<std::vector<double>>();
	py::def("wrapper_multiplicacion", Multiplicacion);
}
