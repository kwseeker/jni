package top.kwseeker.jni.field;

public class FieldAccess {

    static {
        System.loadLibrary("fieldAccess");
    }

    //静态字段
    private static int si;
    //实例字段
    private String s;

    private native void accessInstanceField();

    private native void accessStaticField();

    public static void main(String[] args) {
        FieldAccess c = new FieldAccess();

        //实例字段
        c.s = "abc";
        c.accessInstanceField();

        System.out.println("In Java:");
        System.out.println("2   c.s = \"" + c.s + "\"");

        //静态字段
        FieldAccess.si = 100;
        c.accessStaticField();
        System.out.println("In Java:");
        System.out.println("    FieldAccess.si = " + si);
    }
}
