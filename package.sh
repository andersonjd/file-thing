#!/bin/bash


###############################################################################
#  package.sh
#
#  Pre-req: ./Builder.sh with no args is expected to be called before this script  
#
#  Calling this script creates a debian package from the conan build output
#
###############################################################################

pkg_name='ft'
pkg_ver="${VERSION}"

package() {
    mkdir "${pkg_name}-${pkg_ver}"
    cp build/Release/ft "${pkg_name}-${pkg_ver}"
    tar -zcf "${pkg_name}-${pkg_ver}".orig.tar.gz "${pkg_name}-${pkg_ver}"
    tar -zxf "${pkg_name}-${pkg_ver}".orig.tar.gz
    cd "${pkg_name}-${pkg_ver}"/ || exit
    dh_make -s -c gpl -y -f ../"${pkg_name}-${pkg_ver}".orig.tar.gz
    touch debian/ft.install
    echo "ft usr/bin/" >>debian/ft.install
    debuild -us -uc
}

package