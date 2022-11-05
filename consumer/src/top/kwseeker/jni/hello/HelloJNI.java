package top.kwseeker.jni.hello;

/**
 * 由于jni本地库没有放在系统默认的库目录，需要用“java.library.path”指定
 * -Djava.library.path=/home/lee/mywork/java/jni/consumer/lib
 */
public class HelloJNI {
    static {
        System.loadLibrary("hello"); // Load native library hello.dll (Windows) or libhello.so (Unixes)
    }

    // Declare an instance native method sayHello() which receives no parameter and returns void
    private native void sayHello();

    // Test Driver
    public static void main(String[] args) {
        new HelloJNI().sayHello();  // Create an instance and invoke the native method
    }
}
