#pragma once
#include"titleScene.h"
#include"selectScene.h"
#include"playScene.h"
#include"resultScene.h"

class sceneManager
{
public:
	sceneManager();
	~sceneManager();

	//シーンの付け替え
	void replacementScene();

public:
	primitiveScene* nowscene;

private:
};