
--------------------------------
-- @module MWIOUtils
-- @parent_module mw

--------------------------------
-- Check whether the specified file does exist.<br>
-- param path File path to check.<br>
-- return A boolean value.
-- @function [parent=#MWIOUtils] fileExists 
-- @param self
-- @param #string path
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Copy file from old path to new path.<br>
-- param oldPath Source file path.<br>
-- param newPath New file path.<br>
-- return Operation result.
-- @function [parent=#MWIOUtils] copyFile 
-- @param self
-- @param #string oldPath
-- @param #string newPath
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Write content to the specified file.<br>
-- param content File content to write.<br>
-- param length Content size.<br>
-- param filePath Destination file path.<br>
-- param isAppend Whether to append the content at the end of the file.<br>
-- return Operation result.
-- @function [parent=#MWIOUtils] writeDataToFile 
-- @param self
-- @param #void content
-- @param #unsigned long length
-- @param #string filePath
-- @param #bool isAppend
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Get the raw data from the specified file.<br>
-- param filePath Source file path.<br>
-- return The raw data of the specified file, or nullptr if it failed to read.
-- @function [parent=#MWIOUtils] getDataFromFile 
-- @param self
-- @param #string filePath
-- @return MWBinaryData#MWBinaryData ret (return value: mw.MWBinaryData)
        
--------------------------------
-- 
-- @function [parent=#MWIOUtils] splicePath 
-- @param self
-- @param #string path1
-- @param #string path2
-- @return string#string ret (return value: string)
        
--------------------------------
-- Create a new file.<br>
-- param filePath The new file path.<br>
-- return Operation result.
-- @function [parent=#MWIOUtils] createFile 
-- @param self
-- @param #string filePath
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Get the absolute path to the relative resource path.<br>
-- param path Relative path to the resource folder.<br>
-- return The absolute path.
-- @function [parent=#MWIOUtils] resourcePath 
-- @param self
-- @param #string path
-- @return string#string ret (return value: string)
        
--------------------------------
-- Remove the specified file.<br>
-- param filePath Destination file path.<br>
-- return Operation result.
-- @function [parent=#MWIOUtils] removeFile 
-- @param self
-- @param #string filePath
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Move file from old path to new path.<br>
-- param oldPath Source file path.<br>
-- param newPath New file path.<br>
-- return Operation result.
-- @function [parent=#MWIOUtils] moveFile 
-- @param self
-- @param #string oldPath
-- @param #string newPath
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Create a new directory.<br>
-- param directoryPath The new directory path.<br>
-- return Operation result.
-- @function [parent=#MWIOUtils] createDirectory 
-- @param self
-- @param #string directoryPath
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#MWIOUtils] getInstance 
-- @param self
-- @return MWIOUtils#MWIOUtils ret (return value: mw.MWIOUtils)
        
return nil
