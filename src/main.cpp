#include <iostream>
#include <string>
#include <future>
#include <chrono>
#include <syncstream>

using namespace std;
using namespace std::chrono;

void do_task(const string& name, int sec) {
    this_thread::sleep_for(seconds(sec));
    osyncstream(cout) << name << '\n';
}

void work() {
    auto start = steady_clock::now();

    auto futA2 = async(launch::async, do_task, "A2", 7);
    auto futB2 = async(launch::async, do_task, "B2", 7);

    do_task("A1", 1);
    do_task("A3", 1);
    do_task("A4", 1);

    futA2.get();
    futB2.get();

    do_task("B1", 1);

    do_task("C", 1);

    auto finish = steady_clock::now();
    auto elapsed = duration_cast<seconds>(finish - start).count();

    osyncstream(cout) << "Total time: " << elapsed << " s\n";
    osyncstream(cout) << "Work is done!\n";
}

int main() {
    work();
    return 0;
}