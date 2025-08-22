#include "levelData.hpp"

Level LevelData::GetLevel1() {
	return Level({
		{
			// 1
			GridSpace::GOAL,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::FLIP,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::FLIP,
		},
		{
			// 2
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY
		},
		{
			// 3
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::FLIP,
		},
		{
			// 4
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE
		},
		{
			// 5
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
		},
		{
			// 6
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
		}
	});
}

Level LevelData::GetLevel2() {
	return Level({
		{
			// 1
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::FLIP,
			GridSpace::OBSTACLE
		},
		{
			// 2
			GridSpace::EMPTY,
			GridSpace::FLIP,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE
		},
		{
			// 3
			GridSpace::INVIS,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
		},
		{
			// 4
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::GOAL
		},
		{
			// 5
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
		},
		{
			// 6
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::INVIS,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::INVIS,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
		}
	});
}

Level LevelData::GetLevel3() {
	return Level({
		{
			// 1
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::SPAM,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY
		},
		{
			// 2
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::FLIP
		},
		{
			// 3
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
		},
		{
			// 4
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::FLIP
		},
		{
			// 5
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::SPAM,
			GridSpace::EMPTY,
			GridSpace::SPAM,
			GridSpace::GOAL,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
		},
		{
			// 6
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::FLIP
		}
	});
}

Level LevelData::GetLevel4() {
	return Level({
	{
			// 1
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::EMPTY,
			GridSpace::DARK,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY
		},
		{
			// 2
			GridSpace::EMPTY,
			GridSpace::FLIP,
			GridSpace::EMPTY,
			GridSpace::SPAM,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::INVIS
		},
		{
			// 3
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
		},
		{
			// 4
			GridSpace::EMPTY,
			GridSpace::FLIP,
			GridSpace::GOAL,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::DARK,
			GridSpace::EMPTY,
			GridSpace::DARK,
			GridSpace::FLIP,
			GridSpace::FLIP
		},
		{
			// 5
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
		},
		{
			// 6
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::DARK,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE
		}
	});
}

Level LevelData::GetLevel5() {
	return Level({
	{
			// 1
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::INVIS,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE
		},
		{
			// 2
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::INVIS,
			GridSpace::EMPTY
		},
		{
			// 3
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
		},
		{
			// 4
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::GOAL,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY
		},
		{
			// 5
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
		},
		{
			// 6
			GridSpace::EMPTY,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::DARK,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE
		}
	});
}



Level LevelData::GetLevel6() {
	return Level({
	{
			// 1
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::FLIP,
			GridSpace::EMPTY,
			GridSpace::FLIP,
			GridSpace::SPAM
		},
		{
			// 2
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::FLIP
		},
		{
			// 3
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
		},
		{
			// 4
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE
		},
		{
			// 5
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::GOAL,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
		},
		{
			// 6
			GridSpace::EMPTY,
			GridSpace::DARK,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY
		}
	});
}

Level LevelData::GetLevel7() {
	return Level({
	{
			// 1
			GridSpace::SPAM,
			GridSpace::FLIP,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::GOAL,
			GridSpace::GOAL,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::INVIS,
			GridSpace::EMPTY
		},
		{
			// 2
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY
		},
		{
			// 3
			GridSpace::DARK,
			GridSpace::INVIS,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::GOAL,
			GridSpace::GOAL,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
		},
		{
			// 4
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::GOAL,
			GridSpace::GOAL,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE
		},
		{
			// 5
			GridSpace::SPAM,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::GOAL,
		},
		{
			// 6
			GridSpace::EMPTY,
			GridSpace::SPAM,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::DARK,
			GridSpace::EMPTY,
			GridSpace::INVIS,
			GridSpace::OBSTACLE,
			GridSpace::GOAL,
			GridSpace::GOAL
		}
	});
}

Level LevelData::GetLevel8() {
	return Level({
	{
			// 1
			GridSpace::GOAL,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::GOAL,
			GridSpace::OBSTACLE,
			GridSpace::GOAL,
			GridSpace::DARK,
			GridSpace::OBSTACLE,
			GridSpace::GOAL
		},
		{
			// 2
			GridSpace::OBSTACLE,
			GridSpace::DARK,
			GridSpace::EMPTY,
			GridSpace::INVIS,
			GridSpace::OBSTACLE,
			GridSpace::GOAL,
			GridSpace::OBSTACLE,
			GridSpace::INVIS,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE
		},
		{
			// 3
			GridSpace::FLIP,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::INVIS,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::GOAL
		},
		{
			// 4
			GridSpace::INVIS,
			GridSpace::OBSTACLE,
			GridSpace::GOAL,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::SPAM,
			GridSpace::DARK,
			GridSpace::OBSTACLE,
			GridSpace::GOAL,
			GridSpace::OBSTACLE
		},
		{
			// 5
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::INVIS,
			GridSpace::DARK,
			GridSpace::OBSTACLE,
			GridSpace::INVIS,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::GOAL,
		},
		{
			// 6
			GridSpace::EMPTY,
			GridSpace::DARK,
			GridSpace::FLIP,
			GridSpace::SPAM,
			GridSpace::OBSTACLE,
			GridSpace::GOAL,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE
		}
	});
}

Level LevelData::GetLevel9() {
	return Level({
	{
			// 1
			GridSpace::FLIP,
			GridSpace::FLIP,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::FLIP,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::GOAL
		},
		{
			// 2
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE
		},
		{
			// 3
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE
		},
		{
			// 4
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE
		},
		{
			// 5
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::OBSTACLE
		},
		{
			// 6
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::FLIP,
			GridSpace::FLIP,
			GridSpace::OBSTACLE,
			GridSpace::FLIP,
			GridSpace::FLIP,
			GridSpace::FLIP,
			GridSpace::OBSTACLE
		}
	});
}

Level LevelData::GetLevel10() {
	return Level({
	{
			// 1
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY
		},
		{
			// 2
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY
		},
		{
			// 3
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::GOAL,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY
		},
		{
			// 4
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::OBSTACLE,
			GridSpace::GOAL,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY
		},
		{
			// 5
			GridSpace::INVIS,
			GridSpace::EMPTY,
			GridSpace::DARK,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY
		},
		{
			// 6
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::EMPTY,
			GridSpace::OBSTACLE
		}
	});
}

