#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

using namespace std;
using namespace sf;
class MenuHandler
{
private:
	bool isActive;
	struct ChangeableParams
	{
		string name;
		bool value;
		ChangeableParams(const string &name, const bool &value)
		{
			this->name = name;
			this->value = value;
		}
	};
	struct Button
	{
		Text buttonCap;
		string menuBind;
		bool startsGame, isExit;
		string parameterBind;
		IntRect buttonRect;
		Button(const Font &uiFont, const string &caption, const int &charSize, bool startsGame = false, bool isExit = false, string menuBind = "", string parameterBind = "")
		{
			this->buttonCap = Text(caption, uiFont, charSize);
			this->menuBind = menuBind;
			this->startsGame = startsGame;
			this->isExit = isExit;
			this->parameterBind = parameterBind;
			this->buttonRect = IntRect(this->buttonCap.getGlobalBounds());
		}
		IntRect getButtonRect()
		{
			return buttonRect;
		}
		void setPos(const float &x, const float &y)
		{
			this->buttonCap.setPosition(x, y);
			this->buttonRect = IntRect(this->buttonCap.getGlobalBounds());
		}
	};
	struct Menu
	{
		Text title;
		vector<Button> ui;
		Menu(const Font &uiFont, const string &title, const int &charSize)
		{
			this->title = Text(title, uiFont, charSize);
			this->title.setStyle(Text::Bold);
		}
		void setTitlePos(float x, float y)
		{
			this->title.setPosition(x, y);
		}
		FloatRect getTitleRect()
		{
			return this->title.getGlobalBounds();
		}
		Button &addButton(const Font &uiFont, const string &caption, const int &charSize, bool startsGame = false, bool isExit = false, string menuBind = "", string parameterBind = "")
		{
			ui.emplace_back(uiFont, caption, charSize, startsGame, isExit, menuBind, parameterBind);
			return ui.back();
		}
	};
	Menu *currMenu;
	Button *currButton;
	vector<ChangeableParams> parameters;
	unordered_map<string, Menu> menus;
	void draw(RenderWindow &);
	Menu *getMenu(const string &);
	ChangeableParams *findParam(const string &);

public:
	bool active();
	void update(RenderWindow &);
	void addChangeableParameter(const string &, const bool &);
	Menu &createMenu(const Font &, const string &, const string &, const int &);
	Menu *getCurrentMenu();
	void selectAction(RenderWindow &);
	bool getChangeableParameterValue(const string &);
	void setMenuActive(const string &);
	MenuHandler();
};
