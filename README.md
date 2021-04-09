<div align="center">
  <img src="./logo.png" alt="">
  <blockquote>Sunrise Instrument FT Sensor's Cross-platform SDK</blockquote>
</div>


### Introduction

**_SRI FTSensor SDK_** is a cross-platform C++ wrappper of the FT Sensor made by Sunrise Instruments.

### Dependencies

***The SRI FTSensor SDK*** is a header-only library. But it depends on some Boost Libs.

* **Boost.Asio** Provide tcp, serial-port communication.

And aslo utilize some Boost header-only library, such as ***lexical_cast***, ***format*** and ***string_algo***.

if you are using Linux-like system (e.g. Ubuntu), Boost can be easily installed by package manager:

```bash
$ sudo apt install boost-all-dev
```

### Compile

You can just put all the header file(in the ***include*** directory) into your own project, and compile it. In the root directory, there has an example to show how to use this SDK. After installing the Boost library, you can just type the following command:

```bash
$ git clone https://github.com/thinkexist1989/SRI-FTSensor-SDK.git
$ cd SRI-FTSensor-SDK/
$ mkdir build && cd build
$ cmake ..
$ make -j`nproc`
$ ./test #Run the example
```

### Usage

1. Include the header files in your main.cpp

   ```c++
   #include <sri/ftsensor.hpp> 
   #include <sri/commethernet.hpp> // connection to the tcp-type FTSensor
   
   #include <iostream>
   
   int main() {
       ...
   }
   ```

2. Initialize the communication to FTSensor(I has a tcp-type sensor with ip 192.168.1.108)

   ```c++
   SRI::CommEthernet* ce = new SRI::CommEthernet("192.168.1.108", 4008);
   ```

3. Initialize the Sensor with communication

   ```
   SRI::FTSensor sensor(ce);
   ```

4. Get or set some parameters 

   ```
   IpAddr ip = sensor.getIpAddress();
   ```

5. Get real-time data from sensor

   ```c++
   auto rtData = sensor.getRealTimeDataOnce<float>(rtMode,rtDataValid);
   ```

### What to do next

- Serial Port :warning:unfinished
- CAN Bus :warning: unfinished

### Contributor

:bust_in_silhouette:**Yang Luo**  [Email: luoyang@sia.cn](mailto:luoyang@sia.cn)