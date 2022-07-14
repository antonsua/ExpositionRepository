#include "SoundManager.h"
#include "Music.h"
#include "SoundEffect.h"

SoundManager::SoundManager(SDLGame* game) : game_(game) {
	const Resources* resources = game_->getResources();

	menu_ = resources->getMusic(Resources::MusicId::m_menu);
	music.push_back(menu_);
	board_ = resources->getMusic(Resources::MusicId::m_board);
	music.push_back(board_);
	sumo_ = resources->getMusic(Resources::MusicId::m_sumo);
	music.push_back(sumo_);
	pong_ = resources->getMusic(Resources::MusicId::m_pong);
	music.push_back(pong_);
	apple_ = resources->getMusic(Resources::MusicId::m_apple);
	music.push_back(apple_);
	platform_ = resources->getMusic(Resources::MusicId::m_dodge);
	music.push_back(platform_);
	race_ = resources->getMusic(Resources::MusicId::m_race);
	music.push_back(race_);
	dodge_ = resources->getMusic(Resources::MusicId::m_dodge);
	music.push_back(dodge_);

	//Sumo FX
	sumoBounce_ = resources->getSoundEffect(Resources::SoundEffectId::s_bounce);
	sumoDeath_ = resources->getSoundEffect(Resources::SoundEffectId::s_sumoDeath);

	//Pong FX
	pongBlockHit_ = resources->getSoundEffect(Resources::SoundEffectId::s_Wall_Hit);
	pongPaddleHit_ = resources->getSoundEffect(Resources::SoundEffectId::s_Paddle_Hit);
	//pongDeath_ = resources->getSoundEffect(Resources::SoundEffectId::s_Paddle_Hit);

	//Apple FX
	appleDrop_ = resources->getSoundEffect(Resources::SoundEffectId::s_appleDrop);
	appleFall_ = resources->getSoundEffect(Resources::SoundEffectId::s_appleFall);
	appleHit_ = resources->getSoundEffect(Resources::SoundEffectId::s_moveTree);
	appleCatch_ = resources->getSoundEffect(Resources::SoundEffectId::s_appleCatch);

	//Platform + Race FX
	jump_ = resources->getSoundEffect(Resources::SoundEffectId::s_jump);
	platformDeath_ = resources->getSoundEffect(Resources::SoundEffectId::s_platformDeath);

	//Dodge FX
	dodgeDeath_ = resources->getSoundEffect(Resources::SoundEffectId::s_dodgeDeath);
	dodgeShot_ = resources->getSoundEffect(Resources::SoundEffectId::s_dodgeShot);

	Mix_VolumeMusic(vol_);
}

SoundManager::~SoundManager() {
	//in this case I used pointers
	for (size_t i = 0; i < music.size(); i++) {
		music[i]->close();
	}
}

void SoundManager::receive(Message* msg) {
	switch (msg->id_) {

	case STATE_MENU:
	case STATE_END_GAME:
		menu_->play(50);
		idMusic = 0;
		break;
	case STATE_POP_MINIGAME:
	case STATE_BOARD:
		board_->play(50);
		idMusic = 1;
		break;
	case STATE_SUMO:
		sumo_->play(50);
		idMusic = 2;
		break;
	case STATE_PONG:
		pong_->play(50);
		idMusic = 3;
		break;
	case STATE_APPLE:
		apple_->play(50);
		idMusic = 4;
		break;
	case STATE_PLATFORM:
		platform_->play(50);
		idMusic = 5;
		break;
	case STATE_RACE:
		race_->play(50);
		idMusic = 6;
		break;
	case STATE_DODGE:
		dodge_->play(50);
		idMusic = 7;
		break;

	case STATE_POP:
		break;

		//Sumo FX
	case SUMOGAME_OUT_FROM_AREA:
		sumoDeath_->play();
		break;
	case SUMO_BOUNCE:
		sumoBounce_->play();
		break;

		//Pong FX
	case BALL_BLOCK_COLLISION:
		pongBlockHit_->play();
		break;
	case BALL_PADDLE_COLLISION:
		pongPaddleHit_->play();
		break;

		//Apple FX
	case PLAYER_CAUGTH_APPLE:
		appleCatch_->play();
		break;
	case APPLE_TOUCHED_FLOOR:
		appleDrop_->play();
		break;
	case DETONATE_TREE:
		appleFall_->play();
		break;
	case SHAKING_TREE:
		appleHit_->play();
		break;

		//Platform and Race FX
	case JUMP:
		jump_->play();
		break;
	case PLATFORM_DEATH:
	case RACE_DEATH:
		platformDeath_->play();
		break;

		//Dodge FX
	case DODGE_SHOT:
		dodgeShot_->play();
		break;
	case DODGE_DEATH:
		dodgeDeath_->play();
		break;


	case VOLUP:
		vol_ += volAdd_;
		vol_ > MIX_MAX_VOLUME ? vol_ = MIX_MAX_VOLUME : vol_ = vol_;
		Mix_Volume(-1, vol_);
		Mix_VolumeMusic(vol_);
		break;
	case VOLDOWN:
		vol_ -= volAdd_;
		vol_ < 0 ? vol_ = 0 : vol_ = vol_;
		Mix_Volume(-1, vol_);
		Mix_VolumeMusic(vol_);
		break;
	}
}
