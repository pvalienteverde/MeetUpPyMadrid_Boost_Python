/*
 * Serie.cpp
 *
 *  Created on: Feb 21, 2015
 *      Author: pedro
 */

#include "../include/Serie.h"
#include <boost/format.hpp>

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

std::string Serie::GetDescripcion() const{
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

Serie Serie::Copiar() const{
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

std::ostream &operator<<(std::ostream &ss, const Serie &serie) {
	size_t n(5);
	auto tam=serie.size()<n?serie.size()/2:n;


	std::string descripcion_valores("[ ");
	auto lambda=[&descripcion_valores](const auto &valor){descripcion_valores+=boost::str(boost::format("%.2f") % valor)+", ";};

    std::for_each(serie.begin(), serie.begin()+tam,lambda);
    descripcion_valores+="... ";
    std::for_each(serie.end()-tam, serie.end(),lambda);
    descripcion_valores+="]";

	ss << "Valores:       " << descripcion_valores << "\n";
	ss << "Num.Valores:   " << serie.size() << "; ";
	ss << "Fecha Inicial: " << serie.PrimeraFecha() << "; ";
	ss << "Resolucion:    " << serie.GetResolucion() << "\n";
	ss << "Descripcion:   " << serie.GetDescripcion() << "\n";
	return ss;
}

Serie operator+(const Serie& serie, double valor){
	auto serie_mod=serie.Copiar();
	for (auto &valor:serie_mod)
		valor+=valor;
	return serie_mod;
}
Serie operator-(const Serie& serie, double valor){
	return serie+(-1*valor);
}

} /* namespace serie_historica */
