# 本项目是用C++以onnxruntime的方式部署YOLOX的前向推理模型

## 快速执行

cd 到yolox_onnxruntime_Cpp/build路径下，执行

```
cmake -DCMAKE_BUILD_TYPE=Realese .. && make -j4
```

进行编译

编译若成功，则在build路径下会出现一个test_infer,执行它进行测试，终端会打印检测结果的相关信息

```
./test_infer
```

可在yolox_onnxruntime_Cpp/img_out 路径下查看检测结果



## 依赖库安装

### 1.OpenCV(4.5.2)

下载原始文件  

```
mkdir ~/library && cd ~/library
wget https://github.com/opencv/opencv/archive/refs/tags/4.5.2.zip
unzip 4.5.2.zip
```

编译安装

```
cd opencv-4.5.2
mkdir build && cd build
cmake .. \
  -D CMAKE_BUILD_TYPE=Release \
  -D CMAKE_INSTALL_PREFIX=/usr/local \
  -D BUILD_TESTS=OFF \
  -D BUILD_PERF_TESTS=OFF \
  -D BUILD_opencv_python3=OFF \
  -D BUILD_opencv_python2=OFF \
  -D BUILD_SHARED_LIBS=ON \
  -D BUILD_opencv_apps=OFF \
make -j4
sudo make install
```

查询已安装OpenCV版本

```
opencv_version
> 4.5.2
```

### 2.ONNXRuntime(1.7.0)

下载官方构建的库

``` 
cd ~/library
wget https://github.com/microsoft/onnxruntime/releases/download/v1.7.0/onnxruntime-linux-x64-1.7.0.tgz
tar zxvf onnxruntime-linux-x64-1.7.0.tgz
```

查看lib下编译好的onnxruntime库

```
ls onnxruntime-linux-x64-1.7.0/lib
> libonnxruntime.so  libonnxruntime.so.1.7.0
```

### 3.Lite.Ai.ToolKit

下载原始文件

```
cd ~/library
git clone https://github.com/DefTruth/lite.ai.toolkit.git
```

复试自行编译的 opencv库到 lib/linux 之下

复制自行编译的 onnxruntime 库到 lib/linux 之下

```
cd lite.ai.toolkit
cp ~/library/opencv-4.5.2/build/lib/* lib/linux
cp ~/library/onnxruntime-linux-x64-1.7.0/lib/* lib/linux
```

编译lite.ai.toolkit

```
sh ./build.sh
```

执行测试样例

```
cd build/lite.ai.toolkit/bin
./lite_yolov5
```



### YOLOX infer API

将yolox_onnxruntime_Cpp放置到 ~/ 路径下

复制编译好的的 include 跟 lib 到yolox_onnxruntime_Cpp/lite.ai.toolkit 进行替换

```
mkdir lite.ai.toolkit
cp -r ~/library/lite.ai.toolkit/build/lite.ai.toolkit/include lite.ai.toolkit
cp -r ~/library/lite.ai.toolkit/build/lite.ai.toolkit/lib lite.ai.toolkit
```

设置环境变量

```
export LD_LIBRARY_PATH=~/yolox_onnxruntime_Cpp/lite.ai.toolkit/lib:$LD_LIBRARY_PATH
export LIBRARY_PATH=~/yolox_onnxruntime_Cpp/lite.ai.toolkit/lib:$LIBRARY_PATH
```

主程序为obj_infer.cpp，可通过

```
vim obj_infer.cpp
```

对代码进行修改，第5、6、7行为可修改的onnx文件路径、输入图像路径和输出图像的检测路径

vim 中键盘输入 **i** 进入编辑模式，完成修改后**Esc**退出编辑模式，**shift+z+z**保存并退出

编译

```
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Realese .. && make -j4
```

编译若成功，则在build路径下会出现一个test_infer,执行它进行测试

```
./test_infer
```

