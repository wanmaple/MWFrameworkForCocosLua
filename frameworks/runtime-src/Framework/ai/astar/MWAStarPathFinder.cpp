#include "MWAStarPathFinder.h"
#include "../../lua/MWLuaUtils.h"

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
	_mapPoints.clear();
	_pathList.clear();
	_mapPoints.reserve(mapWidth);
	for (size_t i = 0; i < mapWidth; i++)
	{
		vector<MWAStarPoint> columns;
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

bool MWAStarPathFinder::findPath(const cocos2d::Point &start, const cocos2d::Point &goal, bool ignoreCornor)
{
	if (!_isPointValid(start.x, start.y) || !_isPointValid(goal.x, goal.y))
	{
		CCLOG("Invalid start point or goal point.");
		return false;
	}

	MWAStarPoint *startPt = &_mapPoints[start.x][start.y];
	MWAStarPoint *goalPt = &_mapPoints[goal.x][goal.y];
	startPt->setG(0.f);		// The cost from start to start is certainly 0.
	startPt->setH(_calculateH(startPt, goalPt));	// For the first node, h value is completely heuristic.

	_openList.clear();
	_openList.push_back(startPt);
	_closeList.clear();

	while (!_openList.empty())
	{
		// seek the node of minimum f value from the open list
		MWAStarPoint *firstNode = *_openList.begin();
		float minF = firstNode->getF();
		auto minIter = _openList.begin();
		for (auto iter = _openList.begin(); iter != _openList.end(); ++iter)
		{
			MWAStarPoint *node = *iter;
			if (node->getF() < minF)
			{
				minF = node->getF();
				minIter = iter;
			}
		}
		MWAStarPoint *current = *minIter;

		// if the seeked node is the goal, then the way is found.
		if (current->getX() == goal.x && current->getY() == goal.y)
		{
			_reconstructPath(current);
			return true;
		}

		// remove from the open list and add to the close list.
		_openList.erase(minIter);
		_closeList.push_back(current);

		// get neighbor points of the seeked point.
		auto neighbors = _neighborPoints(current, ignoreCornor);
		for (auto &neighbor : neighbors)
		{
			// ignore the neighbor which is already evaluated.
			if (std::find(_closeList.begin(), _closeList.end(), neighbor) != _closeList.end())
			{
				continue;
			}
			float tentativeG = current->getG() + _calculateG(current, neighbor);
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
			neighbor->setParent(current);
			neighbor->setG(tentativeG);
			neighbor->setH(_calculateH(neighbor, goalPt));
		}
	}

	return false;
}

std::vector<cocos2d::Point> MWAStarPathFinder::getFoundPath()
{
	vector<Point> ret;
	for (auto &node : _pathList)
	{
		ret.push_back(Point(node->getX(), node->getY()));
	}
	return ret;
}

void MWAStarPathFinder::setDelegate(IAStarDelegate *delegate)
{
	CC_SAFE_DELETE(_delegate);
	_delegate = delegate;
}

bool MWAStarPathFinder::_isPointValid(int x, int y)
{
	bool ret = x >= 0 && x < _mapWidth && y >= 0 && y < _mapHeight;
	return ret;
}

std::vector<MWAStarPoint *> MWAStarPathFinder::_neighborPoints(MWAStarPoint *center, bool ignoreCornor)
{
	std::vector<MWAStarPoint *> ret;
	std::vector<Point> offsets = { Point(0, 1), Point(1, 0), Point(0, -1), Point(-1, 0), };
	for (auto &offset : offsets)
	{
		int x = center->getX() + offset.x;
		int y = center->getY() + offset.y;
		if (_isPointValid(x, y) && _isWalkable(x, y))
		{
			ret.push_back(&_mapPoints[x][y]);
		}
	}
	if (_is8Directions)
	{
		offsets = { Point(1, 1), Point(1, -1), Point(-1, -1), Point(-1, 1), };
		if (!ignoreCornor)
		{
			// you can't go across the cornor
			if (!_isWalkable(center->getX() + 1, center->getY()))
			{
				for (auto iter = offsets.begin(); iter != offsets.end();)
				{
					if (iter->x == 1)
					{
						iter = offsets.erase(iter);
					}
					else
					{
						++iter;
					}
				}
			}
			if (!_isWalkable(center->getX() - 1, center->getY()))
			{
				for (auto iter = offsets.begin(); iter != offsets.end();)
				{
					if (iter->x == -1)
					{
						iter = offsets.erase(iter);
					}
					else
					{
						++iter;
					}
				}
			}
			if (!_isWalkable(center->getX(), center->getY() + 1))
			{
				for (auto iter = offsets.begin(); iter != offsets.end();)
				{
					if (iter->y == 1)
					{
						iter = offsets.erase(iter);
					}
					else
					{
						++iter;
					}
				}
			}
			if (!_isWalkable(center->getX(), center->getY() - 1))
			{
				for (auto iter = offsets.begin(); iter != offsets.end();)
				{
					if (iter->y == -1)
					{
						iter = offsets.erase(iter);
					}
					else
					{
						++iter;
					}
				}
			}
		}

		for (auto &offset : offsets)
		{
			int x = center->getX() + offset.x;
			int y = center->getY() + offset.y;
			if (_isPointValid(x, y) && _isWalkable(x, y))
			{
				ret.push_back(&_mapPoints[x][y]);
			}
		}
	}
	return ret;
}

bool MWAStarPathFinder::_isWalkable(int x, int y)
{
	if (_delegate)
	{
		return _delegate->isWalkable(x, y);
	}
#if MW_ENABLE_SCRIPT_BINDING
	if (_scriptDelegate)
	{
		auto params = MWArrayList::create();
		params->appendObject(__Integer::create(x));
		params->appendObject(__Integer::create(y));
		auto paramTypes = MWArrayList::create();
		paramTypes->appendObject(__String::create("__Integer"));
		paramTypes->appendObject(__String::create("__Integer"));
		__Bool *walkable = (__Bool *)MWLuaUtils::getInstance()->executePeertableFunction(_scriptDelegate, "isWalkable", params, paramTypes, true);
		return walkable->getValue();
	}
#endif
	return true;
}

float MWAStarPathFinder::_calculateG(MWAStarPoint *current, MWAStarPoint *goal)
{
	if (_delegate)
	{
		return _delegate->calculateG(current, goal);
	}
#if MW_ENABLE_SCRIPT_BINDING
	if (_scriptDelegate)
	{
		auto params = MWArrayList::create();
		params->appendObject(__Integer::create(current->getX()));
		params->appendObject(__Integer::create(current->getY()));
		params->appendObject(__Integer::create(goal->getX()));
		params->appendObject(__Integer::create(goal->getY()));
		auto paramTypes = MWArrayList::create();
		paramTypes->appendObject(__String::create("__Integer"));
		paramTypes->appendObject(__String::create("__Integer"));
		paramTypes->appendObject(__String::create("__Integer"));
		paramTypes->appendObject(__String::create("__Integer"));
		__Double *ret = (__Double *)MWLuaUtils::getInstance()->executePeertableFunction(_scriptDelegate, "calculateG", params, paramTypes, true);
		return ret->getValue();
	}
#endif
}

float MWAStarPathFinder::_calculateH(MWAStarPoint *current, MWAStarPoint *goal)
{
	if (_delegate)
	{
		return _delegate->calculateH(current, goal);
	}
#if MW_ENABLE_SCRIPT_BINDING
	if (_scriptDelegate)
	{
		auto params = MWArrayList::create();
		params->appendObject(__Integer::create(current->getX()));
		params->appendObject(__Integer::create(current->getY()));
		params->appendObject(__Integer::create(goal->getX()));
		params->appendObject(__Integer::create(goal->getY()));
		auto paramTypes = MWArrayList::create();
		paramTypes->appendObject(__String::create("__Integer"));
		paramTypes->appendObject(__String::create("__Integer"));
		paramTypes->appendObject(__String::create("__Integer"));
		paramTypes->appendObject(__String::create("__Integer"));
		__Double *ret = (__Double *)MWLuaUtils::getInstance()->executePeertableFunction(_scriptDelegate, "calculateH", params, paramTypes, true);
		return ret->getValue();
	}
#endif
}

void MWAStarPathFinder::_reconstructPath(MWAStarPoint *current)
{
	_pathList.clear();
	while (current)
	{
		_pathList.push_back(current);
		current = current->getParent();
	}
	std::reverse(_pathList.begin(), _pathList.end());
}

MW_FRAMEWORK_END