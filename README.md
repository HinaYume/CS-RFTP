# 專案建置教學

### clone llvm source code：
    git clone https://github.com/llvm/llvm-project.git -b release/5.x
  
### 將四個資料夾分別覆蓋貼上至llvm source code
  * include → llvm-project/clang
  * lib → llvm-project/clang
  * libclang → llvm-project/clang/tools
  * Vote → llvm-project/clang-tools-extra

### 編譯llvm
 e.g.
 
    cd $LLVM_BUILD`

    cmake -DCLANG_OPENMP_NVPTX_DEFAULT_ARCH=sm_37 -DLIBOMPTARGET_NVPTX_COMPUTE_CAPABILITIES=37,60,70 \
    -DLLVM_ENABLE_PROJECTS="clang;clang-tools-extra;openmp" \
    -DLLVM_USE_LINKER=gold -DLLVM_USE_SPLIT_DWARF=ON \
    -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ $LLVM_SRC/llvm
    
    make -j8

### 將編譯完成的bin檔複製到/usr/bin之中
  e.g. 

    sudo cp $LLVM_BUILD/bin/For_Fork /usr/bin

# For_Fork使用教學



