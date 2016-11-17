/******************************
Description: AStar path finder.
Author: M.Wan
Date: 10/19/2016
******************************/

#ifndef __AI_ASTAR_ASTAR_PATH_FINDER__
#define __AI_ASTAR_ASTAR_PATH_FINDER__

#include "../../base/mwbase.h"
#include "cocos2d.h"

MW_FRAMEWORK_BEGIN

class MWAStarPoint
{
public:
	MWAStarPoint(int x, int y);
	MWAStarPoint() : MWAStarPoint(0, 0) {}

	inline float getF()
	{
		return _g + _h;
	}

	MW_SYNTHESIZE(int, _x, getX, setX);
	MW_SYNTHESIZE(int, _y, getY, setY);
	MW_SYNTHESIZE(float, _g, getG, setG);		// the exact cost from the start node to this node.
	MW_SYNTHESIZE(float, _h, getH, setH);		// heuristic cost estimate from this node to the goal node.
	MW_SYNTHESIZE(MWAStarPoint *, _parent, getParent, setParent);
};

class IAStarDelegate
{
public:
	virtual ~IAStarDelegate() {}

	virtual bool isWalkable(int x, int y) = 0;
	virtual float calculateG(MWAStarPoint *current, MWAStarPoint *goal) = 0;
	virtual float calculateH(MWAStarPoint *current, MWAStarPoint *goal) = 0;
};

class MWAStarPathFinder : public MWObject
{
public:
	static MWAStarPathFinder *create(int mapWidth, int mapHeight, bool is8Directions = true);
    
    ~MWAStarPathFinder();

	bool findPath(const cocos2d::Point &start, const cocos2d::Point &goal, bool ignoreCornor = false);
	std::vector<cocos2d::Point> getFoundPath();

	void setDelegate(IAStarDelegate *delegate);
#if MW_ENABLE_SCRIPT_BINDING
	MW_SYNTHESIZE_RETAIN(cocos2d::Ref *, _scriptDelegate, getScriptDelegate, setScriptDelegate);
#endif

	MW_SYNTHESIZE_READONLY(int, _mapWidth, getMapWidth);
	MW_SYNTHESIZE_READONLY(int, _mapHeight, getMapHeight);

private:
	bool init(int mapWidth, int mapHeight, bool is8Directions);

	bool _isPointValid(int x, int y);
	std::vector<MWAStarPoint *> _neighborPoints(MWAStarPoint *center, bool ignoreCornor);
	bool _isWalkable(int x, int y);
	float _calculateG(MWAStarPoint *current, MWAStarPoint *goal);
	float _calculateH(MWAStarPoint *current, MWAStarPoint *goal);
	void _reconstructPath(MWAStarPoint *current);

	MWAStarPathFinder();

	std::vector<std::vector<MWAStarPoint>> _mapPoints;
	bool _is8Directions;
	std::list<MWAStarPoint *> _openList;
	std::vector<MWAStarPoint *> _closeList;
	std::vector<MWAStarPoint *> _pathList;

	IAStarDelegate *_delegate;
};

MW_FRAMEWORK_END

#endif