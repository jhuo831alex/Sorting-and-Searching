////////////////////////////////////////////////////////////////////////////////
// @file text_element.h
// @author Jiahao Huo
// @date 2016-05-18
//
// Description: This file contains the declaration of class TextElement and Sentence,
// operators of TextElement, and non-member functions of class TextElement and 
// Sentence.
//
// Known bugs: None yet!
////////////////////////////////////////////////////////////////////////////////

#ifndef TEXT_ELEMENT_H
#define TEXT_ELEMENT_H

#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <utility>

////////////////////////////////////////////////////////////////////////////////
// @class TextElement
// @brief A TextElement is a small piece of text which may be a word or
// punctuation. 
// ordering among punctuation is just ASCII ordering. In the ordering, words
// always p
//
// TextElements can be read, written, and compared. Comparison
// of words is alphabetical (dictionary "lexicographic" order), while the
// ordering among punctuation is just ASCII ordering. In the ordering, words
// always precede punctuation. The text of a TextElement is stored as a
// formatted std::string. For a word, the string is all lower-case, containing
// only the letters 'a' through 'z'. A punctuation TextElement has a string
// consisting of a single punctuation mark, '.', '!', or '?'. All other text
// is ignored!
////////////////////////////////////////////////////////////////////////////////

class TextElement{
public:
	enum Type { word, punctuation, empty };

	TextElement();
	TextElement(std::string str);
	TextElement(std::string str, TextElement::Type type);


	// @return the string str_ which stores the value of the TextElement
	std::string get_string() const;

	// Set the string str_ which stores the value of the TextElement. The string
	// str is "normalized" to adhere to the str_ specification (see the
	// TextElement class description).
	// @param str is the std::string containing the (possibly unformatted) text
	void set_string(const std::string str);

	// @return th TextElement::Type of the TextElement
	TextElement::Type get_type() const;

	// Set the TextElement::Type of the TextElement.
	// @param type is the new TextElement::Type for the TextElement.
	void set_type(TextElement::Type type);

	// @return a string which is a copy of str_ with the first letter capitalized.
	std::string capitalize();

private:
	std::string str_;
	TextElement::Type type_;
};

////////////////////////////////////////////////////////////////////////////////
// @class Sentence
// @brief A Sentence is a list of TextElements
//
// A list of TextElements is stored as a Sentence. Sentences can be printed out
// with capitalized first character and proper spaces between words.
////////////////////////////////////////////////////////////////////////////////

class Sentence {
public:
	
	// Default constructor of Sentence
	Sentence();

	// Store a list of TextElement in a Sentence
	Sentence(std::list <TextElement> textlist);

	// Print the Sentence
	// Capitalize the first character
	// spaces between TextElements except for the last two (the last word and the punctuation)
	void print_as_string();
private:
	std::list <TextElement> elements_;
};

// Test if two TextElements are equal (i.e., have the same formatted str_)
// @param lhs a TextElement to the left of "=="
// @param rhs a TextElement to the right of "=="
// @return true if and only if lhs.str_ = rhs.str_
bool operator==(const TextElement& lhs, const TextElement& rhs);

// The order of TextElements is defined as follows: if lhs and rhs are the
// same TextElement::Type, then the order is lexicographic (dictionary) order.
// Non-alphabet characters have their ASCII values. If lhs and rhs have
// different TextElement::Type, then the order should be
// word < punctuation < empty
bool operator<(const TextElement& lhs, const TextElement& rhs);
bool operator>(const TextElement& lhs, const TextElement& rhs);
bool operator<=(const TextElement& lhs, const TextElement& rhs);
bool operator>=(const TextElement& lhs, const TextElement& rhs);

// Read a single TextElement from is.
std::istream& operator>>(std::istream& is, TextElement& te);

// Write te to os
std::ostream& operator<<(std::ostream& os, const TextElement& te);

// Take a string str and
// 1. If str contains a single punctuation mark, do nothing.
// 2. Otherwise, remove all non alphabet characters from str.
// 3. Make all letters lower-case.
// @param str a string to be normalized.
// @return a reference to the (normalized) str.
std::string& normalize(std::string& str);

// Check if a charcter is punctuation ('.', '!', or '?')
// @param ch a character
// @return true if an only if ch is '.', '!', or '?'.
bool is_punctuation(char ch);

// Check if a charcter is a letter 'A' through 'Z' or 'a' through 'z'
// @param ch a character
// @return true if an only if ch is a letter
bool is_letter(char ch);

// Count words in a TextElement vector
// Count does not include punctuations
int word_count(std::vector<TextElement> t);

// Break a vector of TextElement into sentences
// Extract a sentence if the current TextElement is a punctuation and the next one is a word
// @return a vector of Sentence
std::vector<Sentence> break_into_sentences(std::vector<TextElement> t);

// Decide if the vector pair pair_vec has the same TextElement as text
// If it has one, return the index of the same Textelement in the pair vector
// If not, return -1
int is_same(TextElement text, std::vector<std::pair<TextElement, int>> pair_vec);

// Populate a pair vector, Put distinct TextElement into the pair vector
// If the TextElement is already in the pair vector, increment the seondtype of pair by 1
void populate_pair_vec(const std::vector<TextElement>& text_elts, std::vector<std::pair<TextElement, int>>& pair_vec);

// Count distinct words in a vector of pairs
// Count does not include punctuations
// @return the number of distinct words in the pair_vec
int distinct_words(std::vector<std::pair<TextElement, int>> pair_vec);

// Compare two pairs according to its second type int
// @ return true if the int of lhs is smaller than int of rhs
bool compare_pair(const std::pair<TextElement, int>& lhs, const std::pair<TextElement, int>& rhs);

// Print the 10 most common word in a pair vector
// Ignore punctuations
// @param sorted pair vector
void pring_10_common_word(std::vector<std::pair<TextElement, int>> pair_vec);

#endif