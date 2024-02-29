#!/bin/bash

###############################################################################
#  Builder.sh
#  
#  Calling this script with no arguments builds the ft utility locally.
#
#  Arguments:
#
#    unit_test - Builds and runs the ft unit tests
#    upload    - Builds and upload the ft conan package
###############################################################################
skip_unit_tests='True'

build_type='Release'
build_dir='build'

output_path="${build_dir}/${build_type}"
pkg_name='ft'
pkg_ver="${VERSION}"

clean() {
    rm -r "${build_dir}"
}

build() {
    conan install . -c tools.build:skip_test="${skip_unit_tests}" --build=missing --version="${pkg_ver}"
    conan build . -c tools.build:skip_test="${skip_unit_tests}" --version="${pkg_ver}"
}

upload() {
        conan create . -c tools.build:skip_test=True -tf="" --version="${pkg_ver}"
        conan upload "${pkg_name}/${pkg_ver}" -r conan-local 
}

if [ "$1" == "unit_test" ]; then
    skip_unit_tests='False'
fi

clean
build

if [ "$1" == "upload" ]; then
    upload
fi
