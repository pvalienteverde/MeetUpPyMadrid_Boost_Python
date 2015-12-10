#include "../include/envoltorio_datetime.h"

using namespace boost::python;

namespace convertidores {

PyObject* convertidores::ptime2datetime::convert(
		boost::posix_time::ptime const&t) {
	auto d = t.date();
	auto tod = t.time_of_day();
	auto usec = tod.total_microseconds() % 1000000;
	// Utlizamola api de datetime: https://docs.python.org/2/c-api/datetime.html
	return PyDateTime_FromDateAndTime(d.year(), d.month(), d.day(), tod.hours(),
			tod.minutes(), tod.seconds(), usec);
}

void* datetime2ptime::convertible(PyObject* obj) {
	//std::cout<<"Convertidor datetime2ptime:"<<PyDateTime_Check( obj )<<","<<PyTZInfo_Check(obj )<<std::endl;
	return (PyDateTime_Check( obj ) and !PyTZInfo_Check( obj )) ? obj : nullptr;
	// Si queremos un conversor de string seria: return PyString_Check( obj ) ? obj : nullptr;
}

void datetime2ptime::construct(PyObject* obj,
		converter::rvalue_from_python_stage1_data* data) {

	// Obtain a handle to the memory block that the converter has allocated for the C++ type.
	auto storage = reinterpret_cast<converter::rvalue_from_python_storage<
			boost::posix_time::ptime>*>(data)->storage.bytes;

	// Se puede hacer a lo bruto o por medio de la api de cada objeto, en este ejemplo
	// uilizamos la api de datetime: https://docs.python.org/2/c-api/datetime.html
	boost::gregorian::date date_only(PyDateTime_GET_YEAR(obj),
			PyDateTime_GET_MONTH(obj), PyDateTime_GET_DAY(obj));

	boost::posix_time::time_duration time_of_day(PyDateTime_DATE_GET_HOUR(obj),
			PyDateTime_DATE_GET_MINUTE(obj), PyDateTime_DATE_GET_SECOND(obj));

	time_of_day += boost::posix_time::microsec(
			PyDateTime_DATE_GET_MICROSECOND(obj));

	// si no hubieramos tenido la api, lo tendriamos que realizar: http://stackoverflow.com/questions/15842126/feeding-a-python-list-into-a-function-taking-in-a-vector-with-boost-python/15940413#15940413
	new (storage) boost::posix_time::ptime(date_only, time_of_day);
	data->convertible = storage;
}

/* Convert date to/from python */
PyObject* date_to_python_date::convert(boost::gregorian::date const& date) {
	return PyDate_FromDate((int )date.year(), (int )date.month(),
			(int )date.day());
}

void* date_from_python_date::convertible(PyObject * obj_ptr) {
	if (!PyDate_Check(obj_ptr))
		return 0;
	return obj_ptr;
}

void date_from_python_date::construct(PyObject* obj_ptr,
		boost::python::converter::rvalue_from_python_stage1_data * data) {
	PyDateTime_Date const* pydate = reinterpret_cast<PyDateTime_Date*>(obj_ptr);

	// Create date object
	boost::gregorian::date _date(PyDateTime_GET_YEAR(pydate),
			PyDateTime_GET_MONTH(pydate), PyDateTime_GET_DAY(pydate));

	// Create posix time object
	void* storage = ((boost::python::converter::rvalue_from_python_storage<
			boost::gregorian::date>*) data)->storage.bytes;
	new (storage) boost::gregorian::date(_date);
	data->convertible = storage;
}

long get_usecs(boost::posix_time::time_duration const& d) {
	static long resolution =
			boost::posix_time::time_duration::ticks_per_second();
	long fracsecs = d.fractional_seconds();
	if (resolution > 1000000)
		return fracsecs / (resolution / 1000000);
	else
		return fracsecs * (1000000 / resolution);
}

PyObject* tduration_to_python_delta::convert(
		boost::posix_time::time_duration d) {
	long days = d.hours() / 24;
	if (days < 0)
		days--;
	long seconds = d.total_seconds() - days * (24 * 3600);
	long usecs = get_usecs(d);
	if (days < 0)
		usecs = 1000000 - 1 - usecs;
	return PyDelta_FromDSU(days, seconds, usecs);
}


void* tduration_from_python_delta::convertible(PyObject * obj_ptr) {
	if (!PyDelta_Check(obj_ptr))
		return 0;
	return obj_ptr;
}

void tduration_from_python_delta::construct(PyObject* obj_ptr,
		boost::python::converter::rvalue_from_python_stage1_data * data) {
	PyDateTime_Delta const* pydelta =
			reinterpret_cast<PyDateTime_Delta*>(obj_ptr);

	long days = pydelta->days;
	bool is_negative = (days < 0);
	if (is_negative)
		days = -days;

	boost::posix_time::time_duration duration = boost::posix_time::hours(24)
			* days + boost::posix_time::seconds(pydelta->seconds)
			+ boost::posix_time::microseconds(pydelta->microseconds);
	if (is_negative)
		duration = duration.invert_sign();

	void* storage = ((boost::python::converter::rvalue_from_python_storage<
			boost::posix_time::time_duration>*) data)->storage.bytes;
	new (storage) boost::posix_time::time_duration(duration);
	data->convertible = storage;
}

//TODO NO pasa la zona horaria, por ahora funciona correctamente en UTC
PyObject* convertidores::LocalTime2datetime::convert(
		boost::local_time::local_date_time const&t) {
	auto d = t.date();
	auto tod = t.time_of_day();
	auto usec = tod.total_microseconds() % 1000000;
	// Utlizamola api de datetime: https://docs.python.org/2/c-api/datetime.html
	return PyDateTime_FromDateAndTime(d.year(), d.month(), d.day(), tod.hours(),
			tod.minutes(), tod.seconds(), usec);
}

void* datetime2LocalTime::convertible(PyObject* obj) {
	//std::cout<<"Convertidor datetime2LocalTime:"<<PyDateTime_Check( obj )<<","<<PyTZInfo_Check( obj )<<std::endl;
	return (PyDateTime_Check( obj )) ? obj : nullptr;
	// Si queremos un conversor de string seria: return PyString_Check( obj ) ? obj : nullptr;
}

void datetime2LocalTime::construct(PyObject* obj,
		converter::rvalue_from_python_stage1_data* data) {

	// Obtain a handle to the memory block that the converter has allocated for the C++ type.
	auto storage = reinterpret_cast<converter::rvalue_from_python_storage<
			boost::local_time::local_date_time>*>(data)->storage.bytes;

	// Se puede hacer a lo bruto o por medio de la api de cada objeto, en este ejemplo
	// uilizamos la api de datetime: https://docs.python.org/2/c-api/datetime.html
	boost::gregorian::date date_only(PyDateTime_GET_YEAR(obj),
			PyDateTime_GET_MONTH(obj), PyDateTime_GET_DAY(obj));

	boost::posix_time::time_duration time_of_day(PyDateTime_DATE_GET_HOUR(obj),
			PyDateTime_DATE_GET_MINUTE(obj), PyDateTime_DATE_GET_SECOND(obj));

	time_of_day += boost::posix_time::microsec(
			PyDateTime_DATE_GET_MICROSECOND(obj));

	auto zona_horaria = "UTC";
	boost::local_time::time_zone_ptr tz(
			new boost::local_time::posix_time_zone(zona_horaria));
	boost::posix_time::ptime fecha_sin_zona_horaria(date_only, time_of_day);
	// si no hubieramos tenido la api, lo tendriamos que realizar: http://stackoverflow.com/questions/15842126/feeding-a-python-list-into-a-function-taking-in-a-vector-with-boost-python/15940413#15940413
	new (storage) boost::local_time::local_date_time(fecha_sin_zona_horaria,
			tz);
	data->convertible = storage;
}


void RegistrarDatetime() {
	PyDateTime_IMPORT;

	datetime2ptime();
	to_python_converter<boost::posix_time::ptime, ptime2datetime>();
}

void RegistrarGregorian() {
	PyDateTime_IMPORT;

	date_from_python_date();
	to_python_converter<const boost::gregorian::date,
			date_to_python_date>();

}

void RegistrarDuration() {
	PyDateTime_IMPORT;
	tduration_from_python_delta();

	to_python_converter<const boost::posix_time::time_duration,
			tduration_to_python_delta>();
}

void RegistrarLocalTime() {
	PyDateTime_IMPORT;
	datetime2LocalTime();

	to_python_converter<const boost::local_time::local_date_time,
		LocalTime2datetime>();
}

}

