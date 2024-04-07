#include "processor.hpp"

int main(int argc, const char *argv[]) {

  Processor processor;
  processor.welcomeMessage();
  if (processor.modeSelection() == 1) {
    return 0;
  }
  if (processor.gameSetUp() == 0) {
    processor.gameProcessing();
  } else {
    return 0;
  }
  return 0;
}
