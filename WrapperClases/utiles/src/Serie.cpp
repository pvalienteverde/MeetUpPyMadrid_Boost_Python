/*
 * Serie.cpp
 *
 *  Created on: Feb 21, 2015
 *      Author: pedro
 */

#include "../include/Serie.h"

namespace utiles {

Serie::Serie(const std::vector<double> &serie,
		    const boost::posix_time::ptime &fecha_inicio,
		    const boost::posix_time::time_duration &resolucion ,
		    std::string descripcion ) :
		vector(serie), fecha_inicio(fecha_inicio),resolucion(resolucion), descripcion(descripcion) {

}

Serie::Serie() :
		fecha_inicio(boost::local_time::not_a_date_time),resolucion( boost::posix_time::seconds(3600)) {

}

std::string Serie::GetDescripcion() {
	return this->descripcion;
}

const std::vector<double>  &Serie::GetValores() const{
	return *this;
}

void Serie::SetDescripcion(std::string descripcion) {
	this->descripcion = descripcion;
}

boost::posix_time::time_duration Serie::GetResolucion() const  {
	return this->resolucion;
}

bool Serie::operator==(Serie const& otra_serie) const {
	bool iguales = false;
	if (otra_serie.UltimaFechaValida() == this->UltimaFechaValida()
			and otra_serie.size() == this->size())
		iguales = true;
	return iguales;
}

Serie Serie::Copiar() {
	return Serie(*this,this->fecha_inicio,this->resolucion,this->descripcion);
}

boost::posix_time::ptime  Serie::PrimeraFecha() const{
	return this->fecha_inicio;
}
boost::posix_time::ptime Serie::UltimaFechaValida() const {
	auto ultima_fecha_valida = boost::posix_time::ptime(
			boost::local_time::not_a_date_time);
	auto it = std::find_if(this->rbegin(), this->rend(), [](double valor) {
		return !std::isnan(valor);
	});
	if (it != this->rend()) {
		auto distancia_horaria = std::distance(++it, this->rend());
		return fecha_inicio + boost::posix_time::hours(distancia_horaria);
	} else {
		return fecha_inicio + boost::posix_time::hours(this->size() - 1);
	}

	return ultima_fecha_valida;
}

} /* namespace serie_historica */
