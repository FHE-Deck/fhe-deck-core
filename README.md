FHE-Deck
=======

About
-----------

FHE-Deck is a C++ library that implements Fully Homomorphic Encryption schemes based on Functional Bootstraping.


Compilation
-----------

With Ubuntu 20.4:

```
sudo apt-get install  build-essential
sudo apt-get install libntl-dev
sudo apt-get install libfftw3-dev
sudo apt-get install fftw-dev
```

Then install Intel Hexl from [link](https://github.com/intel/hexl).
Finally run:
```
cmake -S . -B build
cmake --build build
```

Check example:
```
build/examples/fhe_context_examples
```


Usage
-----------

More detailed description is under development.
But the test file "fhe_context_test.cpp" contains examples of the high level interface.


References
-----------

1. Kamil Kluczniak. NTRU-$\nu$-um: Secure Fully Homomorphic Encryption from NTRU with Small Modulus. [link](https://eprint.iacr.org/2022/089).

2. Kamil Kluczniak. Circuit Privacy for FHEW/TFHE-Style Fully Homomorphic Encryption in Practice. [link](https://eprint.iacr.org/2022/1459)

