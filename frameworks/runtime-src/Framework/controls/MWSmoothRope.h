/******************************
Description: Draw smooth rope of custom segments.
Author: M.Wan
Date: 4/20/2016
******************************/

#ifndef __CONTROLS_SMOOTH_ROPE__
#define __CONTROLS_SMOOTH_ROPE__

#include "../base/mwbase.h"
#include "cocos2d.h"

MW_FRAMEWORK_BEGIN

typedef MWVertex2D ROPE_VERT;

class MWSmoothRope : public cocos2d::Node
{
public:
	static MWSmoothRope *create(float length, float thickness, int segments = 4);

	~MWSmoothRope();

	void setEndPoints(const cocos2d::Point &end1, const cocos2d::Point &end2);
	/**
	* Use sprite frame with a '#' prefix otherwise it will be recognized as a local image.
	*/
	void setSegmentTexture(const std::string &path);
	void setBending(float val);
	void setSegments(int segments);
	void setLength(float length);
	void setThickness(float thickness);
	void setColor(const cocos2d::Color3B &color);
	void setOpacity(GLubyte opacity);

	MW_SYNTHESIZE_READONLY(float, _bending, Bending);
	MW_SYNTHESIZE_READONLY(float, _length, Length);
	MW_SYNTHESIZE_READONLY(float, _thickness, Thickness);
	MW_SYNTHESIZE_READONLY(int, _segments, Segments);
	MW_SYNTHESIZE_RETAIN(cocos2d::Texture2D *, _segTex, SegmentTexture);
	MW_SYNTHESIZE_PASS_BY_CONST_REF(cocos2d::Rect, _texRect, TextureRect);

protected:
	MWSmoothRope();

	bool init(float length, float thickness, int segments);

	virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
	void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);

	void _updateVerts();

	cocos2d::Point _end1;
	cocos2d::Point _end2;

	bool _vertDirty;
	bool _rectRotated;

	std::vector<ROPE_VERT> _verts;
	std::vector<GLushort> _indices;
	
	GLuint _vao;
	GLuint _vbos[2];		// 0: verts		1: indices

	cocos2d::CustomCommand _cmd;
	cocos2d::GLProgram *_program;
};

MW_FRAMEWORK_END

#endif