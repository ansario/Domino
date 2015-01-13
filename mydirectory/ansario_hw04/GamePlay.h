/****************************************************************
 * Header file for the class to find sequences in a domino game.
 *
 * Author/copyright:  Duncan Buell edited by Omar A. Ansari
 * Date: 13 July 2014
 *
**/

#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
using namespace std;

#include "Domino.h"

#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

class GamePlay
{
public:
  GamePlay();
  virtual ~GamePlay();

  void dealDominos(ofstream& outStream, int seed);
  void initialize();
  void findLongestSeq(ofstream& outStream);
  string toString() const;
  string toStringSeq(string label, const vector<Domino>& theSeq) const; //edited label to be passed by reference.

private:
  int maxLength;

  vector<Domino> allDominos;
  vector<Domino> myDominos;
  vector<Domino> maxSeq;
  vector<Domino> mySeq;

  void extendSeq(int from, const vector<Domino>& seq,
                 int level, ofstream& outStream);
};

#endif
