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

	inline float getF()
	{
		return _g + _h;
	}

	MW_SYNTHESIZE(int, _x, X);
	MW_SYNTHESIZE(int, _y, Y);
	MW_SYNTHESIZE(float, _g, G);
	MW_SYNTHESIZE(float, _h, H);
	MW_SYNTHESIZE(MWAStarPoint *, _parent, Parent);
	MW_SYNTHESIZE(float, _flag, Flag);
};

class IAStarDelegate
{
public:
	virtual ~IAStarDelegate();

	virtual float calculateG(const MWAStarPoint &start, const MWAStarPoint &end) = 0;
	virtual float calculateH(const MWAStarPoint &start, const MWAStarPoint &end) = 0;
};

class MWAStarPathFinder : public MWObject
{
public:
	static MWAStarPathFinder *create(int mapWidth, int mapHeight, bool is8Directions = true);

	void updatePointFlag(int x, int y, float flag);

	const std::vector<cocos2d::Point> &findPath(const cocos2d::Point &start, const cocos2d::Point &end);

	void setDelegate(IAStarDelegate *delegate);
#if MW_ENABLE_SCRIPT_BINDING
	MW_SYNTHESIZE_RETAIN(cocos2d::Ref *, _scriptDelegate, ScriptDelegate);
#endif

	MW_SYNTHESIZE_READONLY(int, _mapWidth, MapWidth);
	MW_SYNTHESIZE_READONLY(int, _mapHeight, MapHeight);

private:
	bool init(int mapWidth, int mapHeight, bool is8Directions);

	bool _isPointValid(int x, int y);
	std::vector<MWAStarPoint> _surroundingPoints(const MWAStarPoint &center);

	MWAStarPathFinder();
	~MWAStarPathFinder();

	std::vector<std::vector<MWAStarPoint>> _mapPoints;
	bool _is8Directions;

	IAStarDelegate *_delegate;
};

MW_FRAMEWORK_END

#endif