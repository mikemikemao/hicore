package com.hikvision.hicoredemo.utils;


/**
 * @date: 2018/12/28 8:34
 * @author: zhang.yw
 */
public class HexStringUtils {
    private static final char[] HEX_ARRAY = "0123456789abcdef".toCharArray();
    private static final char[] CHAR_ARRAY = new char[128];

    static {
        for (int i = 0; i < HEX_ARRAY.length; i++) {
            char c = HEX_ARRAY[i];
            CHAR_ARRAY[c] = (char) i;
        }
    }

    public static String bytesToHexString(byte[] bytes) {
        return bytesToHexString(bytes, bytes.length);
    }

    public static String bytesToHexString(byte[] bytes, int length) {
        return bytesToHexString(bytes, 0, length);
    }

    /**
     * 将byte[] 数组转换为十六进制字符串，每个byte以空格分割
     * 使用{@link #hexStringToBytes(String)}可还原此byte[]
     *
     * @param bytes  byte array
     * @param offset offset
     * @param length length
     * @return HexString
     * @see #hexStringToBytes(String)
     */
    public static String bytesToHexString(byte[] bytes, int offset, int length) {
        char[] hexChars = new char[length * 3];
        for (int j = offset; j < offset + length; j++) {
            int v = bytes[j] & 0xFF;
            hexChars[j * 3] = HEX_ARRAY[v >>> 4];
            hexChars[j * 3 + 1] = HEX_ARRAY[v & 0xF];
            hexChars[j * 3 + 2] = ' ';
        }
        return new String(hexChars);
    }

    public static String toHexString(long number, int len) {
        char[] hexChars = new char[len * 2];
        for (int i = 0; i < len; i++) {
            int v = (int) ((number >> (8 * i)) & 0xFF);
            hexChars[(len - 1 - i) * 2] = HEX_ARRAY[v >>> 4];
            hexChars[(len - 1 - i) * 2 + 1] = HEX_ARRAY[v & 0xF];
        }
        return new String(hexChars);
    }

    public static String toString(int number, int totalLen) {
        byte[] bytes = Integer.toString(number).getBytes();
        if (bytes.length > totalLen) {
            return new String(bytes);
        } else {
            byte[] result = new byte[totalLen];
            System.arraycopy(bytes, 0, result, 0, bytes.length);
            for (int i = bytes.length; i < result.length; i++) {
                result[i] = ' ';
            }
            return new String(result);
        }
    }


    /**
     * 将{@link #bytesToHexString(byte[])}转换的String 还原
     *
     * @param hexString HexString
     * @return byte array
     * @see #bytesToHexString(byte[])
     */
    public static byte[] hexStringToBytes(String hexString) {
        byte[] bytes = new byte[hexString.length() / 3];
        for (int i = 0, len = bytes.length; i < len; i++) {
            int i0 = CHAR_ARRAY[hexString.charAt(i * 3)];
            int i1 = CHAR_ARRAY[hexString.charAt(i * 3 + 1)];
            bytes[i] = (byte) ((i0 << 4) | (i1 & 0xf));
        }
        return bytes;
    }
}
