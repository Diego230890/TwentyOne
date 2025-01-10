
#include "../include/Game.hpp"

int main( int argc, char** argv ){
    
    if( argc == 2 ){
        std::string option = argv[ 1 ];
        if( option == "help" || option == "ajuda" ){
            std::cout << "help \t- Shows this help text." << std::endl;
            std::cout << argv[ 0 ] << " pt runs the game in portuguese." << std::endl;
            std::cout << argv[ 0 ] << " en runs the game in english." << std::endl;
        }
        else if( option == "pt" || option == "en" ){ 
            Game game( option );
            game.run(); 
        }
        else{ std::cout << "Type " << argv[ 0 ] << " help for more information." << std::endl; }
    }
    else if( argc == 1 ){ std::cout << "type " << argv[ 0 ] << " help  for more information."<< std::endl; }
    
}



