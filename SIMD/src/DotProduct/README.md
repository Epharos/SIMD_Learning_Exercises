<a id="readme-top"></a>

<div align="center">

[![Unlicense License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

</div>

# Dot Product

## Overview

This exercise was part of my SIMD learning process. The dot product is a common operation in many numerical applications, and implementing it using SIMD can lead to significant performance improvements. The goal was to implement the dot product using SIMD (Single Instruction, Multiple Data) instructions. The exercise was designed to help me understand how to leverage SIMD for performance improvements in numerical computations.

### Goals

- Implement the dot product using SIMD instructions.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Solution

The solution that was provided by the exercise is different than the one I used. I implemented the dot product using `_mm_hadd_ps` after multiplying the two vectors. This approach is more efficient than the one provided in the exercise, which uses manual shuffle.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Contact

REY Aurélien - [Website](http://www.epharos.fr/) - [Linked In][linkedin-url] - aur.rey30@gmail.com

Project Link: [https://github.com/Epharos/SIMD](https://github.com/Epharos/SIMD)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/Epharos/SIMD/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&color=0a66c2
[linkedin-url]: https://www.linkedin.com/in/aur%C3%A9lien-rey-b06039145/