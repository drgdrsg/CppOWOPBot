#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Bots/BotManager.h"
#include "Tools/ITool.h"
#include "Lua/LuaEnviornment.h"

class UInterface
{
public:
	UInterface(BotManager &manager, sf::RenderWindow &target) :mManager(manager),mTarget(target),mView(target.getView()),mLuaEnv(manager,target) {  }

	void DrawGui();
	void ProcessEvent(const sf::Event &e);
	void Update(float dt);

	template <typename T, typename ...Args>
	void AddTool(Args &&...args)
	{
		mTools.emplace_back(std::make_shared<T>(*this,mManager, mTarget, std::forward<Args>(args)...));
	}

	LuaEnviornment &GetLuaEnviornment() { return mLuaEnv; }

	bool IsViewActive();

private:

	void StartFullscreen();
	void EndFullscreen();

	bool mIsFocused;

	bool mDragging;
	sf::Vector2f mDragStart;
	sf::Vector2f mViewCenter;
	sf::View mDragView;

	LuaEnviornment mLuaEnv;

	std::vector<std::shared_ptr<ITool>> mTools;
	std::shared_ptr<ITool> mSelectedTool;

	sf::View mView;
	sf::RenderWindow &mTarget;
	BotManager &mManager;

	ImVec4 colorEditCol;
	sf::Color fillcol = sf::Color(255, 0, 255);

};

