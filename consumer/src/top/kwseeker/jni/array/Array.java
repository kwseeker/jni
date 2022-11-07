package top.kwseeker.jni.array;

/**
 * JNI 访问数组
 */
public class Array {

    static {
        System.loadLibrary("array");
    }

    /**
     * 基本类型数组
     */
    private native int sumArray(int[] arr);

    /**
     * 对象数组
     */
    private static native int[][] initInt2DArray(int size);

    public static void main(String[] args) {
        Array p = new Array();

        //1 固定长度数组
        int[] arr = new int[10];
        for (int i = 0; i < 10; i++) {
            arr[i] = i;
        }
        int sum = p.sumArray(arr);
        System.out.println("sum = " + sum);

        int[][] i2arr = initInt2DArray(3);
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; j++) {
                System.out.print(" " + i2arr[i][j]);
            }
            System.out.println();
        }
    }
}
