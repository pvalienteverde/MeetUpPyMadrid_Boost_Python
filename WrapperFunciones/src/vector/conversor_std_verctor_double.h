/*
 * conversor_std_vector_double.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: Pedro Valiente Verde
 */

#include <iostream>
#include <boost/python.hpp>
#include "multiplicacion.h"
#include "conversor_std_verctor_double.h"

namespace py = boost::python;

struct ObjetoIterable2Numpy {
	static PyObject* convert(const std::vector<double>& objeto) {

		py::list l;
		for(auto valor:objeto)
			l.append(valor);

		return py::incref<>(py::numeric::array(l).ptr());
	}
};


struct Numpy2ObjetoIterable {

	/**
	 * Constructor, realmente es el que se encarga del registro
	 */
	Numpy2ObjetoIterable() {
		boost::python::converter::registry::push_back(
				&Numpy2ObjetoIterable::convertible,
				&Numpy2ObjetoIterable::construct,
				py::type_id<std::vector<double>>());


	}

	/**
	 * Detecta que el objeto sea iterable
	 *
	 * @param object
	 */
	static void* convertible(PyObject* object) {
		return PyObject_GetIter(object) ? object : NULL;
	}


	/**
	 * Convertidor de PyObject a C++
	 *
	 * @param object:
	 * 	      * 1 requisito: std::vector<double>::value_type debe tener constructor copia
	 * 	      * 2 requisito: std::vector<double> pueda ser construido a partir de dos iteradores
	 *
	 * @param data
	 */
	static void construct(PyObject* object,
			py::converter::rvalue_from_python_stage1_data* data) {

		// Object is a borrowed reference, so create a handle indicting it is
		// borrowed for proper reference counting.
		py::handle<> handle(py::borrowed(object));

		// Obtain a handle to the memory block that the converter has allocated
		// for the C++ type.
		typedef py::converter::rvalue_from_python_storage<std::vector<double>> storage_type;
		void* storage = reinterpret_cast<storage_type*>(data)->storage.bytes;

		typedef py::stl_input_iterator<typename std::vector<double>::value_type> iterator;

		// Allocate the C++ type into the converter's memory block, and assign
		// its handle to the converter's convertible variable.  The C++
		// std::vector<double> is populated by passing the begin and end iterators of
		// the python object to the std::vector<double>'s constructor.
		new (storage) std::vector<double>(iterator(py::object(handle)), // begin
		iterator());                      // end
		data->convertible = storage;
	}
};

void RegistrarObjetosIterables(){
	py::numeric::array::set_module_and_type("numpy", "ndarray");
	py::to_python_converter<std::vector<double> , ObjetoIterable2Numpy>();
	Numpy2ObjetoIterable();

}
