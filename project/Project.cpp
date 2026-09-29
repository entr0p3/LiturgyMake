#include "Project.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

namespace {

std::string trim(const std::string& value) {
    const std::size_t start = value.find_first_not_of(" \t\r\n");

    if (start == std::string::npos) {
        return {};
    }

    const std::size_t end = value.find_last_not_of(" \t\r\n");

    return value.substr(start, end - start + 1);
}

bool startsWith(
    const std::string& line,
    const std::string& command
) {
    if (!line.starts_with(command)) {
        return false;
    }

    if (line.size() == command.size()) {
        return true;
    }

    return line[command.size()] == ' ' ||
           line[command.size()] == '\t';
}

std::string getArgument(const std::string& line) {
    const std::size_t space = line.find_first_of(" \t");

    if (space == std::string::npos) {
        return {};
    }

    return trim(line.substr(space + 1));
}

std::string getStringArgument(const std::string& line) {
    const std::string argument = getArgument(line);

    if (argument.size() < 2) {
        return {};
    }

    if (argument.front() != '"' ||
        argument.back() != '"') {
        return {};
    }

    return argument.substr(
        1,
        argument.size() - 2
    );
}

bool parseInteger(
    const std::string& value,
    int& result
) {
    try {
        std::size_t position = 0;

        const int number =
            std::stoi(value, &position);

        if (position != value.size()) {
            return false;
        }

        result = number;

        return true;
    }
    catch (...) {
        return false;
    }
}

}

namespace ProjectManager {

bool load(Project& project) {
    const fs::path projectFile =
        fs::current_path() / "liturgy.ls";

    if (!fs::exists(projectFile)) {
        std::cerr
            << "\n"
            << "  [ERROR] liturgy.ls not found.\n"
            << "  [INFO] Expected file:\n"
            << "         "
            << projectFile
            << "\n\n";

        return false;
    }

    std::ifstream file(projectFile);

    if (!file) {
        std::cerr
            << "\n"
            << "  [ERROR] Failed to open liturgy.ls.\n\n";

        return false;
    }

    bool hasLScript = false;
    bool hasProject = false;

    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) {
        ++lineNumber;

        line = trim(line);

        if (line.empty()) {
            continue;
        }

        // Comments
        if (line.starts_with("#")) {
            continue;
        }

        // Language declaration
        if (line == "using LScript") {
            hasLScript = true;
            continue;
        }

        // Application
        if (startsWith(line, "app")) {
            const std::string name =
                getStringArgument(line);

            if (name.empty()) {
                std::cerr
                    << "  [ERROR] Invalid app declaration at line "
                    << lineNumber
                    << ".\n"
                    << "         Expected: app \"Name\"\n";

                return false;
            }

            project.name = name;
            project.type = ProjectType::Executable;
            hasProject = true;

            continue;
        }

        // Static library
        if (startsWith(line, "lib")) {
            const std::string name =
                getStringArgument(line);

            if (name.empty()) {
                std::cerr
                    << "  [ERROR] Invalid lib declaration at line "
                    << lineNumber
                    << ".\n"
                    << "         Expected: lib \"Name\"\n";

                return false;
            }

            project.name = name;
            project.type = ProjectType::StaticLibrary;
            hasProject = true;

            continue;
        }

        // DLL
        if (startsWith(line, "dll")) {
            const std::string name =
                getStringArgument(line);

            if (name.empty()) {
                std::cerr
                    << "  [ERROR] Invalid dll declaration at line "
                    << lineNumber
                    << ".\n"
                    << "         Expected: dll \"Name\"\n";

                return false;
            }

            project.name = name;
            project.type = ProjectType::SharedLibrary;
            hasProject = true;

            continue;
        }

        // C++ version
        if (startsWith(line, "cpp")) {
            const std::string value =
                getArgument(line);

            if (!parseInteger(value, project.cppStandard)) {
                std::cerr
                    << "  [ERROR] Invalid C++ version at line "
                    << lineNumber
                    << ": "
                    << value
                    << '\n';

                return false;
            }

            continue;
        }

        // Source directory
        if (startsWith(line, "src")) {
            const std::string source =
                getStringArgument(line);

            if (source.empty()) {
                std::cerr
                    << "  [ERROR] Invalid src declaration at line "
                    << lineNumber
                    << ".\n"
                    << "         Expected: src \"directory\"\n";

                return false;
            }

            project.sourceDirectory = source;

            continue;
        }

        // Include directory
        if (startsWith(line, "include")) {
            const std::string include =
                getStringArgument(line);

            if (include.empty()) {
                std::cerr
                    << "  [ERROR] Invalid include declaration at line "
                    << lineNumber
                    << ".\n"
                    << "         Expected: include \"directory\"\n";

                return false;
            }

            project.includes.push_back(include);

            continue;
        }

        // Preprocessor definition
        if (startsWith(line, "define")) {
            const std::string define =
                getArgument(line);

            if (define.empty()) {
                std::cerr
                    << "  [ERROR] Invalid define at line "
                    << lineNumber
                    << ".\n"
                    << "         Expected: define NAME\n";

                return false;
            }

            project.defines.push_back(define);

            continue;
        }

        // Link library
        if (startsWith(line, "link")) {
            const std::string library =
                getArgument(line);

            if (library.empty()) {
                std::cerr
                    << "  [ERROR] Invalid link at line "
                    << lineNumber
                    << ".\n"
                    << "         Expected: link library\n";

                return false;
            }

            project.links.push_back(library);

            continue;
        }

        std::cerr
            << "  [ERROR] Unknown command at line "
            << lineNumber
            << ": "
            << line
            << '\n';

        return false;
    }

    if (!hasLScript) {
        std::cerr
            << "\n"
            << "  [ERROR] This is not an LScript file.\n"
            << "  [INFO] Add: using LScript\n\n";

        return false;
    }

    if (!hasProject || project.name.empty()) {
        std::cerr
            << "\n"
            << "  [ERROR] Project declaration is missing.\n"
            << "  [INFO] Example: app \"MyProject\"\n\n";

        return false;
    }

    std::cout
        << "\n"
        << "  ==============================\n"
        << "       LiturgyMake Project\n"
        << "  ==============================\n"
        << "\n"
        << "  [ OK ] LScript loaded\n"
        << "  [INFO] Name: "
        << project.name
        << '\n'
        << "  [INFO] C++: "
        << project.cppStandard
        << '\n'
        << "  [INFO] Source: "
        << project.sourceDirectory
        << '\n'
        << "  [INFO] Includes: "
        << project.includes.size()
        << '\n'
        << "  [INFO] Defines: "
        << project.defines.size()
        << '\n'
        << "  [INFO] Links: "
        << project.links.size()
        << "\n\n";

    return true;
}

}