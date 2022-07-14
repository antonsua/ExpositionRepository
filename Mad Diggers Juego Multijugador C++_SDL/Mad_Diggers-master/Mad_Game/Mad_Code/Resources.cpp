#include "SDLGame.h" //fowarded
#include "Resources.h"

const vector<Resources::ColorId> Resources::_DEFAULT_PLAYERS_COLORS_ID_
{
	Resources::c_Red_light,
	Resources::c_Green_light,
	Resources::c_Blue_corrected,
	Resources::c_Pink,
};

vector<SDL_Color> Resources::colorsValues_{
	{ COLOR(0xffffffff) },
	{ COLOR(0x000000ff) },
	{ COLOR(0xdbdbdbff) },
	{ COLOR(0xadadadff) },
	{ COLOR(0x5e5e5eff) },

	{ COLOR(0xff1111ff) },
	{ COLOR(0x11ff11ff) },
	{ COLOR(0x1111ffff) },

	{ COLOR(0x11ffffff) },
	{ COLOR(0xff11ffff) },
	{ COLOR(0xffff00ff) },

	{ COLOR(0xff1111ff) },
	{ COLOR(0x64ff64ff) },
	{ COLOR(0x6464ffff) },
	{ COLOR(0xffff64ff) },

	{ COLOR(0xaaffbbff) },
	{ COLOR(0x1164ffff) },
	{ COLOR(0x00aaaaff) },
	{ COLOR(0xee9908ff) },
	{ COLOR(0xefb316ff) }
};

vector<Resources::SpriteSheetInfo> Resources::spriteSheetsFiles_{
	{ "images/demo/dog.png", 6, 1 },
	{ "images/board/background10x6.png", 10, 6},
	{ "images/Controls/SumoTemp.png", 4, 2 },
	{ "images/Controls/PongTemp.png", 4, 2 },
	{ "images/countDown.png", 1, 34 },

	{ "images/pongGame/fillHoneyAnimation.png", 5, 4 },

	{ "images/_player/beekeeperAnim1.png", 4, 1 },
	{ "images/_player/beekeeperAnim.png", 4, 1 },
	{ "images/board/spinnerTimeAnim.png", 3, 7},
};

vector<string> Resources::shapeFiles_{
	"images/board/shadedHexVec.png",
	"images/board/bees/bee.png",
	"images/board/rolling/bocadillo1.png",

	"images/board/rolls/beeRollSelector.png",
	"images/board/rolls/beeRoll1.png",
	"images/board/rolls/beeRoll2.png",
	"images/board/rolls/beeRoll3.png",
	"images/board/rolls/beeRoll4.png",

	"images/HoneyButton.png",

	"images/platformGame/beehive.png",

	"images/Controls/sumop1.png",
	"images/Controls/sumop2.png",
	"images/Controls/sumop3.png",
	"images/Controls/sumop4.png",

	"images/Controls/pongp1.png",
	"images/Controls/pongp2.png",
	"images/Controls/pongp3.png",
	"images/Controls/pongp4.png",
	"images/pongGame/shadedPanalPong.png",
	"images/appleGame/tree.png",
	"images/appleGame/hive.png",

	"images/_player/beekeeper.png",
	"images/_player/beekeeper1.png",
	"images/_player/head.png",

	"images/Controls/applePlayer.png",
	"images/Controls/platPlayer.png",
	"images/Controls/bulletPlayer.png",
};

vector<string> Resources::imageFiles_{
	"images/blank.png",
	"images/demo/keyboard.png",
	"images/demo/ai.png",

	"images/board/rolling/drop2.png",

	"images/sumoGame/sumo1.png",
	"images/sumoGame/sumo3.png",
	"images/sumoGame/sumo4.png",
	"images/sumoGame/sumo2.png",
	"images/sumoGame/sumo5.png",

	"images/sumoGame/bolaRoja.png",
	"images/sumoGame/bolaVerde.png",
	"images/sumoGame/bolaAzul.png",
	"images/sumoGame/bolaRosa.png",

	"images/sumoGame/minArea2P.png",
	"images/sumoGame/minArea4P.png",
	"images/sumoGame/sumoArea.png",

	"images/pongGame/redPaddle.png",
	"images/pongGame/greenPaddle.png",
	"images/pongGame/yellowPaddle.png",
	"images/pongGame/purplePaddle.png",

	"images/pongGame/honeyPongU.png",
	"images/pongGame/honeyPongD.png",
	"images/pongGame/honeyPongL.png",
	"images/pongGame/honeyPongR.png",

	"images/menu/MADLogo.png",
	"images/menu/button_blue.png",
	"images/menu/green_button.png",
	"images/menu/copySym.png",

	"images/appleGame/p1.png",
	"images/appleGame/t1.png",
	"images/appleGame/a1.png",
	"images/appleGame/a2.png",
	"images/appleGame/a3.png",
	"images/appleGame/a4.png",
	"images/appleGame/p2.png",
	"images/appleGame/t2.png",
	"images/appleGame/timer.png",

	"images/platformGame/spikeTrap.png",
	"images/platformGame/beePlatformBlock.png",
	"images/platformGame/redFlower.png",

	"images/dodgeGame/dodgebullet1.png",
	"images/dodgeGame/beeTerrain.png",

	"images/credits/alvaro.jpg",
	"images/credits/antonio.jpg",
	"images/credits/diego.jpg",
	"images/credits/jorge.jpg",
	"images/credits/lluis.jpg",
	"images/credits/marcos.jpg",
	"images/credits/mario.jpg",
	"images/credits/sergio.jpg",
	"images/podium/podium.png",

	"images/podium/podium.png",
	"images/menu/TheHiveMenu.png",
	"images/menu/start0.png",
	"images/menu/start1.png",
	"images/menu/howto0.png",
	"images/menu/howto1.png",
	"images/menu/credits1.png",
	"images/menu/credits.png",
	"images/menu/palo.png",
	"images/menu/rules1.png",
	"images/menu/creditosback.png",
	"images/menu/creditsState.png",

	"images/Controls/spinner/interrogacion.png",
	"images/Controls/spinner/sumo.png",
	"images/Controls/spinner/pong.png",
	"images/Controls/spinner/apple.png",
	"images/Controls/spinner/platform.png",
	"images/Controls/spinner/race.png",
	"images/Controls/spinner/dodge.png",

	"images/board/spinnerTime1.png",
	"images/board/startMsg1.png",
	"images/board/endMsg1.png",

	"images/Controls/spinner/spinnerBack.png",
	"images/Controls/spinner/spinnertop.png",

	"images/Controls/pongControls.png",
	"images/Controls/pressA.png",
	"images/Controls/sumoControls.png",
	"images/Controls/appleControls.png",
	"images/Controls/platControls.png",
	"images/Controls/challControls.png",
	"images/Controls/bulletControls.png",

	"images/menu/rules2.png",
	"images/menu/next.png",
	"images/menu/rulesMenu.png",
	"images/menu/inst.png",
};

vector<string> Resources::jsonFiles_{
	"jsonFiles/SumoMiniGame.json",
	"jsonFiles/SumoPlayer.json",
	"jsonFiles/BackgroundObject.json",
	"jsonFiles/Board.json",
	"jsonFiles/PongMiniGame.json",
	"jsonFiles/Menu.json",
};

vector<Resources::FontInfo> Resources::fontFiles_{
	{ "fonts/ARIAL.ttf", 64 },
	{ "fonts/ARIAL.ttf", 128 },
	{ "fonts/NES-Chimera.ttf", 64 },
	{ "fonts/NES-Chimera.ttf", 128 },
	{ "fonts/Capture_it.ttf", 64 },
	{ "fonts/Capture_it.ttf", 128 },
	{ "fonts/Hack-Regular.ttf", 64 },
	{ "fonts/Hack-Regular.ttf", 128 },
	{ "fonts/Hack-Bold.ttf", 64 },
	{ "fonts/Hack-Bold.ttf", 128 },
	{ "fonts/Hack-Italic.ttf", 64 },
	{ "fonts/Hack-Italic.ttf", 128 },
	{ "fonts/Hack-BoldItalic.ttf", 64 },
	{ "fonts/Hack-BoldItalic.ttf", 128 },
};

vector<Resources::TextMsgInfo> Resources::textMsgs_{
	{ "Hello World", { colorsValues_[c_Grey_light] }, f_ARIAL_64 },
	{ "Press Any Key ...", { colorsValues_[c_Yellow_light] }, f_ARIAL_128 },
	{ "Game Over", { colorsValues_[c_Green_olive] }, f_ARIAL_128 },
	{"Let's go into Madness!",{ colorsValues_[c_Grey_light] }, f_ARIAL_128 },
	{ "Who are we?",{ colorsValues_[c_Grey_light] }, f_ARIAL_128 },

	{ "El pro de los mandos",{ colorsValues_[c_Grey_light] }, f_ARIAL_128 },
	{ "El poderoso",{ colorsValues_[c_Grey_light] }, f_ARIAL_128 },
	{ "The Architect",{ colorsValues_[c_Grey_light] }, f_ARIAL_128 },
	{ "El pelo mas sedoso del grupo",{ colorsValues_[c_Grey_light] }, f_ARIAL_128 },
	{ "Es Lluis baby, no Luis",{ colorsValues_[c_Grey_light] }, f_ARIAL_128 },
	{ "Sip, habia TPV antes de P2",{ colorsValues_[c_Grey_light] }, f_ARIAL_128 },
	{ "Pero que vives en MONCLOA!",{ colorsValues_[c_Grey_light] }, f_ARIAL_128 },
	{ "Give me that flow gyal",{ colorsValues_[c_Grey_light] }, f_ARIAL_128 },
};

vector<string> Resources::musicFiles_{
	"sound/Music/mainMenu.mp3",
	"sound/Music/board.mp3",
	//"sound/Music/credits.mp3",

	"sound/Music/sumo.mp3",
	"sound/Music/pong.wav",
	"sound/Music/apples.mp3",
	"sound/Music/race.mp3",
	"sound/Music/platform.mp3",
	"sound/Music/dodge.mp3",

};

vector<string> Resources::soundEffectFiles_{

	"sound/jump.wav",

	"sound/sumo_pop.wav",
	"sound/sumo_death.wav",

	"sound/wall_hit.wav",
	"sound/ponghit.wav",
	//"sound/dodge.wav",

	"sound/apple_hit.wav",
	"sound/apple_download.wav",
	"sound/apple_catch.wav",
	"sound/apple_drop.wav",

	"sound/platform_death.ogg",

	"sound/dodge_shot.wav",
	"sound/dodge_death.wav",

};

///////////////////////////////////////////////////////////////////

Resources::Resources(SDLGame* game) :
	game_(game),
	numOfSpritesheetsTextures_(0), spriteSheetsTextures_(nullptr),
	numOfShapeTextures_(0), shapeTextures_(nullptr),
	numOfImageTextures_(0), imageTextures_(nullptr),
	numOfTextTextures_(0), textTextures_(nullptr),
	numOfFonts_(0), fonts_(nullptr),
	numOfMusic_(0), music_(nullptr),
	numOfSoundEffects_(0), soundEffects_(nullptr) {
	//sets all resources
	setFonts(fontFiles_);
	setMusic(musicFiles_);
	setSoundEffects(soundEffectFiles_);
	setSpritesheetsTextures(spriteSheetsFiles_);
	setShapeTextures(shapeFiles_);
	setImageTextures(imageFiles_);
	setTextTextures(textMsgs_);
}

Resources::~Resources() {
	//closes all resources
	closeSpritesheetsTextures();
	closeShapeTextures();
	closeTextTextures();
	closeImageTextures();
	closeFonts();
	closeMusic();
	closeSoundEffects();
}

///////////////////////////////////////////////////////////////////

//loads all images of given vector and pushes them into spritesheetsTextures_
void Resources::setSpritesheetsTextures(vector<SpriteSheetInfo> spriteSheets) {
	closeSpritesheetsTextures();
	numOfSpritesheetsTextures_ = spriteSheets.size();
	spriteSheetsTextures_ = new Texture*[numOfSpritesheetsTextures_];
	for (int i = 0; i < numOfSpritesheetsTextures_; i++) {
		spriteSheetsTextures_[i] = new Texture(game_->getRenderer(),
			spriteSheets[i].fileName, spriteSheets[i].cols, spriteSheets[i].fils);
	}
}

//loads all shapes of given vector and pushes them into shapeTextures_
void Resources::setShapeTextures(vector<string> shapes) {
	closeShapeTextures();
	numOfShapeTextures_ = shapes.size();
	shapeTextures_ = new Texture*[numOfShapeTextures_];
	for (int i = 0; i < numOfShapeTextures_; i++) {
		shapeTextures_[i] = new Texture(game_->getRenderer(), shapes[i]);
	}
}

//loads all images of given vector and pushes them into imageTextures_
void Resources::setImageTextures(vector<string> textures) {
	closeImageTextures();
	numOfImageTextures_ = textures.size();
	imageTextures_ = new Texture*[numOfImageTextures_];
	for (int i = 0; i < numOfImageTextures_; i++) {
		imageTextures_[i] = new Texture(game_->getRenderer(), textures[i]);
	}
}

//loads all images of given vector and pushes them into imageTextures_
void Resources::setTextTextures(vector<TextMsgInfo> texts) {
	closeTextTextures();
	numOfTextTextures_ = texts.size();
	textTextures_ = new Texture*[numOfTextTextures_];
	for (int i = 0; i < numOfTextTextures_; i++) {
		string txt = texts[i].text;
		Font* font = getFont(texts[i].fontId);
		SDL_Color color = texts[i].color;
		textTextures_[i] = new Texture(game_->getRenderer(), txt, *font, color);
	}
}

//loads all fonts of given vector and pushes them into fonts_
void Resources::setFonts(vector<FontInfo> fonts) {
	closeFonts();
	numOfFonts_ = fonts.size();
	fonts_ = new Font*[numOfFonts_];
	for (int i = 0; i < numOfFonts_; i++) {
		fonts_[i] = new Font(fonts[i].fileName, fonts[i].size);
	}
}

//loads all music of given vector and pushes them into music_
void Resources::setMusic(vector<string> music) {
	closeMusic();
	numOfMusic_ = music.size();
	music_ = new Music*[numOfMusic_];
	for (int i = 0; i < numOfMusic_; i++) {
		music_[i] = new Music(music[i]);
	}
}

//loads all soundEffects of given vector and pushes them into soundEffects_
void Resources::setSoundEffects(vector<string> soundEffects) {
	closeSoundEffects();
	numOfSoundEffects_ = soundEffects.size();
	soundEffects_ = new SoundEffect*[numOfSoundEffects_];
	for (int i = 0; i < numOfSoundEffects_; i++) {
		soundEffects_[i] = new SoundEffect(soundEffects[i]);
	}
}

///////////////////////////////////////////////////////////////////

void Resources::closeShapeTextures() {
	for (int i = 0; i < numOfShapeTextures_; i++) {
		if (shapeTextures_[i] != nullptr) {
			delete shapeTextures_[i];
		}
	}
	delete[] shapeTextures_;
	numOfShapeTextures_ = 0;
}

//closes and deletes all spritesheetsTextures_
void Resources::closeSpritesheetsTextures() {
	for (int i = 0; i < numOfSpritesheetsTextures_; i++) {
		if (spriteSheetsTextures_[i] != nullptr) {
			delete spriteSheetsTextures_[i];
		}
	}
	delete[] spriteSheetsTextures_;
	numOfSpritesheetsTextures_ = 0;
}

//closes and deletes all imageTextures_
void Resources::closeImageTextures() {
	for (int i = 0; i < numOfImageTextures_; i++) {
		if (imageTextures_[i] != nullptr) {
			delete imageTextures_[i];
		}
	}
	delete[] imageTextures_;
	numOfImageTextures_ = 0;
}

//closes and deletes all textTextures_
void Resources::closeTextTextures() {
	for (int i = 0; i < numOfTextTextures_; i++) {
		if (textTextures_[i] != nullptr) {
			delete textTextures_[i];
		}
	}
	delete[] textTextures_;
	numOfTextTextures_ = 0;

}
//closes and deletes all fonts_
void Resources::closeFonts() {
	for (int i = 0; i < numOfFonts_; i++) {
		if (fonts_[i] != nullptr) {
			delete fonts_[i];
		}
	}
	delete[] fonts_;
	numOfFonts_ = 0;
}

//closes and deletes all music_
void Resources::closeMusic() {
	for (int i = 0; i < numOfMusic_; i++) {
		if (music_[i] != nullptr) {
			delete music_[i];
		}
	}
	delete[] music_;
	numOfMusic_ = 0;
}

//closes and deletes all soundEffects_
void Resources::closeSoundEffects() {
	for (int i = 0; i < numOfSoundEffects_; i++) {
		if (soundEffects_[i] != nullptr) {
			delete soundEffects_[i];
		}
	}
	delete[] soundEffects_;
	numOfSoundEffects_ = 0;
}

///////////////////////////////////////////////////////////////////

Texture* Resources::getSpriteSheetTexture(SpriteSheetId i) const {
	if (i < numOfSpritesheetsTextures_)
		return spriteSheetsTextures_[i];
	else
		return nullptr;
}

Texture * Resources::getShapeTexture(ShapeId i) const {
	if (i < numOfShapeTextures_)
		return shapeTextures_[i];
	else
		return nullptr;
}

Texture* Resources::getImageTexture(ImageId i) const {
	if (i < numOfImageTextures_)
		return imageTextures_[i];
	else
		return nullptr;
}

Texture* Resources::getTextTexture(TextId i) const {
	if (i < numOfTextTextures_)
		return textTextures_[i];
	else
		return nullptr;
}

Font* Resources::getFont(FontId i) const {
	if (i < numOfFonts_)
		return fonts_[i];
	else
		return nullptr;
}

Music* Resources::getMusic(MusicId i) const {
	if (i < numOfMusic_)
		return music_[i];
	else
		return nullptr;
}

std::string Resources::getJsonFile(jsonFilesId i) const {
	return jsonFiles_[i];
}

SoundEffect* Resources::getSoundEffect(SoundEffectId i) const {
	if (i < numOfSoundEffects_)
		return soundEffects_[i];
	else
		return nullptr;
}

//different (static, etc), maybe return color instead of pointer
//almost all functions use a color as parameter (instead of pointer)
SDL_Color* Resources::getSDLColor(ColorId i) {
	SDL_assert(i < colorsValues_.size()); //loaded before expected
	return &colorsValues_[i];
}
