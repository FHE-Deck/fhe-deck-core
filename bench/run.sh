#!/bin/sh

echo '[+] add3_boolean'
build/bench/add3_boolean 2> /dev/null | grep 'BM'
echo '[+] add3_lut2'
build/bench/add3_lut2 2> /dev/null | grep 'BM'
echo '[+] add3_lut2fa'
build/bench/add3_lut2fa 2> /dev/null | grep 'BM'
echo '[+] add3_lut3'
build/bench/add3_lut3 2> /dev/null | grep 'BM'
echo '[+] add3_lut3fa'
build/bench/add3_lut3fa 2> /dev/null | grep 'BM'
echo '[+] add3_lut4'
build/bench/add3_lut4 2> /dev/null | grep 'BM'
echo '[+] add3_lut4fa'
build/bench/add3_lut4fa 2> /dev/null | grep 'BM'
echo '[+] add4_boolean'
build/bench/add4_boolean 2> /dev/null | grep 'BM'
echo '[+] add4_lut2'
build/bench/add4_lut2 2> /dev/null | grep 'BM'
echo '[+] add4_lut2fa'
build/bench/add4_lut2fa 2> /dev/null | grep 'BM'
echo '[+] add4_lut3'
build/bench/add4_lut3 2> /dev/null | grep 'BM'
echo '[+] add4_lut3fa'
build/bench/add4_lut3fa 2> /dev/null | grep 'BM'
echo '[+] add4_lut4'
build/bench/add4_lut4 2> /dev/null | grep 'BM'
echo '[+] add4_lut4fa'
build/bench/add4_lut4fa 2> /dev/null | grep 'BM'
echo '[+] calculator_boolean'
build/bench/calculator_boolean 2> /dev/null | grep 'BM'
echo '[+] calculator_lut2'
build/bench/calculator_lut2 2> /dev/null | grep 'BM'
echo '[+] calculator_lut2fa'
build/bench/calculator_lut2fa 2> /dev/null | grep 'BM'
echo '[+] calculator_lut3'
build/bench/calculator_lut3 2> /dev/null | grep 'BM'
echo '[+] calculator_lut3fa'
build/bench/calculator_lut3fa 2> /dev/null | grep 'BM'
echo '[+] calculator_lut4'
build/bench/calculator_lut4 2> /dev/null | grep 'BM'
echo '[+] calculator_lut4fa'
build/bench/calculator_lut4fa 2> /dev/null | grep 'BM'
echo '[+] const4_boolean'
build/bench/const4_boolean 2> /dev/null | grep 'BM'
echo '[+] const4_lut2'
build/bench/const4_lut2 2> /dev/null | grep 'BM'
echo '[+] const4_lut2fa'
build/bench/const4_lut2fa 2> /dev/null | grep 'BM'
echo '[+] const4_lut3'
build/bench/const4_lut3 2> /dev/null | grep 'BM'
echo '[+] const4_lut3fa'
build/bench/const4_lut3fa 2> /dev/null | grep 'BM'
echo '[+] const4_lut4'
build/bench/const4_lut4 2> /dev/null | grep 'BM'
echo '[+] const4_lut4fa'
build/bench/const4_lut4fa 2> /dev/null | grep 'BM'
echo '[+] image_gaussian_boolean'
build/bench/image_gaussian_boolean 2> /dev/null | grep 'BM'
echo '[+] image_gaussian_lut2'
build/bench/image_gaussian_lut2 2> /dev/null | grep 'BM'
echo '[+] image_gaussian_lut2fa'
build/bench/image_gaussian_lut2fa 2> /dev/null | grep 'BM'
echo '[+] image_gaussian_lut3'
build/bench/image_gaussian_lut3 2> /dev/null | grep 'BM'
echo '[+] image_gaussian_lut3fa'
build/bench/image_gaussian_lut3fa 2> /dev/null | grep 'BM'
echo '[+] image_gaussian_lut4'
build/bench/image_gaussian_lut4 2> /dev/null | grep 'BM'
echo '[+] image_gaussian_lut4fa'
build/bench/image_gaussian_lut4fa 2> /dev/null | grep 'BM'
echo '[+] image_ricker_boolean'
build/bench/image_ricker_boolean 2> /dev/null | grep 'BM'
echo '[+] image_ricker_lut2'
build/bench/image_ricker_lut2 2> /dev/null | grep 'BM'
echo '[+] image_ricker_lut2fa'
build/bench/image_ricker_lut2fa 2> /dev/null | grep 'BM'
echo '[+] image_ricker_lut3'
build/bench/image_ricker_lut3 2> /dev/null | grep 'BM'
echo '[+] image_ricker_lut3fa'
build/bench/image_ricker_lut3fa 2> /dev/null | grep 'BM'
echo '[+] image_ricker_lut4'
build/bench/image_ricker_lut4 2> /dev/null | grep 'BM'
echo '[+] image_ricker_lut4fa'
build/bench/image_ricker_lut4fa 2> /dev/null | grep 'BM'
echo '[+] image_sharpen_boolean'
build/bench/image_sharpen_boolean 2> /dev/null | grep 'BM'
echo '[+] image_sharpen_lut2'
build/bench/image_sharpen_lut2 2> /dev/null | grep 'BM'
echo '[+] image_sharpen_lut2fa'
build/bench/image_sharpen_lut2fa 2> /dev/null | grep 'BM'
echo '[+] image_sharpen_lut3'
build/bench/image_sharpen_lut3 2> /dev/null | grep 'BM'
echo '[+] image_sharpen_lut3fa'
build/bench/image_sharpen_lut3fa 2> /dev/null | grep 'BM'
echo '[+] image_sharpen_lut4'
build/bench/image_sharpen_lut4 2> /dev/null | grep 'BM'
echo '[+] image_sharpen_lut4fa'
build/bench/image_sharpen_lut4fa 2> /dev/null | grep 'BM'
echo '[+] relu_boolean'
build/bench/relu_boolean 2> /dev/null | grep 'BM'
echo '[+] relu_lut2'
build/bench/relu_lut2 2> /dev/null | grep 'BM'
echo '[+] relu_lut2fa'
build/bench/relu_lut2fa 2> /dev/null | grep 'BM'
echo '[+] relu_lut3'
build/bench/relu_lut3 2> /dev/null | grep 'BM'
echo '[+] relu_lut3fa'
build/bench/relu_lut3fa 2> /dev/null | grep 'BM'
echo '[+] relu_lut4'
build/bench/relu_lut4 2> /dev/null | grep 'BM'
echo '[+] relu_lut4fa'
build/bench/relu_lut4fa 2> /dev/null | grep 'BM'
echo '[+] sqrt_boolean'
build/bench/sqrt_boolean 2> /dev/null | grep 'BM'
echo '[+] sqrt_lut2'
build/bench/sqrt_lut2 2> /dev/null | grep 'BM'
echo '[+] sqrt_lut2fa'
build/bench/sqrt_lut2fa 2> /dev/null | grep 'BM'
echo '[+] sqrt_lut3'
build/bench/sqrt_lut3 2> /dev/null | grep 'BM'
echo '[+] sqrt_lut3fa'
build/bench/sqrt_lut3fa 2> /dev/null | grep 'BM'
echo '[+] sqrt_lut4'
build/bench/sqrt_lut4 2> /dev/null | grep 'BM'
echo '[+] sqrt_lut4fa'
build/bench/sqrt_lut4fa 2> /dev/null | grep 'BM'
echo '[+] strrev_boolean'
build/bench/strrev_boolean 2> /dev/null | grep 'BM'
echo '[+] strrev_lut2'
build/bench/strrev_lut2 2> /dev/null | grep 'BM'
echo '[+] strrev_lut2fa'
build/bench/strrev_lut2fa 2> /dev/null | grep 'BM'
echo '[+] strrev_lut3'
build/bench/strrev_lut3 2> /dev/null | grep 'BM'
echo '[+] strrev_lut3fa'
build/bench/strrev_lut3fa 2> /dev/null | grep 'BM'
echo '[+] strrev_lut4'
build/bench/strrev_lut4 2> /dev/null | grep 'BM'
echo '[+] strrev_lut4fa'
build/bench/strrev_lut4fa 2> /dev/null | grep 'BM'
echo '[+] structs_1d_boolean'
build/bench/structs_1d_boolean 2> /dev/null | grep 'BM'
echo '[+] structs_1d_lut2'
build/bench/structs_1d_lut2 2> /dev/null | grep 'BM'
echo '[+] structs_1d_lut2fa'
build/bench/structs_1d_lut2fa 2> /dev/null | grep 'BM'
echo '[+] structs_1d_lut3'
build/bench/structs_1d_lut3 2> /dev/null | grep 'BM'
echo '[+] structs_1d_lut3fa'
build/bench/structs_1d_lut3fa 2> /dev/null | grep 'BM'
echo '[+] structs_1d_lut4'
build/bench/structs_1d_lut4 2> /dev/null | grep 'BM'
echo '[+] structs_1d_lut4fa'
build/bench/structs_1d_lut4fa 2> /dev/null | grep 'BM'
echo '[+] structs_3d_boolean'
build/bench/structs_3d_boolean 2> /dev/null | grep 'BM'
echo '[+] structs_3d_lut2'
build/bench/structs_3d_lut2 2> /dev/null | grep 'BM'
echo '[+] structs_3d_lut2fa'
build/bench/structs_3d_lut2fa 2> /dev/null | grep 'BM'
echo '[+] structs_3d_lut3'
build/bench/structs_3d_lut3 2> /dev/null | grep 'BM'
echo '[+] structs_3d_lut3fa'
build/bench/structs_3d_lut3fa 2> /dev/null | grep 'BM'
echo '[+] structs_3d_lut4'
build/bench/structs_3d_lut4 2> /dev/null | grep 'BM'
echo '[+] structs_3d_lut4fa'
build/bench/structs_3d_lut4fa 2> /dev/null | grep 'BM'
echo '[+] sum3d_boolean'
build/bench/sum3d_boolean 2> /dev/null | grep 'BM'
echo '[+] sum3d_lut2'
build/bench/sum3d_lut2 2> /dev/null | grep 'BM'
echo '[+] sum3d_lut2fa'
build/bench/sum3d_lut2fa 2> /dev/null | grep 'BM'
echo '[+] sum3d_lut3'
build/bench/sum3d_lut3 2> /dev/null | grep 'BM'
echo '[+] sum3d_lut3fa'
build/bench/sum3d_lut3fa 2> /dev/null | grep 'BM'
echo '[+] sum3d_lut4'
build/bench/sum3d_lut4 2> /dev/null | grep 'BM'
echo '[+] sum3d_lut4fa'
build/bench/sum3d_lut4fa 2> /dev/null | grep 'BM'
echo '[+] sum_boolean'
build/bench/sum_boolean 2> /dev/null | grep 'BM'
echo '[+] sum_lut2'
build/bench/sum_lut2 2> /dev/null | grep 'BM'
echo '[+] sum_lut2fa'
build/bench/sum_lut2fa 2> /dev/null | grep 'BM'
echo '[+] sum_lut3'
build/bench/sum_lut3 2> /dev/null | grep 'BM'
echo '[+] sum_lut3fa'
build/bench/sum_lut3fa 2> /dev/null | grep 'BM'
echo '[+] sum_lut4'
build/bench/sum_lut4 2> /dev/null | grep 'BM'
echo '[+] sum_lut4fa'
build/bench/sum_lut4fa 2> /dev/null | grep 'BM'
