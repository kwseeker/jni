package top.kwseeker.jni.method;

public class MethodCall {

    static {
        System.loadLibrary("methodCall");
        initIDs();
    }

    private static native void initIDs();

    /**
     * 本地方法调用实例方法 callback
     */
    private native void nativeMethod();

    /**
     * 本地方法调用静态方法 staticCallback
     */
    private native void nativeStaticMethod();

    /**
     * 本地方法调用父类实例方法
     */

    /**
     * 本地方法调用构造函数
     */



    private void callback() {
        System.out.println("callback() In Java");
    }

    private static void staticCallback(){
        System.out.println("staticCallback() In Java");
    }

    public static void main(String[] args) {
        MethodCall c = new MethodCall();
        c.nativeMethod();
    }
}
