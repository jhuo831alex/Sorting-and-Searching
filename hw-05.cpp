////////////////////////////////////////////////////////////////////////////////
// @file hw-05.cpp
// @mainpage
// @author Jiahao Huo
// @date 2016-04-29
//
// Description: It contains the main function texting the class of TextElement
// and sorting and searching. 
//
// Known bugs: None yet!
////////////////////////////////////////////////////////////////////////////////

#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "text_element.h"

// This is the threshold length below which hybrid_sort
// just calls selection sort. If the threshold is set to 1
// hybrid_sort should be essentially the same as merge_sort
const size_t MERGE_THRESHOLD = 20;

// sort using both selection sort and merge sort, if the size of the vector is less than thresh
// use selection sort, otherwise use merge sort
// @param the TextElement vector than need to be sorted
// @param the fist index to sort
// @param the last+1 index to sort
// @param the threshold between using selection or merge sort
void hybrid_sort(std::vector<TextElement>& text, size_t min, size_t max, size_t thresh = MERGE_THRESHOLD);

// Merge two (sorted) sub-vectors from min to mid - 1 and mid to max - 1 into a single sorted sub-vector 
// from mid to max - 1
void merge(std::vector<TextElement>& text, size_t min, size_t mid, size_t max);

// sort the vector using merge sort
void merge_sort(std::vector<TextElement>& text, size_t min, size_t max);

// sort the vector using selection sort
void selection_sort(std::vector<TextElement>& text, size_t min, size_t max);

// return the index of min in vector text from min to max
size_t get_min_index(std::vector<TextElement>& text, size_t min, size_t max);

// swap the position of element in a vector
void swap(std::vector<TextElement>& text, size_t i, size_t j);

// print out the elements in a TextElement vector
void print_text_elements(std::vector<TextElement>& text);

// Perform recursive binary search to see if text contains te
size_t binary_search(const std::vector<TextElement>& text, size_t min, size_t max, const TextElement& te);

int main() {

	TextElement te;
	std::string input;
	std::vector<TextElement> user_input, text_elts, copy_1, copy_2;

	std::cout << "Enter some text: ";
	getline(std::cin, input);

	std::stringstream ss(input);
	while (ss >> te) {
		if (te.get_string() != "") {
			user_input.push_back(te);
		}
	}

	std::cout << "The text you entered contains " << user_input.size() << " text elements:" << std::endl;
	print_text_elements(user_input);
	std::cout << std::endl;

	copy_1 = user_input;
	copy_2 = user_input;

	std::cout << "Sorting using selection sort..." << std::endl;
	selection_sort(user_input, 0, user_input.size());
	std::cout << "The (selection) sorted version of your input is:" << std::endl;
	print_text_elements(user_input);
	std::cout << std::endl << std::endl;

	std::cout << "Sorting using merge sort..." << std::endl;
	merge_sort(copy_1, 0, copy_1.size());
	std::cout << "The (merge) sorted version of your input is:" << std::endl;
	print_text_elements(copy_1);
	std::cout << std::endl << std::endl;

	std::cout << "Sorting using hybrid sort..." << std::endl;
	hybrid_sort(copy_2, 0, copy_2.size());
	std::cout << "The (hybrid) sorted version of your input is:" << std::endl;
	print_text_elements(copy_2);
	std::cout << std::endl << std::endl;

	std::cout << "Enter a filename to read: ";
	std::cin >> input;

	std::clock_t start;
	std::clock_t stop;

	std::ifstream is;

	is.open(input.c_str());

	while (is >> te) {
		if (te.get_string() != "") {
			text_elts.push_back(te);
		}
	}

	std::cout << "The file you entered contains " << text_elts.size() << " text elements." << std::endl;

	copy_1 = text_elts;
	copy_2 = text_elts;

	std::cout << "Sorting first copy using selection sort..." << std::endl;

	start = std::clock();
	selection_sort(text_elts, 0, text_elts.size());
	stop = std::clock();

	std::cout << "That took " << 1000.00 * (stop - start) / CLOCKS_PER_SEC << " ms" << std::endl;

	std::cout << "Sorting second copy using merge sort..." << std::endl;

	start = std::clock();
	merge_sort(copy_1, 0, copy_1.size());
	stop = std::clock();

	std::cout << "That took " << 1000.00 * (stop - start) / CLOCKS_PER_SEC << " ms" << std::endl;


	std::cout << "Sorting third copy using hybrid sort..." << std::endl;

	start = std::clock();
	hybrid_sort(copy_2, 0, copy_2.size());
	stop = std::clock();

	std::cout << "That took " << 1000.00 * (stop - start) / CLOCKS_PER_SEC << " ms" << std::endl;

	std::cout << "Enter a filename to write the sorted elements: ";
	std::cin >> input;

	std::ofstream os;
	os.open(input.c_str());
	for (size_t i = 0; i < copy_2.size(); ++i) {
		os << copy_2[i] << std::endl;
	}

	os.close();


	std::cout << "Enter search query: ";
	std::cin >> te;

	size_t index = binary_search(text_elts, 0, text_elts.size(), te);

	if (index == -1) {
		std::cout << input << " does not contain \"" << te << "\"" << std::endl;
	}

	else {
		std::cout << input << " contains \"" << te << "\" as entry "
			<< index << " alphabetically" << std::endl;
	}

	return 0;
}

void hybrid_sort(std::vector<TextElement>& text, size_t min, size_t max, size_t thresh){
	
	if (max - min <= thresh){
		selection_sort(text, min, max);
	}
	else{
		size_t mid = (min + max) / 2;
		hybrid_sort(text, min, mid, thresh);
		hybrid_sort(text, mid, max, thresh);
		merge(text, min, mid, max);
	}
}

void merge(std::vector<TextElement>& text, size_t min, size_t mid, size_t max){
	size_t i = min;
	size_t j = mid;

	std::vector<TextElement> merged;

	// Copy the values to merged in non-decreasing order
	while (i < mid && j < max) {
		if (text[i] < text[j]) {
			merged.push_back(text[i]);
			++i;
		}

		else{
			merged.push_back(text[j]);
			++j;
		}
	}

	// Add any remaining entries between min and mid to merged
	while (i < mid) {
		merged.push_back(text[i]);
		++i;
	}

	// Add any remaining entries between mid and max to merged
	while (j < max) {
		merged.push_back(text[j]);
		++j;
	}

	// Copy the merged values back to data
	for (i = min; i < max; ++i) {
		text[i] = merged[i - min];
	}
}

void merge_sort(std::vector<TextElement>& text, size_t min, size_t max){

	// Vectors of length 1 are already sorted!
	if (max - min <= 1) {
		return;
	}

	// The middle index betwee min and max
	size_t mid = (max + min) / 2;

	// Sort between min and mid
	merge_sort(text, min, mid);

	// Sort between mid and max
	merge_sort(text, mid, max);

	// Merge sorted sub-vectors between min, mid, and max
	merge(text, min, mid, max);
}

void selection_sort(std::vector<TextElement>& text, size_t min, size_t max){
	size_t smallest;
	// Loop through and find the i-th smallest entry
	// put i-th smallest entry in i-th position
	for (size_t i = min; i < max; ++i) {
		// get index of smallest value starting at i to max
		smallest = get_min_index(text, i, max);

		// swap values at smallest and i-th positions
		swap(text, i, smallest);
	}
}

size_t get_min_index(std::vector<TextElement>& text, size_t min, size_t max){
	size_t smallest = min;
	TextElement small_val = text[min];

	for (int j = min + 1; j < max; ++j) {
		if (text[j] < small_val) {
			smallest = j;
			small_val = text[j];
		}
	}
	return smallest;
}

void swap(std::vector<TextElement>& text, size_t i, size_t j){
	TextElement old_val = text[i];
	text[i] = text[j];
	text[j] = old_val;
}

void print_text_elements(std::vector<TextElement>& text){
	size_t size = text.size();
	for (int i = 0; i < size - 1; ++i) {
		std::cout << text[i] << std::endl;
	}
	std::cout << text[size - 1] << std::endl;
}

size_t binary_search(const std::vector<TextElement>& text, size_t min, size_t max, const TextElement& te){

	// if the size of the interval (max - min) is 1, check if the (single) entry
	// is equal to te, and return the result
	if (max - min == 1) {
		if (te == text[min]) {
			return min;
		}
		return -1;
	}

	// Look at the middle entry of the interval [min, max)
	size_t mid = (min + max) / 2;

	// if te < text[mid], the look for te in the interval
	// [min, mid)
	if (te < text[mid]) {
		return binary_search(text, min, mid, te);
	}

	// otherwise, look for the te in the interval [mid, max)
	return binary_search(text, mid, max, te);
}