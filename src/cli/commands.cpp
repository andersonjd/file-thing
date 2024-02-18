#include "commands.h"
#include "../ft/file_thing.h"

void setupCommands(CLI::App &app)
{
    // Create
    // Create the option and subcommand objects.
    auto createOpts = std::make_shared<CreateOpts>();
    auto *createCommand = app.add_subcommand("create", "Create a file");

    // Add options to sub, binding them to opt.
    createCommand->add_option("-f,--file", createOpts->file, "File name")->required();
    createCommand->add_option("-t,--text", createOpts->text, "Optional text to be inserted into file");

    // Set the run function as callback to be called when this subcommand is issued.
    createCommand->callback([createOpts]()
                            { runCreate(*createOpts); });

    // Copy
    auto copyOpts = std::make_shared<CopyOpts>();
    auto *copyCommand = app.add_subcommand("copy", "Copy a file from one location to another");

    copyCommand->add_option("-s, --source", copyOpts->source_file, "Source file")->required();
    copyCommand->add_option("-d, --dest", copyOpts->dest_file, "Destination file")->required();

    copyCommand->callback([copyOpts]()
                          { runCopy(*copyOpts); });

    // Combine
    auto combineOpts = std::make_shared<CombineOpts>();
    auto *combineCommand = app.add_subcommand("combine", "Combine two files into a third");

    combineCommand->add_option("-1, --file1", combineOpts->source_file1, "Source file 1")->required();
    combineCommand->add_option("-2, --file2", combineOpts->source_file2, "Source file 2")->required();
    combineCommand->add_option("-d, --dest", combineOpts->dest_file, "Destination")->required();

    combineCommand->callback([combineOpts]()
                             { runCombine(*combineOpts); });

    // Delete
    auto delOpts = std::make_shared<DeleteOpts>();
    auto *delCommand = app.add_subcommand("delete", "Delete a file");

    delCommand->add_option("-f, --file", delOpts->file, "File to delete")->required();

    delCommand->callback([delOpts]()
                         { runDelete(*delOpts); });
}

void runCreate(CreateOpts const &opt)
{
    std::cout << "Create called with: " << std::endl;
    std::cout << '\t' << opt.file << std::endl;
    std::cout << "Text:" << std::endl
              << '\t' << opt.text << std::endl
              << std::endl;

    auto errorCode = createFileWithText(opt.file, opt.text);
}

void runCopy(CopyOpts const &opt)
{
    std::cout << "Copy called with: " << std::endl;
    std::cout << "\t Source: " << opt.source_file << std::endl;
    std::cout << "\t Dest: " << opt.dest_file << std::endl
              << std::endl;

    auto errorCode = copyFile(opt.source_file, opt.dest_file);
}

void runCombine(CombineOpts const &opt)
{
    std::cout << "Combine called with: " << std::endl;
    std::cout << "\t File 1: " << opt.source_file1 << std::endl;
    std::cout << "\t File 2: " << opt.source_file2 << std::endl;
    std::cout << "\t Dest: " << opt.dest_file << std::endl
              << std::endl;

    auto errorCode = combineFiles(opt.source_file1, opt.source_file2, opt.dest_file);
}

void runDelete(DeleteOpts const &opt)
{
    std::cout << "Delete called with: " << std::endl;
    std::cout << "\t File: " << opt.file << std::endl
              << std::endl;

    auto errorCode = deleteFile(opt.file);
}