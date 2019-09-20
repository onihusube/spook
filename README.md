# spook

spook is immediate functions library.

Immediate function is consteval function on C++20.

- header only
- type safe
- zero overhead on runtime
- no undefined behavior
- no supported compiler

To use it, `#include "include/spook.h"`.

### About building a test project

- Things necesary
  - [Meson](https://github.com/mesonbuild/meson)
  - Ninja (not Windows)
  - VC++2019 latest (Windows)

1. Change to the checked out directory
    - Within Windows, use *x64 Native Tools Command Prompt*
2. You can run `meson build`
    - Within Windows, `meson build --backend vs`
3. Change to the `./build` directory
4. You can run `ninja` or open VS Solution file(`spook.sln`).

### Welcome to your contribution!

- Function implementation
- Bug fix
- Feature suggestions
- And so on···
