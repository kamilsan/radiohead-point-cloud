## Radiohead - Point cloud visualization

Interactive viewer of Thom Yorke singing House of Cards, represented as a point cloud.

![](https://i.imgur.com/WXu2YnW.png)

### Preparation

Download point cloud data from [this repository](https://github.com/dataarts/radiohead), extract archives and place .csv files to _data_ directory.

### Requirements

* libglfw3-dev
* CMake
* OpenGL 3.3 Core support

### Build

```
cmake .
make -j8
```

### Run

```
./app
```
