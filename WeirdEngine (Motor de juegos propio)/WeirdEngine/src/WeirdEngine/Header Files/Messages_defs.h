#pragma once

#include <vector>
#include <string>
#include "Utilities\Vector3.h"

#include "Messages_decl.h"

class EntityC;

namespace msg {

	struct Message {
		Message(msg::MessageType type, msg::ObjectId sender) :
			type_(type), sender_(sender), destination_(msg::None) {
		}
		Message(msg::MessageType type, msg::ObjectId sender, msg::ObjectId destination) :
			type_(type), sender_(sender), destination_(destination) {
		}
		msg::MessageType type_;
		msg::ObjectId sender_;
		msg::ObjectId destination_;
	};

	struct Move : public msg::Message{
		Move(msg::ObjectId sender, msg::ObjectId destination, Vector3 dir) :
			Message(msg::MOVE, sender, destination), _dir(dir) {}
		Vector3 _dir;
	};

	struct Jump : public msg::Message {
		Jump(msg::ObjectId sender, msg::ObjectId destination, Vector3 dir) :
			Message(msg::JUMP, sender, destination), _dir(dir) {}
		Vector3 _dir;
	};

	struct Close_Win : public msg::Message {
		Close_Win(msg::ObjectId sender, msg::ObjectId dest) :
			Message(msg::CLOSE_WIN, sender, dest) {}
	};

	struct Colision : public msg::Message {
		Colision(msg::ObjectId sender, msg::ObjectId dest, std::string type, bool doIt) :
			Message(msg::COLISION, sender, dest), _type(type), _doIt(doIt) {}
		std::string _type;
		bool _doIt;
	};

	struct SwitchComp : public msg::Message {
		SwitchComp(msg::ObjectId sender, msg::ObjectId dest) :
			Message(msg::SWITCH_COMP, sender, dest) {}
	};

	struct SceneOver : public msg::Message {
		SceneOver(msg::ObjectId sender, msg::ObjectId dest) :
			Message(msg::SCENE_OVER, sender, dest) {}
	};

	struct SceneStart : public msg::Message {
		SceneStart(msg::ObjectId sender, msg::ObjectId dest) :
			Message(msg::SCENE_START, sender, dest) {}
	};

	struct Hability : public msg::Message {
		Hability(msg::ObjectId sender, msg::ObjectId dest, std::string type) :
			Message(msg::HABILITY, sender, dest), _type(type) {}
		std::string _type;
	};

	struct PlaySound : public msg::Message {
		PlaySound(msg::ObjectId sender, msg::ObjectId dest, std::string name) :
			Message(msg::PLAY_SOUND, sender, dest), _name(name) {}
		std::string _name;
	};
};