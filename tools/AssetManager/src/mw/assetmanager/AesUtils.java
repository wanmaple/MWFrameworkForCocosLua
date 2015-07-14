/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mw.assetmanager;

import java.io.UnsupportedEncodingException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.KeyGenerator;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;

/**
 *
 * @author Maple
 */
public class AesUtils {
    public static AesUtils getInstance()
    {
        if (_instance == null) {
            _instance = new AesUtils();
        }
        return _instance;
    }
    
    private static AesUtils _instance;
    
    private AesUtils()
    {
    }
    
    public byte[] encipher(String content, String password) {
        try {             
            KeyGenerator kgen = KeyGenerator.getInstance("AES");  
            SecureRandom secureRandom = SecureRandom.getInstance("SHA1PRNG");  
            secureRandom.setSeed(password.getBytes()); 
            kgen.init(128, secureRandom);  
            SecretKey secretKey = kgen.generateKey();  
            byte[] enCodeFormat = secretKey.getEncoded();  
            SecretKeySpec key = new SecretKeySpec(enCodeFormat, "AES");  
            Cipher cipher = Cipher.getInstance("AES");// 创建密码器   
            byte[] byteContent = content.getBytes("utf-8");  
            cipher.init(Cipher.ENCRYPT_MODE, key);// 初始化   
            byte[] result = cipher.doFinal(byteContent);  
            return result; 
        } catch (NoSuchAlgorithmException e) {  
            e.printStackTrace();  
        } catch (NoSuchPaddingException e) {  
            e.printStackTrace();  
        } catch (InvalidKeyException e) {  
            e.printStackTrace();  
        } catch (UnsupportedEncodingException e) {  
            e.printStackTrace();  
        } catch (IllegalBlockSizeException e) {  
            e.printStackTrace();  
        } catch (BadPaddingException e) {  
            e.printStackTrace();  
        }  
        return null;  
    }
    
    public byte[] decipher(byte[] content, String password) {
        try {  
            KeyGenerator kgen = KeyGenerator.getInstance("AES");    
            SecureRandom secureRandom = SecureRandom.getInstance("SHA1PRNG");  
            secureRandom.setSeed(password.getBytes()); 
            kgen.init(128, secureRandom);  
            SecretKey secretKey = kgen.generateKey();  
            byte[] enCodeFormat = secretKey.getEncoded();  
            SecretKeySpec key = new SecretKeySpec(enCodeFormat, "AES");              
            Cipher cipher = Cipher.getInstance("AES");// 创建密码器   
            cipher.init(Cipher.DECRYPT_MODE, key);// 初始化   
            byte[] result = cipher.doFinal(content);  
            return result;
        } catch (NoSuchAlgorithmException e) {  
            e.printStackTrace();  
        } catch (NoSuchPaddingException e) {  
            e.printStackTrace();  
        } catch (InvalidKeyException e) {  
            e.printStackTrace();  
        } catch (IllegalBlockSizeException e) {  
            e.printStackTrace();  
        } catch (BadPaddingException e) {  
            e.printStackTrace();  
        }  
        return null; 
    }
}
