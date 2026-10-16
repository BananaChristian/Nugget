#include "engine.h"

int main(void) {
  Engine engine = {0};

  bool initialized = engine_init(&engine);

  if (initialized)
    engine_run(&engine);

  engine_destroy(&engine);

  return initialized ? 0 : 1;
}
