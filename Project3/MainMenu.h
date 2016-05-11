#ifndef __MainMenu_h_
#define __MainMenu_h_

namespace Ogre
{
	class Overlay;
}

class World;
class InputHandler;

class MainMenu 
{
public:
	MainMenu(World *world, InputHandler *input);
	
	void Think(float time);
	void displayMenu();
	void hideMenu();
	void changeOption(int difference);
	void selectOption();
	void release();
	bool getInMenu() { return inMenu; }

private:
	World *mWorld;
	InputHandler *mInputHandler;

	bool inMenu;
	bool released;
	bool transitionIn;
	bool transitionOut;
	double cameraY;

	int optionSelected;

	Ogre::Overlay *mOverlay;
	Ogre::Overlay *mRestartButtonOverlay;
	Ogre::Overlay *mPlayButtonOverlay;
	Ogre::Overlay *mExitButtonOverlay;
};

#endif