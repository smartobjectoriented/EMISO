
#ifndef EMISO_CLI_H
#define EMISO_CLI_H

#include <iostream>
#include <readline/readline.h>
#include <readline/history.h>

#include "../daemon/image.hpp"

namespace emiso {

    class Cli {
    public:
    	Cli();

		// Destructor
        ~Cli();

        void start();

    private:
    	const std::string _prompt = "(emiso)>> ";
    	daemon::Image _image;


    	void splitCmd(std::string const &str, const char delim, std::vector<std::string> &out);

    	void handleHelloCommand();
		void handleHelpCommand();
		void handleImagesCommand(std::vector<std::string> &tockens);
    };
}

#endif // EMISO_CLI_H
