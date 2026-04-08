/*
 * Names: Shenghua Jin, Luke Choi
 * SFU IDs: 301659564, 301658198
 * Emails: sja204@sfu.ca, esc9@sfu.ca
 *
 * Statement of Originality:
 * All the code and comments below are my (our) own original work. For any non-
 * original work, I (we) have provided citations above and in the comments with
 * enough detail so that someone can see the exact source and extent of the
 * borrowed work.
 *
 * In addition, I (we) have not shared this work with anyone else, and I (we) have
 * not seen solutions from other students, tutors, websites, books, etc.
 */

#pragma once
#include "a5.h"
#include <string>

// Generates dataset.csv for training the Neural Network
void generateDataset(int numGames, int depth, const std::string& filename);
