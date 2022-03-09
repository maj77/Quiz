#pragma once
#include <iostream>
#include <string>
#include <locale>
#include <clocale>
#include <vector>
#include <map>
#include <fstream>
#include <random>
#include <algorithm>
#include <cstdlib>


#define file_path "Questions_Answers.txt" 
using std::cout, std::cin, std::endl, std::vector, std::string,
	  std::fstream, std::map;

class Game {
private:
	double g_points;
	bool file_loaded_flag;
	bool questions_prepared_flag;
	map<int, string> g_questions;
	map<int, string> g_answers;
	map<int, string> g_correct_answers;
public:
	/**
	 * .Constructor
	 */
	Game();

	/**
	 * .Destructor
	 */
	~Game();

	/**
	* .Method reads questions and answers form file and puts it in maps.
	* 
	* \param file_path
	*/
	void read_file();

	/**
	* .Method that chooses correct answer from file and modifies answer string 
	*  so it can be printed.
	* \param g_answers	- map containing answers to questions
	* \param g_correct_answers - map containing letter of correct answer
	*/
	void prepare_questions();
	
	/**
	* .Method picks 10 random questions, ask user to answer them
	* 
	* \return vector<int> of question numbers
	*/
	vector<int> pick_questions();
	
	/**
	* .Method asks questions and checks if answer is correct
	*  if is then add +1 to return value
	* 
	* \param vector<int> which contains question numbers
	* \returns int score
	*/
	int play(vector<int>);

	/**
	 * .Method prints main menu and interacts with user.
	 * 
	 */
	void main_menu();

	/**
	 * .Method checks if answer is A, B, C, D or EXIT
	 * 
	 * \param Answer string
	 * \return True/False
	 */
	bool check_answer(string);

	/**
	 * .Method calculates grade from earned points
	 * 
	 */
	void calculate_grade();
};

