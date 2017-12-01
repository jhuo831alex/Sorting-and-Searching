////////////////////////////////////////////////////////////////////////////////
// @file text_element.cpp
// @author Jiahao Huo
// @date 2016-05-01
//
// Description: Implementation file for text_element.h
//
// Known bugs: None yet!
////////////////////////////////////////////////////////////////////////////////

#include "text_element.h"
#include <list>


TextElement::TextElement() : str_(""), type_(empty) {

}

TextElement::TextElement(std::string str) : str_(normalize(str)), type_(empty) {

}

TextElement::TextElement(std::string str, TextElement::Type type) : str_(normalize(str)), type_(type) {

}

std::string TextElement::get_string() const {
	return str_;
}

void TextElement::set_string(std::string str) {
	// Normalize input before setting value of str_
	normalize(str);
	str_ = str;
}

TextElement::Type TextElement::get_type() const {
	return type_;
}

void TextElement::set_type(TextElement::Type type) {
	type_ = type;
}

std::string TextElement::capitalize() {
	std::string str = str_;

	// if the TextElement is a word, capitalize the first letter
	if (type_ == word) {
		str[0] = str[0] + 'A' - 'a';
	}

	return str;
}

Sentence::Sentence(){
	elements_ = {};
}

Sentence::Sentence(std::list<TextElement> textlist){
	elements_ = textlist;
}

void Sentence::print_as_string(){

	// Capitalize the first word in a sentence
	TextElement first_word = elements_.front();
	std::string cap_firstword = first_word.capitalize();
	std::cout << "\"" << cap_firstword << " ";

	// print the following TextElements until the last two
	std::list<TextElement>::iterator it;
	for (it = ++(elements_.begin()); it != --(--elements_.end()); ++it){
		std::cout << *it << " ";
	}

	// There is no space after the last two TextElements in a sentence
	it;
	std::cout << *it;
	++it;
	std::cout << *it << "\"";
}

bool operator==(const TextElement& lhs, const TextElement& rhs) {
	return lhs.get_string() == rhs.get_string();
}

bool operator<=(const TextElement& lhs, const TextElement& rhs) {
	return((lhs == rhs) || (lhs < rhs));
}

bool operator>=(const TextElement& lhs, const TextElement& rhs) {
	return rhs <= lhs;
}

bool operator<(const TextElement& lhs, const TextElement& rhs) {
	if (lhs.get_type() == rhs.get_type()) {
		return lhs.get_string() < rhs.get_string();
	}

	return lhs.get_type() < rhs.get_type();
}

bool operator>(const TextElement& lhs, const TextElement& rhs) {
	return rhs < lhs;
}

std::istream& operator>>(std::istream& is, TextElement& te) {
	std::string str = "";
	char ch;

	// read characters until the first letter or punctuation is encountered
	while (is) {
		is >> ch;

		// if a punctuation mark is read, set te to its value
		if (is_punctuation(ch)) {
			str += ch;
			te = TextElement(str, TextElement::punctuation);
			return is;
		}

		// break after reading the first letter
		if (is_letter(ch)) {
			break;
		}
	}

	// if a letter is read, read the rest of the word
	if (is) {

		is.unget();

		// read characters until the next whitespace, EOF or
		// or punctuation is encountered
		while (!isspace(ch) && (ch != EOF) && !is_punctuation(ch)) {
			is.get();

			// add only letters to ch
			if (is_letter(ch)) {
				str += ch;
			}

			ch = is.peek();
		}

		// create a TextElement using the letters read.
		te = TextElement(str, TextElement::word);
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, const TextElement& te) {
	return os << te.get_string();
}

std::string& normalize(std::string& str) {

	if (str.size() == 1 && is_punctuation(str[0])) {
		return str;
	}

	int i = 0;

	while (i < str.size()) {

		// if str[i] is a letter from 'a' to 'z' do nothing
		if (str[i] >= 'a' && str[i] <= 'z') {
			++i;
		}

		// if str[i] is upper case (from 'A' to 'Z'), make it lower case
		else if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = str[i] - 'A' + 'a';
			++i;
		}

		// remove all other characters
		else {
			str.erase(i, 1);
		}
	}

	return str;
}

bool is_punctuation(char ch) {
	return ((ch == '.') || (ch == '!') || (ch == '?'));
}

bool is_letter(char ch) {
	return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

int word_count(std::vector <TextElement> t){
	int count = 0;
	for (size_t i = 0; i < t.size(); ++i){
		if (t[i].get_type() == TextElement::word){
			++count;
		}
	}
	return count;
}

std::vector<Sentence> break_into_sentences(std::vector<TextElement> textvector){
	std::vector<Sentence> sentence_vector;
	std::list<TextElement> textlist;

	for (size_t i = 0; i < textvector.size()-1; ++i){

		// the end of a sentence is a punctuation and the following TextElement should be a word
		if (textvector[i].get_type() == TextElement::punctuation && textvector[i + 1].get_type() == TextElement::word){
			textlist.push_back(textvector[i]);
			sentence_vector.push_back(Sentence(textlist));
			textlist.clear();
		}
		else{
			textlist.push_back(textvector[i]);
		}
	}
	
	// Store the last sentences
	textlist.push_back(textvector[textvector.size() - 1]);
	sentence_vector.push_back(Sentence(textlist));

	return sentence_vector;
}

int is_same(TextElement text, std::vector<std::pair<TextElement,int>> pair_vec){
	for (size_t i = 0; i < pair_vec.size(); ++i){
		if (pair_vec[i].first == text){
			return i;
		}
	}
	return -1;
}

void populate_pair_vec(const std::vector<TextElement>& text_elts, std::vector<std::pair<TextElement, int>>& pair_vec){
	for (size_t i = 0; i < text_elts.size(); ++i){
		if (is_same(text_elts[i], pair_vec) != -1){
			++pair_vec[is_same(text_elts[i], pair_vec)].second;
		}
		else if (is_same(text_elts[i], pair_vec) == -1){
			pair_vec.push_back(std::make_pair(text_elts[i], 1));
		}
	}
}

int distinct_words(std::vector<std::pair<TextElement, int>> pair_vec){
	int count = pair_vec.size();
	for (size_t i = 0; i < pair_vec.size(); ++i){
		if (pair_vec[i].first.get_type() == TextElement::punctuation){
			--count;
		}
	}
	return count;
}

bool compare_pair(const std::pair<TextElement, int>& lhs, const std::pair<TextElement, int>& rhs){
	return lhs.second < rhs.second;
}

void pring_10_common_word(std::vector<std::pair<TextElement, int>> pair_vec){
	int count = 0;
	for (size_t i = pair_vec.size() - 1; i > 0; --i) {
		if (pair_vec[i].first.get_type() == TextElement::word){
			std::cout << "   " << pair_vec[i].first << " (" << pair_vec[i].second << ")" << std::endl;
			++count;
			if (count == 10){
				break;
			}
		}
	}
}

