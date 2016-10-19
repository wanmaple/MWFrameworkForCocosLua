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

bool MWAStarPathFinder::findPath(const cocos2d::Point &start, const cocos2d::Point &goal)
{
	if (!_isPointValid(start.x, start.y) || !_isPointValid(goal.x, goal.y))
	{
		CCLOG("Invalid start point or goal point.");
		return false;
	}

	MWAStarPoint &startPt = _mapPoints[start.x][start.y];
	MWAStarPoint &goalPt = _mapPoints[goal.x][goal.y];
	startPt.setG(0.f);		// The cost from start to start is certainly 0.
	startPt.setH(_calculateH(startPt, goalPt));	// For the first node, h value is completely heuristic.

	_openList.clear();
	_openList.push_back(startPt);
	_closeList.clear();

	while (!_openList.empty())
	{
		// seek the node of minimum f value from the open list
		float minH = _openList.begin()->getH();
		auto minIter = _openList.begin();
		for (auto iter = _openList.begin(); iter != _openList.end(); ++iter)
		{
			if (iter->getH() < minH)
			{
				minH = iter->getF();
				minIter = iter;
			}
		}
		MWAStarPoint &current = *minIter;

		// if the seeked node is the goal, then the way is found.
		if (current.getX() == goal.x && current.getY() == goal.y)
		{
			_reconstructPath(current);
			return true;
		}

		// remove from the open list and add to the close list.
		_openList.erase(minIter);
		_closeList.push_back(current);

		// get neighbor points of the seeked point.
		auto neighbors = _neighborPoints(current);
		for (auto &neighbor : neighbors)
		{
			// ignore the neighbor which is already evaluated.
			if (std::find(_closeList.begin(), _closeList.end(), neighbor) != _closeList.end())
			{
				continue;
			}
			float tentativeG = current.getG() + _calculateG(current, neighbor);
			// discover a new node.
			if (std::find(_openList.begin(), _openList.end(), neighbor) == _openList.end())
			{
				_openList.push_back(neighbor);
			}
			else if (tentativeG >= _calculateG(startPt, neighbor))
			{
				// not a better path.
				continue;
			}

			// this path is the best now and record it.
			neighbor.setParent(&current);
			neighbor.setG(tentativeG);
			neighbor.setH(_calculateH(neighbor, goalPt));
		}
	}

	return false;
}

MW_FRAMEWORK_END