# Cmake Learn
1. 使用Cmake

    1.1 项目文件目录结构
    
项目目录结构如下图，facedetect和facefeature都要用到opencl中的include文件,1.2,2.0,2.1是不同的opencl版本的头文件，  
希望在cmake创建Makefile时，opencl文件夹下的CMakeLists.txt能定义类似INCLUDE_OPENCL_1_2,INCLUDE_OPENCL_2_0,INCLUDE_OPENCL_2_1,这样的变量，以保存不同版本的opencl 头文件位置，    
最后关键是能让项目中其他子目录的CMakeList.txt能使用这些变量。
```c
├─facedetect
├─facefeature
└─opencl
    └─include
       ├─1.2
       │  └─CL
       ├─2.0
       │  └─CL
       └─2.1
           └─CL
```

2. 方法

   2.1. set:

一般用[set]1命令定义的变量能从父目录传递到子目录，  
但opencl与facedetect和facefeature在同级目录，所以用set定义的变量无法共享，  
要用set(variable value CACHE INTERNAL docstring )这种方式定义的变量会把变量加入到CMakeCache.txt然后各级目录共享会访问到这个变量  
比如:   
在opencl下的CMakeLists.txt中定义一个变量
```cmake
set(ICD_LIBRARY "${PROJECT_BINARY_DIR}/lib" CACHE INTERNAL "ICD Library location" )
//"ICD Library location"这个字符串相当于对变量的描述说明，不能省略，但可以自己随便定义
```  
在facedetect下的CMakeLists.txt中读取这个一个变量
```cmake
MESSAGE(STATUS "ICD_LIBRARY :${ICD_LIBRARY}")
```  
每次运行cmake都会更新这个变量，你会在CMakeCache.txt中找到这个变量
```cmake
//ICD Library location
ICD_LIBRARY:INTERNAL=J:/workspace/facecl.prj/lib
```  
2. set_property / get_property  

使用[set_property]2实现共享变量的方法，不会将变量写入CMakeCache.txt，应该是内存中实现的。   
当用set_property定义的property时，第一个指定作用域(scope)的参数设为GLOBAL，这个property在cmake运行期间作用域就是全局的。然后其他目录下的CMakeLists.txt可以用[get_property]3来读取这个property  


在opencl下的CMakeLists.txt中定义一个名为INCLUDE_OPENCL_1_2 的global property  
```cmake
set_property(GLOBAL PROPERTY INCLUDE_OPENCL_1_2 "${CMAKE_CURRENT_LIST_DIR}/include/1.2" )
```  
在facedetect下的CMakeLists.txt中读取这个一个property
```cmake
//先调用get_property将这个property读取到一个变量中(variable)INCLUDE_OPENCL 
get_property(INCLUDE_OPENCL GLOBAL PROPERTY "INCLUDE_OPENCL_1_2" ) 
//显示INCLUDE_OPENCL 
MESSAGE(STATUS "INCLUDE_OPENCL :${INCLUDE_OPENCL}")
```

上面的例子可以看出这种方式相比方法一在使用变量时多了一步，先要将先调用get_property将这个property读取到一个变量中(variable)才能使用。

Summary:  
两种方法相比，从使用便利性角度，方法一好一些，但方法一将变量保存在CMakeCache.txt，需要读写CMakeCache.txt文件，目前没有发现别的副作用，但记住这个区别是有好处的。   

3. CMake Library output directory Set  

   1. CMAKE_ARCHIVE_OUTPUT_DIRECTORY：默认存放静态库的文件夹位置
   2. CMAKE_LIBRARY_OUTPUT_DIRECTORY：默认存放动态库的文件夹位置
   3. LIBRARY_OUTPUT_PATH：默认存放库文件的位置，如果产生的是静态库并且没有指定 
   4. CMAKE_ARCHIVE_OUTPUT_DIRECTORY 则存放在该目录下，动态库也类似
   5. CMAKE_RUNTIME_OUTPUT_DIRECTORY：存放可执行软件的目录
