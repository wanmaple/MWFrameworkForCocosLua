package org.cocos2dx.lua;

import java.io.UnsupportedEncodingException;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.SecretKey;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;

import android.annotation.SuppressLint;
import android.content.ClipboardManager;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Debug;
import android.util.Base64;
import android.util.Log;

@SuppressLint("NewApi") 
public class AndroidUtils {
	public static void copyToPasteBoard(String content) {
		ClipboardManager cb = (ClipboardManager) AppActivity.getInstance().getSystemService(Context.CLIPBOARD_SERVICE);
		cb.setText(content);
	}
	
	public static double getCurrentUsedMemory() {
		Debug.MemoryInfo memoryInfo = new Debug.MemoryInfo();
		Debug.getMemoryInfo(memoryInfo);
		
		return memoryInfo.nativePss;
	}
	
	public static int checkNetStatus() {
		ConnectivityManager cm = (ConnectivityManager) AppActivity.getInstance().getSystemService(Context.CONNECTIVITY_SERVICE);
		NetworkInfo ni = cm.getActiveNetworkInfo();
		if (ni == null || !ni.isConnected()) {
			// not connected.
			return 0;
		}
		if (ni.getTypeName().toUpperCase().equals("WIFI")) {
			return 1;
		}
		return 2;
	}
	
	public static byte[] encipherAes256(byte[] clearText, String keyString) throws NullPointerException {
	    if (keyString == null || keyString.length() == 0) {
	        throw new NullPointerException("Please give Password");
	    }
	    
	    if (clearText == null || clearText.length <= 0) {
	        throw new NullPointerException("Please give clearText");
	    }
	    
	    try {
	        SecretKeySpec skeySpec = getKey(keyString);
	        
	        // IMPORTANT TO GET SAME RESULTS ON iOS and ANDROID
	        final byte[] iv = new byte[16];
	        Arrays.fill(iv, (byte) 0x00);
	        IvParameterSpec ivParameterSpec = new IvParameterSpec(iv);
	        
	        // Cipher is not thread safe
	        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS7Padding");
	        cipher.init(Cipher.ENCRYPT_MODE, skeySpec, ivParameterSpec);
	        
	        return cipher.doFinal(clearText);
	        
	    } catch (InvalidKeyException e) {
	        e.printStackTrace();
	    } catch (UnsupportedEncodingException e) {
	        e.printStackTrace();
	    } catch (NoSuchAlgorithmException e) {
	        e.printStackTrace();
	    } catch (BadPaddingException e) {
	        e.printStackTrace();
	    } catch (NoSuchPaddingException e) {
	        e.printStackTrace();
	    } catch (IllegalBlockSizeException e) {
	        e.printStackTrace();
	    } catch (InvalidAlgorithmParameterException e) {
	        e.printStackTrace();
	    }
	    return null;
	}
	 
	public static byte[] decipherAes256(byte[] encrypedPwdBytes, String password) throws NullPointerException {
	    
	    if (password == null || password.length() == 0) {
	        throw new NullPointerException("Please give Password");
	    }
	    
	    if (encrypedPwdBytes == null || encrypedPwdBytes.length <= 0) {
	        throw new NullPointerException("Please give encrypedPwdBytes");
	    }
	    
	    try {
	        SecretKey key = getKey(password);
	        
	        // IMPORTANT TO GET SAME RESULTS ON iOS and ANDROID
	        final byte[] iv = new byte[16];
	        Arrays.fill(iv, (byte) 0x00);
	        IvParameterSpec ivParameterSpec = new IvParameterSpec(iv);
	        
	        // cipher is not thread safe
	        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS7Padding");
	        cipher.init(Cipher.DECRYPT_MODE, key, ivParameterSpec);
	        byte[] decryptedValueBytes = (cipher.doFinal(encrypedPwdBytes));
	        
	        return decryptedValueBytes;
	        
	    } catch (InvalidKeyException e) {
	        e.printStackTrace();
	    } catch (UnsupportedEncodingException e) {
	        e.printStackTrace();
	    } catch (NoSuchAlgorithmException e) {
	        e.printStackTrace();
	    } catch (BadPaddingException e) {
	        e.printStackTrace();
	    } catch (NoSuchPaddingException e) {
	        e.printStackTrace();
	    } catch (IllegalBlockSizeException e) {
	        e.printStackTrace();
	    } catch (InvalidAlgorithmParameterException e) {
	        e.printStackTrace();
	    }
	    return null;
	}
	
	private static SecretKeySpec getKey(String password) throws UnsupportedEncodingException {
	    
	    // You can change it to 128 if you wish
	    int keyLength = 256;
	    byte[] keyBytes = new byte[keyLength / 8];
	    // explicitly fill with zeros
	    Arrays.fill(keyBytes, (byte) 0x0);
	    
	    // if password is shorter then key length, it will be zero-padded
	    // to key length
	    byte[] passwordBytes = password.getBytes("UTF-8");
	    int length = passwordBytes.length < keyBytes.length ? passwordBytes.length : keyBytes.length;
	    System.arraycopy(passwordBytes, 0, keyBytes, 0, length);
	    SecretKeySpec key = new SecretKeySpec(keyBytes, "AES");
	    return key;
	}
}
