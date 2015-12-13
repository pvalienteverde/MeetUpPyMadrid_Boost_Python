/*
 * Serie.h
 *
 *  Created on: Feb 21, 2015
 *      Author: Pedro Valiente Verde
 */

#ifndef SERIE_H_
#define SERIE_H_

#include "boost/date_time/gregorian/gregorian.hpp"
#include "boost/date_time/time_zone_base.hpp"
#include "boost/date_time/local_time/local_time.hpp"
#include "boost/iterator/filter_iterator.hpp"

#include "matematicas/constantes.h"

namespace utiles {

class Serie: private std::vector<double> {
	typedef std::vector<double> vector;
public:
	/**
	 * Constructor por defecto
	 */
	Serie();

	/**
	 * Constructor dado los datos
	 *
	 * @param serie
	 * @param fecha_inicio
	 * @param resolucion
	 * @param descripcion
	 */
	Serie(const std::vector<double> &serie,
		  const boost::posix_time::ptime &fecha_inicio,
		  const boost::posix_time::time_duration &resolucion = boost::posix_time::seconds(3600),
		  std::string descripcion = "");

	/**
	 * Devuelve la ultima fecha valida
	 * @return
	 */
	boost::posix_time::ptime UltimaFechaValida() const;

	/**
	 * Primera fecha valida
	 * @return
	 */
	boost::posix_time::ptime PrimeraFecha() const;

	//TODO: Constructor copia
	Serie Copiar() const;

	/**
	 * Devuelve los valores en bruto
	 *
	 * @return
	 */
	const std::vector<double> &GetValores() const;


	/**
	 * Get y set de la descripcion
	 *
	 * @return
	 */
	std::string GetDescripcion() const;
	void SetDescripcion(std::string descripcion);

	/**
	 * Devuelve el valor de la resolucin de la serie
	 *
	 * @return
	 */
	boost::posix_time::time_duration GetResolucion() const;

	/**
	 * Operadores heredados de std::vector
	 *
	 */
	using vector::operator[];
	using vector::begin;
	using vector::end;
	using vector::rbegin;
	using vector::rend;
	using vector::empty;
	using vector::size;
	using vector::back;
	using vector::iterator;
	using vector::reverse_iterator;
	using vector::const_iterator;
	using vector::const_reverse_iterator;
	using vector::at;
	using vector::size_type;
	using vector::insert;

	bool operator==(Serie const& otra_serie) const;

private:
	boost::posix_time::ptime fecha_inicio;
	boost::posix_time::time_duration resolucion;
	std::string descripcion;

};


Serie operator+(const Serie& serie, double valor);
Serie operator-(const Serie& serie, double valor);

std::ostream &operator<<(std::ostream &os, const Serie &serie);

} /* namespace serie */

#endif /* SERIE_H_ */
