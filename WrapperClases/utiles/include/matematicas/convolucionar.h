/*
 * convolucionar.h
 *
 *  Created on: Nov 3, 2015
 *      Author: Pedro Valiente Verde
 */

#ifndef INCLUDE_MATEMATICAS_CONVOLUCIONAR_H_
#define INCLUDE_MATEMATICAS_CONVOLUCIONAR_H_

#include <algorithm>
#include <functional>
#include <map>
#include "../Serie.h"
#include <boost/gil/extension/dynamic_image/algorithm.hpp>

//#include <experimental/algorithm>

namespace utiles {
namespace matematicas {


/**
 * Convolucion 1D, tipo de convolucion: same
 *
 * @param datos Datos a convolucionar
 * @param filtro Filtro
 * @return
 */
template <typename T>
T Convolucionar(const T &datos, const std::vector<double> &filtro) {
	// Se crean los ceros por delante y atras
	auto tam_real = filtro.size() - 1;
	T vector_transformado(tam_real,0);
	vector_transformado.reserve(datos.size()+tam_real*2);

	vector_transformado.insert(vector_transformado.begin()+tam_real, datos.begin(),
			datos.end());

	T fin_ceros(tam_real,0);
	vector_transformado.insert(vector_transformado.end(),fin_ceros.begin(),fin_ceros.end());

	for (auto it_vector_transformacion = vector_transformado.begin();
			it_vector_transformacion < vector_transformado.end() - tam_real;
			it_vector_transformacion++) {
		*it_vector_transformacion = std::inner_product(filtro.rbegin(),
				filtro.rend(), it_vector_transformacion, 0.0);
	}
	int distancia=std::distance(vector_transformado.begin(),vector_transformado.end() -filtro.size())-datos.size();
	int der=distancia/2;
	int izq=distancia-der;


	//std::cout<<"Distncia: "<<distancia<<", izq: "<<izq<<", der: "<<der<<std::endl;
	T vector_transformado_valid(
			std::make_move_iterator(vector_transformado.begin()+izq),
			std::make_move_iterator(vector_transformado.end() -filtro.size()-der));
	return std::move(vector_transformado_valid);
}

/**
 * Especializacion del template de convolucion
 *
 * @param datos
 * @param filtro
 * @return
 */
utiles::Serie ConvolucionarSerie(const utiles::Serie &datos,
		const std::vector<double> &filtro);

/**
 * Devuelve los coeficientes de daubechies
 *
 * https://en.wikipedia.org/wiki/Daubechies_wavelet
 * http://es.mathworks.com/help/wavelet/ref/orthfilt.html
 *
 */
class FiltrosDaubechies {
public:
	/**
	 * Constructor,
	 *
	 * @param numero_daubechies Orden de los coeficientes de daubechies
	 */
	FiltrosDaubechies(int numero_daubechies);

	/**
	 * Devuelve los coeficientes Reconstruccion Paso Alto
	 *
	 * @return
	 */
	const std::vector<double>& getHiD() const;

	/**
	 * Devuelve los coeficientes Descomposicion Paso Alto
	 *
	 * @return
	 */
	const std::vector<double>& getHiR() const;

	/**
	 * Devuelve los coeficientes Descomposicion Paso Bajo
	 *
	 * @return
	 */
	const std::vector<double>& getLoD() const;

	/**
	 * Devuelve los coeficientes Reconstruccion Paso Bajo
	 *
	 * @return
	 */
	const std::vector<double>& getLoR() const;

private:
	std::vector<double> Lo_D, Hi_D, Lo_R, Hi_R;
	std::vector<double> coeficientes;
	static const std::map<int, std::vector<double>> daubechies_coeficientes;
};

}
}

#endif /* INCLUDE_MATEMATICAS_CONVOLUCIONAR_H_ */
