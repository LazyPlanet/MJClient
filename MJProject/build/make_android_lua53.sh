export ANDROID_NDK=~/android-ndk-r10e
#export ANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-4.9
echo $ANDROID_NDK
echo $ANDROID_TOOLCHAIN_NAME

mkdir -p build_v7a && cd build_v7a
cmake -DANDROID_ABI=armeabi-v7a -DCMAKE_TOOLCHAIN_FILE=../cmake/android.toolchain.cmake -DANDROID_TOOLCHAIN_NAME=arm-linux-androideabi-clang3.6 -DANDROID_NATIVE_API_LEVEL=android-9 ../
cd ..
cmake --build build_v7a --config Release
cp build_v7a/libxlua.so plugin_lua53/Plugins/Android/libs/armeabi-v7a/libxlua.so

mkdir -p build_x86 && cd build_x86
cmake -DANDROID_ABI=x86 -DCMAKE_TOOLCHAIN_FILE=../cmake/android.toolchain.cmake -DANDROID_TOOLCHAIN_NAME=x86-clang3.5 -DANDROID_NATIVE_API_LEVEL=android-9 ../
cd ..
cmake --build build_x86 --config Release
cp build_x86/libxlua.so plugin_lua53/Plugins/Android/libs/x86/libxlua.so


