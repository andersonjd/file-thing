# File Thing

Manipulate files with ease!

- Create a file (empty or with optional text) 
- Copy a file 
- Combine two files into a third 
- Delete a file 


Developed and tested on:
 - Ubuntu 22.04
 - gcc version 11.4.0 (c++ 17 std)

Debian package build available on 'Releases' page.

## Descritpion

File Thing provides a command line interface for basic file manipulation tasks.  You can create a file (empty or from text), copy a file from one location to another, combine two files to create a third, and finally delete a file.

## Usage

### Create a file

Create a new empty file:

```
$ ft create path/to/file.txt
```

## Building

Building requires Conan, CMake, and a working C++ toolchain.

The easiest way to install Conan is with pip:

```
$ pip install conan
```

For more detailed instructions see the official docs [here](https://docs.conan.io/2/installation.html).


## Testing

Unit tests are run by default


## Notes

- Currently the scripts only support building in release
- The Github actions runner and artifactory being used for the CI are personal resources and not up 24/7.
- Versions is static, should be automated.

