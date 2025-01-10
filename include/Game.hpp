#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <random>

class Game{
    public:
        Game( const std::string& language );
        ~Game();

        void run();
        void version();
    private:
        enum Suit{
            Copas   = 1,
            Espadas = 2,
            Ouros   = 3,
            Paus    = 4
        };

        struct Card {
            unsigned int value;
            std::string name;
            std::string type; 
        };

        std::vector< Card > cards;
        std::vector< Card > player_deck;
        std::vector< Card > computer_deck;

        std::map< std::string, std::string > english_phrases;
        std::map< std::string, std::string > portuguese_phrases;
        std::map< std::string, std::string > portuguese_commands;
        std::map< std::string, std::string > english_commands;
        std::map< std::string, std::string > english_suits;
        std::map< std::string, std::string > portuguese_suits;
        std::map< std::string, std::string > phrases;
        std::map< std::string, std::string > commands;
        std::map< std::string, std::string > suits;

        const std::string dev_name = "Diego Ferreira";
        const std::string ver = "2.5";

        bool loop;

    private:
        void create_phrases();
        void create_deck();
        Card get_card();
        unsigned int check_points( const std::vector< Card >& deck );
        void show_deck( const std::vector< Card > deck );
        void help();
        void shuffle();
        std::string convert( const unsigned int& value );


};