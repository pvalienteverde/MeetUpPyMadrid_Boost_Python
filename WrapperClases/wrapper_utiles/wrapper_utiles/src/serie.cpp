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

namespace py = boost::python;
namespace wrapper_utiles {

double GetItemSerie(const utiles::Serie& self, int index) {
	if (index < 0)
		index += static_cast<int>(self.size());

	if (index < 0 || static_cast<int>(self.size()) <= index)
		throw std::out_of_range("Fuera de rango");

	return self[index];
}

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
			py::init<std::vector<double>,boost::posix_time::ptime const&,py::optional<boost::posix_time::time_duration,std::string>>
	                 (( py::arg("datos"),
	                    py::arg("fecha_inicio"),
						py::arg("resolucion")="3600",
						py::arg("descripcion")=""
					  ), "Constructor de la serie") )
			.def("ultima_fecha_valida",&utiles::Serie::UltimaFechaValida) // boost::posix_time::ptime UltimaFechaValida() const;
			.def("primera_fecha",&utiles::Serie::PrimeraFecha) // boost::posix_time::ptime PrimeraFecha() const;
			.def_readonly("resolucion",&utiles::Serie::GetResolucion) // boost::posix_time::time_duration GetResolucion() const;
			.add_property("descripcion",&utiles::Serie::GetDescripcion,&utiles::Serie::SetDescripcion) // std::string GetDescripcion() const, void SetDescripcion(std::string descripcion);
			.def("valores", &utiles::Serie::GetValores,py::return_value_policy<py::copy_const_reference>()) //const std::vector<double> &GetValores() const;
			.def("copiar", &utiles::Serie::Copiar) //Serie &Copiar() const;
			.def(str(py::self))  // std::ostream &operator<<(std::ostream &os, const Serie &serie);
			.def(repr(py::self)) // std::ostream &operator<<(std::ostream &os, const Serie &serie);
			.def(py::self + double()) // Serie operator+(const Serie& serie, double valor);
			.def(py::self - double()) // Serie operator-(const Serie& serie, double valor);
			.def("__eq__",&utiles::Serie::operator==) // bool operator==(Serie const& otra_serie) const;
			.def("__iter__",py::iterator<utiles::Serie>()) // using vector::iterator;
			.def("__getitem__",&GetItemSerie)       // using vector::operator[];
			.def("__getitem__",&GetItemSliceSerie); // using vector::begin; using vector::end;
}

} /* namespace wrapper_utiles */
