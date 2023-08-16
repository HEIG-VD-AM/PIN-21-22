#ifndef IMPORTER_H
#define IMPORTER_H

#include <iostream>
#include <string>
#include <fstream>
#include "../thirdparty/nlohmann.h"

#include "timeline.h"

namespace importer {
	/// Fonction d'importation JSON basique
	/// \tparam T le type de l'objet qui doit être retourné
	/// \param filename le chemin vers le fichier
	/// \return l'objet de type T converti du JSON
	template<typename T>
	T basicImport(const std::string& filename) {
		using json = nlohmann::json;
		// we assume the file has been validated.
		std::ifstream ifs;
		ifs.open(filename);
		if (!ifs.good()) {
			std::cout << "Failed to open file: " << filename << std::endl;
			return T{};
		}
		json data = json::parse(ifs);
		return data.get<T>();
	}

	/// Fonction d'exportation de timeline
	/// \param timeline la timeline à exporter
	/// \param filename le chemin vers le fichier où doit être exportée la timeline.
	void exportTimeline(const Timeline& timeline, const std::string& filename) {
		using nlohmann::json;
		json tl = timeline;
		std::string tlStr = tl.dump();
		std::ofstream ofs;
		ofs.open(filename);
		if (!ofs.good()) {
			std::cout << "Couldn't write to file: " << filename << std::endl;
			return;
		}
		ofs << tlStr;
		std::cout << "Saved timeline to " << filename;
	}
}

#endif //IMPORTER_H
