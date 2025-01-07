# sprite-sheet-sfml
___

Implementation of sprite based animations for character movement with SFML. All code resides in the `main.cpp` file.

## Tools used

| Name  | Version |
|-------|---------|
| CMake | 3.31.0  |
| g++   | 11.4.0  |
| SFML  | 3.0.0   |

------------------
## Running

Clone the source
```
https://github.com/abilondias/sprite-sheet-sfml.git
cd sprite-sheet-sfml
```

If the `build/debug` directory is missing
```
mkdir -p build/debug
```

Install dependencies and build
```
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug
cmake --build ./build/debug --target sprite_sheet_sfml
```

> In the ocasion of building issues, refer to [SFML's project and IDE setup](https://github.com/SFML/cmake-sfml-project?tab=readme-ov-file#how-to-use)  

Run
```
./build/debug/sprite_sheet_sfml
```
