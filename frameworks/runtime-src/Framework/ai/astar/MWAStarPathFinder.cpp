#include "MWAStarPathFinder.h"

#include <new>

using namespace cocos2d;
using namespace std;

MW_FRAMEWORK_BEGIN

MWAStarPoint::MWAStarPoint(int x, int y)
: _x(x)
, _y(y)
, _g(0.f)
, _h(0.f)
, _parent(nullptr)
, _flag(0.f)
{
}



MWAStarPathFinder *MWAStarPathFinder::create(int mapWidth, int mapHeight, bool is8Directions)
{
	auto ret = new (nothrow)MWAStarPathFinder();
	if (ret && ret->init(mapWidth, mapHeight, is8Directions))
	{
		ret->autorelease();
		return ret;
	}
	CC_SAFE_RELEASE(ret);
	return nullptr;
}

bool MWAStarPathFinder::init(int mapWidth, int mapHeight, bool is8Directions)
{
	_mapPoints.reserve(mapWidth);
	for (size_t i = 0; i < mapWidth; i++)
	{
		vector<MWAStarPoint> columns(mapHeight);
		for (size_t j = 0; j < mapHeight; j++)
		{
			MWAStarPoint pt(i, j);
			columns.push_back(pt);
		}
		_mapPoints.push_back(columns);
	}
	_mapWidth = mapWidth;
	_mapHeight = mapHeight;

	return true;
}

MWAStarPathFinder::MWAStarPathFinder()
	: _is8Directions(true)
	, _delegate(nullptr)
#if MW_ENABLE_SCRIPT_BINDING
	, _scriptDelegate(nullptr)
#endif
{
}

MWAStarPathFinder::~MWAStarPathFinder()
{
	CC_SAFE_DELETE(_delegate);
}

void MWAStarPathFinder::updatePointFlag(int x, int y, float flag)
{
	if (!_isPointValid(x, y))
	{
		CCLOG("Invalid point (%d, %d)", x, y);
		return;
	}
	MWAStarPoint &pt = _mapPoints[x][y];
	pt.setFlag(flag);
}

MW_FRAMEWORK_END