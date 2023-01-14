#define MAX_SIZE_HIGHSCORE 10

struct _score {
	long long int score;
	double time;
};

void addScore(long long int scoreToSave, double timeToSave);

//bool showScore(_screen screen, char mode);

void orderByTime(_score ordered[]);

void orderByScore(_score ordered[]);
