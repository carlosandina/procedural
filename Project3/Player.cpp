#include "Player.h"
#include "World.h"
#include "InputHandler.h"
#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "Ogre.h"
#include "OBB.h"
#include "MainMenu.h"
Player::Player(World *world) : mWorld(world)
{
	i = 1 ;
}


void 
Player::restart() 
{
	tankEntity = mWorld->SceneManager()->createEntity("DrawCall_640.001.mesh");
	mTank = mWorld->SceneManager()->getRootSceneNode()->createChildSceneNode();
	mTank->attachObject(tankEntity);
	mTank->setPosition(0, 1, 20);
	mTank->scale(.5,.3,.5);
	mTank->setVisible(false);
	playerOBB = new OBB(tankEntity->getBoundingBox(), mTank->getPosition(), mTank->getOrientation());
	i = 1;
}

Player::~Player(void)
{
}


void 
Player::Think(float time, InputHandler *mInputHandler)
{
	playerOBB->setScale(Ogre::Vector3(0.5, 0.3, 0.5));
	playerOBB->setPosition(mTank->getPosition());
	playerOBB->setOrientation(mTank->getOrientation());


	if (mWorld->mStaticCollisions->begin() != mWorld->mStaticCollisions->end())
	{
		for(std::vector<OBB*>::iterator it = mWorld->mStaticCollisions->begin(); it != mWorld->mStaticCollisions->end(); ++it) 
		{
			Ogre::Vector3 moveVector;

			if ((*it)->collides(playerOBB, moveVector) == true)
			{
				mTank->translate(-moveVector);
				playerOBB->setPosition(mTank->getPosition());
			}
			
		}
	}

	const float RADIANS_PER_SECOND = 1;
	const float SPEED = 7;

	mInputHandler->mMouse->capture();

	int mx =mInputHandler->mMouse->getMouseState().X.rel;
	int my = mInputHandler->mMouse->getMouseState().Y.rel;
	
	//The bigger the # you divide by, the slower the move
	mTank->yaw((Ogre::Degree) mx*-10 / 60, Ogre::Node::TS_WORLD);

	Ogre::Radian oldPitch = mTank->getOrientation().getPitch();
	Ogre::Radian newPitch = Ogre::Math::Abs((Ogre::Degree)(my*-10 / 60) + oldPitch);

	if(newPitch < Ogre::Radian(Ogre::Math::PI/2)) {
		mTank->pitch((Ogre::Degree) my*-10 / 60);
	}


	if (mInputHandler->IsKeyDown(OIS::KC_RIGHT) || mInputHandler->IsKeyDown(OIS::KC_D))
	{
		if (mInputHandler->IsKeyDown(OIS::KC_SPACE) && i < 600) {
			mTank->translate(time * (SPEED + 4), 0, 0, Ogre::Node::TS_LOCAL);
			i++;
		} else {
			
		mTank->translate(time * SPEED, 0, 0, Ogre::Node::TS_LOCAL);
		}
	}
	else if (mInputHandler->IsKeyDown(OIS::KC_LEFT) || mInputHandler->IsKeyDown(OIS::KC_A))
	{
		if (mInputHandler->IsKeyDown(OIS::KC_SPACE) && i < 600) {
			mTank->translate(-time * (SPEED + 4), 0, 0, Ogre::Node::TS_LOCAL);
			i++;
		} else {
			
		mTank->translate(-time * SPEED, 0, 0, Ogre::Node::TS_LOCAL);
		}
	}
	if (mInputHandler->IsKeyDown(OIS::KC_UP) || mInputHandler->IsKeyDown(OIS::KC_W))
	{
		if (mInputHandler->IsKeyDown(OIS::KC_SPACE) && i < 600) {
			mTank->translate(0,0, -time * (SPEED+4), Ogre::Node::TS_LOCAL);
			i = i + 1;
		} else {
			mTank->translate(0,0, -time * SPEED, Ogre::Node::TS_LOCAL);
			 
		}
	} 
	else if (mInputHandler->IsKeyDown(OIS::KC_DOWN) || mInputHandler->IsKeyDown(OIS::KC_S))
	{
		i = i - 1;
		if (mInputHandler->IsKeyDown(OIS::KC_SPACE) && i < 600) {
			mTank->translate(0,0, time * (SPEED + 4), Ogre::Node::TS_LOCAL);
			
		} else {
			mTank->translate(0,0, time * SPEED, Ogre::Node::TS_LOCAL);
			
		}
	} else {
		i = i-1;
	}

	


	//Quick and dirty: Fixes issue of moving up if aiming up. If ground not at 0, change y component to be whatever the ground is at.
	mTank->setPosition(mTank->getPosition().x, 1, mTank->getPosition().z);

}