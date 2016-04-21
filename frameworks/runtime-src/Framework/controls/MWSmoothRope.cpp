#include "MWSmoothRope.h"

#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWSmoothRope *MWSmoothRope::create(float length, float thickness, int segments)
{
	auto ret = new (nothrow)MWSmoothRope();
	if (ret && ret->init(length, thickness, segments))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

bool MWSmoothRope::init(float length, float thickness, int segments)
{
	if (!Node::init())
	{
		return false;
	}

	_length = length;
	_thickness = thickness;
	_segments = segments;

	_program = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR);
	_program->retain();

	// generate vao and vbo
	glGenVertexArrays(1, &_vao);
	glGenBuffers(2, &_vbos[0]);

	return true;
}

MWSmoothRope::MWSmoothRope()
	: Node()
	, _segTex(nullptr)
	, _program(nullptr)
	, _vertDirty(true)
	, _rectRotated(false)
	, _vao(0)
{
}

MWSmoothRope::~MWSmoothRope()
{
	CC_SAFE_RELEASE(_segTex);
	CC_SAFE_RELEASE(_program);
	
	glDeleteBuffers(2, &_vbos[0]);
	glDeleteVertexArrays(1, &_vao);
}

void MWSmoothRope::setBending(float val)
{
	if (_bending != val)
	{
		_bending = val;
		_vertDirty = true;
	}
}

void MWSmoothRope::setLength(float val)
{
	if (_length != val)
	{
		_length = val;
		_vertDirty = true;
	}
}

void MWSmoothRope::setThickness(float val)
{
	if (_thickness != val)
	{
		_thickness = val;
		_vertDirty = true;
	}
}

void MWSmoothRope::setSegments(int val)
{
	if (_segments != val)
	{
		_segments = val;
		_vertDirty = true;
	}
}

void MWSmoothRope::setEndPoints(const cocos2d::Point &end1, const cocos2d::Point &end2)
{
	if (!_end1.equals(end1) || !_end2.equals(end2))
	{
		_end1 = end1;
		_end2 = end2;
		_vertDirty = true;
	}
}

void MWSmoothRope::setColor(const Color3B &color)
{
	if (!_displayedColor.equals(color))
	{
		_displayedColor = color;
		_vertDirty = true;
	}
}

void MWSmoothRope::setOpacity(GLubyte opacity)
{
	if (_displayedOpacity != opacity)
	{
		_displayedOpacity = opacity;
		_vertDirty = true;
	}
}

void MWSmoothRope::setSegmentTexture(const std::string &path)
{
	if (path.length() <= 0)
	{
		CCLOG("MWSmoothRope ERROR: Empty texture path.");
		return;
	}

	if (path[0] == '#')
	{
		Texture2D *tex = nullptr;
		Rect texRect = Rect::ZERO;
		string sfpath = path.substr(1, path.length() - 1);
		auto sf = SpriteFrameCache::getInstance()->getSpriteFrameByName(sfpath);
		if (!sf)
		{
			CCLOG("MWSmoothRope ERROR: SpriteFrame %s doesn't exist.", sfpath.c_str());
			return;
		}
		if (sf->getTexture() != _segTex)
		{
			setSegmentTexture(sf->getTexture());
			setTextureRect(sf->getRect());
			_rectRotated = sf->isRotated();
		}
	}
	else
	{
		auto tex = Director::getInstance()->getTextureCache()->addImage(path);
		if (!tex)
		{
			CCLOG("MWSmoothRope ERROR: Texture %s load failed.", path.c_str());
		}
		if (tex != _segTex)
		{
			setSegmentTexture(tex);
			setTextureRect(Rect(0, 0, tex->getContentSize().width, tex->getContentSize().height));
			_rectRotated = false;
		}
	}
}

void MWSmoothRope::draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags)
{
	if (!_segTex)
	{
		return;
	}
	if (_end1.equals(_end2))
	{
		// end points overlap.
		return;
	}

	_cmd.init(_globalZOrder);
	_cmd.func = MW_CALLBACK_0(MWSmoothRope::onDraw, this, transform, flags);
	renderer->addCommand(&_cmd);
}

void MWSmoothRope::onDraw(const cocos2d::Mat4 &transform, uint32_t flags)
{
	if (_vertDirty)
	{
		_updateVerts();
		_vertDirty = false;
	}

	Director *director = Director::getInstance();
	director->pushMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
	director->loadMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW, transform);

	_program->use();

	const Mat4 &mvMat = transform;
	const Mat4 &pMat = director->getMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_PROJECTION);
	const Mat4 &mvpMat = pMat * mvMat;
	GLint mvpMatLoc = _program->getUniformLocation("CC_MVPMatrix");
	_program->setUniformLocationWithMatrix4fv(mvpMatLoc, mvpMat.m, 1);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _segTex->getName());
	GLint texLoc = _program->getUniformLocation("CC_Texture0");
	_program->setUniformLocationWith1i(texLoc, 0);

	glBindVertexArray(_vao);

	glBindBuffer(GL_ARRAY_BUFFER, _vbos[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbos[1]);

	glDrawElements(GL_TRIANGLES, _segments * 6, GL_UNSIGNED_SHORT, (GLvoid *)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	CHECK_GL_ERROR_DEBUG();

	director->popMatrix(MATRIX_STACK_TYPE::MATRIX_STACK_MODELVIEW);
}

void MWSmoothRope::_updateVerts()
{
	_verts.clear();

	// draw line if the distance is greater than the length
	float disSq = (_end1.x - _end2.x) * (_end1.x - _end2.x) + (_end1.y - _end2.y) * (_end1.y - _end2.y);
	float r = (float)_displayedColor.r / 255;
	float g = (float)_displayedColor.g / 255;
	float b = (float)_displayedColor.b / 255;
	float a = (float)_displayedOpacity / 255;
	if (disSq >= _length * _length)
	{
		float k = (_end2.y - _end1.y) / (_end2.x - _end1.x);
		float dx, dy;
		if (k == 0.f)
		{
			dx = 0;
			dy = _thickness*0.5;
		}
		else
		{
			float k2 = -1.f / k;
			dx = sqrtf(_thickness*_thickness*0.25 / (1 + k2 * k2));
			dy = dx * k2;
		}
		float segX = (_end2.x - _end1.x) / _segments;
		float segY = (_end2.y - _end1.y) / _segments;
		float prevXu = _end1.x + dx;
		float prevYu = _end1.y + dy;
		float prevXd = _end1.x - dx;
		float prevYd = _end1.y - dy;
		for (size_t i = 1; i <= _segments; i++)
		{
			ROPE_VERT tl, bl, tr, br;
			// vertices
			float xu = _end1.x + i * segX + dx;
			float yu = _end1.y + i * segY + dy;
			float xd = _end1.x + i * segX - dx;
			float yd = _end1.y + i * segY - dy;
			tl.vertice.set(prevXu, prevYu);
			bl.vertice.set(prevXd, prevYd);
			tr.vertice.set(xu, yu);
			br.vertice.set(xd, yd);
			prevXu = xu;
			prevYu = yu;
			prevXd = xd;
			prevYd = yd;

			// texture coordinates
			Texture2D *tex = _segTex;
			const Rect &rect = _texRect;
			float atlasWidth = (float)tex->getPixelsWide();
			float atlasHeight = (float)tex->getPixelsHigh();

			float left, right, top, bottom;

			if (_rectRotated)
			{
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
				left = (2 * rect.origin.x + 1) / (2 * atlasWidth);
				right = left + (rect.size.height * 2 - 2) / (2 * atlasWidth);
				top = (2 * rect.origin.y + 1) / (2 * atlasHeight);
				bottom = top + (rect.size.width * 2 - 2) / (2 * atlasHeight);
#else
				left = rect.origin.x / atlasWidth;
				right = (rect.origin.x + rect.size.height) / atlasWidth;
				top = rect.origin.y / atlasHeight;
				bottom = (rect.origin.y + rect.size.width) / atlasHeight;
#endif
				tl.texCoord.set(right, top);
				bl.texCoord.set(left, top);
				tr.texCoord.set(right, bottom);
				br.texCoord.set(left, bottom);
			}
			else
			{
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
				left = (2 * rect.origin.x + 1) / (2 * atlasWidth);
				right = left + (rect.size.width * 2 - 2) / (2 * atlasWidth);
				top = (2 * rect.origin.y + 1) / (2 * atlasHeight);
				bottom = top + (rect.size.height * 2 - 2) / (2 * atlasHeight);
#else
				left = rect.origin.x / atlasWidth;
				right = (rect.origin.x + rect.size.width) / atlasWidth;
				top = rect.origin.y / atlasHeight;
				bottom = (rect.origin.y + rect.size.height) / atlasHeight;
#endif
				tl.texCoord.set(left, top);
				bl.texCoord.set(left, bottom);
				tr.texCoord.set(right, top);
				br.texCoord.set(right, bottom);
			}

			// color
			tl.color.set(r, g, b, a);
			bl.color.set(r, g, b, a);
			tr.color.set(r, g, b, a);
			br.color.set(r, g, b, a);

			_verts.push_back(tl);
			_verts.push_back(bl);
			_verts.push_back(tr);
			_verts.push_back(br);
		}
	}
	else
	{
		// use quadratic bezier
		float dis = sqrtf(disSq);
		Point center = Point(_end1.x + (_end2.x - _end1.x) * _bending, _end1.y - _length * (1 - dis / _length));
		float seg = 1.f / _segments;

		// derivation at 0
		float dxt0 = -2 * _end1.x + 2 * center.x;
		float dyt0 = -2 * _end1.y + 2 * center.y;
		float k0 = dyt0 / dxt0;
		float dx0, dy0;
		if (k0 == 0.f)
		{
			dx0 = 0.f;
			dy0 = _thickness * 0.5;
		}
		else
		{
			float k02 = -1.f / k0;
			dx0 = sqrtf(_thickness * _thickness * 0.25 / (1 + k02 * k02));
			dy0 = dx0 * k02;
		}
		float prevXu = _end1.x + (-k0 / abs(k0)) * dx0;
		float prevYu = _end1.y + (-k0 / abs(k0)) * dy0;
		float prevXd = _end1.x - (-k0 / abs(k0)) * dx0;
		float prevYd = _end1.y - (-k0 / abs(k0)) * dy0;
		for (size_t i = 1; i <= _segments; i++)
		{
			ROPE_VERT tl, bl, tr, br;
			// vertices
			float t = seg * i;
			// do derivation
			float dxt = -2 * (1 - t) * _end1.x + 2 * (1 - 2 * t) * center.x + 2 * t * _end2.x;
			float dyt = -2 * (1 - t) * _end1.y + 2 * (1 - 2 * t) * center.y + 2 * t * _end2.y;
			float k = dyt / dxt;
			float dx, dy;
			if (k == 0.f)
			{
				dx = 0.f;
				dy = _thickness * 0.5;
			}
			else
			{
				float k2 = -1.f / k;
				dx = sqrtf(_thickness * _thickness * 0.25 / (1 + k2 * k2));
				dy = dx * k2;
			}

			float xu = (1 - t) * (1 - t) * _end1.x + 2 * (1 - t) * t * center.x + t * t * _end2.x + (-k / abs(k)) * dx;
			float yu = (1 - t) * (1 - t) * _end1.y + 2 * (1 - t) * t * center.y + t * t * _end2.y + (-k / abs(k)) * dy;
			float xd = (1 - t) * (1 - t) * _end1.x + 2 * (1 - t) * t * center.x + t * t * _end2.x - (-k / abs(k)) * dx;
			float yd = (1 - t) * (1 - t) * _end1.y + 2 * (1 - t) * t * center.y + t * t * _end2.y - (-k / abs(k)) * dy;
			tl.vertice.set(prevXu, prevYu);
			bl.vertice.set(prevXd, prevYd);
			tr.vertice.set(xu, yu);
			br.vertice.set(xd, yd);
			prevXu = xu;
			prevYu = yu;
			prevXd = xd;
			prevYd = yd;

			// texture coordinates
			Texture2D *tex = _segTex;
			const Rect &rect = _texRect;
			float atlasWidth = (float)tex->getPixelsWide();
			float atlasHeight = (float)tex->getPixelsHigh();

			float left, right, top, bottom;

			if (_rectRotated)
			{
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
				left = (2 * rect.origin.x + 1) / (2 * atlasWidth);
				right = left + (rect.size.height * 2 - 2) / (2 * atlasWidth);
				top = (2 * rect.origin.y + 1) / (2 * atlasHeight);
				bottom = top + (rect.size.width * 2 - 2) / (2 * atlasHeight);
#else
				left = rect.origin.x / atlasWidth;
				right = (rect.origin.x + rect.size.height) / atlasWidth;
				top = rect.origin.y / atlasHeight;
				bottom = (rect.origin.y + rect.size.width) / atlasHeight;
#endif
				tl.texCoord.set(right, top);
				bl.texCoord.set(left, top);
				tr.texCoord.set(right, bottom);
				br.texCoord.set(left, bottom);
			}
			else
			{
#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
				left = (2 * rect.origin.x + 1) / (2 * atlasWidth);
				right = left + (rect.size.width * 2 - 2) / (2 * atlasWidth);
				top = (2 * rect.origin.y + 1) / (2 * atlasHeight);
				bottom = top + (rect.size.height * 2 - 2) / (2 * atlasHeight);
#else
				left = rect.origin.x / atlasWidth;
				right = (rect.origin.x + rect.size.width) / atlasWidth;
				top = rect.origin.y / atlasHeight;
				bottom = (rect.origin.y + rect.size.height) / atlasHeight;
#endif
				tl.texCoord.set(left, top);
				bl.texCoord.set(left, bottom);
				tr.texCoord.set(right, top);
				br.texCoord.set(right, bottom);
			}

			// color
			tl.color.set(r, g, b, a);
			bl.color.set(r, g, b, a);
			tr.color.set(r, g, b, a);
			br.color.set(r, g, b, a);

			_verts.push_back(tl);
			_verts.push_back(bl);
			_verts.push_back(tr);
			_verts.push_back(br);
		}
	}

	// update indices
	for (size_t i = _indices.size(); i < _segments; i++)
	{
		_indices.push_back(i * 4 + 0);
		_indices.push_back(i * 4 + 1);
		_indices.push_back(i * 4 + 2);
		_indices.push_back(i * 4 + 1);
		_indices.push_back(i * 4 + 2);
		_indices.push_back(i * 4 + 3);
	}

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbos[0]);

	glBindBuffer(GL_ARRAY_BUFFER, _verts.size() * sizeof(_verts[0]), &_verts[0], GL_DYNAMIC_DRAW);

	GLint posLoc = _program->getAttribLocation("a_position");
	GLint colorLoc = _program->getAttribLocation("a_color");
	GLint texCoordLoc = _program->getAttribLocation("a_texCoord");

	glEnableVertexAttribArray(posLoc);
	glEnableVertexAttribArray(colorLoc);
	glEnableVertexAttribArray(texCoordLoc);

	glVertexAttribPointer(posLoc, 2, GL_FLOAT, GL_FALSE, sizeof(_verts[0]), nullptr);
	glVertexAttribPointer(texCoordLoc, 2, GL_FLOAT, GL_FALSE, sizeof(_verts[0]), (const GLvoid *)(2 * sizeof(GLfloat)));
	glVertexAttribPointer(colorLoc, 4, GL_FLOAT, GL_FALSE, sizeof(_verts[0]), (const GLvoid *)(4 * sizeof(GLfloat)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbos[1]);

	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLushort), &_indices[0], GL_DYNAMIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

MW_FRAMEWORK_END