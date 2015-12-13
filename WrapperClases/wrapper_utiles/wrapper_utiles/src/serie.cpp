/*
 * Serie.cpp
 *
 *  Created on: Dec 9, 2015
 *      Author: pedro
 */

#include "../include/serie.h"

#include <boost/python.hpp>
#include <boost/python/implicit.hpp>
#include <boost/python/slice.hpp>

#include <include/Serie.h>

#include <numeric>
#include <sstream>

namespace py = boost::python;
namespace wrapper_utiles {

double GetItemSerie(const utiles::Serie& self, int index) {
	if (index < 0)
		index += static_cast<int>(self.size());

	if (index < 0 || static_cast<int>(self.size()) <= index)
		throw std::out_of_range("Fuera de rango");

	return self[index];
}

/// Para mas ayuda sobre Slice: http://www.boost.org/doc/libs/1_35_0/libs/python/doc/v2/slice.html
py::numeric::array GetItemSliceSerie(const utiles::Serie& self,
		py::slice slice) {
	py::list resultado;
	py::slice::range<std::vector<double>::const_iterator> rango;
	try {
		rango = slice.get_indices(self.begin(), self.end());
	} catch (std::invalid_argument&) {
		return py::numeric::array(resultado);
	}

	for (; rango.start != rango.stop; std::advance(rango.start, rango.step)) {
		resultado.append(*rango.start);
	}
	resultado.append(*rango.start); //Ultimo elemento
	return py::numeric::array(resultado);
}




void exportar_serie() {
	py::object modulo_serie(py::handle<>(py::borrowed(PyImport_AddModule("serie"))));
	py::scope().attr("serie") = modulo_serie;
	py::scope util_scope = modulo_serie;

	py::class_<utiles::Serie>("Serie",
			py::init<std::vector<double>,
			         boost::posix_time::ptime const&,
					 py::optional<
					              boost::posix_time::time_duration,
								  std::string>
	                             >
	                 (( py::arg("datos"),
	                    py::arg("fecha_inicio"),
						py::arg("resolucion")="3600",
						py::arg("descripcion")=""
					  ), "Constructor de la serie") )
			.def("ultima_fecha_valida",&utiles::Serie::UltimaFechaValida)
			.def("primera_fecha",&utiles::Serie::PrimeraFecha)
			.def_readonly("resolucion",&utiles::Serie::GetResolucion)
			.add_property("descripcion",&utiles::Serie::GetDescripcion,&utiles::Serie::SetDescripcion)
			.def("valores", &utiles::Serie::GetValores,py::return_value_policy<py::copy_const_reference>())
			.def(str(py::self))
			.def(repr(py::self))
			.def(py::self + double())
			.def(py::self - double())
			.def("__iter__",py::iterator<utiles::Serie>())
			.def("__getitem__",&GetItemSerie)
			.def("__getitem__",&GetItemSliceSerie);




}

} /* namespace wrapper_utiles */
