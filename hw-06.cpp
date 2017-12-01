////////////////////////////////////////////////////////////////////////////////
// @file hw-06.cpp
// @mainpage
// @author Jiahao Huo
// @date 2016-05-18
//
// Description: This program prompts the user to input a file. Then, the program
// reveals the number of text elements, number of words, number of distinct text
// elements, and number of distinct words. The program also lists 10 most common 
// words in the file in decreasing order.
//
// This program also shows the number of sentences in the file, then print out
// the first and last sentence in the file. Lastly, the program asks the user to 
// put in the index number of the sentence he/she wish to read and then print it.
//
// Known bugs: None yet!
////////////////////////////////////////////////////////////////////////////////

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <utility>
#include <algorithm>
#include "text_element.h"

int main() {

	TextElement te;
	std::string input;
	std::vector<TextElement> text_elts;
	std::vector<Sentence> sentence_vector;
	std::vector<std::pair<TextElement, int>> pair_vec;

	std::cout << "Enter a filename to read: ";
	std::cin >> input;
	std::ifstream is;
	is.open(input.c_str());

	while (is >> te) {
		if (te.get_string() != "") {
			text_elts.push_back(te);
		}
	}

	populate_pair_vec(text_elts, pair_vec);

	std::sort(pair_vec.begin(), pair_vec.end(), compare_pair);

	sentence_vector = break_into_sentences(text_elts);

	std::cout << "\"" << input << "\" contains: " << std::endl << std::endl;

	std::cout << "*   " << text_elts.size() << " text elements." << std::endl
		<< "*   " << word_count(text_elts) << " words." << std::endl
		<< "*   " << pair_vec.size() << " distinct text elements." << std::endl
		<< "*   " << distinct_words(pair_vec) << " distinct words." << std::endl << std::endl;

	std::cout << "The 10 most common words are:" << std::endl << std::endl;
	pring_10_common_word(pair_vec);
	std::cout << std::endl;

	std::cout << "Breaking up into sentences..." << std::endl
		<< "   The text contains " << sentence_vector.size() << " sentences." << std::endl << std::endl;

	std::cout << "The first sentence is: " << std::endl << std::endl << "   ";
	sentence_vector[0].print_as_string();
	std::cout << std::endl << std::endl;
	std::cout << "The last sentence is: " << std::endl << std::endl << "   ";
	sentence_vector[sentence_vector.size() - 1].print_as_string();
	std::cout << std::endl << std::endl;

	int sentence_num;
	std::cout << "Which sentence would you like to read?: ";
	std::cin >> sentence_num;
	std::cout << std::endl << "   ";
	sentence_vector[sentence_num].print_as_string();
	std::cout << std::endl;
	
	return 0;
}


