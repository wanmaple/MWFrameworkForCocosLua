/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mw.am;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Maple
 */
public class Md5Utils { 
    public static Md5Utils getInstance()
    {
        if (_instance == null) {
            _instance = new Md5Utils();
        }
        return _instance;
    }
    
    private static Md5Utils _instance;
    
    private Md5Utils()
    {
    }
    
    private static char hexDigits[] = { '0', '1', '2', '3', '4', '5', '6',  
            '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' }; 
    
    private static MessageDigest _messageDigest = null;  
    static {  
        try {  
            _messageDigest = MessageDigest.getInstance("MD5");  
        } catch (NoSuchAlgorithmException ex) {
            Logger.getLogger(Md5Utils.class.getName()).log(Level.SEVERE, null, ex);
        }  
    }  
  
    public String getFileMD5String(File file) throws IOException {  
        FileInputStream in = new FileInputStream(file);  
        FileChannel ch = in.getChannel();  
        MappedByteBuffer byteBuffer = ch.map(FileChannel.MapMode.READ_ONLY, 0,  
                file.length());  
        _messageDigest.update(byteBuffer);  
        return bufferToHex(_messageDigest.digest());  
    }  
  
    public String getMD5String(String s) {  
        return getMD5String(s.getBytes());  
    }  
  
    public String getMD5String(byte[] bytes) {  
        _messageDigest.update(bytes);  
        return bufferToHex(_messageDigest.digest());  
    }  
  
    private String bufferToHex(byte bytes[]) {  
        return bufferToHex(bytes, 0, bytes.length);  
    }  
  
    private String bufferToHex(byte bytes[], int m, int n) {  
        StringBuffer stringbuffer = new StringBuffer(2 * n);  
        int k = m + n;  
        for (int l = m; l < k; l++) {  
            appendHexPair(bytes[l], stringbuffer);  
        }  
        return stringbuffer.toString();  
    }  
  
    private void appendHexPair(byte bt, StringBuffer stringbuffer) {  
        char c0 = hexDigits[(bt & 0xf0) >> 4];  
        char c1 = hexDigits[bt & 0xf];  
        stringbuffer.append(c0);  
        stringbuffer.append(c1);  
    }  
  
    public boolean checkPassword(String password, String md5PwdStr) {  
        String s = getMD5String(password);  
        return s.equals(md5PwdStr);  
    }
}