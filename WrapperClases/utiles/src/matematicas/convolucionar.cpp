#include <algorithm>
#include <functional>
#include "../../include/matematicas/convolucionar.h"
#include <cmath>
#include <cfloat>


utiles::Serie utiles::matematicas::ConvolucionarSerie(const utiles::Serie &datos,
		const std::vector<double> &filtro) {
	auto valores = datos.GetValores();
	auto valores_convolucionados = utiles::matematicas::Convolucionar(valores,
			filtro);
	return utiles::Serie(valores_convolucionados, datos.PrimeraFecha());

}

const std::map<int, std::vector<double>> utiles::matematicas::FiltrosDaubechies::daubechies_coeficientes =
		{ { 1, { 0.5, 0.5 } }, { 2, { 0.34150635094622, 0.59150635094587,
				0.15849364905378, -0.09150635094587 } }, { 3, {
				0.23523360389270, 0.57055845791731, 0.32518250026371,
				-0.09546720778426, -0.06041610415535, 0.02490874986589 } }, { 4,
				{ 0.16290171402562, 0.50547285754565, 0.44610006912319,
						-0.01978751311791, -0.13225358368437, 0.02180815023739,
						0.02325180053556, -0.00749349466513 } }, { 5, {
				0.11320949129173, 0.42697177135271, 0.51216347213016,
				0.09788348067375, -0.17132835769133, -0.02280056594205,
				0.05485132932108, -0.00441340005433, -0.00889593505093,
				0.00235871396920 } }, };

utiles::matematicas::FiltrosDaubechies::FiltrosDaubechies(int numero_daubechies) :
		Lo_D(std::vector<double>(numero_daubechies * 2, 0)), Hi_D(
				std::vector<double>(numero_daubechies * 2, 0)), Lo_R(
				std::vector<double>(numero_daubechies * 2, 0)), Hi_R(
				std::vector<double>(numero_daubechies * 2, 0)), coeficientes(
				utiles::matematicas::FiltrosDaubechies::daubechies_coeficientes.at(
						numero_daubechies)) {

	double sumatorio = std::accumulate(coeficientes.begin(), coeficientes.end(),
			0.0);
	std::for_each(coeficientes.begin(), coeficientes.end(),
			[&sumatorio](double &valor) {valor/=sumatorio;});

	std::copy(coeficientes.begin(), coeficientes.end(), Lo_R.begin());
	std::for_each(Lo_R.begin(), Lo_R.end(),
			[](double &peso) {peso=std::sqrt(2)*peso;});

	std::copy(Lo_R.rbegin(), Lo_R.rend(), Hi_R.begin());
	for (auto it_Hi_R = Hi_R.begin(); it_Hi_R < Hi_R.end(); it_Hi_R += 2) {
		*it_Hi_R = -1 * (*it_Hi_R);
	}

	std::copy(Hi_R.rbegin(), Hi_R.rend(), Hi_D.begin());
	std::copy(Lo_R.rbegin(), Lo_R.rend(), Lo_D.begin());

}
;

const std::vector<double>& utiles::matematicas::FiltrosDaubechies::getHiD() const {
	return Hi_D;
}

const std::vector<double>& utiles::matematicas::FiltrosDaubechies::getHiR() const {
	return Hi_R;
}

const std::vector<double>& utiles::matematicas::FiltrosDaubechies::getLoD() const {
	return Lo_D;
}

const std::vector<double>& utiles::matematicas::FiltrosDaubechies::getLoR() const {
	return Lo_R;
}

