/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package mw.assetmanager;

import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFileChooser;
import javax.swing.JScrollBar;
import javax.swing.SwingUtilities;

/**
 *
 * @author Maple
 */
public class MainFrame extends javax.swing.JFrame {

    /**
     * Creates new form MainFrame
     */
    public MainFrame() {
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        fcSelectPath = new javax.swing.JFileChooser();
        btnVersionPath = new javax.swing.JButton();
        txtVersionPath = new javax.swing.JTextField();
        jLabel1 = new javax.swing.JLabel();
        lblCurrentVersion = new javax.swing.JLabel();
        btnAssetPath = new javax.swing.JButton();
        txtAssetPath = new javax.swing.JTextField();
        jLabel2 = new javax.swing.JLabel();
        txtNewVersion = new javax.swing.JTextField();
        btnAutoVersion = new javax.swing.JButton();
        btnCreateAsset = new javax.swing.JButton();
        svLog = new javax.swing.JScrollPane();
        txtLog = new javax.swing.JTextArea();
        jLabel3 = new javax.swing.JLabel();
        jLabel4 = new javax.swing.JLabel();
        txtMinProgramVersion = new javax.swing.JTextField();
        jLabel5 = new javax.swing.JLabel();
        txtProgramUpdateUrl = new javax.swing.JTextField();

        setDefaultCloseOperation(javax.swing.WindowConstants.EXIT_ON_CLOSE);
        setTitle("Asset Manager (Made By M.Wan)");
        setResizable(false);

        btnVersionPath.setText("版本库目录");
        btnVersionPath.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnVersionPathActionPerformed(evt);
            }
        });

        txtVersionPath.setFocusable(false);

        jLabel1.setText("当前版本：");

        lblCurrentVersion.setText("0.00");

        btnAssetPath.setText("新版本目录");
        btnAssetPath.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnAssetPathActionPerformed(evt);
            }
        });

        txtAssetPath.setFocusable(false);

        jLabel2.setText("新版本：");

        btnAutoVersion.setText("自动");
        btnAutoVersion.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnAutoVersionActionPerformed(evt);
            }
        });

        btnCreateAsset.setText("生成");
        btnCreateAsset.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                btnCreateAssetActionPerformed(evt);
            }
        });

        txtLog.setColumns(20);
        txtLog.setRows(5);
        txtLog.setFocusable(false);
        svLog.setViewportView(txtLog);

        jLabel3.setForeground(new java.awt.Color(255, 0, 0));
        jLabel3.setText("注意：至多保留两位小数");

        jLabel4.setText("最低C++版本：");

        jLabel5.setText("C++更新地址：");

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(getContentPane());
        getContentPane().setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addGroup(layout.createSequentialGroup()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addGap(31, 31, 31)
                                .addComponent(jLabel1)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(lblCurrentVersion))
                            .addGroup(layout.createSequentialGroup()
                                .addGap(30, 30, 30)
                                .addComponent(jLabel2)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(txtNewVersion, javax.swing.GroupLayout.PREFERRED_SIZE, 76, javax.swing.GroupLayout.PREFERRED_SIZE)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(btnAutoVersion)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(jLabel3)))
                        .addGap(0, 251, Short.MAX_VALUE))
                    .addGroup(layout.createSequentialGroup()
                        .addContainerGap()
                        .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(btnAssetPath)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(txtAssetPath))
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(btnVersionPath)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(txtVersionPath))
                            .addComponent(svLog)
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(jLabel4)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(txtMinProgramVersion))
                            .addGroup(layout.createSequentialGroup()
                                .addComponent(jLabel5)
                                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                                .addComponent(txtProgramUpdateUrl)))))
                .addContainerGap())
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(btnCreateAsset)
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(txtVersionPath, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btnVersionPath))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel1)
                    .addComponent(lblCurrentVersion))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(btnAssetPath)
                    .addComponent(txtAssetPath, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel2)
                    .addComponent(txtNewVersion, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                    .addComponent(btnAutoVersion)
                    .addComponent(jLabel3))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel4)
                    .addComponent(txtMinProgramVersion, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel5)
                    .addComponent(txtProgramUpdateUrl, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(btnCreateAsset)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(svLog, javax.swing.GroupLayout.DEFAULT_SIZE, 246, Short.MAX_VALUE)
                .addContainerGap())
        );

        pack();
    }// </editor-fold>//GEN-END:initComponents

    private void btnVersionPathActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnVersionPathActionPerformed
        // TODO add your handling code here:
        fcSelectPath.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        try {
            fcSelectPath.setSelectedFile(new File(".").getCanonicalFile());
        } catch (IOException ex) {
            Logger.getLogger(MainFrame.class.getName()).log(Level.SEVERE, null, ex);
        }
        int result = fcSelectPath.showOpenDialog(this);
        if (result == JFileChooser.APPROVE_OPTION) {
            String path = fcSelectPath.getSelectedFile().getAbsolutePath();
            if (!txtVersionPath.getText().equals(path)) {
                txtVersionPath.setText(path);
                this.checkAssetPath();
            }
        }
    }//GEN-LAST:event_btnVersionPathActionPerformed

    private void btnAssetPathActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnAssetPathActionPerformed
        // TODO add your handling code here:
        fcSelectPath.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        try {
            fcSelectPath.setSelectedFile(new File(".").getCanonicalFile());
        } catch (IOException ex) {
            Logger.getLogger(MainFrame.class.getName()).log(Level.SEVERE, null, ex);
        }
        int result = fcSelectPath.showOpenDialog(this);
        if (result == JFileChooser.APPROVE_OPTION) {
            String path = fcSelectPath.getSelectedFile().getAbsolutePath();
            txtAssetPath.setText(path);
        }
    }//GEN-LAST:event_btnAssetPathActionPerformed

    private void btnAutoVersionActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnAutoVersionActionPerformed
        // TODO add your handling code here:
        txtNewVersion.setText(String.format("%.2f", this.autoVersion()));
    }//GEN-LAST:event_btnAutoVersionActionPerformed

    private void btnCreateAssetActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_btnCreateAssetActionPerformed
        // TODO add your handling code here:
        double newVersion = 0.00;
        try {
            newVersion = Double.valueOf(txtNewVersion.getText().trim());
        } catch (Exception ex) {
            this.log("不合法的版本号，版本号必须为数字。");
            return;
        }
        
        if (newVersion < 1) {
            this.log("不合法的版本号，版本号至少要为1.00。");
            return;
        }
        
        File versionPath = new File(txtVersionPath.getText());
        File assetPath = new File(txtAssetPath.getText());
        if (!versionPath.exists()) {
            this.log("版本库目录不存在。");
            return;
        }
        if (!assetPath.exists()) {
            this.log("新版本目录不存在。");
            return;
        }
        
        this.copyNewAsset();
        this.generateAssetConfig();
        this.generateBundleMd5();
        this.generateNewVersionFile(newVersion);
        this.generateUploadFiles();
        
        this.log("所有操作完成，请将版本库下" + this.UPLOAD_DIR + "目录下的内容上传到服务器热更新地址。");
    }//GEN-LAST:event_btnCreateAssetActionPerformed

    private void copyNewAsset()
    {
        this.log("正在拷贝新资源到版本库...");
        
        String versionPath = txtVersionPath.getText();
        String assetPath = txtAssetPath.getText();
        String newVersion = txtNewVersion.getText();
        
        String versionDir = versionPath;
        if (versionPath.endsWith(File.separator)) {
            versionDir += this.VERSION_DIR + File.separator + newVersion;
        } else {
            versionDir += File.separator + this.VERSION_DIR + File.separator + newVersion;
        }
        
        FileUtils.getInstance().copyDirectory(assetPath, versionDir);
        
        this.log("操作成功。");
    }
    
    private void generateAssetConfig()
    {
        this.log("正在生成Asset的配置文件...");
        
        this._oldMd5Map = new HashMap<String, String>();
        
        String versionPath = txtVersionPath.getText();
        String assetPath = txtAssetPath.getText();
        
        String uploadDirPath = versionPath;
        if (versionPath.endsWith(File.separator)) {
            uploadDirPath += UPLOAD_DIR + File.separator;
        } else {
            uploadDirPath += File.separator + UPLOAD_DIR + File.separator;
        }
        if (!new File(uploadDirPath).exists()) {
            FileUtils.getInstance().createDirectory(uploadDirPath);
        }
        
        String oldAssetConfigPath = uploadDirPath + ASSET_CONFIG_FILE_NAME;
        File oldAssetConfig = new File(oldAssetConfigPath);
        if (oldAssetConfig.exists()) {
            String content = null;
            byte[] buffer = FileUtils.getInstance().readDataFromFile(oldAssetConfigPath);
            content = new String(buffer);
            JSONObject json = JSONObject.parseObject(content);
            JSONObject files = json.getJSONObject("files");
            Set<String> keys = files.keySet();
            String md5 = null;
            for (String key : keys) {
                md5 = files.getString(key);
                _oldMd5Map.put(key, md5);
            }
        }
        
        this._newMd5Map = new HashMap<String, String>();
        
        File assetDir = new File(assetPath);
        int fileCount = 0;
        for (File file : assetDir.listFiles()) {
            fileCount += this.generateMd5ForEachFile(file, "", 0);
        }
        String newVersion = txtNewVersion.getText();
        
        JSONObject json = new JSONObject();
        json.put("fileCount", fileCount);
        json.put("version", newVersion);
        JSONObject md5Vals = new JSONObject();
        Set<String> keys = this._newMd5Map.keySet();
        JSONArray ary = new JSONArray();
        for (String key : keys) {
            md5Vals.put(key, _newMd5Map.get(key));
            ary.add(key);
        }
        json.put("files", md5Vals);
        JSONObject modules = new JSONObject();
        modules.put(MAIN_MODULE_NAME, ary);
        json.put("modules", modules);
        
        String newAssetConfigPath = versionPath;
        if (versionPath.endsWith(File.separator)) {
            newAssetConfigPath += ASSET_CONFIG_FILE_NAME;
        } else {
            newAssetConfigPath += File.separator + ASSET_CONFIG_FILE_NAME;
        }
        
//        byte[] bytes = AesUtils.getInstance().encipher(json.toString(), AES_KEY);
        FileUtils.getInstance().writeDataToFile(newAssetConfigPath, json.toString().getBytes());
        FileUtils.getInstance().writeDataToFile(oldAssetConfigPath, json.toString().getBytes());
        
        this.log("操作成功。");
    }
    
    private void generateBundleMd5()
    {
        this.log("正在生成Asset的md5文件...");
        
        String versionPath = txtVersionPath.getText();
        String newVersion = txtNewVersion.getText();
        
        String bundleMd5Path = versionPath;
        String uploadBundleMd5Path = versionPath;
        if (versionPath.endsWith(File.separator)) {
            bundleMd5Path += BUNDLE_MD5_DIR + File.separator + newVersion + File.separator;
            uploadBundleMd5Path += UPLOAD_DIR + File.separator + BUNDLE_MD5_DIR + File.separator;
        } else {
            bundleMd5Path += File.separator + BUNDLE_MD5_DIR + File.separator + newVersion + File.separator;
            uploadBundleMd5Path += File.separator + UPLOAD_DIR + File.separator + BUNDLE_MD5_DIR + File.separator;
        }
        if (!new File(bundleMd5Path).exists()) {
            FileUtils.getInstance().createDirectory(bundleMd5Path);
        }
        if (new File(uploadBundleMd5Path).exists()) {
            FileUtils.getInstance().removeDirectory(uploadBundleMd5Path);
        }
        uploadBundleMd5Path += newVersion + File.separator + BUNDLE_MD5_FILE_NAME;
        
        String bundleMd5FilePath = bundleMd5Path + BUNDLE_MD5_FILE_NAME;
        JSONObject md5List = new JSONObject();
        Set<String> keys = _newMd5Map.keySet();
        for (String key : keys) {
            md5List.put(key, _newMd5Map.get(key));
        }
        
        FileUtils.getInstance().writeDataToFile(bundleMd5FilePath, md5List.toString().getBytes());
        FileUtils.getInstance().copyFile(bundleMd5FilePath, uploadBundleMd5Path);
        
        this.log("操作成功。");
    }
    
    private void generateNewVersionFile(double newVersion)
    {
        this.log("正在生成新版本文件...");
        
        String minProgramVersion = txtMinProgramVersion.getText().trim();
        String programUpdateUrl = txtProgramUpdateUrl.getText().trim();
        String versionPath = txtVersionPath.getText();
        
        JSONObject jsonVersion = new JSONObject();
        jsonVersion.put("version", String.format("%.2f", newVersion));
        jsonVersion.put("min_cpp_version", minProgramVersion);
        jsonVersion.put("cpp_update_url", programUpdateUrl);
//        byte[] bytes = AesUtils.getInstance().encipher(jsonVersion.toString(), AES_KEY);
        
        String newVersionPath = versionPath;
        String uploadVersionPath = versionPath;
        if (versionPath.endsWith(File.separator)) {
            newVersionPath += VERSION_FILE_NAME;
            uploadVersionPath += UPLOAD_DIR + File.separator + VERSION_FILE_NAME;
        } else {
            newVersionPath += File.separator + VERSION_FILE_NAME;
            uploadVersionPath += File.separator + UPLOAD_DIR + File.separator + VERSION_FILE_NAME;
        }
        FileUtils.getInstance().writeDataToFile(newVersionPath, jsonVersion.toString().getBytes());
        FileUtils.getInstance().writeDataToFile(uploadVersionPath, jsonVersion.toString().getBytes());
        
        this.log("操作成功。");
    }
    
    private void generateUploadFiles()
    {
        this.log("正在生成增量资源包...");
        
        String versionPath = txtVersionPath.getText();
        String assetPath = txtAssetPath.getText();
        
        String logDirPath = versionPath;
        if (versionPath.endsWith(File.separator)) {
            logDirPath += CHANGE_LOG_DIR + File.separator;
        } else {
            logDirPath += File.separator + CHANGE_LOG_DIR + File.separator;
        }
        if (!new File(logDirPath).exists()) {
            FileUtils.getInstance().createDirectory(logDirPath);
        }
        
        String newVersion = txtNewVersion.getText();
        
        // Change log
        String logFileName = lblCurrentVersion.getText() + "-" + newVersion + ".txt";
        String logFilePath = logDirPath + logFileName;
        List<String> addFiles = new ArrayList<String>();
        List<String> modifyFiles = new ArrayList<String>();
        List<String> deleteFiles = new ArrayList<String>();
        Set<String> oldMd5Keys = _oldMd5Map.keySet();
        Set<String> newMd5Keys = _newMd5Map.keySet();
        for (String key : newMd5Keys) {
            if (_oldMd5Map.containsKey(key)) {
                if (!_newMd5Map.get(key).equals(_oldMd5Map.get(key))) {
                    modifyFiles.add(key);
                }
            } else {
                addFiles.add(key);
            }
        }
        for (String key : oldMd5Keys) {
            if (!_newMd5Map.containsKey(key)) {
                deleteFiles.add(key);
            }
        }
        int total = addFiles.size() + modifyFiles.size() + deleteFiles.size();
        StringBuilder sb = new StringBuilder();
        sb.append(String.format("Total: %d\tAdd: %d\tModify: %d\tDelete: %d\n\n", total, addFiles.size(), modifyFiles.size(), deleteFiles.size()));
        for (String content : addFiles) {
            sb.append(String.format("A\t%s\n", content));
        }
        for (String content : modifyFiles) {
            sb.append(String.format("M\t%s\n", content));
        }
        for (String content : deleteFiles) {
            sb.append(String.format("D\t%s\n", content));
        }
        
        FileUtils.getInstance().writeDataToFile(logFilePath, sb.toString().getBytes());
        
        // Upload resources
        String uploadResourcesPath = versionPath;
        if (versionPath.endsWith(File.separator)) {
            uploadResourcesPath += UPLOAD_DIR + File.separator + UPLOAD_RESOURCES_DIR + File.separator;
        } else {
            uploadResourcesPath += File.separator + UPLOAD_DIR + File.separator + UPLOAD_RESOURCES_DIR + File.separator;
        }
        if (new File(uploadResourcesPath).exists()) {
            FileUtils.getInstance().removeDirectory(uploadResourcesPath);
        }
        FileUtils.getInstance().createDirectory(uploadResourcesPath);
        
        if (!assetPath.endsWith(File.separator)) {
            assetPath += File.separator;
        }
        
        for (String rpath : addFiles) {
            FileUtils.getInstance().copyFile(assetPath + rpath, uploadResourcesPath + rpath);
        }
        for (String rpath : modifyFiles) {
            FileUtils.getInstance().copyFile(assetPath + rpath, uploadResourcesPath + rpath);
        }
        
        this.log("操作成功。");
    }
    
    private void checkAssetPath()
    {
        String versionPath = txtVersionPath.getText();
        File versionDir = new File(versionPath);
        File[] children = versionDir.listFiles();
        File versionFile = null;
        for (File child : children) {
            if (child.isFile() && child.getName().equals(VERSION_FILE_NAME)) {
                versionFile = child;
                break;
            }
        }
        
        if (versionFile != null) {
            String content = null;
            byte[] buffer = FileUtils.getInstance().readDataFromFile(versionFile.getAbsolutePath());
            content = new String(buffer);
            JSONObject json = JSONObject.parseObject(content);
            String version = json.getString(VERSION_KEY);
            lblCurrentVersion.setText(version);
        } else {
            lblCurrentVersion.setText("0.00");
        }
        txtNewVersion.setText(String.format("%.2f", this.autoVersion()));
    }
    
    private int generateMd5ForEachFile(File file, String parentPath, int fileCount) {
        try {
            if (file.isDirectory()) {
                File[] files = file.listFiles();
                for (File f : files) {
                    fileCount = this.generateMd5ForEachFile(f, parentPath + file.getName() + File.separator, fileCount);
                }
            } else if (file.isFile()) {
                ++fileCount;
                _newMd5Map.put(parentPath + file.getName(), Md5Utils.getInstance().getFileMD5String(file));
            }
        } catch (IOException ex) {
            ex.printStackTrace();
        }
        
        return fileCount;
    }
    
    private double autoVersion()
    {
        double currentVersion = Double.valueOf(lblCurrentVersion.getText());
        if (currentVersion < 1) {
            return 1.00;
        }
        return currentVersion + 0.01;
    }
    
    private void log(String content) {
        _contents.offer(content);
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                txtLog.append(_contents.poll() + "\n");
                JScrollBar scrollBar = svLog.getVerticalScrollBar();
                if (scrollBar != null) {
                    scrollBar.setValue(scrollBar.getMaximum());
                }
            }
        });
    }
    
    private Map<String, String> _oldMd5Map;
    private Map<String, String> _newMd5Map;
    private Queue<String> _contents = new LinkedList<String>();
    
    private final String VERSION_FILE_NAME = "version.bin";
    private final String ASSET_CONFIG_FILE_NAME = "asset.config.bin";
    private final String BUNDLE_MD5_FILE_NAME = "bundle.md5.bin";
    private final String VERSION_KEY = "version";
    private final String MAIN_MODULE_NAME = "am.main";
    private final String VERSION_DIR = "Version";
    private final String BUNDLE_MD5_DIR = "BundleMd5";
    private final String CHANGE_LOG_DIR = "ChangeLog";
    private final String UPLOAD_DIR = "Upload";
    private final String UPLOAD_RESOURCES_DIR = "Resources";
//    private final String AES_KEY = "vgy78ik,";
    
    /**
     * @param args the command line arguments
     */
    public static void main(String args[]) {
        /* Set the Nimbus look and feel */
        //<editor-fold defaultstate="collapsed" desc=" Look and feel setting code (optional) ">
        /* If Nimbus (introduced in Java SE 6) is not available, stay with the default look and feel.
         * For details see http://download.oracle.com/javase/tutorial/uiswing/lookandfeel/plaf.html 
         */
        try {
            for (javax.swing.UIManager.LookAndFeelInfo info : javax.swing.UIManager.getInstalledLookAndFeels()) {
                if ("Nimbus".equals(info.getName())) {
                    javax.swing.UIManager.setLookAndFeel(info.getClassName());
                    break;
                }
            }
        } catch (ClassNotFoundException ex) {
            java.util.logging.Logger.getLogger(MainFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (InstantiationException ex) {
            java.util.logging.Logger.getLogger(MainFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (IllegalAccessException ex) {
            java.util.logging.Logger.getLogger(MainFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        } catch (javax.swing.UnsupportedLookAndFeelException ex) {
            java.util.logging.Logger.getLogger(MainFrame.class.getName()).log(java.util.logging.Level.SEVERE, null, ex);
        }
        //</editor-fold>

        /* Create and display the form */
        java.awt.EventQueue.invokeLater(new Runnable() {
            public void run() {
                new MainFrame().setVisible(true);
            }
        });
    }

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JButton btnAssetPath;
    private javax.swing.JButton btnAutoVersion;
    private javax.swing.JButton btnCreateAsset;
    private javax.swing.JButton btnVersionPath;
    private javax.swing.JFileChooser fcSelectPath;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JLabel jLabel4;
    private javax.swing.JLabel jLabel5;
    private javax.swing.JLabel lblCurrentVersion;
    private javax.swing.JScrollPane svLog;
    private javax.swing.JTextField txtAssetPath;
    private javax.swing.JTextArea txtLog;
    private javax.swing.JTextField txtMinProgramVersion;
    private javax.swing.JTextField txtNewVersion;
    private javax.swing.JTextField txtProgramUpdateUrl;
    private javax.swing.JTextField txtVersionPath;
    // End of variables declaration//GEN-END:variables
}
