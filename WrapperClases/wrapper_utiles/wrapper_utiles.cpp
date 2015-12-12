#include <iostream>
#include <boost/python.hpp>
#include "include/envoltorio_datetime.h"
#include "include/envoltorio_objetos_iterables.h"

#include "include/matematicas/convolucionar.h"
#include "include/serie.h"

BOOST_PYTHON_MODULE(wrapper_utiles)
{

	boost::python::object package = boost::python::scope();
	package.attr("__path__") = "wrapper_utiles";

	convertidores::RegistrarDatetime();
	convertidores::RegistrarLocalTime();
	convertidores::RegistrarDuration();
	convertidores::RegistrarObjetosIterables<std::vector<double>>();

	wrapper_utiles::matematicas::exportar_convolucionar();
	wrapper_utiles::exportar_serie();

}

