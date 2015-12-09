/*
 * ejemplo8.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: Pedro Valiente Verde
 */

#include <iostream>
#include <string>

#include <boost/python.hpp>
#include "boost/python/stl_iterator.hpp"
#include "boost/python/numeric.hpp"

#include <boost/assign/std/vector.hpp>

using namespace boost::assign;
namespace py = boost::python;

std::vector<double> multiplicacion(const std::vector<double> &datos,
		double factor = 1) {
	std::vector<double> datos_transformados(datos);

	std::transform(datos_transformados.begin(), datos_transformados.end(),
			datos_transformados.begin(),
			[&factor](auto a) {return (a*factor);});

	return datos_transformados;
}

void test_multiplicacion() {
	std::vector<double> datos;
	datos += 1.0, 2.0, 3.0, 4.0;
	double factor(2);

	auto nuevos_datos = multiplicacion(datos, factor);

	std::cout << "Datos originales:" << std::endl;
	std::copy(datos.begin(), datos.end(),
			std::ostream_iterator<double>(std::cout, " "));
	std::cout << std::endl
			<< "Datos transformados, multiplicados por el factor: " << factor
			<< std::endl;
	std::copy(nuevos_datos.begin(), nuevos_datos.end(),
			std::ostream_iterator<double>(std::cout, " "));
}

template<class T>
struct ObjetoIterable2Numpy {
	static PyObject* convert(const T& objeto) {

		boost::python::list* l = new boost::python::list();
		for(auto valor:objeto)
			(*l).append(valor);

		return l->ptr();
	}
};

struct Numpy2ObjetoIterable {

	template<typename Container>
	Numpy2ObjetoIterable&
	from_python() {
		boost::python::converter::registry::push_back(
				&Numpy2ObjetoIterable::convertible,
				&Numpy2ObjetoIterable::construct<Container>,
				boost::python::type_id<Container>());

		return *this;
	}

	static void* convertible(PyObject* object) {
		return PyObject_GetIter(object) ? object : NULL;
	}


	template<typename Container>
	static void construct(PyObject* object,
			boost::python::converter::rvalue_from_python_stage1_data* data) {

		// referencia compartida
		py::handle<> handle(py::borrowed(object));

		// Obtiene la cabecera del bloque de memoria
		typedef py::converter::rvalue_from_python_storage<Container> storage_type;
		void* storage = reinterpret_cast<storage_type*>(data)->storage.bytes;

		//      py::stl_input_iterator<double> begin(datos), end;
		typedef py::stl_input_iterator<typename Container::value_type> iterator;

		//
		new (storage) Container(iterator(py::object(handle)), iterator());
		data->convertible = storage;
	}
};

template <class T>
void RegistroObjetosIterables(){
	py::to_python_converter<T , ObjetoIterable2Numpy<T > >();
	Numpy2ObjetoIterable().from_python<T>();

}

BOOST_PYTHON_MODULE(ejemplo8)
{

	// Asocicacion manual
	RegistroObjetosIterables<std::vector<double> >();

	py::def("test_multiplicacion", test_multiplicacion);
	py::def("multiplicacion", multiplicacion,
			"wrapper de la funcion multiplicacion");





}

