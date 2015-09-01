
--------------------------------
-- @module MWZipData
-- @extend MWObject
-- @parent_module mw

--------------------------------
-- Get the total raw data of the compressed file.<br>
-- param compressedFile Compressed file path.<br>
-- password The compressed password if required.
-- @function [parent=#MWZipData] getCompressedFileData 
-- @param self
-- @param #string compressedFile
-- @return MWBinaryData#MWBinaryData ret (return value: mw.MWBinaryData)
        
--------------------------------
-- Compress new file into the zip.<br>
-- param name The compressed file name.<br>
-- param fileData The data to compress.<br>
-- param Add a password if desired.<br>
-- param level Compressed level 0-9.
-- @function [parent=#MWZipData] zipNewFile 
-- @param self
-- @param #string name
-- @param #mw.MWBinaryData fileData
-- @param #int level
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Prepare to unzip from the zip.<br>
-- note You have to call this before using "getCompressedFileData", otherwise you will failed to get the correct data.
-- @function [parent=#MWZipData] beginUnzip 
-- @param self
        
--------------------------------
-- Stop to do unzip operations.<br>
-- note Don't forget to end after all unzip operations are done, otherwise you will failed to do other operations after that.
-- @function [parent=#MWZipData] endUnzip 
-- @param self
        
--------------------------------
-- Prepare to zip new file to the zip.<br>
-- note You have to call this before using "zipNewFile", otherwise you will failed to add the data to the zip.
-- @function [parent=#MWZipData] beginZip 
-- @param self
        
--------------------------------
-- Stop to do zip operations.<br>
-- note Don't forget to end after all zip operations are done, otherwise you will failed to do other operations after that.
-- @function [parent=#MWZipData] endZip 
-- @param self
        
--------------------------------
-- Wrapper the zip data from the file and password if required.<br>
-- param filePath The zip file path.
-- @function [parent=#MWZipData] createWithExistingFile 
-- @param self
-- @param #string filePath
-- @param #string password
-- @return MWZipData#MWZipData ret (return value: mw.MWZipData)
        
--------------------------------
-- Create an empty zip.<br>
-- param filePath The zip file path to create.
-- @function [parent=#MWZipData] createWithNewFile 
-- @param self
-- @param #string filePath
-- @param #string password
-- @return MWZipData#MWZipData ret (return value: mw.MWZipData)
        
return nil
