#pragma once

#include <string>
#include <vector>

enum class ProjectType {
    Executable,
    StaticLibrary,
    SharedLibrary
};

struct Project {
    std::string name;

    int cppStandard = 23;

    ProjectType type = ProjectType::Executable;

    std::string sourceDirectory = "src";

    std::vector<std::string> includes;
    std::vector<std::string> defines;
    std::vector<std::string> links;
};

namespace ProjectManager {

    bool load(Project& project);

}