#include "MenuHandler.hpp"
bool MenuHandler::active() // this method returns true if menuhandler has an active menu
{
	return isActive;
}
bool MenuHandler::getChangeableParameterValue(const string &parameterName) // this method returns parameter value based on given name
{
	auto param = findParam(parameterName); // find parameter in the list
	return param->value;				   // return its value
}
void MenuHandler::draw(RenderWindow &window) // this method draws menu on the screen
{
	window.draw(currMenu->title);
	for (auto buttons : currMenu->ui) // draw every button in the menu buttons list
		window.draw(buttons.buttonCap);
}
MenuHandler::Menu *MenuHandler::getMenu(const string &menuName) // this method returns ptr to menu based on given menu name
{
	return &menus.find(menuName)->second;
}
MenuHandler::ChangeableParams *MenuHandler::findParam(const string &parameterName) // this method returns ptr to parameter based on given name
{
	for (auto it = parameters.begin(); it != parameters.end(); it++) // check the whole list
		if (it->name == parameterName)								 // if there is such parameter
			return &*it;											 // return link to its value
	return nullptr;													 // otherwise return null pointer
}
MenuHandler::Menu *MenuHandler::getCurrentMenu() // this method returns link to the current menu value
{
	return &*currMenu;
}
void MenuHandler::selectAction(RenderWindow &window) // this method handles user action
{
	if (currButton != nullptr) // if any of the buttons has been selected
	{
		if (currButton->menuBind != "") // if button has menu bind
		{
			currMenu = getMenu(currButton->menuBind); // get menu based on menuBind button parameter
		}
		else if (currButton->parameterBind != "") // else if button has parameter bind
		{
			auto param = findParam(currButton->parameterBind); // get parameter based on parameterBind button parameter
			param->value = !param->value;					   // invert its value
		}
		else if (currButton->startsGame)
		{
			isActive = false; // if the button starts the game, then the menu should be closed
		}
		else if (currButton->isExit)
		{
			isActive = false; // if the button closes the game, then the menu should be closed
			window.close();	  // close the game window
		}
	}
}
void MenuHandler::addChangeableParameter(const string &parameterName, const bool &parameterBaseValue) // this method adds parameter to menu parameter list
{
	parameters.emplace_back(parameterName, parameterBaseValue);
}
void MenuHandler::update(RenderWindow &window) // this method updates currMenu state
{
	for (auto &buttons : currMenu->ui) // reset every button in the menu button list
	{
		buttons.buttonCap.setStyle(Text::Regular);
		if (buttons.parameterBind != "") // reset parameter button color
			buttons.buttonCap.setFillColor(findParam(buttons.parameterBind)->value ? Color::Green : Color::Red);
	}
	currButton = nullptr;			// clear pointer to the current button
	auto it = currMenu->ui.begin(); // create iterator for buttons list
	bool end = false;
	while (!end && it != currMenu->ui.end())
	{
		if ((it->getButtonRect()).contains(Mouse::getPosition(window))) // if the user hovered over the button
		{
			it->buttonCap.setStyle(Text::Underlined); // change button caption style
			end = true;								  // end the loop
			currButton = &*it;						  // set current button
		}
		else
			it++; // otherwise go further
	}
	draw(window); // draw the current menu
}

void MenuHandler::setMenuActive(const string &menuName) // this method activates the menu by the passed name
{
	isActive = true;
	currMenu = getMenu(menuName); // set the current menu
}

MenuHandler::Menu &MenuHandler::createMenu(const Font &uiFont, const string &name, const string &title, const int &charSize) // this method creates new menu in handler menu list
{
	menus.emplace(make_pair(name, Menu(uiFont, title, charSize)));
	if (currMenu == nullptr)
		currMenu = &menus.find(name)->second; // if there is no active menu, then set the created one as the current menu
	return menus.find(name)->second;		  // return link to this menu
}
MenuHandler::MenuHandler() : currMenu(nullptr), currButton(nullptr)
{
	isActive = true;
}
