#include <iostream>
#include <vector>

// ------------ DECLARATIONS
const std::string cardValues[13] = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K", "A"};
const char suits[4] = {'h','d','s','c'};
std::vector<std::string> playerHand;
std::vector<std::string> dealerHand;
std::vector<std::string> dealtCards;
std::string getCard();
std::string player = "Player";
std::string dealer = "Dealer";
int playerPoints = 0;
int dealerPoints = 0;
std::string newCard;
char keyPress;
int getRandomIndex(int num);
int checkTotalPoints(std::vector<std::string> hand);
int getCardValue(std::string card);
bool checkBust(int points);
void checkWinner(int playerPoints, int dealerPoints);
void pushCard(std::string card, std::vector<std::string>& hand, std::vector<std::string>& cardsAlreadyDealt);
void playerHitOrStand(char keyPress, std::string newCard, int playPoints, std::vector<std::string>& playerHand, int dealerPoints, std::vector<std::string>& dealerHand, std::vector<std::string>& cardsAlreadyDealt);
void dealerHitOrStand(int points, std::vector<std::string>& hand, std::vector<std::string>& cardsAlreadyDealt);
void printHand(std::string user, int points, std::vector<std::string> hand);
int addPoints(int points, std::vector<std::string> hand);
int addPoints(int points, std::string card);
void currentState(std::vector<std::string> playerHand, int playerPoints, std::vector<std::string> dealerHand, int dealerPoints, std::vector<std::string> dealtCards);
std::string dealCard(std::vector<std::string>& cardsAlreadyDealt);
// ------------

// ------------
int main() {
    
    std::cout << "---------------------\n";
    std::cout << "      Black Jack     \n";
    std::cout << "---------------------\n";
    std::cout << "\n";

    // -------------
    newCard = dealCard(dealtCards); // deal first card
    pushCard(newCard, playerHand, dealtCards);
    
    newCard = dealCard(dealtCards); // deal second card
    pushCard(newCard, playerHand, dealtCards);

    playerPoints = addPoints(playerPoints, playerHand);
    printHand(player, playerPoints, playerHand);

    if(checkBust(playerPoints)) {
        std::cout << "\n";
        std::cout << "BUST! -- YOU LOSE\n";
        std::cout << "\n";
        return 0;
    };
    // ------------

    // ------------
    newCard = dealCard(dealtCards);
    pushCard(newCard, dealerHand, dealtCards);

    newCard = dealCard(dealtCards);
    pushCard(newCard, dealerHand, dealtCards);

    dealerPoints = addPoints(dealerPoints, dealerHand);
    std::cout << "Dealer's hand: ";
    std::cout << dealerHand[0] << " " << "--"; // show dealers first card only
    std::cout << "  ";
    std::cout << "Score: " << "--\n";
    std::cout << "--------------------\n";
    std::cout << "\n";
    // ------------

    // ------------
    do {
        std::cout << "\n";
        std::cout << "Hit or stand? (press 'h' or 's'): \n";

        std::cin >> keyPress; // capture keyPress
        std::cout << "\n";

        if (keyPress == 'h') {
            newCard = dealCard(dealtCards); // deal new card
            pushCard(newCard, playerHand, dealtCards);
            playerPoints = addPoints(playerPoints, newCard);

            printHand(player, playerPoints, playerHand);
            std::cout << "Dealer's hand: ";
            std::cout << dealerHand[0] << " --"; // show dealers first card only
            std::cout << "  ";
            std::cout << "Score: --\n";
            std::cout << "--------------------\n";

            if (checkBust(playerPoints)) {
                std::cout << "\n";
                std::cout << "BUST! -- YOU LOSE\n";
                std::cout << "\n";
                return 0;
            };
        }
    } while (keyPress != 's');
    // ------------


    // ------------
    if (keyPress == 's') {
        std::cout << "\n";
        std::cout << "Dealer's Turn...\n";
        std::cout << "\n";
        while (dealerPoints < 17) {
            newCard = dealCard(dealtCards);
            pushCard(newCard, dealerHand, dealtCards);
            dealerPoints = addPoints(dealerPoints, newCard);
        };

        printHand(player, playerPoints, playerHand);
        printHand(dealer, dealerPoints, dealerHand);

    // ------------
    // currentState(playerHand, playerPoints, dealerHand, dealerPoints, dealtCards);
    // ------------
        checkWinner(playerPoints, dealerPoints); // print the result
    }
    
    return 0;
}

// utilities
std::string dealCard(std::vector<std::string>& cardsAlreadyDealt) {
    std::string card = getCard();
    for(std::string dealtCard : cardsAlreadyDealt) {
        while (dealtCard == card){
            card = getCard();
        }
    }
    return card;
}
std::string getCard() {
    int numberIndex = getRandomIndex(13);
    int suitIndex = getRandomIndex(4);
    std::string card = cardValues[numberIndex] + suits[suitIndex];
    return card;
}
int getRandomIndex(int num) {
    srand(time(0));
    return rand() % num;
}

void pushCard(std::string card, std::vector<std::string>& hand, std::vector<std::string>& cardsAlreadyDealt) {
    hand.push_back(card); // push to players hand
    cardsAlreadyDealt.push_back(card); // push to already dealt cards to no repeats are dealt
}

int addPoints(int points, std::vector<std::string> hand) {
    for (std::string card : hand) {
        points += getCardValue(card);
    }
    return points;
}

int addPoints(int points, std::string card) {
    points += getCardValue(card);
    return points;
}

void printHand(std::string user, int points, std::vector<std::string> hand) {
    std::cout << user << "'s hand: ";
    for(std::string card : hand) { 
        std::cout << card << " ";
    }
    std::cout << "  ";
    std::cout << "Score: " << points << "\n";
    std::cout << "--------------------\n";
    std::cout << "\n";
}

bool checkBust(int points) {
    if (points > 21) {
        return true;
    }
    return false;
}

void currentState(std::vector<std::string> playerHand, int playerPoints, std::vector<std::string> dealerHand, int dealerPoints, std::vector<std::string> dealtCards) {
    std::cout << "Current state: " << "\n";
    std::cout << "playerHand: ";
    for(std::string card : playerHand){
        std::cout << card << " ";
    }
    std::cout << "\n";
    std::cout << "playerPoints: " << playerPoints << "\n";
    std::cout << "dealerHand: ";
    for(std::string card : dealerHand){
        std::cout << card << " ";
    }
    std::cout << "\n";
    std::cout << "dealerPoints: " << dealerPoints << "\n";
    std::cout << "dealtCards: ";
    for(std::string card : dealtCards){
        std::cout << card << " ";
    }
    std::cout << "\n";
    std::cout << "-------------------\n";
    std::cout << "\n";
}

void checkWinner(int playerPoints, int dealerPoints) {
    if (dealerPoints > 21) {
        std::cout << "YOU WIN -- DEALER BUSTS!\n";
        return;
    }
    if (playerPoints == dealerPoints) {
        std::cout << "TIE\n";
        return;
    }
    if (dealerPoints > playerPoints) {
        std::cout << "YOU LOSE\n";
        return;
    }
    if (playerPoints > dealerPoints) {
        std::cout << "YOU WIN\n";
        return;
    }
    return;
}
    
int getCardValue(std::string card) {
    char cardValue = card[0];
    int value;
    switch (cardValue) {
        case '2':
            value = 2;
            break;
        case '3':
            value = 3;
            break;
        case '4':
            value = 4;
            break;
        case '5':
            value = 5;
            break;
        case '6':
            value = 6;
            break;
        case '7':
            value = 7;
            break;
        case '8':
            value = 8;
            break;
        case '9':
            value = 9;
            break;
        case '1':
            value = 10;
            break;
        case 'J':
            value = 10;
            break;
        case 'Q':
            value = 10;
            break;
        case 'K':
            value = 10;
            break;
        case 'A':
            value = 11;
            break;
        default:
            break;
    }
    return value;
}