/*
 * convolucionar.cpp
 *
 *  Created on: Nov 4, 2015
 *      Author: pedro
 */

#include "../../include/matematicas/convolucionar.h"
#include <boost/python.hpp>
#include <boost/python/implicit.hpp>
#include <include/matematicas/convolucionar.h>

namespace py = boost::python;

void wrapper_utiles::matematicas::exportar_convolucionar(){
	py::object modulo_convolucionar(py::handle<>(py::borrowed(PyImport_AddModule("wrapper_utiles.matematicas"))));
	py::scope().attr("matematicas") = modulo_convolucionar;
	py::scope util_scope = modulo_convolucionar;

	py::def("convolucionar", &utiles::matematicas::ConvolucionarSerie,
    			"Convolucionar la serie de datos, primer elemento con el filtro, segundo elemento");

    py::class_<utiles::matematicas::FiltrosDaubechies>("FiltrosDaubechies",
    			py::init<int>(( py::arg("coeficiente")), "Constructor los coeficientes de Daubechies") )
    			.def("getHiD",&utiles::matematicas::FiltrosDaubechies::getHiD,py::return_value_policy<py::copy_const_reference>())
    			.def("getHiR",&utiles::matematicas::FiltrosDaubechies::getHiR,py::return_value_policy<py::copy_const_reference>())
    			.def("getLoD",&utiles::matematicas::FiltrosDaubechies::getLoD,py::return_value_policy<py::copy_const_reference>())
    			.def("getLoR", &utiles::matematicas::FiltrosDaubechies::getLoR,py::return_value_policy<py::copy_const_reference>());


}
