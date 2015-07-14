/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mw.assetmanager;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.PrintWriter;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 *
 * @author Maple
 */
public class FileUtils {
    public static FileUtils getInstance()
    {
        if (_instance == null) {
            _instance = new FileUtils();
        }
        return _instance;
    }
    
    private static FileUtils _instance;
    
    private FileUtils()
    {
    }
    
    public boolean createDirectory(String dirPath)
    {
        boolean ret = false;
        File dir = new File(dirPath);
        if (!dir.exists()) {
            ret = dir.mkdirs();
        }
        
        return ret;
    }
    
    public boolean writeDataToFile(String filePath, byte[] content) {
        boolean ret = false;
        File file = new File(filePath);
        try {
            if (!file.exists()) {
                ret = file.createNewFile();
                if (!ret) {
                    return false;
                }
            }
            FileOutputStream fos = new FileOutputStream(filePath);
            fos.write(content);
            fos.close();
            
            return true;
        } catch (IOException ex) {
            Logger.getLogger(FileUtils.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        return false;
    }
    
    public byte[] readDataFromFile(String filePath) {
        FileInputStream fis = null;
        try {
            fis = new FileInputStream(filePath);
            FileChannel channel = fis.getChannel();
            ByteBuffer buffer = ByteBuffer.allocate((int)channel.size());
            while (channel.read(buffer) > 0) {
                // do nothing
            }
            
            return buffer.array();
        } catch (FileNotFoundException ex) {
            Logger.getLogger(FileUtils.class.getName()).log(Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(FileUtils.class.getName()).log(Level.SEVERE, null, ex);
        }
        
        return null;
    }
    
    public boolean createFile(String filePath, byte[] content)
    {
        boolean ret = false;
        File file = new File(filePath);
        if (!file.exists()) {
            try {
                ret = file.createNewFile();
            } catch (IOException ex) {
                Logger.getLogger(FileUtils.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        if (ret) {
            try {
                FileOutputStream fos = new FileOutputStream(filePath);
                fos.write(content);
                fos.close();
            } catch (IOException ex) {
                Logger.getLogger(FileUtils.class.getName()).log(Level.SEVERE, null, ex);
            }
        }
        
        return ret;
    }
    
    public boolean removeFile(String filePath)
    {
        boolean ret = false;
        if (filePath == null || filePath.isEmpty()) {
            return ret;
        }
        File file = new File(filePath);
        if (file.isFile() && file.exists()) {
            ret = file.delete();
        }
        
        return ret;
    }
    
    public boolean removeDirectory(String dirPath)
    {
        boolean ret = false;
        if (dirPath == null || dirPath.isEmpty()) {
            return ret;
        }
        File dir = new File(dirPath);
        if (dir.isDirectory() && dir.exists()) {
            ret = dir.delete();
        }
        
        return ret;
    }
    
     public void removeAllFiles(String dirPath) {  
        File dir = new File(dirPath);  
        if (!dir.exists()) {  
            return;  
        }  
        if (!dir.isDirectory()) {  
            return;  
        }  
        String[] fileList = dir.list();  
        File tempFile = null;  
        for (int i = 0; i < fileList.length; i++) {  
            if (dirPath.endsWith(File.separator)) {  
                tempFile = new File(dirPath + fileList[i]);  
            } else {  
                tempFile = new File(dirPath + File.separator + fileList[i]);  
            }  
            if (tempFile.isFile()) {  
                tempFile.delete();  
            }  
            if (tempFile.isDirectory()) {  
                this.removeAllFiles(dirPath + "/" + fileList[i]);  
                this.removeDirectory(dirPath + "/" + fileList[i]);  
            }  
        }  
    }  
     
    public void copyFile(String oldPath, String newPath)
    {
        try {
            File oldFile = new File(oldPath);  
            if (oldFile.isFile() && oldFile.exists()) {  
                FileInputStream fis = new FileInputStream(oldPath);
                FileChannel channel = fis.getChannel();
                ByteBuffer buffer = ByteBuffer.allocate((int)channel.size());
                while (channel.read(buffer) > 0) {
                    // Do nothing.
                }
                FileOutputStream fos = new FileOutputStream(newPath);
                fos.write(buffer.array());
                fos.flush();
                fis.close();
                fos.close();
            }  
        } catch (Exception ex) {  
            Logger.getLogger(FileUtils.class.getName()).log(Level.SEVERE, null, ex);
        } 
    }
    
    public void copyDirectory(String oldPath, String newPath)
    {
        try {
            (new File(newPath)).mkdirs();  
            File oldDir = new File(oldPath); 
            if (!oldDir.isDirectory()) {
                return;
            }
            String[] fileNames = oldDir.list();  
            File temp = null;  
            for (int i = 0; i < fileNames.length; i++) {  
                if (oldPath.endsWith(File.separator)) {  
                    temp = new File(oldPath + fileNames[i]);  
                } else {  
                    temp = new File(oldPath + File.separator + fileNames[i]);  
                }  
                String path1 = temp.getAbsolutePath();
                String path2 = null;
                if (newPath.endsWith(File.separator)) {
                    path2 = newPath + fileNames[i];
                } else {
                    path2 = newPath + File.separator + fileNames[i];
                }
                if (temp.isFile()) {  
                    this.copyFile(path1, path2);
                } else if (temp.isDirectory()) {  
                    this.copyDirectory(path1, path2);
                }  
            } 
        } catch (Exception ex) {
            Logger.getLogger(FileUtils.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
}
