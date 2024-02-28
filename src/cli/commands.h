#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <CLI/CLI.hpp>
#include <string>

struct CreateOpts {
    std::string file;
    std::string text;
};

struct CopyOpts {
    std::string source_file;
    std::string dest_file;
};

struct CombineOpts {
    std::string source_file1;
    std::string source_file2;
    std::string dest_file;
};

struct DeleteOpts {
    std::string file;
};

void setupCommands(CLI::App &app);


void runCreate(CreateOpts const &opt);
void runCopy(CopyOpts const &opt);
void runCombine(CombineOpts const &opt);
void runDelete(DeleteOpts const &opt);

#endif