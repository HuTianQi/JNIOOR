package tech.huqi.jnioor;

/**
 * Created by hzhuqi on 2019/6/25
 */
public class Sample {
    private static final String TAG = "JniReflectSample";
    private int intField = 0;
    private static int staticIntField = 0;

    private long longField = 0;
    private static long staticLongField = 0;

    private float floatField = 0.1f;
    private static float staticFloatField = 0.1f;

    private double doubleField = 0.1;
    private static double staticDoubleField = 0.1;

    private String stringField = "this is a non-static String";
    private static String staticStringField = "this is a static String";

    public static native void nativePrint();

    public int getIntField() {
        return intField;
    }

    public long getLongField() {
        return longField;
    }

    public float getFloatField() {
        return floatField;
    }

    public double getDoubleField() {
        return doubleField;
    }

    public String getStringField() {
        return stringField;
    }

    @Override
    public String toString() {
        return "Sample{" +
                "intField=" + intField +
                ", longField=" + longField +
                ", floatField=" + floatField +
                ", doubleField=" + doubleField +
                ", stringField='" + stringField + '\'' +
                ", staticIntField=" + staticIntField +
                ", staticLongField=" + staticLongField +
                ", staticFloatField=" + staticFloatField +
                ", staticDoubleField=" + staticDoubleField +
                ", staticStringField='" + staticStringField + '\'' +
                '}';
    }
}
