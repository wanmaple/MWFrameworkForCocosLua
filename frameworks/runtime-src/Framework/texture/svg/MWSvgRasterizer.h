/******************************
 Description: SVG rasterizer.
 Author: M.Wan
 Date: 5/5/2015
 ******************************/

#ifndef __TEXTURE_SVG_SVG_RASTERIZER__
#define __TEXTURE_SVG_SVG_RASTERIZER__

#include "../../base/mwbase.h"
#include <string>

#include <stdio.h>
#include <string.h>
#include <float.h>
#define NANOSVG_IMPLEMENTATION
#include "nanosvg/nanosvg.h"
#define NANOSVGRAST_IMPLEMENTATION
#include "nanosvg/nanosvgrast.h"

MW_FRAMEWORK_BEGIN

/**
 * SVG Rasterizer.
 */
class MW_DLL MWSvgRasterizer
{
    MW_SINGLETON(MWSvgRasterizer);
public:
    /**
     * Destructor.
     */
    ~MWSvgRasterizer();
    
    /**
     * Raster an svg vector graphic into the image buffer.
     */
    void rasterize(NSVGimage *image, float offsetX, float offsetY, float scale, MW_RAW_DATA buffer, int width, int height, int stride);
};

MW_FRAMEWORK_END

#endif
