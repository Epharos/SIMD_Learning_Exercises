<a id="readme-top"></a>

<div align="center">

[![Unlicense License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

</div>

# Matrix Multiplication with Vector

## Overview

This exercise was the first actual challenge while learning SIMD. The goal was to implement a 4x4 matrix multiplication with a 4x1 vector.

### Goals

- Load the matrix and vector data into SIMD registers.
- Multiply the matrix and vector.
- Save the result back to memory to be used somewhere else.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Solution

I used the previous exercise (Dot Product) to implement the matrix multiplication. Since each computation to get the final result is to perform a dot product of each matrix row with the vector, I perform the multiplication using `_mm_mul_ps`, and then use `_mm_hadd_ps` to sum the results.

I used that exercise to implement an AVX version, using `_mm256_dp_ps` to perform the dot product in one instruction. This is a great improvement over the SSE version, as it allows for better performance on modern CPUs that support AVX. Also, it introduced me to masks withing function calls.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Contact

REY Aurélien - [Website](http://www.epharos.fr/) - [Linked In][linkedin-url] - aur.rey30@gmail.com

Project Link: [https://github.com/Epharos/SIMD](https://github.com/Epharos/SIMD)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/Epharos/SIMD/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&color=0a66c2
[linkedin-url]: https://www.linkedin.com/in/aur%C3%A9lien-rey-b06039145/