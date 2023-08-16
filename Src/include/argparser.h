#ifndef ARGPARSER_H
#define ARGPARSER_H

#include <algorithm>
#include <string_view>
#include <cstdio>

/// Utility functions for console argument parsing
/// from https://stackoverflow.com/questions/865668/parsing-command-line-arguments-in-c

namespace argparser {

	// https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c
	/// Fonction permettant de vérifier si un fichier existe et à la bonne extension
	/// \param filename le nom du fichier à vérifier
	/// \param ext l'extension à vérifier
	/// \return si le fichier est valide selon les conditions données.
	bool checkFileValid(const std::string& filename, const std::string& ext) {
		bool fileExists = false;
		bool validExt = false;
		if (FILE *f = fopen(filename.c_str(), "r")) {
			fclose(f);
			fileExists = true;
		}

		if (filename.substr(filename.find_last_of(".") + 1) == ext) {
			validExt = true;
		}

		return fileExists && validExt;
	}
	/// Récupère le paramètre passé dans les arguments du programmes
	/// Exemple --arg foo -> redonne `foo`
	/// \param begin le début de la chaîne de caractères à rechercher
	/// \param end la fin de la chaîne de caractères à rechercher
	/// \param options l'option recherchée
	/// \return la valeur de l'option recherchée.
	char *getCmdOptions(char **begin, char **end, const std::string& options) {
		char **iterator = std::find(begin, end, options);
		if (iterator != end && ++iterator != end)
			return *iterator;
		return nullptr;
	}

	/// Vérifie qu'un argument est passée dans les arguments du programme
	/// \param begin le début de la chaîne de caractères à rechercher
	/// \param end la fin de la chaîne de caractères à rechercher
	/// \param options l'option recherchée
	/// \return si l'option est présente
	bool cmdOptionsExists(char **begin, char **end, const std::string& options) {
		return std::find(begin, end, options) != end;
	}
}

#endif //ARGPARSER_H
