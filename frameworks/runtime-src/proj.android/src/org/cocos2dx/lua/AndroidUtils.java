package org.cocos2dx.lua;

import android.annotation.SuppressLint;
import android.content.ClipboardManager;
import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Debug;

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
}
