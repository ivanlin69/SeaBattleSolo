#ifndef processor_hpp
#define processor_hpp

#include "ocean.hpp"
#include <memory>

class Processor {

private:
  std::unique_ptr<Ocean> ocean;
  int mode;

public:
  Processor() { mode = 1; };
  void modeSelection();
  void gameSetUp();
  void gameProcessing();
};

#endif
