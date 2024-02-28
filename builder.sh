#!/bin/bash

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

package() {
    mkdir "${pkg_name}-${pkg_ver}"
    cp "${output_path}"/ft "${pkg_name}-${pkg_ver}"
    tar -zcf "${pkg_name}-${pkg_ver}".orig.tar.gz "${pkg_name}-${pkg_ver}"
    tar -zxf "${pkg_name}-${pkg_ver}".orig.tar.gz
    cd "${pkg_name}-${pkg_ver}"/ || exit
    dh_make -s -c gpl -y -f ../"${pkg_name}-${pkg_ver}".orig.tar.gz
    touch debian/ft.install
    echo "ft usr/bin/" >>debian/ft.install
    debuild -us -uc
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
