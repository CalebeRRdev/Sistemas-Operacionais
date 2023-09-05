/**
 * @file 	main.cpp
 * @brief 	Frog race in C++.
 * @details	In this game, three frogs will jump to the finish line, the first to come will be the winner.
 * @author 	Robert George.
 * @since 	20/08/2017.
 * @date	22/08/2017.
 */
#ifndef _SAPO_H_
#define _SAPO_H_
#include <random>

class Sapo 
{
	private:
		
		int Dist;
		int pular;

		std::random_device rnd;
		std::default_random_engine dre;
		std::uniform_int_distribution<> uid;

	public:
		Sapo();
		Sapo( int, int );
		~Sapo();

		static int total;
		static int getDisTotal();

		void setDist_( int );
		int getDist_();
		
		int getPular();
		
};

void abertura();

int recebe_aposta( );

int circuito();

int distancia( int S1, int S2, int S3);

void imprime( int p, int D1_, int D2_, int D3_);

void Resultado( int C1_, int C2_, int C3_, int aposta, int cont);

#endif
