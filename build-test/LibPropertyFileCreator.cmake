
    FILE(SHA1 "/tmp/workspace/xexes/sevenzipjbinding/build-test/jbinding-cpp/lib7-Zip-JBinding.so" HASH1)
    FILE(WRITE  "/tmp/workspace/xexes/sevenzipjbinding/build-test/Linux-amd64/sevenzipjbinding-lib.properties" "build.ref=9iSqtlhCYwZN\n\n")
    FILE(APPEND "/tmp/workspace/xexes/sevenzipjbinding/build-test/Linux-amd64/sevenzipjbinding-lib.properties" "lib.1.name=lib7-Zip-JBinding.so\n")
    FILE(APPEND "/tmp/workspace/xexes/sevenzipjbinding/build-test/Linux-amd64/sevenzipjbinding-lib.properties" "lib.1.hash=${HASH1}\n")
