//#ifndef BOARDSQUAREMANAGER_H_
//#define BOARDSQUAREMANAGER_H_
//
//#include "BoardSquare.h"
//#include "Emitter.h"
//
////#include "BasicMotionPhysics.h"
//
//#include "SkeletonRenderer.h"
//#include "ImageRenderer.h"
//#include "FillRectRenderer.h"
//
//class BoardSquaresManager : public GameObject, public Emitter, public Listener {
//
//public:
//	BoardSquaresManager(Game* game);
//	virtual ~BoardSquaresManager();
//
//	virtual void handleInput(Uint32 time, const SDL_Event& event); //nothing
//	virtual void update(Uint32 time);
//	virtual void render(Uint32 time);
//
//	virtual void receive(Message* msg);
//	virtual std::vector<BoardSquare*>& getSquares();
//
//private:
//	BoardSquare* getBee();
//	void initSquares();
//	void createBee(int generations, Vector2D pos, Vector2D vel);
//	void setAllInactive();
//
//	vector<BoardSquare*> bees_;
//
//	FillRectRenderer rect_RC_;
//	ImageRenderer text_RC_;
//	SkeletonRenderer debug_RC_;
//
//	int numOfSquares_; //active squares
//};
//
//#endif /* BOARDSQUAREMANAGER_H_ */
