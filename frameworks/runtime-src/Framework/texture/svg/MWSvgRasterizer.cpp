#include "MWSvgRasterizer.h"

MW_FRAMEWORK_BEGIN

MW_LOCAL NSVGrasterizer *g_rasterizer = nullptr;

MWSvgRasterizer::MWSvgRasterizer()
{
    
}

MWSvgRasterizer::~MWSvgRasterizer()
{
    if (g_rasterizer) {
        nsvgDeleteRasterizer(g_rasterizer);
        g_rasterizer = nullptr;
    }
}

void MWSvgRasterizer::rasterize(NSVGimage *image, float offsetX, float offsetY, float scale, void *buffer, int width, int height, int stride)
{
    if (!g_rasterizer) {
        g_rasterizer = nsvgCreateRasterizer();
    }
    CCASSERT(g_rasterizer, "Invalid svg rasterizer.");
    
    nsvgRasterize(g_rasterizer, image, offsetX, offsetY, scale, (unsigned char *) buffer, width, height, stride);
}

MW_FRAMEWORK_END