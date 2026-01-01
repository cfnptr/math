# Math

A [library](https://github.com/cfnptr/math) providing common linear algebra math operations.

See the [documentation](https://cfnptr.github.io/math).

## Features

* Vector (float2/3/4, int2/3/4, half)
* Matrix (float2x2/3x3/4x4)
* Quaternion (float4)
* SIMD optimized (f32x4, f32x4x4, f16x4)
* Euler angles/radians conversion
* Matrix translate, scale, rotate
* Pespective, orthographics projection
* Ray, line, plane, triangle, sphere...
* Axis aligned bounding box (AABB)
* Frustum culling, matrix extraction
* Bounding volume hierarchy (BVH)
* Color conversion (RGBA, linear)
* Version (major, minor, patch, build)
* Hexadecimal string conversion
* Packed vector (1bit container)
* Tone mapping, gamma correction
* Image based lighting (IBL, BRDF)
* Spherical harmonics (SH)
* Enum class flags declaration
* Simplified integer types (int64, uint32, int8...)

## Supported operating systems

* Windows (10/11)
* Ubuntu (22.04/24.04)
* macOS (15/26)

This list includes only those systems on which functionality testing is conducted.
However, you can also compile it under any other Linux distribution or operating system.

## Build requirements

* C++17 compiler
* [Git 2.30+](https://git-scm.com/)
* [CMake 3.16+](https://cmake.org/)

Use building [instructions](BUILDING.md) to install all required tools and libraries.

### CMake options

| Name              | Description               | Default value |
|-------------------|---------------------------|---------------|
| MATH_BUILD_SHARED | Build Math shared library | `ON`          |
| MATH_BUILD_TESTS  | Build Math library tests  | `ON`          |

### CMake targets

| Name        | Description          | Windows | macOS    | Linux |
|-------------|----------------------|---------|----------|-------|
| math-static | Static Math library  | `.lib`  | `.a`     | `.a`  |
| math-shared | Dynamic Math library | `.dll`  | `.dylib` | `.so` |

## Cloning

```
git clone https://github.com/cfnptr/math
```

## Building ![CI](https://github.com/cfnptr/math/actions/workflows/cmake.yml/badge.svg)

* Windows: ```./scripts/build-release.bat```
* macOS / Ubuntu: ```./scripts/build-release.sh```

### Inspired by

* [GLM](https://github.com/g-truc/glm/)
* [3DCollisions](https://gdbooks.gitbooks.io/3dcollisions/content/)
* [Filament](https://github.com/google/filament/)
* [JoltPhysics](https://github.com/jrouwe/JoltPhysics)
* [SLEEF](https://github.com/shibatch/sleef)
