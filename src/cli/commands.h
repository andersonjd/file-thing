#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <CLI/CLI.hpp>
#include <string>

/**
 *  Struct to hold arguments for the create subcommand callback
*/
struct CreateOpts {
    std::string file;
    std::string text;
};

/**
 *  Struct to hold arguments for the copy subcommand callback
*/
struct CopyOpts {
    std::string source_file;
    std::string dest_file;
};

/**
 *  Struct to hold arguments for the combine subcommand callback
*/
struct CombineOpts {
    std::string source_file1;
    std::string source_file2;
    std::string dest_file;
};

/**
 *  Struct to hold arguments for the delete subcommand callback
*/
struct DeleteOpts {
    std::string file;
};



/**
 * Sets up the subcommands and registers the callbacks
 * 
 * @param app CLI::App reference to register commands to
*/
void setupCommands(CLI::App &app);

/**
 * Callback for the create subcommand
 * 
 * @param opt The options passed in on the command line
 * 
 * @return True if command is successful
*/
bool runCreate(CreateOpts const &opt);

/**
 * Callback for the copy subcommand
 * 
 * @param opt The options passed in on the command line
 * 
 * @return True if command is successful
*/
bool runCopy(CopyOpts const &opt);

/**
 * Callback for the combine subcommand
 * 
 * @param opt The options passed in on the command line
 * 
 * @return True if command is successful
*/
bool runCombine(CombineOpts const &opt);

/**
 * Callback for the delete subcommand
 * 
 * @param opt The options passed in on the command line
 * 
 * @return True if command is successful
*/
bool runDelete(DeleteOpts const &opt);

#endif