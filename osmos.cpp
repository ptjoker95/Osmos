#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <algorithm>
#include <math.h>
using namespace std;

class Osmos
{
	private:
		unsigned long long int A;
		int N, Operations, MaxOperations;
		vector<unsigned long long int> motes;
		bool CanAbsorb( unsigned long long int osmos, unsigned long long int mote )
		{
			return osmos > mote;
		}
		void DeleteLastMote()
		{
			motes.pop_back();
		}
		
		unsigned long long int BiggerMote( unsigned long long int M, int i )
		{
			if( i == 0 )
				return M;
			else
				return pow(2,i)*( M - 1 ) + 1;
		}
		
		void OsmosGame()
		{
			unsigned long long int Added;
			
			Added = this->A;
			
			while( !motes.empty() )
			{
				if( this->CanAbsorb( Added, motes[0] ) )
				{
					//cout << "mote: " << Added << " ,next mote: " << motes[0] << " ,Operation: " << this->Operations << endl;
					Added += motes[0];
					motes.erase( motes.begin() );
				}
				else
				{
					if( motes.size() == 1 )
					{
						//cout << "last mote: " << motes[0] << " ,Operation: " << this->Operations << endl;
						this->DeleteLastMote();
						this->Operations++;
						return;
					}
					else
					{
						if( Added == 1 )
						{
							this->Operations = motes.size();
							return;
						}
						else
						{
							unsigned int i;
							i=1;
							while( BiggerMote( Added, i ) < this->motes[0] )
							{
								//cout << "Bigger Mote: " << BiggerMote( Added, i ) << endl;
								i++;
							}
					
							if( i >= this->motes.size() )
							{
								this->Operations += motes.size();
								return;
							}
							else
							{
								Added = BiggerMote( Added, i);
								//cout << "Added: " << Added << endl;
								this->Operations += i;
							}
							
						}
					}
				}
			}
		}
	public:
		void InputData( unsigned long long int a, int n, vector<unsigned long long int> m )
		{
			this->Operations = 0;
			this->MaxOperations = 0;
			this->motes.clear();
			
			this->A = a;
			this-> N = n;
			this->motes = m;
			
			this->MaxOperations = motes.size();
			
			sort( motes.begin(), motes.end() );
			
			/*
			for( unsigned int i=0; i<motes.size(); i++ )
			{
				cout << motes[i] << " ,";
			}
			cout << endl;
			*/
			this->OsmosGame();
		}
		int OutputOperations()
		{
			//return this->Operations;
			
			if( this->MaxOperations > this->Operations )
				return this->Operations;
			else
				return this->MaxOperations;
		}
};

int main( int argc, char** argv )
{
	int T;
	unsigned long long int A;
	int N;
	vector<unsigned long long int> motes;
	Osmos osmos;
	
	fstream myfile;
	
	myfile.open( argv[1] );
	
	myfile >> T;

	if( myfile.is_open() )
	{
		for(int i=0; i<T; i++ )
		{
			myfile >> A >> N;
			for( int j=0; j<N; j++ )
			{
				unsigned long long int temp;
				
				myfile >> temp;
				
				motes.push_back( temp );
			}
			
			osmos.InputData( A, N, motes );
			
			cout << "Case #" << i+1 << ": " << osmos.OutputOperations() << endl;
			
			motes.clear();
		}
	}
	
	myfile.close();
}
