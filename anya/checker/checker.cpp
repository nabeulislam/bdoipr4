#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
	registerChecker("anya", argc, argv);
	compareRemainingLines();
}
