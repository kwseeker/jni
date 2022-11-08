package top.kwseeker.jni.method;

public class MethodCall extends Task {

    static {
        System.loadLibrary("methodCall");
        initIDs();
    }

    /**
     * 这个本地方法只是用于指明后面的native方法要调用的普通方法
     */
    private static native void initIDs();

    /**
     * 本地方法调用实例方法 callback
     */
    private native void nativeMethod();

    /**
     * 本地方法调用静态方法 staticCallback
     */
    private static native void nativeStaticMethod();

    /**
     * 本地方法调用父类实例方法
     */
    private native void nativeCallPMethod();

    /**
     * 本地方法调用构造函数，比如调用 java.lang.String 的构造方法新建一个字符串
     */
    private native String nativeNewString(String str);


    /**
     * 测试调用父类方法
     */
    @Override
    public void run() {
        System.out.println("Override parent method run() In Java");
    }

    // JNI 中对 callback 方法的调用是通过方法名写死了的
    private void callback() {
        System.out.println("callback() In Java");
    }

    // JNI 中对 staticCallback 方法的调用是通过方法名写死了的
    private static void staticCallback(){
        System.out.println("staticCallback() In Java");
    }

    public static void main(String[] args) {
        MethodCall c = new MethodCall();
        c.nativeMethod();
        nativeStaticMethod();
        c.nativeCallPMethod();
        String str = c.nativeNewString("Hello");
        System.out.println("In Java: " + str);
    }
}
