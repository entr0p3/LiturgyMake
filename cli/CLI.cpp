#include "CLI.h"

#include "../build/Builder.h"
#include "../project/Project.h"

#include <iostream>
#include <string>

namespace CLI {

    void printHelp() {
        std::cout
            << "\n"
            << "  LiturgyMake - C++ Project Manager\n"
            << "\n"
            << "  Usage:\n"
            << "    lmake <command>\n"
            << "\n"
            << "  Commands:\n"
            << "    build      Build the project\n"
            << "    run        Run the project\n"
            << "    clean      Clean build files\n"
            << "    generate   Generate CMake project\n"
            << "    help       Show this help\n"
            << "\n";
    }

    int run(int argc, char* argv[]) {
        if (argc < 2) {
            printHelp();
            return 0;
        }

        const std::string command = argv[1];

        if (command == "build") {
            Project project;

            if (!ProjectManager::load(project)) {
                return 1;
            }

            return Builder::build(project) ? 0 : 1;
        }

        if (command == "generate") {
            Project project;

            if (!ProjectManager::load(project)) {
                return 1;
            }

            return Builder::generateCMake(project) ? 0 : 1;
        }

        if (command == "run") {
            Project project;

            if (!ProjectManager::load(project)) {
                return 1;
            }

            return Builder::run(project) ? 0 : 1;
        }

        if (command == "clean") {
            return Builder::clean() ? 0 : 1;
        }

        if (command == "help") {
            printHelp();
            return 0;
        }

        std::cerr
            << "\n"
            << "  [ERROR] Unknown command: "
            << command
            << "\n";

        printHelp();

        return 1;
    }

}