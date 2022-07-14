//Mad_Diggers

#ifndef RESOURCES_H_
#define RESOURCES_H_

#include "Texture.h"
#include "Font.h"
#include "Music.h"
#include "SoundEffect.h"

#include "sdl_includes.h"
//#include "checkML.h" //gotta add this to all cpp

//all classes will include these indirectly
#include <vector>
#include <list>		//entities_ (could be a vector)

#include <time.h>	//much used (Uint32, etc)

#include <string>
#include <iostream> //not really used, just allows cout debug

//#include <queue>		//BoardState.h, miniGameState.h
//#include <stack>		//GameStatesMachine.h

//#include <math.h>		//Vector2D.cpp
//#include <assert.h>	//Vector2D.cpp
//#include <algorithm>	//SkeletonRenderer.cpp

//#include <string>		//SDLError.h
//#include <sstream>
//#include <stdexcept>

//#include <tuple>		//not used atm


using namespace std;

class SDLGame; //foward

class Resources
{
public:
	// Here we define the enums for the resources.
	// Then in the cpp we write the data in the vecotrs ordered
	// The enums are simple used to make access readable ...

	// Spritesheets (filenames, cols, fils) -- each spritesheet file is loaded as an instance of Texture
	enum SpriteSheetId {
		ss_Dog,
		ss_BackGround,

		ss_ControlSumo,
		ss_ControlPong,

		ss_SumoCD,

		ss_HoneyAnimation,

		ss_PlayerHandsMoving,
		ss_PlayerIdleNet,
		ss_SpinnerTime
	};

	// Images (filenames) -- each image file is loaded as an instance of Texture
	enum ImageId {
		i_Blank,
		i_KeyBoardIcon,
		i_AIIcon,

		i_Drop,

		i_redCircle,
		i_yellowCircle,
		i_purpleCircle,
		i_greenCircle,
		i_blueCircle,
		i_sumoP0,
		i_sumoP1,
		i_sumoP2,
		i_sumoP3,
		i_minArea2P,
		i_minArea4P,
		i_sumoArea,

		i_paddle0,
		i_paddle1,
		i_paddle2,
		i_paddle3,
		i_honeyPongU,
		i_honeyPongD,
		i_honeyPongL,
		i_honeyPongR,

		i_madLogo,
		i_blueButton,
		i_greenButton,
		i_copySym,

		i_applePlayer1,
		i_tree1,
		i_apple1,
		i_apple2,
		i_apple3,
		i_apple4,
		i_applePlayer2,
		i_tree2,
		i_timer,

		i_spikeTrap,
		i_pBlock,
		i_gem,

		i_bullet,
		i_terrain,

		i_Alvaro,
		i_Antonio,
		i_Diego,
		i_Jorge,
		i_Lluis,
		i_Marcos,
		i_Mario,
		i_Sergio,
		i_Podium,

		i_BackGroundPodium,
		i_TheHiveBack,
		i_StartOff,
		i_StartOn,
		i_HowToOff,
		i_HowToOn,
		i_CreditsOff,
		i_CreditsOn,
		i_paloMenu,
		i_rulesMenu1,
		i_creditsStateBack,
		i_creditsPeople,

		i_Interr,
		i_spin_sumo,
		i_spin_pong,
		i_spin_apple,
		i_spin_platform,
		i_spin_race,
		i_spin_dodge,

		i_spinnerTimeMsg,
		i_startMsg,
		i_endMsg,

		i_spinBack,
		i_spinFront,

		i_pongControls,
		i_pressA_,
		i_sumoControls,
		i_appleControls,
		i_platControls,
		i_challControls,
		i_dodgeControls,

		i_rulesMenu2,
		i_menuNext_,
		i_rulesBackMenu,
		i_inst,

	};

	// Shapes (filenames) -- each image file is loaded as an instance of Texture
	enum ShapeId {
		s_hexagon,
		s_bee,
		s_bocadillo,

		s_diceSelector,
		s_dice1,
		s_dice2,
		s_dice3,
		s_dice4,

		s_honeyButton,

		s_beehive,

		s_sumoCP1,
		s_sumoCP2,
		s_sumoCP3,
		s_sumoCP4,

		s_pongCP1,
		s_pongCP2,
		s_pongCP3,
		s_pongCP4,
		s_pongBlock,

		s_tree,
		s_hive,

		s_BeeKeeper,
		s_BeeKeeperNet,
		s_playerHead,

		s_beeKeepingPlayer,
		s_platPlayer,
		s_bulletPlayer,


	};

	// Text Messages (filenames) - each is loaded as an instance of a texture
	enum TextId {
		t_HelloWorld,
		t_PresAnyKey,
		t_GameOver,
		t_startMenuButton,
		t_creditsMenuButton,
		t_Alvaro,
		t_Antonio,
		t_Diego,
		t_Jorge,
		t_Lluis,
		t_Marcos,
		t_Mario,
		t_Sergio,
	};

	// Fonts (filenames, size) -- each is loaded as an instance of Font
	enum FontId {
		f_ARIAL_64,
		f_ARIAL_128,
		f_NESChimera_64,
		f_NESChimera_128,
		f_CaptureIt_64,
		f_CaptureIt_128,
		f_Hack_64,
		f_Hack_128,
		f_Hack_Bold_64,
		f_Hack_Bold_128,
		f_Hack_Italic_64,
		f_Hack_Italic_128,
		f_Hack_BoldItalic_64,
		f_Hack_BoldItalic_128,
	};

	// Music (filenames) -- each file is loaded as an instance of Music
	enum MusicId {
		m_menu,
		m_board,
		//m_credits,

		m_sumo,
		m_pong,
		m_apple,
		m_platform,
		m_race,
		m_dodge,

	};

	// Sound Effects (filenames) -- each file is loaded as an instance of SoundEffect
	enum SoundEffectId {

		//Multiuse
		s_jump,

		//Sumo
		s_bounce,
		s_sumoDeath,

		//Pong
		s_Wall_Hit,
		s_Paddle_Hit,
		//s_pongDeath,

		//Apples
		s_moveTree,
		s_appleFall,
		s_appleCatch,
		s_appleDrop,

		//Platform + Race
		s_platformDeath,

		//Dodge
		s_dodgeShot,
		s_dodgeDeath,

	};

	//Json files id route
	enum jsonFilesId {
		j_SumoMinigame,
		j_SumoPlayer,
		j_BackgroundObject,
		j_Board,
		j_PongMinigame,
		j_MainMenu,
	};

	// Colors (SDL_Color values) -- different, no need to load and public vector
	enum ColorId {
		c_White,
		c_Black,
		c_Grey_light,
		c_Grey,
		c_Grey_dark,

		c_Red,
		c_Green,
		c_Blue,

		c_Cian,
		c_Pink,
		c_Yellow,

		c_Red_light,
		c_Green_light,
		c_Blue_light,
		c_Yellow_light,

		c_Green_olive,
		c_Blue_corrected,
		c_Aqua,
		c_Orange,
		c_Honey,
	};

private:

	//basic spritesheet data
	struct SpriteSheetInfo {
		string fileName;
		int cols, fils;
	};

	//basic font data
	struct FontInfo {
		string fileName;
		int size;
	};

	//basic messages data
	struct TextMsgInfo {
		string text;
		SDL_Color color;
		FontId fontId;
	};

	//These vectors store all the data to load the resources
	//Use Id enums to acces them
	//All initialized in .cpp

	static vector<SpriteSheetInfo> spriteSheetsFiles_;
	static vector<string> shapeFiles_;
	static vector<string> imageFiles_;
	static vector<TextMsgInfo> textMsgs_;
	static vector<FontInfo> fontFiles_;
	static vector<string> musicFiles_;
	static vector<string> soundEffectFiles_;
	static vector<string> jsonFiles_;

	//stores all colors values (along with alpha)
	static vector<SDL_Color> colorsValues_;

public:
	Resources(SDLGame* game);
	virtual ~Resources();

	//returns a pointer to the Texture of given SpriteSheetId
	Texture* getSpriteSheetTexture(SpriteSheetId i) const;
	//returns a pointer to the Texture of given ShapeTexture
	Texture* getShapeTexture(ShapeId i) const;
	//returns a pointer to the Texture of given ImageId
	Texture* getImageTexture(ImageId i) const;

	//returns a pointer to the Texture of given TextId
	Texture* getTextTexture(TextId i) const;
	//returns a pointer to the Font of given FontId
	Font* getFont(FontId i) const;

	//returns a pointer to the Music of given MusicId
	Music* getMusic(MusicId i) const;
	//returns a pointer to the SoundEffect of given SoundEffectId
	SoundEffect* getSoundEffect(SoundEffectId i) const;

	//returns a pointer to the JsonFile of given jsonFileId
	std::string getJsonFile(jsonFilesId i) const;

	//return a pointer to the Color of given ColorId (no need for instance)
	static SDL_Color* getSDLColor(ColorId i);
	static int getNumOfColors() { return colorsValues_.size(); };

	static const vector<ColorId> _DEFAULT_PLAYERS_COLORS_ID_;

private:
	void setSpritesheetsTextures(vector<SpriteSheetInfo> textures);
	void setShapeTextures(vector<string> textures);
	void setImageTextures(vector<string> textures);
	void setTextTextures(vector<TextMsgInfo> texts);
	void setFonts(vector<FontInfo> fonts);
	void setMusic(vector<string> music);
	void setSoundEffects(vector<string> soundEffects);

	void closeShapeTextures();
	void closeSpritesheetsTextures();
	void closeImageTextures();
	void closeTextTextures();
	void closeFonts();
	void closeMusic();
	void closeSoundEffects();

	///////////////////////////////////////////////////////////////////

	SDLGame* game_; //pointer to SDLGame

	int numOfSpritesheetsTextures_;
	Texture** spriteSheetsTextures_;//pointer to the vector of spritesheetsTextures

	int numOfShapeTextures_;
	Texture** shapeTextures_;		//pointer to the vector of shapeTextures

	int numOfImageTextures_;
	Texture** imageTextures_;		//pointer to the vector of imageTextures

	int numOfTextTextures_;
	Texture** textTextures_;		//pointer to the vector of textTextures

	int numOfFonts_;
	Font** fonts_;					//pointer to the vector of fonts

	int numOfMusic_;
	Music** music_;					//pointer to the vector of musics

	int numOfSoundEffects_;
	SoundEffect** soundEffects_;	//pointer to the vector of soundEffects
};

#endif /* RESOURCES_H_ */
