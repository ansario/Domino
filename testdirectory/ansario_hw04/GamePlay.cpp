#include "GamePlay.h"

/******************************************************************************
*3456789 123456789 123456789 123456789 123456789 123456789 123456789 123456789
* Class 'GamePlay' for playing part of a dominos game.
*
* This class implements all of the functions needed to determine the longest 
* possible sequence of dominos that can be played from any starting number, 
* given a hand of 12 random tiles. It does so recursively. 
*
* Author: Duncan A. Buell modified by Omar A. Ansari 
* Date last modified: 6 October 2014
**/

/******************************************************************************
* Constructor
**/
GamePlay::GamePlay()
{
}

/******************************************************************************
* Destructor
**/
GamePlay::~GamePlay()
{
}

/******************************************************************************
* Accessors and Mutators
**/

/******************************************************************************
* General functions.
**/

/******************************************************************************
* Function 'dealDominos'.
*
* This function deals 12 dominos to your hand from a vector containg all 91
* dominos in a standard game.
*
* Parameters:
*   outStream - the output stream to which to write
*
**/
void GamePlay::dealDominos(ofstream& outStream, int seed)
{
    #ifdef EBUG
    Utils::logStream << "Generate 10 random numbers.\n";
    #endif
    
    int domsDealt = 0;
    int randomNumber = 0;
    string label = "";
    
    srand(seed);
    //Generate random numbers from 0(inc)-10(exc).
    for(int i = 0; i < 10; ++i) 
    {
        
       outStream << "random " << rand() << endl; 
        
    }
    //Prepare to write out dominos in hand.
    outStream << "MY HAND";	
    //Generate a random number between 0(inc)-91(exc).
    randomNumber = rand() % 91;	
    
    //Deal dominos until the number dealt is = 12.
    for  (domsDealt; domsDealt < 12; domsDealt++) { 
        //We do not want repeats. Check to see if the domino has been dealt.
        while (allDominos[randomNumber].wasDealt() == true){ 
            //If domino has been dealt, generate new random. 
            randomNumber = rand() % 91; 
        }
        //Add domino to hand of dominos.
        myDominos.push_back(allDominos[randomNumber]); 
        //Set "dealt" flag as true. This prevents duplicates.
        allDominos[randomNumber].setDealt(true); 
    }
    
    //toString the dominos in hand.
    outStream << toString() << endl; 

    #ifdef EBUG
    Utils::logStream << "leave dealDominos\n";
    #endif
    
}

/******************************************************************************
* Function 'extendSeq'.
* This function extends the seqfrom the start number.
*
* Parameters:
*   from - the number to be matched from unplayed dominos
*   seq - the current sequence of played dominos
*   level - the level of recursion on entry to this function
*   outStream - the output stream to which to write
**/
void GamePlay::extendSeq(int from, const vector<Domino>& seq, int level,
ofstream& outStream)
{
    
    #ifdef EBUG
    Utils::logStream << "enter extendSeq\n";
    #endif
    
    string label = "NEW MAX:";
    
    //From 0(inc) - dominos in hand(exc), extend sequence if mySeq becomes longer than maxSeq.
    for (int i = 0; i < static_cast<int>(myDominos.size()); i++) 
    {	//If domino has been played, do nothing.
        if (myDominos[i].hasBeenPlayed() == true) 
        {
            
        } else
            
        {
            //If left value is equal to the furthest most right value in sequence, set played value to true
            //and push the domino from your hand into the sequence of dominos currently in play.
            if (myDominos[i].getLeft() == mySeq[static_cast<int>(mySeq.size())-1].getRight())
            {
                myDominos[i].setPlayed(true);
                mySeq.push_back(myDominos[i]);
      			//If the new sequence in play is more than the maximum sequence played before, 
      			//Print the maxSequence, add the domino from hand to maxSequence, and call extendSeq.
                if  (static_cast<int>(mySeq.size()) >= static_cast<int>(maxSeq.size()))
                {
                    outStream << toStringSeq(label, maxSeq) << endl;
                    maxSeq.push_back(myDominos[i]);
                    extendSeq(i, mySeq, level+1, outStream); //Call extend sequence from current index.
                } 
                   //Remove the last added domino and set that domino as not played. 
                   //This allows to check for other combinations of domino tiles.
                    mySeq.pop_back();
                    myDominos[i].setPlayed(false);
             }

            //If right value is equal to the furthest most right value in sequence, flip domino, set played value to true
            //and push the domino from your hand into the sequence of dominos currently in play.
            else if ((myDominos[i].getRight() == mySeq[static_cast<int>(mySeq.size())-1].getRight()))
            {	//Flip so matching numbers can be touching.
                myDominos[i].flipEnds(); 
                myDominos[i].setPlayed(true);
                mySeq.push_back(myDominos[i]);
                //If the new sequence in play is more than the maximum sequence played before, 
      			//Print the maxSequence, add the domino from hand to maxSequence, and call extendSeq.
                if (static_cast<int>(mySeq.size()) >= static_cast<int>(maxSeq.size()))
                {
                    maxSeq.push_back(myDominos[i]);
                    outStream << toStringSeq(label, maxSeq) << endl;
                    extendSeq(i, mySeq, level+1, outStream);//Call extend sequence from current index.
                } 
                //Remove the last added domino and set that domino as not played. 
                //This allows to check for other combinations of domino tiles.
                mySeq.pop_back();
                myDominos[i].setPlayed(false);
           }
        }
    }      

	return;

    #ifdef EBUG
    Utils::logStream << "leave extendSeq\n";
    #endif
    
}

/******************************************************************************
* Function 'findLongestSeq'.
*
* This function actually does the outer loop for the recursion. It does the 
* initial check for matchin dominos and then calls extendSeq().
*
* Parameters:
*   outStream - the output stream to which to write
**/
void GamePlay::findLongestSeq(ofstream& outStream)
{
    
    #ifdef EBUG
    Utils::logStream << "enter findLongestSeq\n";
    #endif
    
    string label = "NEW MAX:";
  
    //For all starting values from 0(inc) to 13(exc), check if tile exists
    //in hand which matches (either side) the sequence in play.
    for (int i = 0; i < 13; i++)
    {
        outStream << "startNum " << i  << endl;

        //From 0(inc)- myDominos-1(exc), check if tile exists
    	//in hand which matches (either side) the sequence in play.
        for (int j = 0; j < static_cast<int>(myDominos.size())-1; j++)
        {
            //If the domino value on the right matches the current sequence, clear the sequence, 
            //flip the domino so matching ends touch, push the domino into the mySeq and maxSeq vectors,
    		//set playedValue to true, and call extendSeq.
            if ((myDominos[j].getRight() == i))
            {
                
                mySeq.clear();
                maxSeq.clear();
                
                myDominos[j].flipEnds();
               
                mySeq.push_back(myDominos[j]);
                myDominos[j].setPlayed(true);
                
                maxSeq.push_back(myDominos[j]);
                myDominos[j].setPlayed(true);
               
                extendSeq(i, mySeq, 0, outStream);
                
            }

            //If the domino value on the left matches the current sequence, clear the sequence, 
            //push the domino into the mySeq and maxSeq vectors, set playedValue to true, and call extendSeq.
            else if ((myDominos[j].getLeft() == i))
            {
                mySeq.clear();
                maxSeq.clear();
                
                mySeq.push_back(myDominos[j]);
                myDominos[j].setPlayed(true);
                
                maxSeq.push_back(myDominos[j]);
                myDominos[j].setPlayed(true);
                
                extendSeq(i, mySeq, 0, outStream);
            }
        }
        
        //We must set all the played values as false since we are going to check the next starting value.
        for (int i = 0; i < 13; i++)
        {
            myDominos[i].setPlayed(false);
        }
        
        //Print max sequence.
            label = "MAX SEQ:";
            outStream << toStringSeq(label, maxSeq) << endl;
            maxSeq.clear();
   
    }
    
    #ifdef EBUG
    Utils::logStream << "leave findLongestSeq\n";
    #endif
    
}

/******************************************************************************
* Function 'initialize'.
*
* This function sets up the allDominos vector and creates 91 dominos with all 
* the possible combinations from a standard "Mexican Train" domino game.
*
**/
void GamePlay::initialize()
{
    
    #ifdef EBUG
    Utils::logStream << "enter initialize\n";
    #endif
    
    //Create 91 dominos in a standard "Mexican Train" domino game. !NOTE! The j subscript is dependent on i.
    //This is due to the fact that the max side of one domino is the maximum possible value that the other side can be.
    //For example, a domino with 1 on one side can only have 1 or 0 on the other. 
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < i+1; j++)
        {
            Domino dom = Domino (i, j);
            allDominos.push_back(dom);
        }
    }
    
    #ifdef EBUG
    Utils::logStream << "leave initialize\n";
    #endif
    
}

/******************************************************************************
* Function 'toString'.
* This function dumps the 'vector' of data to a 'string' and returns it.
*
* Returns:
*   the 'toString' of the data in the class
**/
string GamePlay::toString() const
{
    #ifdef EBUG
    Utils::logStream << "enter toString\n";
    #endif
    
    string s = "";
    
    //Loop through the myDominos vector and call the toString method in the Domino class.
    for (int  i = 0; i < static_cast<int>(myDominos.size()); i++) 
    {
        s+= myDominos[i].toString();
        
    }
    
    #ifdef EBUG
    Utils::logStream << "leave toString\n";
    #endif
    return s;
}

/******************************************************************************
* Function 'toStringSeq'.
* This function dumps the 'mySeq' data to a 'string' and returns it.
*
* Returns:
*   the 'toString' of the 'vector' of dominoes
**/
string GamePlay::toStringSeq(string label, const vector<Domino>& theSeq) const
{
    
    #ifdef EBUG
    Utils::logStream << "enter toStringSeq\n";
    #endif
    string s = "";
    
    s+= label;
    //s+= static_cast<int>(theSeq.size()) + "     ";
    
    for (int  i = 0; i < static_cast<int>(theSeq.size()); i++)
    {
        s+= theSeq[i].toString();
        
    }
   
    #ifdef EBUG
    Utils::logStream << "leave toStringSeq\n";
    #endif
    return s;
}
