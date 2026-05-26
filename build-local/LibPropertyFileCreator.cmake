
    FILE(SHA1 "/tmp/workspace/xexes/sevenzipjbinding/build-local/jbinding-cpp/lib7-Zip-JBinding.so" HASH1)
    FILE(WRITE  "/tmp/workspace/xexes/sevenzipjbinding/build-local/Linux-amd64/sevenzipjbinding-lib.properties" "build.ref=UFl54REgeyWU\n\n")
    FILE(APPEND "/tmp/workspace/xexes/sevenzipjbinding/build-local/Linux-amd64/sevenzipjbinding-lib.properties" "lib.1.name=lib7-Zip-JBinding.so\n")
    FILE(APPEND "/tmp/workspace/xexes/sevenzipjbinding/build-local/Linux-amd64/sevenzipjbinding-lib.properties" "lib.1.hash=${HASH1}\n")
