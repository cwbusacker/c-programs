/***********************************************************************
 * Module:
 *    Week 08, Huffman
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the huffman() function
 ************************************************************************/

#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <fstream>
#include <string>
#include <iostream>
#include "pair.h"
#include <list>
#include "bnode.h"
#include "huffmanTree.h"
using namespace std;

string search(pbNode root, char findMe);
void huffman(string filename);

#endif // HUFFMAN_h
