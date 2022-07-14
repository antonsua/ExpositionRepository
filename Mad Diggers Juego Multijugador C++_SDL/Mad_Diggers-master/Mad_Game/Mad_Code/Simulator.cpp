#include "Simulator.h"
#include "BoardState.h" //fowarded
#include <Windows.h>
#include "FileNotFoundError.h"
#include "FileFormatError.h"

const int Simulator::_MAX_REPETITIONS_TO_LOG_ = 101;

const string Simulator::_RELATIVE_PATH_ = "simulations/";
const string Simulator::_FILENAME_EXTENSION_ = ".sim";
const string Simulator::_LOG_EXTENSION_ = ".simlog";
const string Simulator::_FILENAME_DATA_ = "_data";
const string Simulator::_FILENAME_LOG_ = "_log";
const string Simulator::_FILENAME_STATS_ = "_stats";

const string Simulator::_FILENAME_SEPARATOR_ = "_";
const string Simulator::_FILENAME_ITERATORS_ = "_iterator.iter";
const string Simulator::_RELATIVE_LOG_PATH_ = "simulations/logs/";
//const string Simulator::_PATH_FOR_FOLDERS_ = "C:\hlocal\Mad_Diggers-master\Mad_Game\Mad_Code\simulations\logs";

Simulator::Simulator(Game* game, size_t numPlayers) :
	GameInputComponent(game), console_log_SaveFile_(true)
{
	numPlayers_ = numPlayers;
	file_ = "0";
	times_ = 500;
}

Simulator::~Simulator()
{
}

///////////////////////////////////////////////////////////////////

void Simulator::handleEvents(Uint32 time, const SDL_Event & event)
{
	if (event.type == SDL_KEYDOWN) {
		switch (event.key.keysym.sym)
		{
		case SDLK_q: //execute simulation
			simulate(true);
			break;
		case SDLK_s: //execute simulation
			simulate(false);
			break;
		case SDLK_z: //execute simulation and store it
			simulateAndSaveIndividual();
			break;
		case SDLK_x: //execute 50 simulations and store them
			simulateRepited(times_, true);
			break;
		case SDLK_a: //calculate statistics
			calculateStatistics();
			break;
		}
	}
}
void Simulator::logControls()
{
	cout << "//  * Q : RELEASE THE BEES // simulates with bees on" << endl;
	cout << "//  * S : Simulate the configured match // resets current one" << endl;
	cout << "//  * Z : Simulate and save the configured match" << endl;
	cout << "//  * X : Simulate and save x50 // SHOULD SWITCH LOG OFF" << endl;
	cout << "//  * A : Calculate statistics // (stores them)" << endl;
	cout << "//  " << endl;
}

///////////////////////////////////////////////////////////////////

void Simulator::receive(Message* msg)
{
	if (isActive()) switch (msg->id_)
	{
	case BOARD_LOG_CONTROLS: {
		logControls();
		break;
	}
	case BOARD_GAMEOVER: {
		//cast for specific msg type
		BoardMessage_GameOverResults* specificMsg =
			static_cast<BoardMessage_GameOverResults*> (msg);

		scores_ = specificMsg->playerScores_;
		break;
	}
	}
}
///////////////////////////////////////////////////////////////////

void Simulator::simulateRepited(size_t times, bool save)
{
	if (times > _MAX_REPETITIONS_TO_LOG_)
	{
		cout << endl << "///// OVER " << _MAX_REPETITIONS_TO_LOG_ << " SIMULATIONS ///// " << " total log shut down /////" << endl << endl;
		console_log_SaveFile_ = false;
	}

	if (!save) for (size_t i = 0; i < times; i++) simulate(false);
	else for (size_t i = 0; i < times; i++) simulateAndSaveIndividual();

	//ignores if console log is activated
	cout << endl << "///// AMOUNT ///// " << times << " /////" << endl << endl;
	console_log_SaveFile_ = true;
}

void Simulator::simulate(bool bees)
{
	//cout << endl << "///// RESET ///// ONGOING GAME CANCELLED /////" << endl << endl;
	send(&Message(BOARD_RESET));

	string data_path = _RELATIVE_PATH_ + file_ + _FILENAME_DATA_ + _FILENAME_EXTENSION_;
	stringstream buffer = loadBufferFromFile(data_path);
	loadDataFromBuffer(buffer);

	for (size_t i = 0; i < sim_rounds_data.size(); i++)
	{
		for (size_t j = 0; j < sim_rounds_data[i].size(); j++)
		{
			for (int k = 0; k < sim_rounds_data[i][j]; k++)
			{
				send(&BoardMessage_numPlayerInfo(j, bees));
			}
		}
	}

	if (console_log_SaveFile_) {
		cout << "///// SIMULATION FINISHED ///// " << data_path << " /////" << endl;
	}
}

void Simulator::simulateAndSave()
{
	simulate(false);

	string data_path = _RELATIVE_PATH_ + file_ + _FILENAME_DATA_ + _FILENAME_EXTENSION_;
	string log_path = _RELATIVE_PATH_ + file_ + _FILENAME_LOG_ + _LOG_EXTENSION_;

	checkFile(log_path, data_path + " results: ");

	//all logs to the same file
	stringstream buffer;
	buffer = loadBufferFromFile(log_path);
	buffer << endl;

	saveResultsToBuffer(buffer);

	//write the file
	ofstream log_file;
	log_file.open(log_path);
	log_file << buffer.rdbuf(); //writes all the buffer
	log_file.close();

	if (console_log_SaveFile_) {
		cout << "///// SIMULATION STORED ///// " << log_path << " /////" << endl;
	}
}

void Simulator::simulateAndSaveIndividual()
{
	simulate(false);
	int numIter = getnumIter();

	string data_path = _RELATIVE_PATH_ + file_ + _FILENAME_DATA_ + _FILENAME_EXTENSION_;
	string log_path = _RELATIVE_LOG_PATH_ + file_ + _FILENAME_LOG_ + _FILENAME_SEPARATOR_ + to_string(numIter) + _LOG_EXTENSION_;

	//Add +1 to iterator file
	saveNumIter(numIter);

	stringstream buffer;
	saveResultsToBuffer(buffer);

	//write the file
	ofstream log_file(log_path);
	log_file << buffer.rdbuf(); //writes all the buffer
	log_file.close();

	if (console_log_SaveFile_) {
		cout << "///// SIMULATION STORED ///// " << log_path << " /////" << endl;
	}
}

///////////////////////////////////////////////////////////////////

void Simulator::calculateStatistics()
{
	//load the buffer and then the data
	//vector <vector<int>> data = loadStats();
	vector <vector<int>> data = loadStatsIndividual();

	//different statistics vectors
	vector<int> freq; freq.resize(numPlayers_, 0);
	vector<int> zeros; zeros.resize(numPlayers_, 0);

	//calculate specific statistics per match
	for (size_t i = 0; i < data.size(); i++)
	{
		checkWinFrequences(data[i], freq);
		checkZeroFrequences(data[i], zeros);
	}

	cout << endl << "///// Number of matches " << " ///// " << data.size() << endl << endl;

	stringstream buffer;
	string data_path = _RELATIVE_PATH_ + file_ + _FILENAME_DATA_ + _FILENAME_EXTENSION_;
	buffer << data_path << " statistics of " << data.size() << " matches:" << endl << endl;

	outputStatData(freq, "Wins freq", buffer, data.size());
	outputStatData(zeros, "Zeros freq", buffer, data.size());

	//save the stats in a file
	string stats_path = _RELATIVE_LOG_PATH_ + _FILENAME_SEPARATOR_ + file_ + _FILENAME_STATS_ + _FILENAME_EXTENSION_;
	ofstream stats_file;
	stats_file.open(stats_path);
	stats_file << buffer.rdbuf(); //writes all the buffer
	stats_file.close();

	cout << "\n///// STATISTICS STORED ///// " << stats_path << " /////" << endl << endl;
}

vector<vector<int>> Simulator::loadStats()
{
	string log_path = _RELATIVE_PATH_ + file_ + _FILENAME_LOG_ + _LOG_EXTENSION_;
	stringstream buffer;
	vector <vector<int>> data;

	buffer = loadBufferFromFile(log_path);
	data = loadLogFromBuffer(buffer);
	return data;
}

vector<vector<int>> Simulator::loadStatsIndividual()
{
	string log_path;
	stringstream buffer;
	vector <vector<int>> data;

	int numIter = getnumIter();
	for (size_t i = 0; i < numIter; i++)
	{
		log_path = _RELATIVE_LOG_PATH_ + file_ + _FILENAME_LOG_ + _FILENAME_SEPARATOR_ + to_string(i) + _LOG_EXTENSION_;
		buffer = loadBufferFromFile(log_path);
		data.push_back(loadLogFromBufferIndividual(buffer));
	}
	return data;
}

///////////////////////////////////////////////////////////////////

void Simulator::checkWinFrequences(const vector<int> dataMatch, vector<int> & freq)
{
	int tmpTop = 0;

	for (size_t j = 0 + 1; j < numPlayers_; j++)
	{
		if (dataMatch[j] > dataMatch[tmpTop]) tmpTop = j;
	}

	freq[tmpTop]++;
}

void Simulator::checkZeroFrequences(const vector<int> dataMatch, vector<int> & zeros)
{
	for (size_t j = 0 + 1; j < numPlayers_; j++)
	{
		if (dataMatch[j] == 0) zeros[j]++;
	}
}

///////////////////////////////////////////////////////////////////

void Simulator::outputStatData(const vector<int> stat, string dataName, stringstream & buffer, const int n)
{
	cout << "///// " << dataName << " ///// P1< ";
	cout << stat[0] << " /// P2< " << stat[1] << " /// P3< ";
	cout << stat[2] << " /// P4< " << stat[3] << endl;

	cout << "///// " << dataName << ":" << n << " ///// P1< ";
	cout << (float)stat[0] / n << " /// P2< " << (float)stat[1] / n << " /// P3< ";
	cout << (float)stat[2] / n << " /// P4< " << (float)stat[3] / n << endl << endl;

	saveStatsToBuffer(stat, dataName, buffer, n);
}

void Simulator::saveStatsToBuffer(const vector<int> stat, string dataName, stringstream & buffer, const int n)
{
	//abs freq
	buffer << dataName << " ->  ";
	for (size_t i = 0; i < stat.size(); i++) buffer << stat[i] << " / ";
	buffer << endl;

	//rel freq
	buffer << dataName << ":" << n << " ->  ";
	for (size_t i = 0; i < stat.size(); i++) buffer << (float) stat[i] / n << " / ";
	buffer << endl;
	buffer << endl;
}

void Simulator::saveResultsToBuffer(stringstream & buffer)
{
	//atm just write raw results
	for (size_t i = 0; i < scores_.size(); i++) buffer << scores_[i] << " ";
}

///////////////////////////////////////////////////////////////////

stringstream Simulator::loadBufferFromFile(string filename)
{
	ifstream file(filename);
	stringstream buffer;

	if (file.fail()) throw FileNotFoundError("(load) " + filename);

	//loads the file content in the stringstream
	buffer << file.rdbuf();
	file.close();

	return buffer;
}

void Simulator::loadDataFromBuffer(stringstream & buffer)
{
	//some exceptions here

	buffer >> sim_last_round;
	buffer >> sim_first_round; //not used atm
	buffer >> rolls_per_round; //not used atm

	sim_rounds_data.clear();
	sim_rounds_data.resize(sim_last_round);

	int tmp;
	for (size_t i = 0; i < sim_last_round; i++)
	{
		for (size_t j = 0; j < numPlayers_; j++)
		{
			buffer >> tmp;
			sim_rounds_data[i].push_back(tmp);
		}
	}
}

vector<vector<int>> Simulator::loadLogFromBuffer(stringstream & buffer)
{
	vector<vector<int>> data;

	//delete some trash strings
	string nonData; size_t nonDataStrings = 2;
	for (size_t i = 0; i < nonDataStrings; i++) buffer >> nonData;

	int tmpData;
	while (!buffer.eof())
	{
		vector<int> tmpVector;

		for (size_t n = 0; n < numPlayers_; n++)
		{
			buffer >> tmpData;
			tmpVector.push_back(tmpData);
		}

		data.push_back(tmpVector);
	}
	data.pop_back(); //last one is trash

	return data;
}

vector<int> Simulator::loadLogFromBufferIndividual(stringstream& buffer)
{
	vector<int> data;

	int tmpData;
	while (!buffer.eof())
	{
		for (size_t n = 0; n < numPlayers_; n++) {
			buffer >> tmpData;
			data.push_back(tmpData);
		}
	}
	return data;
}

///////////////////////////////////////////////////////////////////

int Simulator::getnumIter()
{
	string it_path = _RELATIVE_LOG_PATH_ + _FILENAME_SEPARATOR_ + file_ + _FILENAME_ITERATORS_;

	checkFile(it_path, to_string(0));

	//Open Iterator file
	ifstream iterator_seeker(it_path);
	int numIter = 0;

	iterator_seeker >> numIter;
	iterator_seeker.clear();
	iterator_seeker.close();
	return numIter;
}

void Simulator::saveNumIter(int num)
{
	string it_path = _RELATIVE_LOG_PATH_ + _FILENAME_SEPARATOR_ + file_ + _FILENAME_ITERATORS_;
	num += 1;

	ofstream iterator_writer(it_path);
	iterator_writer << num;
	iterator_writer.close();
}

void Simulator::checkFile(string path, string insert)
{
	//create new file if unexistent
	ifstream fileChecker(path);
	if (fileChecker.fail()) {
		ofstream newFile;
		newFile.open(path);
		newFile << insert;
		newFile.close();
	}
	fileChecker.close();
}