/*
 * fechas.h
 *
 *  Created on: Feb 22, 2015
 *      Author: Pedro Valiente Verde
 */

#ifndef FECHAS_H_
#define FECHAS_H_

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/time_zone_base.hpp"
#include "boost/date_time/local_time/local_time.hpp"

namespace utiles {
namespace fechas {

boost::local_time::local_date_time ConstruirFecha(int ano, int mes, int dia,
		int hora = 0, int minuto = 0, int segundos = 0,
		std::string zona_horaria = "UTC") {
	boost::local_time::time_zone_ptr tz(
			new boost::local_time::posix_time_zone(zona_horaria));
	boost::posix_time::ptime fecha_sin_zona_horaria(
			boost::gregorian::date(ano, mes, dia),
			boost::posix_time::time_duration(hora, minuto, segundos));
	return boost::local_time::local_date_time(fecha_sin_zona_horaria, tz);
}

boost::posix_time::ptime ConstruirFechaSinZOnaHoraria(int ano, int mes, int dia,
		int hora = 0, int minuto = 0, int segundos = 0) {

	boost::posix_time::ptime fecha_sin_zona_horaria(
			boost::gregorian::date(ano, mes, dia),
			boost::posix_time::time_duration(hora, minuto, segundos));

	return fecha_sin_zona_horaria;
}

}
}

#endif /* FECHAS_H_ */
