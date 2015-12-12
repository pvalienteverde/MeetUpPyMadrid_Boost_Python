/*
 * envoltorio_datetime.h
 *
 *  Created on: May 9, 2015
 *      Author: Pedro Valiente Verde
 */

#ifndef INCLUDE_ENVOLTORIO_DATETIME_H_
#define INCLUDE_ENVOLTORIO_DATETIME_H_

#include <boost/python.hpp>
#include <boost/date_time/posix_time/posix_time_types.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <datetime.h>
#include "boost/date_time/time_zone_base.hpp"
#include "boost/date_time/local_time/local_time.hpp"

using namespace boost::python;

//http://sysmagazine.com/posts/168827/
//https://github.com/jktjkt/deska/blob/master/src/deska/LowLevelPyDeska/DateTimeConversions.cpp


namespace convertidores {

/**
 * Clase Publica Conversor de un objeto c++ to python
 * 		- convert, obligatorio, se especifica la conversrion
 *
 * Para mas ayuda: http://www.boost.org/doc/libs/1_37_0/libs/python/doc/v2/to_python_converter.html
 */
struct ptime2datetime {
	/**
	 * Se tiene que crear en cualquier conversor de c++ to python, el metodo convert que devuelve un miembro estatico boost::python::PyObject
	 *
	 * @param
	 * @return
	 */
	static PyObject* convert(boost::posix_time::ptime const&);
};

/**
 * Conversor de py2c++, tiene que tener 3 metodos:
 * 		- Constructor de la clase que unicamente añade el registro del conversor
 * 		- convertible: Es la clave, asi la boost sabe que convsersor se utiliza para cada tipo python: PyDateTime_Check, PyString_Check, ...
 * 		- construct:
 *
 * Para mas ayuda:
 * 		- http://stackoverflow.com/questions/16105539/boost-python-custom-converter
 * 		- https://misspent.wordpress.com/2009/09/27/how-to-write-boost-python-converters/
 * 		- http://stackoverflow.com/questions/15842126/feeding-a-python-list-into-a-function-taking-in-a-vector-with-boost-python/15940413#15940413
 */
struct datetime2ptime {
	/**
	 * Registro del conversor
	 */
	datetime2ptime() {
		converter::registry::push_back(convertible, construct,
				type_id<boost::posix_time::ptime>());
	}

	/**
	 * Decide si la clase encargada de convertir el tipo
	 *
	 * @param
	 */
	static void* convertible(PyObject*);

	/**
	 * Directivas de como realizarlo
	 *
	 * @param
	 * @param
	 */
	static void construct(PyObject*,
			converter::rvalue_from_python_stage1_data*);
};

/* Convert date to/from python */
struct date_to_python_date {
	static PyObject* convert(boost::gregorian::date const& date);
};

struct date_from_python_date {
	date_from_python_date() {
		boost::python::converter::registry::push_back(&convertible, &construct,
				boost::python::type_id<boost::gregorian::date>());
	}

	static void* convertible(PyObject * obj_ptr);

	static void construct(PyObject* obj_ptr,
			boost::python::converter::rvalue_from_python_stage1_data * data);
};


long get_usecs(boost::posix_time::time_duration const& d);

/* Convert time_duration to/from python */
struct tduration_to_python_delta {
	static PyObject* convert(boost::posix_time::time_duration d);
};

struct tduration_from_python_delta {
	tduration_from_python_delta() {
		boost::python::converter::registry::push_back(&convertible, &construct,
				boost::python::type_id<boost::posix_time::time_duration>());
	}

	static void* convertible(PyObject * obj_ptr);

	static void construct(PyObject* obj_ptr,
			boost::python::converter::rvalue_from_python_stage1_data * data);
};

struct LocalTime2datetime {
	/**
	 *
	 * @param
	 * @return
	 */
	static PyObject* convert(boost::local_time::local_date_time const&);
};


struct datetime2LocalTime {
	/**
	 * Registro del conversor
	 */
	datetime2LocalTime() {
		converter::registry::push_back(convertible, construct,
				type_id<boost::local_time::local_date_time>());
	}

	/**
	 * Decide si la clase encargada de convertir el tipo
	 *
	 * @param
	 */
	static void* convertible(PyObject*);

	/**
	 * Directivas de como realizarlo
	 *
	 * @param
	 * @param
	 */
	static void construct(PyObject*,
			converter::rvalue_from_python_stage1_data*);
};

/**
 * Inicializa los convertidores
 */

// Para tener ayuda de como construir las fechas http://pymotw.com/2/datetime/
void RegistrarDatetime();// datetime.datetime
void RegistrarGregorian();// datetime.date
void RegistrarDuration();// datetime.timedelta
void RegistrarLocalTime();

}

#endif /* INCLUDE_DATETIME_H_ */
