# Check if the desired compiler is gcc, this flag is passed to test test cases.
if [[ $1 == "gcc" ]]; then
    echo "[Test] Using GCC to compile tests. Only the test-cases will be tested!"
    USE_GCC=1
else
    USE_GCC=0
fi

# This is the script that tests our compiler on all the test cases
# This file is mostly copied from the langproc lab section 3

# Try to find a portable way of getting rid of
# any stray carriage returns
if which dos2unix ; then
    DOS2UNIX="dos2unix"
elif which fromdos ; then
    DOS2UNIX="fromdos"
else
    # This works on a GNU version of sed. I think this
    # will work in OSX as well, but don't have a machine
    # on which to test that. From reading the OSX docs,
    # it looks compatible.
    # The code \x0D is the ASCII code of carriage-return,
    # so it the regex should delete any CRs at the end of
    # a line (or anywhere in a line)
    DOS2UNIX="cat"
    # Tested for combinations of:
    # - Ubuntu
    # - Cygwin
    # and inputs formats:
    # - LF
    # - CRLF
fi

echo "========================================"
echo "[Build] Cleaning the temporaries and outputs"
make clean

echo "========================================"
echo "[Build] Running make all"
make all
if [[ "$?" -ne "0" ]]; then
    echo "[Build] Error while building compiler."
    exit 1;
fi

echo "========================================="

PASSED=0
CHECKED=0

# Clearing test folder
rm -rf test/test_run_results
mkdir -p test/test_run_results

# go through the test_cases directories
for d in test/compiler_test_cases/*/ ; do

    for driver_file in $d*_driver.c ; do
        echo "########################################"
        # test/compiler_test_cases/array/something(_driver).c
        testcase_file=$(echo "$driver_file" | sed 's/_driver//g')
        base_dir=$(echo "$testcase_file" | sed 's/test\/compiler_test_cases//')
        compiler_target_file=$(echo "test/test_run_results$base_dir" | sed 's/\.c//g')
        mkdir -p test/test_run_results$(dirname $base_dir)
        echo "[Test] Running test for:  $testcase_file"

        if [[ $USE_GCC -ne 0 ]]; then
            echo "Using GCC to compile the test-cases"
            mips-linux-gnu-gcc -mfp32 -static -o $compiler_target_file $testcase_file $driver_file
        else
            # Compiling the testcase using the C to MIPS compiler under test
            bin/c_compiler -S $testcase_file -o ${compiler_target_file}.s
            # Assembling the MIPS Assembly using gcc
            mips-linux-gnu-gcc -mfp32 -o "${compiler_target_file}.o" -c ${compiler_target_file}.s
            # Linking the MIPS-Assembled object file with the driver file using gcc
            mips-linux-gnu-gcc -mfp32 -static -o $compiler_target_file "${compiler_target_file}.o" $driver_file
            # Simulating the assembled code on MIPS using the qemu mips emulator
        fi

        # Simulating the assembled code on MIPS using the qemu mips emulator
        qemu-mips $compiler_target_file
        # If the test has passed, then the exit code should be zero
        if [[ $? -ne 0 ]]; then
            echo "[Test] Test-case FAILED!"
        else
            echo "[Test] Test-case PASSED!"
            PASSED=$(( ${PASSED}+1 ));
        fi
        CHECKED=$(( ${CHECKED}+1 ));
    done
done

echo "########################################"
echo "[Report] Passed ${PASSED} out of ${CHECKED}".
echo ""

# For Timeo: If wrong bison installation is used, run: export PATH="/usr/local/opt/bison/bin:$PATH"
