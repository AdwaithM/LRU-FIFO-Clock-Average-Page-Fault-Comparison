/********************************************************************************
 * File: Pgm3Base.cpp
 * Author: Adwaith Moothezhath Rajesh
 * Modification History: Adwaith Moothezhath - 4/25/2021
 * Procedures:
 * LRU  -Function which uses the Least Recently Used Page Replacement algorithm  
 *       to return number of Page pageFaults
 * FIFO  -Function which uses the First in First Out Page Replacement algorithm
 *        to return number of Page pageFaults
 * Clock  -Function which has a circular list of pageTraces in memory and the pointer
 *         which points to a page with R bit = 1 if there is no page fault 
 *         and if RBit is 0 replaces that and return number of Page pageFaults
 * main  -creates poisson distribution with lambda = 10 and runs the three
 *          functions 1000 times for each working set size 2-20 and retuns average
 *          pagefault for each working set size
*******************************************************************************/
#include <iostream>                                     //Header file iostream to read/write to the standard input/output streams
#include <random>                                       //Header file random for poisson_distribution                              
#include<vector>                                        //Header file for vector
#include <iomanip>                                      //Header file for setwidth 

using namespace std;                                    //namespace std is for cout 
   
/********************************************************************************
 * int LRU(int wss, int pageTraces[])
 * Author: Adwaith Moothezhath Rajesh
 * Date: 4/25/2021
 * Modification History: Adwaith Moothezhath - 4/25/2021
 * Description: This function is used to calculate the number of
* page pageFaults using the Least Recently Used algorithm.
* It uses a vector and counts the number to add to end and delete lRU element.
*******************************************************************************/
int LRU(int wss, int pageTraces[])
{
  vector<int> lruVect;                                   //declare vector array
  int pageFaults = 0;                                    //initalize page faults to 0

  for(int i=0; i<1000; i++)                              //go through all pageTraces
  {
    int currInWss = 0;                                   //initalize currently in working set size to 0
    int currPostion = 0;                                 //initalize current Postion to 0

    for(int j=0;j<lruVect.size();j++)                    //run from 0 to length of vector because it grows when elements are added
    {
      if(lruVect.at(j) == pageTraces[i])                 //if the page is already in the working set size 
      {
        currInWss = 1;                                   //set currently in working set size to 1
        currPostion = j;                                 //set current postion to j
      }
    }

    if(currInWss == 0)                                  //if the page is not in the working set size
    {
      if(lruVect.size() < wss)                          //if the size of teh vector is less than the working set size
      {
        lruVect.push_back(pageTraces[i]);               //insert the page into the vector

        pageFaults++;                                   //increment the page fault by 1
      }
      else
      {
        lruVect.erase(lruVect.begin());                 //delete the least recently used page which automatcily shifts and resizes

        pageFaults++;                                   //increment the page fault by 1

        lruVect.push_back(pageTraces[i]);               //insert the page into the vector at the end 
      }
    }
    else                                               //if the page is in the working set size
    {
      lruVect.erase(lruVect.begin() + currPostion);    //delete the least recently used page (this is the same as swapping bc the page is in the working set size)

      lruVect.push_back(pageTraces[i]);                //insert the page into the vector at the end (this is the same as swapping bc the page is in the working set size)
    } 
  }
  return pageFaults;                                   //return the total page faults counted   
}

/********************************************************************************
 * int FIFO(int wss, int pageTraces[])
 * Author: Adwaith Moothezhath Rajesh
 * Date: 4/25/2021
 * Modification History: Adwaith Moothezhath - 4/25/2021
 * Description: This function is used to calculate the number of
 * page pageFaults using the First-in-First-out algorithm.
 * It uses a vector to add elements to end and delete the first element which came in the memory                 
*******************************************************************************/
int FIFO(int wss, int pageTraces[])
{
  vector<int> fifoArray;                          //declare vector array
  int pageFaults = 0;                             //initalize page faults to 0

  for(int i=0; i<1000; i++)                       //go through all pageTraces
  {
    int currInWss = 0;                            //initalize currently in working set size to 0
    int currPostion = 0;                          //initalize current Postion to 0

    for(int j=0;j<fifoArray.size();j++)            //run from 0 to length of vector because it grows when elements are added
    {
      if(fifoArray.at(j) == pageTraces[i])        //if the page is already in the working set size
      {
        currInWss = 1;                            //set currently in working set size to 1
        currPostion = j;                          //set current postion to j
      }
    }
    if(currInWss == 0)                            //if the page is not in the working set size
    {
      if(fifoArray.size() < wss)                  //if the size of teh vector is less than the working set size
      {
        fifoArray.push_back(pageTraces[i]);       //insert the page into the vector

        pageFaults++;                             //increment the page fault by 1
      }
      else
      {
        fifoArray.erase(fifoArray.begin());       //delete the least recently used page which automatcily shifts and resizes

        pageFaults++;                             //increment the page fault by 1

        fifoArray.push_back(pageTraces[i]);       //insert the page into the vector at the end
      }
    } 
  }
  return pageFaults;                              //return the total page faults counted

}

/********************************************************************************
 * int clock(int wss, int pageTraces[])
 * Author: Adwaith Moothezhath Rajesh
 * Date: 4/25/2021
 * Modification History: Adwaith Moothezhath - 4/25/2021
 * Description: This function is used to calculate the number of
 * page pageFaults using the Clock algorithm. It uses two arrays one is for page
 * another for Rbit which is used to see if the elemnt has a second chance to say in memory  
*******************************************************************************/
int Clock(int wss, int pageTraces[])
{
  int clockArray[1000];                             //declare array with size 1000
  int rBit[1000];                                   //declaring Rbit array with size 1000 
  int clockArraySize = 0;                           //initalize array size to 0
  int currentPointer = 0;                           //initalize current Postion to 0
  int pageFaults = 0;                               //initalize page faults to 0

  for(int i=0;i<1000;i++)                           //run for 1000 times
  {
    clockArray[i] = 0;                              //initalize array elements to 0
    rBit[i] = 0;                                    //initalize rBit elements to 0
  }

  for(int i=0;i<1000;i++)                           //go through all pageTraces                         
  {
    
    int currInWss = 0;                              //set currently in working set size to 0
    int currPostion = -1;                           //set current postion to -1                
    for(int j=0;j<clockArraySize;j++)               //run from 0 to length of array
    {
      if(clockArray[j] == pageTraces[i])            //if the page is already in the working set size
      {
        currInWss = 1;                              //set currently in working set size to 1
        currPostion = j;                            //set current postion to j
        rBit[j] = 1;                                //set current RBit to 1
      }
    }

    if(currInWss == 0)                             //if the page is not in the working set size
    {
      if(clockArraySize < wss)                     //if the size of teh vector is less than the working set size
      {
        clockArray[clockArraySize]=pageTraces[i]; //insert the page into the array   
        rBit[clockArraySize] = 1;                 //set Rbit to 1
        clockArraySize++;                         //increment the array size by 1
      }
      else
      {
        int inserted = 0;                        //initalize inesrted to 0
        for(int a=0;a<wss;a++)                   //run through working set size
        {
          if(rBit[a] == 0)                       //if the rBit is 0
          {
            clockArray[a] = pageTraces[i];      //set page to array
            rBit[a] = 1;                        //set rbit of the element to 1
            inserted = 1;                       //set inserted to 1
            break;                              //break from loop
          }
        }
        if(inserted == 0)
        {
          for(int a = 0;a<wss;a++)              //run through working set size
          {
            rBit[a] = 0;                        //set Rbit to 0
          }
          clockArray[0] = pageTraces[i];        //set page to array
          rBit[0] = 1;                          //set Rbit to 1
        }
      }
      pageFaults++;                             //increment the page fault by 1
    }
  } 
  return pageFaults;                            //return the total page faults counted
}

/********************************************************************************
 * int main( int argc, char *argv[] )
 * Author: Adwaith Moothezhath Rajesh
 * Date: 4/25/2021
 * Modification History: Adwaith Moothezhath - 4/25/2021
 * Description: Implements a Poisson distrubtion with lamda = 10 and runs an experiment 1000
 * times and for each experiment runs the wroking set size from 2-20 inclusively for eacch of the
 * three alogrithms LRU,FiFO, Clock and reutns the average page fualts for all of them
 * Parameters: 
 *	argc 	I/P 		int 		The number of arguments on the command line
 * 	argv 	I/P 		char *[] 	The arguments on the command line
 * 	main	O/P		int		Status code (not currently used)  
*******************************************************************************/
int main( int argc, char *argv[] ) 
{
 
default_random_engine generator;                //random number class to generates pseudo-random numbers                            
poisson_distribution<int> distribution(10);     //generates poisson random number with lamda = 10

int pageTraces[1000] = {};                      //initalize page traces array with size 1000                
int lrufaultCount[20];                        //declare lru counter array with size 20
int fifofaultCount[20];                       //declare fifo counter array with size 20
int clockfaultCount[20];                      //declare clock counter array with size 20

for(int i = 0; i< 20; i++)                     //run through lru counter array
{
	lrufaultCount[i] = 0;                      //set all elements to 0
}
for(int i = 0; i< 20; i++)                     //run through fifo counter array
{
	fifofaultCount[i] = 0;                     //set all elements to 0
}
for(int i = 0; i< 20; i++)                     //run through clock counter array
{
	clockfaultCount[i] = 0;                   //set all elements to 0
}

int experiment = 1000;                       //initalize experiment to 1000 
while(experiment --> 0 )                     //run through 1000 experiments
{
  for(int i = 0; i < 1000; i++)              //run 1000 times
  {
    pageTraces[i] = distribution(generator); //get 1000 page Traces
  }

  for(int wss = 2; wss <= 20; wss++)          //run through 20 working set sizes
  {

    lrufaultCount[wss] += LRU(wss, pageTraces);     //count total page faults for each working set sizes
    fifofaultCount[wss] += FIFO(wss, pageTraces);   //count total page faults for each working set sizes
    clockfaultCount[wss] += Clock(wss, pageTraces); //count total page faults for each working set sizes

  }  
}


cout << setw(15) << "Working set Size" << setw(15) << "LRU Average" << setw(15) << "FIFO Average" << setw(15) << "Clock Average" <<  endl << endl; 

  for(int wss = 2; wss <= 20; wss++)
  {
    cout << setw(5) << wss << setw(15) << lrufaultCount[wss] / 1000;
    cout << setw(15) << fifofaultCount[wss] / 1000 << setw(15) << clockfaultCount[wss] / 1000 << endl;
  }
}




