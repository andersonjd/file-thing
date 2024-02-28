
#include "CLI/CLI.hpp"
#include "CLI/Argv.hpp"
#include "CLI/Config.hpp"
#include "CLI/Macros.hpp"

#include "cli/commands.h"

#include <iostream>

CLI::App app{};

int main(int argc, char *argv[])
{
    app.description("File Thing: Manipulate files with ease!");
 
    setupCommands(app);

    app.require_subcommand(); 

    CLI11_PARSE(app, argc, argv);

    return 0;
}