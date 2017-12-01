////////////////////////////////////////////////////////////////////////////////
// @file text_element.cpp
// @author Jiahao Huo	
// @date 2016-05-06
//
// Description: This is the implementation file for text_element.h
//
// Known bugs: None yet.
////////////////////////////////////////////////////////////////////////////////

#include"text_element.h"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>

TextElement::TextElement(){
	str_ = "";
	type_ = empty;
}

TextElement::TextElement(std::string str){
	str_ = normalize(str);
	type_ = word;
}

TextElement::TextElement(std::string str, TextElement::Type type){
	str_ = normalize(str);
	type_ = type;
}

std::string TextElement::get_string() const{
	return str_;
}

void TextElement::set_string(const std::string str){
	str_ = str;
}

TextElement::Type TextElement::get_type() const{
	return type_;
}

void TextElement::set_type(TextElement::Type type) {
	type_ = type;
}

std::string TextElement::capitalize(){
	// if it is a word, capitalize it
	if (type_ == word){
		for (size_t i = 0; i < str_.length(); ++i){
			str_[i] = toupper(str_[i]);
		}
		return str_;
	}
	// not a word, no need to capitalize
	else{
		return str_;
	}
}

bool operator==(const TextElement& lhs, const TextElement& rhs){
	if (lhs.get_type() == rhs.get_type() && lhs.get_string() == rhs.get_string()){
		return true;
	}
	return false;
}

bool operator<=(const TextElement& lhs, const TextElement& rhs){
	return (lhs < rhs || lhs == rhs);
}

bool operator>=(const TextElement& lhs, const TextElement& rhs){
	return (lhs > rhs || lhs == rhs);
}

bool operator<(const TextElement& lhs, const TextElement& rhs){
	// Order of types: empty < word < punctuation
	if (lhs.get_type() == rhs.get_type()){
		return lhs.get_string() < rhs.get_string();
	}
	else if (lhs.get_type() == TextElement::word && rhs.get_type() == TextElement::punctuation){
		return true;
	}
	else if (lhs.get_type() == TextElement::punctuation && rhs.get_type() == TextElement::word){
		return false;
	}
	else if ((lhs.get_type() == TextElement::punctuation || lhs.get_type() == TextElement::word)
		&& rhs.get_type() == TextElement::empty){
		return false;
	}
	else if ((rhs.get_type() == TextElement::punctuation || rhs.get_type() == TextElement::word)
		&& lhs.get_type() == TextElement::empty){
		return true;
	}
}

bool operator>(const TextElement& lhs, const TextElement& rhs){
	return !(lhs < rhs);
}

std::ostream& operator<<(std::ostream& os, const TextElement& te){
	os << te.get_string();
	return os;
}

std::istream& operator>>(std::istream& is, TextElement& te){
	char ch;
	std::string s = "";

	is >> ch;
	// if ch is a punctuation, read in only one char and set it to a TextElement
	if (is_punctuation(ch)){
		s.push_back(ch);
		te.set_string(s);
		te.set_type(TextElement::punctuation);
		return is;
	}
	// in other cases, keep reading in next char, until it hits a whitespace or punctuation or EOF
	else{
		is.unget();
		while (ch != ' '&& !is_punctuation(ch) && (ch != EOF)){
			is.get();
			s.push_back(ch);
			ch = is.peek();
		}
		normalize(s);
		te.set_string(s);
		te.set_type(TextElement::word);
		return is;
	}
}

std::string& normalize(std::string& str){
	std::string temp = "";
	for (size_t i = 0; i < str.length(); ++i){
		if (str[i] >= 'A' && str[i] <= 'z'){
			temp += tolower(str[i]);
		}
	}
	str = temp;
	return str;
}

bool is_punctuation(char ch){
	if (ch == '?' || ch == '!'||ch=='.'){
		return true;
	}
	return false;
}