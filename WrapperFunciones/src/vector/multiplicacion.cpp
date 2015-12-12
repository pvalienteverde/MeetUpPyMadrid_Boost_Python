/*
 * multiplicacion.cpp
 *
 *  Created on: Dec 8, 2015
 *      Author: Pedro Valiente Verde
 */

#include <vector>
#include <algorithm>
#include "multiplicacion.h"

std::vector<double> Multiplicacion(const std::vector<double> &datos, double factor) {
	std::vector<double> datos_transformados(datos);
	std::transform(datos_transformados.begin(), datos_transformados.end(),
			datos_transformados.begin(),
			[&factor](auto a) {return (a*factor);});
	return datos_transformados;
}
