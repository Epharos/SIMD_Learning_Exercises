<a id="readme-top"></a>

<div align="center">

[![Unlicense License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

</div>

# Matrix Multiplication

## Overview

This exercise is a simplified version of a problem of real world math libraries. Matrix multiplication is a common operation, especially in 3D rendering. This exercise aims at computing the product of two 4x4 matrices.

### Goals

- Optimizing the load and save operations.
- Perform the product of two 4x4 matrices using SIMD instructions.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Solution

I split the solution into 3 parts:
1. Scalar implementation
2. SSE implementation
3. AVX implementation

The Scalar implementation is the most straightforward. It uses 2 nested loops to compute the product of two matrices. 

The SSE implementation loads the rows of the first matrix and then loops through the columns of the second matrix. Since matrix is stored in row-major order, before anything the second matrix was transposed. This allows to load the columns of the second matrix in a single instruction. Then, I performed the product of each row (from the first matrix) with the currently loaded column (from the second matrix). By cleverly using `_mm_hadd_ps` 3 times, the result is saved in a single register and then stored in the result matrix.

The AVX implementation is a bit more tricky. The idea there is a batch processing, I loop 4 times, loading 2 rows are a time from 2 matrices in 4 different registers. Then looping through the columns of the second matrix, I load 2 columns at a time from 2 matrices again in 4 other registers. The result is then to add twice the result of the products of the corresponding rows and columns. The result is stored in the result matrix. That way we can effectively process 8 matrices at a time dividing the entire computation time by 9 compared to the scalar version.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Contact

REY Aurélien - [Website](http://www.epharos.fr/) - [Linked In][linkedin-url] - aur.rey30@gmail.com

Project Link: [https://github.com/Epharos/SIMD](https://github.com/Epharos/SIMD)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/Epharos/SIMD/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&color=0a66c2
[linkedin-url]: https://www.linkedin.com/in/aur%C3%A9lien-rey-b06039145/