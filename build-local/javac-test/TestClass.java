
public class TestClass {
    private static class Java15Test<T> {
        void doIt(T t) {t.toString();}
    }
    public static void main(String args[]) {
        new Java15Test<String>().doIt("Hello World");
        System.out.print(System.getProperty("os.arch"));
    }
}