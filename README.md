<a id="readme-top"></a>

<div align="center">

[![Unlicense License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]

</div>

# SIMD Exercises

This repository holds every exercises I made while learning about SIMD (Single Instruction, Multiple Data).

This is not a project as such but more of a showcase of what I worked on in order to learn new things and improve my code quality.

### Built with

This repository was built using

![cpp-shield] ![vs-shield]

# Exercises summary

Each exercise is contained within its own subfolder of `src`. They all have their own `README.md` to explain the exercise deeper and display how I solved it.

In order to make the navigation better here is a quick summary of those said exercises :

## Load and Save

*Load and Save* is the very first exercise I did. The goal was to get familiar with `_mm_load_ps` and `_mm_store_ps` functions and understand the basics of SIMD.

## Basic Arithmetics

*Basic Arithmetics* was a necessity of SIMD. It introduces how `_mm_add_ps` (addition), `_mm_mul_ps` (multiplication), ... and others arithmetical operations were handled using SIMD and vectorized operations. 

<!---All the following operations were tested and profiled compared to a scalar, more classical, approach :
- Addition
- Substraction
- Multiplication
- Division
- Square root
- Reciprocal

All of these were tested on floats (32 bits) and integers (32 bits). -->

## Dot Product

I feel like this one is an obvious exercise in order to really understand the power of SIMD. *Dot product* is, as the name implies, the dot product of two four-dimensional vectors. It's the first practical use of previously seen operations and the introduction of `_mm_hadd_ps` and `_mm_dp_ps`.

## Min Max

*MinMax* introduces new intrinsics such as `_mm_min_ps`, `_mm_max_ps` and the `_mm_set1_ps` macro in order to look for the min and max values in an array of values.

## MatMulVec

Behind that weird name, the goal of that exercise was to use previously seen functions to multiply a 4x4 matrix with a 4-dimensionnal vector. I used that exercice to introduce myself to AVX syntax and way of thinking (since my CPU is compatible), but it also introduces to `_mm256_set_m128` macro and masks (with `_mm256_dp_ps`).

## Matrix

The *Matrix* exercise is a necessity to truly understand how powerful SIMD is if you know how to use it properly. The goal is to perform a multiplication between two 4x4 matrices.

I used that exercise to improve my understanding of AVX and leverage the 256 bits registers by batching matrices in order to process 8 of them at a time, which proved to process in just 1/9th of the time it took the scalar version.



[license-shield]: https://img.shields.io/github/license/othneildrew/Best-README-Template.svg?style=for-the-badge
[license-url]: https://github.com/Epharos/SIMD/blob/master/LICENSE.txt
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&color=0a66c2
[linkedin-url]: https://www.linkedin.com/in/aur%C3%A9lien-rey-b06039145/
[cpp-shield]: https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white
[vs-shield]: https://img.shields.io/badge/Visual_Studio-5C2D91?style=for-the-badge&logo=visual%20studio&logoColor=white