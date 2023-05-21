FHE-Deck
=======

About
-----------

FHE-Deck is a C++ library that implements Fully Homomorphic Encryption scheme based on functional bootstraping.


Compilation
-----------

With Ubuntu 20.4:

> sudo apt-get install  build-essential
> 
> sudo apt-get install libntl-dev
> 
> sudo apt-get install libfftw3-dev
> 
> sudo apt-get install fftw-dev (I run this before the libfftw3-dev) but it didn't compile. I don't know whether this fftw-dev is needed.

Then install Intel Hexl from [link](https://github.com/intel/hexl).
Finally run:
> make

Check example:
> ./fhe_context_test 


Usage
-----------

More detailed description is under development.
But the test file "fhe_context_test.cpp" contains examples of the high level interface.


References
-----------

1. Kamil Kluczniak. NTRU-$\nu$-um: Secure Fully Homomorphic Encryption from NTRU with Small Modulus. [link](https://eprint.iacr.org/2022/089).

2. Kamil Kluczniak. Circuit Privacy for FHEW/TFHE-Style Fully Homomorphic Encryption in Practice. [link](https://eprint.iacr.org/2022/1459)

