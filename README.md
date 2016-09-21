# Artificial Neural Networks (ANN) Image Compression

for laboratory work.

## Library

<a href="http://arma.sourceforge.net/docs.html/">Armadillo C++ linear algebra library</a>

<a href="http://cimg.eu/">The CImg Library for image processing</a>

for Ubuntu:

```sh
sudo apt-get install libarmadillo-dev libarmadillo6
sudo apt-get install cimg-dev

```

##Input:

n – hight of rectangle;

m – width of rectangle;

p – number of neuron for second layer;

e – error degree;

α – learning step;


##Output:

Z – compression ratio;

Iteration – number of iterations;

E – total error for the training sample;


## Example

Input Image
<p align="center">
  <img src="https://raw.githubusercontent.com/blrB/ANNImageCompression/master/256px-Lenna.png" alt="Input"/>
</p>

Output Image(n:8; m:8; p:48; e:256; a:0.001; Iteration = 515; Z = 3.36831)
<p align="center">
  <img src="https://raw.githubusercontent.com/blrB/ANNImageCompression/master/256px-Lenna-output-error-256.png" alt="Output"/>
</p>

Output Image(n:8; m:8; p:32; e:450; a:0.001; Iteration = 561; Z = 5.05237)
<p align="center">
  <img src="https://raw.githubusercontent.com/blrB/ANNImageCompression/master/256px-Lenna-output-error-450.png" alt="Output"/>
</p>

Output Image(n:8; m:8; p:16; e:973; a:0.001; Iteration = 490; Z = 10.1042)
<p align="center">
  <img src="https://raw.githubusercontent.com/blrB/ANNImageCompression/master/256px-Lenna-output-error-973.png" alt="Output"/>
</p>