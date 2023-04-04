#include <iostream>
#include <vector>
#include <iomanip>
#include "doprava.hpp"

//Feel free to create your solution in multiple files
// and add the includes here. e.g.:
//#include "solution.hpp"


void print_header(Line &tmp_line, const std::string &stop, int j);

Time_table &print_time(Time_table &time);

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
        Time_table time; // time struct
        Line tmp_line;
        int nmb_of_lines = net.nlines(); // number of lines
        for (std::string stop: stop_in) {
            for (int j = 0; j < nmb_of_lines; ++j) {
                tmp_line = net.getLine(j);
                auto find_stop = std::find(tmp_line.stops.begin(), tmp_line.stops.end(),
                                           stop); // try to find input stop in current line
                if (find_stop != tmp_line.stops.end()) { // if our stop is in current line
                    print_header(tmp_line, stop, j); // printing header

                    time.counter = 0;
                    char oldFill = std::cout.fill(' '); // default fill
                    auto index = std::distance(tmp_line.stops.begin(), find_stop); // get index of our station
                    for (unsigned int k = 0; k < net.getLine(j).conns_fwd.size(); ++k) {
                        auto time_def = net.getLine(j).conns_fwd[k];
                        time.seconds = time_def.at(index).ti.gets();
                        time.hours = time.seconds / 3600;
                        time.minutes = (time.seconds % 3600) / 60;
                        if ((time.counter < time.hours) && (k == 0)){ // print rest of time in begin
                            for (unsigned int t = 0; t < time.hours; ++t){
                                std::cout << "\n| " << std::setw(2) << std::setfill('0') << t << " |";
                                time.counter ++;
                            }
                        }
                        time = print_time(time);
                    }

                    time.counter = time.hours;
                    if (time.counter < 23){ // print rest of time in end
                        for (unsigned int t = time.counter + 1; t <= 23; ++t){
                            std::cout << "\n| " << std::setw(2) << std::setfill('0') << t << " |";
                            time.counter ++;
                        }
                    }
                    std::cout.fill(oldFill); // set fill to default
                    std::cout << "\n";
                }
                //tmp_line.stops.clear(); // clear tmp_line, it is not mandatory
            }
        }



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

Time_table &print_time(Time_table &time) {
    if (time.tmp_hours != time.hours) {
        std::cout << "\n| " << std::setw(2) << std::setfill('0') << time.hours << " | " << std::setw(2) << std::setfill('0') << time.minutes;
    }
    else if (time.tmp_hours == time.hours) {
        std::cout << " " << std::setw(2) << std::setfill('0') << time.minutes;
    }
    time.tmp_hours = time.hours;
    return time;
}

void print_header(Line &tmp_line, const std::string &stop, int j) {
    std::cout << "+------------------------------------------------------------------------------+\n";
    std::cout << "| " << stop << std::setw(76 - stop.size()) << "Line: " << j << "|\n";
    std::cout << "+--------------------------------------++--------------------------------------+\n";
    std::string last_stop = tmp_line.stops.back().erase(tmp_line.stops.back().find("\r"),
                                                        2); // remove \r symbol
    std::cout << "| To: " << last_stop << std::setw(40 - last_stop.length()) << "|| To: "
              << tmp_line.stops[0] << std::setw(35 - tmp_line.stops[0].size()) << "|\n";
    std::cout << "+----+---------------------------------++----+---------------------------------+";
}
