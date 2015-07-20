#pragma once

#include "mwframework.h"

class UpdateScene : public mwframework::MWGameScene, public mwframework::IAssetUpdateDelegate
{
public:
    static UpdateScene *create();
    
    /**
     * Delegate when the version checking is over.
     */
    void onVersionCheckCompleted(bool latest, int fileCount, bool needUpdateProgram, const std::string &programUpdateUrl);
    /**
     * Delegate when the single file is downloading.
     */
    void onAssetFileDownloading(const std::string &filePath, float progress, long totalToDownload);
    /**
     * Delegate when the single file is updated.
     */
    void onAssetFileDownloaded(const std::string &filePath);
    /**
     * Delegate when the version is updated.
     */
    void onVersionUpdated();
    /**
     * Delegate when download failed.
     */
    void onUpdateError(mwframework::EAssetUpdateErrorType errorType, const std::string &errorMsg);
    
    void onEnter() override;
};

