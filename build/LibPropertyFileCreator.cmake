
    FILE(SHA1 "/home/runner/work/sevenzipjbinding/sevenzipjbinding/build/jbinding-cpp/lib7-Zip-JBinding.so" HASH1)
    FILE(WRITE  "/home/runner/work/sevenzipjbinding/sevenzipjbinding/build/Linux-amd64/sevenzipjbinding-lib.properties" "build.ref=aHoiYbETGutY\n\n")
    FILE(APPEND "/home/runner/work/sevenzipjbinding/sevenzipjbinding/build/Linux-amd64/sevenzipjbinding-lib.properties" "lib.1.name=lib7-Zip-JBinding.so\n")
    FILE(APPEND "/home/runner/work/sevenzipjbinding/sevenzipjbinding/build/Linux-amd64/sevenzipjbinding-lib.properties" "lib.1.hash=${HASH1}\n")
