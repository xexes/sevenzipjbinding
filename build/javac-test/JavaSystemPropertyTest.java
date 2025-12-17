
public class JavaSystemPropertyTest {
    public static void main(String args[]) {
        String property = System.getProperty(args[0]);
        System.out.print(property.split(" ")[0]);
    }
}