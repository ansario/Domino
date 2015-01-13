/****************************************************************
 * Header file for a single domino.
 *
 * Author/copyright:  Duncan Buell used by Omar Ansari.
 * Date: 10 September 2014
 *
**/

#ifndef DOMINO_H
#define DOMINO_H

#include <iostream>
#include <vector>
using namespace std;

#include "../../Utilities/Scanner.h"
#include "../../Utilities/ScanLine.h"

class Domino
{
public:
  Domino();
  Domino(int left, int right);
  virtual ~Domino();

  void flipEnds();
  int getLeft() const;
  int getRight() const;
  bool hasBeenPlayed() const;
  void setDealt(bool value);
  void setPlayed(bool value);
  bool wasDealt() const;
  string toString() const;

private:
  bool played;
  bool dealt;
  int left;
  int right;

};

#endif
