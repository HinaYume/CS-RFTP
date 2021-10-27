# 專案建置教學

### 1. clone llvm source code：
```
git clone https://github.com/llvm/llvm-project.git -b release/5.x
```
### 2. 將四個資料夾分別覆蓋、貼上至llvm source code之下
  * include → llvm-project/clang
  * lib → llvm-project/clang
  * libclang → llvm-project/clang/tools
  * Vote → llvm-project/clang-tools-extra

### 3. 將CMakeLists.txt覆蓋至llvm-project/clang-tools-extra之下（與Vote同一層）
  * 或是編輯llvm-project/clang-tools-extra之下的CMakeLists.txt
```
add_subdirectory(tool-template)
add_subdirectory(Vote/For_Fork)
```

### 4 編譯llvm
 e.g.
 
```
cd $LLVM_BUILD
```

```
cmake -DCLANG_OPENMP_NVPTX_DEFAULT_ARCH=sm_37 -DLIBOMPTARGET_NVPTX_COMPUTE_CAPABILITIES=37,60,70 \
-DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;openmp" \
-DLLVM_USE_LINKER=gold -DLLVM_USE_SPLIT_DWARF=ON \
-DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ $LLVM_SRC/llvm
```

```
make -j8
```

### 5. 將編譯完成的bin檔複製到/usr/bin之中
  e.g. 

```
sudo cp $LLVM_BUILD/bin/For_Fork /usr/bin
```

# For_Fork使用教學

### 1. 使用Compiler directive規定相關參數以及受保護區間

```c
#pragma protect("MonitorVoting") voteMethod target(("varName","varType"),...) monitor("mode or threshold","mode") dep(("varName","varType"),...)
{
 // protected scope.
}
```

e.q.

```c
#pragma protect("MonitorVoting") multiprocess target(("pi","float"),("e","float")) monitor("5","abnormal") dep(("n","float"),("s","float"),("r","int"),("x","float"))
{
 // protected scope.
}
```
### 2. 使用For_Fork將目標程式碼轉換為Fault-tolerant code

```
For_Fork targetProgram --> faultTolerantProgram
```

e.g.

```
For_Fork matrix1.cpp --> matrix1_FT.c
```

### 3. 編譯並執行轉換過的Fault-tolerant code

e.g. 

`gcc matrix1_FT.c -o matrix_FT`

`./matrix_FT`

※ 若是voteMethod選擇multithread的情況下，編譯則須加上-fopenmp的參數

e.g.

`gcc -fopenmp matrix1_FT.c -o matrix_FT`

