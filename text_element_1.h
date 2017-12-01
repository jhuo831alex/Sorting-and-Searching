////////////////////////////////////////////////////////////////////////////////
// @file text_element.h
// @author Jiahao Huo
// @date 2016-05-09
//
// Description: This is the header file of TextElement class and related comparison 
// operators and input/output opeators. 
// The function to normalize a word and determine if a char is punctuation is also
// included.
//
// Known bugs: None yet!
////////////////////////////////////////////////////////////////////////////////

#ifndef TEXT_ELEMENT_H
#define TEXT_ELEMENT_H

#include <string>
#include <iostream>

////////////////////////////////////////////////////////////////////////////////
// @class TextElement
// @brief Construct text elements such as words and punctuations.
//
// The TextElement can store words as a TextElement and normalize them 
// (convert them to lower case). In addition, the class can store single 
// punctuation as a TextElement(!, ? and .).
// This class can get and set the content and type of a Textelement. Also, it can 
// capitalize a TextElement. 
////////////////////////////////////////////////////////////////////////////////

class TextElement{
public:
	// Three types of TextElement
	enum Type { word, punctuation, empty };

	// Default constructor - default stirng is empty and type is empty
	TextElement();

	// Construct a TextElement of content str;
	TextElement(std::string str);

	// Construct a TextElement of content str and type "type"
	TextElement(std::string str, TextElement::Type type);

	// return the content (str_) of a TextElement
	std::string get_string() const;

	// set the content of a TextElement to str
	void set_string(const std::string str);

	// return the type of a TextElement
	TextElement::Type get_type() const;

	// set the type of a TextElement to type
	void set_type(TextElement::Type type);

	// capitalize a TextElement
	// @return the capitalized string
	std::string capitalize();

private:
	// the content of a TextElement
	std::string str_;

	// the type of a TextElement
	TextElement::Type type_;
};

// Check if two TextElement are equal.
// @param the left Integer
// @param the right Integer
// @return a bool which is true if and only if lhs and rhs store the same value
bool operator==(const TextElement& lhs, const TextElement& rhs);

// Check if left hand side TextElement is less or equal to the right one
// @param the left Integer
// @param the right Integer
// @return a bool which is true if and only if lhs is less or equal to rhs 
bool operator<=(const TextElement& lhs, const TextElement& rhs);

// Check if left hand side TextElement is larger or equal to the right one
// @param the left Integer
// @param the right Integer
// @return a bool which is true if and only if lhs is larger or equal to rhs 
bool operator>=(const TextElement& lhs, const TextElement& rhs);

// Check if left hand side TextElement is less than the right one
// @param the left Integer
// @param the right Integer
// @return a bool which is true if and only if lhs is less than rhs 
bool operator<(const TextElement& lhs, const TextElement& rhs);

// Check if left hand side TextElement is bigger than the right one
// @param the left Integer
// @param the right Integer
// @return a bool which is true if and only if lhs is bigger than rhs 
bool operator>(const TextElement& lhs, const TextElement& rhs);

// the input operator for TextElement
// read TextElement te to stream
std::istream& operator>>(std::istream& is, TextElement& te);

// the output operator for TextElement
// write TextElement te to stream
std::ostream& operator<<(std::ostream& os, const TextElement& te);

// normalize a string, convert a string to lower case
// if it contains punctuation other "?!." , eleminate them
// @param a string needs to be normalize
// @return a normalized string with all lower case and no punctuation
std::string& normalize(std::string& str);

// decide if the char is ? or ! or .
// @param a punctuation
// @return if this punctuation is ? or ! or .
bool is_punctuation(char ch);

#endif