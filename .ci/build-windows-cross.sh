#!/bin/bash
# The Windows x64 core, cross-built on Linux for the libretro buildbot, whose
# own Windows runner has MSVC 2019 16.8 - too old for Vita3K, which is C++23.
# clang-cl and lld-link (LLVM 21) against the MSVC CRT and Windows SDK that
# xwin downloads, so the result links against the same runtime as an MSVC
# build. Run from the repository root in ubuntu:24.04, as root:
#
#   BUILD_DIR=build/windows-x86_64 NUMPROC=8 .ci/build-windows-cross.sh
#
# leaves the core at $BUILD_DIR/vita3k_libretro.dll.
#
# The libraries vcpkg provides in the GitHub build come another way here:
# OpenSSL as the prebuilt MSVC package external/CMakeLists.txt downloads when
# it finds none, curl built from source by the same file, and Boost.Filesystem
# - the one compiled Boost library the core links - built below from the
# bundled Boost, as b2 cannot target Windows from a Linux host.

set -euo pipefail

BUILD_DIR=${BUILD_DIR:-build/windows-x86_64}
NUMPROC=${NUMPROC:-$(nproc)}
[ "$NUMPROC" -gt 0 ] || NUMPROC=1
TOOLS=${V3K_CROSS_TOOLS:-/opt/v3k-cross}
LLVM=/usr/lib/llvm-21/bin
XWIN_VERSION=0.10.0
SRC=$PWD

export DEBIAN_FRONTEND=noninteractive
apt-get update -qq
apt-get install -y --no-install-recommends \
  ca-certificates wget gnupg lsb-release software-properties-common \
  git python3 python3-venv ninja-build make file unzip xz-utils pkg-config perl
wget -qO- https://apt.llvm.org/llvm-snapshot.gpg.key > /etc/apt/trusted.gpg.d/apt.llvm.org.asc
apt-add-repository -y --no-update "deb http://apt.llvm.org/noble/ llvm-toolchain-noble-21 main"
apt-get update -qq
apt-get install -y --no-install-recommends \
  clang-21 clang-tools-21 lld-21 llvm-21 libclang-rt-21-dev
git config --global --add safe.directory '*'

# A current CMake; 24.04's pip wants a venv. Kept when TOOLS comes back from
# the buildbot's cache (V3K_CROSS_TOOLS, .gitlab-ci.yml).
mkdir -p "$TOOLS"
if [ ! -x "$TOOLS/venv/bin/cmake" ]; then
  python3 -m venv "$TOOLS/venv"
  "$TOOLS/venv/bin/pip" install -q --upgrade cmake
fi
export PATH="$TOOLS/venv/bin:$PATH"

# The MSVC CRT and the Windows SDK, fetched once for this xwin version
MSVC="$TOOLS/msvc"
if [ ! -f "$MSVC/.splat-$XWIN_VERSION" ]; then
  rm -rf "$MSVC"
  wget -q -O "$TOOLS/xwin.tar.gz" \
    "https://github.com/Jake-Shadle/xwin/releases/download/$XWIN_VERSION/xwin-$XWIN_VERSION-x86_64-unknown-linux-musl.tar.gz"
  tar -xzf "$TOOLS/xwin.tar.gz" -C "$TOOLS" --strip-components=1
  "$TOOLS/xwin" --accept-license --arch x86_64 --cache-dir "$TOOLS/xwin-cache" \
    splat --output "$MSVC"
  rm -rf "$TOOLS/xwin-cache" "$TOOLS/xwin.tar.gz"
  touch "$MSVC/.splat-$XWIN_VERSION"
fi

# Headers the sources name in another case than the SDK's files (<Windows.h>
# for windows.h): a link of that spelling next to each
python3 - "$MSVC" <<'PY'
import os, re, sys
root = sys.argv[1]
dirs = [os.path.join(root, d) for d in ("crt/include", "sdk/include/ucrt",
        "sdk/include/um", "sdk/include/shared", "sdk/include/winrt")]
files = {}
for d in dirs:
    for name in os.listdir(d):
        files.setdefault(name.lower(), (d, name))
wanted = set()
pattern = re.compile(rb'#\s*include\s*[<"]([A-Za-z0-9_]+\.[hH])[>"]')
for top in ("vita3k", "external"):
    for base, _, names in os.walk(top):
        for n in names:
            if n.endswith((".h", ".hpp", ".c", ".cc", ".cpp", ".inl", ".ipp")):
                try:
                    data = open(os.path.join(base, n), "rb").read()
                except OSError:
                    continue
                wanted.update(m.decode() for m in pattern.findall(data))
made = 0
for name in wanted:
    hit = files.get(name.lower())
    if hit and hit[1] != name and not os.path.exists(os.path.join(hit[0], name)):
        os.symlink(hit[1], os.path.join(hit[0], name))
        made += 1
print(f"case links: {made}")
# and libraries asked for with a capital (Version.lib for version.lib)
libs = 0
for d in ("sdk/lib/um/x86_64", "sdk/lib/ucrt/x86_64", "crt/lib/x86_64"):
    d = os.path.join(root, d)
    for name in os.listdir(d):
        if name.endswith(".lib") and name == name.lower():
            cap = name[0].upper() + name[1:]
            if not os.path.lexists(os.path.join(d, cap)):
                os.symlink(name, os.path.join(d, cap))
                libs += 1
print(f"library case links: {libs}")
PY

# clang-cl with the headers, for what is compiled outside CMake
mkdir -p "$TOOLS/bin"
cat > "$TOOLS/bin/clang-cl" <<WRAPPER
#!/bin/sh
exec "$LLVM/clang-cl" --target=x86_64-pc-windows-msvc -fuse-ld=lld \\
  -Wno-unused-command-line-argument \\
  /imsvc "$MSVC/crt/include" /imsvc "$MSVC/sdk/include/ucrt" \\
  /imsvc "$MSVC/sdk/include/um" /imsvc "$MSVC/sdk/include/shared" \\
  /imsvc "$MSVC/sdk/include/winrt" "\$@"
WRAPPER
chmod +x "$TOOLS/bin/clang-cl"

TOOLCHAIN="$TOOLS/clang-cl-x86_64.cmake"
cat > "$TOOLCHAIN" <<EOF
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_VERSION 10.0)
set(CMAKE_SYSTEM_PROCESSOR AMD64)
set(CMAKE_C_COMPILER "$LLVM/clang-cl")
set(CMAKE_CXX_COMPILER "$LLVM/clang-cl")
set(CMAKE_C_COMPILER_TARGET x86_64-pc-windows-msvc)
set(CMAKE_CXX_COMPILER_TARGET x86_64-pc-windows-msvc)
set(CMAKE_LINKER "$LLVM/lld-link")
set(CMAKE_AR "$LLVM/llvm-lib")
set(CMAKE_RC_COMPILER "$LLVM/llvm-rc")
set(CMAKE_MT "$LLVM/llvm-mt")
set(V3K_CLANG_CL_INCLUDES
  "$MSVC/crt/include" "$MSVC/sdk/include/ucrt" "$MSVC/sdk/include/um"
  "$MSVC/sdk/include/shared" "$MSVC/sdk/include/winrt")
set(V3K_CLANG_CL_LIBS
  "$MSVC/crt/lib/x86_64" "$MSVC/sdk/lib/um/x86_64" "$MSVC/sdk/lib/ucrt/x86_64")
set(_v3k_includes "")
set(_v3k_rc_includes "")
foreach(_v3k_dir IN LISTS V3K_CLANG_CL_INCLUDES)
  string(APPEND _v3k_includes " /imsvc \"\${_v3k_dir}\"")
  string(APPEND _v3k_rc_includes " /I \"\${_v3k_dir}\"")
endforeach()
# BOOST_ALL_NO_LIB: Boost's headers would otherwise ask the linker for a
# library named after the toolset (auto-linking); the one built here is
# linked by its path
set(_v3k_flags "-Wno-unused-command-line-argument -DBOOST_ALL_NO_LIB\${_v3k_includes}")
set(_v3k_link "/manifest:no")
foreach(_v3k_dir IN LISTS V3K_CLANG_CL_LIBS)
  string(APPEND _v3k_link " /libpath:\"\${_v3k_dir}\"")
endforeach()
set(CMAKE_C_FLAGS_INIT "\${_v3k_flags}")
set(CMAKE_CXX_FLAGS_INIT "\${_v3k_flags}")
set(CMAKE_RC_FLAGS_INIT "\${_v3k_rc_includes}")
set(CMAKE_EXE_LINKER_FLAGS_INIT "\${_v3k_link}")
set(CMAKE_SHARED_LINKER_FLAGS_INIT "\${_v3k_link}")
set(CMAKE_MODULE_LINKER_FLAGS_INIT "\${_v3k_link}")
# find_library(ws2_32 ...) and the like look here
set(CMAKE_LIBRARY_PATH \${V3K_CLANG_CL_LIBS})
# The release CRT only: xwin fetches no debug runtime, and the compiler
# checks would otherwise link msvcrtd
set(CMAKE_TRY_COMPILE_CONFIGURATION Release)
set(CMAKE_MSVC_RUNTIME_LIBRARY MultiThreadedDLL)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
EOF

# Boost.Filesystem from the bundled Boost, as a static library, with the
# package files find_package(Boost ... PATHS <build>/external/boost) reads
BOOST_SRC="$SRC/external/boost"
BOOST_OUT="$SRC/$BUILD_DIR/external/boost"
BOOST_VER=$(sed -n 's/^#define BOOST_LIB_VERSION "\([0-9]*\)_\([0-9]*\)"/\1.\2.0/p' "$BOOST_SRC/boost/version.hpp")
mkdir -p "$BOOST_OUT/lib" "$BOOST_OUT/obj"
# C++20: Boost.Filesystem takes std::atomic_ref unless its build system found
# it missing
boost_pids=()
for f in codecvt_error_category directory exception operations path path_traits \
         portability unique_path utf8_codecvt_facet windows_file_codecvt; do
  "$TOOLS/bin/clang-cl" /nologo /c /std:c++20 /EHsc /MD /O2 /DNDEBUG \
    /DBOOST_ALL_NO_LIB /DBOOST_FILESYSTEM_STATIC_LINK=1 /DBOOST_FILESYSTEM_SOURCE \
    /D_CRT_SECURE_NO_WARNINGS /D_SCL_SECURE_NO_WARNINGS \
    /I "$BOOST_SRC" /I "$BOOST_SRC/libs/filesystem/src" \
    "/Fo$BOOST_OUT/obj/$f.obj" "$BOOST_SRC/libs/filesystem/src/$f.cpp" &
  boost_pids+=($!)
done
for pid in "${boost_pids[@]}"; do wait "$pid"; done
ls "$BOOST_OUT/obj"
"$LLVM/llvm-lib" /nologo "/out:$BOOST_OUT/lib/boost_filesystem.lib" "$BOOST_OUT"/obj/*.obj
cat > "$BOOST_OUT/BoostConfigVersion.cmake" <<EOF
set(PACKAGE_VERSION "$BOOST_VER")
if(PACKAGE_FIND_VERSION VERSION_GREATER PACKAGE_VERSION)
  set(PACKAGE_VERSION_COMPATIBLE FALSE)
else()
  set(PACKAGE_VERSION_COMPATIBLE TRUE)
endif()
EOF
cat > "$BOOST_OUT/BoostConfig.cmake" <<EOF
# Written by .ci/build-windows-cross.sh: the bundled Boost's headers and the
# Boost.Filesystem built from them
if(NOT TARGET Boost::headers)
  add_library(Boost::headers INTERFACE IMPORTED)
  set_target_properties(Boost::headers PROPERTIES
    INTERFACE_INCLUDE_DIRECTORIES "$BOOST_SRC"
    INTERFACE_COMPILE_DEFINITIONS "BOOST_ALL_NO_LIB")
  add_library(Boost::boost INTERFACE IMPORTED)
  set_target_properties(Boost::boost PROPERTIES INTERFACE_LINK_LIBRARIES Boost::headers)
  add_library(Boost::filesystem STATIC IMPORTED)
  set_target_properties(Boost::filesystem PROPERTIES
    IMPORTED_LOCATION "$BOOST_OUT/lib/boost_filesystem.lib"
    INTERFACE_COMPILE_DEFINITIONS "BOOST_FILESYSTEM_STATIC_LINK=1"
    INTERFACE_LINK_LIBRARIES "Boost::headers;bcrypt")
endif()
set(Boost_FOUND TRUE)
set(Boost_VERSION "$BOOST_VER")
set(Boost_VERSION_STRING "$BOOST_VER")
set(Boost_INCLUDE_DIRS "$BOOST_SRC")
set(Boost_LIBRARIES Boost::filesystem)
set(Boost_filesystem_FOUND TRUE)
set(Boost_FILESYSTEM_FOUND TRUE)
set(Boost_FILESYSTEM_LIBRARY Boost::filesystem)
EOF

# zlib from the sources psvpfstools carries. Left to itself, psvpfstools links
# the zlibstaticd.lib committed next to them: a debug build, which wants the
# debug runtime (MSVCRTD.lib) that is not here, and does not belong in a
# release core anyway.
ZLIB_SRC="$SRC/external/psvpfstools/zlib"
ZLIB_OUT="$SRC/$BUILD_DIR/external/zlib-static"
mkdir -p "$ZLIB_OUT/obj"
zlib_pids=()
for f in adler32 compress crc32 deflate gzclose gzlib gzread gzwrite infback \
         inffast inflate inftrees trees uncompr zutil; do
  "$TOOLS/bin/clang-cl" /nologo /c /MD /O2 /DNDEBUG /D_CRT_SECURE_NO_WARNINGS \
    /D_CRT_NONSTDC_NO_DEPRECATE -Wno-everything /I "$ZLIB_SRC" \
    "/Fo$ZLIB_OUT/obj/$f.obj" "$ZLIB_SRC/$f.c" &
  zlib_pids+=($!)
done
for pid in "${zlib_pids[@]}"; do wait "$pid"; done
"$LLVM/llvm-lib" /nologo "/out:$ZLIB_OUT/zlibstatic.lib" "$ZLIB_OUT"/obj/*.obj

# OpenSSL as static libraries, where external/CMakeLists.txt looks for the
# ones its Windows libretro build makes with nmake and a Windows Perl, neither
# of which is here. The same version, configured as OpenSSL's GNU-make Windows
# target and compiled by clang for the MSVC ABI and the DLL runtime, so the
# objects link like MSVC's. No assembly: that target's is written for the GNU
# assembler's MinGW conventions.
OPENSSL_VERSION=3.6.1
OPENSSL_OUT="$SRC/$BUILD_DIR/external/openssl-static/x64"
if [ ! -f "$OPENSSL_OUT/lib/libssl.lib" ]; then
  mkdir -p "$TOOLS/openssl"
  wget -q -O "$TOOLS/openssl.tar.gz" \
    "https://github.com/openssl/openssl/releases/download/openssl-$OPENSSL_VERSION/openssl-$OPENSSL_VERSION.tar.gz"
  tar -xzf "$TOOLS/openssl.tar.gz" -C "$TOOLS/openssl" --strip-components=1
  cat > "$TOOLS/bin/clang-msvc" <<WRAPPER
#!/bin/sh
exec "$LLVM/clang" --target=x86_64-pc-windows-msvc -fms-runtime-lib=dll \\
  -Wno-unused-command-line-argument -Wno-everything \\
  -isystem "$MSVC/crt/include" -isystem "$MSVC/sdk/include/ucrt" \\
  -isystem "$MSVC/sdk/include/um" -isystem "$MSVC/sdk/include/shared" "\$@"
WRAPPER
  chmod +x "$TOOLS/bin/clang-msvc"
  (
    cd "$TOOLS/openssl"
    CC="$TOOLS/bin/clang-msvc" AR="$LLVM/llvm-ar" RANLIB="$LLVM/llvm-ranlib" \
      perl Configure mingw64 no-shared no-tests no-apps no-docs no-asm \
        "--prefix=$OPENSSL_OUT" "--openssldir=$OPENSSL_OUT" --libdir=lib
    make -j "$NUMPROC" build_libs > "$TOOLS/openssl-build.log" 2>&1 || { tail -60 "$TOOLS/openssl-build.log"; exit 1; }
    make install_dev > /dev/null
  )
  # under the names the MSVC build's check and find_package look for
  cp "$OPENSSL_OUT/lib/libssl.a" "$OPENSSL_OUT/lib/libssl.lib"
  cp "$OPENSSL_OUT/lib/libcrypto.a" "$OPENSSL_OUT/lib/libcrypto.lib"
  ls -la "$OPENSSL_OUT/lib" "$OPENSSL_OUT/lib/cmake/OpenSSL" || true
fi

cmake -S . -B "$BUILD_DIR" -G Ninja -DCMAKE_BUILD_TYPE=Release \
  -DCMAKE_TOOLCHAIN_FILE="$TOOLCHAIN" \
  -DCMAKE_POLICY_VERSION_MINIMUM=3.5 \
  -DBUILD_LIBRETRO=ON -DVITA3K_FORCE_CUSTOM_BOOST=ON \
  -DUSE_DISCORD_RICH_PRESENCE=OFF \
  -DZLIB_LIBRARY="$ZLIB_OUT/zlibstatic.lib" -DZLIB_INCLUDE_DIR="$ZLIB_SRC"
export PATH="$LLVM:$PATH"
cmake --build "$BUILD_DIR" --target vita3k_libretro -- -j "$NUMPROC" ${V3K_CROSS_KEEP_GOING:+-k 0}
mv "$(find "$BUILD_DIR" -name vita3k_libretro.dll | head -1)" "$BUILD_DIR/vita3k_libretro.dll"
file "$BUILD_DIR/vita3k_libretro.dll"
"$LLVM/llvm-objdump" -p "$BUILD_DIR/vita3k_libretro.dll" | grep 'DLL Name' | sort -u
