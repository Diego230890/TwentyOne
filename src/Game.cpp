#include "../include/Game.hpp"

Game::Game( const std::string& language ) : loop( true ){
    create_phrases();

    if( language == "en" ){
        phrases = std::move( english_phrases );
        commands = std::move( english_commands );
        suits = std::move( english_suits );
    }
    else{
        phrases = std::move( portuguese_phrases );
        commands = std::move( portuguese_commands );
        suits = std::move( portuguese_suits );
    }

    create_deck();
    shuffle();
}

Game::~Game(){
    if( cards.size() > 0 ){ cards.clear(); cards.shrink_to_fit(); }
    if( player_deck.size() > 0 ){ player_deck.clear(); player_deck.shrink_to_fit(); }
    if( computer_deck.size() > 0 ){ computer_deck.clear(); computer_deck.shrink_to_fit(); }

}

void Game::run(){
    
    std::string option;
    
    unsigned short int player_points;
    unsigned short int computer_points;

    bool new_game = false;
    bool inner_loop = false;

    while( loop ){    
        std::cout << phrases[ "main info" ] << std::endl;
        //std::cin.ignore();
        std::getline( std::cin, option );

        if( option == commands[ "help command" ] ){
            std::cout << phrases[ "help main help" ] << std::endl;
            std::cout << phrases[ "play main help" ] << std::endl;
            std::cout << phrases[ "exit main help" ] << std::endl;
        }
        else if( option == commands[ "exit command" ] ){ 
            loop = false; 
        }
        else if( option == commands[ "play command" ] ){
            while( loop ){
                std::cout << phrases[ "main info" ] << std::endl;
               // std::cin.ignore();
                std::getline( std::cin, option );

                if( option == commands[ "help command" ] ){ help(); }
                else if( option == commands[ "stop command" ] ){
                    
                    new_game = false;
                    inner_loop = true;

                    player_points = check_points( player_deck );
                    computer_points = check_points( computer_deck );

                    if( player_points > computer_points ){
                        std::cout << phrases[ "you lost" ] << std::endl;
                    }
                    else if( computer_points > player_points ){
                        std::cout << phrases[ "computer lost" ] << std::endl;
                    }
                    else if(  computer_points == player_points ){
                        std::cout << phrases[ "tie" ] << std::endl;
                    }

                    std::cout << phrases[ "you have" ]<< player_points << phrases[ "points" ] << std::endl;
                    std::cout << phrases[ "your deck" ] << std::endl;
                    show_deck( player_deck );

                    std::cout << std::endl << phrases[ "computer have" ] << computer_points << phrases[ "points" ] << std::endl;
                    std::cout << phrases[ "computer deck" ] << std::endl;
                    show_deck( computer_deck );

                    while( inner_loop ){
                        std::cout << phrases[ "game over" ] << std::endl;
                        std::cin >> option;

                        if( option == commands[ "exit command" ] ){ inner_loop = false; new_game = false; }
                        if( option == commands[ "new command" ] ){
                            player_deck.clear();
                            player_deck.shrink_to_fit();

                            computer_deck.clear();
                            computer_deck.shrink_to_fit();

                            std::cout << phrases[ "new game" ] << std::endl;
                            new_game = true;
                            inner_loop = false;
                        }

                    }
                    if( inner_loop == false && new_game == false ){ 
                        loop = false; 
                    }
                    
                }
                else if( option == commands[ "get command" ] ){
                    
                    new_game = false;
                    inner_loop = true;
                    if( cards.size() > 10 ){
                        player_deck.emplace_back( get_card() );
                        computer_deck.emplace_back( get_card() );
                    }
                    else{
                        cards.clear();
                        cards.shrink_to_fit();
                        create_deck();
                        shuffle();
                    }
                    
                    Card last_player_card = player_deck.back();

                    player_points = check_points( player_deck );
                    computer_points = check_points( computer_deck );
                    
                    std::cout << phrases[ "you have a new card" ] << last_player_card.name << " " <<  last_player_card.type << std::endl;
                    if( player_deck.size() == 0 ){ 
                        std::cout << phrases[ "you dont have any card" ] << std::endl; 
                    }
                    else{
                        if( player_points == 21 ){
                            std::cout << phrases[ "you win" ] << std::endl;
                        }
                        else if( computer_points == 21 ){
                            std::cout << phrases[ "computer wins" ] << std::endl;
                        }
                        else if( player_points >= 21 || computer_points >= 21 ){
                            if( player_points == computer_points ){
                                std::cout << phrases[ "tie" ] << std::endl;
                            }
                            else if( player_points > 21 && computer_points < player_points ){
                            std::cout << phrases[ "you lost" ] << std::endl;
                            }
                            else if( computer_points > 21 && player_points < computer_points  ){
                                std::cout << phrases[ "computer lost" ] << std::endl;
                            }
                        } 
                        else if( player_points < 21 && computer_points != 21 ){
                            std::cout << phrases[ "you have" ] << player_points << phrases[ "points" ] << std::endl;
                        }

                        if( player_points >= 21 || computer_points >= 21 ){

                            std::cout << phrases[ "you have" ] << " " << player_points << phrases[ "points" ] << std::endl;
                            std::cout << phrases[ "your deck" ] << ":" << std::endl;
                            show_deck( player_deck );

                            std::cout << std::endl << phrases[ "computer have" ] << computer_points << phrases[ "points" ] << std::endl;
                            std::cout << phrases[ "computer deck" ]  << ":" << std::endl;
                            show_deck( computer_deck );

                            while( inner_loop ){
                                std::cout << phrases[ "game over" ] << std::endl;
                                std::getline( std::cin, option );

                                if( option == commands[ "exit command" ] ){ inner_loop = false; new_game = false; }
                                if( option == commands[ "new command" ] ){
                                    player_deck.clear();
                                    player_deck.shrink_to_fit();

                                    computer_deck.clear();
                                    computer_deck.shrink_to_fit();

                                    std::cout << phrases[ "new game" ] << std::endl;
                                    new_game = true;
                                    inner_loop = false;
                                }

                            }
                            if( inner_loop == false && new_game == false ){ 
                                loop = false; 
                            }
                        }

                    }
                }
                else if( option == commands[ "exit command" ] ){ loop = false; }
                else if( option == commands[ "version command" ] ){ version(); }
                else if( option == commands[ "list command" ] ){ show_deck( player_deck ); }
                else{ std::cout << commands[ "command" ] << option << " " << commands[ "invalid" ] << std::endl; }
            }
        }
        else{ 
            std::cout << commands[ "command" ] << option << " " << commands[ "invalid" ] << std::endl;
        }
    }
}

void Game::create_phrases(){
    portuguese_phrases = { { "main info","Digite a opção desejada, ou digite ajuda para obter informações sobre como jogar." },
                           { "help main help", "ajuda -\t Imprime esse guia de ajuda." },
                           { "play main help", "jogar -\t Inicia o jogo." },
                           { "exit main help", "sair -\t sair do jogo." },
                           { "you have a new card", "Voce obteve uma nova carta: " },
                           { "you dont have any card", "Você não obteve nehuma carta." },
                           { "you win", "Você Ganhou !!!" },
                           { "computer win", "O computador ganhou !!!" },
                           { "tie", "Empate !!!" },
                           { "you lost", "Você Perdeu !!!" },
                           { "computer lost", "O computador perdeu !!!" },
                           { "you have", "Você possui " },
                           { "points", " pontos." },
                           { "your deck", "Seu deck:" },
                           { "computer have" ,"O computador possui " },
                           { "computer deck", "Deck do computador: " },
                           { "game over", "O jogo Acabou. Digite sair ou novo para iniciar um novo jogo:" },
                           { "new game", "NOVO JOGO" }, 
                           { "help game help", "ajuda  -\t Mostra esse texto de ajuda." },
                           { "get game help", "obter  -\t Obtem uma nova carta." },
                           { "list game help", "listar -\t Mostra suas cartas" },
                           { "version game help", "versão -\t Mostra a versão do jogo" },
                           { "quit game help", "sair   -\t Sai do jogo." },
                           { "no more cards", "Não há mais cartas no baralho para obter." },
                           { "your deck is empty", "Seu deck está vazio digite obter para obter uma carta."},
                           { "created by", "Criado por "},
                           { "version", " Versão " } };
    
    portuguese_commands = { { "help command", "ajuda" },
                            { "play command", "jogar" },
                            { "exit command", "sair" },
                            { "version command", "versão" },
                            { "list command", "listar" },
                            { "stop command", "parar" },
                            { "get command", "obter" },
                            { "new command", "novo" },
                            { "command", "comando "},
                            { "invalid", " inválido" } };
    
    english_phrases = { { "main info","Type the chosen option, or type help to get information about how to play." },
                        { "help main help", "help -\t Show this help guide." },
                        { "play main help", "play -\t Starts the game." },
                        { "exit main help", "quit -\t Quit the game." },
                        { "you have a new card", "You have a new card: " },
                        { "you dont have any card", "You dont have any cards." },
                        { "you win", "You Win !!!" },
                        { "computer win", "The Computer Wins!!!" },
                        { "tie", "Tie !!!" },
                        { "you lost", "You Lost !!!" },
                        { "computer lost", "The Computer Lost !!!" },
                        { "you have", "You have " },
                        { "points", " points." },
                        { "your deck", "Your deck:" },
                        { "computer have" ,"The computer have " },
                        { "computer deck", "Computer Deck: " },
                        { "game over", "The game is over. Type quit or new to play a new game:" },
                        { "new game", "NEW GAME" }, 
                        { "help game help", "help  -\t Shows this help." },
                        { "get game help", "get  -\t Get a new card." },
                        { "list game help", "list -\t Shows your cards" },
                        { "version game help", "version -\t Shows the game version" },
                        { "exit game help", "quit   -\t Quit the Game." },
                        { "no more cards", "No more cards." },
                        { "your deck is empty", "Your deck is empty, type get to obtain a new card." },
                        { "created by", "Created by "},
                        { "version", " Version " } };
    
    english_commands = { { "help command", "help" },
                         { "play command", "play" },
                         { "exit command", "quit" },
                         { "version command", "version" },
                         { "list command", "list" },
                         { "stop command", "stop" },
                         { "get command", "get" },
                         { "new command", "new" },
                         { "command", " command"},
                         { "invalid", " invalid" } };
    
    portuguese_suits = { { "spades", "Espadas" },
                         { "diamonds", "Ouros" },
                         { "hearts", "Copas" },
                         { "clubs", "Paus" } };

    english_suits = { { "spades", "Spades" },
                      { "diamonds", "Diamonds" },
                      { "hearts", "Hearts" },
                      { "clubs", "Clubs" } };
}

void Game::create_deck(){
    
    const unsigned int cards_size = 53;
    Card card;
    unsigned int suit_of_cards = 1;
    unsigned int card_value = 1;
    for( unsigned int i = 1; i < cards_size; i++ ){
        if( suit_of_cards == Suit::Copas ){
            card.value = card_value;
            card.name = convert( card_value );
            card.type = suits[ "hearts" ];

            card_value++;

            cards.emplace_back( card );
        }
        else if( suit_of_cards == Suit::Espadas ){
            card.value = card_value;
            card.name = convert( card_value );
            card.type = suits[ "spades" ];

            card_value++;

            cards.emplace_back( card );
        }
        else if( suit_of_cards == Suit::Ouros ){
            card.value = card_value;
            card.name = convert( card_value );
            card.type = suits[ "diamonds" ];

            card_value++;

            cards.emplace_back( card );
        }
        else if( suit_of_cards == Suit::Paus ){
            card.value = card_value;
            card.name = convert( card_value );
            card.type = suits[ "clubs" ];

            card_value++;

            cards.emplace_back( card );
        }

        if( i % 13 == 0 ){
            suit_of_cards++;
            card_value = 1;
        }
    }

    for( auto& it : cards ){
        if( it.value == 1 ){ it.name = "A"; }
        if( it.value == 11 ){ it.name = "J"; }
        if( it.value == 12 ){ it.name = "Q"; }
        if( it.value == 13 ){ it.name = "K"; }
    }
}

Game::Card Game::get_card(){
    Card aux;
    if( cards.size() > 0 ){
        aux = cards.back();
        cards.pop_back();
    }
    else{ std::cout << phrases[ "no more cards" ] << std::endl; }

    return aux;
}

unsigned int Game::check_points( const std::vector< Card >& deck ){
    unsigned int sum = 0;
    for( auto& it : deck ){
        sum += it.value;
    }

    return sum;
}

void Game::show_deck( const std::vector< Card > deck ){
    if( deck.size() == 0 ){ std::cout << phrases[ "your deck is empty" ] << std::endl; }
    for( auto& it : deck ){
        std::cout << it.name << " " << it.type << std::endl;
    }
}

void Game::help(){
    std::cout << phrases[ "help game help" ] << std::endl;
    std::cout << phrases[ "get game help" ] << std::endl;
    std::cout << phrases[ "list game help" ] << std::endl;
    std::cout << phrases[ "version game help" ] << std::endl;
    std::cout << phrases[ "quit game help" ] << std::endl;
}

void Game::shuffle(){
    std::random_device random_dev;
    std::mt19937 mersenne_twister( random_dev() );
    std::shuffle( cards.begin(), cards.end(), mersenne_twister );
}

std::string Game::convert( const unsigned int& value ){
    std::stringstream conv;
    std::string aux;
    conv << value;
    conv >> aux;
    conv.clear();

    return aux;
}

void Game::version(){ std::cout << phrases[ "created by" ] << dev_name << phrases[ "version" ] << ver << std::endl; }
