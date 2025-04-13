<a id="readme-top"></a>

<div align="center">

[![Unlicense License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

</div>

# Min Max

## Overview

This exercise aims at profiling the performance between a scalar implementation and a SIMD implementation when it comes to searching for the minimum and maximum values in an array of floats.

### Goals

- Learning new SIMD intrinsics

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Solution

I believe for this exercise the code speaks for itself. I just used `_mm_min_ps` and `_mm_max_ps` to compute the minimum and maximum values of 4 floats at a time.

<p align="right">(<a href="#readme-top">back to top</a>)</p>

## Contact

REY Aurélien - [Website](http://www.epharos.fr/) - [Linked In][linkedin-url] - aur.rey30@gmail.com

Project Link: [https://github.com/Epharos/SIMD](https://github.com/Epharos/SIMD)

<p align="right">(<a href="#readme-top">back to top</a>)</p>

[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/Epharos/SIMD/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&color=0a66c2
[linkedin-url]: https://www.linkedin.com/in/aur%C3%A9lien-rey-b06039145/