# TODO: NDK path to be configured.
NDK     = ./android-ndk-r26b
SYSROOT = $(NDK)/toolchains/llvm/prebuilt/linux-x86_64/sysroot
TARGET  = aarch64-none-linux-android33
ANDROID_JAR = ./android.jar # todo: configure
cc      = $(NDK)/toolchains/llvm/prebuilt/linux-x86_64/bin/clang

default:
	@mkdir -p build
	-rm MyProject.apk MyProject.apk.unaligned
	$(cc) --target=$(TARGET) --sysroot=$(SYSROOT) -g -DANDROID -fPIC -o build/main.c.o -c ./main.c
	$(cc) --target=$(TARGET) --sysroot=$(SYSROOT) -fPIC -g -DANDROID -static-libstdc++ -Wl,--build-id=sha1 -Wl,--no-undefined-version -Wl,--fatal-warnings -Wl,--no-undefined -Qunused-arguments  -shared -Wl,-soname,libMyProject.so -o build/lib/arm64-v8a/libMyProject.so build/main.c.o  -llog -latomic -lm -lGLESv2
	aapt package -f -M ./AndroidManifest.xml -S res/ -I $(ANDROID_JAR) -F MyProject.apk.unaligned
	cd build && aapt add -v ../MyProject.apk.unaligned lib/arm64-v8a/MyProject.so
	zipalign 4 MyProject.apk.unaligned MyProject.apk
	echo "plaintext password" | apksigner sign --ks your_keystore.keystore MyProject.apk
	adb install -r MyProject.apk
