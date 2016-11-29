
#pragma once

struct GameState
{
	enum scene
	{
		SCENE_TITLE,
		SCENE_MATCHING,
		SCENE_MAIN,
		SCENE_RESULT
	};

	char	scene = SCENE_TITLE;
};