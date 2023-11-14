# Math ![CI](https://github.com/cfnptr/math/actions/workflows/cmake.yml/badge.svg)

A library providing common linear algebra math operations.

## Features

* Vector (float2/3/4, int2/3/4)
* Matrix (float2x2/3x3/4x4)
* Quaternion (float4)
* Euler Angles, Radians
* Axis Aligned Bounding Box (AABB)
* Ray, Line, Plane, Triangle, Sphere
* BRDF, IBL, Spherical Harmonics
* Bounding Volume Hierarchy (BVH)
* Pespective, Orthographics projection.
* Matrix translate, scale, rotate.

## Supported operating systems

* Ubuntu
* MacOS
* Windows

## Build requirements

* C++17 compiler
* [Git 2.30+](https://git-scm.com/)
* [CMake 3.16+](https://cmake.org/)

### CMake options

| Name              | Description               | Default value |
|-------------------|---------------------------|---------------|
| MATH_BUILD_SHARED | Build Math shared library | `ON`          |
| MATH_BUILD_TESTS  | Build Math library tests  | `ON`          |

## Cloning

```
git clone https://github.com/cfnptr/math
```

### Inspired by

* [GLM](https://github.com/g-truc/glm/)
* [3DCollisions](https://gdbooks.gitbooks.io/3dcollisions/content/)
* [Filament](https://github.com/google/filament/)