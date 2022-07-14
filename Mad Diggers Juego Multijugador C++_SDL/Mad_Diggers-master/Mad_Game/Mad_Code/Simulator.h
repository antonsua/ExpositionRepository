//Mad_Diggers - dimateos

#ifndef SIMULATOR_H_
#define SIMULATOR_H_

#include <string>
#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Emitter.h"
#include "GameInputComponent.h"

using namespace std;

class Simulator: public GameInputComponent, public Emitter, public Listener  {

public:
	Simulator(Game* game, size_t numPlayers);
	virtual ~Simulator();

	virtual void handleEvents(Uint32 time, const SDL_Event& event);
	void logControls();
	void receive(Message* msg);

	///////////////////////////////////////////////////////////////////

	void simulate(bool bees);
	void simulateAndSave();
	void simulateAndSaveIndividual();
	void simulateRepited(size_t times, bool save);
	void calculateStatistics();

	//void saveStatsToFile(stringstream & buffer);
	vector<vector<int>> loadStats();
	vector<vector<int>> loadStatsIndividual();

private:
	static const int _MAX_REPETITIONS_TO_LOG_;

	static const string _RELATIVE_PATH_;
	static const string _FILENAME_EXTENSION_;
	static const string _LOG_EXTENSION_;
	static const string _FILENAME_DATA_;
	static const string _FILENAME_LOG_;
	static const string _FILENAME_STATS_;

	static const string _FILENAME_SEPARATOR_;
	static const string _FILENAME_ITERATORS_;
	static const string _RELATIVE_LOG_PATH_;
	static const string _PATH_FOR_FOLDERS_;

	///////////////////////////////////////////////////////////////////

	void checkWinFrequences(const vector<int> dataMatch, vector<int> & freq);
	void checkZeroFrequences(const vector<int> dataMatch, vector<int>& zeros);

	void outputStatData(const vector<int> stat, string dataName, stringstream & buffer, const int n);
	void saveStatsToBuffer(const vector<int> stat, string dataName, stringstream & buffer, const int n);

	void saveResultsToBuffer(stringstream & buffer);

	///////////////////////////////////////////////////////////////////

	stringstream loadBufferFromFile(string filename);
	void loadDataFromBuffer(stringstream & buffer);
	vector<vector<int>> loadLogFromBuffer(stringstream & buffer);
	vector<int> loadLogFromBufferIndividual(stringstream &buffer);

	///////////////////////////////////////////////////////////////////

	int getnumIter();
	void saveNumIter(int num);

	void checkFile(string path, string insert);

	//////////////////////////////////////////////////////////////////

	string file_;
	size_t times_;
	size_t numPlayers_;

	bool console_log_SaveFile_;

	vector<int> scores_;

	size_t sim_last_round;
	size_t sim_first_round;
	size_t rolls_per_round;

	vector<vector<int>> sim_rounds_data;
};

#endif /* SIMULATOR_H_ */