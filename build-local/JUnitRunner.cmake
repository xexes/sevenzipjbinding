STRING(REPLACE "%3D" "=" JAVA_OPT_TO_USE "${JAVA_OPT}")
                                     EXECUTE_PROCESS(COMMAND
                                            "/bin/java" -Xmx512m -cp "/tmp/workspace/xexes/sevenzipjbinding/test/JavaTests/lib/junit-4.11.jar:/tmp/workspace/xexes/sevenzipjbinding/test/JavaTests/lib/hamcrest-core-1.3.jar:/tmp/workspace/xexes/sevenzipjbinding/build-local/jbinding-java/sevenzipjbinding-tests.jar:/tmp/workspace/xexes/sevenzipjbinding/build-local/jbinding-java/sevenzipjbinding.jar:/tmp/workspace/xexes/sevenzipjbinding/build-local/sevenzipjbinding-Linux-amd64.jar"
                                            "-DSINGLEBUNDLE=${SINGLEBUNDLE}" ${JAVA_OPT_TO_USE} ${RUNTIME_JAVA_OPTS} "-Dskip-debug-mode-tests=true" org.junit.runner.JUnitCore net.sf.sevenzipjbinding.junit.AllTestSuite
                                            WORKING_DIRECTORY /tmp/workspace/xexes/sevenzipjbinding/test/JavaTests/src/..
                                            RESULT_VARIABLE RESULT)
                                     IF(RESULT)
                                         MESSAGE(SEND_ERROR "Error during JUnit Tests. Return code: ${RESULT}")
                                     ENDIF(RESULT)
                                     