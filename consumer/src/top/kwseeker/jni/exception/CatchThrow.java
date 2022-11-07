package top.kwseeker.jni.exception;

public class CatchThrow {

    static {
        System.loadLibrary("CatchThrow");
    }

    private native void doIt() throws IllegalArgumentException;

    private void callback() throws NullPointerException {
        throw new NullPointerException("CatchThrow.callback");
    }

    public static void main(String[] args) {
        CatchThrow c = new CatchThrow();
        try {
            c.doIt();
        } catch (Exception e) {
            System.out.println("In Java:\n\t" + e);
        }
    }
}
