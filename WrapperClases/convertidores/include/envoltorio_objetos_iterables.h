/*
 * envoltorio_objetos_iterables.h
 *
 *  Created on: May 10, 2015
 *      Author: pedro
 */

#ifndef SCR_ENVOLTORIO_OBJETOS_ITERABLES_H_
#define SCR_ENVOLTORIO_OBJETOS_ITERABLES_H_

#include <iostream>
#include <list>
#include <vector>
#include <boost/python.hpp>
#include <boost/python/stl_iterator.hpp>

/// Esta sacado de: http://stackoverflow.com/questions/15842126/feeding-a-python-list-into-a-function-taking-in-a-vector-with-boost-python/15940413#15940413

namespace py = boost::python;

namespace convertidores {

template<class T>
struct ObjetoIterable2Numpy {
	static PyObject* convert(const T& objeto) {

		py::list* l = new py::list();
		for(auto valor:objeto)
			(*l).append(valor);

		return l->ptr();
	}
};


template<typename Container>
struct Numpy2ObjetoIterable {

	/**
	 * Constructor, realmente es el que se encarga del registro
	 */
	Numpy2ObjetoIterable() {
		boost::python::converter::registry::push_back(
				&Numpy2ObjetoIterable::convertible,
				&Numpy2ObjetoIterable::construct,
				py::type_id<Container>());


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
	 * 	      * 1 requisito: Container::value_type debe tener constructor copia
	 * 	      * 2 requisito: Container pueda ser construido a partir de dos iteradores
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
		typedef py::converter::rvalue_from_python_storage<Container> storage_type;
		void* storage = reinterpret_cast<storage_type*>(data)->storage.bytes;

		typedef py::stl_input_iterator<typename Container::value_type> iterator;

		// Allocate the C++ type into the converter's memory block, and assign
		// its handle to the converter's convertible variable.  The C++
		// container is populated by passing the begin and end iterators of
		// the python object to the container's constructor.
		new (storage) Container(iterator(py::object(handle)), // begin
		iterator());                      // end
		data->convertible = storage;
	}
};

template <class T>
void RegistrarObjetosIterables(){

	py::numeric::array::set_module_and_type("numpy", "ndarray");
	py::to_python_converter<T , ObjetoIterable2Numpy<T > >();
	convertidores::Numpy2ObjetoIterable<T>();

}

} /* namespace conversores */

#endif /* SCR_ENVOLTORIO_OBJETOS_ITERABLES_H_ */
