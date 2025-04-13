<a id="readme-top"></a>

<div align="center">

[![Unlicense License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

</div>

# Load and Save

## Overview

This exercise was the introduction of my SIMD learning process. SIMD (Single Instruction, Multiple Data) is a parallel computing architecture that allows a single instruction to operate on multiple data points simultaneously. The goal was to implement basic load and save operations using SIMD instructions.

### Goals

- Load data from memory into SIMD registers.
- Transform them with a basic operation (I chose to use multiplication).
- Save the results back to memory.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Solution

My solution is working on 4 floats (32 bits) at a time. I used the `_mm_load_ps` intrinsic to load data from memory into a SIMD register, and `_mm_store_ps` to save the results back to memory. The multiplication operation was performed using the `_mm_mul_ps` intrinsic.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Contact

REY Aurélien - [Website](http://www.epharos.fr/) - [Linked In][linkedin-url] - aur.rey30@gmail.com

Project Link: [https://github.com/Epharos/SIMD](https://github.com/Epharos/SIMD)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/Epharos/SIMD/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&color=0a66c2
[linkedin-url]: https://www.linkedin.com/in/aur%C3%A9lien-rey-b06039145/