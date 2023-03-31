#include <iostream>
#include <vector>
#include <iomanip>
#include "doprava.hpp"

//Feel free to create your solution in multiple files
// and add the includes here. e.g.:
//#include "solution.hpp"


int main(int argc, char **argv) {

    // Load files:
    DriverList dl;
    dl.loadFromFile("driver_list.txt");

    Network net;
    net.loadFromFile("network.txt");

    // variables for argument decoding
    std::string flag_in;
    std::list<std::string> stop_in;

    if (argc > 1)
        flag_in = std::string(argv[1]);
    else {
        std::cerr << "Missing argument. Terminating." << "\n";
        return 1;
    }

    if ((!flag_in.compare("--schedule"))) {
        // input check - do not edit
        if (argc > 2) {
            for (int i = 2; i < argc; i++) {
                std::string temp = argv[i];
                replace(temp.begin(), temp.end(), '_', ' ');
                stop_in.push_back(temp);
            }
        } else {
            std::cerr << "Missing stop name. Terminating." << "\n";
            return 2;
        }
        // end of input check
        std::cout << "\n";
        Line tmp_line;
        int nmb_of_lines = net.nlines(); // number of lines
        for (unsigned long i = 0; i < stop_in.size(); ++i) {
            auto first = stop_in.begin();
            std::advance(first, i);
            for (int j = 0; j < nmb_of_lines; ++j) {
                tmp_line = net.getLine(j);
                auto find_stop = std::find(tmp_line.stops.begin(), tmp_line.stops.end(),
                                           *first); // try to find input stop in current line
                if (find_stop != tmp_line.stops.end()) { // if our stop is in current line
                    std::cout << "For stop: " << *first << "\nFirst stop: " << tmp_line.stops[0] << "\nLast stop: "
                              << tmp_line.stops.back()
                              << "\n\n"; // print first and last stop in curren line
                    // TODO print table
                }
                tmp_line.stops.clear(); // clear tmp_line, it is not mandatory
            }
        }



//        unsigned int stops_cnt = stop_in.size();
//        for (std::string stop : stop_in){
//            std::cout << "+------------------------------------------------------------------------------+\n";
//            std::cout << "| " << stop << std::setw(79-stop.size()) << "Line: L |\n";
//        }

        /* here should start the code for printing timetables*/
        /* stop_in contains names of stops, for which the timetable is to be printed. */

        // This is an example, how it can be done using lambda-function
//        for_each(stop_in.begin(), stop_in.end(), [&] (std::string stop_name) {print_timetable(net,stop_name);} );
        // This is an example, how it can be done using for-loop 
        // for( auto iter = stop_in.begin(); iter != stop_in.end(); iter++) print_timetable(net,*iter);

        /* here should end the code for printing timetables*/
    } else if ((!flag_in.compare("--line-routing"))) {

        /* here should start the code for printing line routes without stats*/



        /* here should end the code for printing line routes without stats*/
    } else if ((!flag_in.compare("--driver-stops"))) {

        /* here should start the code for stops statistics for drivers */



        /* here should end the code for stops statistics for drivers */
    } else {
        std::cout << "Flag not recognized, terminating." << "\n";
    }

    return 0;
}