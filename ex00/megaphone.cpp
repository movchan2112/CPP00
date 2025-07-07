#include <iostream> 

int main(int argc, char **argv) {

    if(argc > 1)
    {
        for(int i = 1; i < argc; i++)
        {
            for(int n = 0; argv[i][n] != '\0';n++)
            {
                char c = std::toupper(argv[i][n]);
                std::cout << c;
            }
            std::cout << std::endl;
        }
    }
    else
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
    return 0;
}