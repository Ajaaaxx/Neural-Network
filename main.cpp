#include <iostream>
#include "Couche/couche.hpp"
#include "Morpion/morpion.hpp"
#include <stdlib.h> 
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

/* CODE IA MORPION MIN MAX */

struct Move 
{ 
    int row, col; 
}; 
  
char player = 'x', opponent = 'o'; 
  
// This function returns true if there are moves 
// remaining on the board. It returns false if 
// there are no moves left to play. 
bool isMovesLeft(char board[3][3]) 
{ 
    for (int i = 0; i<3; i++) 
        for (int j = 0; j<3; j++) 
            if (board[i][j]=='_') 
                return true; 
    return false; 
} 
  
// This is the evaluation function as discussed 
// in the previous article ( http://goo.gl/sJgv68 ) 
int evaluate(char b[3][3]) 
{ 
    // Checking for Rows for X or O victory. 
    for (int row = 0; row<3; row++) 
    { 
        if (b[row][0]==b[row][1] && 
            b[row][1]==b[row][2]) 
        { 
            if (b[row][0]==player) 
                return +10; 
            else if (b[row][0]==opponent) 
                return -10; 
        } 
    } 
  
    // Checking for Columns for X or O victory. 
    for (int col = 0; col<3; col++) 
    { 
        if (b[0][col]==b[1][col] && 
            b[1][col]==b[2][col]) 
        { 
            if (b[0][col]==player) 
                return +10; 
  
            else if (b[0][col]==opponent) 
                return -10; 
        } 
    } 
  
    // Checking for Diagonals for X or O victory. 
    if (b[0][0]==b[1][1] && b[1][1]==b[2][2]) 
    { 
        if (b[0][0]==player) 
            return +10; 
        else if (b[0][0]==opponent) 
            return -10; 
    } 
  
    if (b[0][2]==b[1][1] && b[1][1]==b[2][0]) 
    { 
        if (b[0][2]==player) 
            return +10; 
        else if (b[0][2]==opponent) 
            return -10; 
    } 
  
    // Else if none of them have won then return 0 
    return 0; 
} 
  
// This is the minimax function. It considers all 
// the possible ways the game can go and returns 
// the value of the board 
int minimax(char board[3][3], int depth, bool isMax) 
{ 
    int score = evaluate(board); 
  
    // If Maximizer has won the game return his/her 
    // evaluated score 
    if (score == 10) 
        return score; 
  
    // If Minimizer has won the game return his/her 
    // evaluated score 
    if (score == -10) 
        return score; 
  
    // If there are no more moves and no winner then 
    // it is a tie 
    if (isMovesLeft(board)==false) 
        return 0; 
  
    // If this maximizer's move 
    if (isMax) 
    { 
        int best = -1000; 
  
        // Traverse all cells 
        for (int i = 0; i<3; i++) 
        { 
            for (int j = 0; j<3; j++) 
            { 
                // Check if cell is empty 
                if (board[i][j]=='_') 
                { 
                    // Make the move 
                    board[i][j] = player; 
  
                    // Call minimax recursively and choose 
                    // the maximum value 
                    best = max( best, 
                        minimax(board, depth+1, !isMax) ); 
  
                    // Undo the move 
                    board[i][j] = '_'; 
                } 
            } 
        } 
        return best; 
    } 
  
    // If this minimizer's move 
    else
    { 
        int best = 1000; 
  
        // Traverse all cells 
        for (int i = 0; i<3; i++) 
        { 
            for (int j = 0; j<3; j++) 
            { 
                // Check if cell is empty 
                if (board[i][j]=='_') 
                { 
                    // Make the move 
                    board[i][j] = opponent; 
  
                    // Call minimax recursively and choose 
                    // the minimum value 
                    best = min(best, 
                           minimax(board, depth+1, !isMax)); 
  
                    // Undo the move 
                    board[i][j] = '_'; 
                } 
            } 
        } 
        return best; 
    } 
} 
  
// This will return the best possible move for the player 
Move findBestMove(char board[3][3]) 
{ 
    int bestVal = -1000; 
    Move bestMove; 
    bestMove.row = -1; 
    bestMove.col = -1; 
  
    // Traverse all cells, evaluate minimax function for 
    // all empty cells. And return the cell with optimal 
    // value. 
    for (int i = 0; i<3; i++) 
    { 
        for (int j = 0; j<3; j++) 
        { 
            // Check if cell is empty 
            if (board[i][j]=='_') 
            { 
                // Make the move 
                board[i][j] = player; 
  
                // compute evaluation function for this 
                // move. 
                int moveVal = minimax(board, 0, false); 
  
                // Undo the move 
                board[i][j] = '_'; 
  
                // If the value of the current move is 
                // more than the best value, then update 
                // best/ 
                if (moveVal > bestVal) 
                { 
                    bestMove.row = i; 
                    bestMove.col = j; 
                    bestVal = moveVal; 
                } 
            } 
        } 
    } 
  
    //printf("The value of the best Move is : %d\n\n", 
    //bestVal); 
  
    return bestMove; 
}

/* FIN DU CODE IA MORPION MIN MAX */

int main() {
  /* Création du réseau de neurones pour le morpion */
  srand (time(NULL));
 
  Couche * c1 = new Couche(9);
  Couche * c2 = new Couche(50);
  Couche * c3 = new Couche(50);
  Couche * c4 = new Couche(9);
  
  c2->relier(c1);
  c3->relier(c2);
  c4->relier(c3);

  
  for (int i = 0; i < 100000; i++) {
    /* On réinitialise les couches */
    c1->resetErreur();
    c2->resetErreur();
    c3->resetErreur();
    c4->resetErreur();
    
    /* On créer une partie du morpion à un état aléatoire */
    Morpion * m = new Morpion(1);

    char ** board = new char*[3];
    for (int i = 0; i < 3; i++) {
      board[i] = new char[3];
    }
    m->toChar(board);
    char b[3][3];
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
	b[j][k] = board[j][k];
      }
    }

    //On vide board
    for (int i = 0; i < 3; i++) {
      delete[] board[i];
    }
    delete[] board;
    Move bestMove = findBestMove(b);

    /* On charge l'état de la partie dans la première couche du réseau de neurones */
    int * etat = m->getJeu();
    for (int j = 0; j < 9; j++) {
      c1->getNeurones()[j]->setValue(etat[j]);
    }
    delete[] etat;
    /* On évalue le réseau de neurones en entier */
    c2->eval();
    c3->eval();
    c4->eval();

    /* On calcule l'erreur sur la dernière couche */
    for (int j = 0; j < 9; j++) {
      if (bestMove.row*3 + bestMove.col == j) { //Possibilité d'erreur ************************ à vérifier si bug
	std::cout << "Meilleur mouvement : " << bestMove.row << " / " << bestMove.col << std::endl;
	std::cout << "Meilleur mouvement = " << j << std::endl;
	c4->getNeurones()[j]->setErreur(1-c4->getNeurones()[j]->getValue());
      } else { 
	c4->getNeurones()[j]->setErreur(-c4->getNeurones()[j]->getValue());
      }
    }

    /* On rétropropage l'erreur */
    c4->updateErreur();
    c3->updateErreur();
    c2->updateErreur();

    /* On met à jour les poids */
    c4->updatePoids();
    c3->updatePoids();
    c2->updatePoids();

    /* On affiche l'erreur de la dernière couche */
    for (int j = 0; j < 9; j++) {
      std::cout << "Valeur " << j << " : " << (c4->getNeurones()[j]->getValue()) << std::endl;
    }
    delete m;
  }
  return 0;
}






  

//int main() {
  /*
  srand (time(NULL));
 
  Couche * c1 = new Couche(3);
  Couche * c2 = new Couche(2);
  Couche * c3 = new Couche(1);
  c2->relier(c1);
  c3->relier(c2);

  for (int i = 0; i < 100000; i++) { //Entrainement
    int a = rand()%2,b = rand()%2, c = rand()%2, result = 1;
    if (c == 1) {
      result = 0;
    }
    
    c1->getNeurones()[0]->setValue(a);
    c1->getNeurones()[1]->setValue(b);
    c1->getNeurones()[2]->setValue(c);

    c2->eval();
    c3->eval();

    c3->getNeurones()[0]->setErreur(result-c3->getNeurones()[0]->getValue());
    
    //  Condition nécessaire avant de rétropropager l'erreur :
    //  Les erreurs de couches précédentes doivent être réinitialiser à 0
    
    c2->resetErreur();
    c3->updateErreur(); //Rétropropagation de l'erreur à la couche 2

    c1->resetErreur();
    c2->updateErreur();

    c3->updatePoids();
    c2->updatePoids();

    std::cout << "Erreur " << i << " : " << c3->getNeurones()[0]->getErreur() << std::endl;
  }
  float somme = 0;
  for (int i = 0; i < 10000; i++) { //Entrainement
    int a = rand()%2,b = rand()%2, c = rand()%2, result = 1;
    if (c == 1) {
      result = 0;
    }
    
    c1->getNeurones()[0]->setValue(a);
    c1->getNeurones()[1]->setValue(b);
    c1->getNeurones()[2]->setValue(c);

    c2->eval();
    c3->eval();

    c3->getNeurones()[0]->setErreur(result-c3->getNeurones()[0]->getValue());
    
    //  Condition nécessaire avant de rétropropager l'erreur :
    //  Les erreurs de couches précédentes doivent être réinitialiser à 0
    
    c2->resetErreur();
    c3->updateErreur(); //Rétropropagation de l'erreur à la couche 2

    c1->resetErreur();
    c2->updateErreur();

    //c3->updatePoids();
    //c2->updatePoids();

    somme += c3->getNeurones()[0]->getErreur();
  }
  std::cout << "Erreur test : " << somme/10000.f << std::endl;
  */
  /*
  Morpion * m = new Morpion(1);
  m->afficher();
  m->toChar();
  
  while (m->estTermine() == 0) {
    int x,y;
    do {
      std::cin >> x;
      std::cin >> y;
    }
    while (!(m->jouer(x,y)));
    m->jeuRandom();
    m->afficher();
  }
  std::cout << m->estTermine() << std::endl;*/
  //return 0;
  //}
