#include <iostream>

#include "include/argparser.h"
#include "include/importer.h"
#include "include/timeline.h"
#include "include/generation.h"

int main(int argc, char **argv) {
	if (argparser::cmdOptionsExists(argv, argv + argc, "-h") ||
	argparser::cmdOptionsExists(argv, argv + argc, "--help")) {
		std::cout << "Generates timeline with specified constraints and an initial state.\n\n"
					 "Usage: setup --state [filename] --constraints [filename] "
					 "--output [filename]\n"
					 "Options:\n"
					 "\t-h, --help                       \t display this help\n"
					 "\t-s, --state [path to file]       \t select the .stat file as the initial state of the application\n"
					 "\t-c, --constraints [path to file] \t select the .constraints as the constraints of the application\n"
					 "\t-o, --output [path to file]      \t name of the output file"
					 "constraints of the application"
					 << std::endl;
		return EXIT_SUCCESS;
	}
	char *initFilename = nullptr;
	char *constrFilename = nullptr;
	char *outputFilename = nullptr;

	if (argparser::cmdOptionsExists(argv, argv + argc, "-s"))
		initFilename = argparser::getCmdOptions(argv, argv + argc, "-s");

	if (argparser::cmdOptionsExists(argv, argv + argc, "--state"))
		initFilename = argparser::getCmdOptions(argv, argv + argc, "--state");

	if (argparser::cmdOptionsExists(argv, argv + argc, "-c"))
		constrFilename = argparser::getCmdOptions(argv, argv + argc, "-c");

	if (argparser::cmdOptionsExists(argv, argv + argc, "--constraints"))
		constrFilename = argparser::getCmdOptions(argv, argv + argc, "--constraints");

	if (argparser::cmdOptionsExists(argv, argv + argc, "-o"))
		outputFilename = argparser::getCmdOptions(argv, argv + argc, "-o");

	if (argparser::cmdOptionsExists(argv, argv + argc, "--output"))
		outputFilename = argparser::getCmdOptions(argv, argv + argc, "--output");

	// todo: search for the first .stat file in the directory.
	if (!initFilename) {
		std::cout << "Missing initial state. See setup --help for more information.\n";
		return EXIT_SUCCESS;
	}

	if (!constrFilename) {
		std::cout << "Missing constraints. See setup --help for more information.\n";
		return EXIT_SUCCESS;
	}

	if (!argparser::checkFileValid(initFilename, "stat")) {
		std::cout << "Invalid initial state, check if the file exists and has the good extension. See setup --help for more information.\n";
		return EXIT_SUCCESS;
	}

	if (!argparser::checkFileValid(constrFilename, "constraints")) {
		std::cout << "Invalid constrains, check if the file exists and has the good extension. See setup --help for more information.\n";
		return EXIT_SUCCESS;
	}

	std::cout << "Decontamination Utility software setup application" << std::endl;

	auto state = importer::basicImport<State>(initFilename);
	auto constraints = importer::basicImport<Constraints>(constrFilename);
	Timeline tl = generation::generateTimeline(state, constraints);
	importer::exportTimeline(tl, outputFilename);
}