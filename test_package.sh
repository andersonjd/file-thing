#!/bin/bash

###############################################################################
#  test_package.sh
#
#  Pre-req: ft Debina package should be installed in system
#           `sudo dpkg -i ft_0.1-1_amd64.deb`
#
#  Runs basic post-install package integration tests
#
###############################################################################

test_dir="int_tests"

# Creates test directory and cd into it
setup() {
    mkdir -p "${test_dir}"
    cd "${test_dir}" || exit 1
}

# Removes created directory
teardown() {
    cd ../
    rm -r "${test_dir}"
}

# Check to make sure ft is installed
check_installed() {
    if ! command -v ft &>/dev/null; then
        echo "The utility 'ft' is not installed." >&2
        exit 1
    fi
}

# Check to make sure ft installed in /usr/bin
check_location() {
    local expected_location="/usr/bin/ft"
    if [ ! -x "$expected_location" ]; then
        echo "Error: 'ft' is not installed in the correct location or is not executable." >&2
        exit 1
    fi
}

# Test ft create command
test_create() {

    setup

    local file="./test.txt"
    local text="This is a test."

    ft create --file "${file}" --text "${text}" &>/dev/null

    # Check if ./test.txt exists
    if [ ! -f "${file}" ]; then
        echo "Error: ${file} does not exist." >&2
        teardown
        exit 1
    fi

    # Validate the content of ./test.txt
    if ! grep -q "${text}" "${file}"; then
        echo "Error: The file ${file} does not contain the expected text." >&2
        teardown
        exit 1
    fi

    teardown
}

# Test ft copy command
test_copy() {

    setup

    local orig="./orig.txt"
    local copy="./copy.txt"
    local text="This is a test."

    # Create orig
    touch "${orig}"
    echo "${text}" >>"${orig}"

    ft copy --source "${orig}" --dest "${copy}" &>/dev/null

    # Check if ./copy.txt exists
    if [ ! -f "${copy}" ]; then
        echo "Error: ${copy} does not exist." >&2
        teardown
        exit 1
    fi

    # Validate the content of ./copy.txt
    diff -w -q <(cat "${copy}") <(cat "${orig}") &>/dev/null
    if [ ! $? -eq 0 ]; then
        echo "Error: The file ${copy} does not contain the expected text." >&2
        teardown
        exit 1
    fi

    teardown
}

# Test ft combine command
test_combine() {
    setup

    local file1="./file1.txt"
    local text1="This is a first test."
    local file2="./file2.txt"
    local text2="This is a second test."
    local dest="./combined.txt"
    local expected="./expected.txt"

    # Create test files
    touch "${file1}"
    echo "${text1}" >>"${file1}"

    touch "${file2}"
    echo "${text2}" >>"${file2}"

    touch "${expected}"
    echo "${text1}" >"${expected}"
    echo "${text2}" >>"${expected}"

    ft combine -1 "${file1}" -2 "${file2}" -d "${dest}" &>/dev/null

    # Check if ./combined.txt exists
    if [ ! -f "${dest}" ]; then
        echo "Error: ${dest} does not exist." >&2
        teardown
        exit 1
    fi

    # Validate the content of ./combined.txt
    diff -w -q <(cat "${dest}") <(cat "${expected}") &>/dev/null
    if [ ! $? -eq 0 ]; then
        echo "Error: The file ${dest} does not contain the expected text." >&2
        teardown
        exit 1
    fi

    teardown
}

# Test ft delete command
test_delete() {
    setup

    local file="./file.txt"
    touch "${file}"

    # Check if ./file.txt exists
    if [ ! -f "${file}" ]; then
        echo "Error: ${file} does not exist." >&2
        teardown
        exit 1
    fi

    ft delete -f "${file}" &>/dev/null

    if [ -f "${file}" ]; then
        echo "Error: ${file} exists and should not." >&2
        teardown
        exit 1
    fi

    teardown
}

# Run tests

echo "Running installation checks..."

check_installed
check_location

echo "Passed!"
echo ""

echo "Running create test..."
test_create
echo "Passed!"
echo ""

echo "Running copy test..."
test_copy
echo "Passed!"
echo ""

echo "Running combine test..."
test_combine
echo "Passed!"
echo ""

echo "Running delete test..."
test_delete
echo "Passed!"
echo ""
