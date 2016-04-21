/******************************
Description: Some basic structure of graphic.
Author: M.Wan
Date: 4/20/2016
******************************/

#ifndef __BASE_GRAPHIC_BASE__
#define __BASE_GRAPHIC_BASE__

#include "cocos2d.h"
#include "FrameworkMacros.h"

MW_FRAMEWORK_BEGIN

struct MWVertex2D
{
public:
	cocos2d::Vec2 vertice;
	cocos2d::Vec2 texCoord;
	cocos2d::Vec4 color;
};

struct MWVertex3D
{
public:
	cocos2d::Vec3 vertice;
	cocos2d::Vec2 texCoord;
	cocos2d::Vec4 color;
	cocos2d::Vec3 normal;
};

MW_FRAMEWORK_END

#endif