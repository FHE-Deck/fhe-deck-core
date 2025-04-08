FHE-Deck
=======

About
-----------

FHE-Deck is a C++ library that implements fully homomorphic encryption schemes based on functional bootstrapping.

Compilation
-----------

With Ubuntu 20.4:

```
sudo apt-get install build-essential
sudo apt-get install libntl-dev 
```
 
A default build of the library can be done as follows.
```
cmake -S . -B build
cmake --build build
```

## Compilation Options

You can customize the build. In particular, you can choose which compute engines and serialization libraries to use.
The following CMake flags can be used to configure the build:

### `INV_ENGINE`
- **Description**: Specifies the polynomial inversion engine to use.
- **Options**:
  - `NTL`: Use the NTL library for polynomial inversion.
  - `BUILDIN`: Use the built-in inversion engine (default).
- **Default**: `BUILDIN`

### `NTT_ENGINE`
- **Description**: Specifies the Number Theoretic Transform (NTT) engine to use.
- **Options**:
  - `Hexl`: Use Intel HEXL for NTT operations.
  - `BUILDIN`: Use the built-in NTT engine.
- **Default**: `Hexl`

### `FFT_ENGINE`
- **Description**: Specifies the FFT engine to use for floating-point arithmetic.
- **Options**:
  - `FFTW`: Use the FFTW library for FFT operations.
  - `BUILDIN`: Use the built-in FFT engine.
- **Default**: `FFTW`

### `FFT_LONG_DOUBLE_ENGINE`
- **Description**: Specifies the FFT engine to use for long double arithmetic.
- **Options**:
  - `FFTW`: Use the FFTW library for FFT operations with long double precision.
  - `BUILDIN`: Use the built-in FFT engine for long double precision.
- **Default**: `FFTW`

### `USE_CEREAL`
- **Description**: Enables or disables support for serialization using the Cereal library.
- **Options**:
  - `TRUE`: Enable Cereal support.
  - `FALSE`: Disable Cereal support.
- **Default**: `TRUE`

### `USE_EXAMPLES`
- **Description**: Specifies whether to compile example programs.
- **Options**:
  - `TRUE`: Compile the examples in the `examples` directory.
  - `FALSE`: Do not compile the examples.
- **Default**: `FALSE`


For example, if you do not want to include FFTW and CEREAL as dependencies, configure and build the library as follows:


```
cmake -S . -B build -DFFT_ENGINE=BUILDIN -DFFT_LONG_DOUBLE_ENGINE=BUILDIN -DUSE_CEREAL=FALSE
cmake --build build
```



Usage
-----------

The `examples` directory contains several example programs that demonstrate the usage of the FHE-Deck library. Below is a brief description of each example:

- **`partial_domain_functional_bootstrap_examples.cpp`**: Demonstrates the basic usage of the libraries interface including different variants of functional bootstrapping.
- **`full_domain_functional_bootstrapping_examples.cpp`**: Demonstrates shortcommings of partial domain plaintext encoding and full domain functional bootstrapping as well as modular arithmetic on ciphertexts. 
- **`serialization_example.cpp`**: Show how to use the libraries interface to store and load keys and ciphertexts.
- **`integers_examples.cpp`**: Demonstrates FHE-Deck's implementation of big integers via digit decomposition and the residue number system.
- **`partial_domain_signed_ints_example.cpp`**: Demonstrates a partial domain-style encoding that handles small signed integers. 

To build and run the examples, configure the project with the `USE_EXAMPLES` flag set to `TRUE`:

```bash
cmake -S . -B build -DUSE_EXAMPLES=TRUE
cmake --build build
```

You can then run the examples from the build/examples directory:

```bash
./build/examples/partial_domain_functional_bootstrap_examples
./build/examples/full_domain_functional_bootstrap_examples
# and so on...
```


References
-----------

1. Kamil Kluczniak. NTRU-$\nu$-um: Secure Fully Homomorphic Encryption from NTRU with Small Modulus. [link](https://eprint.iacr.org/2022/089).

2. Kamil Kluczniak. Circuit Privacy for FHEW/TFHE-Style Fully Homomorphic Encryption in Practice. [link](https://eprint.iacr.org/2022/1459)


3. Kamil Kluczniak, Leonard Schild. FDFB^2: Functional Bootstrapping via Sparse Polynomial Multiplication. [link](https://eprint.iacr.org/2024/1376)


Acknowledgements
-----------
I thank Leonard Schild for contributions to the library. In particular, for the initial implementation of the KS bootstrapping algorithm. 