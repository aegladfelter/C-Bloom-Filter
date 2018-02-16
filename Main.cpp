/***************************************************************
<Austin Gladfelter>
<Main.cpp>
<Program4>
<This is the main file of a program for the implementation and testing
 of a bloom filter.
 This calls on BloomFilter.hpp to implement functions written by Michael Schmatz 
 for the Bloom Filter data structure and test the size and false positive rates
 as the program runs iterations of growing element sets.  
 These sets range from 16 and double every test until it reaches the maximum number 
 of elements which is 8,388,688.>
***************************************************************/

#include "BloomFilter.hpp"
#include <iostream>
#include <cmath>

using namespace std;


int main()
{
	
	double x = 2.0;
	
		
	for (x ; x <= 8.0; x = x + 1.0)
	{
		 
		//bloom filter instantiation for new data structure
		//double p
		double p = (1 / pow(2.0, x));
		for (int numElem = 16; numElem <= 8388608; numElem = numElem * 2)
		{
		//initialize number of false positivs to 0 and 
		//calculate bit usage and number of hashes
			int FP = 0;
			double bits = (-1 * ((numElem * log(p)) / pow(log(2), 2)));
			int numHashes = (bits / (double)numElem) * log(2.0);

			//constructor for Bloom Filter  
			//positive rate calculation
			BloomFilter Bloom(bits, numHashes);

			//adding elements to the bloom filter
			for (int a = 1; a <= numElem; a++)
			{
				(Bloom.add((const uint8_t*)(&a), sizeof(int)));
			}
			//testing the incremented set of elements which is doubled
			for (int testVal = (3 * numElem) + 1; testVal > numElem; testVal--)
			{
				if (Bloom.possiblyContains((const uint8_t*)(&testVal), sizeof(int)))
				{
					FP++;
				}
			}
			//false postive rate calculation
			double FPrate = FP / (2.0 * numElem);

			////output results
			cout << "Bloom Filter data : " << "\n";
			cout << "Rate of theoretical False Positive: " << p << "\n";
			cout << "Number of elements : " << numElem << "\n";
			cout << "Size in bits: " << (int)bits << "\n";
			cout << "Hash Functions : " << numHashes << "\n";
			cout << "Rate of false positives : " << FPrate << "\n";
			cout << "\n";
			

		}
	}
	
	return 0;
}



