rm LostKey
cd openssl-1.1.0f
CC=clang ./Configure no-shared -m32 linux-generic32 -O0
make -j 16 all
cd ..
clang -s -static -m32 lost_key.c rop.c -L openssl-1.1.0f -l:libcrypto.a -oLostKey
cd openssl-1.1.0f
make clean
cd ..
