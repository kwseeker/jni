package top.kwseeker.jni.prompt;

public class Prompt {
    static {
        System.loadLibrary("prompt");
    }

    private native String getLine(String prompt);
    private native String getLine2(String prompt);

    public static void main(String[] args) {
        Prompt p = new Prompt();
        String input = p.getLine("Type a line: ");
        System.out.println("User typed: " + input);

        input = p.getLine2("Type a line 2: ");
        System.out.println("User typed: " + input);
    }
}