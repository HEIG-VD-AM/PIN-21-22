#ifndef UTILITY_H
#define UTILITY_H

#include <cmath>

namespace utility {
	// https://stackoverflow.com/questions/11980292/how-to-wrap-around-a-range
	/// Fonction permettant d'obtenir un angle θ mod 360deg.
	/// \param ang l'angle à replacer dans le bon intervalle
	/// \return un angle dans l'intervalle [-360, 360]
	inline double wrapAngle(double ang) {
		return ang - 360 * floor(ang / 360);
	}
}

#endif //UTILITY_H
