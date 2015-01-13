#include "Domino.h"

/******************************************************************************
 *3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
 * Class 'Domino' for a single domino.
 *
 * This class contains all the attributes of a single domino object which is used
 * in the GamePlay class.
 *
 * Author: Duncan A. Buell modified by Omar A. Ansari
 * Date last modified: 10 September 2014
**/

/******************************************************************************
 * Constructor
**/
Domino::Domino()
{
  left = 0;
  right = 0;
  setPlayed(false);
  setDealt(false);
}

/******************************************************************************
 * Constructor with data supplied
**/
Domino::Domino(int left, int right)
{
  this->left = left;
  this->right = right;
  setPlayed(false);
  setDealt(false);
}

/******************************************************************************
 * Destructor
**/
Domino::~Domino()
{
}

/******************************************************************************
 * Accessors and Mutators
**/
 /******************************************************************************
 * Function 'flipEnds'.
 * This function flips the left and right values of the domino.
**/
void Domino::flipEnds()
{
  int temp = 0;

  temp = left;
  left = right;
  right = temp;
}

/******************************************************************************
 * Function 'getLeft'.
 * This returns the left value of the domino.
**/
int Domino::getLeft()const
{
	return left;
}

/******************************************************************************
 * Function 'getRight'.
 * This returns the right value of the domino.
**/
int Domino::getRight() const
{
	return right;
}

/******************************************************************************
 * Function 'hasBeenPlayed'.
 * This returns the played boolean of the domino.
**/
bool Domino::hasBeenPlayed() const
{
	return played;
}

/******************************************************************************
 * Function 'setDealt'.
 * This returns the the dealt boolean of the domino.
 *
 * parameter:
 *  value - boolean which dealt will be set to.
**/
void Domino::setDealt(bool value)
{
	dealt = value;
}

/******************************************************************************
 * Function 'hasBeenPlayed'.
 * This returns the the played boolean of the domino.
 * parameter:
 *  value - boolean which played will be set to.
**/
void Domino::setPlayed(bool value)
{
	played = value;
}

/******************************************************************************
 * Function 'wasDealt'.
 * This returns the the dealt boolean of the domino.
**/
bool Domino::wasDealt() const
{
	return dealt;
}

/******************************************************************************
 * General functions.
**/

/******************************************************************************
 * Function 'toString'.
 * This returns the 'played' as well as the left and right numbers.
**/
string Domino::toString() const
{
  string s = "[ ";
  
  if (played)
  {
    s += " T ";
  }
  else
  {
    s += " F ";
  }

  s += Utils::Format(this->left, 3);
  s += Utils::Format(this->right, 3);

  s += " ]";

  return s;
}
