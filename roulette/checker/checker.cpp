#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerChecker("roulette", argc, argv);
	compareRemainingLines();
}
