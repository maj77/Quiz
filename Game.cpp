#include "Game.h"


Game::Game() :g_points{ 0 }, questions_prepared_flag{ 0 } {}
Game::~Game() {};

void Game::read_file() {
	fstream file(file_path);
	if (file.is_open()) {
		int text_line = 0;
		int question_number = 0;
		string line;

		while (getline(file, line)) {
			text_line++;
			if (text_line % 2 != 0) {
				question_number++;						// on every odd line increment question number
				g_questions[question_number] = line;		// questions are in odd lines of .txt file
			}
			if (text_line % 2 == 0) g_answers[question_number] = line;		// answers are in even lines
		}
		cout << "file opened succesfully! " << endl;
		file_loaded_flag = true;
		file.close();
	}
	else {
		cout << "Program couldn't open file! " << endl;
		file_loaded_flag = false;
		file.close();
	}
}

void Game::prepare_questions(){
	
	int start = 0;
	int c_end = 0;
	int map_size = g_answers.size();
	//TODO: spwardzenie czy plik wejsciowy ma poprawny format poprzez np ustalenie cyz na poczatku jest nawias ostry z prawidlowa odpowiedzia
	for (int a_nr = 1; a_nr <= map_size; a_nr++) {

		// find correct answer letter which is befoer '>' sign
		c_end = g_answers[a_nr].find('>');		
		g_correct_answers[a_nr] = g_answers[a_nr][c_end - 1];
		
		// cut off correct answer letter
		g_answers[a_nr] = g_answers[a_nr].substr(c_end);		
		
		// get string containing only answers
		start = g_answers[a_nr].find(':', c_end);
		g_answers[a_nr] = g_answers[a_nr].substr(start + 2);		


		start = 0;
		c_end = 0;
	}

	for (int q_nr = 1; q_nr <= map_size; q_nr++) {
		
		// cut off "Question" from question string.
		c_end = g_questions[q_nr].find(':');
		g_questions[q_nr] = g_questions[q_nr].substr(c_end + 1);
		
		c_end = 0;
	}
}

vector<int> Game::pick_questions(){
	int question_quantity = g_questions.size();
	vector<int> question_nr;
	
	// create vector containing question numbers
	for (int i = 1; i <= question_quantity; i++) question_nr.push_back(i);

	//create random generator and shuffle values in vector
	std::random_device rd;
	std::mt19937 gen{ rd() };
	std::ranges::shuffle(question_nr, gen);
	
	// shorten vector to 10
	question_nr.resize(10);

	return question_nr;
}

int Game::play(vector<int> question_nr) {
	g_points = 0;
	string answer;
	
	cout << "Answer 10 questions, to exit to main menu type: EXIT" << endl;
	// print questions and answers
	for (int i = 0; i < 10; i++) {

		cout << "==============================================================" << endl;
		cout << "Question " << i + 1 << ". " << g_questions[question_nr[i]] << endl;
		cout << g_answers[question_nr[i]] << endl;
		cout << "-------------------------------------------------------------" << endl;
		
		// user input
		cout << "Your answer: ";
		cin >> answer;
		
		// transform answer to upper case
		std::transform(answer.begin(), answer.end(), answer.begin(), ::toupper);

		//check if answer is A, B, C, D or EXIT
		if (check_answer(answer)) {	
			if (answer.compare(g_correct_answers[question_nr[i]]) == 0) {	// check if answer is correct
				g_points++;
					cout << "Good answer! +1 point" << endl << endl;
			}
			else if (answer.compare("EXIT") == 0) {
				system("CLS");
				return 0;
			}
			else {
				cout << "Bad answer! correct answer is: " << g_correct_answers[question_nr[i]] << endl << endl;
			}
		}
		else {	// if answer isn't A, B, C, or EXIT then:
			cin.clear();				// ignore input buffer 
			cin.ignore(256, '\n');		// ignore the line change
			i--;
			cout << "WRONG INPUT: Type A, B, C, D or EXIT" << endl;
		}
		
		cout << "Current points: " << g_points << endl << endl;
	}

	cout << "Total Points: " << g_points << endl;
	calculate_grade();
	cout << "Click enter to continue" << endl;
	cin.get();
	cin.get();
	system("CLS");
	
	return g_points;
}
void Game::main_menu() {
	int option = 0;
	cout << "-------------------------------------------" << endl;
	cout << "                Main Menu                  " << endl;
	cout << "-------------------------------------------" << endl;
	cout << "1. Load file." << endl;
	cout << "2. Start Quiz." << endl;
	cout << "3. Exit." << endl;
	
	cin >> option;    
	system("CLS");

	// if input isn't integer then print error
	if (cin.fail()) {											
		cout << "Wrong input. Please enter 1, 2 or 3" << endl;
		cin.clear();
		cin.ignore(256, '\n');		// ignore the line change
	}
	else {
		if (option == 1) {
			read_file();
			prepare_questions();
			questions_prepared_flag = 1;
			cout << "Type 2 to start quiz." << endl;
		}
		else if (option == 2) {
			if (questions_prepared_flag && file_loaded_flag) { // method pick_questions picks 10 random questions and give it to play() method which prints them out and asks	user to answer.	
				play(pick_questions());
			}
			else {
				cout << "Questions not loaded, loading it automatically." << endl;
				read_file();
				prepare_questions();
				questions_prepared_flag = 1;
			}
		}
		else if (option == 3) {
			cout << "Program closed." << endl;
			exit(1);
		}
		else {			// if input is integer but it isn't 1, 2 or 3 print error
			cout << "Wrong input. Please enter 1, 2 or 3\n";		
		}
	}
}

bool Game::check_answer(string answer) {
	if (answer.compare("A") == 0)
		return true;
	else if (answer.compare("B") == 0)
		return true;
	else if (answer.compare("C") == 0)
		return true;
	else if (answer.compare("D") == 0)
		return true;
	else if (answer.compare("EXIT") == 0)
		return true;
	else
		return false;
}

void Game::calculate_grade(){
	double percentage_grade = ((double)g_points / (double)10) * (double)100;
	double grade = 0;
	if (percentage_grade > 90) grade = 5;
	else if (percentage_grade > 80) grade = 4.5;
	else if (percentage_grade > 70) grade = 4;
	else if (percentage_grade > 60) grade = 3.5;
	else if (percentage_grade >= 50) grade = 3;
	else grade = 2;
	cout << "Your grade is: " << percentage_grade << "%" << " = " << grade << endl;
}